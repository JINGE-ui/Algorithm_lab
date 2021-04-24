#include<stdio.h>
//类似矩阵链乘法
//状态转移方向：dp[1][1]->dp[1][n]
#define N 400
#define INF 0x7fffffffffffffff
typedef long long ll;
ll dp[N+1][N+1];
ll A[N+1];
int main(){
    int num;   //num>=2
    scanf("%d",&num);
    int i=1;
    ll sum1i=0,sum1j=0;;
    for(int i=1;i<N+1;i++){
        dp[i][i]=0;
    }
    int tmp = num;
    while(num--){
        scanf("%lld",&A[i]);
        i++;
    }
    ll minbuf=INF;
    for(int j=1;j<=tmp;j++){
        sum1j = sum1j + A[j];
        for(int i=j;i>=1;i--){
            sum1i = sum1i + A[i];
            for(int k=i;k<j;k++){
                if((dp[i][k]+dp[k+1][j]+sum1i)<minbuf){
                    minbuf = dp[i][k]+dp[k+1][j]+sum1i;
                }
            }
            if(minbuf!=INF){
                dp[i][j]=minbuf;
                minbuf=INF;
            }
        }
        sum1i = 0;
    }
    printf("%lld",dp[1][tmp]);
    return 0;
}