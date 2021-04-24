#include<stdio.h>
#include<string.h>
using namespace std;
#define MAXN 100009
struct ds{
    int num;  //使用二进制表示的颜色拥有情况 
    int b;   //懒惰标记
}DS[4*MAXN];

void build(int s,int t,int p){  //对[s,t]区间建立,当前编号为p
    if(s==t){
        DS[p].num = 1;
        return;
    }
    int mid = (s+t)/2;
    build(s,mid,p*2);
    build(mid+1,t,p*2+1);
    //
    DS[p].num = DS[p*2].num | DS[p*2+1].num;
}
int getsum(int l,int r,int s,int t,int p){
    //[l,r]为查询区间，[s,t]为当前节点包含区间，p为当前节点编号
    if(l<=s&&t<=r){  //[s,t]包含于[l,r]
        return DS[p].num;
    }
    int mid = (s+t)/2,sum=0;
    //下传惰性标记
    if(DS[p].b){
        DS[p*2].num = DS[p].b;
        DS[p*2+1].num = DS[p].b;
        DS[p*2].b = DS[p].b;
        DS[p*2+1].b = DS[p].b;
        DS[p].b = 0;
    }
    if(l<=mid){ //l在左儿子的区间里
        sum |= getsum(l,r,s,mid,p*2);
    }
    if(r>mid){  //r在右儿子的区间里
        sum |= getsum(l,r,mid+1,t,p*2+1);
    }
    return sum;
}
void update(int l,int r,int c,int s,int t,int p){
    //[l,r]为修改区间,c为修改量,[s,t]为当前节点包含的区间，p为当前节点编号
    //区间[l,r]上颜色c
    if(l<=s && t<=r){ //[s,t]包含于[l,r]，[s,t]需要修改
        DS[p].num = c;
        DS[p].b = c;  //暂时存储于懒惰标记中
        return ;
    }
    int mid = (s+t)/2;
    if(DS[p].b && s!=t){
    // 如果当前节点的懒标记非空,则更新当前节点两个子节点的值和懒标记值
        DS[p*2].num = DS[p].b;
        DS[p*2+1].num = DS[p].b;
        DS[p*2].b = DS[p].b;
        DS[p*2+1].b = DS[p].b;
        DS[p].b = 0;
    }
    if(l<=mid){
        update(l,r,c,s,mid,p*2);
    }
    if(r>mid){
        update(l,r,c,mid+1,t,p*2+1);
    }
    DS[p].num = (DS[p*2].num) | (DS[p*2+1].num);
}
int main(){
    int L,T,O; //分别是区间长度、颜色总数、询问次数    char ch[10];
    int l,r,col;
    char ch[10];
    scanf("%d%d%d",&L,&T,&O)!=EOF;
    memset(DS,0,sizeof(DS));
    build(1,L,1);
    while(O--){
        scanf("%s",ch);
        if(ch[0]=='C'){
            scanf("%d%d%d",&l,&r,&col);
            if(l>r){
                update(r,l,1<<(col-1),1,L,1);
            }else{
                update(l,r,1<<(col-1),1,L,1);
            }
        }
        if(ch[0]=='P'){
            scanf("%d%d",&l,&r);
            int ans;
            if(l<=r){
                ans = getsum(l,r,1,L,1);
            }else{
                ans = getsum(r,l,1,L,1);
            }
            //计算ans中1的个数
            int count = 0;
            for(int i=0;i<32;i++){
                if((ans>>i)&1){
                    count++;
                }
            }
            printf("%d\n",count);
        }
    }
    return 0;
}