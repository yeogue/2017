#include "air.h"

void empAdd(LIST* empList) {
	EMP* emp;
	NODE* empNode;
	//값 대입 시작
	emp = (EMP*)malloc(sizeof(EMP));
	empNode = (NODE*)malloc(sizeof(NODE));
	
	empNode->next = NULL;
	empNode->prev = NULL;
	empNode->data = emp;

	printf("이름 입력: ");
	fflush(stdin);
	gets(emp->name);
	
	strcpy(emp->job, "미정");

	printf("나이 입력: ");
	fflush(stdin);
	scanf("%d", &emp->age);
	//값 대입 끝
	if(empList->head == NULL) {
		empList->head = empNode;
		empList->tail = empNode;
	}
	else {
		empList->tail->next = empNode;
		empNode->prev = empList->tail;
		empList->tail = empNode;
	}
	printf("직원 추가\n");
	system("pause");
}
