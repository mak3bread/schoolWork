#include <iostream>
#include <vector>
using namespace std;
 
template <typename T>
class Node {
public:
    Node<T>* left;
    Node<T>* right;
    Node<T>* parent;
    T n;
    int cnt=0;

};
 
template <typename T>
class Tree{
private:
    typedef Node<T>* pNODE;
    typedef Node<T> NODE;
    
    int t_size;
public:
    pNODE root;
    Tree() {
        t_size = 0;
    }
    
    ~Tree() {}
 
    int size() { return t_size; }
 
    bool empty() { return (t_size == 0); }
 
    pNODE createNew(T data) {
        pNODE newN = new NODE;
        newN->left = NULL;
        newN->right = NULL;
        newN->parent = NULL;
        newN->n = data;
        return newN;
    }
 
    void insert(T data) {
        pNODE newN =createNew(data);
        
        if (empty()) {
            root = newN;
            t_size++;
        }
        
        else {
            t_size++;
            pNODE cur = root;
            while (1) {
                if (cur->n < data) {
                    if (cur->right == NULL) {
                        cur->right = newN;
                        newN->parent = cur;
                        break;
                    }
                    else { cur = cur->right; }
                }
                else {
                    if (cur->left == NULL) {
                        cur->left = newN;
                        newN->parent = cur;
                        break;
                    }
                    else {
                        cur = cur->left;
                    }
                }
            }
        }
    }
 
    pNODE find(T data) {
        pNODE cur = root;
        while (1) {
            if (cur->n == data) { return cur; }
            if (cur->n < data) {
                if (cur->right == NULL) { return NULL; }
                else { cur = cur->right; }
            }
            else {
                if (cur->left == NULL) { return NULL; }
                else { cur = cur->left; }
            }
        }
    }
 
    int findDepth(T data) {
        pNODE cur = root;
        int depth = 0;
        while (1) {
            if (cur->n == data) { return depth; }
            
            if (cur->n < data) {
                if (cur->right == NULL) { return 0; }
                else { depth++; cur = cur->right; }
            }
            else {
                if (cur->left == NULL) { return 0; }
                else { depth++; cur = cur->left; }
            }
        }
    }
 
    int findchild(pNODE r) {
        if(r==NULL||(r->left==NULL&&r->right==NULL)){return 0;}
        else if((r->left==NULL&&r->right!=NULL)||(r->right==NULL&&r->left!=NULL)){
            return 1;
        }
        else{return 2;}
    }
    
    void transplant(pNODE u, pNODE v) {
        if (u->parent == NULL) { root = v; }
        else if (u==u->parent->left) { u->parent->left = v; }
        else { u->parent->right = v; }
        if (v != NULL) { v->parent = u->parent; }
    }
 
    void remove(T data) {
        pNODE removal = find(data);
       // if (removal == NULL) { return; }
     
            t_size--;
            if (removal->left == NULL) {
                transplant(removal, removal->right);
                delete removal;
            }
            else if (removal->right == NULL) {
                transplant(removal, removal->left);
                delete removal;
            }
            else {
                pNODE min = findRightMin(removal->right);
                if (min->parent != removal) {
                    transplant(min, min->right);
                    min->right = removal->right;
                    min->right->parent = min;
                }
                transplant(removal, min);
                min->left = removal->left;
                min->left->parent = min;
                delete removal;
            }
    }
 
    pNODE findRightMin(pNODE r) {
        pNODE cur = r;
        while (1) {
            if (cur->left == NULL) { break; }
            else { cur = cur->left; }
        }
        return cur;
    }
 
 
    void treeDestructor(pNODE root) {
        if (root == NULL)
            return;
 
        if (root->left != NULL)
            this->treeDestructor(root->left);
        if (root->right!=NULL)
            this->treeDestructor(root->right);
        t_size--;
        delete(root);
    }
 
    void preorder(pNODE r){
        if(r==NULL)return;
        cout<<r->n<<' ';
        preorder(r->left);
        preorder(r->right);
    }
};
 //11-1
/*
int main() {
    int T;
    cin >> T;
 
    for (int i = 0; i < T; i++) {
        int N;
        cin >> N;
        Tree<int> btr;
 
        for (int j = 0; j < N; j++) {
            int a;
            cin >> a;
            btr.insert(a);
        }
 
        int M;
        cin >> M;
 
        for (int k = 0; k < M; k++) {
            int b;
            cin >> b;
            
            if (btr.find(b) == NULL) { cout << 0 << '\n'; }
            else {
                cout <<btr.findchild(btr.find(b)) << " " <<btr.findDepth(b)  ;
                cout << '\n';
            }
        }
        btr.treeDestructor(btr.root);
    }
    return 0;
}*/

//11-2
/*
int main() {
 
    int T;
    cin >> T;
 
    for (int i = 0; i < T; i++) {
        int N;
        cin >> N;
        Tree<int> btr;
        vector<int> vc;
        vector<int>depth;
        for (int j = 0; j < N; j++) {
            int a;
            cin >> a;
            btr.insert(a);
            vc.push_back(a);
        }
        for (int j = 0; j < N; j++) {
            depth.push_back(btr.findDepth(vc[j]));
        }
        int max = depth[0];
        for (int j = 0; j < N; j++) {
            if (max < depth[j]) { max = depth[j]; }
        }
        cout << max << '\n';
        btr.treeDestructor(btr.root);
    }
 
    return 0;
}*/
 
//11-3

int main() {
 
    int T;
    cin >> T;
 
    for (int i = 0; i < T; i++) {
        int N;
        cin >> N;
        Tree<int> btr;
 
        for (int j = 0; j < N; j++) {
            int a;
            cin >> a;
            btr.insert(a);
 
        }
 
        int M;
        cin >> M;
 
        for (int j = 0; j < M; j++)
        {
            int b;
            cin >> b;
            btr.remove(b);
        }
        if(btr.root==NULL){cout<<0<<'\n';}
        else{
        btr.preorder(btr.root);
        cout<<'\n';
        }
        btr.treeDestructor(btr.root);
    }
 
    return 0;
}

