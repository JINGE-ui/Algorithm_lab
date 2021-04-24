#include <iostream>
#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
#define N 1000005
#define rank Rank
int wa[N],wb[N],wsf[N],wv[N],sa[N];
int rank[N],height[N],s[N],a[N];
//sa[i]:字典序中排第i位的起始位置
//rank[i]:str第i个位置的后缀是在字典序排第几
//height[i]：字典序排i和i-1的后缀的最长公共前缀
char str[N];
int len[105],size,ans[N];
//len[i]:输入的第i个字符串的长度
//ans[i]:第i个答案的长度
bool vis[105];

int cmp(int *r,int a,int b,int k)
{
    return r[a]==r[b]&&r[a+k]==r[b+k];
}
void getsa(int *r,int *sa,int n,int m)//构造后缀数组
{
    int i,j,p,*x=wa,*y=wb,*t;
    for(i=0; i<m; i++)  wsf[i]=0;
    for(i=0; i<n; i++)  wsf[x[i]=r[i]]++;
    for(i=1; i<m; i++)  wsf[i]+=wsf[i-1];
    for(i=n-1; i>=0; i--)  sa[--wsf[x[i]]]=i;
    p=1;
    j=1;
    for(; p<n; j*=2,m=p)
    {
        for(p=0,i=n-j; i<n; i++)  y[p++]=i;
        for(i=0; i<n; i++)  if(sa[i]>=j)  y[p++]=sa[i]-j;
        for(i=0; i<n; i++)  wv[i]=x[y[i]];
        for(i=0; i<m; i++)  wsf[i]=0;
        for(i=0; i<n; i++)  wsf[wv[i]]++;
        for(i=1; i<m; i++)  wsf[i]+=wsf[i-1];
        for(i=n-1; i>=0; i--)  sa[--wsf[wv[i]]]=y[i];
        t=x;
        x=y;
        y=t;
        x[sa[0]]=0;
        for(p=1,i=1; i<n; i++)
            x[sa[i]]=cmp(y,sa[i-1],sa[i],j)? p-1:p++;
    }
}
void getheight(int *r,int n)//求height数组
{
    int i,j,k=0;
    for(i=1; i<=n; i++) {
        rank[sa[i]]=i;
    }
    for(i=0; i<n; i++)
    {
        if(k)
            k--;
        else
            k=0;
        j=sa[rank[i]-1];
        while(r[i+k]==r[j+k]){
            k++;
        }
        height[rank[i]]=k;
    }
}
 
int check(int mid,int n,int k)
{
    int i,j;
    int size = 0,cnt = 0;
    memset(vis,false,sizeof(vis));  //vis标记数组
    for(i = 1; i<=n; i++){
        if(height[i]>=mid){
            for(j = 1; j<=k; j++){
                //把sa[i-1]或sa[i]所在的字符串给标记，同样的串不重复累加
                if(sa[i]>len[j-1]&&sa[i]<len[j]) cnt+=(vis[j]?0:1),vis[j]=true;
                if(sa[i-1]>len[j-1]&&sa[i-1]<len[j]) cnt+=(vis[j]?0:1),vis[j]=true;
            }
        }
        else{
            if(cnt>k/2){
                ans[++size] = sa[i-1];
            }
            cnt = 0;
            memset(vis,false,sizeof(vis));
        }
    }
    if(cnt>k/2){
        ans[++size] = sa[n];
    }
    if(size!=0){
        ans[0] = size;
        return 1;
    }
    return 0;
}
 
int main()
{
    int n,k,i,j,flag = 0; //flag为算例之间的换行标志
    while(scanf("%d",&k),k!=0)
    {
        n = 0;
        size = 0;
        for(i = 1; i<=k; i++)
        {
            scanf("%s",str+n);
            for(; str[n]!='\0'; n++)
                s[n] = str[n];  //str写入s
            s[n] = '#'+i;  //字符串之间隔开
            len[++size] = n;  //记录每个字符串的大小
            n++;
        }
        s[n-1] = 0;
        getsa(s,sa,n,255);
        getheight(s,n-1);
        int left=1,right=n,mid;
        while(left<=right)  //二分法
        {
            mid = (left+right)/2;
            if(check(mid,n,k)){
                left = mid+1;
            }else{
                right = mid-1;
            }
        }
        if(flag){
            printf("\n");
        }
        flag = 1;
        if(left==1){
            printf("?\n");
        }else{
            for(i = 1; i<=ans[0]; i++){
                for(j = ans[i]; j<ans[i]+left-1; j++)
                    printf("%c",s[j]);
                printf("\n");
            }
        }
    }
    return 0;
}