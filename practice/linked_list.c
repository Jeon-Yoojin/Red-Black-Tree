#include <stdio.h>
#include <stdlib.h>

typedef int element;
// 노드 타입을 구조체로 정의한다.
typedef struct ListNode { 
	element data;
	struct ListNode* link;
} ListNode;
// 앞부분에 노드 삽입
ListNode* insert_first(ListNode* head, int value)
{
	// ListNode* p = (ListNode*)malloc(sizeof(ListNode)); //(1)
	// p->data = value;
	// // (2)
	// p->link = head; //(3)
	// head = p; //(4)
    //return head;

    // malloc으로 메모리 공간 할당
    ListNode *p = (ListNode*)malloc(sizeof(ListNode));
    // value를 해당 메모리에 담기
    p->data = value;
    // 새로 할당한 메모리가 head 포인터 가리키하기
    p->link = head;
    // head가 새로 할당한 메모리를 가리키도록 하기
    head = p;
	return head;

}
// 노드 pre 뒤에 새로운 노드 삽입
ListNode* insert(ListNode* head, ListNode* pre, element value)
{
	// ListNode* p = (ListNode*)malloc(sizeof(ListNode));
	// //(1)
	// p->data = value; //(2)
	// p->link = pre->link; //(3)
	// pre->link = p; //(4)
	// return head; //(5)

    // p 만들기
    ListNode *p = (ListNode*)malloc(sizeof(ListNode));
    p->data = value;
    // 삽입할 노드가 prev 노드의 link를 가리키기
    p->link = pre->link;
    // prev 노드가 삽입할 노드 가리키기
    pre->link = p;
    return head;
}
// 앞부분의 노드 제거
ListNode* delete_first(ListNode* head)
{
	// ListNode* removed;
	// if (head == NULL) return NULL;
	// removed = head; // (1)
	// head = removed->link; // (2)
	// free(removed); // (3)
	// return head; // (4)

    ListNode* removed;
    // head가 NULL을 가리키고 있는 경우
    if (head == NULL) return NULL;
    // head를 현재 해드가 가리키는 노드의 주소를 가리키도록 하기
    removed = head;
    head = removed->link;
    // 원래 head 주소를 free 시켜주기
    free(removed);
    return head;
}
// pre가 가리키는 노드의 다음 노드를 삭제.
ListNode* delete(ListNode* head, ListNode* pre)
{
	// ListNode* removed;
	// removed = pre->link;
	// pre->link = removed->link; // (2)
	// free(removed); // (3)
	// return head; // (4)

    ListNode* removed;
    // removed에 pre가 가리키는 다음 노드를 넣기
    removed = pre->link;
    // pre가 removed가 가리키는 노드를 가리키도록 하기
    pre->link = removed->link;
    // removed 노드를 free로 해제하기
    free(removed);
    return head;
}
// 리스트 출력
void print_list(ListNode* head)
{
	// for (ListNode* p = head; p != NULL; p = p->link)
	// 	printf("%d->", p->data);
	// printf("NULL \n");
    for(ListNode *p = head; p!= NULL ; p = p->link){
        printf("%d->", p->data);
    }
    printf("NULL\n");
}

ListNode* search_list(ListNode *head, element x){
    // head부터 하나씩 이동하면서, x인지 확인
    for(ListNode *p = head; p!= NULL; p = p->link){
    // 맞으면 리턴, break
        if(p->data == x){
            return p;
        }
    // NULL 출력
    }
    return NULL;
}

//메인 1
int main(void)
{
	ListNode *head = NULL;

	for (int i = 0; i < 5; i++) {
		head = insert_first(head, i);
		print_list(head);
	}
	for (int i = 0; i < 5; i++) {
		head = delete_first(head);
		print_list(head);
	}
	return 0;
}
// 메인 2
// int main(void)
// {
// 	ListNode *head = NULL;

// 	head = insert_first(head, 10);
// 	print_list(head);
// 	head = insert_first(head, 20);
// 	print_list(head);
// 	head = insert_first(head, 30);
// 	print_list(head);
// 	if (search_list(head, 30) != NULL)
// 		printf("리스트에서 30을 찾았습니다. \n");
// 	else
// 		printf("리스트에서 30을 찾지 못했습니다. \n");
// 	return 0;
// }

/* 실행결과
0->NULL
1->0->NULL
2->1->0->NULL
3->2->1->0->NULL
4->3->2->1->0->NULL
3->2->1->0->NULL
2->1->0->NULL
1->0->NULL
0->NULL
NULL
*/
