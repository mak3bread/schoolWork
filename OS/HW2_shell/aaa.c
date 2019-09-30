#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>

int main(){
    
pid_t pid; //int 값 번호의 pid 를 가질 수 있다.
    
        sleep(10);
   
    
printf("\n프로세스 ID : %d is processing now\n\n",getpid()); // getpid = 이 함수를 호출하는 프로세스 pid 를 출력
printf("enter를 눌러주세요. \n");
return 0;
}

