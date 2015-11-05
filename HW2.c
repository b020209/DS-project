#include <stdio.h>
#include <stdlib.h>
typedef struct node *tree;
typedef struct node{
	int data;
	tree left;
	tree right;
};
void insert(void);
void delete_node(void);
void search_node(void);
void printInfixOrder(void);
void printLevelOrder(void);
void exit_a(void);
void print(void);
void binary_search_tree(void);
void treasure_hunter(void);
int main() {
	char temp,flag=0;
	while(flag==0) {
		printf("Enter the function you want to use:\n(B)inary Search Tree.\n(T)reasure Hunter.\n(E)xit.\n");
		while(1) {
			scanf("%c",&temp);
			if(temp=='B') {
				binary_search_tree();
				break;
			} else if(temp=='T') {
				treasure_hunter();
				break;
			} else if(temp=='E') {
				exit_a();
				flag=1;
				break;
			}
		}
	}
	return 0;
}
void treasure_hunter(void) {
    printf("Please input the map file:");
}
void binary_search_tree(void) {
	char temp;
	while(1) {
		printf("Please enter the function number you want to use:\n(I)nsert a number.\n(D)elete a number.\n(S)earch a number.\n(P)rint in infix&level order.\n(R)eturn.\n");
		while(1) {
			scanf("%c",&temp);
			if(temp=='I') {
				insert();/* let the user insert a number i; error out when it is already existing.*/
				break;
			} else if(temp=='D') {
				delete_node();/*let the user delete a number i; error out when it is not existing.If the node with two child nodes is deleted, choose the smallest one on the right subtree to replace the deleted node.*/
				break;
			} else if(temp=='S') {
				search_node();/*search the tree; message out whether the number i is found or not.*/
				break;
			}
			else if(temp=='P'){
				print();/* print the whole tree in infix order (from left to right) and level order (from up to down)*/
				break;
			}
			else if(temp=='R'){
                return;
			}
		}
	}
}
void insert(void) {
    int n;
    printf("Enter a number : ");
    scanf("%d",&n);
    
}
void delete_node(void) {
	int n;
    printf("Enter a number to delete : ");
    scanf("%d",&n);
}
void search_node(void) {
    int n;
    printf("Enter a number to search : ");
    scanf("%d",&n);
}
void print(void){
	printInfixOrder();/* print the whole tree in infix order (from left to right)*/
	printLevelOrder();/* print the whole tree in level order (from up to down)*/
}
void printInfixOrder(void){

}
void printLevelOrder(void){

}
void exit_a(void) {
    printf("Thank you for using.\nGoodbye!\n");
}
