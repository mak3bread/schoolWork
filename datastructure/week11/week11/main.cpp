#include <iostream>
#include <vector>
using namespace std;
//11-1
/*
struct Node{
    Node* parent;
    int n;
    int depth=0;
    vector<Node*> ch;
};
vector<Node*> Tree;
vector<int> height;
 
void insert(int a,int b) {
    int idx = 0;
    for (int i = 1; i < Tree.size(); i++) {
        if (Tree[i]->n == a) { idx = i; break; }
    }
    Node* newN = new Node;
    newN->n = b;
    newN->parent = Tree[idx];
    newN->depth = Tree[idx]->depth + 1;
    Tree.push_back(newN);
    Tree[idx]->ch.push_back(newN);
    height.push_back(newN->depth);
}
 
void preorder(Node* r) {
    if (r == NULL) { return; }
    cout << r->n << ' ';
    for (int i = 0; i < r->ch.size(); i++) {
        preorder(r->ch[i]);
    }
}
 
void postorder(Node* r) {
    if (r == NULL) { return; }
    
    for (int i = 0; i < r->ch.size(); i++) {
        postorder(r->ch[i]);
    }
    cout << r->n << ' ';
}
 
void printHeight() {
    int max = height[0];
    for (int i = 0; i < height.size(); i++) {
        if (max < height[i]) { max = height[i]; }
    }
    cout << max << '\n';
}
 
 
 
int main() {
 
    int N;
    cin >> N;
 
    for (int i = 0; i < N; i++) {
        int M;
        cin >> M;
        Tree.push_back(0);
        Node* root;
        Node* newN = new Node;
        newN->n = 1;
        newN->parent = NULL;
        root = newN;
        Tree.push_back(newN);
 
        for (int j = 0; j < M; j++) {
            int a,b;
            cin >>a>>b;
            insert(a, b);
        }
        preorder(root);
        cout << '\n';
        postorder(root);
        cout << '\n';
        printHeight();
        Tree.clear();
        height.clear();
    }
 
    return 0;
}*/
 
//11-2
 
/*
class Heap {
private:
    int hcount;
 
public:
    vector <int> hp;
 
    Heap() {
        hp.push_back(0);
        hcount = 0;
    }
    ~Heap() {
        hp.clear();
    }
 
    bool empty() { return (hcount == 0); }
 
    void swap(int* a, int* b) {
        int temp = *a;
        *a = *b;
        *b = temp;
    }
 
    void insert(int data) {
        hp.push_back(data);
        hcount++;
        if (hcount <= 1) { return; }
        else {
            int child = hcount;
            while (1) {
                if (hcount <= 1) { break; }
                int parent = child / 2;
                if (hp[child] >= hp[parent]) { break; }
                else { swap(&hp[child], &hp[parent]); }
                child = child / 2;
            }
 
        }
    }
 
    void print() {
        if (empty()) { cout << -1 << '\n'; }
        else {
            for (int i = 1; i < hp.size(); i++) {
                cout << hp[i] << ' ';
            }
            cout << '\n';
        }
    }
    
 
    int size() { return hcount; }
};
 
 
int main() {
 
    int N;
    cin >> N;
    Heap hp;
    for (int i = 0; i < N; i++) {
        string s;
        cin >> s;
 
            if (s == "isEmpty") {
                cout << hp.empty() << '\n';
            }
            else  if (s == "insert") {
                int a;
                cin >> a;
                hp.insert(a);
            }
            else if (s=="print") {
                hp.print();
            }
            else if (s=="size") {
                cout << hp.size() << '\n';
            }
 
    }
 
    return 0;
}*/
 
//11-3

class Node {
public:
    int n;
    int depth ;
    Node* parent;
    Node* left;
    Node* right;
};
 
class Tree{
private:
    int t_size;
    typedef Node* pNODE;
    typedef Node NODE;
 
public:
    pNODE root;
 
    Tree() {
        root = NULL;
        t_size = 0;
    }
 
    void treeD(pNODE r) {
        if (r == NULL)return;
        if (r->left != NULL) { treeD(r->left); }
        if (r->right != NULL) { treeD(r->right); }
        t_size--;
        delete(r);
    }
 
    pNODE createNew(int data) {
        pNODE newN = new NODE;
        newN->n = data;
        newN->depth = 1;
        newN->parent = NULL;
        newN->left = NULL;
        newN->right = NULL;
        return newN;
    }
 
    pNODE find(int data) {
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
 
    bool empty() { return(t_size == 0); }
 
    void insert(int data) {
        pNODE newN = createNew(data);
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
                        newN->parent = cur;
                        cur->right = newN;
                        newN->depth = cur->depth + 1;
                        break;
                    }
                    else { cur = cur->right; }
 
                }
                else {
                    if (cur->left == NULL) {
                        newN->parent = cur;
                        cur->left = newN;
                        newN->depth = cur->depth + 1;
                        break;
                    }
                    else { cur = cur->left; }
                }
            }
        }
    }
};
 
int main() {
 
    int T;
    cin >> T;
 
    for (int i = 0; i < T; i++) {
        int N;
        cin >> N;
        Tree tr;
        for (int j = 0; j < N; j++) {
            int a;
            cin >> a;
            tr.insert(a);
        }
 
        int M;
        cin >> M;
 
        for (int j = 0; j < M; j++) {
            int b;
            cin >> b;
            Node* cur=tr.find(b);
            if (cur == NULL) { cout << 0 << '\n'; }
            else {
                cout << cur->depth << '\n';
            }
        }
 
 
        tr.treeD(tr.root);
    }
 
}
