/*union-find算法*/
#include<iostream>
#include<string>
#include<cstring>
#include<fstream>

using namespace std;

class UF {
private:
    int* id;
    int N;
public:
    UF(int N);
    ~UF();

    void Union(int p, int q);
    int find(int p);
    bool connected(int p, int q);
    int count();
};

UF::UF(int N) {
    this->N = N;
    id = new int[N];
    for (int i =0; i < N; ++i) {
        id[i] = i;
    }
}

UF::~UF() {
    if(id) {
        delete[] id;
    }
}

int UF::count() {
    return this->N;
}

bool UF::connected(int p, int q) {
    return find(p) == find(q);
}

int UF::find(int p) {
    while (p != id[p]) {
        p = id[p];
    }
    return p;
}

void UF::Union(int p, int q) {
    int pRoot = find(p);
    int qRoot = find(q);
    if (pRoot == qRoot) {
        return;
    }
    id[qRoot] = pRoot;
    N--;
}

int main() {
    string path = "C:\\Users\\60187\\Desktop\\ItA\\algs4\\algs4-data\\";
    string filename = "tinyUF.txt";
    ifstream in(path + filename);
    string item;
    if (in.is_open()) {
        getline(in, item);
        UF uf = UF(atoi(item.c_str()));
        while (getline(in, item)) {
            string pStr = item.substr(0, item.find(" "));
            string qStr = item.substr(item.find(" ") + 1, item.length());
            int p = atoi(pStr.c_str());
            int q = atoi(qStr.c_str());
            if (uf.connected(p, q)) {
                continue;
            }
            uf.Union(p, q);
            // cout << p << "-" << q << endl;
        }
        int num = uf.count();
        cout << num << " components" << endl;
    }
    else {
        cout << "no such file!" << endl;
    }
    return 0;
}