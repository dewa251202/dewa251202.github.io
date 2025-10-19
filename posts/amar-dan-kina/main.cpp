#include <iostream>
using namespace std;
typedef long long int lli;

const int MAXX = 1'000'000;

int T, N, K;
int A[MAXX];
lli ans, special_cnt;
int cnt[MAXX + 1];

void update(int x, bool add){
    // numbers greater than K
    // are impossible to become
    // a special number
    if(x > K) return;

    if(add){
        cnt[x]++;
        if(cnt[x] == x){
            special_cnt++;
        }
        else if(cnt[x] == x + 1){
            special_cnt--;
        }
    }
    else{
        cnt[x]--;
        if(cnt[x] == x){
            special_cnt++;
        }
        else if(cnt[x] == x - 1){
            special_cnt--;
        }
    }
}

int main(){
    cin.tie(0)->sync_with_stdio(0);

    cin >> T;
    while(T--){
        cin >> N >> K;
        for(int i = 0; i < N; i++){
            cin >> A[i];
        }

        ans = special_cnt = 0;
        for(int i = 0; i < K; i++){
            update(A[i], 1);
        }
        ans += special_cnt;

        for(int i = K; i < N; i++){
            update(A[i], 1);
            update(A[i - K], 0);
            ans += special_cnt;
        }

        cout << ans << '\n';

        // reset
        for(int i = 1; i <= K; i++){
            cnt[i] = 0;
        }
    }
    return 0;
}