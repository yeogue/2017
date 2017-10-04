#include "bus.h"

void a2(BUSLIST* busList) {
	int num = 0;

	printBusList(busList);
	printf("취소할 버스를 선택: ");
	scanf("%d", &num);
	deleteBus(busList, num);
}

void printBusList(BUSLIST* busList) {
	BUSLINK* busCur;
	int i = 0;

	busCur = busList->first;
	printf("==출발 대기 중인 버스==\n");
	while(busCur != NULL) {
		printf("버스 [%d] - 목적지 %s\n", ++i, busCur->data->dest);
		busCur = busCur->nextBus;
	}
}

void deleteBus(BUSLIST* busList, int num) {
	BUSLINK* busCur;
	BUSLINK* busCurBefore;

	busCur = busList->first;
	if(num == 1) {
		busList->first = busCur->nextBus;
		free(busCur->data);
		free(busCur);
		printf("해당 버스가 삭제되었습니다.\n");
		system("pause");
		return;
	}
	while(num - 1) {
		busCurBefore = busCur;
		busCur = busCur->nextBus;
		num--;
	}
	busCurBefore->nextBus = busCur->nextBus;
	free(busCur->data);
	free(busCur);
	printf("해당 버스가 삭제되었습니다.\n");
	system("pause");
}
