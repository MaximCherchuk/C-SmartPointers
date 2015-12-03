#include <bits/stdc++.h>
#include "SmartPointer.hpp"

using namespace std;

int main() {
    SmartPointer<vector<int>> p(new vector<int>[3], [] (vector<int> *v) {
        delete [] v;
    });
    SmartPointer<vector<int>> q = p;
    q->push_back(10);
    cout << p->size();
}
