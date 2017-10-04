#include "hotel.h"

void hotel_stack(void) {
	int AU;
	int num;
	int roomNum = 0;
	STACK stack;
	ROOM** dp;

	printf("[1] 관리자\n");
	printf("[2] 사용자\n");
	printf("[3] 종료\n");
	printf("번호 입력: ");
	scanf("%d", &AU);
	while(1) {
		switch(AU) {
		case 1:
			printf("[1] 호텔생성\n");
			printf("[2] 객실현황\n");
			printf("[3] 돌아가기\n");
			printf("번호 입력: ");
			scanf("%d", &num);
			switch(num) {
			case 1:
				system("cls");
				dp = createHotel_stack(&stack);
				system("cls");
				break;
			case 2:
				system("cls");
				checkRoom_stack(stack);
				system("pause");
				system("cls");
				break;
			case 3:
				printf("[1] 관리자\n");
				printf("[2] 사용자\n");
				printf("[3] 종료\n");
				printf("번호 입력: ");
				scanf("%d", &AU);
				break;
			}
			break;
		case 2:
			printf("[1] 객실예매\n");
			printf("[2] 객실변경\n");
			printf("[3] 객실취소\n");
			printf("[4] 돌아가기\n");
			printf("번호 입력: ");
			scanf("%d", &num);
			switch(num) {
			case 1:
				roomNum = roomSelect_stack(dp);
				break;
			case 2:
				roomChange_stack(dp, &roomNum);
				break;
			case 3:
				roomCancel_stack(dp, &roomNum);
				break;
			case 4:
				printf("[1] 관리자\n");
				printf("[2] 사용자\n");
				printf("[3] 종료\n");
				printf("번호 입력: ");
				scanf("%d", &AU);
				break;
			}
			break;
		case 3:
			return;
			break;
		}
	}
}
