#include "bus.h"

void u3(BUSLIST* busList, CUSTOMER* customer) {
	BUS* bus;
	BUSLINK* busLink;
	int num = 0;
	
	num = customer->busInfo;
	busLink = busList->first;
	while(num - 1) {
		busLink = busLink->nextBus;
		num--;
	}
	bus = busLink->data;

	bus->seat[customer->seat - 1] = 'O';
}
