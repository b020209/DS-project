#include <stdio.h>
#include <stdlib.h>
typedef struct node tree;
typedef struct node {
	int data;
	tree *left;
	tree *right;
};
tree *insert(tree*,int);
tree *delete_node(tree*,int);
tree *search_node(tree*,int);
void printInfixOrder(tree*);
void printLevelOrder(tree*);
void exit_a(void);
void binary_search_tree(void);
void treasure_hunter(void);
void travel(tree*,int,int);
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
			} else if(temp=='\n') {
				continue;
			} else {
				printf("Input error!!!\n");
			}
		}
	}
	return 0;
}
void treasure_hunter(void) {
	printf("Please input the map file:");
	char  file_name[100];
	scanf("%s",file_name);
	FILE *fptr=fopen(file_name,"r");
	if(fptr) {
		printf("Load file success.\n");

	} else {
		printf("Load file fail.\n");
		return;
	}
	tree *root=NULL;
	int temp;
	while(1){
        if(fscanf(fptr,"%d",&temp)==EOF){
            fclose(fptr);
            return;
        }
        else{
            fscanf(fptr,"%d",&temp);
            root=insert(root,temp);
        }
	}
	int key,treasure;
	printf("Please input the key location : ");
	scanf("%d",&key);
	printf("Please input the treasure location : ");
	scanf("%d",&treasure);
    int stack[10000];
    if(!search_node(root,key))
        printf("Key is not found.\n");
    if(!search_node(root,treasure))
        printf("Treasure is not found.\n");
    else{
        travel(root,key,treasure);
    }
}
void binary_search_tree(void) {
	char temp;
	int n;
	tree *root=NULL;
	while(1) {
		printf("Please enter the function number you want to use:\n(I)nsert a number.\n(D)elete a number.\n(S)earch a number.\n(P)rint in infix&level order.\n(R)eturn.\n");
		while(1) {
			scanf("%c",&temp);
			if(temp=='I') {
				printf("Enter a number : ");
				scanf("%d",&n);
				if(search_node(root,n))
					printf("%d is in the tree.\n",n);
				else
					root=insert(root,n);/* let the user insert a number i; error out when it is already existing.*/
				break;
			} else if(temp=='D') {
				printf("Enter a number to delete : ");
				scanf("%d",&n);
				if(!search_node(root,n))
					printf("%d isn't in the tree.\n",n);
				else
					root=delete_node(root,n);/*let the user delete a number i; error out when it is not existing.If the node with two child nodes is deleted, choose the smallest one on the right subtree to replace the deleted node.*/
				break;
			} else if(temp=='S') {/*search the tree; message out whether the number i is found or not.*/
				printf("Enter a number to search : ");
				scanf("%d",&n);
				if(search_node(root,n))
					printf("%d is in the tree.\n",n);
				else
					printf("%d isn't in the tree.\n",n);
				break;
			} else if(temp=='P') {
				printInfixOrder(root);/* print the whole tree in infix order (from left to right)*/
				printf("\n");
				printLevelOrder(root);/* print the whole tree in level order (from up to down)*//* print the whole tree in infix order (from left to right) and level order (from up to down)*/
				break;
			} else if(temp=='R') {
				return;
			} else if(temp=='\n') {
				continue;
			} else {
				printf("Input error!!!\n");
			}
		}
	}
}
tree *insert(tree *ptr,int n) {
	if(ptr==NULL) {
		tree *tar;
		tar=(tree*)malloc(sizeof(tree));
		tar->data=n;
		tar->left=NULL;
		tar->right=NULL;
		return tar;
	} else {
		if(ptr->data>n)
			ptr->left=insert(ptr->left,n);
		else
			ptr->right=insert(ptr->right,n);
		return ptr;
	}
}
tree *delete_node(tree *ptr,int n) {
    if(ptr==NULL) {
		return NULL;
	}
	else if(ptr->data>n)
        ptr->left=delete_node(ptr->left,n);
    else if(ptr->data<n)
        ptr->right=delete_node(ptr->right,n);
    else if(ptr->left==NULL){
        tree *temp=ptr->right;
        ptr=NULL;
        return temp;
    }
    else if(ptr->left->right==NULL){
        tree *temp=ptr->left;
        temp->right=ptr->right;
        ptr=NULL;
        return temp;
    }
    else{
        tree *temp,*tar;
        for(temp=ptr->right;temp->left->left!=NULL;temp=temp->left);
        tar=temp->left;
        temp->left=tar->left;
        tar->left=ptr->left;
        tar->right=ptr->right;
        ptr=NULL;
        return tar;
    }
    return ptr;
}
tree *search_node(tree *ptr,int n) {
	while(ptr) {
		if(n==ptr->data) return ptr;
		if(n<ptr->data)
			return search_node(ptr->left,n);
		else
			return search_node(ptr->right,n);
	}
	return NULL;
}
void printInfixOrder(tree *ptr) {
	if(ptr) {
		printInfixOrder(ptr->left);
		printf("%d ",ptr->data);
		printInfixOrder(ptr->right);
	}
}
void printLevelOrder(tree *ptr) {
	int front,rear;
	front=rear=0;
	tree *qu[1000];
	if(!ptr) {
		printf("There is no data in the tree.\n");
		return;
	}
	qu[rear++]=ptr;
	while(front!=rear) {
		ptr=qu[front++];
		if(ptr) {
			printf("%d ",ptr->data);
			if(ptr->left)
				qu[rear++]=ptr->left;
			if(ptr->right)
				qu[rear++]=ptr->right;
		}
		else break;
	}
	printf("\n");
}
void exit_a(void) {
	printf("Thank you for using.\nGoodbye!\n");
}
void travel(tree *ptr,int key,int trea){
    int top=0,top2=0;
    tree *stack1[1000],*stack2[1000];
    while(1) {
		if(key==ptr->data){
            printf("%d",ptr->data);
            break;
		}
		else if(key<ptr->data){
            stack1[top++]=ptr;
            printf("%d",ptr->data);
            ptr=ptr->left;
		}
		else if(key>ptr->data){
            stack1[top++]=ptr;
            printf("%d",ptr->data);
            ptr=ptr->right;
		}
		printf("->");
	}
    while(1) {
		if(trea==ptr->data){
            stack2[top2++]=ptr;
            break;
		}
		else if(key<ptr->data){
            stack2[top2++]=ptr;
            ptr=ptr->left;
		}
		else if(key>ptr->data){
            stack2[top2++]=ptr;
            ptr=ptr->right;
		}
	}int flag=0;
	for(int i=top;i>=0;i--){
        if(stack1[i]==stack2[i]){
            flag=i;
            break;
        }
        else printf("%d->",stack1[i]->data);
	}
	for(int j=flag;j<top2-1;j++){
	    printf("%d->",stack2[j]->data);
	}
	printf("%d\n",stack2[top2-1]->data);
}
