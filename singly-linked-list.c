/*
 * singly linked list
 *
 *  Data Structures
 *  School of Computer Science
 *  at Chungbuk National University
 */


#include<stdio.h>
#include<stdlib.h>

 /* 필요한 헤더파일 추가 */

typedef struct Node {  // 노드 구조체 정의 및 변수 선언
    int key;
    struct Node* link;
} listNode;

typedef struct Head {
    struct Node* first;    // 노드 구조체를 가리키는 포인터를 가지는 구조체 정의 후 변수 선언
} headNode;


/* 함수 리스트 */
headNode* initialize(headNode* h);
int freeList(headNode* h);
int insertFirst(headNode* h, int key);
int insertNode(headNode* h, int key);
int insertLast(headNode* h, int key);
int deleteFirst(headNode* h);
int deleteNode(headNode* h, int key);
int deleteLast(headNode* h);
int invertList(headNode* h);
void printList(headNode* h);

int main() {
    char command;
    int key;
    headNode* headnode = NULL;   // 노드를 가리킬 구조체 변수 생성



    do {
        printf("----------------------------------------------------------------\n");
        printf("                     Singly Linked List                         \n");
        printf("----------------------------------------------------------------\n");
        printf(" Initialize    = z           Print         = p \n");
        printf(" Insert Node   = i           Delete Node   = d \n");
        printf(" Insert Last   = n           Delete Last   = e\n");
        printf(" Insert First  = f           Delete First  = t\n");
        printf(" Invert List   = r           Quit          = q\n");
        printf("----------------------------------------------------------------\n");

        // command 입력 받음
        printf("Command = ");
        scanf(" %c", &command);


        // command에 따른 다른 함수 실행
        switch (command) {
        case 'z': case 'Z':
            headnode = initialize(headnode);    // headnode 생성
            break;
        case 'p': case 'P':
            printList(headnode);
            break;
        case 'i': case 'I':
            printf("Your Key = ");  // key 입력 받음
            scanf("%d", &key);
            insertNode(headnode, key);
            break;
        case 'd': case 'D':
            printf("Your Key = ");  
            scanf("%d", &key);
            deleteNode(headnode, key);
            break;
        case 'n': case 'N':
            printf("Your Key = ");
            scanf("%d", &key);
            insertLast(headnode, key);
            break;
        case 'e': case 'E':
            deleteLast(headnode);
            break;
        case 'f': case 'F':
            printf("Your Key = ");
            scanf("%d", &key);
            insertFirst(headnode, key);
            break;
        case 't': case 'T':
            deleteFirst(headnode);
            break;
        case 'r': case 'R':
            invertList(headnode);
            break;
        case 'q': case 'Q':
            freeList(headnode);
            break;
        default:
            printf("\n       >>>>>   Concentration!!   <<<<<     \n");
            break;
        }

    } while (command != 'q' && command != 'Q');

    return 1;
}

headNode* initialize(headNode* h) {

    /* headNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제 */
    if (h != NULL)
        freeList(h);

    	/* headNode에 대한 메모리를 할당하여 리턴 */
    headNode* temp = (headNode*)malloc(sizeof(headNode));
    temp->first = NULL;
    return temp;
}


int freeList(headNode* h) {
    	/* h와 연결된 listNode 메모리 해제
	 * headNode도 해제되어야 함.
	 */
    listNode* p = h->first;

    listNode* prev = NULL;

    while (p != NULL) {
        prev = p;
        p = p->link;
        free(prev);
    }

    free(h);
    return 0;
}

/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(headNode* h, int key) {

    listNode* node = (listNode*)malloc(sizeof(listNode));
    node->key = key;  // 생성한 노드에 key값 넣음

    node->link = h->first;  // 생성한 노드의 link가 headnode의 first를 가리키도록 함
    h->first = node;    // headnode의 first가 새로 생성한 노드를 가리키도록 함
    
    return 0;
}

/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(headNode* h, int key) {

    if (h->first == NULL || key < h->first->key)
        return insertFirst(h, key);

    listNode* node = (listNode*)malloc(sizeof(listNode));
    node->key = key;  // 생성한 노드에 key값 넣음
    node->link = NULL;  // 생성한 노드의 link를 NULL로 초기화

    listNode* current = h->first;

    while (current->link != NULL && current->link->key < key) { // key값보다 큰 값이 나오는 노드 바로 앞에 삽입
        current = current->link;
    }

    node->link = current->link; // 새로 생성한 노드의 link가 current의 link를 가리키도록 함
    current->link = node;   // current의 link가 새로 생성한 노드를 가리키도록 함

    return 0;
}
/**
 * list에 key에 대한 노드하나를 추가
 */

// list의 마지막에 key에 대한 노드하나를 추가
int insertLast(headNode* h, int key) {
    if (h->first == NULL)   // 리스트가 비어있으면 insertFirst 호출
        return insertFirst(h, key);

    listNode* last = h->first;

    while (last->link != NULL) {    // 리스트의 마지막 노드 찾기
        last = last->link;    
    }

    listNode* node = (listNode*)malloc(sizeof(listNode));

    node->key = key;
    node->link = NULL;
    last->link = node;

    return 0;
}

/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(headNode* h) {
    if (h->first == NULL)   // 리스트가 비어있으면 -1 반환
        return -1;

    listNode* temp = h->first;

    h->first = h->first->link;  // headnode의 first가 다음 노드를 가리키도록 함
    free(temp); // 첫번째 노드 메모리 해제

    return 0;
}

/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(headNode* h, int key) {
    listNode* current = h->first;
    listNode* prev = NULL;

    while (current != NULL) {   // key값을 가진 노드 찾기
        if (current->key == key) {  // key값을 가진 노드를 찾으면
            if (prev == NULL)       // 첫번째 노드를 삭제하는 경우
                return deleteFirst(h);  // 첫번째 노드를 삭제
            prev->link = current->link; // 이전 노드의 link가 다음 노드를 가리키도록 함
           
            free(current);
            return 0;
        }
        prev = current;
        current = current->link;
    }

    printf("Key not found.\n");
    return -1;
}
/**
 * list의 마지막 노드 삭제
 */
int deleteLast(headNode* h) {
    if (h->first == NULL)   // 리스트가 비어있으면 -1 반환
        return -1;

    listNode* last = h->first;
    listNode* prev = NULL;

    while (last->link != NULL) {    // 마지막 노드 찾기
        prev = last;
        last = last->link;
    }

    if (prev == NULL) { // 리스트에 노드가 하나만 있는 경우
        free(last);
        h->first = NULL;
    } else {    // 리스트에 노드가 여러개 있는 경우
        free(last);
        prev->link = NULL;
    }

    return 0;
}
/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(headNode* h) {
    listNode* prev = NULL;
    listNode* current = h->first;
    listNode* next = NULL;

    while (current != NULL) {   // 리스트의 링크를 역순으로 재배치
        next = current->link;
        current->link = prev;
        prev = current;
        current = next;
    }

    h->first = prev;    // headnode의 first가 역순으로 재배치된 리스트의 첫번째 노드를 가리키도록 함
    return 0;
}

void printList(headNode* h) {
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if (h == NULL) {    // 리스트가 비어있으면
		printf("Nothing to print....\n");
		return;
	}

	p = h->first;

	while (p != NULL) { // 리스트의 노드들을 출력
		printf("[ [%d]=%d ] ", i, p->key);  // 노드의 key값 출력
		p = p->link;
		i++;
	}

	printf("  items = %d\n", i);
}
