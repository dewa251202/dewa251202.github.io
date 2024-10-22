#include <iostream>
using namespace std;
typedef long long int lli;

const int MOD = 1E9 + 7;
const int MAXN = 1000;

int dp[6][MAXN + 1];

int f(int k, int n){
    if(n == 0) return 0;
    if(n == 1) return 1;

    int& ret = dp[k][n];
    if(ret != -1) return ret;
    
    if(k == 1)
        ret = ((lli)f(3, n - 1) + f(2, n - 2)) % MOD;
    if(k == 2)
        ret = ((lli)f(4, n - 1) + f(1, n - 2) + f(3, n - 2)) % MOD;
    if(k == 3)
        ret = ((lli)f(1, n - 1) + f(5, n - 1) + f(2, n - 2) + f(4, n - 2)) % MOD;
    if(k == 4)
        ret = ((lli)f(2, n - 1) + f(3, n - 2) + f(5, n - 2)) % MOD;
    if(k == 5)
        ret = ((lli)f(3, n - 1) + f(4, n - 2)) % MOD;
    return ret;
}

int N;

int main(){
    cin >> N;
    for(int i = 1; i <= 5; i++){
        for(int j = 0; j <= N; j++){
            dp[i][j] = -1;
        }
    }

    cout << ((lli)f(1, N) + f(2, N) + f(3, N) + f(4, N) + f(5, N)) % MOD << '\n';
}