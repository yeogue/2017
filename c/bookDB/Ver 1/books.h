#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct Book {
	int bookNumber;
	char title[30];
	char writer[30];
} book;

void Add(void);
void Print(const book* books);
void Search(const book* books);
void Modify(book* books);
void Delete(book* books);
void Exit(void);

extern book* allBooks;
