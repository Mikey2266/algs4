#include<iostream>
#include<vector>
#include<fstream>

using namespace std;

class Shell {
private:
    void exch(vector<string>& a, int i, int j);
public:
    Shell();
    ~Shell();

    void show(vector<string>& a);
    void sort(vector<string>& a);
    bool isSorted(vector<string>& a);
};

Shell::Shell() {}
Shell::~Shell() {}

void Shell::exch(vector<string>& a, int i, int j) {
    string temp = a[i];
    a[i] = a[j];
    a[j] = temp;
}

void Shell::show(vector<string>& a) {
    if (a.size() > 0) {
        cout << a[0];
        for (int i = 1; i < a.size(); i++) {
            cout << " " << a[i];
        }
        cout << endl;
    }
}

bool Shell::isSorted(vector<string>& a) {
    for (int i = 1; i < a.size(); i++) {
        if (a[i - 1] > a[i]) {
            return false;
        }
    }
    return true;
}

void Shell::sort(vector<string>& a) {
    int N = a.size();
    int h = 1;
    while (h < N /3) {
        h = h * 3 + 1;
    }
    while (h >= 1) {
        for (int i = h; i < N; i++) {
            for (int j = i; j >= h && a[j] < a[j - h];j -= h) {
                exch(a, j, j - h);
            }
        }
        h = h / 3;
    }
}

int main() {
    string path = "C:\\Users\\60187\\Desktop\\ItA\\algs4\\algs4-data\\";
    string filename = "tiny.txt";
    ifstream in(path + filename);
    string item;
    if (in.is_open()) {
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
            Shell sort = Shell();
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
