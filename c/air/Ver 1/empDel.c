#include "air.h"

void empDel(LIST* empList) {
	EMP* emp;
	char name[NAMELEN];
	NODE* empNode;

	empListPrint(empList);

	empNode = empList->head;
	if(empNode == NULL) {
		printf("등록된 직원이 없음\n");
		system("pause");
		return;
	}

	printf("삭제할 직원 이름 입력: ");
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

	if(empList->head == empList->tail) {
		if(!strcmp(name, ((EMP*)empNode->data)->name)) {
			free(empNode->data);
			free(empNode);
			empList->head = NULL;
			empList->tail = NULL;
		}
	}
	else {
		if(!strcmp(name, emp->name)) {
			if(empNode == empList->head) {
				empList->head = empNode->next;
				empList->head->prev = NULL;
				free(empNode->data);
				free(empNode);
			}
			else if(empNode == empList->tail) {
				empList->tail = empNode->prev;
				empList->tail->next = NULL;
				free(empNode->data);
				free(empNode);
			}
			else {
				empNode->prev->next = empNode->next;
				empNode->next->prev = empNode->prev;
				free(empNode->data);
				free(empNode);
			}
		}
	}
	printf("삭제 완료\n");
	system("pause");
}
