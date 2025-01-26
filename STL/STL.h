#include <stdio.h>

typedef struct String
{
  struct String* next;
  size_t sz;
  char data;
} String;

String* CreateString(const char* data);
String* Append(String* string, String* string2);
void PrintString(String* string);

