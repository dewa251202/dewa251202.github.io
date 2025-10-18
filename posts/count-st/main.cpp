#include <iostream>
#include <vector>
#include <queue>
#include <map>
using namespace std;
typedef long long int lli;

lli T, N, M, Ai, Bi, idx, ans, k = 1E9 + 7;
vector <int> al[50000];
map < pair <int, int >, bool> bridge;
int id[50000];
int lowlink[50000];
bool onstack[50000];

void dfs(int u, int pred = -1){
    id[u] = lowlink[u] = idx++;
    onstack[u] = 1;

    for(int v : al[u]){
        if(v == pred){
            continue;
        }

        if(!onstack[v]){
            dfs(v, u);
            lowlink[u] = min(lowlink[u], lowlink[v]);

            if(lowlink[v] > id[u]){
                bridge[make_pair(min(u, v), max(u, v))] = 1;
            }
        }
        else{
            lowlink[u] = min(lowlink[u], id[v]);
        }
    }
}

void sfd(int u, int pred = -1){
    onstack[u] = 1;

    for(int v : al[u]){
        if(v == pred || bridge[make_pair(min(u, v), max(u, v))]){
            continue;
        }

        if(id[v] == -1){
            id[v] = id[u] + 1;
            sfd(v, u);
        }
        else{
            if(onstack[v]){
                ans = (ans * (id[u] - id[v] + 1)) % k;
            }
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
        cin >> N >> M;

        for(int i = 0; i < M; i++){
            cin >> Ai >> Bi;

            al[Ai].push_back(Bi);
            al[Bi].push_back(Ai);
        }

        for(int i = 0; i < N; i++){
            id[i] = lowlink[i] = -1;
            onstack[i] = 0;
        }

        idx = 0;
        dfs(0);

        for(int i = 0; i < N; i++){
            id[i] = -1;
            onstack[i] = 0;
        }

        ans = 1;
        idx = 0;
        for(int i = 0; i < N; i++){
            if(id[i] == -1){
                id[i] = 0;
                sfd(i);
            }
        }

        cout << ans << '\n';

        for(int i = 0; i < N; i++){
            al[i].clear();
        }
        bridge.clear();
    }
    return 0;
}