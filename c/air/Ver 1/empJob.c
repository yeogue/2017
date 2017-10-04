#include "air.h"

void empJob(LIST* empList) {
	EMP* emp;
	NODE* empNode;
	char name[NAMELEN];

	empListPrint(empList);

	empNode = empList->head;

	if(empNode == NULL) {
		printf("등록된 직원이 없음\n");
		system("pause");
		return;
	}

	printf("일을 지정할 직원 이름 입력: ");
	fflush(stdin);
	gets(name);

	while(empNode != NULL) {
		if(!strcmp(name, ((EMP*)empNode->data)->name)) {
			emp = (EMP*)empNode->data;
			break;
		}
		empNode = empNode->next;
	}

	if(empNode == NULL) {
		printf("해당하는 직원이 없음\n");
		system("pause");
		return;
	}

	if(!strcmp(name, emp->name)) {
		printf("직종 입력: ");
		fflush(stdin);
		gets(emp->job);
	}
	printf("일 등록 완료\n");
	system("pause");
}

void empListPrint(LIST* empList) {
	NODE* empNode;

	empNode = empList->head;

	printf("직원 목록\n");
	if(empNode == NULL) {
		return;
	}
	while(empNode != NULL) {
		printf("%s\n", ((EMP*)empNode->data)->name);
		empNode = empNode->next;
	}
}
