#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void) {
	char bat[3][5] = {"가위", "바위", "보"};
	char humanHand;
	char YN = 'n';
	int computerHand;
	int computerCalc;
	int humanCalc;
	int num;
	
	while('n' == YN) {
		srand(time(NULL));
		printf("가위, 바위, 보 중 하나를 선택하세요.(가위=a, 바위=b, 보=c): ");
		fflush(stdin);
		scanf("%c", &humanHand);
		printf("승률입력(%%): ");
		fflush(stdin);
		scanf("%d", &num);
		computerHand = (rand()%100)+1;
		humanCalc = humanHand-97;

		if(computerHand > num) {
			computerCalc = (humanCalc+1)%3;		
			printf("컴퓨터 승~!!(컴퓨터:%s, 사람:%s)\n", bat[computerCalc], bat[humanCalc]);
		}
		else if(computerHand > ((100-num)/2)+num) {
			printf("비겼습니다.(컴퓨터:%s, 사람:%s)\n", bat[humanCalc], bat[humanCalc]);
		}
		else {	
			computerCalc = (humanCalc+2)%3;
			printf("사람 승!(컴퓨터:%s, 사람:%s)\n", bat[computerCalc], bat[humanCalc]);
		}

		printf("종료하시겠습니까?(y/n) : ");
		fflush(stdin);
		scanf("%c", &YN);
		system("cls");
	}

	return 0;
}
