#include<iostream>
#include<vector>
#include<fstream>

using namespace std;

class Insertion {
private:
    void exch(vector<string>& a, int i, int j);
public:
    Insertion();
    ~Insertion();

    void show(vector<string>& a);
    void sort(vector<string>& a);
    bool isSorted(vector<string>& a);
};

Insertion::Insertion() {}
Insertion::~Insertion() {}

void Insertion::exch(vector<string>& a, int i, int j) {
    string temp = a[i];
    a[i] = a[j];
    a[j] = temp;
}

void Insertion::show(vector<string>& a) {
    if (a.size() > 0) {
        cout << a[0];
        for (int i = 1; i < a.size(); i++) {
            cout << " " << a[i];
        }
        cout << endl;
    }
}

bool Insertion::isSorted(vector<string>& a) {
    for (int i = 1; i < a.size(); i++) {
        if (a[i - 1] > a[i]) {
            return false;
        }
    }
    return true;
}

void Insertion::sort(vector<string>& a) {
    int N = a.size();
    for (int i = 1; i < N; i++) {
        for (int j = i; j > 0 && a[j] < a[j -1]; j--) {
            exch(a, j, j - 1);
        }
    }
}

int main() {
    string path = "C:\\Users\\60187\\Desktop\\ItA\\algs4\\algs4-data\\";
    string filename = "tiny.txt";
    ifstream in(path + filename);
    string item;
    if (in) {
        while (getline(in, item)) {
            vector<string> vec;
            int head = 0;
            while (!item.empty()) {
                vec.push_back(item.substr(head, item.find(" ")));
                if (item.find(" ") < item.length()) {
                    item = item.substr(item.find(" ") + 1, item.length());
                }
                else {
                    item.clear();
                }
            }
            Insertion sort = Insertion();
            sort.show(vec);
            sort.sort(vec);
            if (!sort.isSorted(vec)) {
                cout << "sort error" << endl;
            }
            sort.show(vec);
        }
    }
    else {
        cout << "no such file!" << endl;
    }
    return 0;
}
