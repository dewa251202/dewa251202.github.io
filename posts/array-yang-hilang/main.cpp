#include <iostream>
using namespace std;
typedef long long int lli;

const lli MOD = 1E9 + 7;

lli T, N, Ai, ans;
lli cnt[100001];
lli F[2000001];
lli invers[2000001];
lli iF[2000001];

// Binomial coefficient
// n!/(r! * (n - r)!) = (1/r! * 1/(n - r)! * n!)
lli C(lli n, lli r){
    return ((iF[r] * iF[n - r]) % MOD * F[n] % MOD) % MOD;
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    // Precompute factorials (F[]) and the modular multiplicative inverse (iF[])
    F[0] = invers[0] = iF[0] = 1;
    for(lli i = 1; i <= 2000000; i++){
        F[i] = (i * F[i - 1]) % MOD;
        // https://cp-algorithms.com/algebra/module-inverse.html#finding-the-modular-inverse-for-prime-moduli-using-euclidean-division
        invers[i] = (i == 1 ? 1 : (MOD - ((MOD/i) * invers[MOD % i]) % MOD));
        iF[i] = (invers[i] * iF[i - 1]) % MOD;
    }

    cin >> T;
    while(T--){
        for(int i = 0; i <= 100000; i++)
            cnt[i] = 0;

        cin >> N;
        for(int i = 0; i < N; i++){
            cin >> Ai;
            for(int j = 2; j * j <= Ai; j++){
                while(Ai % j == 0){
                    cnt[j]++;
                    Ai /= j;
                }
            }
            if(Ai != 1) cnt[Ai]++;
        }

        ans = 1;
        for(lli i = 0; i <= 100000; i++)
            if(cnt[i])
                ans = (ans * C(cnt[i] + N - 1, cnt[i])) % MOD;

        cout << ans << '\n';
    }
    return 0;
}