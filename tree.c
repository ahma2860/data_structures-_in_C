/*
 * your program signature
 */

#include <stdio.h>
#include <stdlib.h>
#include "queue_stack.h"
#include "tree.h"

int max(int a, int b){
	if (a>=b) return a;
	else return b;
}

int node_count(TNODE *root) {
if (root == NULL) {return 0;}
return 1 + node_count(root->left) + node_count(root->right);
}

int height(TNODE *root){
	if (root == NULL) return 0;
	return 1+max(height(root->left),height(root->right));
}

TPROPS tree_property(TNODE *root) {
	TPROPS new;
	new.order=node_count(root);
	new.height=height(root);
	return new;
}

void preorder(TNODE *root) {
	if (root) {
	printf("%c ", root->data);
	preorder(root->left);
	preorder(root->right);
	}
}

void inorder(TNODE *root) {
	if (root) {
	inorder(root->left);
	printf("%c ", root->data);
	inorder(root->right);
	}
}

void postorder(TNODE *root) {
	if (root) {
	postorder(root->left);
	postorder(root->right);
	printf("%c ", root->data);
	}
}

void bforder(TNODE *root) {
	TNODE *r = NULL;
	if (root ) {
	QUEUE queue = {0}; // auxiliary queue for BST
	enqueue(&queue, root);
	while (queue.front) {
	TNODE *tnp = (TNODE*) dequeue(&queue);
	printf("%c",tnp->data);
	if (tnp->left){enqueue(&queue,tnp->left);}
	if(tnp->right){enqueue(&queue,tnp->right);}
	}
	clean_queue(&queue);
	}
}

TNODE *bfs(TNODE *root, char val) {
	TNODE *r = NULL;
	if (root ) {
	QUEUE queue = {0}; // auxiliary queue for BST
	enqueue(&queue, root);
	while (queue.front) {
	TNODE *tnp = (TNODE*) dequeue(&queue);
	if (tnp->data==val) {
	r=tnp;
	break;
	}
	if (tnp->left){enqueue(&queue,tnp->left);}
	if(tnp->right){enqueue(&queue,tnp->right);}
	}
	clean_queue(&queue);
	}
	return r;
}

TNODE *dfs(TNODE *root, char val) {
	TNODE *r = NULL;
	if (root) {
	STACK stack = {0};
	push(&stack, root);
	while(stack.top){
	TNODE *p = (TNODE *) pop(&stack);
	if (val==p->data)
	{
	r=p;
	break;
	}
	if (p->left){push(&stack,p->left);}
	if(p->right){push(&stack,p->right);}
	}
	clean_stack(&stack);
	}
	return r;
	}


// the following functions are given, need to add to your program.

//TNODE *new_node(char val) {
//    TNODE *np = (TNODE *) malloc(sizeof(TNODE));
//    if (np != NULL) {
//        np->data = val;
//        np->left = NULL;
//        np->right = NULL;
//    }
//    return np;
//}

void clean_tree(TNODE **rootp) {
    TNODE *p = *rootp;
    if (p) {
        if (p->left)
            clean_tree(&p->left);
        if (p->right)
            clean_tree(&p->right);
        free(p);
    }
    *rootp = NULL;
}

void insert_tree(TNODE **rootp, char val) {
    if (*rootp == NULL) {
        *rootp = new_node(val);
    } else {
        QUEUE queue = { 0 };
        TNODE *p;
        enqueue(&queue, *rootp);
        while (queue.front) {
            p = dequeue(&queue);
            if (p->left == NULL) {
                p->left = new_node(val);
                break;
            } else {
                enqueue(&queue, p->left);
            }

            if (p->right == NULL) {
                p->right = new_node(val);
                break;
            } else {
                enqueue(&queue, p->right);
            }
        }
    }

}
