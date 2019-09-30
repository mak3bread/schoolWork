#include <iostream>
using namespace std;

template <typename T>
class Node {
public:
    T data;
    Node<T>* prev;
    Node<T>* next;
};

template <typename T>
class Dqueue {
private:
    typedef Node<T>* pNODE;
    typedef Node<T> NODE;
    pNODE head;
    pNODE tail;
    int n;
    int result;
    
public:
    Dqueue() {
        head = new NODE;
        tail = new NODE;
        head->next = tail;
        tail->prev = head;
        n = 0;
        result = 0;
    }
    
    ~Dqueue() {
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
    
    void pop_front() {
        if (empty()) { cout << "Empty" << '\n'; }
        else {
            n--;
            pNODE removal = head->next;
            removal->next->prev = head;
            head->next = removal->next;
            cout << removal->data << '\n';
            delete removal;
        }
    }
    
    int pop_deck() {
        if (empty()) { return -1; }
        else {
            n--;
            pNODE removal = head->next;
            removal->next->prev = head;
            head->next = removal->next;
            result= removal->data;
            delete removal;
            return result;
        }
    }
    
    void pop_back() {
        if (empty()) { return; }
        else {
            n--;
            pNODE removal = tail->prev;
            removal->prev->next = tail;
            tail->prev = removal->prev;
            delete removal;
        }
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
    
    void push_front(T data) {
        n++;
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
    
    pNODE front() { return head->next; }
    
    pNODE back() { return tail; }
    
    void print() {
        if (empty()) { return; }
        else {
            for (pNODE aNode = front(); aNode != back(); aNode = aNode->next) {
                cout << aNode->data;
                if (aNode != back()) { cout << " "; }
            }
        }
    }
    
    int top() {
        if (empty()) { return -1; }
        else {
            return head->next->data;
        }
    }
    
    int rear() {
        if (empty()) { return -1; }
        else { return tail->prev->data; }
    }
    
    int size() { return n; }
};

//1,2번
/*
 int main() {
 int N;
 cin >> N;
 Dqueue<int> dq;
 
 for (int i = 0; i < N; i++) {
 string s;
 cin >> s;
 
 if (s == "enqueue") {
 int a;
 cin >> a;
 if (a >= 1 && a <= 9) {
 dq.push_back(a);
 }
 else { continue; }
 }
 
 else if (s == "dequeue") {
 dq.pop_front();
 }
 
 else if (s == "size") {
 cout << dq.size() << '\n';
 }
 
 else if (s == "isEmpty") {
 cout << dq.empty() << '\n';
 }
 
 else if (s == "front") {
 if (dq.top() == -1) { cout << "Empty"<<'\n'; }
 else { cout << dq.top() << '\n'; }
 }
 
 else if (s == "rear") {
 if (dq.rear() == -1) { cout << "Empty" << '\n'; }
 else { cout << dq.rear() << '\n'; }
 }
 
 else { continue; }
 }
 
 return 0;
 }*/

//3번
/*
 int main() {
 
 int T;
 cin >> T;
 
 Dqueue<int> dq1;
 Dqueue<int> dq2;
 
 
 for (int i = 0; i < T; i++) {
 int n;
 cin >> n;
 
 
 for (int j = 0; j < n; j++) {
 int a;
 cin >> a;
 dq1.push_back(a);
 
 }
 
 for (int j = 0; j < n; j++) {
 int b;
 cin >> b;
 dq2.push_back(b);
 }
 
 int r1 = 0;
 int r2 = 0;
 
 for (int j = 0; j < n; j++) {
 if (dq1.top() > dq2.top()) {
 r1++;
 
 if (!dq1.empty() && !dq2.empty()) {
 dq1.pop_deck();
 dq2.pop_deck();
 }
 
 continue;
 }
 else if (dq1.top() < dq2.top()) {
 r2++;
 
 if (!dq1.empty() && !dq2.empty()) {
 dq1.pop_deck();
 dq2.pop_deck();
 }
 continue;
 }
 else if (dq1.top() == dq2.top()) {
 if (!dq1.empty() && !dq2.empty()) {
 dq1.pop_deck();
 dq2.pop_deck();
 }
 continue;
 }
 else { continue; }
 }
 
 if (r1 > r2) { cout << 1 << '\n'; }
 else if (r1 < r2) { cout << 2 << '\n'; }
 else if (r1 == r2) { cout << 0 << '\n'; }
 else { continue; }
 
 }
 return 0;
 }
 */

//4번
/*
 int main() {
 
 int T;
 cin >> T;
 
 Dqueue<int> dq1;
 Dqueue<int> dq2;
 
 
 for (int i = 0; i < T; i++) {
 int n;
 cin >> n;
 
 
 for (int j = 0; j < n; j++) {
 int a;
 cin >> a;
 dq1.push_back(a);
 
 }
 
 for (int j = 0; j < n; j++) {
 int b;
 cin >> b;
 dq2.push_back(b);
 }
 
 int r1 = 0;
 int r2 = 0;
 
 for (int j = 0; j < n; j++) {
 if (dq1.top() > dq2.top()) {
 r1++;
 int a = dq1.top() - dq2.top() - 1;
 if (!dq1.empty() && !dq2.empty()) {
 dq1.pop_deck();
 dq2.pop_deck();
 }
 int b = dq1.top() + a;
 if (!dq1.empty()) {
 dq1.pop_deck();
 dq1.push_front(b);
 }
 continue;
 }
 else if (dq1.top() < dq2.top()) {
 r2++;
 int a = dq2.top() - dq1.top()-1;
 
 if (!dq1.empty() && !dq2.empty()) {
 dq1.pop_deck();
 dq2.pop_deck();
 }
 int b = dq2.top() + a;
 if (!dq2.empty()) {
 dq2.pop_deck();
 dq2.push_front(b);
 }
 continue;
 }
 else if (dq1.top() == dq2.top()) {
 if (!dq1.empty() && !dq2.empty()) {
 dq1.pop_deck();
 dq2.pop_deck();
 }
 continue;
 }
 else { continue; }
 }
 
 if (r1 > r2) { cout << 1 << '\n'; }
 else if (r1 < r2) { cout << 2 << '\n'; }
 else if(r1==r2) { cout << 0 << '\n'; }
 else { continue; }
 
 }
 return 0;
 }
 */
