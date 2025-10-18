#include <iostream>
#include <vector>
using namespace std;
typedef long long int lli;

const lli MOD = 1E9 + 7;

lli T, N, M, Ai, Bi, ans;
vector <int> al[50000];
int id[50000];
bool onstack[50000];

void dfs(int u, int pred = -1){
    onstack[u] = 1;

    for(int v : al[u]){
        if(v == pred){
            continue;
        }

        if(id[v] == -1){
            id[v] = id[u] + 1;
            dfs(v, u);
        }
        else if(onstack[v]){
            ans = (ans * (id[u] - id[v] + 1)) % MOD;
        }
    }

    onstack[u] = 0;
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> T;
    while(T--){
        for(int i = 0; i < N; i++){
            al[i].clear();
        }
        
        cin >> N >> M;

        for(int i = 0; i < M; i++){
            cin >> Ai >> Bi;

            al[Ai].push_back(Bi);
            al[Bi].push_back(Ai);
        }

        for(int i = 0; i < N; i++){
            id[i] = -1;
            onstack[i] = 0;
        }

        ans = 1;
        id[0] = 0;
        dfs(0);

        cout << ans << '\n';
    }
    return 0;
}