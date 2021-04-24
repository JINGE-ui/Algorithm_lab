#include<iostream>
#define MIN(A,B)  ((A<B)?(A):(B))
#define MAX(A,B)  ((A>B)?(A):(B))

using namespace std;
typedef long long ll;

#define INF 9999999999   //WA排除：INF>1e9
ll minw[105][100030];
int main(){
    ll sum_Weight,num_items,w,v;  //过大
    scanf("%lld %lld",&num_items,&sum_Weight);
    ll i=1;
    ll tmp = num_items;
    for(int j=0;j<1e5+30;j++){
        minw[0][j]=INF;
    }
    minw[0][0]=0;
    //minnw[i][j] 1~i个背包达到j的价值所需的最小重量
    while(num_items--){
        scanf("%lld %lld",&w,&v);
        //空间优化为一维  minw[j]
        /*
        for i=1->NUM:
			for j=max_value->0:
				minw[j]=MIN(minw[j-1],minw[j-1]+w[i])
        */ 
        for(int j=0;j<1e5+30;j++){
            if(j<v){
                minw[i][j]=minw[i-1][j];
            }else{
                minw[i][j]=MIN(minw[i-1][j],minw[i-1][j-v]+w);
            }
        }
        i++;
    }
    if(sum_Weight==0||tmp==0){
        cout<<0;
        return 0;
    }
   for(int i=1e5+20;i>0;i--){
       if(minw[tmp][i]<=sum_Weight){
           printf("%d",i);
           return 0;
       }
   }
    printf("%d",0);
    return 0;
}
