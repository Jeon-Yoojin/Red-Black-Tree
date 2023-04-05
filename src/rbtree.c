#include "rbtree.h"
#include <stdio.h>
#include <stdlib.h>

/* 확인 완료 */
rbtree *new_rbtree(void) {
  rbtree *p = (rbtree *)calloc(1, sizeof(rbtree));
  // TODO: initialize struct if needed
  // nil 노드 만들기
  p->nil = (node_t *)calloc(1, sizeof(node_t));
  // 루트 노드가 nil을 가리키도록 하기
  p->root = p->nil;
  // nil 노드가 검은색이어야 하므로, 검은색으로 초기화
  p->nil->color = RBTREE_BLACK;
  return p;
}

/* 확인 완료 */
void left_rotate(rbtree *t, node_t *x) {
  node_t *y = x->right;
  // y의 left 노드를 새로운 루트 노드의 right에 연결
  x->right = y->left;
  if (y->left != t->nil){
    y->left->parent = x;
  }
  // y와 x의 parent를 연결하는 과정
  y->parent = x->parent;
  if (x->parent == t->nil){
    t->root = y;
  }
  else if (x == x->parent->left) {
    x->parent->left = y;
  }
  else{
    x->parent->right = y;
  }
  // y를 새로운 루트 노드로 만드는 과정
  y->left = x;
  x->parent = y;
}

/* 확인 완료 */
void right_rotate(rbtree *t, node_t *y) {
  node_t *x = y->left;
  y->left = x->right;
  if (x->right != t->nil){
    x->right->parent = y;
  }
  x->parent = y->parent;
  if (y->parent == t->nil){
    t->root = x;
  }
  else if (y == y->parent->left){
    y->parent->left = x;
  }
  else{
    y->parent->right = x;
  }
  x->right = y;
  y->parent = x;
}

/* 확인 완료 */
void traverse_to_delete(rbtree *t, node_t *p) {
  // 내가 만든 노드들을 하나씩 순회하면서 free
  if (p == t->nil) return;
  traverse_to_delete(t, p->left);
  traverse_to_delete(t, p->right);
  free(p);
}

/* 확인 완료 */
void delete_rbtree(rbtree *t) {
  // TODO: reclaim the tree nodes's memory
  traverse_to_delete(t, t->root);
  // 트리에서 할당한 동적 메모리 free
  free(t->nil);
  free(t);
}

/* 확인 완료, TODO: 주석 달기*/
void rbtree_insert_fixup(rbtree *t, node_t *z){
  while (z->parent->color == RBTREE_RED){
    // y 지정
    if (z->parent == z->parent->parent->left) {
      node_t *y = z->parent->parent->right;
      // y노드 색이 red일 경우,
      if (y->color == RBTREE_RED){
        // z의 부모 색을 Black으로 바꾸기
        z->parent->color = RBTREE_BLACK;
        // y의 색을 Black으로 바꾸기
        y->color = RBTREE_BLACK;
        // z의 할아버지 색을 Red로 바꾸기
        z->parent->parent->color = RBTREE_RED;
        z = z->parent->parent;
      }
      else if (z == z->parent->right){
        z = z->parent;
        left_rotate(t, z);
      }
      else{
        // z의 부모 색 Black으로 바꾸기
        z->parent->color = RBTREE_BLACK;
        // z의 할아버지 노드 Red로 바꾸기
        z->parent->parent->color = RBTREE_RED;
        // z의 부모 노드를 기준으로 Right Rotate
        right_rotate(t, z->parent->parent);
      }
    }
    else{
      node_t *y = z->parent->parent->left;
      if (y->color == RBTREE_RED){
        z->parent->color = RBTREE_BLACK;
        y->color = RBTREE_BLACK;
        z->parent->parent->color = RBTREE_RED;
        z = z->parent->parent;
      }
      else if (z == z->parent->left){
        z = z->parent;
        right_rotate(t, z);
      }
      else{
        z->parent->color = RBTREE_BLACK;
        z->parent->parent->color = RBTREE_RED;
        left_rotate(t, z->parent->parent);
      }
    }
  }
  t->root->color = RBTREE_BLACK;
}

/* 확인 완료 */
node_t *rbtree_insert(rbtree *t, const key_t key) {
  // TODO: implement insert
  // 일단 들어 갈 위치를 찾기
  node_t *z = (node_t *)calloc(1, sizeof(node_t));

  node_t *y = t->nil;
  node_t *x = t->root;
  // 루트 노드부터 내려오면서 올바른 자리를 찾는다.
  while(x != t->nil) {
    y = x;
    if (key < x->key) x = x->left;
    else x = x->right;
  }
  // y로부터 left든 right든 떨어져 나온 게 z이다. parent 연결 작업
  z->parent = y;
  // parent가 nil인 경우, z가 루트가 되어야 한다.
  if (y == t->nil) t->root = z;
  // parent의 왼쪽 자식이 되어야 하는지, 오른쪽 자식이 되어야 하는지 확인 후 삽입.
  else if (key < y->key) y->left = z;
  else y->right = z;
  // 해당 위치에 값이 key이고 색이 red인 노드를 넣기
  z->left = t->nil;
  z->right = t->nil;
  z->key = key;
  z->color = RBTREE_RED;
  // RB-Tree 조건 만족하지 않으면 만족하도록 restruct
  rbtree_insert_fixup(t, z);
  return t->root;
}

/* 확인 완료 */
node_t *rbtree_find(const rbtree *t, const key_t key) {
  // TODO: implement find
  // 이분 탐색의 아이디어를 적용한다.
  // 해당 루트 노드와 같으면 루트 노드 리턴,
  node_t *p = t->root;
  while (p != t->nil){
    if (p->key == key) return p;
    // 루트 노드보다 크면 오른쪽 subtree, 작으면 왼쪽 subtree에서의 탐색을 반복한다.
    else if (p->key < key){
      p = p->right;
    }
    else if(p->key > key){
      p = p->left;
    }
  }
  // 만약 찾는 노드가 없으면 NULL을 리턴해야 한다. (nil 말고 NULL)
  return NULL;
}

/* 확인 완료 */
node_t *rbtree_min(const rbtree *t) {
  // TODO: implement find
  // RB Tree는 기본적으로 BST의 성질을 가지므로, BST에서 최소값을 뽑는 것과 같은 과정을 수행한다.
  // 루트 노드부터 시작하여,
  node_t *p = t->root;
  while (p->left != t->nil){
  // 노드가 nil 노드일 때까지 왼쪽 자식 노드로 간다.
    p = p->left;
  // 해당 노드의 값을 리턴한다.
  }
  return p;
}

/* 확인 완료 */
node_t *rbtree_max(const rbtree *t) {
  // TODO: implement find
  // BST에서 최댓값을 뽑는 것과 같은 과정을 수행한다.
  // 루트 노드부터 시작하여,
  node_t *p = t->root;
  while (p->right != t->nil){
  // 두 자식 노드가 nil 노드일 때까지 오른쪽 자식 노드로 간다.
    p = p->right;
  // 해당 노드의 값을 리턴한다.
  }
  return p;
}

/* 확인 완료 */
// u 자리에 v를 루트 노드로 갖는 서브트리를 이식
void transparent(rbtree *t, node_t *u, node_t *v) {
  // 루트 노드 자리로 v를 루트 노드로 갖는 서브트리가 들어갈 경우
  if (u->parent == t->nil) t->root = v;
  // v 서브트리가 왼쪽 자식 자리로 들어가는 경우
  else if(u->parent->left == u) u->parent->left = v;
  // v 서브트리가 오른쪽 자식 자리로 들어가는 경우
  else u->parent->right = v;
  // v의 parent도 연결해주기
  v->parent = u->parent;
}

/* 확인 완료 */
node_t *min_successor(rbtree *t, node_t *p) {
  // p보다 큰, 가장 작은 노드를 찾는다.
  while (p->left != t->nil) {
    p = p->left;
  }
  return p;
}

/* 확인 완료 & TODO: 주석 달기, 영상 방법대로(조금 다름) 해보기*/
void rbtree_delete_fixup(rbtree *t, node_t *x) {
  node_t *w = NULL;
  // x가 root이고 color가 Black이 될 때까지 반복
  while(x != t->root && x->color == RBTREE_BLACK){
    // x가 왼쪽 자식인 경우
    if (x == x->parent->left) {
      // w: x의 형제 노드 (x가 왼쪽 자식이니까, w는 오른쪽 자식)
      w = x->parent->right;
      // case D - 형제 노드의 색이 red인 경우
      if (w->color == RBTREE_RED) {
        // 부모의 색과 형제의 색 바꾸기
        w->color = RBTREE_BLACK;
        x->parent->color = RBTREE_RED;
        // 부모를 기준으로 왼쪽 회전
        left_rotate(t, x->parent);
        // 형제 노드 갱신
        w = x->parent->right;
      }
      // case C - 형제가 black & 형제의 두 자녀 모두 black
      // [참고] 형제가 red일 수는 없다. 이미 if문을 거쳐서 black으로 바뀌었을 것이다.
      if (w->left->color == RBTREE_BLACK && w->right->color == RBTREE_BLACK){
        // 형제 노드의 색 바꾸기
        w->color = RBTREE_RED;
        // 부모가 extra black이 되었다.-> case A, B
        x = x->parent;
      }
      // case A, B - 형제 노드의 자식 중 하나가 black이 아닐 경우
      else{
        // 왼쪽이 red인 경우, case A로 바꿀 수 있다.
        if (w->right->color == RBTREE_BLACK) {
          // 왼쪽 자식과 w 노드의 색을 바꾸고,
          w->left->color = RBTREE_BLACK;
          w->color = RBTREE_RED;
          // right rotate한다.
          right_rotate(t, w);
          // 형제 노드를 갱신해준다.
          w = x->parent->right;
        }
        // 형제를 부모의 색으로,
        w->color = x->parent->color;
        // 부모는 black으로,
        x->parent->color = RBTREE_BLACK;
        // 형제의 오른쪽 자녀는 Black으로,
        w->right->color = RBTREE_BLACK;
        // 부모를 기준으로 왼쪽으로 rotate
        left_rotate(t, x->parent);
        // case A ~ D가 해결되었으므로 종료 조건
        x = t->root;
      }
    }
    // x가 오른쪽 자식인 경우
    else{
      w = x->parent->left;
      if (w->color == RBTREE_RED){
        w->color = RBTREE_BLACK;
        x->parent->color = RBTREE_RED;
        right_rotate(t, x->parent);
        w = x->parent->left;
      }
      if (w->right->color == RBTREE_BLACK && w->left->color == RBTREE_BLACK){
        w->color = RBTREE_RED;
        x = x->parent;
      }
      else{
        if (w->left->color == RBTREE_BLACK) {
          w->right->color = RBTREE_BLACK;
          w->color = RBTREE_RED;
          left_rotate(t, w);
          w = x->parent->left;
        }
        w->color = x->parent->color;
        x->parent->color = RBTREE_BLACK;
        w->left->color = RBTREE_BLACK;
        right_rotate(t, x->parent);
        x = t->root;
      }
    }
  }
  x->color = RBTREE_BLACK;
}

/* 확인 완료 */
int rbtree_erase(rbtree *t, node_t *p) {
  // TODO: implement erase
  node_t *y = p;
  node_t *x = NULL;
  // p노드의 원래 color를 저장해놓는다.
  color_t y_original_color = y->color;

  // 삭제할 노드의 왼쪽 자식이 존재하지 않는 경우
  if (p->left == t->nil) {
    // 오른쪽 노드가 대체하면 됨
    x = p->right;
    transparent(t, p, p->right);
  }
  // 삭제할 노드의 오른쪽 자식이 존재하지 않는 경우
  else if(p->right == t->nil) {
    // 왼쪽 노드가 대체하면 됨
    x = p->left;
    transparent(t, p, p->left);
  }
  else{
    // STEP 1: 대체할 노드 찾기
    /* y: successor(대체할 노드), p: 삭제할 노드, x: y의 자식 subtree의 루트 */
    // 삭제할 노드의 successor를 찾는다
    y = min_successor(t, p->right);
    // 원래 색깔을 저장해 놓는다.
    y_original_color = y->color;
    // y의 오른쪽 자식 노드를 임시로 담아 둔다.
    x = y->right;

    // STEP 2: p(삭제할 노드)의 자식들과 맞추기
    // p의 right 자식 노드가 y인 경우
    if (y->parent == p) x->parent = y;
    else {
    // y가 p와 인접한 노드가 아닌 경우(자식이 x)
      transparent(t, y, y->right);
      // y가 들어가갈 자리의 오른쪽에 p의 right subtree가 와야 한다. y의 자식은 올라오지 않는다.
      y->right = p->right;
      y->right->parent = y;
    }
    // p에 y 이식
    transparent(t, p, y);
    // y가 들어가야 하는 자리의 노드와 그 자리의 left 노드와의 연결
    y->left = p->left;
    y->left->parent = y;
    // 원 노드의 색으로 색칠
    y->color = p->color;
  }
  // STEP 3: 삭제 후 RB-Tree 조건을 만족하도록 조정한다. 이 작업은 삭제한 노드가 black일 때만 수행한다.
  if (y_original_color == RBTREE_BLACK) {
    rbtree_delete_fixup(t, x);
  }
  // 추가로, 삭제할 노드를 free해 준다.
  free(p);
  return 0;
}

/* 확인 완료 */
void inorder_traverse(const rbtree *t, node_t *x, key_t *arr, int *i, const size_t n){
  if (x == t->nil || *i >= n) return;
  // 우선 왼쪽 노드로 갈 수 있는 만큼 계속 가기
  inorder_traverse(t, x->left, arr, i, n);
  // 다음으로 루트 노드를 array에 넣기
  arr[*i] = x->key;
  (*i)++;
  // 오른쪽 노드로 갈 수 있는 만큼 계속 가기
  inorder_traverse(t, x->right, arr, i, n);
}

/* 확인 완료 */
int rbtree_to_array(const rbtree *t, key_t *arr, const size_t n) {
  // TODO: implement to_array
  if (t->root == t->nil) return 0;
  // 배열의 인덱스를 위해 0을 표현하는 포인터를 만든다.
  int idx = 0;
  int *p = &idx;
  inorder_traverse(t, t->root, arr, p, n);
  return 0;
}
