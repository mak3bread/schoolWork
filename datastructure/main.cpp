////1,2번 혼합
//#include <iostream>
//using namespace std;
//
//class Arr {
//    int n;
//    int* arr;
//
//public:
//    Arr(int size) {
//        this->n = 0;
//        this->arr = new int[size];
//        for (int i = 0; i < size; i++) {
//            arr[i] = 0;
//        }
//
//    }
//
//    int at(int idx) {
//
//        if (arr[idx] == 0) {
//            return 0;
//        }
//        else { return arr[idx]; }
//    }
//
//    void set(int idx, int X) {
//
//        if (arr[idx] == 0) {
//            cout << 0 << endl;
//        }
//        else {
//            arr[idx] = X;
//
//        }
//    }
//
//    void add(int idx, int num) {
//
//        n=0;
//        for (int i = 0; i < 10000; i++) {
//            if (arr[i] != 0) { n++; }
//        }
//
//
//        if (arr[idx] == 0) {
//            arr[n] = num;
//            n++;
//        }
//        else {
//            n++;
//            for (int i = n; i > idx; i--) {
//                arr[i] = arr[i - 1];
//            }
//            arr[n] = num;
//        }
//    }
//
//    int remove(int idx) {
//        n=0;
//        for (int i = 0; i < 10000; i++) {
//            if (arr[i] != 0) { n++; }
//        }
//        if (arr[idx]==0) {
//            return 0;
//        }
//        else{
//        int value = arr[idx];
//            arr[idx] = 0;
//        for (int j = idx+1; j < n; j++) {
//            arr[j - 1] = arr[j];
//        }
//
//            n--;
//            return value;
//        }
//
//
//    }
//
//    void printArray() {
//        if (n == 0) {
//            cout << 0 << endl;
//        }
//        else {
//            for (int i = 0; i < n; i++) {
//                cout << arr[i] << " ";
//                if (i == n-1) {
//                    cout << endl;
//                }
//            }
//        }
//    }
//
//
//
//};
//
//int main() {
//    int N = 10000;
//
//    Arr arr(N);
//
//    int M;
//    cin >> M;
//
//    for (int i = 0; i < M; i++) {
//        string X;
//        cin >> X;
//        if (X == "at") {
//            int index;
//            cin >> index;
//            cout << arr.at(index) << '\n';
//        }
//
//        else if (X == "add") {
//            int index;
//            int num;
//            cin >> index >> num;
//            arr.add(index, num);
//        }
//
//        else if (X == "set") {
//            int index;
//            int num;
//            cin >> index >> num;
//
//            arr.set(index, num);
//        }
//
//       else if (X == "printArray") {
//            arr.printArray();
//        }
//
//        else if (X == "remove") {
//            int index;
//            cin >> index;
//           cout<<arr.remove(index)<<endl;
//        }
//
//        else{
//            return 0;
//        }
//
//    }
//    return 0;
//}
//


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

#include <iostream>
using namespace std;

int main(){
    
    int M;
    cin>>M;
    
    for(int i=0;i<M;i++){
        int N;
        cin>>N;
        int *arr=new int[N];
        
        for(int j=0;j<N;j++){
            cin>>arr[j];
        }
        
        int kor_sum=0,kor_count=0;
        int jp_sum=0,jp_count=0;
        int ch_sum=0,ch_count=0;
        
        for(int k=0;k<N;k++){
            if(k%3==0){
                kor_sum+=arr[k];
                if(arr[k]!=0){
                kor_count++;
                }
            }
            if(k%3==1){
                jp_sum+=arr[k];
                if(arr[k]!=0){
                       jp_count++;
                }
            }
            if(k%3==2){
                ch_sum+=arr[k];
                if(arr[k]!=0){
                    ch_count++;
                }
            }
        }
        int kor_avg=0;
        int jp_avg=0;
        int ch_avg=0;
        
        if(kor_count!=0){
          kor_avg=kor_sum/kor_count;
        }
        else{
            kor_avg=0;
        }
        if(jp_count!=0){
        jp_avg=jp_sum/jp_count;
        }
        else{
            jp_avg=0;
        }
        if(ch_count!=0){
        ch_avg=ch_sum/ch_count;
        }
        else{
            ch_avg=0;
        }
        
        cout<<kor_sum<<" "<<jp_sum<<" "<<ch_sum<<endl;
        cout<<kor_avg<<" "<<jp_avg<<" "<<ch_avg<<endl;
        
        delete []arr;
    }
    
    return 0;
}
