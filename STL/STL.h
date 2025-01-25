#include <stdio.h>

typedef struct String
{
  struct String* next;
  int sz;
  char data;
} String;

String* CreateString(const char* data);
void PrintString(String* string);


