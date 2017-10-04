#include "air.h"

void fileOpen(LIST* airList, LIST* empList, LIST* custList) {
	FILE* f;
	AIR* insAir;
	SEAT* insSeat;
	EMP* insEmp;
	CUST* insCust;
	NODE* insNode;

	printf("기존 데이터 로드중\n");

	f = fopen("C:\\Users\\BIT\\Desktop\\custLog.txt", "rb");

	if(f == NULL) {
		return;
	}

	insCust = (CUST*)malloc(sizeof(CUST));
	insNode = (NODE*)malloc(sizeof(NODE));
	insNode->data = insCust;
	insNode->next = NULL;
	insNode->prev = NULL;
	while(fread(insCust, sizeof(CUST), 1, f)) {
		if(custList->head == NULL) {
			custList->head = insNode;
			custList->tail = insNode;
		}
		else {
			custList->tail->next = insNode;
			insNode->prev = custList->tail;
			custList->tail = insNode;
		}
		insCust = (CUST*)malloc(sizeof(CUST));
		insNode = (NODE*)malloc(sizeof(NODE));
		insNode->data = insCust;
		insNode->next = NULL;
		insNode->prev = NULL;
	}
	fclose(f);

	f = fopen("C:\\Users\\BIT\\Desktop\\airLog.txt", "rb");

	if(f == NULL) {
		return;
	}

	insAir = (AIR*)malloc(sizeof(AIR));
	insNode = (NODE*)malloc(sizeof(NODE));
	insNode->data = insAir;
	insNode->next = NULL;
	insNode->prev = NULL;
	while(fread(insAir, sizeof(AIR), 1, f)) {
		if(airList->head == NULL) {
			airList->head = insNode;
			airList->tail = insNode;
		}
		else {
			airList->tail->next = insNode;
			insNode->prev = airList->tail;
			airList->tail = insNode;
		}
		insAir = (AIR*)malloc(sizeof(AIR));
		insNode = (NODE*)malloc(sizeof(NODE));
		insNode->data = insAir;
		insNode->next = NULL;
		insNode->prev = NULL;
	}
	fclose(f);

	f = fopen("C:\\Users\\BIT\\Desktop\\seatLog.txt", "rb");

	if(f == NULL) {
		return;
	}

	insNode = airList->head;
	while(insNode != NULL) {
		insSeat = (SEAT*)malloc(sizeof(SEAT)*40);
		((AIR*)insNode->data)->seat = insSeat;
		fread(insSeat, sizeof(SEAT)*40, 1, f);
		insSeat = (SEAT*)malloc(sizeof(SEAT)*40);
		insNode = insNode->next;
	}
	fclose(f);

	f = fopen("C:\\Users\\BIT\\Desktop\\empLog.txt", "rb");

	if(f == NULL) {
		return;
	}

	insEmp = (EMP*)malloc(sizeof(EMP));
	insNode = (NODE*)malloc(sizeof(NODE));
	insNode->data = insEmp;
	insNode->next = NULL;
	insNode->prev = NULL;
	while(fread(insEmp, sizeof(EMP), 1, f)) {
		if(empList->head == NULL) {
			empList->head = insNode;
			empList->tail = insNode;
		}
		else {
			empList->tail->next = insNode;
			insNode->prev = empList->tail;
			empList->tail = insNode;
		}
		insEmp = (EMP*)malloc(sizeof(EMP));
		insNode = (NODE*)malloc(sizeof(NODE));
		insNode->data = insEmp;
		insNode->next = NULL;
		insNode->prev = NULL;
	}
	fclose(f);
}
