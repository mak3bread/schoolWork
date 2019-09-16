/*#include <iostream>
 using namespace std;
 
 template <typename T>
 class Node {
 private:
 public:
 Node<T>* next;
 Node<T>* prev;
 T data;
 };
 
 template <typename T>
 class SList {
 private:
 typedef Node<T> NODE;
 typedef Node<T>* pNODE;
 pNODE head;
 pNODE tail;
 int rdata = 0;
 
 public:
 SList() {
 head = new NODE;
 tail = new NODE;
 head->next = tail;
 tail->prev = head;
 }
 
 pNODE createNode(T data) {
 pNODE newNode = new NODE;
 newNode->next = NULL;
 newNode->prev = NULL;
 newNode->data = data;
 
 return newNode;
 }
 
 void addFront(T data) {
 pNODE aNode = createNode(data);
 if (head->next == tail) {
 aNode->next = tail;
 aNode->prev = head;
 head->next = aNode;
 tail->prev = aNode;
 }
 
 else {
 aNode->prev = head;
 aNode->next = head->next;
 aNode->next = head->next;
 head->next = aNode;
 }
 }
 
 T removeFront() {
 pNODE rNode = head->next;
 if (head->next == tail) { return -1; }
 else {
 rdata = rNode->data;
 rNode->next->prev = head;
 head->next = rNode->next;
 delete rNode;
 return rdata;
 }
 }
 
 pNODE front() {
 
 return head->next;
 }
 
 pNODE Back() {
 
 return tail;
 }
 
 int empty() {
 if (head->next == tail) { return 1; }
 else { return 0; }
 }
 
 void print() {
 if (head->next == tail) {
 cout << -1 << '\n';
 }
 else {
 for (pNODE aNode = head->next; aNode != Back(); aNode = aNode->next) {
 cout << aNode->data<<" ";
 }
 cout << '\n';
 }
 }
 
 void addBack(T data) {
 pNODE bNode = createNode(data);
 bNode->next = tail;
 bNode->prev = tail->prev;
 tail->prev->next = bNode;
 tail->prev = bNode;
 }
 
 
 };
 
 int main() {
 int N;
 cin >> N;
 
 SList<int> sl;
 
 for (int i = 0; i < N; i++) {
 string s;
 cin >> s;
 
 if (s == "empty") {
 cout << sl.empty() << '\n';
 }
 else if (s == "front") {
 if (sl.front()== sl.Back()) {
 cout << -1 << '\n';
 }
 else {
 cout << sl.front()->data << '\n';
 }
 }
 else if (s == "removeFront") {
 cout << sl.removeFront() << '\n';
 }
 else if (s == "addFront") {
 int d;
 cin >> d;
 sl.addFront(d);
 }
 else if (s == "showList") {
 sl.print();
 }
 else if (s == "addBack") {
 int a;
 cin >> a;
 sl.addBack(a);
 }
 else { continue; }
 }
 
 return 0;
 }*/

#include <iostream>
using namespace std;

template <typename T>
class Node {
private:
public:
    Node<T>* next;
    Node<T>* prev;
    T data;
};

template <typename T>
class SList {
private:
    typedef Node<T> NODE;
    typedef Node<T>* pNODE;
    pNODE head;
    pNODE tail;
    int rdata = 0;
    
public:
    SList() {
        head = new NODE;
        tail = new NODE;
        head->next = tail;
        tail->prev = head;
        tail->next = head;
    }
    ~SList() {
        while (!empty()) { removeFront(); }
    }
    
    pNODE createNode(T data) {
        pNODE newNode = new NODE;
        newNode->next = NULL;
        newNode->prev = NULL;
        newNode->data = data;
        
        return newNode;
    }
    
    void addFront(T data) {
        pNODE aNode = createNode(data);
        if (head->next == tail) {
            aNode->next = tail;
            aNode->prev = head;
            head->next = aNode;
            tail->prev = aNode;
        }
        
        else {
            aNode->prev = head;
            aNode->next = head->next;
            aNode->next = head->next;
            head->next = aNode;
        }
    }
    
    T removeFront() {
        pNODE rNode = head->next;
        if (head->next == tail) { return -1; }
        else {
            rdata = rNode->data;
            rNode->next->prev = head;
            head->next = rNode->next;
            delete rNode;
            return rdata;
        }
    }
    
    pNODE front() {
        
        return head->next;
    }
    
    pNODE Back() {
        
        return tail;
    }
    
    int empty() {
        if (head->next == tail) { return 1; }
        else { return 0; }
    }
    
    void print() {
        if (head->next == tail) {
            cout << -1 << '\n';
        }
        else {
            for (pNODE aNode = head->next; aNode != Back(); aNode = aNode->next) {
                cout << aNode->data << " ";
            }
            cout << '\n';
        }
    }
    
    void remove(pNODE r) {
        if (head->next == tail) {
            return;
        }
        else {
            r->next->prev = r->prev;
            r->prev->next = r->next;
            
        }
    }
    
    void addBack(T data) {
        pNODE bNode = createNode(data);
        bNode->next = tail;
        bNode->prev = tail->prev;
        tail->prev->next = bNode;
        tail->prev = bNode;
    }
    
    
};

int main() {
    
    int N;
    cin >> N;
    
    
    
    
    
    
    for (int i = 0; i < N; i++) {
        
        SList<int> sl;
        for (int j = 0; j < 10; j++) {
            int a;
            cin >> a;
            sl.addBack(a);
        }
        
        for (int k = 0; k < 3; k++) {
            
            
            
            string s;
            cin >> s;
            Node<int>* cursor = sl.front();
            
            if (s == "Delete") {
                int b;
                cin >> b;
                
                if (b == 0) {
                    
                    sl.remove(cursor);
                }
                else {
                    for (int i = 0; i < b; i++) {
                        if (cursor->next == sl.Back()) {
                            cursor = sl.front();
                        }
                        else {
                            cursor = cursor->next;
                        }
                    }
                    sl.remove(cursor);
                }
            }
            else {
                continue;
            }
        }
        
        sl.print();
        sl.~SList();
        
    }
    
    return 0;
}
