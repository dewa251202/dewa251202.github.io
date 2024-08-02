#include <iostream>
#include <vector>
#include <map>
using namespace std;
typedef long long int lli;

struct codemon {
    int idx, L, P, S;
    lli B;
};

const int MAXN = 50000;
const int MAXL = 50000;
const int MAXP = 50000;

int N, M;
lli ans[MAXN];
lli ST[4 * MAXP];
map <int, vector<codemon>, greater<int> > L;

void update(int node, int l, int r, const int& idx, const lli& val){
    if(l == r){
        ST[node] |= val;
        return;
    }

    int m = (l + r)/2;
    if(idx <= m)
        update(2 * node + 1, l, m, idx, val);
    else
        update(2 * node + 2, m + 1, r, idx, val);
    ST[node] = ST[2 * node + 1] | ST[2 * node + 2];
}

lli query(int node, int l, int r, const int& ql, const int& qr){
    if(ql > qr || r < ql || qr < l) return 0;

    if(ql <= l && r <= qr) return ST[node];

    int m = (l + r)/2;
    return  query(2 * node + 1, l, m, ql, qr) |
            query(2 * node + 2, m + 1, r, ql, qr);
}

int main(){
    cin.tie(0)->sync_with_stdio(0);

    cin >> N >> M;

    int mxP = 0;
    for(int i = 0; i < N; i++){
        codemon c;
        cin >> c.L >> c.P >> c.S;
        c.L--, c.P--;
        c.B = 0;
        c.idx = i;
        
        while(c.S--){
            int Bi;
            cin >> Bi;
            Bi--;
            c.B |= 1LL << Bi;
        }

        mxP = max(mxP, c.P);
        L[c.L].push_back(c);
    }

    for(const auto& p : L){
        const int& Li = p.first;
        const vector<codemon>& C = p.second;
        for(const codemon& c : C)
            ans[c.idx] = query(0, 0, mxP, c.P + 1, mxP) | c.B;

        for(const codemon& c : C)
            update(0, 0, mxP, c.P, c.B);
    }

    for(int i = 0; i < N; i++)
        cout << __builtin_popcountll(ans[i]) << '\n';
    return 0;
}