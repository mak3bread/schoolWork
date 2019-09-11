//1,2번 혼합
#include <iostream>
using namespace std;

class Arr {
    int n;
    int* arr;
    int max;

public:
    Arr(int size) {
        max=size;
        this->n = 0;
        this->arr = new int[size];
        for (int i = 0; i < size; i++) {
            arr[i] = 0;
        }

    }

    int at(int idx) {

        if (idx<0||idx>=n) {
            return 0;
        }
        else { return arr[idx]; }
    }

    void set(int idx, int X) {

        if (idx<0||idx>=n) {
            cout << 0 << endl;
        }
        else {
            arr[idx] = X;
        }
    }
    
    void add(int idx, int num) {
        
        if (n == max) {                            //현재 원소의 갯수가 다 차있으면
            if (idx < 0 || idx >= n) {            //idx 가 인덱스 범위를 벗어나면
                return;                            //그냥 리턴으로 함수 종료
            }
            else {
                for (int i = n - 2; i >= idx; i--) {    //원소가 꽉 차있으므로
                    arr[i + 1] = arr[i];                //n-2 부터 하나씩 +1 만큼 이동
                }
                arr[idx] = num;                            //arr[idx] 에 num 값 삽입
            }
        }
        
        else {
            if (n == 0) {                        //현재 원소의 갯수가 0이면
                arr[0] = num;                    //arr[0]에 num 값 삽입
                n++;                            //원소의 갯수 1 증가
            }
            else {
                if (idx < 0 || idx >= n) {        //0이 아니고 인덱스 범위를 벗어나면
                    arr[n] = num;                //배열의 마지막에 num 값 삽입
                    n++;                        //원소의 갯수1 증가
                }
                else {
                    for (int i = n - 1; i >= idx; i--) {
                        arr[i + 1] = arr[i];            //그게아니면 n-1 부터 +1 만큼 이동
                    }
                    arr[idx] = num;                //idx 에 num 값 삽입
                    n++;                        //원소의 갯수 1 증가
                }
            }
        }
    }

    int remove(int idx) {
        if (idx<0||idx>=n) {
            return 0;
        }
        else{
        int value = arr[idx];
           
        for (int j = idx+1; j < n; j++) {
            arr[j - 1] = arr[j];
        }
           arr[n-1] = 0;
            n--;
            return value;
        }
    }

    void printArray() {
        if (n == 0) {
            cout << 0 << endl;
        }
        else {
            for (int i = 0; i < n; i++) {
                cout << arr[i] << " ";
                if (i == n-1) {
                    cout << endl;
                }
            }
        }
    }
};

int main() {
    int N = 10000;

    Arr arr(N);

    int M;
    cin >> M;

    for (int i = 0; i < M; i++) {
        string X;
        cin >> X;
        if (X == "at") {
            int index;
            cin >> index;
            cout << arr.at(index) << '\n';
        }

        else if (X == "add") {
            int index;
            int num;
            cin >> index >> num;
            arr.add(index, num);
        }

        else if (X == "set") {
            int index;
            int num;
            cin >> index >> num;

            arr.set(index, num);
        }

       else if (X == "printArray") {
            arr.printArray();
        }

        else if (X == "remove") {
            int index;
            cin >> index;
           cout<<arr.remove(index)<<endl;
        }

        else{
            return 0;
        }

    }
    return 0;
}

//#include <iostream>
//#include <string>
//using namespace std;
//class Array {
//public:
//    int n;
//    int *arr;
//    int max;
//    Array(int size) {
//        max = size;                                //배열의 최댓값 10000 저장
//        this->n = 0;
//        this->arr = new int[size];                //배열 할당
//        for (int i = 0; i < size; i++) {        //배열의 원소 0으로 초기화
//            arr[i] = 0;
//        }
//    }
//    int at(int idx) {
//        if (idx < 0 || idx >= n) {                //배열이 인덱스 범위를 벗어나면
//            return 0;                            //0을 리턴
//        }
//        else
//            return arr[idx];                    //인덱스 범위 안이면 arr[idx] 리턴
//    }
//    void set(int idx, int x) {
//        if (idx < 0 || idx >= n) {                //배열이 인덱스 범위 벗어나면
//            cout << 0 << '\n';                    //0을 출력
//        }
//        else
//            arr[idx] = x;                        //아니면 arr[idx]에 x 삽입
//    }
//    void add(int idx, int num) {
//        if (n == max) {                            //현재 원소의 갯수가 다 차있으면
//            if (idx < 0 || idx >= n) {            //idx 가 인덱스 범위를 벗어나면
//                return;                            //그냥 리턴으로 함수 종료
//            }
//            else {
//                for (int i = n - 2; i >= idx; i--) {    //원소가 꽉 차있으므로
//                    arr[i + 1] = arr[i];                //n-2 부터 하나씩 +1 만큼 이동
//                }
//                arr[idx] = num;                            //arr[idx] 에 num 값 삽입
//            }
//        }
//        else {
//            if (n == 0) {                        //현재 원소의 갯수가 0이면
//                arr[0] = num;                    //arr[0]에 num 값 삽입
//                n++;                            //원소의 갯수 1 증가
//            }
//            else {
//                if (idx < 0 || idx >= n) {        //0이 아니고 인덱스 범위를 벗어나면
//                    arr[n] = num;                //배열의 마지막에 num 값 삽입
//                    n++;                        //원소의 갯수1 증가
//                }
//                else {
//                    for (int i = n - 1; i >= idx; i--) {
//                        arr[i + 1] = arr[i];            //그게아니면 n-1 부터 +1 만큼 이동
//                    }
//                    arr[idx] = num;                //idx 에 num 값 삽입
//                    n++;                        //원소의 갯수 1 증가
//                }
//            }
//        }
//    }
//    int remove(int idx) {
//        if (idx < 0 || idx >= n)                //범위 벗어나면 0 리턴
//            return 0;
//        else {
//            int temp = arr[idx];                //제거할 값 temp 에 저장
//            for (int i = idx + 1; i < n; i++) {
//                arr[i - 1] = arr[i];            //하나씩 옆으로 이동
//            }
//            arr[n - 1] = 0;                        //마지막 원소에 0 대입
//            n--;                                //원소의 갯수 1 감소
//            return temp;                        //제거한 값 리턴
//        }
//    }
//    void printArray() {
//        int i = 0;
//        if (n == 0)                                //배열이 아무것도 없으면 0 출력
//            cout << 0 << '\n';
//        else {
//            while (i < n) {
//                cout << arr[i] << " ";            //배열 원소 하나씩 출력
//                i++;
//            }
//            cout << '\n';
//        }
//    }
//};

//int main() {
//    Array arr(10000);
//    int m;
//    int a;
//    int b;
//    string str;
//    cin >> m;                        //명령어의 수 입력받음
//    for (int i = 0; i < m; i++) {
//        cin >> str;
//        if (str == "printArray")        //받은 문자가 printArray면
//            arr.printArray();            //printArrray 함수 실행
//        else {
//            cin >> a;
//            if (str == "at")            //at 이면
//                cout << arr.at(a) << '\n';        //at 실행
//            else {
//                if (str == "remove")                //remove 면
//                    cout << arr.remove(a) << '\n';    //remove 실행
//                else {
//                    cin >> b;                    //여기서부턴 2개의 숫자를 입력받으므로 b 하나 추가
//                    if (str == "set")            //set 이면
//                        arr.set(a, b);
//                    else
//                        arr.add(a, b);            //아니면
//                }
//            }
//        }
//    }
//}



//3번
//#include <iostream>
//using namespace std;
//
//int main(){
//
//    int M;
//    cin>>M;
//
//    for(int i=0;i<M;i++){
//        int N;
//        cin>>N;
//        int *arr=new int[N];
//
//        for(int j=0;j<N;j++){
//            cin>>arr[j];
//        }
//
//        int kor_sum=0;
//        int jp_sum=0;
//        int ch_sum=0;
//
//        for(int k=0;k<N;k++){
//            if(k%3==0){
//            kor_sum+=arr[k];
//            }
//            if(k%3==1){
//            jp_sum+=arr[k];
//            }
//            if(k%3==2){
//            ch_sum+=arr[k];
//            }
//        }
//        cout<<kor_sum<<" "<<jp_sum<<" "<<ch_sum<<endl;
//
//        delete []arr;
//    }
//
//    return 0;
//}

//4번
//
//#include <iostream>
//using namespace std;
//
//int main(){
//
//    int M;
//    cin>>M;
//
//    for(int i=0;i<M;i++){
//        int N;
//        cin>>N;
//        int *arr=new int[N];
//
//        for(int j=0;j<N;j++){
//            cin>>arr[j];
//        }
//
//        int kor_sum=0,kor_count=0;
//        int jp_sum=0,jp_count=0;
//        int ch_sum=0,ch_count=0;
//
//        for(int k=0;k<N;k++){
//            if(k%3==0){
//                kor_sum+=arr[k];
//                if(arr[k]!=0){
//                kor_count++;
//                }
//            }
//            if(k%3==1){
//                jp_sum+=arr[k];
//                if(arr[k]!=0){
//                       jp_count++;
//                }
//            }
//            if(k%3==2){
//                ch_sum+=arr[k];
//                if(arr[k]!=0){
//                    ch_count++;
//                }
//            }
//        }
//        int kor_avg=0;
//        int jp_avg=0;
//        int ch_avg=0;
//
//        if(kor_count!=0){
//          kor_avg=kor_sum/kor_count;
//        }
//        else{
//            kor_avg=0;
//        }
//        if(jp_count!=0){
//        jp_avg=jp_sum/jp_count;
//        }
//        else{
//            jp_avg=0;
//        }
//        if(ch_count!=0){
//        ch_avg=ch_sum/ch_count;
//        }
//        else{
//            ch_avg=0;
//        }
//
//        cout<<kor_sum<<" "<<jp_sum<<" "<<ch_sum<<endl;
//        cout<<kor_avg<<" "<<jp_avg<<" "<<ch_avg<<endl;
//
//        delete []arr;
//    }
//
//    return 0;
//}
