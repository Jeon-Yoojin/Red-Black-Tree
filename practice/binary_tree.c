#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode{
    int key;
    struct TreeNode* left, *right;
} TreeNode;

TreeNode *search(TreeNode *node, int key){
    if (node == NULL) return NULL;
    if (key == node->key) return node;
    else if (key < node->key) return search(node->left, key);
    else return search(node->right, key);
}

TreeNode *new_node(int item){
    TreeNode *temp = (TreeNode *)malloc(sizeof(TreeNode));
    temp->key = item;
    temp->left = NULL;
    temp->right = NULL;
    return temp;
}

TreeNode *insert_node(TreeNode *node, int key){
    if (node == NULL) return new_node(key);
    if (key < node->key)
        node->left = insert_node(node->left, key);
    else if (key > node->key)
        node->right = insert_node(node->right, key);
    
    return node;
}

TreeNode *delete_node(TreeNode *root, int key){ // key 노드 삭제 후 루트 노드 반환
    if (root == NULL) return root;
    if (key < root->key)
        root->left = delete_node(root->left, key);
    else if (key > root->key)
        root->right = delete_node(root->right, key);
    else{ // 현재 삭제해야 하는 노드를 찾은 경우
        if (root->left == NULL){
            TreeNode *temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL){
            TreeNode *temp = root->left;
            free(root);
            return temp;
        }
        
        // 나보다 작은 노드를 찾기
        TreeNode *temp = min_value_node(root->right);
        root->key = temp->key;
        root->right = delete_node(root->right, temp->key);
        // 그 노드를 삭제한 노드의 자리로 
    }
    return root;
}

int main() {
    // 이진 탐색 트리 생성
    TreeNode *root = (TreeNode*)malloc(sizeof(TreeNode));
    TreeNode *n1 = (TreeNode*)malloc(sizeof(TreeNode));
    TreeNode *n2 = (TreeNode*)malloc(sizeof(TreeNode));
    TreeNode *n3 = (TreeNode*)malloc(sizeof(TreeNode));
    TreeNode *n4 = (TreeNode*)malloc(sizeof(TreeNode));

    root->key = 3;
    root->left = n1;
    root->right = n2;

    n1->key = 1;
    n1->left = NULL;
    n1->right = NULL;

    n2->key = 5;
    n2->left = n3;
    n2->right = n4;

    n3->key = 4;
    n3->left = NULL;
    n3->right = NULL;

    n4->key = 6;
    n4->left = NULL;
    n4->right = NULL;

    TreeNode *result = search(root, 4);
    if (result == NULL) printf("찾는 값이 없습니다.");
    else printf("찾는 값 %d이(가) 있습니다.", result->key);

    return 0;
}