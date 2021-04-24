#include<stdio.h>
#include<string.h>
#include<queue>

using namespace std;
#define MAXV 30
#define MAXE 100000
#define INF 0x7fffffff

struct node{
    int to,cost,next;
}Edge[MAXE];

int head[MAXE];
int E;
int dist[MAXV];
int r[MAXV],t[MAXV];
//r[i]:i~i+1需要的数目
//t[i]:i~i+1应征的数目
int vis[MAXV];  //是否入队

void add_edge(int u,int v,int co){
    Edge[E].to = v;
    Edge[E].cost = co;
    Edge[E].next = head[u];
    head[u]=E++;
}

int SPFA(int val)  ////求单源最长路径
{
    memset(dist,-0x7f,sizeof(dist));
    queue<int>q;
    dist[0]=0;
    q.push(0);
    while(q.size()!=0)
    {
        int p=q.front();q.pop();
        vis[p]=0;
        if(p==24&&dist[p]>val) return 0;
        for(int i=head[p];i!=-1;i=Edge[i].next)  //i是v起始的边
        {
            if(dist[Edge[i].to]<dist[p]+Edge[i].cost)  //更新为最长的路径
            {
                dist[Edge[i].to]=dist[p]+Edge[i].cost;
                if(!vis[Edge[i].to])    
                {
                     vis[Edge[i].to]=1;
                     q.push(Edge[i].to);
                }
            }
        }
    }
    return dist[24]<=val?1:0;
    
}

void init(){
    memset(head,-1,sizeof(head));
    memset(dist,-0xffff,sizeof(dist));
    memset(vis,0,sizeof(vis));
    E = 0;
}
//节点:0~24  节点0是起始节点 时刻i从1起
//边数从0起
int main(){
    int queries,N,k;
    int right,l,mid;
    int ans;  
    scanf("%d",&queries);
    while(queries--){
        for(int i=0;i<=23;i++){
            scanf("%d",&r[i]);
        }
        scanf("%d",&N);
        memset(t,0,sizeof(t));
        for(int i=0;i<N;i++){
            scanf("%d",&k);
            t[k]++;
        }
        //建模
        //s[a]-s[b]>=c：cost_from_b_to_a = c 
        right = N+1;
        l=0;
        ans = INF;
        while(l<=right){
            init();
            mid = (l+right)>>1;
            //build
            for(int i=0;i<=23;i++){
                add_edge(i,i+1,0);
                add_edge(i+1,i,-t[i]);
            }
            for(int i=7;i<=23;i++){
                add_edge(i-7,i+1,r[i]);
            }
            add_edge(0,24,mid);
            //add_edge(24,0,-mid);
            for(int i=0;i<7;i++){
                add_edge(i+17,i+1,r[i]-mid);
            }

            if(SPFA(mid)){
                ans = mid;
                right = mid-1;
            }else{
                l = mid + 1;
            }
        }
        if(ans>N){
            printf("No Solution\n");
        }else{
            printf("%d\n",ans);
        }
    }
    return 0;
}