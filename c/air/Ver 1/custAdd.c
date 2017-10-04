#include "air.h"

CUST* custAdd(LIST* custList) {
	CUST* cust;
	NODE* custNode;
	NODE* numCheck;
	// 변수 값 대입 시작
	cust = (CUST*)malloc(sizeof(CUST));
	custNode = (NODE*)malloc(sizeof(NODE));

	custNode->next = NULL;
	custNode->prev = NULL;
	
	cust->money = 1000000;

	custNode->data = cust;
	numCheck = custList->head;

	printf("회원 이름: ");
	fflush(stdin);
	gets(cust->name);

	cust->num = rand()+10000;
	while(numCheck != NULL) {
		if(cust->num == ((CUST*)numCheck->data)->num) {
			cust->num = rand()+10000;
			numCheck = custList->head;
		}
		numCheck = numCheck->next;
	}
	// 값 대입 끝
	if(custList->head == NULL) {
		custList->head = custNode;
		custList->tail = custNode;
	}
	else {
		custList->tail->next = custNode;
		custNode->prev = custList->tail;
		custList->tail = custNode;
	}
	printf("회원 등록 완료\n");
	printf("고유번호: %d\n", cust->num);
	system("pause");

	return cust;
}
