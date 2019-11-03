#include <iostream>
using namespace std;

template<typename T>
class Node{
public:
    T n;
    Node<T>* left;
    Node<T>* right;
    Node<T>* parent;
};

template <typename T>
class Tree{
private:
    typedef Node<T>* pNODE;
    typedef Node<T> NODE;
    pNODE root;
    int count;
    int size;
public:
    Tree(){
        count=0;
        pNODE newN=new NODE;
        newN->left=NULL;
        newN->right=NULL;
        newN->parent=NULL;
        newN->n=0;
        root=newN;
        size=1;
    }
    ~Tree(){}
    
    int Size(){return size;}
    
    bool empty(){return (size==0);}
    
    pNODE find(T data){
        pNODE r=root;
        int count=0;
        while(1){
            count++;
            if(r->n==data){
                return r;
            }
            if(r->n<data){
                if(r->right==NULL){
                    return NULL;
                }
                else{
                    r=r->right;
                }
            }
            else{
                if(r->left==NULL){return NULL;}
                else{r=r->left;}
            }
        }
    }
    
    pNODE createNew(T data){
        pNODE newN=new NODE;
        newN->left=NULL;
        newN->right=NULL;
        newN->n=data;
        newN->parent=NULL;
        return newN;
    }
    
    void insert(T data){
        if(root->n==0){
            root->n=data;
            return;
        }
       // if(this->find(data)!=NULL){cout<<"이미 값이 존재"<<'\n'; return;} 만약 중복 입력이 있는경우
        pNODE aNode=createNew(data);
        pNODE r=root;
        while(1){
            if(r->n<data){
                if(r->right==NULL){
                    r->right=aNode;
                    aNode->parent=r;
                    aNode->n=data;
                    return;
                }
                else{r=r->right;}
            }
            else{
                if(r->left==NULL){
                    r->left=aNode;
                    aNode->parent=r;
                    aNode->n=data;
                    return;
                }
                else{r=r->left;}
            }
        }
    }
    
    int findRightMinC(pNODE r){//노드 r 의 오른쪽 자식중에서 가장 작은 노드를 찾는다 left로 접근
        pNODE cur=r->right;
        int count=0;
        if(r->left==NULL){return count;}
        else{
        while(1){
            if(cur->left==NULL){break;}
            cur=cur->left;
            count++;
        }
        return count;
        }
    }
    
    pNODE findRightMin(pNODE r){
        if(r->left==NULL){return NULL;}
        else{
            pNODE cur=r->right;
            while(1){
                if(cur->left==NULL){break;}
                cur=cur->left;
            }
            return cur;
        }
    }
    
    void remove(T data){
        pNODE removal=find(data);
        if(removal==NULL){cout<<"해당 노드가 없습니다."<<'\n';}
        else{
            if(removal->left==NULL){
                transplant(removal, removal->right);
            }
            else if(removal->right==NULL){
                transplant(removal,removal->left);
            }
            else{
                pNODE min=findRightMin(removal);
                if(min->parent!=removal){
                    transplant(min, min->right);
                    min->right=removal->right;
                    min->right->parent=min;
                }
                transplant(removal, min);
                min->left=removal->left;
                min->left->parent=min;
            }
        }
        
    }
    
    void transplant(pNODE u,pNODE v){
        if(u->parent==NULL){
            root=v;
        }
        else if(u==u->parent->left){
            u->parent->left=v;
        }
        else{u->parent->right=v;}
        if(v!=NULL){
            v->parent=u->parent;
        }
    }
};
