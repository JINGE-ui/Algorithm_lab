#include<stdio.h>
#include<string.h>

#define MAXV 30005   //最大点数
#define MAXE 150005  //最多边数
#define INF 0x7fffffff
struct node{
    int to,next,cost;  
};
struct node Edge[MAXE];
int head[MAXV];  //点到边的映射，点从1计数
int num_ver,num_edge;
int E=0; //当前边数
int dist[MAXV],vis[MAXV];  
int STACK[MAXV],top;  //当前栈中元素个数

void spfa(int s){  //源点s到所有点的最短路径
    for(int i=1;i<=num_ver;i++){
        dist[i]=INF;
    }
    dist[s]=0;
    STACK[top++]=s;
    vis[1]=s;
    while(top){
        int v = STACK[--top];
        vis[v]=0;  //出栈
        for(int i=head[v];i!=-1;i=Edge[i].next){  //i是v起始的边,遍历所有v起始的边
            if(dist[Edge[i].to]>dist[v]+Edge[i].cost){
                dist[Edge[i].to] = dist[v]+Edge[i].cost; //松弛
                if(!vis[Edge[i].to]){ //满足松弛条件且该未入栈
                    vis[Edge[i].to]=1;
                    STACK[top++]=Edge[i].to;
                }
            }
        }
    }
}
void add_edge(int u,int v,int co){
    Edge[E].to = v;
    Edge[E].cost=co;
    Edge[E].next=head[u];  //从u起始的另一条边
    head[u]=E;
    E++;
}
int main(){
    int u,v,co;
    while(scanf("%d %d",&num_ver,&num_edge)!=EOF){
        //init
        E=0; //边从0计数
        top=0;
        memset(vis,0,sizeof(vis));
        memset(head,-1,sizeof(head));
        memset(STACK,0,sizeof(STACK));
        //
        for(int i=1;i<=num_edge;i++){
            scanf("%d%d%d",&u,&v,&co);  //d[v]-d[u]<=co,则cost_from_u_to_v = co
            add_edge(u,v,co);
        }
        spfa(1);
        printf("%d\n",dist[num_ver]);
    }
    return 0;
}