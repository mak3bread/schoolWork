#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>

typedef struct
{
long priority; //데이터 키의 값
int temp; //전송할 온도의 값
int pid; //프로세스 번호
int stable; //다른 프로세스의 상태변화를 알려줌

}msgp;

int main(int argc, char * argv[])
{
int server_msgq_id; 
//서버 메세지큐 번호; 메세지 생성과 삭제,전송,받기 등에 쓰임.
int client_msgq_id; //4개의 클라이언트 번호
msgp message; //구조체 선언
message.temp = (int)atoi(argv[1]); //입력받은 값을 서버 온도에 저장 형변환

printf("서버 온도 = %d\n",message.temp);
printf("클라이언트 대기 중 \n");


//서버 메세지큐 생성, 키값으로 1234를 사용
if ( -1 == ( server_msgq_id = msgget( (key_t)1234, IPC_CREAT | 0666)))
    {
       perror("msgget() 실패"); //예외,실패
       exit(1);
    }

int q_stat; //큐의상태, 전송,받기에 사용
int tempC[5]; 
//비교할 온도값을 저장하는 배열, 인덱스 0 : 서버온도/ 1~4 : 각 클라이언트 온도
message.stable = 0; //안정화는 False
while(message.stable == 0) //stable True가 될 때까지 루프
{
tempC[0] = message.temp; //서버온도를 저장
int pri =1;
//pri는 카운터변수, msgrcv() 함수의 세 번째 파라미터, 서버가 원하는 데이타타입을 //골라서 가져올수있다.
while( pri < 5 )//pri -> 원하는 자료를 구별
{

//pri 값에 따라 pid 1~4의 메세지큐에 접근
q_stat = msgrcv( server_msgq_id, &message, sizeof(msgp)-sizeof(long),(long)pri ,0);
tempC[pri] = message.temp; //메세지큐에서 받은 온도정보를 배열에 저장
printf("클라이언트 %d =%d \n",pri,tempC[pri]); 
//1~4 클라이언트의 현재 온도값을 알려준다.
pri++; //카운터 증가

}

//서버온도와 1~4클라이언트 값이 안정됐는지 비교
int key = 1;
while( key < 5 )
{
//서버온도와 4개의 클라이언트온도가 안정됐는지 비교
if(tempC[0] == tempC[1] && tempC[0] == tempC[2] && tempC[0] == tempC[3] && tempC[0] == tempC[4])
{
//안정됨
message.stable = 1; //각 클라이언트에게 모든 작업이 끝남을 전달 

}
else //안정 안된 경우
{
//받은 온도를 계산하여 message.temp->서버 온도에 저장됨.
message.temp = ( tempC[1]+tempC[2]+tempC[3]+tempC[4] + tempC[0] * 2 ) / 6;
}
//메세지를 전송할 큐 생성
if ( -1 == ( client_msgq_id = msgget( (key_t)key, IPC_CREAT | 0666))) 

//각 key값은 1~4 클라이언트에 대응
{
perror( "msgget() 실패"); //예외처리
exit(1);
}
message.pid = key; //전송 받을 클라이언트와 일치시킴
message.priority = (long)key; 
//전송 받을 클라이언트가 자신의 데이타타입으로 접근가능 하게 함.
q_stat = msgsnd(client_msgq_id, &message, sizeof(msgp)-sizeof(long), 0);
key++; //카운터 증가
}
printf("\n");
}
msgctl( server_msgq_id, IPC_RMID, 0);
msgctl( client_msgq_id, IPC_RMID, 0);

//생성했었던 메세지 큐를 삭제
printf("안정된 온도 = %d \n", message.temp); //최종 안정화된 온도를 출력
printf("\n 끄읕! \n");
return 0;
}


