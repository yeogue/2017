#include "bus.h"

void a3(BUSLIST* busList) {
	int num = 0;

	printBusList(busList);
	printf("좌석 현황을 볼 버스 선택: ");
	scanf("%d", &num);

	seat(busList, num);
}

void seat(BUSLIST* busList, int num) {
	BUS* bus;
	BUSLINK* busLink;
	int i = 0;
	
	busLink = busList->first;
	while(num - 1) {
		busLink = busLink->nextBus;
		num--;
	}
	bus = busLink->data;
	for(i = 1; i < 11; i++) {
		printf("%2d ", i);
	}
	printf("\n");
	for(i = 0; i < 10; i++) {
		printf("%2c ", bus->seat[i]);
	}
	printf("\n");
	printf("\t통\t로\t\n");
	for(i = 10; i < 30; i++) {
		if((i%2)-1) {
			printf("%2c ", bus->seat[i]);
		}
	}
	printf("\n");
	for(i = 10; i < 30; i++) {
		if(i%2) {
			printf("%2c ", bus->seat[i]);
		}
	}
	printf("\n");
	for(i = 11; i < 31; i++) {
		if(i%2) {
			printf("%2d ", i);
		}
	}
	printf("\n");
	for(i = 11; i < 31; i++) {
		if((i%2)-1) {
			printf("%2d ", i);
		}
	}
	printf("\n");
	system("pause");
}
