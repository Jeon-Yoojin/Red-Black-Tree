#include "rbtree.h"
#include <stdio.h>
void inorderTraversalPrint(node_t *root) {
    if (root->left == NULL && root->right == NULL) return;
    inorderTraversalPrint(root->left);
    printf("%d ", root->key);
    inorderTraversalPrint(root->right);
}
int main(int argc, char *argv[]) {
    rbtree *tree = new_rbtree();
    node_t *t = rbtree_insert(tree, 10);
     t = rbtree_insert(tree, 5);
     t = rbtree_insert(tree, 8);
     t = rbtree_insert(tree, 34);
     t = rbtree_insert(tree, 67);
     t = rbtree_insert(tree, 23);
     t = rbtree_insert(tree, 156);
     t = rbtree_insert(tree, 24);
     t = rbtree_insert(tree, 2);
     t = rbtree_insert(tree, 12);
     t = rbtree_insert(tree, 24);
     t = rbtree_insert(tree, 36);
     t = rbtree_insert(tree, 990);
     t = rbtree_insert(tree, 25);
    inorderTraversalPrint(t);
    printf("\n");
    //node_t *x = rbtree_min(tree); //최소값 확인
    //printf("%d\n",x->key);
    // node_t *x = rbtree_max(tree); //최댓값 확인
    // printf("%d\n",x->key);
     rbtree_erase(tree, rbtree_find(tree,12));
     rbtree_erase(tree, rbtree_find(tree,8));
    //rbtree_erase(tree, rbtree_find(tree,34));
    inorderTraversalPrint(t);
    int *arr = (int *)malloc(sizeof(int)*14); // 동적으로 할당해야함~
    rbtree_to_array(tree,arr,14);
    //int n = sizeof(arr) / sizeof(int);
    printf("\n");
    for(int i =0; i<14; i++){
        printf("%d ",arr[i]);
    }
}
// raw
// #include "rbtree.h"
// int main(int argc, char *argv[]) {
// }
//1st test main
    // rbtree *tree = new_rbtree();
    // node_t *t = rbtree_insert(tree, 30);
    // t = rbtree_insert(tree, 20);
    // t = rbtree_insert(tree, 10);
    // t = rbtree_insert(tree, 5);
    // t = rbtree_insert(tree, 65);
    // inorderTraversalPrint(t);
    // printf("%d", tree->root->key);
    // printf(" max : %d, min : %d\n", rbtree_max(tree)->key, rbtree_min(tree)->key);
    // rbtree_erase(tree, t -> right -> right);
    // inorderTraversalPrint(t);
    // return 0;
