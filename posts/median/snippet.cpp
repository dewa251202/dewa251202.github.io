typedef pair<int, int> pii;

vector <pii> left;
pii count = {0, 0};
for(int L = K - 1; 1 <= L; L--){
    if(S[L] < S[K]) count.first++;
    else if(S[L] > S[K]) count.second++;
    left.push_back(count);
}

vector <pii> right;
count = {0, 0};
for(int R = K + 1; R <= N; R++){
    if(S[R] < S[K]) count.first++;
    else if(S[R] > S[K]) count.second++;
    right.push_back(count);
}