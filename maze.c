#include <stdio.h>
#include <stdlib.h>
#define maze_size 5
#define FALSE 0
#define EXIT_COL1 maze_size-2
#define EXIT_ROW1 maze_size-2
#define EXIT_COL2 1
#define EXIT_ROW2 1
#define true 1
int maze[2][maze_size][maze_size],mark1[2][maze_size][maze_size],mark2[2][maze_size][maze_size];// 0 for wall ,1 for road ,2 for stairs ,3 for path
int top1=0,top2=0;
typedef struct{
    int z;
    int x;
    int y;
    int dir;
}place;
typedef struct{
    int stairs;
    int vert;
    int horiz;
}offsets;
typedef struct{
    int z;
    int x;
    int y;
}mouse;
offsets move1[5],move2[5];
place mouse1[10000],mouse2[10000];
mouse A,B;
int A_MEET_B(void){
    if(A.x==B.x&&A.y==B.y&&A.z==B.z) return 1;
    return 0;
}
void print_place(void){
    printf("ratA(%d,%d,%d)\n",A.z,A.x,A.y);
    printf("ratB(%d,%d,%d)\n",B.z,B.x,B.y);
}
void input(void){
    char temp;
    int a;
    for(int m=0;m<2;m++){
        scanf("%d",&a);
        for(int i=0;i<maze_size;i++){
            for(int j=0;j<maze_size;j++){
                while(1){
                    scanf("%c",&temp);
                    if(temp=='X') {
                        maze[m][i][j]=0;
                        mark1[m][i][j]=0;
                        mark2[m][i][j]=0;
                        break;
                    }
                    else if(temp=='.'){
                        maze[m][i][j]=1;
                        mark1[m][i][j]=1;
                        mark2[m][i][j]=1;
                        break;
                    }
                    else if(temp=='o'){
                        maze[m][i][j]=2;
                        if(m==0){
                            mark1[m][i][j]=2;
                            mark2[m][i][j]=1;
                        }
                        else if(m==1){
                            mark1[m][i][j]=1;
                            mark2[m][i][j]=2;
                        }
                        break;
                    }
                }
            }
        }
    }
}
void print(void){
    for(int m=0;m<2;m++){
        printf("\n");
        for(int i=0;i<maze_size;i++){
            for(int j=0;j<maze_size;j++){
                if(maze[m][i][j]==0) {
                    printf("X");
                }
                else if(maze[m][i][j]==1) {
                    printf(".");
                }
                else if(maze[m][i][j]==2) {
                    printf("o");
                }
            }
            printf("\n");
        }
    }
}
int A_arrive(void){
    if(A.x==EXIT_ROW1&&A.y==EXIT_COL1&&A.z==1) return 1;
    return 0;
}
int B_arrive(void){
    if(B.x==EXIT_ROW2&&B.y==EXIT_COL2&&B.z==0) return 1;
    return 0;
}
void path1(void){

}
int main(){
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    input();
    print();
    while(1){
        //path1();
        //path2();
        if(A_arrive()){
            printf("rats didn't encounter each other in this maze\n");
            break;
        }
        else if(B_arrive()){
            printf("ratA(%d,%d,%d)\n",A.z,A.x,A.y);
            printf("rats didn't encounter each other in this maze\n");
            break;
        }
        else if(A_MEET_B()){
            printf("ratA(%d,%d,%d)\n",A.z,A.x,A.y);
            printf("rats encounter each other in (%d,%d,%d)",B.z,B.x,B.y);
            break;
        }
        print_place();
    }
    return 0;
}
