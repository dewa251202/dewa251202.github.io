#include <iostream>
#include <vector>
using namespace std;

const int MOD = 1E9 + 7;

int A, B;

int main(){
    cin >> A >> B;

    int ans = 0;
    for(int i = 1; i <= A; i++){
        vector <int> divs;
        for(int j = 1; j * j <= i; j++){
            if(i % j == 0){
                divs.push_back(j);
                if(j * j != i)
                    divs.push_back(i/j);
            }
        }

        for(const int& d : divs){
            ans += 1LL * B/d * d % MOD;
            ans %= MOD;
        }
    }

    cout << ans << '\n';
    return 0;
}