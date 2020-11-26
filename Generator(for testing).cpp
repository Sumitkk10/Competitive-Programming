// This file is used to generate random testcase.
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int MOD = 1e9 + 7;
const int N = 1e6 + 5;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int genNum(int l, int r) {
    return l + rand() % (r - l + 1);
}

vector<int> genArr(int n, int l, int r) {
    vector<int> res;
    for (int i = 0; i < n; i++) {
        res.push_back(genNum(l, r));
    }
    return res;
}

vector<int> genArrNoRep(int n, int l, int r) {
    vector<int> res;
    map<int, int> done;
    for (int i = 0; i < n; i++) {
        int cur = genNum(l, r);
        while (done[cur]) {
            cur = genNum(l, r);
        }
        done[cur] = 1;
        res.push_back(cur);
    }
    return res;
}

string genStrAlpha(int n, char ccase) {
    string res = "";
    for (int i = 0; i < n; i++) {
        res.push_back(ccase + rand() % 26);
    }
    return res;
}

string genStrBinary(int n, char one, char two) {
    string res = "";
    for (int i = 0; i < n; i++) {
        if (rand() % 2 == 0)
            res.push_back(one);
        else
            res.push_back(two);
    }
    return res;
}

string genStrTernary(int n, char one, char two, char three) {
    string res = "";
    for (int i = 0; i < n; i++) {
        if (rand() % 3 == 0)
            res.push_back(one);
        else if (rand() % 3 == 1)
            res.push_back(two);
        else
            res.push_back(three);
    }
    return res;
}

string genStrQuad(int n, char one, char two, char three, char four) {
    string res = "";
    for (int i = 0; i < n; i++) {
        if (rand() % 4 == 0)
            res.push_back(one);
        else if (rand() % 4 == 1)
            res.push_back(two);
        else if (rand() % 4 == 2)
            res.push_back(three);
        else
            res.push_back(four);
    }
    return res;
}
void genGraph(int n, int m) {
    m = min(m, (n * (n - 1)) / 2);
    cout << n << ' ' << m << endl;
    map<pair<int, int>, bool> done;
    vector<pair<int, int>> edges;
    for (int i = 0; i < m; i++) {
        while (true) {
            int x = genNum(1, n);
            int y = genNum(1, n);
            if (x == y)continue;
            if (!done[ {x, y}] and !done[ {y, x}]) {
                edges.push_back({x, y});
                done[ {x, y}] = 1;
                done[ {y, x}] = 1;
                break;
            }
        }
    }
    for (auto x : edges)
        cout << x.first << ' ' << x.second << endl;
    return ;
}
vector<int> genPerm(int n) {
    vector<int> res;
    for (int i = 0; i < n; i++)
        res.push_back(i + 1);
    random_shuffle(res.begin(), res.end());
    return res;
}
void genTree(int n) {
    assert(n >= 0);
    int permutation[n + 14];
    vector<pair<int, int>> res(n ? n - 1 : 0);
    iota(permutation, permutation + 1 + n, 0);
    shuffle(permutation + 1, permutation + 1 + n, rng);
    for (int i = 2; i <= n; ++i) {
        int u = i, v = genNum(1, i - 1);
        u = permutation[u], v = permutation[v];
        res[i - 2] = minmax(u, v);
    }
    shuffle(res.begin(), res.end(), rng);
    cout << n << endl;
    for (auto x : res)
        cout << x.first << ' ' << x.second << endl;
    return ;
}
string genKAlphaString(int n, int k) {
    string res = "";
    for (int i = 0; i < n; i++)
        res.push_back('a' + rand() % k);
    return res;
}

int32_t main() {
    srand(chrono::steady_clock::now().time_since_epoch().count());
    // for testcase;
    cout << 1 << endl;
    int n = genNum(3, 10);
    vector<int> temp = genArr(n, 1, 10);
    cout << n << endl;
    for (auto t : temp )
        cout << t << " ";
    cout << endl;
    return 0;
}
