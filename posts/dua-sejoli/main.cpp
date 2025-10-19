#include <iostream>
#include <vector>
using namespace std;
typedef pair <int, int> pii;

const int MAXN = 50000;
const int MOD = 1E9 + 7;

int T, N, Q, LOG_N;
int cycle_start, cycle_size;
int parent[MAXN];
int cycle_idx[MAXN];
int depth[MAXN];
int sparta[MAXN][20];
vector <pii> al[MAXN];
vector <int> cycle;
bool vis[MAXN];
bool push_cycle;

void get_cycle(const int& u, const int& idx = -1){
    vis[u] = 1;
    for(const pii& p : al[u]){
        if(cycle_start != -1) break;
        if(p.second == idx) continue;
        if(p.second != idx && vis[p.first]){
            cycle_start = p.first;
            push_cycle = 1;
            break;
        }
        get_cycle(p.first, p.second);
    }

    if(push_cycle){
        cycle.push_back(u);
        if(u == cycle_start) push_cycle = 0;
    }
}

void get_parent(const int& u, const int& prev = -1){
    parent[u] = prev;
    for(const pii& p : al[u]){
        if(p.first == prev || cycle_idx[p.first] != -1)
            continue;
        depth[p.first] = depth[u] + 1;
        get_parent(p.first, u);
    }
}

void construct_sparta(){
    for(int i = 0; i < N; i++)
        sparta[i][0] = parent[i];

    for(int j = 1; j <= LOG_N; j++)
        for(int i = 0; i < N; i++){
            int v = sparta[i][j - 1];
            if(v == -1) sparta[i][j] = -1;
            else sparta[i][j] = sparta[v][j - 1];
        }
}

int get_root(int v){
    int jump = depth[v];
    for(int i = LOG_N; 0 <= i; i--)
        if((1 << i) <= jump){
            jump -= 1 << i;
            v = sparta[v][i];
        }
    return v;
}

int lca(int u, int v){
    if(depth[v] < depth[u])
        swap(u, v);

    int diff = depth[v] - depth[u];
    for(int i = LOG_N; 0 <= i; i--)
        if((1 << i) <= diff){
            diff -= 1 << i;
            v = sparta[v][i];
        }

    if(u == v) return v;

    for(int i = LOG_N; 0 <= i; i--)
        if(sparta[u][i] != sparta[v][i]){
            u = sparta[u][i];
            v = sparta[v][i];
        }
    return sparta[v][0];
}

int main(){
    cin.tie(0)->sync_with_stdio(0);
    cin >> T;

    while(T--){
        cin >> N;
        cycle.clear();
        for(int i = 0; i < N; i++){
            al[i].clear();
            vis[i] = 0;
            parent[i] = -1;
            cycle_idx[i] = -1;
            depth[i] = 0;
        }

        int u, v;
        for(int i = 0; i < N; i++){
            cin >> u >> v;
            u--, v--;
            al[u].push_back({v, i});
            al[v].push_back({u, i});
        }

        cycle_start = -1;
        push_cycle = 0;
        get_cycle(0);

        for(size_t i = 0; i < cycle.size(); i++)
            cycle_idx[cycle[i]] = i;

        for(int i = 0; i < N; i++)
            if(cycle_idx[i] != -1)
                get_parent(i);

        int k = 1;
        LOG_N = 0;
        while(k < N){
            k <<= 1;
            LOG_N++;
        }
        construct_sparta();

        cycle_size = cycle.size();
        cin >> Q;
        while(Q--){
            cin >> u >> v;
            u--, v--;
            if(get_root(u) == get_root(v))
                cout << "1 " << (depth[u] + depth[v] - 2 * depth[lca(u, v)]) % MOD << '\n';
            else if(cycle_idx[u] != -1 && cycle_idx[v] != -1){
                int dist = max(cycle_idx[u], cycle_idx[v]) - min(cycle_idx[u], cycle_idx[v]);
                cout << "2 " << (1LL * dist * (cycle_size - dist)) % MOD << '\n';
            }
            else
                cout << "1 " << (depth[u] + depth[v]) % MOD << '\n';
        }
    }
    return 0;
}