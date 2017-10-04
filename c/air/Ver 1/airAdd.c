#include "air.h"

void airAdd(LIST* airList) {
	AIR* air;
	NODE* airNode;
	NODE* nameCheck;
	SEAT* seat;
	int i;
	// 변수 값 대입 시작
	air = (AIR*)malloc(sizeof(AIR));
	airNode = (NODE*)malloc(sizeof(NODE));
	seat = (SEAT*)malloc(sizeof(SEAT)*40);

	air->seat = seat;

	airNode->next = NULL;
	airNode->prev = NULL;
	
	air->money = 0;
	for(i = 0; i < 40; i++) {
		air->seat[i].s = 'O';
		air->seat[i].cust = NULL;
	}

	airNode->data = air;
	nameCheck = airList->head;

	printf("목적지 설정: ");
	fflush(stdin);
	gets(air->dest);

	while(nameCheck != NULL) {
		if(!strcmp(air->dest, ((AIR*)nameCheck->data)->dest)) {
			printf("이미 같은 목적지의 비행기가 있음\n");
			printf("목적지 설정: ");
			fflush(stdin);
			gets(air->dest);
			nameCheck = airList->head;
		}
		nameCheck = nameCheck->next;
	}
	// 값 대입 끝
	if(airList->head == NULL) {
		airList->head = airNode;
		airList->tail = airNode;
	}
	else {
		airList->tail->next = airNode;
		airNode->prev = airList->tail;
		airList->tail = airNode;
	}
	printf("비행기 생성\n");
	system("pause");
}
