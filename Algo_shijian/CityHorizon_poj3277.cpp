#include<stdio.h>
#include<algorithm>
#include<string.h>
using namespace std;
#define MAXN 80010
typedef long long ll;

struct tree{
    ll l,r,h;  //l,r记录未离散化之前的
}TREE[4*MAXN];  //线段树节点

struct node{
    ll left,right,height;
}NODE[MAXN];  //一次根据输入记录，下标从1起
ll N[100000];  //将NODE的left和right排序，去重后结果，达到离散化，下标从1起
int num; //离散化后实际的区间长度
bool myfunc(struct node x,struct node y){{
    return x.height<y.height;
}}
void build(int l,int r,int p){  //[l,r]为当前区间，p为当前区间的序号
    //[l,r]包含于[1,num]
    /*if(l==r){  //没有长度的线段没有意义？？？
        return ;
    }
    */
    TREE[p].l = N[l];  
    TREE[p].r = N[r];
    if(r-l==1){
        return ;
    }
    int mid = (l+r)/2;
    build(l,mid,p*2);
    build(mid,r,p*2+1); //这里不是mid+1
}
void update(ll left,ll right,ll value,int p){
    //[left,right]是未离散化之前的区间，待修改区间
    if(left<=TREE[p].l&&TREE[p].r<=right){
        //当前区间是待修改区间的子集
        TREE[p].h = value;
        return ;  //区间完整，返回
    }
    //以下是区间被割裂（同一区间有两个height
    if(TREE[p].h>0){
        TREE[2*p].h = TREE[p*2+1].h = TREE[p].h;
    } //先传递给子区间，自身再置-1，表示无效
    TREE[p].h = -1;
    /*
    if(TREE[p].r<left || right<TREE[p].l){  //两区间没有交集
        return ;
    }
    */
    if(right>TREE[p*2].r){  //这里的TREE[p*2].r视为mid
        update(left,right,value,p*2+1);
    }
    if(left<TREE[p*2].r){
        update(left,right,value,p*2);
    }
    /*
    这种更新是错误的，必须找到mid
    update(left,right,value,p*2);
    update(left,right,value,p*2+1);
    */
}
ll getsum(int p){
    if(TREE[p].h>0){
        return TREE[p].h*(TREE[p].r-TREE[p].l);
    }
    if(TREE[p].h==0){
        return 0;
    }
    return getsum(p*2)+getsum(p*2+1);
}
int main(){
    int a,b,h,n;
    scanf("%d",&n);   //楼房数目
    memset(NODE,0,sizeof(NODE));
    memset(N,0,sizeof(N));
    memset(TREE,0,sizeof(TREE));
    for(int i=1;i<=n;i++){
        scanf("%lld%lld%lld",&NODE[i].left,&NODE[i].right,&NODE[i].height);
        N[2*i-1] = NODE[i].left;
        N[2*i] = NODE[i].right;
    }
    sort(NODE+1,NODE+1+n,myfunc);
    sort(N+1,N+1+2*n);
    num = unique(N+1,N+1+2*n)-N-1;

    build(1,num,1);
    for(int i=1;i<=n;i++){
        update(NODE[i].left,NODE[i].right,NODE[i].height,1);
    }
    printf("%lld\n",getsum(1));
    return 0;
}