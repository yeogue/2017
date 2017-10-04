#include "air.h"

void custDel(LIST* custList) {
	CUST* cust;
	int num;
	NODE* custNode;

	custListPrint(custList);

	custNode = custList->head;
	if(custNode == NULL) {
		printf("등록된 회원이 없음\n");
		system("pause");
		return;
	}

	printf("삭제할 회원 고유번호 입력: ");
	fflush(stdin);
	scanf("%d", &num);

	while(custNode != NULL) {
		if(num == ((CUST*)custNode->data)->num) {
			cust = (CUST*)custNode->data;
			break;
		}
		custNode = custNode->next;
	}

	if(custNode == NULL) {
		printf("해당하는 회원이 없음\n");
		system("pause");
		return;
	}

	if(custList->head == custList->tail) {
		if(num == ((CUST*)custNode->data)->num) {
			free(custNode->data);
			free(custNode);
			custList->head = NULL;
			custList->tail = NULL;
		}
	}
	else {
		if(num == cust->num) {
			if(custNode == custList->head) {
				custList->head = custNode->next;
				custList->head->prev = NULL;
				free(custNode->data);
				free(custNode);
			}
			else if(custNode == custList->tail) {
				custList->tail = custNode->prev;
				custList->tail->next = NULL;
				free(custNode->data);
				free(custNode);
			}
			else {
				custNode->prev->next = custNode->next;
				custNode->next->prev = custNode->prev;
				free(custNode->data);
				free(custNode);
			}
		}
	}
	printf("삭제 완료\n");
	system("pause");
}

void custListPrint(LIST* custList) {
	NODE* custNode;

	custNode = custList->head;

	printf("회원 목록\n");
	if(custNode == NULL) {
		return;
	}
	while(custNode != NULL) {
		printf("고유번호: %d ", ((CUST*)custNode->data)->num);
		printf("이름: %s\n", ((CUST*)custNode->data)->name);
		custNode = custNode->next;
	}
}
