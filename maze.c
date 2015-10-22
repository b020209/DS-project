#include <stdio.h>
#include <stdlib.h>
#define maze_size 101
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
    int vert;
    int horiz;
}offsets;
typedef struct{
    int z;
    int x;
    int y;
}mouse;
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
                        break;
                    }
                    else if(temp=='.'){
                        maze[m][i][j]=1;
                        break;
                    }
                    else if(temp=='o'){
                        maze[m][i][j]=2;
                        break;
                    }
                }
            }
        }
    }
}
void print(void){
    for(int m=0;m<2;m++){
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
    place temp;
    mouse1[top1].x=A.x;
    mouse1[top1].y=A.y;
    mouse1[top1].z=A.z;
    mouse1[top1].dir=0;
    if(!mark1[A.z][A.x][A.y]) mark1[A.z][A.x][A.y]=1;
    if(mark1[A.z][A.x][A.y+1]==0&&(maze[A.z][A.x][A.y+1]==1||maze[A.z][A.x][A.y+1]==2)){
        mouse1[top1++].dir=0;
        A.y+=1;
    }
    else if(mark1[A.z][A.x+1][A.y]==0&&(maze[A.z][A.x+1][A.y]==1||maze[A.z][A.x+1][A.y]==2)){
        mouse1[top1++].dir=1;
        A.x+=1;
    }
    else if(mark1[A.z][A.x-1][A.y]==0&&(maze[A.z][A.x-1][A.y]==1||maze[A.z][A.x-1][A.y]==2)){
        mouse1[top1++].dir=2;
        A.x-=1;
    }
    else if(mark1[A.z][A.x][A.y-1]==0&&(maze[A.z][A.x][A.y-1]==1||maze[A.z][A.x][A.y-1]==2)){
        mouse1[top1++].dir=3;
        A.y-=1;
    }
    else{
        top1--;
        A.x=mouse1[top1].x;
        A.y=mouse1[top1].y;
        A.z=mouse1[top1].z;
    }
    if(maze[A.z][A.x][A.y]==2){
        A.z=1;
        mouse1[top1].dir=0;
    }
}
void path2(void){
    place temp;
    mouse2[top2].x=B.x;
    mouse2[top2].y=B.y;
    mouse2[top2].z=B.z;
    mouse2[top2].dir=0;
    if(!mark2[B.z][B.x][B.y]) mark2[B.z][B.x][B.y]=1;
    if(mark2[B.z][B.x][B.y-1]==0&&(maze[B.z][B.x][B.y-1]==1||maze[B.z][B.x][B.y-1]==2)){
        mouse2[top2++].dir=0;
        B.y-=1;
    }
    else if(mark2[B.z][B.x-1][B.y]==0&&(maze[B.z][B.x-1][B.y]==1||maze[B.z][B.x-1][B.y]==2)){
        mouse2[top2++].dir=1;
        B.x-=1;
    }
    else if(mark2[B.z][B.x+1][B.y]==0&&(maze[B.z][B.x+1][B.y]==1||maze[B.z][B.x+1][B.y]==2)){
        mouse2[top2++].dir=2;
        B.x+=1;
    }
    else if(mark2[B.z][B.x][B.y+1]==0&&(maze[B.z][B.x][B.y+1]==1||maze[B.z][B.x][B.y+1]==2)){
        mouse2[top2++].dir=3;
        B.y+=1;
    }
    else{
        top2--;
        B.x=mouse2[top2].x;
        B.y=mouse2[top2].y;
        B.z=mouse2[top2].z;
    }
    if(maze[B.z][B.x][B.y]==2){
        B.z=0;
        mouse2[top2].dir=0;
    }
}
int main(){
    freopen("maze.txt","r",stdin);
    freopen("output.txt","w",stdout);
    input();
    print();
    A.z=0;
    A.x=1;
    A.y=1;
    B.z=1;
    B.x=maze_size-2;
    B.y=maze_size-2;
    while(1){
        path1();
        path2();
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
