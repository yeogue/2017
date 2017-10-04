#include "bus.h"

CUSTOMER* u1(BUSLIST* busList) {
	int num = 0;
	CUSTOMER* customer;

	customer = (CUSTOMER*)malloc(sizeof(CUSTOMER));
	printBusList(busList);
	printf("예매할 버스를 선택: ");
	scanf("%d", &num);
	seat(busList, num);
	printf("예매할 좌석을 선택: ");
	scanf("%d", &customer->seat);
	printf("예매자 이름: ");
	scanf("%s", customer->name);
	changeSignal(busList, customer, num);
	customer->busInfo = num;

	return customer;
}

void changeSignal(BUSLIST* busList, CUSTOMER* customer, int num) {
	BUS* bus;
	BUSLINK* busLink;
	int i = 0;
	
	busLink = busList->first;
	while(num - 1) {
		busLink = busLink->nextBus;
		num--;
	}
	bus = busLink->data;
	if(bus->seat[customer->seat - 1] == 'X') {
		printf("좌석 예매 불가\n");
		return;
	}
	bus->seat[customer->seat - 1] = 'X';
}
