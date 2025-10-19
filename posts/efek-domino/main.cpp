#include <iostream>
#include <bigint.h>
using namespace std;

const int MAXN = 1000;

int T;
bigint F[MAXN + 1];

int main(){
    cin.tie(0)->sync_with_stdio(0);

    F[0] = 1;
    for(int i = 1; i <= MAXN; i++){
        F[i] = F[i - 1] * (i/2 + 1);
    }

    cin >> T;
    for(int i = 0; i < T; i++){
        int x;
        cin >> x;
        cout << F[x] << '\n';
    }
    return 0;
}