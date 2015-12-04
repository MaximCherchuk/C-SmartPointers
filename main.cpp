#include <bits/stdc++.h>
#include "smart_ptr.hpp"

using namespace std;

int main() {
    htop::smart_ptr<vector<int>> p(new vector<int>[3], [] (vector<int> *v) {
        delete [] v;
    });
    htop::smart_ptr<vector<int>> q = p;
    q[0].push_back(10);
    q[1].push_back(10);
    q[2].push_back(10);
    int ans = 0;
    for(int i = 0; i < 3; ++i) {
        ans += p[i].size();
    }
    cout << ans << ' ';
    cout << p->size();
}