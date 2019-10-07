#include <iostream>
 
using namespace std;
 
template <typename T>
class Node {
public:
    Node<T>* next;
    Node<T>* prev;
    T data;
};
 
template <typename T>
class Deq {
private:
    typedef Node<T> NODE;
    typedef Node<T>* pNODE;
    pNODE head;
    pNODE tail;
    int n;
public:
    Deq() {
        head = new NODE;
        tail = new NODE;
        head->next = tail;
        tail->prev = head;
        n = 0;
    }
    ~Deq() { while (!empty())pop(); }
 
    pNODE createNew(T data) {
        pNODE aNode = new NODE;
        aNode->next = NULL;
        aNode->prev = NULL;
        aNode->data = data;
        return aNode;
    }
 
    bool empty() { return (head->next == tail); }
 
    void pop() {
        if (empty()) { return; }
        else {
            --n;
            pNODE removal = head->next;
            removal->next->prev = head;
            head->next = removal->next;
            delete removal;
        }
    }
 
    void push_front(T data) {
        ++n;
        pNODE aNode = createNew(data);
        aNode->next = head->next;
        aNode->prev = head;
        head->next->prev = aNode;
        head->next = aNode;
    }
 
    void push_back(T data) {
        n++;
        pNODE aNode = createNew(data);
        aNode->next = tail;
        aNode->prev = tail->prev;
        tail->prev->next = aNode;
        tail->prev = aNode;
    }
 
    void pop_front() {
        if (empty()) { cout << -1 << '\n'; }
        else {
            n--;
            pNODE removal = head->next;
            removal->next->prev = head;
            head->next = removal->next;
            cout << removal->data << '\n';
            delete removal;
        }
    }
 
    void pop_back() {
        if (empty()) { cout << -1 << '\n'; }
        else {
            n--;
            pNODE removal = tail->prev;
            removal->prev->next = tail;
            tail->prev = removal->prev;
            cout << removal->data << '\n';
            delete removal;
        }
    }
 
    void front() {
        if (empty()) { cout << -1 << '\n'; }
        else {
            cout << head->next->data << '\n';
        }
    }
    
    int top() { return head->next->data; }
 
    int size() { return n; }
 
    pNODE ptop() { return head->next; }
};
 
//1
/*
int main() {
 
    int N;
    cin >> N;
    Deq<int> dq;
 
    for (int i = 0; i < N; i++) {
        string s;
        cin >> s;
 
        if (s == "empty") {
            cout << dq.empty() << '\n';
        }
 
        else if (s == "front") {
            dq.front();
        }
 
        else if (s=="removeFront") {
            dq.pop_front();
        }
 
        else if (s == "addFront") {
            int a;
            cin >> a;
            dq.push_front(a);
        }
        else { continue; }
 
    }
 
    
    return 0;
}*/
 
//2
/*
int main() {
    int T;
    cin >> T;
 
    Deq<int> dq1;
    Deq<int> dq2;
 
    for (int i = 0; i < T; i++) {
        int N;
        cin >> N;
        for (int j = 0; j < N; j++) {
            int a;
            cin >> a;
            dq1.push_back(a);
        }
 
        for (int j = 0; j < N; j++) {
            int b;
            cin >> b;
            dq2.push_back(b);
        }
    
        int p1 = 0;
        int p2 = 0;
 
        for (int j = 0; j < N; j++) {
            if (dq1.top() > dq2.top()) {
                p1++;
                int a = dq1.top();
                int b = dq2.top();
                if (!dq1.empty()&&!dq2.empty()) {
                    dq1.pop();
                    dq2.pop();
                }
                int result = a - b - 1;
                if (!dq1.empty()) {
                    result += dq1.top();
                    dq1.pop();
                    dq1.push_front(result);
                }
            }
 
            else if (dq1.top() < dq2.top()) {
                p2++;
                int a = dq1.top();
                int b = dq2.top();
                if (!dq1.empty() && !dq2.empty()) {
                    dq1.pop();
                    dq2.pop();
                }
                int result = b-a - 1;
                if (!dq2.empty()) {
                    result += dq2.top();
                    dq2.pop();
                    dq2.push_front(result);
                }
            }
 
            else if (dq1.top() == dq2.top()) {
                if (!dq1.empty() && !dq2.empty()) {
                    dq1.pop();
                    dq2.pop();
                }
            }
            else { continue; }
        
        }
        if (p1 > p2) { cout << 1 << '\n'; }
        else if (p1 < p2) { cout << 2 << '\n'; }
        else if (p1 == p2) { cout << 0 << '\n'; }
        else { continue; }
 
    }
 
    return 0;
}*/
 
//3
 //dq.size() >=3 이 조건 안줘서 에러 뜸..
int main() {
 
    int N;
    cin >> N;
 
    for (int i = 0; i < N; i++) {
        Deq<char> dq;
        string s;
        cin >> s;
        bool life = true;
        
        
        for (int j = 0; j < s.size(); j++) {
            if (s[j] == 'A') {
                dq.push_front('A');
            }
            else if (s[j] == 'B') {
                dq.push_front('B');
            }
 
            else if (s[j] == 'C') {
                dq.push_front('C');
            }
 
            else if (s[j] == 'D') {
                dq.push_front('D');
            }
           
                while (true) {
                    
                    if (dq.size() >= 3 && !dq.empty() && dq.ptop()->data == dq.ptop()->next->data && dq.ptop()->next->data == dq.ptop()->next->next->data) {
                        
                        dq.pop();
                        dq.pop();
                        dq.pop();
                    }
                    else { break; }
                }
 
            if (dq.size() >= 10) {
                life = false;
                break;
            }
            
        }
 
        if (life == true) { cout << 1 << '\n'; }
        else if(life==false){ cout << 0 << '\n'; }
    }
    return 0;
}
