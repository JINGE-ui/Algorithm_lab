#include<stdio.h>
#include<string.h> 
#include<vector>
#include<map>
#include<algorithm>

#define MAXP 600

using namespace std;

//fa[x]=y,val[x]=1表示x与y是异类，val[x]=0表同类 
int father[MAXP+5],val[MAXP+5];
bool is_treenode[MAXP+5];  //对应下标是否是树根
vector <int> divine;   //升序存储divine tribes 
struct tree{
	int numa,numb;  ///对应下标作为连通分量，val=0计入numa，val=1计入numb 
	vector <int> a;
	vector <int> b;
}treenode[MAXP+5];
map<int,int> mymap;  //树根到连通分支(1~n)的映射 
int choose[MAXP+5];  //表示第i个连通分量时选择0类还是1类
int dp[MAXP+5][MAXP+5];  //dp[i][j]=dp[i-1][j-ai]+dp[i-1][j-bi]，表从1~i个连通分支选出j个同一类的方案数 

int find(int x){
	if(father[x]==x){
		return x;
	}
	int t = father[x];
	father[x]=find(t);
	val[x]=(val[x]+val[t])%2;
	return father[x];
}
void UNION(int x,int y,int value){
	int fx = find(x);
	int fy = find(y);
	if(fx!=fy){
		father[fx]=fy;
		val[fx]=(val[x]+val[y]+value)%2;   //!!!!!!!!!!!!!!!!
	}
}

int main(){
    int n,p1,p2;
    int x,y;
    char says[10];
    while((scanf("%d %d %d",&n,&p1,&p2),n+p1+p2)){
        if(n==0){
            if(p1==0){
                printf("end\n");
                continue;
            }
            if(p2==0){
                for(int i=1;i<=p1;i++){
                    printf("%d\n",i);
                }
                printf("end\n");
                continue;
            }
            printf("no\n");
            continue;
        }
    	//init father[N] and val[N]
    	for(int i=1;i<=p1+p2;i++){
    		father[i]=i;
    		val[i]=0;
		}
        for(int i=0;i<n;i++){
            scanf("%d %d %s",&x,&y,says);
            if(x!=y){ //x=y时无法判断，不作考虑 
            	if(says[0]=='n'){  //x和y不同类 
            		UNION(x,y,1);
				}else{  //同类 
					UNION(x,y,0);
				}
			}
        }
        //init is_treenode numa numb
        memset(is_treenode,false,sizeof(is_treenode));
        mymap.erase(mymap.begin(),mymap.end());
        for(int i=0;i<=p1+p2;i++){
        	treenode[i].numa = treenode[i].numb = 0;
        	treenode[i].a.clear();
        	treenode[i].b.clear();
		}
        
        //caculate numbers of trees
        int num_trees=0;  //树的个数 
        for(int i=1;i<=p1+p2;i++){
        	int node = find(i);
        	if(!is_treenode[node]){   //node未曾作为树根 
        		is_treenode[node]=true;
        		num_trees++;
        		mymap[node]=num_trees;
			}
			int cnt = mymap[node];
			if(val[i]==0){
				treenode[cnt].numa++;
				treenode[cnt].a.push_back(i);
			}else{
				treenode[cnt].numb++;
				treenode[cnt].b.push_back(i);
			}
		}
		
		memset(dp,0,sizeof(dp));
		dp[0][0]=1;
		for(int i=1;i<=num_trees;i++){
			for(int j=0;j<=p1;j++){
				if(j>=treenode[i].numa){
					dp[i][j]=dp[i-1][j-treenode[i].numa];
				}
				if(j>=treenode[i].numb){
					dp[i][j]+=dp[i-1][j-treenode[i].numb];
				}
			}
		}
		if(dp[num_trees][p1]==1){  //为1时表示唯一解 
			int tmp = p1;
			memset(choose,-1,sizeof(choose));
			int num0=0,num1=0;  //0类和1类的数目 
			for(int k=num_trees;k>=1;k--){  //倒推来确定choose 
				if(dp[k][tmp]==dp[k-1][tmp-treenode[k].numa]){
					choose[k]=0;  //第k个连通 分量选择了0类 
					tmp -= treenode[k].numa;
				}else if(dp[k][tmp]==dp[k-1][tmp-treenode[k].numb]){
					choose[k]=1;
					tmp -= treenode[k].numb;
				}
			} 
			divine.clear();
			int def = ((num0==p1)?0:1);  //
			for(int k=1;k<=num_trees;k++){
				if(choose[k]==0){
                    divine.insert(divine.end(),treenode[k].a.begin(),treenode[k].a.end());
                }
                else{
                    divine.insert(divine.end(),treenode[k].b.begin(),treenode[k].b.end());
                }
			}
			sort(divine.begin(),divine.begin()+p1);
			for(int i=0;i<p1;i++){
				printf("%d\n",divine[i]);
			}
			printf("end\n");
		}else{
			printf("no\n");
		}
    }
    return 0;
}