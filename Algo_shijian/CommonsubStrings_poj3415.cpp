#include<stdio.h>
#include<string.h>
#include<iostream>
using namespace std;
//#define rank Rank
typedef long long LL;
const int maxn = 400000 + 10;

int s[maxn];
int sa[maxn],c[maxn],t[maxn],t2[maxn];
int rank[maxn],height[maxn];

int n,k;
char a[maxn],b[maxn];
int sta[maxn][2];

void getsa(int m,int n){
    int i,*x=t,*y=t2;
    for(i=0;i<m;i++) c[i]=0;
    for(i=0;i<n;i++) c[x[i]=s[i]]++;
    for(i=1;i<m;i++) c[i]+=c[i-1];
    for(i=n-1;i>=0;i--) sa[--c[x[i]]]=i;
    for(int k=1;k<=n;k<<=1) {
        int p=0;
        for(i=n-k;i<n;i++) y[p++]=i;
        for(i=0;i<n;i++) if(sa[i]>=k) y[p++]=sa[i]-k;
        for(i=0;i<m;i++) c[i]=0;
        for(i=0;i<n;i++) c[x[y[i]]]++;
        for(i=0;i<m;i++) c[i]+=c[i-1];
        for(i=n-1;i>=0;i--) sa[--c[x[y[i]]]]=y[i];
        swap(x,y);
        p=1; x[sa[0]]=0;
        for(i=1;i<n;i++) 
            x[sa[i]]=y[sa[i]]==y[sa[i-1]] && y[sa[i]+k]==y[sa[i-1]+k]?p-1:p++;
        if(p>=n) break;
        m=p;
    }
}
void getheight(int n) {
    int i,j,k=0;
    for(i=0;i<=n;i++) rank[sa[i]]=i;
    for(i=0;i<n;i++) {  
        if(k) k--;
        j=sa[rank[i]-1];
        while(s[j+k]==s[i+k]) k++;
        height[rank[i]]=k;
    }
}

int main() {
    while(scanf("%d",&k)==1 && k) {
        scanf("%s%s",a,b);
        int lena=strlen(a),lenb=strlen(b);
        n=0;
        for(int i=0;i<lena;i++) s[n++]=a[i];
        s[n++]=1;
        for(int i=0;i<lenb;i++) s[n++]=b[i];
        s[n]=0;
        getsa('z'+1,n+1);
        getheight(n);
        
        /*
        单调栈，栈中存放两个元素分别height_top与cnt_top，
        分别表示到i为止的最小height和A串的数目。
        维护栈中元素的height从顶到底递减：
        每加入一个元素如果该元素比栈顶元素小则需要
        将tot中cnt_top个已经累计的height_top全部替换为当前元素的height（lcp是取区间最小值）
        */

        int top=0;
        LL ans=0,tot=0;
        for(int i=1;i<=n;i++) {
            if(height[i]<k) top=0,tot=0;
            else {
                int cnt=0;
                if(sa[i-1]<lena) {
                    cnt++; tot+=height[i]-k+1;
                }
                while(top && height[i]<=sta[top-1][0]) {
                    top--;
                    tot+=(height[i]-sta[top][0])*sta[top][1];
                    cnt+=sta[top][1];
                }
                sta[top][0]=height[i],sta[top++][1]=cnt;
                if(sa[i]>lena) ans+=tot;
            }
        }
        top=tot=0;
        for(int i=1;i<=n;i++) {
            if(height[i]<k) top=0,tot=0;
            else {
                int cnt=0;
                if(sa[i-1]>lena) {
                    cnt++; tot+=height[i]-k+1;
                }
                while(top && height[i]<=sta[top-1][0]) {
                    top--;
                    tot+=(height[i]-sta[top][0])*sta[top][1];
                    cnt+=sta[top][1];
                }
                sta[top][0]=height[i],sta[top++][1]=cnt;
                if(sa[i]<lena) ans+=tot;
            }
        }
        cout<<ans<<"\n";
    }
    return 0;
}    
       