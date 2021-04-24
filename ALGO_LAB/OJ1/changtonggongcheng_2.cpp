#include<iostream>
#include<stdio.h>

using namespace std;
#define IFN 999999
//存储结构：邻接矩阵
int adj[105][105];
struct addedge{
    int adj_v;
    int edgenum;
}closeedge[105];
int mini_adjedge(int num_village){
    int tmp=IFN;
    int vertex=-1;
    for(int i=1;i<num_village;i++){
        if((closeedge[i].edgenum<tmp)&&(closeedge[i].edgenum!=0)){
            tmp = closeedge[i].edgenum;
            vertex=i;
        }
    }
    return vertex;
}
void Prim(int num_village){
    //init closeedge,s=1
    int ans = 0;
    closeedge[1].adj_v=0;
    closeedge[1].edgenum=0;
    for(int i=2;i<num_village;i++){
        closeedge[i].adj_v=1;
        closeedge[i].edgenum=adj[i][1];
    }
    //
    for(int k=2;k<num_village;k++){
        int vertex = mini_adjedge(num_village);
        if(vertex==-1){
            cout<<"not exit a MST";
            exit(1);
        }
        ans = ans + closeedge[vertex].edgenum;
        closeedge[vertex].adj_v=0;
        closeedge[vertex].edgenum=0;
        //init again
        for(int i=2;i<num_village;i++){
            if((closeedge[i].adj_v!=0)&&(closeedge[i].edgenum>adj[i][vertex])){
                closeedge[i].adj_v=vertex;
                closeedge[i].edgenum=adj[i][vertex];
            }
        }
    }
    cout<<ans<<endl;
    return;
}

int main(){
    int num_village;
    int weight,a,b;
    while(cin>>num_village,num_village){  //1<n<27
        for(int i=1;i<num_village+1;i++){
            for(int j=1;j<num_village+1;j++){
                adj[i][j]=IFN;
            }
        }
        int num_dis = (num_village-1)*(num_village)/2;
        while(num_dis--){
            cin>>a>>b>>weight;
            adj[a][b]=adj[b][a]=weight;
        }
        //init over
        Prim(num_village+1);
    }
    return 0;
}