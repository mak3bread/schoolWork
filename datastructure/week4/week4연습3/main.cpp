#include <iostream>
using namespace std;

//array class
class arrayStack {
public:
    int* S;
    int capacity;
    int t;

    arrayStack(int cap) {
        capacity = cap;
        t = -1;
        S = new int[capacity];
    }

    int size() { return (t + 1); }

    bool empty() { return (t < 0); }

    int top() {
        if (empty()) { return -1; }
        else { return S[t]; }
    }

    void push(int e) {
        if (size() == capacity) { return; }
        else { S[++t]=e; }
    }

    int pop() {
        if (empty()) {
            return -1;
        }
        else {
            return S[t--];
        }
    }
};

//List Stack class
template <typename T>
class Node {
public:
    T data;
    Node<T>* next;
    Node<T>* prev;
};

template <typename T>
class DStack {
private:
    typedef Node<T>* pNODE;
    typedef Node<T> NODE;
    pNODE head;
    pNODE tail;
    int n;
    T result;
public:
    DStack() {
        head = new NODE;
        tail = new NODE;
        head->next = tail;
        tail->prev = head;
        n = 0;
    }
    ~DStack() {
        while (!empty()) { pop(); }
    }
    
    pNODE createNew(int e) {
        pNODE aNode = new NODE;
        
        aNode->data = e;
        aNode->next = NULL;
        aNode->prev = NULL;
        
        return aNode;
    }
    
    bool empty() { return (head->next == tail); }
    
    int top() {
        if (empty()) { return -1; }
        else { return head->next->data; }
    }
    
    pNODE front() { return head->next; }
    pNODE back() { return tail; }
    
    void push(int e) {
        pNODE aNode = createNew(e);
        aNode->next = head->next;
        aNode->prev = head;
        head->next->prev = aNode;
        head->next = aNode;
        n++;
    }
    
    int pop() {
        if (empty()) { return -1; }
        else {
            pNODE remove = head->next;
            remove->next->prev = head;
            head->next = remove->next;
            n--;
            return remove->data;
        }
    }

    int size() { return n; }
};

int main(){
    int N;
    cin>>N;
    string s="1+9";
    
    for(int i=0;i<N;i++){
        string s;
        cin>>s;
        int result=0;
        DStack<int> ds;
        for (int i = 0; i < s.size(); i++) {
            if ((int)s[i] >= 49&&(int)s[i] <=57) {
                int a = (int)s[i] - 48;
                ds.push(a);
            }
            else if (s[i] == '+') {
                int x = ds.pop();
                int y = ds.pop();
                ds.push(x + y);
            }
            else if (s[i] == '-') {
                int x = ds.pop();
                int y = ds.pop();
                ds.push(y - x);
            }
            else if(s[i]=='*') {
                int x = ds.pop();
                int y = ds.pop();
                ds.push(y * x);
            }
            else{continue;}
        }
        result=ds.pop();
        cout<<result<<'\n';
    }
    
    return 0;
}
