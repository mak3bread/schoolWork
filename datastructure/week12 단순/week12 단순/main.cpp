#include <iostream>
#include <vector>
using namespace std;
vector<int> hs;
int MAX = 353333;
//12-1
/*
int hCode(int key) {return key % MAX;}

int main() {
    int T;
    cin >> T;
    for (int i = 0; i < T; i++) {
        
        hs.resize(MAX,0);
        
        int N;
        cin >> N;
        for (int j = 0; j < N; j++) {
            int key;
            cin >> key;
            int idx = hCode(key);
            while (1) {
                if (hs[idx] == 0) {hs[idx] = key;break;}
                else {idx =(idx + 1)%MAX;}
            }
        }
        
        int M;
        cin >> M;
        
        for (int j = 0; j < M; j++) {
            int key;
            cin >> key;
            
            int idx = hCode(key);
            int tf = 0;
            int cnt = 1;
            
            for (int k = 0; k < MAX; k++) {
                if (hs[idx] == 0) {
                    break;
                }
                else if (hs[idx] == key) {
                    tf = 1;
                    break;
                }
                else {
                    idx = (idx + 1) % MAX;
                    cnt++;
                }
            }
            cout << tf << " " << cnt << endl;
        }
        hs.clear();
    }
}*/
//12-2

int hCode(int key) {
    return key % MAX;
}

int main() {
    int T;
    cin >> T;
    for (int i = 0; i < T; i++) {
        
        hs.resize(MAX,0);
        
        int N;
        cin >> N;
        for (int j = 0; j < N; j++) {
            int key;
            cin >> key;
            int idx = hCode(key);
            while (1) {
                if (hs[idx] == 0||hs[idx]==-1) {hs[idx] = key;break;}
                else {idx =(idx + 1)%MAX;}
            }
        }
        
        int M;
        cin >> M;
        
        for (int j = 0; j < M; j++) {
            int key;
            cin >> key;
            
            int idx = hCode(key);
            int tf = 0;
            int cnt = 1;
            
            for (int k = 0; k < MAX; k++) {
                if (hs[idx] == 0) {
                    break;
                }
                else if (hs[idx] == key) {
                    tf = 1;
                    hs[idx]=-1;
                    break;
                }
                else {
                    idx = (idx + 1) % MAX;
                    cnt++;
                }
            }
            cout << tf << " " << cnt << endl;
        }
        hs.clear();
    }
 return 0;
}

//12-3
/*
int hCode(int key) {return key % MAX;}

int dCode(int key){return (17-(key%17));}

int main() {
int T;
cin >> T;
for (int i = 0; i < T; i++) {
    
    hs.resize(MAX,0);
    
    int N;
    cin >> N;
    for (int j = 0; j < N; j++) {
        int key;
        cin >> key;
        int hidx = hCode(key);
        
        if(hs[hidx]==0){hs[hidx]=key;}
        else{
            int didx=dCode(key);
            int idx=didx+hidx;
        while (1) {
            if (hs[idx] == 0) {hs[idx] = key;break;}
            else {idx =(idx + didx)%MAX;}
        }
    }
}
    
    int M;
    cin >> M;
    
    for (int j = 0; j < M; j++) {
        int key;
        cin >> key;
        
        int hidx = hCode(key);
        int tf = 0;
        int cnt = 1;
        
        if(hs[hidx]==0){cout << 0 << " " << cnt << '\n';continue;}
        else{
            if(hs[hidx]==key){cout << 1 << " " << cnt << '\n';}
            
            else{
                cnt++;
                int didx=dCode(key);
                int idx=didx+hidx;
            for (int k = 0; k < MAX; k++) {
            if (hs[idx] == 0) {
                break;
            }
            else if (hs[idx] == key) {
                tf = 1;
                break;
            }
            else {
                idx = (idx + didx) % MAX;
                cnt++;
            }
        }
        cout << tf << " " << cnt << endl;
        }
    }
}
    hs.clear();
}
    return 0;
}
*/
