#include "air.h"

void custSeat(CUST* mainCust, LIST* airList) {
	NODE* airNode;
	char dest[DESTLEN];
	int num;

	if(mainCust == NULL) {
		printf("회원등록 필요\n");
		system("pause");
		return;
	}

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
		return;
	}
	else {
		printf("예약할 좌석 번호: ");
		scanf("%d", &num);
		if(num%20 < 5 && num %20 > 0) {
			if(mainCust->money >= 500000) {
				if(((AIR*)airNode->data)->seat[num-1].s == 'O') {
					((AIR*)airNode->data)->seat[num-1].s = 'X';
					((AIR*)airNode->data)->seat[num-1].cust = mainCust->name;
					mainCust->money -= 500000;
					((AIR*)airNode->data)->money += 500000;
					printf("남은 소지금: %d\n", mainCust->money);
				}
				else {
					printf("이미 예약된 자리\n");
					system("pause");
					return;
				}
			}
			else {
				printf("돈이 부족함\n");
				system("pause");
				return;
			}
		}
		else {
			if(mainCust->money >= 300000) {
				if(((AIR*)airNode->data)->seat[num-1].s == 'O') {
					((AIR*)airNode->data)->seat[num-1].s = 'X';
					((AIR*)airNode->data)->seat[num-1].cust = mainCust->name;
					mainCust->money -= 300000;
					((AIR*)airNode->data)->money += 300000;
					printf("남은 소지금: %d\n", mainCust->money);
				}
				else {
					printf("이미 예약된 자리\n");
					system("pause");
					return;
				}
			}
			else {
				printf("돈이 부족함\n");
				system("pause");
				return;
			}
		}
	}
	printf("예매 완료\n");
	system("pause");
}
