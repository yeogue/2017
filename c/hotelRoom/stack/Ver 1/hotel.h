#include <stdio.h>
#include <stdlib.h>

#define HOTELSIZE 10

typedef struct stack STACK;
typedef struct room ROOM;

struct room {
	char check;
	int floor;
	int roomSize;
	ROOM* next;
};

struct stack {
	ROOM* top;
};

void hotel_stack(void);

ROOM** createHotel_stack(STACK*);

void checkRoom_stack(STACK);

int roomSelect_stack(ROOM**);

void roomChange_stack(ROOM**, int*);

void roomCancel_stack(ROOM**, int*);
