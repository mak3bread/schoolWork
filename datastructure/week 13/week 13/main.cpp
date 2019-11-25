//13-1 인접행렬
/*
#include <iostream>
#include <vector>
using namespace std;
 
vector<vector<int>>map(10001, vector<int>(10001, 0));
vector<int> v;
 
int find(int a) {
    for (int i = 0; i < v.size(); i++) {
        if (v[i] == a) { return i; }
    }
    return -1;
}
 
int main() {
 
    ios_base::sync_with_stdio(0);
    cin.tie(0);
 
    int N,M;
    cin >> N >> M;
    int edgN = 0;
 
    for (int i = 0; i < N; i++) {
        int I;
        cin >> I;
        v.push_back(I);
    }
 
    for (int i = 0; i < M; i++) {
        int a, b;
        cin >> a >> b;
 
        int idx1 = find(a);
        int idx2 = find(b);
 
        if (a == b) { cout << -1 << '\n'; }
        else if (idx1 == -1 || idx2 == -1) { cout << -1 << '\n'; }
        else if(map[a][b]==1||map[b][a]==1) {
            cout << -1 << '\n';
        }
        else {
            edgN++;
            map[a][b] = 1;
            map[b][a] = 1;
        }
    }
 
    cout << N << ' ' << edgN << '\n';
 
 
 
    return 0;
}*/

//13-1 구조체 배열
/*
#include <iostream>
#include <vector>
using namespace std;
 
struct ver {
    int name;
    int idx;
};
 
struct edg {
    ver* one;
    ver* two;
};
 
vector<ver*> v;
vector<edg*> e;
 
int find(int a) {
    for (int i = 0; i < v.size(); i++) {
        if (v[i]->name == a) { return v[i]->idx; }
    }
    return -1;
}
 
int main() {
 
    ios_base::sync_with_stdio(0);
    cin.tie(0);
 
    int N, M;
    cin >> N >> M;
    int edgN = 0;
 
    for (int i = 0; i < N; i++) {
        int I;
        cin >> I;
        ver* newN = new ver;
        newN->idx = i;
        newN->name = I;
        v.push_back(newN);
    }
 
    for (int i = 0; i < M; i++) {
        int a, b;
        cin >> a >> b;
 
        int idx1 = find(a);
        int idx2 = find(b);
        bool tf = true;
 
        for (int j = 0; j < e.size(); j++) {
            if ((e[j]->one->name == a && e[j]->two->name == b) || (e[j]->one->name == b && e[j]->two->name == a)) {
                tf = false;
                break;
            }
        }
 
        if (tf == false) { cout << -1 << '\n'; continue; }
        if (a == b) { cout << -1 << '\n'; }
        else if (idx1 == -1 || idx2 == -1) { cout << -1 << '\n'; }
        else {
 
            edgN++;
            edg* newN = new edg;
            newN->one = v[idx1];
            newN->two = v[idx2];
            e.push_back(newN);
        }
    }
 
    cout << N << ' ' << edgN << '\n';
    return 0;
}*/
 
//13-2 인접 행렬 쓰면 100001 * 100001 행렬이라 너무 큼
//구조체배열

/*
#include <iostream>
#include <vector>
using namespace std;
 
struct ver {
    int name;
    int idx;
};
 
struct edg {
    ver* one;
    ver* two;
};
 
vector<ver*> v;
vector<edg*> e;
 
int find(int a) {
    for (int i = 0; i < v.size(); i++) {
        if (v[i]->name == a) { return v[i]->idx; }
    }
    return -1;
}
 
int main() {
 
    ios_base::sync_with_stdio(0);
    cin.tie(0);
 
    int N, M, K;
    cin >> N >> M >> K;
    int edgN = 0;
 
    for (int i = 0; i < N; i++) {
        int I;
        cin >> I;
        ver* newN = new ver;
        newN->idx = i;
        newN->name = I;
        v.push_back(newN);
    }
 
    for (int i = 0; i < M; i++) {
        int a, b;
        cin >> a >> b;
 
        int idx1 = find(a);
        int idx2 = find(b);
        bool tf = true;
 
        for (int j = 0; j < e.size(); j++) {
            if ((e[j]->one->name == a && e[j]->two->name == b) || (e[j]->one->name == b && e[j]->two->name == a)) {
                tf = false;
                break;
            }
        }
 
        if (tf == false) { cout << -1 << '\n'; continue; }
        if (a == b) { cout << -1 << '\n'; }
        else if (idx1 == -1 || idx2 == -1) { cout << -1 << '\n'; }
        else {
 
            edgN++;
            edg* newN = new edg;
            newN->one = v[idx1];
            newN->two = v[idx2];
            e.push_back(newN);
        }
    }
 
    cout << N << ' ' << edgN << '\n';
 
 
    for (int i = 0; i < K; i++) {
        int s, d;
        cin >> s >> d;
        int idx1 = find(s);
        int idx2 = find(d);
        bool tf2 = true;
 
        for (int j = 0; j < e.size(); j++) {
            if ((e[j]->one->name == s && e[j]->two->name == d) || (e[j]->one->name == d && e[j]->two->name == s)) {
                tf2 = false;
                break;
            }
        }
        if (tf2 == false) { cout << 1 << '\n'; continue; }
        if (idx1 == -1 || idx2 == -1) { cout << -1 << '\n'; }
        else {
             cout << 0 << '\n';
        }
    }
    
    return 0;
}
 */

//13-3

/*
#include <iostream>
#include <vector>
using namespace std;
 
struct ver {
    int name;
    int idx;
};
 
struct edg {
    ver* one;
    ver* two;
    string s="0";
};
 
vector<ver*> v;
vector<edg*> e;
 
int find(int a) {
    for (int i = 0; i < v.size(); i++) {
        if (v[i]->name == a) { return v[i]->idx; }
    }
    return -1;
}

void print(){
    if(e.size()==0){return;}
    else{
    for(int i=0;i<e.size();i++){
        if(e[i]->s!="0"){
        cout<<e[i]->s<<' ';
        }
    }
        cout<<'\n';
    }
}
 
int main() {
 
    ios_base::sync_with_stdio(0);
    cin.tie(0);
 
    int N, M, K;
    cin >> N >> M >> K;
    int edgN = 0;
 
    for (int i = 0; i < N; i++) {
        int I;
        cin >> I;
        ver* newN = new ver;
        newN->idx = i;
        newN->name = I;
        v.push_back(newN);
    }
 
    for (int i = 0; i < M; i++) {
        int a, b;
        string str;
        cin >> a >> b>>str;
 
        int idx1 = find(a);
        int idx2 = find(b);
        bool tf = true;
 
        for (int j = 0; j < e.size(); j++) {
            if ((e[j]->one->name == a && e[j]->two->name == b) || (e[j]->one->name == b && e[j]->two->name == a)) {
                tf = false;
                break;
            }
        }
 
        if (tf == false) { cout << -1 << '\n'; continue; }
        if (a == b) { cout << -1 << '\n'; }
        else if (idx1 == -1 || idx2 == -1) { cout << -1 << '\n'; }
        else {
 
            edgN++;
            edg* newN = new edg;
            newN->one = v[idx1];
            newN->two = v[idx2];
            newN->s=str;
            e.push_back(newN);
        }
    }
 
    cout << N << ' ' << edgN << '\n';
 
 
    for (int i = 0; i < K; i++) {
        int L;
        cin>>L;
        int idx=find(L);
        int cnt=0;
        
        if(idx==-1){cout<<-1<<'\n';}
        else{
            for(int j=0;j<e.size();j++){
                if(e[j]->one==NULL||e[j]->two==NULL){continue;}
                if(e[j]->one->name==L||e[j]->two->name==L){
                    e[j]->s="0";
                    e[j]->one=NULL;
                    e[j]->two=NULL;
                    cnt++;
                }
            }
            
            v[idx]->name=-1;
            v[idx]->idx=-1;
            edgN-=cnt;
            cout<<edgN<<' ';
            print();
        }
    }
    return 0;
}
*/
