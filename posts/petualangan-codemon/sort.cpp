#include <algorithm>
#include <iostream>
using namespace std;
typedef long long int lli;

struct codemon {
    int idx, L, P, S;
    lli B;
};

const int MAXN = 50000;
const int MAXP = 50000;

int N, M, mxP = 0;
lli ST[4 * MAXP];
codemon C[MAXN];
lli ans[MAXN];

lli _query(int node, int l, int r, const int& ql, const int& qr){
    if(ql > qr || r < ql || qr < l) return 0;

    if(ql <= l && r <= qr) return ST[node];

    int m = (l + r)/2;
    return  _query(2 * node + 1, l, m, ql, qr) |
            _query(2 * node + 2, m + 1, r, ql, qr);
}

lli query(const int& p){
    return _query(0, 0, mxP, p, mxP);
}

void _update(int node, int l, int r, const int& idx, const lli& val){
    if(l == r){
        ST[node] |= val;
        return;
    }

    int m = (l + r)/2;
    if(idx <= m)
        _update(2 * node + 1, l, m, idx, val);
    else
        _update(2 * node + 2, m + 1, r, idx, val);
    ST[node] = ST[2 * node + 1] | ST[2 * node + 2];
}

void update(const int& p, const lli& b){
    _update(0, 0, mxP, p, b);
}

int main(){
    cin.tie(0)->sync_with_stdio(0);

    cin >> N >> M;
    for(int i = 0; i < N; i++){
        codemon& c = C[i];
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
    }

    sort(C, C + N, [](const codemon& x, const codemon& y){
        return x.L > y.L || (x.L == y.L && x.P < y.P);
    });
    for(const auto& c : C){
        ans[c.idx] = query(c.P + 1) | c.B;
        update(c.P, c.B);
    }

    for(int i = 0; i < N; i++)
        cout << __builtin_popcountll(ans[i]) << '\n';
    return 0;
}