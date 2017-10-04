#include "hotel.h"

ROOM** createHotel_stack(STACK* stack) {
	int floor;
	int room;
	int i;
	int j;
	ROOM** d_floor;
	ROOM* d_room;

	stack->top = NULL;

	printf("층 수 입력: ");
	scanf("%d", &floor);
	d_floor = (ROOM**)malloc(sizeof(ROOM*)*floor);
	for(i = 0; i < floor; i++) {
		printf("%d층의 방 수 입력: ", i+1);
		scanf("%d", &room);
		d_room = (ROOM*)malloc(sizeof(ROOM)*room);
		for(j = 0; j < room; j++) {
			d_room[j].check = 'O';
			d_room[j].floor = i+1;
			d_room[j].next = NULL;
			d_room[j].roomSize = HOTELSIZE/room;
			if(stack->top == NULL) {
				stack->top = &d_room[j];
			}
			else {
				d_room[j].next = stack->top;
				stack->top = &d_room[j];
			}
			d_floor[i] = d_room;
		}
	}
//	for(i = 0; stack->top != NULL; i++) {
//		printf("'%c' %d %d\n", stack->top->check, stack->top->floor, stack->top->roomSize);
//		stack->top = stack->top->next;
//	}
	return d_floor;
}

void checkRoom_stack(STACK stack) {
	int i = 0;
	int floor;
	int roomSize;

	while(1) {
		floor = stack.top->floor;
		roomSize = stack.top->roomSize;

		printf("|");
		for(i = 0; i < roomSize; i++) {
			printf(" ");
		}
		printf("%c", stack.top->check);
		for(i = 0; i < roomSize; i++) {
			printf(" ");
		}
		stack.top = stack.top->next;
		if(stack.top == NULL) {
			break;
		}
		if(floor != stack.top->floor) {
			printf("|");
			printf(" %d01호\t\t방 크기: %d\n", floor, roomSize);
			printf("\n");
		}
	}
	printf("|");
	printf(" %d01호\t\t방 크기: %d\n", floor, roomSize);
	printf("\n");
}
