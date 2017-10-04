#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define DESTLEN 10
#define NAMELEN 10
#define JOBLEN 10

typedef struct node NODE;
typedef struct list LIST;
typedef struct air AIR;
typedef struct seat SEAT;
typedef struct emp EMP;
typedef struct cust CUST;

struct node {
	NODE* prev;
	NODE* next;
	void* data;
};

struct list {
	NODE* head;
	NODE* tail;
};

struct air {
	char dest[DESTLEN];
	int money;
	SEAT* seat;
};

struct seat {
	char s;
	char* cust;
};

struct emp {
	char name[NAMELEN];
	char job[JOBLEN];
	int age;
	int num;
};

struct cust {
	char name[NAMELEN];
	int money;
	int num;
};

void air(void);

void airAdd(LIST*);

void airDel(LIST*);

void airSeat(LIST*);
void airListPrint(LIST*);
void airSeatPrint(AIR*);

void airCust(LIST*);

void airMoney(LIST*);

void empAdd(LIST*);

void empJob(LIST*);
void empListPrint(LIST*);

void empMod(LIST*);

void empDel(LIST*);

CUST* custAdd(LIST*);

void custSeat(CUST*, LIST*);

void custSeatChange(CUST*, LIST*);

NODE* custSeatCancel(CUST*, LIST*);

void custDel(LIST*);
void custListPrint(LIST*);

void airLog(LIST*, LIST*, LIST*);

void fileOpen(LIST*, LIST*, LIST*);
