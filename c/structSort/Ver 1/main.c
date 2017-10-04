#include "sort.h"

int main(void) {
	LIST userList;
	USER* userArray;
	int arraySize = 0;

	userList.head = NULL;
	userList.tail = NULL;

	user(&userList);

	userArray = pointerArray(&userList, &arraySize);

	selectSort(userArray, arraySize);
	
	return 0;
}
