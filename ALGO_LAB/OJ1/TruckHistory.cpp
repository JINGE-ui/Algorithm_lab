#include<stdio.h>
#include<iostream>
 
#define INF 999999 
using namespace std;
char derive[2005][8];
int adjMAT[2005][2005];
int close_edge[2005];
void Prim(int num_type){
    int Q = 0;
    //init,s = 0
    close_edge[0]=0;
    for(int i=1;i<num_type;i++){
        close_edge[i]=adjMAT[i][0];
    }
    int count=1;
    for(int i=0;i<num_type-1;i++){
        int min = INF,vertex = -1;
        //find a min closeedge
        for(int j=0;j<num_type;j++){
            if((min>close_edge[j])&&close_edge[j]){
                min = close_edge[j];
                vertex = j;
            }
        }
        if(vertex!=-1){
            count++;
            Q = Q + close_edge[vertex];
            close_edge[vertex]=0;
            //update close_edge
            for(int j=0;j<num_type;j++){
                if(adjMAT[j][vertex]<close_edge[j]&&close_edge[j]){
                    close_edge[j]=adjMAT[j][vertex];
                }
            }
        }
    }
    cout<<"The highest possible quality is 1/"<<Q<<'.'<<endl;
}
int dist(char a[],char b[]){
    int res=0;
    for(int i=0;i<7;i++){
        if(a[i]!=b[i]){
            res++;
        }
    }
    return res;
}
int main(){
    int num_type;
    while(cin>>num_type,num_type){
        for(int i=0;i<num_type;i++){
            cin>>derive[i];
        }
        //init adjMAT:
        for(int i=0;i<num_type;i++){
            for(int j=i;j<num_type;j++){
                if(i==j){
                    adjMAT[i][j]=0;
                }else{
                    adjMAT[i][j]=adjMAT[j][i]=dist(derive[i],derive[j]);
                }
            }
        }
        Prim(num_type);
    }
return 0;

}