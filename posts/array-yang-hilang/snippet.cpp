for(int i = 0; i < N; i++){
    for(int j = 2; j * j <= A[i]; j++){
        while(A[i] % j == 0){
            cnt[j]++;
            A[i] /= j;
        }
    }
    if(A[i] != 1) cnt[A[i]]++;
}