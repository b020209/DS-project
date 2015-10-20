#include <stdio.h>
#include <stdlib.h>
#define maze_size 5
#define FALSE 0
#define EXIT_COL maze_size-2
#define EXIT_ROW maze_size-2
#define true 1
int maze[2][maze_size][maze_size];// 0 for wall ,1 for road ,2 for stairs ,3 for path ,4 for restricted
int top=0;
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
offsets move[5];
place stack[10000];
void path(void);
place pop(void){
    return stack[top--];
}
void push(place item){
    stack[++top]=item;
}
int main(){
    memset(maze,0,sizeof(maze));
    char temp;
    place mouse1,mouse2;
    for(int m=0;m<2;m++){
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
    printf("\n");
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
        printf("\n");
    }
    //walk(1,1,0);
    printf("\n");
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
                else if(maze[m][i][j]==3) {
                    printf("x");
                }
                else if(maze[m][i][j]==4) {
                    printf("*");
                }
            }
            printf("\n");
        }
        printf("\n");
    }
    return 0;
}
void path(void){
    int i,row,col,floor,next_floor,next_row,next_col,dir,found=FALSE;
    place pos;
    stack[0].x=1;
    stack[0].y=1;
    stack[0].dir=1;
    while(top>-1&&!found){
        pos=pop();
        row=pos.x;
        col=pos.y;
        dir=pos.dir;
        while(dir<8&&!found){
            next_row=row+move[dir].vert;
            next_col=col+move[dir].horiz;
            if(next_row==EXIT_ROW&&next_col==EXIT_COL){
                found=true;
            }
            else if(!maze[next_row][next_col]&&!mark[next_row][next_col]){
                mark[next_row][next_col]=1;
                pos.x=row;
                pos.y=col;
                pos.dir=++dir;
                push(pos);
                row=next_row;
                col=next_col;
                dir=0;
            }
            else dir++;
        }
    }
    if(found){
        printf("The path is:\n");
        printf("row col\n");
        for(i=0;i<top;i++){
            printf("%2d%5d",stack[i].row,stack[i].col);
        }
        printf("%2d%5d\n",row,col);
        printf("%2d%5d\n",EXIT_ROW,EXIT_COL);
    }
    else printf("The maze does not have a path\n");
}
/*void walk(int a,int b,int  c){
    if(a==maze_size-2&&b==maze_size-2) return;
    if(maze[a+1][b][c]==1){
         maze[a+1][b][c]=3;
         walk(a+1,b,c);
    }
    if(maze[a-1][b][c]=1){
        maze[a-1][b][c]=3;
        walk(a-1,b,c);
    }
    if(maze[a][b-1][c]==1){
         maze[a][b-1][c]=3;
         walk(a,b-1,c);
    }
    if(maze[a][b+1][c]==1){
        maze[a][b+1][c]=3;
        walk(a,b+1,c);
    }
    if(maze[a-1][b-1][c]==1){
        maze[a-1][b+1][c]=3;
        walk(a,b+1,c);
    }
    if(maze[a-1][b+1][c]==1){
        maze[a-1][b+1][c]=3;
        walk(a-1,b+1,c);
    }
    if(maze[a+1][b-1][c]==1){
        maze[a+1][b-1][c]=3;
        walk(a+1,b-1,c);
    }
    if(maze[a+1][b+1][c]==1){
        maze[a+1][b+1][c]=3;
        walk(a+1,b+1,c);
    }
}*/
