#include <sys/types.h>
#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>

#define MAX_CMD_ARG   10
#define MAX_CMD_LT   10
#define MAX_CMD_GR    10

#ifndef TRUE
#define TRUE    1
#endif
 
#ifndef FALSE
#define FALSE    0
#endif
 
const char *prompt = "mysh> ";
char* cmdargs[MAX_CMD_ARG];
char cmdline[BUFSIZ];
char* cmdgrp[MAX_CMD_GR];
char* cmdlist[MAX_CMD_LT];

struct sigaction action;
static int IS_BACKGROUND=0;

void fatal(char *str){
    perror(str);
    exit(1);
}
 
int makeargv(char *s, const char *delimiters, char** argv, int MAX_LT){
    int numtokens = 0;
    char *snew = NULL;
    
    if((s==NULL)||(delimiters==NULL) ){return -1;}
    
    snew = s+strspn(s, delimiters);
    
    argv[numtokens]=strtok(snew, delimiters);
    
    if( argv[numtokens] !=NULL)
        for(numtokens=1; (argv[numtokens]=strtok(NULL, delimiters)) != NULL; numtokens++){
            if(numtokens == (MAX_LT-1)) return -1;
        }
    
    if( numtokens > MAX_LT) return -1;
    return numtokens;
}


typedef struct {
    char* name;
    char* desc;
    int ( *func )( int argc, char* argv[] );
} COMMAND;

int cmd_cd( int argc, char* argv[] ){
    if( argc == 1 )
        chdir( getenv( "HOME" ) );
    else if( argc == 2 ){
        if( chdir( argv[1] ) )
            printf( "-myshell: cd: %s: No such file or directory\n",argv[1]);
    }
    else
        printf( "USE: cd [dir]\n" );
    return TRUE;
}
 
int cmd_exit( int argc, char* argv[] ){
    printf("[프로세스 종료]\n");
    exit(0);
    return TRUE;
}
 
static COMMAND builtin_cmds[] ={
    { "cd", "디렉토리 변경", cmd_cd },
    { "exit", "쉘 나가기", cmd_exit }
};
 
int backG(char *cm){
    for(int i=0; i < strlen(cm); i++){
        if(cm[i] == '&'){
            cm[i] = ' ';
            return 1;
        }
    }
    return 0;
}

void zom_handle(int sig){
    pid_t pid;
    int stat;
    while ((pid = waitpid(-1, &stat, WNOHANG)) > 0){}
    printf("\n");
}

void redir(char* cm){
    char *arr;
    int cmlen = strlen(cm);
    int file_d;
    
   for(int i = cmlen-1;i >= 0;i--)
    {
        switch(cm[i])
        {
            case '<':
                arr = strtok(&cm[i+1], " \t");
                if((file_d = open(arr, O_RDONLY | O_CREAT, 0644)) < 0){
                    fatal("file open error");
                }
                dup2(file_d, STDIN_FILENO);
                close(file_d);
                cm[i] = '\0';
                break;
            case '>':
                arr = strtok(&cm[i+1], " \t");
                if( (file_d = open(arr, O_WRONLY | O_CREAT | O_TRUNC, 0644)) < 0){
                    fatal("file open error");
                }
                dup2(file_d, STDOUT_FILENO);
                close(file_d);
                cm[i] = '\0';
                break;
            default:
                break;
        }
    }
    
}
 
void run_cmd(char *cmlt){
    redir(cmlt);
    if(makeargv(cmlt, " \t", cmdargs, MAX_CMD_ARG) <= 0){fatal("cmdargs error");}
    execvp(cmdargs[0], cmdargs);
    fatal("run_cmd error");
}
 
void run_cmdgrp(char *cmdgrp){
    int i=0;
    int count = 0;
    int pfd[2];
    sigset_t set;
 
    setpgid(0,0);
    if(!IS_BACKGROUND){
        tcsetpgrp(STDIN_FILENO, getpid());
    }
    sigfillset(&set);
    sigprocmask(SIG_UNBLOCK,&set,NULL);
 
    if((count = makeargv(cmdgrp, "|", cmdlist, MAX_CMD_LT)) <= 0){
        fatal("makeargv_cmdgrp error");
    }
    
    for(i=0; i<count-1; i++){
        pipe(pfd);
        switch(fork()){
            case -1: fatal("fork error");
            case  0: close(pfd[0]);
                dup2(pfd[1], STDOUT_FILENO);
                run_cmd(cmdlist[i]);
            default: close(pfd[1]);
                dup2(pfd[0], STDIN_FILENO);
        }
    }
    run_cmd(cmdlist[i]);
}
 
void run_cmdline(char* cmdline){
    int count = 0;
    int pid;
    char* cmdvector[MAX_CMD_ARG];
    char cmdgrptemp[BUFSIZ];
    int numtokens = 0;
    
    count = makeargv(cmdline, ";", cmdgrp, MAX_CMD_GR);
    
    for(int i=0; i<count; ++i){
        memcpy(cmdgrptemp, cmdgrp[i], strlen(cmdgrp[i]) + 1);
        numtokens = makeargv(cmdgrp[i], " \t", cmdvector, MAX_CMD_GR);
        
        for( int j = 0; j < sizeof( builtin_cmds ) / sizeof( COMMAND ); j++ ){            if( strcmp( builtin_cmds[j].name, cmdvector[0] ) == 0 ){
                builtin_cmds[j].func( numtokens , cmdvector );
                return;
            }
        }
        IS_BACKGROUND = backG(cmdgrptemp);
        switch(pid=fork()){
            case -1:
                fatal("fork error");
            case  0:
                run_cmdgrp(cmdgrptemp);
            default:
                if(IS_BACKGROUND) break;
                waitpid(pid, NULL, 0);
                tcsetpgrp(STDIN_FILENO, getpgid(0));
                fflush(stdout);
        }
    }
}
 
int main(int argc, char**argv){
    sigset_t set;
    sigfillset(&set);
    sigdelset(&set,SIGCHLD);
    sigprocmask(SIG_SETMASK,&set,NULL);
    action.sa_flags = SA_RESTART;
    sigemptyset(&action.sa_mask);
    action.sa_handler = zom_handle;
    sigaction(SIGCHLD, &action, 0);
    
    while (1) {
        fputs(prompt, stdout);
        fgets(cmdline, BUFSIZ, stdin);
        cmdline[strlen(cmdline) -1] ='\0';
        run_cmdline(cmdline);
    }
    return 0;
}
