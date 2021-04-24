#include<stdio.h>
#include<vector>
#include<string.h>
#include<algorithm>
#include<math.h>
using namespace std;
/*
求无向边树任意两点之间的距离
dist[i]:i到根节点的距离
distance_between_(u,v) = dist[u]+dist[v]-2*dist[LCA(u,v)]
本题考虑用RMQ实现LCA
*/
#define MAXN 40005

typedef struct node{
    int ver,len;
}node;
int num_ver;
int COUNT; //当前DFS的访问次序
int tree_root;
int dist[MAXN];  //dist[i]:distance_between_(i,tree_root)
int visit_node[2*MAXN],depth[2*MAXN],R[MAXN];
bool vis[MAXN];  //vis[i]:节点i是否已被访问
//visit_node[i]:第i次访问的节点(i>=1)
//depth[i]:第i次访问的节点的深度
//R[i]:节点i第一次被访问的顺序
//LCA(u,v) = depth数组在R[u]~R[v]区间的最小值，设最小值下标为i
//LCA(u,v)=visit_node[i]
vector<node> adj_node[MAXN];
bool is_root[MAXN];
int dp[2*MAXN][30];
//dp[i][j]：depth在[i,i+2^j-1]区间的最小值的下标

void ST(int num){  //使用ST算法求解RMQ问题
    int a,b;
    for(int i=1;i<=num;i++){
        dp[i][0]=i;
    }
    for(int i=1;i<=log2(num);i++){
        for(int j=1;j<=num;j++){
            if(j+(1<<i)-1<=num){  //COUNT>=j+2^i-1
                a = dp[j][i-1];
                b = dp[j+(1<<i>>1)][i-1];  //!!!!runtime error原因：'+'优先级大于'<<'，必须加上括号！！！
                if(depth[a]<depth[b]){
                    dp[j][i]=a;
                }else{
                    dp[j][i]=b;
                }
            }
        }
    }
}
int RMQ(int x,int y){  //求解depth在区间[x,y]的最小值的下标
    if(x>y){  //必须x<=y
        swap(x,y);
    }
    int k = (int)log2(y-x+1.0);
    int a = dp[x][k];
    int b = dp[y-(1<<k)+1][k];
    if(depth[a]<depth[b]){
        return a;
    }else{
        return b;
    }
}
void DFS(int u,int level){  
//为将LCA转化为RMQ
//遍历树，初始化visit_node,depth,R
    vis[u]=true;
    visit_node[COUNT]=u;
    depth[COUNT]=level;
    R[u]=COUNT++;
    for(int i=0;i<adj_node[u].size();i++){
        int v = adj_node[u][i].ver;
        if(!vis[v]){  //若节点v还未被访问
            dist[v] = dist[u]+adj_node[u][i].len;
            DFS(v,level+1);
            //回溯
            visit_node[COUNT]=u;
            depth[COUNT++]=level;
        }
    }
}
void init(){
    memset(dist,0,sizeof(dist));
    memset(visit_node,0,sizeof(visit_node));
    memset(depth,0,sizeof(depth));
    memset(R,0,sizeof(R));
    memset(dp,0,sizeof(dp));
    for(int i=1;i<=num_ver;i++){
        adj_node[i].clear();
        vis[i]=false;
        is_root[i]=true;
    }
    tree_root=1;
    COUNT = 1;
}
int main(){
    int num_edge,u,v,l;
    int queries; //询问次数
    int ancestor;
    char c;
    node tmp;
    init();
    scanf("%d %d",&num_ver,&num_edge);
    while(num_edge--){
        scanf("%d %d %d %c",&u,&v,&l,&c);
        tmp.ver = v;
        tmp.len = l;
        adj_node[u].push_back(tmp);
        tmp.ver = u;
        adj_node[v].push_back(tmp);
        is_root[v]=false;
    }
    for(int i=1;i<=num_ver;i++){
        if(is_root[i]){
            tree_root = i;
            break;
        }
    }
    dist[tree_root]=0;
    DFS(tree_root,0);
    ST(COUNT);
    scanf("%d",&queries);
    while(queries--){
        scanf("%d%d",&u,&v);
        ancestor = visit_node[RMQ(R[u],R[v])];
        printf("%d\n",dist[u]+dist[v]-2*dist[ancestor]);
    }
    return 0;
}