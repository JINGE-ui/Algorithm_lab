#include<stdio.h>
#include<vector>
#include<string.h>

using namespace std;
#define MAXN 1010
#define LOG_MAXN 10

vector<int> SON[MAXN];   //类邻接表
int in_degree[MAXN];   //每个点的入度
int num_ver,tree_root;
int grand[MAXN][LOG_MAXN]; //grand[i][j]:标号i的点向上2^j遇到的点
int depth[MAXN]; //每个节点的深度，根节点为0
int res[MAXN];  //下标i作为最短公公节点的次数

void SWAP(int &u,int &v){
    int tmp = u;
    u = v;
    v = tmp;
}

void DFS(int node,int father,int level){
    /*
        初始化depth
        得到每个点的grand[i][0]
    */
   grand[node][0]=father;
   depth[node]=level;
   for(int i=0;i<SON[node].size();i++){
       DFS(SON[node][i],node,level+1);
   }
}

void LCA_init(){  //init grand:grand[i][j] = grand[grand[i][j-1]][j-1]
    DFS(tree_root,-1,0);
    for(int j=0;j<LOG_MAXN-1;j++){
        for(int i=1;i<=num_ver;i++){
            if(grand[i][j]<0){
                grand[i][j+1]=-1;
            }else{
                grand[i][j+1] = grand[grand[i][j]][j];
            }
        }
    }
}

int LCA(int u,int v){
    if(depth[u]<depth[v]){  
        SWAP(u,v);
    }
    for(int k=LOG_MAXN-1;k>=0;k--){  //深度大的往深度小的对齐
        if((depth[u]-depth[v])>>k&1){
            u = grand[u][k];
        }
    }
    if(u==v){
        return u;
    }
    for(int k=LOG_MAXN-1;k>=0;k--){
        if(grand[u][k]!=grand[v][k]){ //如果等号成立，说明跳过了
            u = grand[u][k];
            v = grand[v][k];
        }
    }
    //循环截至到最近公共祖先的孩子节点
    return grand[u][0];
}

void init(){
    for(int i=0;i<MAXN;i++){
        SON[i].clear();
    }
    memset(in_degree,0,sizeof(in_degree));
    memset(depth,0,sizeof(depth));
    memset(grand,0,sizeof(grand));
    memset(res,0,sizeof(res));
    tree_root=0;
}

/*
使用倍增算法实现LCA
*/
int main(){
    int num_adj,u,v,num_ask;
    while(scanf("%d",&num_ver)!=EOF){  //可能有多个输入算例
        init();
        for(int i=1;i<=num_ver;i++){  //点标号从1起
            scanf("%d:(%d)",&u,&num_adj);
            while(num_adj--){
                scanf("%d",&v);
                SON[u].push_back(v);
                in_degree[v]++;
            }
        }
        for(int i=1;i<=num_ver;i++){
            if(!in_degree[i]){
                tree_root=i;
                break;
            }
        }
        if(!tree_root){
            printf("输入不合法");  //
            return 0;
        }
        LCA_init();
        scanf("%d",&num_ask);
        while(num_ask--){
            while(getchar()!='(');
            scanf("%d%d",&u,&v);
            while(getchar()!=')');
            res[LCA(u,v)]++;
        }
        //output ans
        for(int i=1;i<=num_ver;i++){
            if(res[i]){
                printf("%d:%d\n",i,res[i]);
            }
        }
    }
    return 0;
}