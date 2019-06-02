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
    int len;
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
    len = N;
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
    return id[p];
}

void UF::Union(int p, int q) {
    int pID = find(p);
    int qID = find(q);
    if (pID == qID) {
        return;
    }
    for (int i = 0; i < len; i++) {
        if (id[i] == pID) {
            id[i] = qID;
        }
    }
    N--;
}

int main() {
    string path = "../../../algs4-data/";
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
            cout << p << "-" << q << endl;
        }
        int num = uf.count();
        cout << num << " components" << endl;
    }
    else {
        cout << "no such file!" << endl;
    }
    return 0;
}