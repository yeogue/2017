#include "hotel.h"

int roomSelect_stack(ROOM* dp[]) {
	int num;
	int i;

	printf("예약할 방번호 입력: ");
	scanf("%d", &num);

	i = 0;
	while(1) {
		if(dp[i][0].floor == num/100) {
			break;
		}
		i++;
	}
	dp[i][(num%100)-1].check = 'X';

	return num;
}

void roomChange_stack(ROOM* dp[], int* roomNum) {
	
	roomCancel_stack(dp, roomNum);
	*roomNum = roomSelect_stack(dp);
}

void roomCancel_stack(ROOM* dp[], int* roomNum) {
	int i;

	if(roomNum == 0) {
		printf("예약한 방이 없음.\n");
		return;
	}

	i = 0;
	while(1) {
		if(dp[i]->floor == *roomNum/100) {
			break;
		}
		i++;
	}
	dp[i][((*roomNum)%100)-1].check = 'O';
}
