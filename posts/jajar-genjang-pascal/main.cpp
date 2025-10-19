#include <iostream>
using namespace std;
typedef long long int lli;

const int MOD = 1E9 + 9;
const int MAXX = 500000;

int T, N, M, L, R;
lli Fact[MAXX + 1];

int Pow(lli x, int y){
    lli ret = 1;
    while(y){
        if(y & 1) (ret *= x) %= MOD;
        (x *= x) %= MOD;
        y >>= 1;
    }
    return ret;
}

int mod_inv(int x){
    return Pow(x, MOD - 2);
}

int C(int n, int k){
    if(n < 0 || k < 0 || n - k < 0) return 0;
    int denom = Fact[k] * Fact[n - k] % MOD;
    return Fact[n] * mod_inv(denom) % MOD;
}

lli F(int X, int Y){
    return (C(Y + X, X) - 1 + MOD) % MOD;
}

int D(int N, int M, int L, int R){
    int a = N - M + 1;
    int b = M;
    int c = a + L - 1;
    int d = b + R - 1;

    lli ret = F(c, d) - F(a - 1, d) - F(c, b - 1) + F(a - 1, b - 1);
    ret %= MOD;
    if(ret < 0) ret += MOD;
    return ret;
}

int main(){
    Fact[0] = 1;
    for(int i = 1; i <= MAXX; i++)
        Fact[i] = (Fact[i - 1] * i) % MOD;

    cin >> T;
    while(T--){
        cin >> N >> M >> L >> R;
        cout << D(N, M, L, R) << '\n';
    }
    return 0;
}