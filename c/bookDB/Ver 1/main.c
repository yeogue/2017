#include "books.h"

int main(void) {
	
	int num = 0;
	
	while(1) {
		printf("================\n");
		printf("[1] 책 추가\n");
		printf("[2] 모든 책 출력\n");
		printf("[3] 책 검색\n");
		printf("[4] 책 정보 수정\n");
		printf("[5] 책 삭제\n");
		printf("[6] 종료\n");
		printf("================\n");
		printf("번호를 선택해주세요: ");
		scanf("%d", &num);
		if(0 >= num || 6 < num) {
		printf("================\n");
		printf("잘못 입력하셨습니다.\n");
		printf("================\n");
		system("pause");
		system("cls");
		fflush(stdin);
		continue;
		}
		switch(num) {
		case 1: 
			system("cls");
			Add();
			system("cls");
			break;
		case 2:
			system("cls");
			Print(allBooks);
			system("cls");
			break;
		case 3: 
			system("cls");
			Search(allBooks);
			system("cls");
			break;
		case 4:
			system("cls");
			Modify(allBooks);
			system("cls");
			break;
		case 5: 
			system("cls");
			Delete(allBooks);
			system("cls");
			break;
		case 6:
			system("cls");
			Exit();
			break;
		default:
			system("cls");
			break;
		}
	}
	return 0;
}
