#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define IDLEN 10
#define PASSWORDLEN 10
#define BOOKLEN 30
#define USERNAMELEN 10

typedef struct book BOOK;
typedef struct list LIST;
typedef struct node NODE;
typedef struct user USER;

struct list {
	NODE* head;
	NODE* tail;
};

struct node {
	NODE* prev;
	void* data;
	NODE* next;
};

struct book {
	int bookNumber;
	char bookName[BOOKLEN];
	char sign;
	char* userName; // USER의 userName 포인터
};

struct user {
	char id[IDLEN];
	char password[PASSWORDLEN];
	char userName[USERNAMELEN];
	char* bookName; // BOOK의 bookName 포인터
};

void library(void);

void addBook(LIST*);
void inputBookInfo(BOOK*);

void printBook(LIST*);
void printBookInfo(NODE*);

NODE* searchBook(LIST*);
NODE* searchNumber(LIST*);
NODE* searchName(LIST*);

void modBook(LIST*);
void modNumber(LIST*, NODE*);
void modName(LIST*, NODE*);

void delBook(LIST*);

/////////////////////////////////////////

void signUp(LIST*);
void inputUserInfo(USER*);

void login(LIST*);

void modUser(LIST*);
void modPass(LIST*, NODE*);
void modUserName(LIST*, NODE*);

void delUser(LIST*);

void lentBook(LIST*);

void lentList(LIST*);

void returnBook(LIST*);
