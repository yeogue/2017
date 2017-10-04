#include "air.h"

void airLog(LIST* airList, LIST* empList, LIST* custList) {
	NODE* delNode;
	FILE* f;

	f = fopen("C:\\Users\\BIT\\Desktop\\airLog.txt", "wb");

	delNode = airList->head;
	while(delNode != NULL) {
		fwrite((AIR*)delNode->data, sizeof(AIR), 1, f);
		delNode = delNode->next;
	}
	fclose(f);

	f = fopen("C:\\Users\\BIT\\Desktop\\seatLog.txt", "wb");

	delNode = airList->head;
	while(delNode != NULL) {
		fwrite((SEAT*)((AIR*)delNode->data)->seat, sizeof(SEAT), 1, f);
		delNode = delNode->next;
	}
	fclose(f);

	f = fopen("C:\\Users\\BIT\\Desktop\\empLog.txt", "wb");

	delNode = empList->head;
	while(delNode != NULL) {
		fwrite((EMP*)delNode->data, sizeof(EMP), 1, f);
		delNode = delNode->next;
	}
	fclose(f);

	f = fopen("C:\\Users\\BIT\\Desktop\\custLog.txt", "wb");

	delNode = custList->head;
	while(delNode != NULL) {
		fwrite((CUST*)delNode->data, sizeof(CUST), 1, f);
		delNode = delNode->next;
	}
	fclose(f);
}
