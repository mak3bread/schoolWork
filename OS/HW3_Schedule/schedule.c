#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <setjmp.h>
#include <malloc.h>
#include <memory.h>
#include <sys/time.h>
#include "schedule.h"


// task switching시 저장되어야 하는 정보
struct frame {
    unsigned long flags;
    unsigned long ebp;
    unsigned long edi;
    unsigned long esi;
    unsigned long edx;
    unsigned long ecx;
    unsigned long ebx;
    unsigned long eax;
    unsigned long retaddr;
    unsigned long retaddr2;
    unsigned long data;
};

typedef struct sch_handle_tag {
    int child_task;
    
    TaskInfo running_task;
    TaskInfo root_task;
} SchHandle;

TaskInfo readyQueue[3]; //multilevel feedback queue(큐의 header level만 저장)
int level = 0; //현재 실행중인 queue의 단계 초기화 0~2 이다.
int timequantum = 0; //timequantum 초기화 RR에서 이용된다.

// global schedule handler
SchHandle gh_sch;

// task data struct
TaskInfo task_get_runningtask();
void task_insert(TaskInfo taskinfo);
void task_delete(TaskInfo taskinfo);
void task_next();
void scheduler();
void parent_task();

void task_change(TaskInfo taskinfo); //다음 queue로 넘어가는 함수 선언

/* thread_create : task를 생성하는 함수로 taskinfo 구조체를 할당하고 구성한다  */
TaskInfo thread_create(TaskFunc callback, void *context) {
    TaskInfo taskinfo;
    // task를 위한 공간 할당
    taskinfo = malloc(sizeof(*taskinfo));
    memset(taskinfo, 0x00, sizeof(*taskinfo));
    
    {
        struct frame *f = (struct frame *) &taskinfo->stack[THREAD_STACKSIZE
                                                            - sizeof(struct frame) / 4];
        // taskinfo로 할당된 공간 중 stack 부분 뒤쪽에 frame을 위한 공간으로 할당
        // 이에 task가 수행되면서  stack공간을 활용
        int i;
        for (i = 0; i < THREAD_STACKSIZE; ++i) { // stack overflow check
            taskinfo->stack[i] = i;
        }
        memset(f, 0, sizeof(struct frame));
        f->retaddr = (unsigned long) callback;
        f->retaddr2 = (unsigned long) thread_kill;
        f->data = (unsigned long) context;
        taskinfo->sp = (unsigned long) &f->flags;
        f->ebp = (unsigned long) &f->eax;
    }
    // task 생성에 따라 gh_sch에 child task가 늘었음을 표시
    gh_sch.child_task++;
    // gh_sch.child_task 값으로 task_id 할당
    taskinfo->task_id = gh_sch.child_task;
    // task 생성시 TASK_READY로 상태를 설정함
    taskinfo->status = TASK_READY;
    // taskinfo구조체들의  linkedlist에  새 thread의  taskinfo 구조체를 삽입
    task_insert(taskinfo);
    
    return taskinfo;
}

/* thread_init : 초기화 함수로 main함수가 처음에 호출하여,  */
/* global scheduler handeler를 초기화 하고 , parent_task를 생성한다  */
void thread_init() {
    
    gh_sch.root_task = NULL;
    gh_sch.running_task = NULL;
    
    gh_sch.child_task = 0;
    
    thread_create(parent_task, NULL);
}


/* thread_switch : 수행중이던  task가 다른 대기중인 task에게 cpu사용을 양보하게 하는 함수로 ,
 현재  cpu레지스터의 값이 수행중이던 task의  stack부분에 차례차례 저장되게 되며 ,
 다음에 수행될 것으로 선택된  task의 taskinfo의 stack정보가 레지스터로 올려진다. */

static unsigned long spsave, sptmp;

//주어진 기존의 schedule.c 코드가 32bit 에서만 작동되어 64비트 환경에 //맞게 switch 코드를 변경했다.

void thread_switch(int a)
{
    asm(    "push %%rax\n \t"
        "push %%rbx\n \t"
        "push %%rcx\n \t"
        "push %%rdx\n \t"
        "push %%rsi\n \t"
        "push %%rdi\n \t"
        "push %%rbp\n \t"
        "push %%rbp\n \t"
        "mov  %%rsp, %0"
        : "=r" (spsave)
        );
    
    
    gh_sch.running_task->sp = spsave;
    
    
    scheduler();
    sptmp = gh_sch.running_task->sp;
    
    
    asm(    "mov %0, %%rsp\n \t"
        "pop %%rbp\n \t"
        "pop %%rbp\n \t"
        "pop %%rdi\n \t"
        "pop %%rsi\n \t"
        "pop %%rdx\n \t"
        "pop %%rcx\n \t"
        "pop %%rbx\n \t"
        "pop %%rax\n \t"
        ::"r" (sptmp)
        );
}

// 다음 수행될 task를 선택하는 함수
void scheduler(void) {
    
    
    //현재 작업이 부모 thread이면 다음 작업으로 넘어간다.
    if (gh_sch.running_task->task_id == 1) {
        task_next();
    }
    //timequantum이 남은 경우 timequantum값 증가
    else {
        timequantum++;
        
    }
    
    //queue0에서 quantum = 8 의 RR이 완료 된 경우 다음 작업 수행
    
    if (timequantum == 8 && level == 0 ) {
        
        timequantum = 0; //timequantum 초기화
        task_next(); //다음 작업 수행
        
    }
    //queue1에서 quantum = 16 의 RR이 완료 된 경우 다음 작업 수행
    
    else if(timequantum == 16 && level==1){
        
        timequantum=0;
        task_next();
        
    }
    
    TaskInfo task;
    // gh_sch의 running_task가 가르키고 있는  taskinfo 받음
    task = task_get_runningtask();
    
    switch (task->status) {
            // task상태가 TASK_RUN이나 TASK_SLEEP이면 선택됨
        case TASK_RUN:
        case TASK_SLEEP:
            break;
            // task상태가 TASK_KILL이면 delete하고 , swiching함수 다시 호출
        case TASK_KILL:
            task_delete(task);
            scheduler();
            break;
            // task상태가 TASK_YIELD이면 상태를  TASK_RUN으로 바꾸고 선택됨
        case TASK_YIELD:
            task->status = TASK_RUN;
            break;
            // task상태가  TASK_READY이면 상태를 TASK_RUN으로 바꾸고 선택됨
        case TASK_READY:
            task->status = TASK_RUN;
            break;
    }
}

void thread_wait(void) {
    parent_task(NULL);
}




// task상태를  TASK_KILL로 설정후 , thread_yield
void thread_kill(void) {
    TaskInfo task;
    task = task_get_runningtask();
    task->status = TASK_KILL;
    thread_switch(0);
}

void thread_uninit(void) {
    return;
}

// child thread가 더이상 없을때까지 thread_switch
void parent_task(void *context) {
    // signal 처리를 위한 정보를 위한 구조체
    struct sigaction act;
    sigset_t masksets;
    pid_t pid;
    
    // signal set 초기화
    sigemptyset(&masksets);
    // signal handler로  thread_switch() 등록
    act.sa_handler = (void*) thread_switch;
    act.sa_mask = masksets;
    act.sa_flags = SA_NODEFER;
    
    // signal 수신 때 취할  action 설정
    sigaction(SIGUSR1, &act, NULL);
    
    if ((pid = fork()) == 0) {
        while (1) {
            sleep(1);
            kill(getppid(), SIGUSR1);
        }
    } else {
        while (1) {
            // child_task가 1개 남았을 때,  즉 , parent_task만 남았을 때
            if (gh_sch.child_task <= 1) {
                kill(pid, SIGINT);
                break;
            }
        };
    }
}
// linkedlist에 새로운 taskinfo 삽입
void task_insert(TaskInfo taskinfo) {
    //level 0에서 작업을 수행,  queue 0에 TASK 저장한다.
    if (level == 0 && gh_sch.root_task == NULL) {
        readyQueue[level] = taskinfo;
    }
    
    if (gh_sch.root_task == NULL) {
        gh_sch.root_task = taskinfo;
        gh_sch.running_task = taskinfo;
    }
    
    else {
        TaskInfo temp;
        temp = gh_sch.root_task;
        
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = taskinfo;
        taskinfo->prev = temp;
    }
    
}

//작업중인 queue를 종료하고 다음 queue로 변경하는 함수
void task_change(TaskInfo taskinfo) {
    //다음 실행시킬 queue가 비어 있으면 현재 작업중인 리스트를 다음 queue에 저장
    if (readyQueue[level + 1] == NULL) {
        readyQueue[level + 1] = readyQueue[level];
    }
    //queue가 비어있지 않으면 마지막 부분에 작업 저장
    else {
        TaskInfo temp = readyQueue[level + 1];
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = taskinfo;
    }
    level++;
    
    //level이 2보다 커지지 않게 함. 큐가 0,1,2 있음
    if (level > 2)
        level = 2;
    
    gh_sch.root_task = readyQueue[level];
    gh_sch.running_task = readyQueue[level]; //root와 running 저장
    
    printf("\nchange the %d queue\n\n", level); //queue변경 알림
    
    
}

// linkedlist에서  gh_sch.running_task가 가르키고 있는 task리턴
TaskInfo task_get_runningtask(void) {
    return gh_sch.running_task;
}

// linkedlist에서  gh_sch.running_task가 가르키고 있는 task의 다음 task리턴
void task_next(void) {
    TaskInfo temp;
    temp = gh_sch.running_task;
    
    //부모 thread가 수행중이면 바로 다음 작업을 running task
    if (gh_sch.running_task->task_id == 1) {
        gh_sch.running_task = temp->next;
    }
    
    //next가 있을 경우 다음 작업을 running task로
    if (temp->next != NULL) {
        gh_sch.running_task = temp->next;
    }
    //다음 작업이 없고 2번 level queue가 아닐경우 다음 queue로 넘어간다.
    else {
        if(level!=2)
            task_change(gh_sch.root_task);
    }
    
}





// linkedlist에서  task를 지움
void task_delete(TaskInfo taskinfo) {
    TaskInfo temp = taskinfo->prev;
    if (gh_sch.root_task == taskinfo) {
        gh_sch.root_task = NULL;
        gh_sch.running_task = NULL;
        gh_sch.child_task = 0;
    }
    
    else {
        temp->next = taskinfo->next;
        
        if (taskinfo == gh_sch.running_task) {
            if (temp->next != NULL) {
                (taskinfo->next)->prev = temp;
                gh_sch.running_task = temp->next;
            } else
                gh_sch.running_task = temp;
        }
        gh_sch.child_task--;
    }
    free(taskinfo);
    
}

// TASK1 1~32
void test_func_one(void *context)
{
    int i = 0;
    while( 1 ){
        
        i++;
        printf("TASK 1 : %5d\n", i);
        sleep(1);
        if( i == 32 )
            break;
    }
}

// TASK2 501~530

void test_func_two(void *context)
{
    int i = 500;
    while( 1 ){
        
        i ++;
        printf("\t\t\tTASK 2 : %3d\n", i);
        sleep(1);
        if( i == 530 )
            break;
    }
}

// TASK3 1001~1028

void test_func_three(void *context)
{
    int i = 1000;
    while( 1 ){
        
        
        i++;
        printf("\t\t\t\t\t\tTASK 3 : %4d\n", i);
        
        
        sleep(1);
        //sleep(1);
        
        if( i == 1028 )
            break;
    }
}


// schedule.c 의 main 함수
int main(void)
{
    thread_init();
    
    
    thread_create(test_func_one, NULL);
    thread_create(test_func_two, NULL);
    thread_create(test_func_three, NULL);
    
    
    thread_wait();
    
    
    return 0;
}

