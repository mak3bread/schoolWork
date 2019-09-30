#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>

typedef struct
{
long priority; //데이터 키의 값 
int temp; //온도 값
int pid; //프로세스 번호
int stable; //다른 프로세스의 상태를 나타냄

}msgp;

int main(int argc, char * argv[])
{
printf("시작\n");
int server_msgq_id; //서버 메세지큐 번호
int client_msgq_id; //클라이언트 메시지큐 번호
msgp message;//구조체 선언
message.temp = (int)atoi(argv[1]); //입력받은 값을 온도에 저장
message.pid =  (int)atoi(argv[2]); //입력받은 pid 값
message.priority = (long)atoi(argv[2]); 
// long타입을 바꾸는것은 server.c에서 4개의 메세지 수신을 구별하기위함.

printf("클라이언트 = %d \n입력받은 온도 = %d\n",message.pid,message.temp); 
//자신의 pid와 입력받은 온도를 출력
printf("=============\n서버 대기  \n");

if ( -1 == ( client_msgq_id = msgget( (key_t)message.pid, IPC_CREAT | 0666))) //클라이언트 메세지큐 생성
    {
       perror( "msgget() 오류"); //예외처리
       exit( 1);
    }

int q_stat;//큐의상태, 전송,받기에 사용
int ex_temp; //현재 자신의 온도(외부온도)를 저장할 변수

message.stable = 0;
while(message.stable == 0)
{
ex_temp = message.temp; //외부온도를 저장
printf("\n전송 전 온도 = %d\n",ex_temp); //전송하기전의 온도출력

if ( -1 == ( server_msgq_id = msgget( (key_t)1234, IPC_CREAT | 0666))) //서버 메시지큐 생성
{
   perror( "msgget() 오류"); //예외처리
   exit( 1);
}

message.pid =  (int)atoi(argv[2]); 
//pid-> msgrcv 후 값이 변할 수 있으므로 초기화

message.priority = (long)atoi(argv[2]); 
//server.c 에서 입력한 pid에 해당하는 데이타 키에 접근할수 있게함



q_stat = msgsnd(server_msgq_id, &message, sizeof(msgp)-sizeof(long), 0); //메세지큐 1234(서버)에 전송

q_stat = msgrcv(client_msgq_id, &message, sizeof(msgp)-sizeof(long), message.priority,0);
//message.priority ->서버에서 전송한 데이타키에 접근

printf("전송 후 온도 = %d\n",message.temp);

if(message.stable ==1) //안정화 된경우
{
printf("안정된 온도 = %d \n", message.temp);
break;
}
else //안정화 되지 않을경우 계속 수행
{
message.temp = (ex_temp * 3 + 2 * message.temp) / 5; 
//새로운 온도로 갱신
}
printf("\n");

sleep(5); //루프마다 5초의 대기시간
}

printf("\n 끄읕 !\n");

msgctl( server_msgq_id, IPC_RMID, 0);
msgctl( client_msgq_id, IPC_RMID, 0);
//생성했었던 메세지 큐를 삭제
return 0;
}




