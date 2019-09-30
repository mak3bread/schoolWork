/******************************************************************************/
/*                                                                            */
/* Project : Simple Shell                                                     */
/* File    : shell.c                                                          */
/* Author  : 김민성_12152854                                                    */
/* Company : INHA Univ. CSE.                                                  */
/* Notes   : Simple unix shell!                                               */
/* Date    : 2019/05/11~                                                      */
/*                                                                            */
/******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/wait.h>
#include <signal.h>

//시그널 핸들링!
// + 컨트롤 c,z 통한 시그널 핸들링 등 foreground ,background process 관련 함수 필요
// command 전 추가적으로 필요한 것들



typedef struct ProcessList{ //프로세스 id와 Name을 저장하는 구조체
    
    int pid;
    char *name;
}ProcessList;

struct ProcessList backGP[30] = {0, NULL}; //백그라운드 프로세스로 실행한 프로세스 저장
struct ProcessList suspended[30]={0, NULL}; //Control Z로 suspended된 프로세스 저장

bool FBG_selection(char *line){ //프로세스가 foreground 인지 background 인지 구별하는 boolean 함수
    
    
    bool ground = true; //true ==foreground
    
    
    for( int i = 0 ; i < strlen(line); i++){
        if(line[i] == '&'){
            ground = false; //false == background
            break;
        }
    }
    
    return ground; //판단된 boolean값을 리턴
}


void handler_C(int sig){ //Control C handler == foreground에서 실행되고 있는 프로세스 종료
    
    printf("\nControl C가 입력 !!\n");
    printf("쉘 프로세스 %d 가 종료 됨\n\n", getpid() ); //쉘 프로세스의 pid를 출력하고 종료
    exit(0);//종료
}




void handler_Z(int sig) {//Control Z handler == foreground에서 실행되고 있는 프로세스 suspend
    
    static int ind= 0; //Control Z로 suspend시킨 프로세스의 주소 나타내는 static 변수


    
    if(sig == SIGTSTP){//control z로 생성 / 실행을 위해 대기    SIGTSTP default 처리를 중지
        
        printf("\nControl Z 가 입력 !!\n");
        printf("프로세스 %s  %d is suspended\n\n",suspended[ind].name,suspended[ind].pid);
        //control z 입력 시 index의 해당 프로세스 pid와 name을 출력
        
     ind=0; //0으로 초기화 후 시작

        for(int i = 0 ; i < 30 ; i++){
            
            if(suspended[i].pid == 0 || !strcmp(suspended[i].name,""))
            {
                continue; //pid가 x or name NULL값일 경우 다음 루프 continue
            }
            
            kill(suspended[i].pid, SIGTSTP); //종료
            ind++;//정지된 process 인덱스가 기억
        }
    }
}

void backGP_Add(int pid, char *name){ //background process 추가
    static int j=0; //프로세스의 주소 저장할 static 변수 j
//프로세스의 주소 저장할 static 변수 i
    backGP[j].pid = pid; //프로세스의 pid 저장
    backGP[j].name = strdup(name); // 프로세스 name 저장
    j++; //주소값 증가++;
}


void suspended_Add(int pid, char *name) //suspended 된 foreground process 추가
{
    static int j=0; //프로세스의 주소 저장할 static 변수 j
    suspended[j].pid = pid; // 프로세스의 pid 저장
    suspended[j].name = strdup(name); //프로세스 name 저장
    j++; //주소값 증가
}

void suspended_RS(int pid) //restart된 foreground process를 리스트에서 삭제
{
    
    for(int i=0; i<30; i++)
    {
        if(pid==suspended[i].pid) //입력받은 pid 를 suspended의 pid들과 비교 , 일치하는 경우
        {
            suspended[i].pid=0;//pid를 0으로,
            suspended[i].name=NULL;//name을 NULL 로 초기화
            break;
        }
    }
}


// 처음부터 여기 까지 추가된 부분

struct COMMAND{//커맨드를 받고 저장하는 구조체
    
    char* name;
    char* desc;
    bool ( *func )( int argc, char* argv[] );
};

bool cmd_cd( int argc, char* argv[] ); //디렉토리 명령 / 변경
bool cmd_exit( int argc, char* argv[] ); //shell 종료
bool cmd_help( int argc, char* argv[] );//도움말 출력
//이 기능 외에 lsb lss rs 3 가지 커맨드가 추가 되야 함!

bool cmd_lsb(int argc,char* argv[]);//백그라운드에 있는 프로세스 이름과 pid를 출력
bool cmd_lss(int argc,char* argv[]);//정지 중인 프로세스 이름과 pid를 출력
bool cmd_rs(int argc,char* argv[]);//SIGCONT 시그널을 보내 정지된 프로세스를 재시작 시킴!

struct COMMAND builtin_cmds[] = {// cmd구현
    
    { "cd",        "change directory",    cmd_cd        },
    { "exit",    "exit this shell",    cmd_exit    },
    { "quit",    "quit this shell",    cmd_exit    },
    { "help",    "show this help",    cmd_help    },
    { "?",        "show this help",    cmd_help    },
    //이제 새로 넣을 command 지정
    { "lsb","Lists the pid and process name of the background processes.",cmd_lsb},
    { "lss","Lists the pid and process name of the stopped processes.",cmd_lss},
    { "rs","Restarts the stopped process by sending it SIGCONT signal.\n",cmd_rs}
};

//여기부터

bool cmd_cd( int argc, char* argv[] ){ //디렉토리 주어진함수
    
    if( argc == 1 )
        chdir( getenv( "HOME" ) );
    else if( argc == 2 )
    {
        if( chdir( argv[1] ) )
            printf( "No directory\n" );
    }
    else
        printf( "USAGE: cd [dir]\n" );
    
    return true;
}

bool cmd_exit( int argc, char* argv[] ){//종료 주어진함수
    
    return false;
}
bool cmd_help( int argc, char* argv[] ){  // 도움말 주어진함수
    
    
    
    for(int i = 0; i < sizeof( builtin_cmds ) / sizeof( struct COMMAND ); i++ )
    {
        if( argc == 1 || strcmp( builtin_cmds[i].name, argv[1] ) == 0 ){
            printf( "%-10s: %s\n", builtin_cmds[i].name, builtin_cmds[i].desc );
        }
    }
    return true;
}


int tokenize( char* buf, char* delims, char* tokens[], int maxTokens ){//주어진 함수
    int token_count = 0;
    char* token;
    
    token = strtok( buf, delims );
    while( token != NULL && token_count < maxTokens )
    {
        tokens[token_count] = token;
        token_count++;
        token = strtok( NULL, delims );
    }
    tokens[token_count] = NULL;
    
    return token_count;
}

bool run( char* line ){
    char delims[] = " \r\n\t";
    char* tokens[128];
    int token_count = 0;
    int status;
    pid_t child;
    
    bool ground = FBG_selection(line);//판단된 그라운드 값을 저장
   
   
    token_count = tokenize( line, delims, tokens, sizeof( tokens ) / sizeof( char* ) );//tokenize함수로부터 정수를 받아 저장 ,메인에서 넘겨받은 명령어와 분별자를 넘김(분별자는 명령어 뒤의 파라미터)
    
    
    sigset_t A, B; //A,B 두개의 시그널 선언
    sigfillset (&A);
    sigfillset (&B);
    //A,B 의 시그널 세트가 모든 시그널을 포함하도록 함
    sigdelset(&B, SIGCHLD); //시그널 세트에 SIGCHLD에 해당되는 시그널 추가
    sigprocmask(SIG_SETMASK, &A, NULL);
    sigprocmask(SIG_UNBLOCK, &B, NULL);
    
    
    if( token_count == 0 )
        return true;
    
    for(int i = 0; i < sizeof( builtin_cmds ) / sizeof( struct COMMAND ); i++ )
    {
        if( strcmp( builtin_cmds[i].name, tokens[0] ) == 0 )
            return builtin_cmds[i].func( token_count, tokens );
    }
    
    child = fork();
    if(ground==false){//background일 때
        backGP_Add(child,tokens[0]);//ground 가 false면 백그라운드 이므로 리스트에 추가
        
    }
    
    if( child == 0 )//자식 프로세스 실행되는 곳
    {
        execvp( tokens[0], tokens );
        printf( "No such file\n" );
        _exit( 0 );
    }
    
    else if( child < 0 )//예외처리
    {
        printf( "Failed to fork()!" );
        _exit( 0 );
    }
    else{//부모 process
        
        if(ground == true) //foreground
        {
            suspended_Add(child, tokens[0]); //suspend 된 리스트에 추가
            waitpid(child, &status, WUNTRACED);
            //자식프로세스를 기다림 child에 해당하는 자식프로세스가 멈춤상태일 경우 그 상태 리턴
        }
        
        else if(ground == false) //background
        {
            waitpid(child, &status, WNOHANG);
            //자식프로세스를 기다림 , 자식이 종료되지 않으면 블록이 되지않고 바로 리턴
        }
    }
    return true;
}

// 여기 까지 주어진 함수 +추가본(RUN 에서 추가됨)
// 여기부터 위에 구조체에서 선언했던 lsb,lss,rs bool를 구현해야됨


bool cmd_lsb(int argc, char* argv[]){ //background process들 출력
    printf("##lsb \n");//lsb 임을 알려줌
    for(int i=0;i<30;i++){
        if(backGP[i].name==NULL){
            break; //프로세스 없으면 break;
        }
        printf("%d. 프로세스ID : %d , 프로세스 이름 : %s &\n\n",i+1,backGP[i].pid,backGP[i].name);//pid,name 출력 ,background 는 & 붙임!
    }
    return true;
}

bool cmd_lss(int argc, char* argv[]){ //stopped 된 process 들 출력
    printf("##lss \n");//형식이 이렇길래 붙여봄..
    
    for(int i=0;i<30;i++){
        if(suspended[i].name==NULL){//stopped process 가 더 이상 없으면 break!
            break;
        }
        printf("%d. 프로세스ID : %d , 프로세스 이름 : %s\n\n",i+1, suspended[i].pid,suspended[i].name);//stopped process pid name 출력
    }
    return true;
}

bool cmd_rs(int argc, char* argv[]){ //stopped 된 process 들 재시작
    int pid=atoi(argv[1]);
    
    printf("%d 재시작\n\n",pid);
    
    for(int i=0;i<30;i++){
        if(suspended[i].pid==pid){
            
            kill(pid,SIGCONT);
            suspended_RS(pid);
            break;
        }
        
    }
    return true;
}

//new commands 만드는것 --끝

char *get_current_dir_name(void){
    char current_name[1024];
    
    return getcwd(current_name, sizeof(current_name)) == NULL ? NULL : strdup(current_name);
}

int main()
{
    char line[1024]; //받을 명령어의 문자배열
    
    if(signal(SIGINT,handler_C)==SIG_ERR)//control c 설정
    { //handler C 호출
        printf("error\n"); //예외처리
        exit(1);
    }

    static struct sigaction act; //signal handler 구조체 선언
    act.sa_handler = handler_Z; //control Z 설정
    sigaction(SIGCHLD, &act, NULL);
    sigaction(SIGTSTP, &act, NULL);
    //child프로세스와 control가 눌렸을때의 액션 설정
    memset(&act, 0, sizeof(act));
    //설정한 act 버퍼에 액션 사이즈크기만큼을 채워 넣음

    while( -1 ){
        
        printf( "\n%s $ ",get_current_dir_name() ); //get_current_dir_name()으로 현재의 디렉토리를 알려주고 $ 다음부터 명령어 입력
        fgets( line, sizeof( line ) - 1, stdin ); //명령어 입력, line 배열에 저장
        
        if( run( line ) == false ) //입력받은 라인을 run함수로 넘김 -> boolean run이 false를 리턴 할 경우 종료
        {
            break;
        }
       
    }
    return 0;
}



