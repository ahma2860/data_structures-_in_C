/*
 * your program signature
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bst.h"


BSTNODE *new_node(RECORD data);
BSTNODE *extract_smallest_node(BSTNODE **rootp);

BSTNODE *bst_search(BSTNODE *root, char *key) {





	  if (root==NULL) return NULL;
	  else if (strncmp(root->data.name,key,20)==0 ) return root;
	  else if (strncmp(root->data.name,key,20)>0) {
	    return bst_search(root->left, key);
	  } else {
	    return bst_search(root->right, key);
	  }



void bst_insert(BSTNODE **rootp, RECORD data) {
	  if (*rootp == NULL) {
	    *rootp = new_node(data);
	  } else {
	    if (strncmp(data.name, (*rootp)->data.name,20)==0) {
	      return;
	    }
	    else if (strncmp(data.name, (*rootp)->data.name,20)<0)
	    bst_insert(&(*rootp)->left, data);
	    else
	    bst_insert(&(*rootp)->right, data);
	  }
}

void bst_delete(BSTNODE **rootp, char *key) {
	BSTNODE *root = *rootp, *tnp;
	  if (root == NULL) {
	    return;
	  }
	  else if(strncmp(key,root->data.name,20)==0) {
	    if(root->left == NULL && root->right == NULL) {
	      free(root);
	      *rootp = NULL;
	    }
	    else if (root->left != NULL && root->right == NULL) {
	      tnp = root->left;
	      free(root);
	      *rootp = tnp;
	    }
	    else if (root->left == NULL && root->right != NULL) {
	      tnp = root->right;
	      free(root);
	      *rootp = tnp;
	    }
	    else if( root->left!= NULL && root->right != NULL ) {
	      tnp = extract_smallest_node(&root->right);
	      tnp->left = root->left;
	      tnp->right = root->right;
	      *rootp = tnp;
	      free(root);
	    }
	    return;
	  }
	  else {
	    if(strncmp(key,root->data.name,20)<0) {
	      bst_delete(&root->left, key);
	    }
	    else {
	      bst_delete(&root->right, key);
	    }
	  }
}



BSTNODE *new_node(RECORD data) {
    BSTNODE *np = (BSTNODE *) malloc(sizeof(BSTNODE));
    if (np) {
        memcpy(np, &data, sizeof(BSTNODE));
        np->left = NULL;
        np->right = NULL;
    }
    return np;
}

BSTNODE *extract_smallest_node(BSTNODE **rootp) {
    BSTNODE *p = *rootp, *parent = NULL;
    if (p) {
        while (p->left) {
            parent = p;
            p = p->left;
        }

        if (parent == NULL)
            *rootp = p->right;
        else
            parent->left = p->right;

        p->left = NULL;
        p->right = NULL;
    }

    return p;
}

void clean_bst(BSTNODE **rootp) {
    BSTNODE *root = *rootp;
    if (root) {
        if (root->left)
            clean_bst(&root->left);
        if (root->right)
            clean_bst(&root->right);
        free(root);
    }
    *rootp = NULL;
}
