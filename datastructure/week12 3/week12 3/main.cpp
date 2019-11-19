#include <iostream>
using namespace std;
#define NUL -2
#define AVAIL -1
#define a_size 353333

//12-1
/*
class Node {
public:
    int k;
    int count=0;
};
 
class Hash {
private:
    int h_size;
public:
    Node** arr;
    
    Hash() {
        h_size = 0;
        arr=new Node*[a_size];
        for (int i = 0; i < a_size; i++) {
            Node* newN=new Node;
            newN->k=NUL;
            arr[i]=newN;
        }
    }
    bool empty() { return (h_size == 0); }
    int hCode(int key) { return key % a_size; }
 
    void linearP(int key) {
        int idx = hCode(key);
        int cnt = 0;
        while (1) {
            if (arr[idx]->k == NUL){ break; }
            idx++;
            idx %=a_size;
            cnt++;
            if (cnt > a_size) { return; }
        }
        h_size++;
        arr[idx]->k=key;
        arr[idx]->count = cnt + 1;
    }
 
    bool find(int key) {
        int idx = hCode(key);
        int cnt = 0;
        while (1) {
            if (arr[idx]->k == NUL) { return false; }
            if (arr[idx]->k == key) { return true; }
            idx++;
            idx %= a_size;
            cnt++;
            if (cnt > a_size) { return false; }
        }
    }
    
    int result(int key) {
        int idx = hCode(key);
        int cnt = 0;
        while (1) {
            if (arr[idx]->k == NUL) { return cnt+1; }
            if (arr[idx]->k == key) { return arr[idx]->count; }
            idx++;
            idx %= a_size;
            cnt++;
            if (cnt > a_size) { return NUL; }
        }
    }
    
    void desty(){
        for (int i = 0; i < a_size; i++) {
            if(arr[i]->k!=NUL){
            arr[i]->k=NUL;
            }
        }
    }
};
 
 
int main() {

    int T;
    cin >> T;
    
   Hash hs;
    
    for (int i = 0; i < T; i++) {
        int N;
        cin >> N;
 
        for (int j = 0; j < N; j++) {
            int a;
            cin >> a;
            hs.linearP(a);
        }
 
        int M;
        cin >> M;
 
        for (int j = 0; j < M; j++) {
            int b;
            cin >> b;
            int cur = hs.result(b);
            if (hs.find(b)) {cout << "1" << ' ' << cur << '\n';  }
            else { cout << "0" << ' ' << cur << '\n'; }
        }
    hs.desty();
    }
    return 0;
}
*/

//12-2
/*
class Node {
public:
    int k;
    int count=0;
};
 
class Hash {
private:
    int h_size;
public:
    Node** arr;
    
    Hash() {
        h_size = 0;
        arr=new Node*[a_size];
        for (int i = 0; i < a_size; i++) {
            Node* newN=new Node;
            newN->k=NUL;
            arr[i]=newN;
        }
    }
    bool empty() { return (h_size == 0); }
    int hCode(int key) { return key % a_size; }
 
    void linearP(int key) {
        int idx = hCode(key);
        int cnt = 0;
        while (1) {
            if (arr[idx]->k == NUL){ break; }
            idx++;
            idx %=a_size;
            cnt++;
            if (cnt > a_size) { return; }
        }
        h_size++;
        arr[idx]->k=key;
        arr[idx]->count = cnt + 1;
    }
 
    bool find(int key) {
        int idx = hCode(key);
        int cnt = 0;
        while (1) {
            if (arr[idx]->k == NUL) { return false; }
            if (arr[idx]->k == key) { return true; }
            idx++;
            idx %= a_size;
            cnt++;
            if (cnt > a_size) { return false; }
        }
    }
    
    int result(int key) {
        int idx = hCode(key);
        int cnt = 0;
        while (1) {
            if (arr[idx]->k == NUL) { return cnt+1; }
            if (arr[idx]->k == key) { return idx; }
            idx++;
            idx %= a_size;
            cnt++;
            if (cnt > a_size) { return NUL; }
        }
    }
    
       int deleteH(int key) {
          int removal = result(key);
           bool tf=find(key);
           if (tf == false) {
               return removal;
           }
           else {
               int result=arr[removal]->count;
               arr[removal]->k=AVAIL;
               arr[removal]->count=0;
               h_size--;
               return result;
           }
       }
    
    void desty(){
        for (int i = 0; i < a_size; i++) {
            if(arr[i]->k!=NUL){
            arr[i]->k=NUL;
            }
        }
    }
};
 
 
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int T;
    cin >> T;
    
   Hash hs;
    
    for (int i = 0; i < T; i++) {
        int N;
        cin >> N;
 
        for (int j = 0; j < N; j++) {
            int a;
            cin >> a;
            hs.linearP(a);
        }
 
        int M;
        cin >> M;
 
        for (int j = 0; j < M; j++) {
            int b;
            cin >> b;
            bool tf=hs.find(b);
            if (tf) {cout << "1" << ' ' << hs.deleteH(b) << '\n';  }
            else { cout << "0" << ' ' << hs.deleteH(b) << '\n'; }
        }
    hs.desty();
    }
    return 0;
}
*/

//12 -3 
class Node {
public:
    int k;
    int count=0;
};
 
class Hash {
private:
    int h_size;
public:
    Node** arr;
    
    Hash() {
        h_size = 0;
        arr=new Node*[a_size];
        for (int i = 0; i < a_size; i++) {
            Node* newN=new Node;
            newN->k=NUL;
            arr[i]=newN;
        }
    }
    bool empty() { return (h_size == 0); }
    int hCode(int key) { return key % a_size; }
    int DCode(int key){return (17-(key%17));}
    
    void dobHash(int key) {
        int hidx = hCode(key);
        int cnt=0;
        if(arr[hidx]->k==NUL){
            h_size++;
            arr[hidx]->k=key;
            arr[hidx]->count = cnt + 1;
        }
        else{
            cnt++;
            if(arr[hidx]->k==key){return;}
            int didx=DCode(key);
            int idx=didx+hidx;
            
        while (1) {
            if (arr[idx]->k == NUL){ break; }
             if(arr[idx]->k==key){return;}
            idx+=didx;
            idx %=a_size;
            cnt++;
            if (cnt > a_size) { return; }
        }
        h_size++;
        arr[idx]->k=key;
        arr[idx]->count = cnt + 1;
        }
    }
 
    bool find(int key) {
        int hidx = hCode(key);
        int cnt = 0;
        if(arr[hidx]->k==NUL){return false;}
        else{
            if(arr[hidx]->k==key){return true;}
            cnt++;
            int didx=DCode(key);
            int idx=didx+hidx;
        while (1) {
            if (arr[idx]->k == NUL) { return false; }
            if (arr[idx]->k == key) { return true; }
            idx+=didx;
            idx %= a_size;
            cnt++;
            if (cnt > a_size) { return false; }
        }
    }
}
    
    int result(int key) {
        int hidx = hCode(key);
            int cnt = 0;
            if(arr[hidx]->k==NUL){return 1;}
            else{
                if(arr[hidx]->k==key){return 1;}
                cnt++;
                int didx=DCode(key);
                int idx=didx+hidx;
            while (1) {
                if (arr[idx]->k == NUL) { return cnt+1; }
                if (arr[idx]->k == key) { return arr[idx]->count; }
                idx+=didx;
                idx %= a_size;
                cnt++;
                if (cnt > a_size) { return false; }
            }
        }
    }
    
    void desty(){
        for (int i = 0; i < a_size; i++) {
            if(arr[i]->k!=NUL){
            arr[i]->k=NUL;
            }
        }
    }
};
 
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int T;
    cin >> T;
    
   Hash hs;
    
    for (int i = 0; i < T; i++) {
        int N;
        cin >> N;
 
        for (int j = 0; j < N; j++) {
            int a;
            cin >> a;
            hs.dobHash(a);
        }
 
        int M;
        cin >> M;
 
        for (int j = 0; j < M; j++) {
            int b;
            cin >> b;
            bool tf=hs.find(b);
            int result=hs.result(b);
            if (tf) {cout << "1" << ' ' << result << '\n';  }
            else { cout << "0" << ' ' << result << '\n'; }
        }
    hs.desty();
    }
    return 0;
}
