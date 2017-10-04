#include <stdio.h>
#include <stdlib.h>

typedef struct bus BUS;
typedef struct busLink BUSLINK;
typedef struct busList BUSLIST;
typedef struct customer CUSTOMER;

struct bus {
	char seat[30];
	char dest[10];
};

struct busLink {
	BUS* data;
	BUSLINK* nextBus;
};

struct busList {
	BUSLINK* first;
	BUSLINK* last;
};

struct customer {
	int seat;
	char name[10];
	int busInfo;
};

void a1(BUSLIST*);
BUSLINK* createBus(void);
void linkBus(BUSLIST*, BUSLINK*);

void a2(BUSLIST*);
void printBusList(BUSLIST*);
void deleteBus(BUSLIST*, int);

void a3(BUSLIST*);
void seat(BUSLIST*, int);

CUSTOMER* u1(BUSLIST*);
void changeSignal(BUSLIST*, CUSTOMER*, int);

void u2(BUSLIST*, CUSTOMER*);
