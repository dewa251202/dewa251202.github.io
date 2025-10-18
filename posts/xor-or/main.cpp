#include <iostream>
#include <vector>
#include <queue>
using namespace std;
typedef long long int lli;
typedef pair <int, int> pii;

const int MAXN = 30000;

int T, N, M;
lli vcnt, cnt[2];
char value[MAXN];
vector <pii> al[MAXN];
queue <int> q;

lli dfs(int u, const int& pos){
    vcnt = cnt[0] = cnt[1] = 0;

    value[u] = '0';
    q.push(u);

    bool odd_cyc = 0;
    while(!q.empty()){
        u = q.front();
        q.pop();
        vcnt++;
        cnt[value[u] & 1]++;

        for(const pii& p : al[u]){
            const int& v = p.first;
            const int w = ((p.second >> pos) & 1);
            if(value[v] == '.'){
                value[v] = value[u] ^ w;
                q.push(v);
            }
            else if(value[v] != (value[u] ^ w))
                odd_cyc = 1;
        }
    }

    if(odd_cyc) return vcnt * (vcnt - 1)/2;
    else return cnt[0] * cnt[1];
}

int main(){
    ios_base::sync_with_stdio(0);

    cin >> T;
    while(T--){
        cin >> N >> M;

        for(int i = 0; i < N; i++)
            al[i].clear();

        int Ui, Vi, Wi, len;
        int mx_pos = 0;
        for(int i = 0; i < M; i++){
            cin >> Ui >> Vi >> Wi;
            Ui--, Vi--;

            al[Ui].push_back({Vi, Wi});
            al[Vi].push_back({Ui, Wi});

            len = 0;
            while(Wi){
                Wi >>= 1;
                len++;
            }
            mx_pos = max(mx_pos, len);
        }

        int ans = 0;
        for(int pos = 0; pos <= mx_pos; pos++){
            for(int i = 0; i < N; i++)
                value[i] = '.';

            int rcnt = 0;
            for(int src = 0; src < N; src++){
                if(value[src] == '.')
                    rcnt += dfs(src, pos);
            }

            ans += rcnt * (1 << pos);
        }

        cout << ans << '\n';
    }
    return 0;
}