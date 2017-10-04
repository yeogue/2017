#include "bus.h"

BUSLIST busList;

int main(void) {
	int num = 0;
	int tf = 0;
	CUSTOMER* customer;

	busList.first = NULL;
	
	printf("[1] 관리자\n");
	printf("[2] 사용자\n");
	printf("값 선택: ");
	scanf("%d", &tf);

	while(1) {
		if(tf - 2) {
			system("cls"); 
			printf("[1] 버스배차\n");
			printf("[2] 배차취소\n");
			printf("[3] 좌석현황\n");
			printf("[4] 돌아가기\n");
			printf("값 선택: ");
			scanf("%d", &num);
			switch(num) {
			case 1: system("cls"); a1(&busList); break;
			case 2: system("cls"); a2(&busList); break; 
			case 3: system("cls"); a3(&busList); break;
			case 4: system("cls"); 
					printf("[1] 관리자\n");
					printf("[2] 사용자\n");
					printf("값 선택: ");
					scanf("%d", &tf);
					break;
			}
		}
		else { 
			system("cls"); 
			printf("[1] 버스예매\n");
			printf("[2] 좌석교체\n");
			printf("[3] 예매취소\n");
			printf("[4] 돌아가기\n");
			printf("값 선택: ");
			scanf("%d", &num);
			switch(num) {
			case 1: system("cls");
					customer = u1(&busList);
					printf("예매 완료\n");
					system("pause");
					break;
			case 2: system("cls"); 
					u2(&busList, customer);
					break; 
			case 3: system("cls"); 
					u3(&busList, customer); 
					printf("예매 취소 완료.\n");
					system("pause");
					break;
			case 4: system("cls"); 
					printf("[1] 관리자\n");
					printf("[2] 사용자\n");
					printf("값 선택: ");
					scanf("%d", &tf);
					break;
			}
		}
	}
}
