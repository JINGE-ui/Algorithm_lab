#include<stdio.h>
#include<stdlib.h>
#include<algorithm>
#include<string.h>

#define MAXN 20005
typedef long long ll;
using namespace std;

struct moo{
    ll v,x;   //保存每头牛的听力阈值，坐标
}MOO[MAXN];
int N;
ll a1[MAXN],c1[MAXN];  //每个位置有多少头牛
ll a2[MAXN],c2[MAXN];  //每头牛的坐标

bool myfunction(struct moo i,struct moo j){  //升序排列
    return i.v<j.v;
}
ll lowbit(ll i){
    return i&(-i);
}
void add(ll k,ll num,ll c[]){
    while(k<=MAXN){
        c[k] += num;
        k += lowbit(k);
    }
}
ll sum(ll k,ll c[]){  //sum of 1~k
    ll res = 0;
    while(k>=1){
        res += c[k];
        k -= lowbit(k);
    }
    return res;
}

int main(){
    scanf("%d",&N);
    //init
    memset(a1,0,sizeof(a1));
    memset(c1,0,sizeof(a1));
    memset(a2,0,sizeof(a1));
    memset(c2,0,sizeof(a1));
    for(int i=1;i<=N;i++){
        scanf("%d %d",&MOO[i].v,&MOO[i].x);
    }
    sort(MOO+1,MOO+N+1,myfunction);  //升序
    ll ans = 0;
    for(int i=1;i<=N;i++){  //听力阈值升序，每一个i只需考虑前面的i与自身的距离
        a1[MOO[i].x]++;  //小于x个数
        a2[MOO[i].x] += MOO[i].x;   //小于x的坐标之和
        add(MOO[i].x,1,c1);
        add(MOO[i].x,MOO[i].x,c2);

        ll num_less = sum(MOO[i].x,c1);  //坐标小于x的个数
        ll sum_less = sum(MOO[i].x,c2);  //坐标小于x之和
        ans += (num_less*MOO[i].x-sum_less)*MOO[i].v;

        ll num_greate = i-num_less;
        ll sum_greate = sum(MAXN,c2)-sum_less;
        ans += (sum_greate-MOO[i].x*num_greate)*MOO[i].v;
    }
    printf("%lld\n",ans);
    return 0;
}