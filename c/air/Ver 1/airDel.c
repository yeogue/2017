#include "air.h"

void airDel(LIST* airList) {
	char dest[DESTLEN];
	NODE* airNode;

	airListPrint(airList);

	airNode = airList->head;
	if(airNode == NULL) {
		printf("등록된 비행기가 없음\n");
		system("pause");
		return;
	}

	printf("삭제할 비행기 목적지 입력: ");
	fflush(stdin);
	gets(dest);

	if(airList->head == airList->tail) {
		if(strcmp(dest, ((AIR*)airNode->data)->dest)) {
			printf("해당하는 비행기가 없음\n");
			system("pause");
			return;
		}
		else {
			free(((AIR*)airNode->data)->seat);
			free(airNode->data);
			free(airNode);
			airList->head = NULL;
			airList->tail = NULL;
		}
	}
	else {
		while(airNode != NULL) {
			if(!strcmp(dest, ((AIR*)airNode->data)->dest)) {
				if(airNode == airList->head) {
					airList->head = airNode->next;
					airList->head->prev = NULL;
					free(((AIR*)airNode->data)->seat);
					free(airNode->data);
					free(airNode);
				}
				else if(airNode == airList->tail) {
					airList->tail = airNode->prev;
					airList->tail->next = NULL;
					free(((AIR*)airNode->data)->seat);
					free(airNode->data);
					free(airNode);
				}
				else {
					airNode->prev->next = airNode->next;
					airNode->next->prev = airNode->prev;
					free(((AIR*)airNode->data)->seat);
					free(airNode->data);
					free(airNode);
				}
				break;
			}
			airNode = airNode->next;
		}
	}
	printf("삭제 완료\n");
	system("pause");
}
