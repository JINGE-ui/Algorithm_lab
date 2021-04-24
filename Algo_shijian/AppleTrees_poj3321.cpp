#include<stdio.h>
#include<vector>
#include<string.h>

#define MAXN 100005
using namespace std;

vector<vector<int>> adj_fork(MAXN);
int N,M;
int Left[MAXN],Right[MAXN],fork[MAXN]; //每个分支上的苹果数 
int c[MAXN];  //树状数组

int key=1;
void DFS(int treenode){
    Left[treenode]=key;   //节点自身计入Left
    for(int i=0;i<adj_fork[treenode].size();i++){
        key++;
        DFS(adj_fork[treenode][i]);
    }
    Right[treenode]=key;
}
int lowbit(int x){  //x作为树状数组节点，2^k
    return x&(-x);
}
int getsum(int i){  //sum of 1~i
    if(i==0){
        return 0;
    }
    int sum=0;
    while(i>=1){
        sum += c[i];
        i -= lowbit(i);
    }
    return sum;
}
void modify(int i,int num){  //修改树状数组的节点i的值
    while(i<=N){
        c[i] += num;
        i += lowbit(i);
    }
}

int main(){
    int a,b;
    scanf("%d",&N);   //分支数
    //init
    for(int i=0;i<MAXN;i++){
        adj_fork[i].clear();
    }
    memset(Left,0,sizeof(Left));
    memset(Right,0,sizeof(Right));
    memset(fork,0,sizeof(fork));
    memset(c,0,sizeof(c));
    //input
    for(int i=0;i<N-1;i++){ //形成树，共N-1条边
        scanf("%d %d",&a,&b);
        adj_fork[a].push_back(b);
    }
    key=1;
    DFS(1);

    for(int i=1;i<=N;i++){  //重新命名节点，构建树状数组
        fork[i]=1;  //初始每个分支都有苹果 
        modify(i,1);
    }

    scanf("%d",&M);
    char ch[10];
    int d;
    for(int i=0;i<M;i++){
        scanf("%s %d",&ch,&d);
        if(ch[0]=='Q'){   //查询，即Left[c]~Right[c]
            printf("%d\n",getsum(Right[d])-getsum(Left[d]-1));
        }
        if(ch[0]=='C'){
            if(fork[d]==1){ //原来分支上有苹果
                modify(Left[d],-1);
                fork[d]=0;
            }else{   //添加苹果
                modify(Left[d],1);
                fork[d]=1;
            }
        }
    }
    return 0;
}