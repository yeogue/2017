#include "air.h"

void custSeatChange(CUST* mainCust, LIST* airList) {
	NODE* airNode;
	int num;

	airNode = custSeatCancel(mainCust, airList);
	/*if(mainCust == NULL) {
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

	while(airNode != NULL) {
		i = 0;
		while(i < 40) {
			if(((AIR*)airNode->data)->seat[i].s == 'X') {

				airSeatPrint((AIR*)airNode->data);
				((AIR*)airNode->data)->seat[i].s = 'O';
				if(i%20 < 5 && i%20 > 0) {
					mainCust->money += 500000;
				}
				else {
					mainCust->money += 300000;
				}

				break;
			}
			i++;
		}
		if(i != 40) {
			break;
		}
		airNode = airNode->next;
	}*/
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
