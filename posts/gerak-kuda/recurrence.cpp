#include <iostream>
using namespace std;
typedef long long int lli;

const int MOD = 1E9 + 7;

int f(int k, int n){
    if(n == 0) return 0;
    if(n == 1) return 1;
    
    if(k == 1)
        return ((lli)f(3, n - 1) + f(2, n - 2)) % MOD;
    if(k == 2)
        return ((lli)f(4, n - 1) + f(1, n - 2) + f(3, n - 2)) % MOD;
    if(k == 3)
        return ((lli)f(1, n - 1) + f(5, n - 1) + f(2, n - 2) + f(4, n - 2)) % MOD;
    if(k == 4)
        return ((lli)f(2, n - 1) + f(3, n - 2) + f(5, n - 2)) % MOD;
    if(k == 5)
        return ((lli)f(3, n - 1) + f(4, n - 2)) % MOD;
    return 0;
}

int N;

int main(){
    cin >> N;
    cout << ((lli)f(1, N) + f(2, N) + f(3, N) + f(4, N) + f(5, N)) % MOD << '\n';
}