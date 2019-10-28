//7-1
/*
#include <iostream>
using namespace std;
#include <vector>

struct Node{
    int n=0;
    vector<Node*>ch;
    Node* parent;
};

int main(){
    vector<Node*>tree;
    
    int N;
    cin>>N;
    Node* root=NULL;
    Node* newNode=new Node;
    newNode->n=1;
    newNode->parent=NULL;
    root=newNode;
    tree.push_back(newNode);
    
    for(int i=0;i<N;i++){
        string s;
        cin>>s;
        if(s=="insert"){
            int a,b;
            cin>>a>>b;
            int indx=0;
            for(int j=0;j<tree.size();j++){
                if(tree[j]->n==a){indx=j;break;}
            }
            Node* newN=new Node;
            newN->n=b;
            newN->parent=tree[indx];
            tree.push_back(newN);
            tree[indx]->ch.push_back(newN);
        }
        else if(s=="printChild"){
            int a;
            cin>>a;
            int indx=0;
            for(int j=0;j<tree.size();j++){
                if(tree[j]->n==a){indx=j;break;}
            }
            for(int j=0;j<tree[indx]->ch.size();j++){
                cout<<tree[indx]->ch[j]->n<<' ';
            }
            cout<<'\n';
        }
        else if(s=="printDepth"){
            
            
        }
        else{continue;}
    }
    
    
    return 0;
}
*/

//7-2
/*
#include <iostream>
using namespace std;
#include <vector>

struct Node{
    int n=0;
    vector<Node*>ch;
    Node* parent;
};

int main(){
    vector<Node*>tree;
    
    int N;
    cin>>N;
    Node* root=NULL;
    Node* newNode=new Node;
    newNode->n=1;
    newNode->parent=NULL;
    root=newNode;
    tree.push_back(newNode);
    
    for(int i=0;i<N;i++){
        string s;
        cin>>s;
        if(s=="insert"){
            int a,b;
            cin>>a>>b;
            int indx=0;
           
            for(int j=0;j<tree.size();j++){
                if(tree[j]->n==a){indx=j;break;}
            }
            if(indx==0&&a!=1){cout<<-1<<'\n';}
            else{
            Node* newN=new Node;
            newN->n=b;
            newN->parent=tree[indx];
            tree.push_back(newN);
            tree[indx]->ch.push_back(newN);
            }
        }
        else if(s=="printChild"){
            int a;
            cin>>a;
            int indx=0;
            for(int j=0;j<tree.size();j++){
                if(tree[j]->n==a){indx=j;break;}
            }
            if(indx==0&&a!=1){cout<<-1<<'\n';}
            else{
                if(tree[indx]->ch.size()==0){cout<<0<<'\n';}
                else{
            for(int j=0;j<tree[indx]->ch.size();j++){
                cout<<tree[indx]->ch[j]->n<<' ';
            }
            cout<<'\n';
                }
            }
        }
        
        else if(s=="printDepth"){
            int a;
            cin>>a;
            int indx=0;
            for(int j=0;j<tree.size();j++){
                if(tree[j]->n==a){indx=j;break;}
            }
            if(indx==0&&a!=1){cout<<-1<<'\n';}
            else{
                int depth=0;
                Node* iter=tree[indx];
                while(iter->parent!=NULL){
                    depth++;
                    iter=iter->parent;
                }
                cout<<depth<<'\n';
            }
            
        }
        else{continue;}
    }
    
    
    return 0;
}
*/

//7-3
/*
#include <iostream>
using namespace std;
#include <vector>

struct Node{
    int n=0;
    vector<Node*>ch;
    Node* parent;
};

void preorder(Node* r){
    if(r==NULL){return;}
    cout<<r->n<<' ';
    for(int i=0;i<r->ch.size();i++){
        preorder(r->ch[i]);
    }
}

void postorder(Node* r){
    if(r==NULL){return;}
    for(int i=0;i<r->ch.size();i++){
        postorder(r->ch[i]);
    }
    cout<<r->n<<' ';
    
}

int main(){
    int N;
    cin>>N;
    for(int i=0;i<N;i++){
        vector<Node*> tree;
        Node* root=NULL;
        Node* newNode=new Node;
        newNode->n=1;
        newNode->parent=NULL;
        root=newNode;
        tree.push_back(newNode);
        
        int M;
        cin>>M;
        for(int j=0;j<M;j++){
            int a,b;
            cin>>a>>b;
            int indx=0;
            for(int k=0;k<tree.size();k++){
                if(tree[k]->n==a){indx=k;break;}
            }
            Node* newN=new Node;
            newN->n=b;
            newN->parent=tree[indx];
            tree.push_back(newN);
            tree[indx]->ch.push_back(newN);
        }
        preorder(root);
        cout<<'\n';
        postorder(root);
        cout<<'\n';
    }
    
    return 0;
}
 */

//7-4
#include <iostream>
using namespace std;
#include <vector>

struct Node{
    int n=0;
    vector<Node*>ch;
    Node* parent;
};

void preorder(Node* r){
    if(r==NULL){return;}
    cout<<r->n<<' ';
    for(int i=0;i<r->ch.size();i++){
        preorder(r->ch[i]);
    }
}

void postorder(Node* r){
    if(r==NULL){return;}
    for(int i=0;i<r->ch.size();i++){
        postorder(r->ch[i]);
    }
    cout<<r->n<<' ';
    
}

int main(){
    int N;
    cin>>N;
    for(int i=0;i<N;i++){
        vector<Node*> tree;
        Node* root=NULL;
        Node* newNode=new Node;
        newNode->n=1;
        newNode->parent=NULL;
        root=newNode;
        tree.push_back(newNode);
        
        int M;
        cin>>M;
        for(int j=0;j<M;j++){
            int a,b;
            cin>>a>>b;
            int indx=0;
            for(int k=0;k<tree.size();k++){
                if(tree[k]->n==a){indx=k;break;}
            }
            Node* newN=new Node;
            newN->n=b;
            newN->parent=tree[indx];
            tree.push_back(newN);
            tree[indx]->ch.push_back(newN);
        }
        vector<int> Height;
        for(int j=0;j<tree.size();j++){
            int depth=0;
            Node* iter=tree[j];
                   while(iter->parent!=NULL){
                       depth++;
                       iter=iter->parent;
                   }
            Height.push_back(depth);
        }
        int max=Height[0];
        
        for(int j=1;j<Height.size();j++){
            if(max<Height[j]){
                max=Height[j];
            }
        }
        
        preorder(root);
        cout<<'\n';
        postorder(root);
        cout<<'\n';
        cout<<max<<'\n';
    }
    
    return 0;
}


