#include <iostream>
#include <stdio.h>
using namespace std;

int p[1008];
int ranknum[1008];

int find(int x){
    int r = x;
    while(p[r]!=r){
        r = p[r];
    }
    int i=x,j;
    //路径压缩
    while(i!=r){
        j=p[i];
        p[i]=r;
        i=j;
    }
    return r;
}
int join(int x,int y){
    int fx = find(x),fy=find(y);
    if(fx!=fy){
        if(ranknum[fx]>ranknum[fy]){
            p[fy]=fx;
            ranknum[fx]+=ranknum[fy];
        }else{
            p[fx]=fy;
            ranknum[fy]+=ranknum[fx];
        }
        return 1;
    }else{
        return 0;
    }
}
int main(){
    int num_city,num_road;
    int a,b;
    int ans;
    while(scanf("%d",&num_city),num_city){
        scanf("%d",&num_road);
        //init
        for(int i=1;i<num_city+1;i++){
            p[i]=i;
            ranknum[i]=1;
        }
        ans = num_city-1;
        while(num_road){
            cin>>a>>b;
            if(join(a,b)){
                ans--;
            }
            num_road--;
        }
        cout<<ans<<endl;
    }
    return 0;
}