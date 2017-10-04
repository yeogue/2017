#include "bus.h"

void a1(BUSLIST* busList) {
	BUSLINK* newBus;
	
	newBus = createBus();
	linkBus(busList, newBus);
}

BUSLINK* createBus(void) {
	BUS* newBus;
	BUSLINK* bus;
	int i = 0;

	newBus = (BUS*)malloc(sizeof(BUS));
	bus = (BUSLINK*)malloc(sizeof(BUSLINK));

	for(i = 0; i < 30; i++) {
		newBus->seat[i] = 'O';
	}
	printf("목적지 입력: ");
	scanf("%s", newBus->dest);
	bus->data = newBus;
	bus->nextBus = NULL;
	printf("버스 배차 완료\n");
	system("pause");

	return bus;
}

void linkBus(BUSLIST* busList, BUSLINK* newBus) {
	if(busList->first == NULL) {
		busList->first = newBus;
		busList->last = newBus;
		return;
	}
	busList->last->nextBus = newBus;
	busList->last = newBus;
}
