#include<iostream>
#include<stdio.h>
#include<math.h>
using namespace std;
#define IFN 999999.0

//存储结构：邻接矩阵
double adj[105][105];
struct addedge{
    int adj_v;
    float edgenum;
}closeedge[105];
struct position{
    int x;
    int y;
}ver_position[105];
int mini_adjedge(int num_village){
    float tmp=IFN;
    int vertex=-1;
    for(int i=2;i<num_village;i++){
        if((closeedge[i].edgenum<tmp)&&(closeedge[i].edgenum!=0)){
            tmp = closeedge[i].edgenum;
            vertex=i;
        }
    }
    return vertex;
}
void Prim(int num_village){
    //init closeedge,s=1
    double ans = 0;
    closeedge[1].adj_v=0;
    closeedge[1].edgenum=0;
    for(int i=2;i<num_village;i++){
        closeedge[i].adj_v=1;
        closeedge[i].edgenum=adj[i][1];
    }
    //
    int count =1;
    for(int k=2;k<num_village;k++){
        double min = IFN;
        int vertex = 0;
        for(int i=1;i<num_village;i++){
            if(min>closeedge[i].edgenum&&closeedge[i].edgenum){
                min = closeedge[i].edgenum;
                vertex = i;
            }
        }
        if(vertex){
            ans = ans + closeedge[vertex].edgenum;
            closeedge[vertex].adj_v=0;
            closeedge[vertex].edgenum = 0;
            count++;
        }
        //init again
        for(int i=2;i<num_village;i++){
            if((closeedge[i].edgenum>adj[i][vertex])&&closeedge[i].edgenum){
                closeedge[i].adj_v=vertex;
                closeedge[i].edgenum=adj[i][vertex];
            }
        }
    }
    if(count==num_village-1){
        printf("%.1lf\n",ans*100);
    }else{
        cout<<"oh!"<<endl;
    }
    return;
}

int main(){
    int num_island,num_case;
    int a,b;
    cin>>num_case;
    while(num_case--){
        cin>>num_island;
        //init
        for(int i=1;i<num_island+1;i++){
            cin>>ver_position[i].x>>ver_position[i].y;
        }
        for(int i=1;i<num_island+1;i++){
            for(int j=1;j<num_island+1;j++){
                if(i==j){
                    adj[i][j]=0;
                }else{
                    int x1 = ver_position[i].x,x2 = ver_position[j].x;
                    int y1 = ver_position[i].y,y2 = ver_position[j].y;
                    double dist = sqrt(1.0*(x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
                    if(dist<10.0||dist>1000.0){
                        adj[i][j]=adj[j][i]=IFN;
                    }else{
                        adj[i][j]=adj[j][i]=dist;
                    }
                }
            }
        }
        Prim(num_island+1);
    }
    return 0;
}


/*
#include <iostream>
#include <cmath>

using namespace std;
const double INF=0x3f3f3f3f*1.0;
struct node
{
	int x;
	int y;
};
 
double d[105][105];
int c;//岛屿个数
void prim()
{
	double sum=0,lowcast[105]={0};
	int count=1;
	for(int i=0;i<c;i++)
	{
		lowcast[i] = d[0][i];
	}
	for(int i=0;i<c-1;i++)
	{
		double min = INF;//INF是自定义常量，表无穷大
		int k = 105;
		for(int j=0;j<c;j++)
			if(min>lowcast[j]&&lowcast[j])
			{
				min = lowcast[j];
				k = j;
			}
		if(k!=105)
		{
			sum+=lowcast[k];
			lowcast[k]=0;
			count++;
		}
		for(int j=0;j<c;j++)
			if(d[j][k]<lowcast[j])
			{
				lowcast[j] = d[j][k];
			}
	}
	if(count==c)
		printf("%.1lf\n",sum*100);
	else
		printf("oh!\n");
}
int main()
{
	int t;
	cin>>t;
	while(t--)
	{
		node n[105];
		cin>>c;
		for(int i=0;i<c;i++)
			cin>>n[i].x>>n[i].y;
		for(int i=0;i<c;i++)
			for(int j=0;j<c;j++)
			{
				if(i==j)
				{		
					d[i][j]=0;
					continue;
				}
				int x1=n[i].x, x2=n[j].x;
				int y1=n[i].y, y2=n[j].y;
				double dist=sqrt(1.0*(x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
				if(dist<10.0||dist>1000.0)
					d[j][i]=d[i][j]=INF;
				else
					d[j][i]=d[i][j]=dist;
			}
			prim();
	}
	return 0;
}
*/