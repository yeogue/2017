#include "air.h"

void airMoney(LIST* airList) {
	NODE* airNode;
	char dest[DESTLEN];

	airListPrint(airList);

	airNode = airList->head;

	if(airNode == NULL) {
		printf("등록된 비행기가 없음\n");
		system("pause");
		return;
	}

	printf("비행기 목적지 입력: ");
	fflush(stdin);
	gets(dest);

	while(airNode != NULL) {
		if(!strcmp(dest, ((AIR*)airNode->data)->dest)) {
			printf("매출액: %d\n", ((AIR*)airNode->data)->money);
			break;
		}
		airNode = airNode->next;
	}
	if(airNode == NULL) {
		printf("해당하는 비행기가 없음\n");
	}
	system("pause");
}
