#include<stdio.h>
#include<string.h>
#include<stdlib.h>
using namespace std;
#define N 105
#define INF 9999999

//邻接表
typedef struct start_node{
    struct adj_node* next;
    int node;
}start_node;
typedef struct adj_node{
    int node;
    int cost;
    struct adj_node* next;
}adj_node;
int numv,nume;
int D[N];
bool vis[N];
struct start_node START[N];
struct adj_node* qnext_now[N];
int main(){
    while((scanf("%d %d",&numv,&nume),numv+nume)!=0){
        int u,v,c;
        D[1]=0;
        for(int i=2;i<=numv;i++){
            D[i]=INF;
        }
        vis[1]=true;
        for(int i=2;i<=numv;i++){
            vis[i]=false;
        }
        for(int i=0;i<nume;i++){
            scanf("%d %d %d",&u,&v,&c);
            if(u==1){
                D[v]=c;
            }else if(v==1){
                D[u]=c;
            }
            if(START[u].next==0){
                qnext_now[u]= START[u].next = (adj_node*)malloc(sizeof(adj_node));
                qnext_now[u]->cost=c;
                qnext_now[u]->node=v;
                qnext_now[u]->next=NULL;
            }else{
                qnext_now[u]->next=(adj_node*)malloc(sizeof(adj_node));
                qnext_now[u]=qnext_now[u]->next;
                qnext_now[u]->cost=c;
                qnext_now[u]->node=v;
                qnext_now[u]->next=NULL;
            }
            /*从链表头插入更简洁
            adj_node* qnode = (adj_node*)malloc(sizeof(adj_node));
            qnode->cost = c;
            qnode->node = v;
            qnode->next = START[u].next;
            START[u].next = qnode;
            */
            if(START[v].next==0){
                qnext_now[v]= START[v].next = (adj_node*)malloc(sizeof(adj_node));
                qnext_now[v]->cost=c;
                qnext_now[v]->node=u;
                qnext_now[v]->next=NULL;
            }else{
                qnext_now[v]->next=(adj_node*)malloc(sizeof(adj_node));
                qnext_now[v]=qnext_now[v]->next;
                qnext_now[v]->cost=c;
                qnext_now[v]->node=u;
                qnext_now[v]->next=NULL;
            }
        }
        for(int count=1;count<numv;count++){
            int buf_min=INF;
            int buf_i = 0;
            for(int i=2;i<=numv;i++){
                if(!vis[i]&&(D[i]<buf_min)){
                    buf_min = D[i];
                    buf_i = i;
                }
            }
            if(!buf_i){
                break;
            }
            D[buf_i]=buf_min;
            vis[buf_i]=true;
            adj_node* qnode = START[buf_i].next;
            while(qnode){
                if(!vis[qnode->node]){
                    if(buf_min+qnode->cost<D[qnode->node]){
                        D[qnode->node]=buf_min+qnode->cost;
                    }
                }
                qnode = qnode->next;
            }
        }
        printf("%d\n",D[numv]);
        //delete
        for(int i=1;i<=numv;i++){
            adj_node* qnode=START[i].next,*bufnode=NULL;
            while(qnode){
                bufnode = qnode->next;
                free(qnode);
                qnode = bufnode;
            }
        }
        for(int i=1;i<=numv;i++){
            START[i].next=NULL;
        }
    }
    return 0;
}

/*
int numv,nume;  //分别为点数和边数
int D[N];
bool IN[N];
int adjMAT[N][N];
//邻接矩阵实现法
int main(){ 
    int u,v,c;
    while((scanf("%d %d",&numv,&nume),numv+nume)!=0){
        for(int i=1;i<=numv;i++){
            for(int j=1;j<=numv;j++){
                adjMAT[i][j]=INF;
            }
        }
        for(int i=0;i<nume;i++){
            scanf("%d %d %d",&u,&v,&c);
            adjMAT[u][v]=adjMAT[v][u]=c;
        }
        //init
        for(int i=2;i<=numv;i++){
            IN[i]=false;
        }
        IN[1]=true;
        for(int i=2;i<=numv;i++){
            D[i]=adjMAT[1][i];
        }
        for(int count=1;count<numv;count++){
            int buf_min=INF,buf_i=0;
            for(int i=2;i<=numv;i++){
                if(!IN[i]&&D[i]<buf_min){
                    buf_min=D[i];
                    buf_i=i;
                }
            }
            if(!buf_i){
                break;
            }
            IN[buf_i]=true;
            for(int i=2;i<=numv;i++){
                if(!IN[i]&&(adjMAT[buf_i][i]+D[buf_i]<D[i])){
                    D[i]=adjMAT[buf_i][i]+D[buf_i];
                }
            }
        }
        printf("%d",D[numv]);
    }
    return 0;

}
*/





