//9-1
/*
 #include <iostream>
#include <vector>
using namespace std;
vector<int> hp;
int hcount=0;

void swap(int* a,int* b){
    int temp=*a;
    *a=*b;
    *b=temp;
}

void push(int data){
    hp.push_back(data);
    hcount++;
    int child=hcount;
    if(hcount<=1){return;}
    else{
        while(1){
            if(child<=1){break;}
            int parent=child/2;
            if(hp[child]>=hp[parent]){break;}
            else{swap(&hp[child],&hp[parent]);}
            
            child=child/2;
        }
    }
}

void print(){
    if(hcount<=0){cout<<-1<<'\n';}
    else{
        vector<int>::iterator it=hp.begin();
        it++;
        for(;it!=hp.end();it++){
            cout<<*it<<' ';
        }
        cout<<'\n';
    }
}

int main(){
hp.push_back(0);
    
    int N;
    cin>>N;
    
    for(int i=0;i<N;i++){
        string s;
        cin>>s;
        
        if(s=="insert"){
            int a;
            cin>>a;
            push(a);
        }
        
        else if(s=="size"){
            cout<<hcount<<'\n';
        }
        
        else if(s=="isEmpty"){
            if(hcount==0){cout<<1<<'\n';}
            else{cout<<0<<'\n';}
        }
        
        else if(s=="print"){
            print();
        }
        
        else{continue;}
    }
    
    return 0;
}
*/

//9-2
/*
#include <iostream>
#include <vector>
using namespace std;
vector<int> hp;
int hcount=0;

void swap(int* a,int* b){
    int temp=*a;
    *a=*b;
    *b=temp;
}

void push(int data){
    hp.push_back(data);
    hcount++;
    int child=hcount;
    if(hcount<=1){return;}
    else{
        while(1){
            if(child<=1){break;}
            int parent=child/2;
            if(hp[child]>=hp[parent]){break;}
            else{swap(&hp[child],&hp[parent]);}
            
            child=child/2;
        }
    }
}

void print(){
    if(hcount<=0){cout<<-1<<'\n';}
    else{
        vector<int>::iterator it=hp.begin();
        it++;
        for(;it!=hp.end();it++){
            cout<<*it<<' ';
        }
        cout<<'\n';
    }
}

int top(){
    if(hcount<=0){return -1;}
    else{return hp[1];}
}

int pop(){
    if(hcount<=0){return -1;}
    else{
        int result=top();
        if(hcount==1){
            hp.pop_back();
            hcount--;
            return result;
        }
        else if(hcount==2){
            swap(&hp[1],&hp[2]);
            hcount--;
            hp.pop_back();
            return result;
        }
        else{
            swap(&hp[1],&hp[hcount]);
            hp.pop_back();
            hcount--;
            
            int parent=1;
            
            while(1){
                int child;
                int left=(parent*2>hcount)?-1:parent*2;
                int right=(parent*2+1>hcount)?-1:parent*2+1;
                if(left==-1&&right==-1){break;}
                else if(left!=-1&&right==-1){child=left;}
                else{child=(hp[left]>hp[right]?right:left);}
                if(hp[parent]<=hp[child]||(left==-1&&right==-1)){break;}
                else{swap(&hp[parent],&hp[child]);}
                
                parent=child;
            }
            return result;
        }
    }
}

int main(){
hp.push_back(0);
    
    int N;
    cin>>N;
    
    for(int i=0;i<N;i++){
        string s;
        cin>>s;
        
        if(s=="insert"){
            int a;
            cin>>a;
            push(a);
        }
        
        else if(s=="size"){
            cout<<hcount<<'\n';
        }
        
        else if(s=="isEmpty"){
            if(hcount==0){cout<<1<<'\n';}
            else{cout<<0<<'\n';}
        }
        
        else if(s=="print"){
            print();
        }
        
        else if(s=="pop"){
            cout<<pop()<<'\n';
        }
        
        else if(s=="top"){
            cout<<top()<<'\n';
        }
        
        else{continue;}
    }
    
    return 0;
}
*/

//9-3
/*
#include <iostream>
#include <vector>
using namespace std;
class heap{
private:
    int hcount =0;
public:
   vector<int> hp;
    heap(){
        hcount=0;
        hp.push_back(0);
    }
    void swap(int* a,int* b){
        int temp=*a;
        *a=*b;
        *b=temp;
    }

    void push(int data){
        hp.push_back(data);
        hcount++;
        int child=hcount;
        if(hcount<=1){return;}
        else{
            while(1){
                if(child<=1){break;}
                int parent=child/2;
                if(hp[child]>=hp[parent]){break;}
                else{swap(&hp[child],&hp[parent]);}
                
                child=child/2;
            }
        }
    }

    void print(){
        if(hcount<=0){cout<<-1<<'\n';}
        else{
            vector<int>::iterator it=hp.begin();
            it++;
            for(;it!=hp.end();it++){
                cout<<*it<<' ';
            }
            cout<<'\n';
        }
    }

    int top(){
        if(hcount<=0){return -1;}
        else{return hp[1];}
    }

    int pop(){
        if(hcount<=0){return -1;}
        else{
            int result=top();
            if(hcount==1){
                hp.pop_back();
                hcount--;
                return result;
            }
            else if(hcount==2){
                swap(&hp[1],&hp[2]);
                hcount--;
                hp.pop_back();
                return result;
            }
            else{
                swap(&hp[1],&hp[hcount]);
                hp.pop_back();
                hcount--;
                
                int parent=1;
                
                while(1){
                    int child;
                    int left=(parent*2>hcount)?-1:parent*2;
                    int right=(parent*2+1>hcount)?-1:parent*2+1;
                    if(left==-1&&right==-1){break;}
                    else if(left!=-1&&right==-1){child=left;}
                    else{child=(hp[left]>hp[right]?right:left);}
                    if(hp[parent]<=hp[child]||(left==-1&&right==-1)){break;}
                    else{swap(&hp[parent],&hp[child]);}
                    
                    parent=child;
                }
                return result;
            }
        }
    }

};



int main(){
    int T;
    cin>>T;
    
    for(int i=0;i<T;i++){
       heap hip;
       heap pq;
       
        int N,p;
        cin>>N>>p;
        
        for(int j=0;j<N;j++){
            int a;
            cin>>a;
            hip.push(a);
        }
        cout<<hip.hp[p]<<'\n';
        for(int j=0;j<N;j++){
            pq.push(hip.pop());
        }
        cout<<pq.hp[p]<<'\n';
    }
  
    return 0;
}
*/

//9-4
#include <iostream>
#include <vector>
using namespace std;
class heap{
private:
    int hcount =0;
    int direction=0;
public:
   vector<int> hp;
    heap(int direct){
        direction=direct;
        hcount=0;
        hp.push_back(0);
    }
    
    void swap(int* a,int* b){
        int temp=*a;
        *a=*b;
        *b=temp;
    }

    void push(int data){
        hp.push_back(data);
        hcount++;
        int child=hcount;
        if(hcount<=1){return;}
        else{
            if(direction==-1){
            while(1){
                if(child<=1){break;}
                int parent=child/2;
                if(hp[child]>=hp[parent]){break;}
                else{swap(&hp[child],&hp[parent]);}
                
                child=child/2;
            }
          }
           if(direction==1){
                while(1){
                    if(child<=1){break;}
                    int parent=child/2;
                    if(hp[child]<=hp[parent]){break;}
                    else{swap(&hp[child],&hp[parent]);}
                    
                    child=child/2;
                }
            }
        
        }
    }

    void print(){
        if(hcount<=0){cout<<-1<<'\n';}
        else{
            vector<int>::iterator it=hp.begin();
            it++;
            for(;it!=hp.end();it++){
                cout<<*it<<' ';
            }
            cout<<'\n';
        }
    }

    int top(){
        if(hcount<=0){return -1;}
        else{return hp[1];}
    }

    int pop(){
        if(hcount<=0){return -1;}
        else{
            int result=top();
            if(hcount==1){
                hp.pop_back();
                hcount--;
                return result;
            }
            else if(hcount==2){
                swap(&hp[1],&hp[2]);
                hcount--;
                hp.pop_back();
                return result;
            }
            else{
                swap(&hp[1],&hp[hcount]);
                hp.pop_back();
                hcount--;
                
                int parent=1;
                if(direction==-1){
                while(1){
                    int child;
                    int left=(parent*2>hcount)?-1:parent*2;
                    int right=(parent*2+1>hcount)?-1:parent*2+1;
                    if(left==-1&&right==-1){break;}
                    else if(left!=-1&&right==-1){child=left;}
                    else{child=(hp[left]>hp[right]?right:left);}
                    if(hp[parent]<=hp[child]||(left==-1&&right==-1)){break;}
                    else{swap(&hp[parent],&hp[child]);}
                    
                    parent=child;
                }
                }
                if(direction==1){
                    while(1){
                        int child;
                        int left=(parent*2>hcount)?-1:parent*2;
                        int right=(parent*2+1>hcount)?-1:parent*2+1;
                        if(left==-1&&right==-1){break;}
                        else if(left!=-1&&right==-1){child=left;}
                        else{child=(hp[left]>=hp[right]?left:right);}
                        if(hp[parent]>=hp[child]||(left==-1&&right==-1)){break;}
                        else{swap(&hp[parent],&hp[child]);}
                        parent=child;
                    }
                }
                return result;
            }
        }
    }

};

int main(){
    int T;
    cin>>T;
    
    for(int i=0;i<T;i++){
       heap hip(-1);
       heap pq(-1);
       heap max_hip(1);
       heap max_pq(1);
        
       
        int N,p;
        cin>>N>>p;
        
        for(int j=0;j<N;j++){
            int a;
            cin>>a;
            hip.push(a);
            max_hip.push(a);
            
        }
        cout<<hip.hp[p]<<'\n';
        
        for(int j=0;j<N;j++){
            pq.push(hip.pop());
        }
        cout<<pq.hp[p]<<'\n';
        cout<<max_hip.hp[p]<<'\n';

        for(int j=0;j<N;j++){
         max_pq.push(max_hip.pop());
        }
            cout<<max_pq.hp[p]<<'\n';

    }
  
    return 0;
}
