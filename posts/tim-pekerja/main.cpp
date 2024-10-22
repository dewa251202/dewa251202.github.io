#include <iostream>
#include <vector>
using namespace std;
typedef long long int lli;
typedef pair <int, lli> pil;

const lli INF = 1E15;

struct component {
    int role[3];
    lli cost;

    component(){
        cost = 0;
        fill(role, role + 3, 0);
    }
};

lli workers_cost, union_cost;
pil workers[100];
vector <pil> al[100];
vector <component> graph;
bool vis[100];
lli dp[101][16][16][16];
bool subset_sum[101][16][16][16];

void dfs(int u){
    if(!vis[u]){
        vis[u] = 1;
        graph.back().role[workers[u].first]++;
        workers_cost += workers[u].second;
        for(const pil& p : al[u]){
            const int& v = p.first;
            union_cost += p.second;
            dfs(v);
        }
    }
}

int main(){
    int T;
    cin >> T;
    while(T--){
        int N, P, K, M, S;
        cin >> N >> P >> K >> M >> S;
        graph.clear();
        for(int i = 0; i < N; i++){
            vis[i] = 0;
            al[i].clear();
        }

        for(int i = 0; i < N; i++){
            string role;
            cin >> role >> workers[i].second;
            if(role == "kuli") workers[i].first = 0;
            if(role == "mandor") workers[i].first = 1;
            if(role == "sekretaris") workers[i].first = 2;
        }

        for(int i = 0; i < P; i++){
            int Ai, Bi;
            lli Qi;
            cin >> Ai >> Bi >> Qi;
            Ai--; Bi--;
            al[Ai].push_back({Bi, Qi});
            al[Bi].push_back({Ai, Qi});
        }

        graph.push_back(component());
        for(int i = 0; i < N; i++){
            if(!vis[i]){
                workers_cost = union_cost = 0;
                graph.push_back(component());
                dfs(i);
                graph.back().cost = workers_cost + union_cost/2;
            }
        }

        for(size_t n = 0; n < graph.size(); n++){
            for(int k = 0; k <= K; k++){
                for(int m = 0; m <= M; m++){
                    for(int s = 0; s <= S; s++){
                        dp[n][k][m][s] = -INF;
                        subset_sum[n][k][m][s] = false;
                    }
                }
            }
        }
        subset_sum[0][0][0][0] = true;
        dp[0][0][0][0] = 0;

        for(size_t n = 1; n < graph.size(); n++){
            for(int k = 0; k <= K; k++){
                for(int m = 0; m <= M; m++){
                    for(int s = 0; s <= S; s++){
                        dp[n][k][m][s] = dp[n - 1][k][m][s];
                        subset_sum[n][k][m][s] = subset_sum[n - 1][k][m][s];

                        if(graph[n].role[0] <= k && graph[n].role[1] <= m && graph[n].role[2] <= s){
                            int nx_k = k - graph[n].role[0];
                            int nx_m = m - graph[n].role[1];
                            int nx_s = s - graph[n].role[2];

                            if(subset_sum[n - 1][nx_k][nx_m][nx_s]){
                                subset_sum[n][k][m][s] = true;
                                lli nx_cost = dp[n - 1][nx_k][nx_m][nx_s] + graph[n].cost;
                                dp[n][k][m][s] = max(dp[n][k][m][s], nx_cost);
                            }
                        }
                    }
                }
            }
        }

        if(!subset_sum[graph.size() - 1][K][M][S])
            cout << "tidak mungkin\n";
        else
            cout << dp[graph.size() - 1][K][M][S] << '\n';
    }
    return 0;
}