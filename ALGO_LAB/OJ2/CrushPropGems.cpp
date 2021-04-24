#include<stdio.h>
#include<queue>
#include<string.h>
#include<math.h>
using namespace std;


#define INF 999999999999999
#define MIN(A,B) ((A)>(B)?(B):(A)) 
typedef long long ll; 
queue<int> q1;
int pre[105];  //前驱,记录增广路径
ll flow[105];
int N;
ll adjMAT[105][105];
ll BFS(int s,int dest){ //使用BFS寻找增广路径
    while(!q1.empty()){  //清空队列
        q1.pop();
    }
    q1.push(s);
    for(int i=1;i<=N+1;i++){
        pre[i]=-1;
    }
    pre[s]=0;
    flow[s]=INF;
    while(!q1.empty()){
        int cur=q1.front();
        q1.pop();
        if(cur == dest){
            break;
        }
        for(int i=1;i<=N+1;i++){
            if(pre[i]==-1&&adjMAT[cur][i]>0){
                pre[i]=cur;
                flow[i]=MIN(flow[cur],adjMAT[cur][i]);
                if(i==dest){
                    return flow[i];
                }
                q1.push(i);
            }
        }
    }
    if(pre[dest]==-1){
        return -1;
    }else{
        return flow[dest];
    }
}
ll max_flow(int s,int t){
    ll sum_flow=0;
    ll flow0;
    while((flow0 = BFS(s,t))!=-1){
        sum_flow+=flow0;
        int tmp = t;
        while(tmp!=s){
            adjMAT[pre[tmp]][tmp]-=flow0;
            adjMAT[tmp][pre[tmp]]+=flow0;
            tmp = pre[tmp];
        }
    }
    return sum_flow;
}
int main(){
    scanf("%d",&N);
    ll ai,sum_positive=0;
    memset(adjMAT,0,sizeof(adjMAT))
    ;
    for(int i=1;i<=N;i++){
        scanf("%lld",&ai);
        if(ai>=0){
            sum_positive+=ai;  //正权和
            adjMAT[0][i]=ai;
        }else{
            adjMAT[i][N+1]=-ai;
        }
        for(int k=1;k<=i/2;k++){
            if(i%k==0){  //i是k的倍数
                adjMAT[i][k]=INF;
            }
        }
    }
    printf("%lld",sum_positive-max_flow(0,N+1));   //W=正权和-最小割
    return 0;
}