#include <iostream>
#include <cassert>
#include <vector>
using namespace std;
typedef long long int lli;

const int MOD = 1E9 + 7;

struct Matrix {
    int N, M;
    vector < vector <int> > entry;

    Matrix(int n, int m) : N(n), M(m) {
        entry.assign(n, vector <int>(m, 0));
    }

    Matrix operator*(const Matrix& other){
        assert(M == other.N);
        Matrix ret(N, other.M);
        for(int i = 0; i < N; i++){
            for(int j = 0; j < other.M; j++){
                for(int k = 0; k < M; k++){
                    ret.entry[i][j] += (lli)entry[i][k] * other.entry[k][j] % MOD;
                    ret.entry[i][j] %= MOD;
                }
            }
        }
        return ret;
    }

    Matrix operator^(int y){
        assert(N == M);
        Matrix ret(N, N);
        for(int i = 0; i < N; i++) ret.entry[i][i] = 1;

        Matrix x = *this;
        while(y){
            if(y & 1) ret = ret * x;
            x = x * x;
            y >>= 1;
        }
        return ret;
    }
};

int N;

int main(){
    cin >> N;

    Matrix A(10, 10);
    for(int i = 0; i < 3; i++) A.entry[i][i + 2] = A.entry[i + 2][i] = 1;
    for(int i = 0; i < 4; i++) A.entry[i][5 + i + 1] = A.entry[i + 1][5 + i] = 1;
    for(int i = 0; i < 5; i++) A.entry[5 + i][i] = 1;

    Matrix base(10, 1);
    for(int i = 0; i < 5; i++) base.entry[i][0] = 1;

    Matrix res = (A ^ (N - 1)) * base;

    int ans = 0;
    for(int i = 0; i < 5; i++) (ans += res.entry[i][0]) %= MOD;

    cout << ans << '\n';
    return 0;
}