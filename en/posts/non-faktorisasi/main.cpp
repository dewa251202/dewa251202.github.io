#include <iostream>
#include <map>
using namespace std;
typedef long long int lli;

const int MOD = 1E9 + 7;

int N, Ai;
map <int, int> powers;

int Pow(lli x, int y){
    lli ret = 1;
    while(y){
        if(y & 1) (ret *= x) %= MOD;
        (x *= x) %= MOD;
        y >>= 1;
    }
    return ret;
}

int main(){
    cin >> N;

    while(N--){
        cin >> Ai;
        for(int i = 2; i * i <= Ai; i++){
            while(Ai % i == 0){
                Ai /= i;
                powers[i]++;
            }
        }
        if(Ai != 1) powers[Ai]++;
    }

    lli ans = 1;
    for(const auto& p : powers){
        (ans *= p.first - 1) %= MOD;
        ans *= Pow(p.first, p.second - 1);
        ans %= MOD;
    }

    cout << ans << '\n';
    return 0;
}