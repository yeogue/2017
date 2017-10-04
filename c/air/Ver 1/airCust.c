#include "air.h"

void airCust(LIST* airList) {
	NODE* airNode;
	AIR* air;
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
			int i;
			air = (AIR*)airNode->data;
			printf("예약된 좌석 목록\n");
			for(i = 0; i < 40; i++) {
				if(air->seat[i].s == 'X') {
					printf("예약자 명: %s, %d번 석\n",((AIR*)airNode->data)->seat[i].cust, i+1);
				}
			}
			printf("\n");
			break;
		}
		airNode = airNode->next;
	}
	if(airNode == NULL) {
		printf("해당하는 비행기가 없음\n");
	}
	else {
		printf("출력 완료\n");
	}
	system("pause");
}
