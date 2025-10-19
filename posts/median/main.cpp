#include <algorithm>
#include <iostream>
#include <map>
using namespace std;

const int MAXN = 100000;

int T, N, K, ans;
int S[MAXN];
map <int, int> R;

int main(){
    cin >> T;
    for(int t = 1; t <= T; t++){
        R.clear();

        cin >> N >> K;
        K--;
        for(int i = 0; i < N; i++){
            cin >> S[i];
        }

        ans = 1;
        int diff = 0;
        for(int i = K + 1; i < N; i++){
            if(S[i] > S[K]) diff++;
            else diff--;

            if(diff == 0){
                ans = max(ans, i - K + 1);
            }

            R[diff] = i;
        }

        diff = 0;
        for(int i = K - 1; 0 <= i; i--){
            if(S[i] > S[K]) diff++;
            else diff--;

            if(diff == 0){
                ans = max(ans, K - i + 1);
            }

            if(R.find(-diff) == R.end()) continue;
            ans = max(ans, R[-diff] - i + 1);
        }


        cout << "Case #" << t << ": " << ans << '\n';
    }
    return 0;
}
