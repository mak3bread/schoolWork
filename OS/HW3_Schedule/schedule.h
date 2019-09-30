
#ifndef    SCHEDULER_H
#define    SCHEDULER_H


#define    THREAD_STACKSIZE     1024
// task의상태
typedef enum {
    TASK_READY    = 0,
    TASK_RUN,
    TASK_YIELD,
    TASK_SLEEP,
    TASK_KILL
} TaskStatus;


// 각task를위한구조체
typedef struct task_info_tag {
    unsigned long stack[THREAD_STACKSIZE];
    unsigned long sp;
    int task_id;
    
    
    TaskStatus status;
    
    
    struct task_info_tag *next;
    struct task_info_tag *prev;
} *TaskInfo;




typedef void (*TaskFunc)(void *context);


TaskInfo thread_create(TaskFunc callback, void *context);


void thread_init(void);
void thread_wait(void);
void thread_uninit(void);
void thread_switch(int);
void thread_kill(void);


#endif    // SCHEDULER_H
