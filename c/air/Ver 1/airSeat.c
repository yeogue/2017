#include "air.h"

void airSeat(LIST* airList) {
	NODE* airNode;
	char dest[DESTLEN];

	airNode = airList->head;
	if(airNode == NULL) {
		printf("등록된 비행기가 없음\n");
		system("pause");
		return;
	}

	airListPrint(airList);

	printf("비행기 목적지 입력: ");
	fflush(stdin);
	gets(dest);

	while(airNode != NULL) {
		if(!strcmp(((AIR*)airNode->data)->dest, dest)) {

			airSeatPrint((AIR*)airNode->data);

			break;
		}
		airNode = airNode->next;
	}
	if(airNode == NULL) {
		printf("해당하는 비행기가 없음\n");
		system("pause");
	}
}

void airListPrint(LIST* airList) {
	NODE* airNode;

	airNode = airList->head;

	printf("대기중인 비행기 목록\n");
	if(airNode == NULL) {
		return;
	}
	while(airNode != NULL) {
		printf("%s\n", ((AIR*)airNode->data)->dest);
		airNode = airNode->next;
	}
}

void airSeatPrint(AIR* air) {
	int i;

	for(i = 0; i < 10; i++) {
		printf("%2d ", (i*2)+1);
	}
	printf("\n");
	for(i = 0; i < 10; i++) {
		printf("%2d ", (i*2)+2);
	}
	printf("\n");
	for(i = 0; i < 10; i++) {
		printf("%2c ", air->seat[(i*2)].s);
	}
	printf("\n");
	for(i = 0; i < 10; i++) {
		printf("%2c ", air->seat[(i*2)+1].s);
	}
	printf("\n");
	printf("\t통\t로\n");
	for(i = 0; i < 10; i++) {
		printf("%2c ", air->seat[(i*2)+20].s);
	}
	printf("\n");
	for(i = 0; i < 10; i++) {
		printf("%2c ", air->seat[(i*2)+21].s);
	}
	printf("\n");
	for(i = 0; i < 10; i++) {
		printf("%2d ", (i*2)+21);
	}
	printf("\n");
	for(i = 0; i < 10; i++) {
		printf("%2d ", (i*2)+22);
	}
	printf("\n");
	
	system("pause");
}
