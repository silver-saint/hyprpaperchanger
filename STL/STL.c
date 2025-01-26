#include "STL.h"
#include <stdlib.h>
#include <string.h>


String* CreateString(const char* data)
{
  const size_t stringLen = strlen(data);
  size_t currentSize = 0;
  String* newString = (String*) malloc((stringLen + 1) * sizeof(String*));
  while(*(data) != '\0')
  {
    newString[currentSize].data = *data;
    if(currentSize < stringLen)
    {
      newString[currentSize].next = &newString[currentSize + 1];
    }
    else 
    {
      newString[currentSize].next = NULL;
    }
    currentSize++;
    data++;
  }
  newString->sz = currentSize;
  return newString;
}
void PrintString(String *string)
{
  while((string->data != '\0'))
  {
    printf("%c", string->data);
    string = string->next;
  }
  printf("\n");
}
String* Append(String* string, String* string2)
{ 
  String* newString = (String*)malloc(string->sz + string2->sz * sizeof(String*));
  while(string->data != '\0')
  {
    newString->data = string->data;
    newString = newString->next;
    string = string->next;
  }
  while(string2->data != '\0')
  {
    newString->data = string2->data;
    newString = newString->next;
    string2 = string2->next;
  }
  newString->next = NULL;
  return newString;
}
