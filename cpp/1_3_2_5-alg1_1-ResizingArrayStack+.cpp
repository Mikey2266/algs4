/*泛型动态栈, 未实现用foreach顺序迭代访问功能*/
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
    int len;
    void resize(int max);
public:
    ResizingArrayStack();
    ~ResizingArrayStack();

    bool isEmpty();
    int size();
    void push(T item);
    T pop();
    int getLen();
};

template<class T>
ResizingArrayStack<T>::ResizingArrayStack() {
    N = 0;
    len = 1;
    a = new T[1];
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
void ResizingArrayStack<T>::resize(int max) {
    T* temp = new T[N];
    for (int i = 0; i < N; i++) {
        temp[i] = a[i];
    }
    delete[] a;
    a = new T[max];
    len = max;
     for (int i = 0; i < N; i++) {
        a[i] = temp[i];
    }
    delete[] temp;
}

template<class T>
void ResizingArrayStack<T>::push(T item) {
    if (N == len) {
        resize(2*len);
    }
    a[N++] = item;
}

template<class T>
T ResizingArrayStack<T>::pop() {
    T item = a[--N];
    if (N > 0 && N == len/4) {
        resize(len/2);
    }
    return item;
}

template<class T>
int ResizingArrayStack<T>::getLen() {
    return len;
}

int main() {
    ResizingArrayStack<string> stack = ResizingArrayStack<string>();
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
    if (in.is_open()) {
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
        cout <<"no such file" << endl;  
    } 
    return 0;
}