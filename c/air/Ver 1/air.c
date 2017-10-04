#include "air.h"

void air(void) {
	LIST airList;
	LIST custList;
	LIST empList;
	int select_1;
	int select_2;
	CUST* mainCust;

	airList.head = NULL;
	airList.tail = NULL;
	custList.head = NULL;
	custList.tail = NULL;
	empList.head = NULL;
	empList.tail = NULL;
	mainCust = NULL;

	fileOpen(&airList, &empList, &custList);

	while(1) {
		select_1 = 0;
		select_2 = 0;
		system("cls");
		printf("[1] 비행기 회사\n");
		printf("[2] 직원\n");
		printf("[3] 사용자\n");
		printf("[4] 종료\n");
		printf("번호 입력: ");
		fflush(stdin);
		scanf("%d", &select_1);
		switch(select_1) {
		case 1:
			while(select_2 != 6) {
				system("cls");
				printf("[1] 비행기 배차하기\n");
				printf("[2] 비행기 배차 취소하기\n");
				printf("[3] 비행기 좌석 현황 보기\n");
				printf("[4] 비행기별 예약현황보기\n");
				printf("[5] 매출액 보기\n");
				printf("[6] 종료\n");
				printf("번호 입력: ");
				fflush(stdin);
				scanf("%d", &select_2);
				switch(select_2) {
				case 1:
					airAdd(&airList);
					break;
				case 2:
					airDel(&airList);
					break;
				case 3:
					airSeat(&airList);
					break;
				case 4:
					airCust(&airList);
					break;
				case 5:
					airMoney(&airList);
					break;
				}
			}
			break;
		case 2:
			while(select_2 != 5) {
			system("cls");
			printf("[1] 직원 등록\n");
			printf("[2] 직원별 일등록\n");
			printf("[3] 직원 수정\n");
			printf("[4] 직원 삭제\n");
			printf("[5] 종료\n");
			printf("번호 입력: ");
			fflush(stdin);
			scanf("%d", &select_2);
			switch(select_2) {
				case 1:
					empAdd(&empList);
					break;
				case 2:
					empJob(&empList);
					break;
				case 3:
					empMod(&empList);
					break;
				case 4:
					empDel(&empList);
					break;
				}
			}
			break;
		case 3:
			while(select_2 != 6) {
			system("cls");
			printf("[1] 회원 등록\n");
			printf("[2] 비행기표 예매하기\n");
			printf("[3] 비행기표 수정하기\n");
			printf("[4] 비행기표 취소하기\n");
			printf("[5] 회원 탈퇴\n");
			printf("[6] 종료\n");
			printf("번호 입력: ");
			fflush(stdin);
			scanf("%d", &select_2);
			switch(select_2) {
				case 1:
					mainCust = custAdd(&custList);
					break;
				case 2:
					custSeat(mainCust, &airList);
					break;
				case 3:
					custSeatChange(mainCust, &airList);
					break;
				case 4:
					custSeatCancel(mainCust, &airList);
					break;
				case 5:
					custDel(&custList);
					break;
				}
			}
			break;
		case 4:
			airLog(&airList, &empList, &custList);
			return;
		}
	}
}
