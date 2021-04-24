#include<stdio.h>

#define NUM 10010
#define MIN(A,B) ((A)<(B)?(A):(B))
#define INF 999999999

int f[NUM];

int main(){
    int H,N;
    scanf("%d %d",&H,&N);
    f[0]=0;
    for(int i=1;i<NUM;i++){
        f[i]=INF;
    }
    int A,B;
    while(N--){
        scanf("%d %d",&A,&B);
        for(int v=1;v<=H+3;v++){
            if(v<=A){
                f[v]=MIN(f[v],B);
            }else{
                f[v]=MIN(f[v],f[v-A]+B);
            }
        }
    }
    printf("%d",f[H]);
    
    return 0;
}
