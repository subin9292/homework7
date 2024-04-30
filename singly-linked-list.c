/*
 * singly linked list
 *
 *  Data Structures
 *  School of Computer Science
 *  at Chungbuk National University
 */


#include<stdio.h>
#include<stdlib.h>

 /* �ʿ��� ������� �߰� */

typedef struct Node {  // ��� ����ü ���� �� ���� ����
    int key;
    struct Node* link;
} listNode;

typedef struct Head {
    struct Node* first;    // ��� ����ü�� ����Ű�� �����͸� ������ ����ü ���� �� ���� ����
} headNode;


/* �Լ� ����Ʈ */
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
    headNode* headnode = NULL;   // ��带 ����ų ����ü ���� ����



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

        // command �Է� ����
        printf("Command = ");
        scanf(" %c", &command);


        // command�� ���� �ٸ� �Լ� ����
        switch (command) {
        case 'z': case 'Z':
            headnode = initialize(headnode);    // headnode ����
            break;
        case 'p': case 'P':
            printList(headnode);
            break;
        case 'i': case 'I':
            printf("Your Key = ");  // key �Է� ����
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

    /* headNode�� NULL�� �ƴϸ�, freeNode�� ȣ���Ͽ� �Ҵ�� �޸� ��� ���� */
    if (h != NULL)
        freeList(h);

    	/* headNode�� ���� �޸𸮸� �Ҵ��Ͽ� ���� */
    headNode* temp = (headNode*)malloc(sizeof(headNode));
    temp->first = NULL;
    return temp;
}


int freeList(headNode* h) {
    	/* h�� ����� listNode �޸� ����
	 * headNode�� �����Ǿ�� ��.
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
 * list ó���� key�� ���� ����ϳ��� �߰�
 */
int insertFirst(headNode* h, int key) {

    listNode* node = (listNode*)malloc(sizeof(listNode));
    node->key = key;  // ������ ��忡 key�� ����

    node->link = h->first;  // ������ ����� link�� headnode�� first�� ����Ű���� ��
    h->first = node;    // headnode�� first�� ���� ������ ��带 ����Ű���� ��
    
    return 0;
}

/* ����Ʈ�� �˻��Ͽ�, �Է¹��� key���� ū���� ������ ��� �ٷ� �տ� ���� */
int insertNode(headNode* h, int key) {

    if (h->first == NULL || key < h->first->key)
        return insertFirst(h, key);

    listNode* node = (listNode*)malloc(sizeof(listNode));
    node->key = key;  // ������ ��忡 key�� ����
    node->link = NULL;  // ������ ����� link�� NULL�� �ʱ�ȭ

    listNode* current = h->first;

    while (current->link != NULL && current->link->key < key) { // key������ ū ���� ������ ��� �ٷ� �տ� ����
        current = current->link;
    }

    node->link = current->link; // ���� ������ ����� link�� current�� link�� ����Ű���� ��
    current->link = node;   // current�� link�� ���� ������ ��带 ����Ű���� ��

    return 0;
}
/**
 * list�� key�� ���� ����ϳ��� �߰�
 */

// list�� �������� key�� ���� ����ϳ��� �߰�
int insertLast(headNode* h, int key) {
    if (h->first == NULL)   // ����Ʈ�� ��������� insertFirst ȣ��
        return insertFirst(h, key);

    listNode* last = h->first;

    while (last->link != NULL) {    // ����Ʈ�� ������ ��� ã��
        last = last->link;    
    }

    listNode* node = (listNode*)malloc(sizeof(listNode));

    node->key = key;
    node->link = NULL;
    last->link = node;

    return 0;
}

/**
 * list�� ù��° ��� ����
 */
int deleteFirst(headNode* h) {
    if (h->first == NULL)   // ����Ʈ�� ��������� -1 ��ȯ
        return -1;

    listNode* temp = h->first;

    h->first = h->first->link;  // headnode�� first�� ���� ��带 ����Ű���� ��
    free(temp); // ù��° ��� �޸� ����

    return 0;
}

/**
 * list���� key�� ���� ��� ����
 */
int deleteNode(headNode* h, int key) {
    listNode* current = h->first;
    listNode* prev = NULL;

    while (current != NULL) {   // key���� ���� ��� ã��
        if (current->key == key) {  // key���� ���� ��带 ã����
            if (prev == NULL)       // ù��° ��带 �����ϴ� ���
                return deleteFirst(h);  // ù��° ��带 ����
            prev->link = current->link; // ���� ����� link�� ���� ��带 ����Ű���� ��
           
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
 * list�� ������ ��� ����
 */
int deleteLast(headNode* h) {
    if (h->first == NULL)   // ����Ʈ�� ��������� -1 ��ȯ
        return -1;

    listNode* last = h->first;
    listNode* prev = NULL;

    while (last->link != NULL) {    // ������ ��� ã��
        prev = last;
        last = last->link;
    }

    if (prev == NULL) { // ����Ʈ�� ��尡 �ϳ��� �ִ� ���
        free(last);
        h->first = NULL;
    } else {    // ����Ʈ�� ��尡 ������ �ִ� ���
        free(last);
        prev->link = NULL;
    }

    return 0;
}
/**
 * ����Ʈ�� ��ũ�� �������� �� ��ġ
 */
int invertList(headNode* h) {
    listNode* prev = NULL;
    listNode* current = h->first;
    listNode* next = NULL;

    while (current != NULL) {   // ����Ʈ�� ��ũ�� �������� ���ġ
        next = current->link;
        current->link = prev;
        prev = current;
        current = next;
    }

    h->first = prev;    // headnode�� first�� �������� ���ġ�� ����Ʈ�� ù��° ��带 ����Ű���� ��
    return 0;
}

void printList(headNode* h) {
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if (h == NULL) {    // ����Ʈ�� ���������
		printf("Nothing to print....\n");
		return;
	}

	p = h->first;

	while (p != NULL) { // ����Ʈ�� ������ ���
		printf("[ [%d]=%d ] ", i, p->key);  // ����� key�� ���
		p = p->link;
		i++;
	}

	printf("  items = %d\n", i);
}
