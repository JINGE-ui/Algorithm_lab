#include<stdio.h>

#define N 50000
#define K 100000

//X吃Y 表示为father[Y]=X
//三个并查集来表示三个种类，0~n-1：A类，n~2n-1:B，2n~3*n-1：C
//关系为A吃B，B吃C，C吃A
int father[3*N+5];
int find(int x){
    if(father[x]==x){
        return x;
    }
    return father[x]=find(father[x]);
}
void union1(int x,int y){
    int fx = find(x);
    int fy = find(y);
    if(fx!=fy){
        father[fx]=fy;
    }
}
bool same(int x,int y){
    return find(x)==find(y);
}
int num_animal,num_tell;
int main(){
    scanf("%d %d",&num_animal,&num_tell);
    int D,X,Y;
    int fake_num=0;
    for(int i=0;i<=3*num_animal;i++){
        father[i]=i;
    }
    while(num_tell--){
        scanf("%d %d %d",&D,&X,&Y);
        if(X>num_animal||Y>num_animal||X<=0||Y<=0){
            fake_num++;
            continue;
        }
        if(D==1){
            if(same(X,Y+num_animal)||same(X,Y+2*num_animal)){
                fake_num++;
            }else{
                union1(X,Y);
                union1(X+num_animal,Y+num_animal);
                union1(X+2*num_animal,Y+2*num_animal);
            }
        }
        if(D==2){
            if(X==Y){
                fake_num++;
            }else{
                if(same(X,Y)||same(X,Y+2*num_animal)){
                    fake_num++;
                }else{
                    union1(X,Y+num_animal);
                    union1(X+num_animal,Y+2*num_animal);
                    union1(X+2*num_animal,Y);
                }
            }
        }
    }
    printf("%d",fake_num);
    return 0;
}