// 由于和算法3.5存在相同的hashcode()问题，不写模板类，这里的键和值的数据类型分别为char, int
#include<iostream>
#include<vector>

using namespace std;

class LinearProbingHashST{
private:
    int N;      // 键值对总数
    int M;
    vector<pair<string, int>*> vec;

    void resize(int cap);
    int hash(string str);
public:
    LinearProbingHashST(int len);
    ~LinearProbingHashST();

    void put(pair<string, int>*);
    int get(string str);
    void del(string str);
    void show();
    void delPointer();
};

LinearProbingHashST::LinearProbingHashST(int len) {
    N = 0;
    M = len;    
    vector<pair<string, int>*> temp(M, NULL);
    vec = temp;
}

LinearProbingHashST::~LinearProbingHashST() { }

void LinearProbingHashST::resize(int cap) {
    LinearProbingHashST t = LinearProbingHashST(cap);
    for (int i = 0; i < M; ++i) {
        if (vec[i]) t.put(vec[i]);
    }
    this->vec = t.vec;
    this->M = t.M;
}

int LinearProbingHashST::hash(string str) {
    int hash = 0;
    for (int i = 0; i < str.length(); ++i) {
        hash = (26 * hash + str[i]) % M;
    }
    return hash;
}

void LinearProbingHashST::put(pair<string, int>* p) {
    if (N >= M / 2)
        resize(M * 2);
    int i;
    for (i = hash(p->first); vec[i]; i = (i + 1) % M) {
        if (vec[i]->first == p->first) {
            vec[i]->second = p->second;
            return;
        }
    }
    vec[i] = p;
    N++;
}

int LinearProbingHashST::get(string str) {
    for (int i = hash(str); vec[i]; i = (i + 1) % M) {
        if (vec[i]->first == str) return vec[i]->second;
    }
    return INT_MIN;
}

void LinearProbingHashST::del(string str) {
    if (get(str) == INT_MIN) return;
    int i = hash(str);
    while (vec[i]->first != str) i = (i + 1) % M;
    vec[i] = NULL;
    i = (i + 1) %  M;
    while (vec[i]) {
        pair<string, int>* temp = new pair<string, int>(vec[i]->first, vec[i]->second);
        vec[i] = NULL;
        N--;
        put(temp);
        i = (i + 1) % M;
    }
    N--;
    if (N > 0 && N == M / 8) resize(M / 2);
}

void LinearProbingHashST::show() {
    for (int i = 0; i < vec.size(); ++i) {
        if (!vec[i]) cout << "x ";
        else cout << "<" << vec[i]->first << ", " << vec[i]->second << "> ";
    }
    cout << endl;
}

void LinearProbingHashST::delPointer() {
    for (int i = 0; i < vec.size(); ++i)
        delete vec[i];
}

int main() {
    LinearProbingHashST st = LinearProbingHashST(16);
    vector<string> strVec = {"S", "E", "A", "R", "C", "H", "E", "X", "A", "M", "P", "L", "E"};
    pair<string, int>* temp;
    for (int i  = 0; i < strVec.size(); ++i) {
        temp = new pair<string, int>(strVec[i], i);
        st.put(temp);
    }
    st.show();
    cout << st.get("A") << endl;
    cout << st.get("M") << endl;
    st.del("A");
    st.show();
    st.del("X");
    st.del("M");
    st.del("L");
    st.del("E");
    st.del("H");
    st.show();
    // 删除指针
    st.delPointer();
    return 0;
}
