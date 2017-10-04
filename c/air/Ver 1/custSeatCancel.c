#include "air.h"

NODE* custSeatCancel(CUST* mainCust, LIST* airList) {
	NODE* airNode;
	int i;

	if(mainCust == NULL) {
		printf("회원등록 필요\n");
		system("pause");
		return NULL;
	}

	airNode = airList->head;
	if(airNode == NULL) {
		printf("등록된 비행기가 없음\n");
		system("pause");
		return NULL;
	}

	while(airNode != NULL) {
		i = 0;
		while(i < 40) {
			if(((AIR*)airNode->data)->seat[i].s == 'X') {

				airSeatPrint((AIR*)airNode->data);
				((AIR*)airNode->data)->seat[i].s = 'O';
				if((i+1)%20 < 5 && (i+1)%20 > 0) {
					mainCust->money += 500000;
					((AIR*)airNode->data)->seat[i].cust = NULL;
					((AIR*)airNode->data)->money -= 500000;
				}
				else {
					mainCust->money += 300000;
					((AIR*)airNode->data)->seat[i].cust = NULL;
					((AIR*)airNode->data)->money -= 300000;
				}

				break;
			}
			i++;
		}
		if(i != 40) {
			break;
		}
		airNode = airNode->next;
	}
	printf("예매 취소 완료\n");
	system("pause");

	return airNode;
}
