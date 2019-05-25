/*泛型先进先出队列, 未实现iterator函数*/
#include<iostream>
#include<cstring>
#include<string>
#include<fstream>

using namespace std;

/*节点结构体*/
template<class T>
struct Node {
    T item;
    Node<T>* next;
    Node(T x) : item(x), next(NULL) {}
};

template<class T>
class Stack {
private:
    Node<T>* first;
    Node<T>* last;
    int N;
public:
    Stack();
    ~Stack();

    bool isEmpty();
    int size();
    void enqueue(T item);
    T dequeue();
};

template<class T>
Stack<T>::Stack() {
    N = 0;
    first = NULL;
    last = NULL;
}

template<class T>
Stack<T>::~Stack() {
    delete first;
    delete last;
}

template<class T>
bool Stack<T>::isEmpty() {
    return first == NULL;
}

template<class T>
int Stack<T>::size() {
    return N;
}

template<class T>
void Stack<T>::enqueue(T item) {
    Node<T>* oldLast = last;
    last = new Node<T>(item);
    if (isEmpty()) {
        first = last;
    }
    else {
        oldLast->next = last;
    }
    N++;
}

template<class T>
T Stack<T>::dequeue() {
    T item = first->item;
    first = first->next;
    if (isEmpty()) {
        last = NULL;
    }
    N--;
    return item;
}

int main() {
    Stack<string> stack = Stack<string>();
    // 手动输入测试
    // string item;
    // while(getline(cin, item)) {
    //     if (item != "-") {
    //         stack.push(atoi(item.c_str()));
    //     }
    //     else if (!stack.isEmpty()) {
    //         cout << stack.pop() << endl;
    //     }
    //     else {
    //         cout << "Stack is empty." << endl;
    //     }
    // }
    
    // 文件输入测试
    string path = "C:\\Users\\60187\\Desktop\\ItA\\algs4\\algs4-data\\";
    string filename = "tobe.txt";
    ifstream in(path + filename);  
    string item;
    if (in) {  
        while (getline(in, item)) {   
            if (item != "-") {
                // stack.push(atoi(item.c_str()));
                stack.enqueue(item);
            }
            else if (!stack.isEmpty()) {
                cout << stack.dequeue() << " ";
            } 
        }
        cout << endl;
    }  
    else {  
        cout << "no such file!" << endl;
    } 
    return 0;
}