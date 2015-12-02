#include <bits/stdc++.h>
#include "SmartPointer.hpp"

using namespace std;

int main() {
    SmartPointer<vector<int>> p(new vector<int>);
    for(int i = 0; i < 10; ++i) {
        p->push_back(10);
    }
    SmartPointer<vector<int>> q = p;
    cout << (*q).size();
}
