/*泛型背包, 未实现iterator函数*/
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
    int N;
public:
    Stack();
    ~Stack();

    bool isEmpty();
    int size();
    void add(T item);
};

template<class T>
Stack<T>::Stack() {
    N = 0;
    first = NULL;
}

template<class T>
Stack<T>::~Stack() {
    delete first;
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
void Stack<T>::add(T item) {
    Node<T>* oldFirst = first;
    first = new Node<T>(item);
    first->next = oldFirst;
    N++;
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
                stack.add(item);
            }
        }
        cout << "adding is over." << endl;
    }  
    else {  
        cout << "no such file!" << endl;
    } 
    return 0;
}