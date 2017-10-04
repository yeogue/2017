#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define IDLEN 20
#define PASSWORDLEN 20
#define USERNAMELEN 10

typedef struct list LIST;
typedef struct node NODE;
typedef struct userInfo USER;

struct list {
	NODE* head;
	NODE* tail;
};

struct node {
	NODE* next;
	NODE* prev;
	USER* data;
};

struct userInfo {
	char id[IDLEN];
	char password[PASSWORDLEN];
	char userName[USERNAMELEN];
};

void user(LIST*);

void userAdd(LIST*);
NODE* newUserAdd(LIST*);

void userDelete(LIST*);

void userModify(LIST*);
void userNameMod(NODE*);
void userPasswordMod(NODE*);

void userPrint(LIST*);

NODE* userSearch(LIST*);

USER* pointerArray(LIST*, int*);

void selectSort(USER*, int);
