/*泛型定容栈*/
#include<iostream>
#include<cstring>
#include<string>
#include<fstream>

using namespace std;

template<class T>
class ResizingArrayStack {
private:
    T* a;
    int N;
public:
    ResizingArrayStack(int cap);
    ~ResizingArrayStack();

    bool isEmpty();
    int size();
    void push(T item);
    T pop();
};

template<class T>
ResizingArrayStack<T>::ResizingArrayStack(int cap) {
    N = 0;
    a = new T[cap];
}

template<class T>
ResizingArrayStack<T>::~ResizingArrayStack() {
    if (a) {
        delete[] a;
    }
}

template<class T>
bool ResizingArrayStack<T>::isEmpty() {
    return N == 0;
}

template<class T>
int ResizingArrayStack<T>::size() {
    return N;
}

template<class T>
void ResizingArrayStack<T>::push(T item) {
    a[N++] = item;
}

template<class T>
T ResizingArrayStack<T>::pop() {
    return a[--N];
}

int main() {
    ResizingArrayStack<string> stack = ResizingArrayStack<string>(100);
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
                stack.push(item);
            }
            else if (!stack.isEmpty()) {
                cout << stack.pop() << " ";
            } 
        }
        cout << endl;
    }  
    else {  
        cout << "no such file!" << endl;
    } 
    return 0;
}