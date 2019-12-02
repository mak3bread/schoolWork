#include <iostream>
#include <vector>
using namespace std;
//14-1 -1 출력은 그래프로 , dfs진행은 간선 벡터 따로 만들어서함 -> 타임리밋이랑 메모리 크기 초가 안됨
/*
struct edg{
    int one;
    int two;
};
vector<vector<int>> map(1000, vector<int>(1000,0));
vector<int> v(1000,0);
vector<edg*> e;

void dfs(int x) {
    if (v[x] == -1||v[x]==0) {return;}
    cout << v[x] << ' ';
    v[x] = -1;
    for (int i = 0; i <e.size(); i++) {
        if(e[i]->one==x){
            int temp=e[i]->two;
            dfs(temp);
            continue;
        }
        if(e[i]->two==x){
            int temp=e[i]->one;
            dfs(temp);
            continue;
        }
    }
}
 
int find(int x) {
    for(int i=0;i<1000;i++){
        if(v[i]==x){return i;}
    }
    return -1;
}
 
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    
    int  N,M, A;
    cin >> N >> M >> A;
 
    for (int i = 0; i < N; i++) {
        int I;
        cin >> I;
        v[i]=I;
    }
 
    for (int i = 0; i < M; i++) {
        int s, d;
        cin >> s >> d;
 
        int idx1 = find(s);
        int idx2 = find(d);
 
        if (map[idx1][idx2]==1||map[idx2][idx1]== 1) { cout << -1 << '\n'; }
        else {
            map[idx1][idx2] = 1;
            map[idx2][idx1] = 1;
            edg* newN=new edg;
            newN->one=idx1;
            newN->two=idx2;
            e.push_back(newN);
        }
    }
    
    int K=find(A);
    dfs(K);
    cout << '\n';
    return 0;
}
*/


//14-2
/*
struct edg{
    string data;
    int one;
    int two;
    string label="UNEXP";
};

vector<vector<int>> map(1000, vector<int>(1000,0));
vector<int> v(1000,0);
vector<edg*> e;
vector<string> d;
vector<string> b;
 
int find(int x) {
    for(int i=0;i<1000;i++){
        if(v[i]==x){return i;}
    }
    return -1;
}

void dfs(int x) {
    if (v[x] == -1||v[x]==0) { return; }
    cout << v[x] << ' ';
    v[x] = -1;
    for(int i=0;i<e.size();i++){
                  if(e[i]->label=="UNEXP"){
                      if(e[i]->one==x){
                          int temp=e[i]->two;
                      if(v[temp]!=-1){
                          e[i]->label="DISCO";
                          dfs(temp);
                      }
                      else{
                          e[i]->label="BACK";
                        }
                      }
                      if(e[i]->two==x){
                        int temp=e[i]->one;
                          if(v[temp]!=-1){
                            e[i]->label="DISCO";
                            dfs(temp);
                            }
                           else{
                            e[i]->label="BACK";
                            }
                        }
        }
    }
}
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    
    int  N,M, A;
    cin >> N >> M >> A;
 
    for (int i = 0; i < N; i++) {
        int I;
        cin >> I;
        v[i]=I;
    }
 
    for (int i = 0; i < M; i++) {
        int s, d;
        string str;
        cin >> s >> d>>str;
 
        int idx1 = find(s);
        int idx2 = find(d);
 
        if (map[idx1][idx2]==1||map[idx2][idx1]== 1) { cout << -1 << '\n'; }
        else {
            map[idx1][idx2] = 1;
            map[idx2][idx1] = 1;
            edg* newN=new edg;
            newN->one=idx1;
            newN->two=idx2;
            newN->data=str;
            e.push_back(newN);
        }
    }
    
    int K=find(A);
    dfs(K);
    cout<<'\n';
    
    for(int i=0;i<e.size();i++){
        if(e[i]->label=="DISCO"){d.push_back(e[i]->data);}
        if(e[i]->label=="BACK"){b.push_back(e[i]->data);}
    }
    
    for(int i=0;i<d.size();i++){
        cout<<d[i]<<' ';
    }
    cout<<'\n';
    for(int i=0;i<b.size();i++){
        cout<<b[i]<<' ';
    }
    cout<<'\n';
    return 0;
}
*/

//14-3
/*
template <typename T>
class Node {
public:
    T data;
    Node<T>* prev;
    Node<T>* next;
};

template <typename T>
class queue {
private:
    typedef Node<T>* pNODE;
    typedef Node<T> NODE;
    pNODE head;
    pNODE tail;
    int n;
    int result;
    
public:
    queue() {
        head = new NODE;
        tail = new NODE;
        head->next = tail;
        tail->prev = head;
        n = 0;
        result = 0;
    }
    
    ~queue() {
        while (!empty()) { pop(); }
    }
    
    pNODE createNew(T data) {
        pNODE aNode = new NODE;
        aNode->next = NULL;
        aNode->prev = NULL;
        aNode->data = data;
        return aNode;
    }
    
    bool empty() {
        return (head->next == tail);
    }

    void pop() {
        if (empty()) { return; }
        else {
            pNODE removal = head->next;
            removal->next->prev = head;
            head->next = removal->next;
            delete removal;
        }
    }
 
    void push_back(T data) {
        n++;
        pNODE aNode = createNew(data);
        aNode->next = tail;
        aNode->prev = tail->prev;
        tail->prev->next = aNode;
        tail->prev = aNode;
    }
    int front() {return head->next->data;}
};

struct edg{
    int one;
    int two;
};

struct ver{
    int data;
    bool flag=false;
};

vector<vector<int>> map(1000, vector<int>(1000,0));
vector<ver*> v;
vector<edg*> e;

int find(int x) {
    for(int i=0;i<v.size();i++){
        if(v[i]->data==x){return i;}
    }
    return -1;
}

void bfs(int x){
    queue<int> q;
    q.push_back(x);
    v[x]->flag=true;
    while(!q.empty()){
        x=q.front();
        cout<<v[x]->data<<' ';
        q.pop();
        for(int i=0;i<e.size();i++){
            if(e[i]->one==x){
                int temp=e[i]->two;
                if(v[temp]->flag==true){continue;}
                q.push_back(temp);
                v[temp]->flag=true;
            }
            if(e[i]->two==x){
                int temp=e[i]->one;
                if(v[temp]->flag==true){continue;}
                q.push_back(temp);
                v[temp]->flag=true;
            }
        }
    }
}
 
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    
    int  N,M, A;
    cin >> N >> M >> A;
 
    for (int i = 0; i < N; i++) {
        int I;
        cin >> I;
        ver* newN =new ver;
        newN->data=I;
        v.push_back(newN);
    }
 
    for (int i = 0; i < M; i++) {
        int s, d;
        cin >> s >> d;
 
        int idx1 = find(s);
        int idx2 = find(d);
 
        if (map[idx1][idx2]==1||map[idx2][idx1]== 1) { cout << -1 << '\n'; }
        else {
            map[idx1][idx2] = 1;
            map[idx2][idx1] = 1;
            edg* newN=new edg;
            newN->one=idx1;
            newN->two=idx2;
            e.push_back(newN);
        }
    }
    
    int K=find(A);
    bfs(K);
    cout << '\n';
    return 0;
}
*/
