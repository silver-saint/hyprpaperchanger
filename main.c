#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <sys/param.h>
#include "STL/STL.h"



#define MAX_NUM_BACKGROUNDS 18
#define MAX_FILENAME_LEN 100
#define FORMATS_SIZE(arr) (sizeof(arr) / sizeof((arr)[0]))

int ChangeDirToLocation(const char* location, char currDir[]);
int FindFolder(char currDir[], const char* folderName);
void ListAllBackgrounds(char currDir[], char backgrounds[]);
int IsBackgroundFile(const char* name);

int main(void)
{
  printf("%d", stuff());
  const char* location = getenv("HOME");
    if(location == NULL)
    {
      printf("Couldn't get working directory\n");
      return -1;
    }
  const size_t totalArrSize = MAX_NUM_BACKGROUNDS * MAX_FILENAME_LEN;
  const char* folderName = "backgrounds";
  const char* configDir = "/.config/hypr/";
  const size_t strLen1 = strlen(location);
  const size_t strLen2 = strlen(configDir);
  char backgrounds[totalArrSize];
  int findFolderSuccess = 0;
  int changeDirSuccess = 0;
  int changeToResultDir = 0;
  char currDir[MAXPATHLEN];
  char* resultDir = malloc(strLen1 + strLen2 + 1);
  strcpy(resultDir, location);
  strcat(resultDir, configDir);
  if(resultDir == NULL)
    {
      printf("Couldn't fetch result directory");
      return -1;
    }
  changeDirSuccess = ChangeDirToLocation(location, currDir);
  if(changeDirSuccess)
    {
      findFolderSuccess = FindFolder(currDir, folderName);
    }
  else
    {
      printf("Program could not change directory... terminating.");
    }

  if(findFolderSuccess)
    {
      ListAllBackgrounds(currDir, backgrounds);
    }
  
   int bg;
   printf("Enter a number between 1 and %d\n", MAX_NUM_BACKGROUNDS);
  
  scanf("%d", &bg);
  changeToResultDir = ChangeDirToLocation(resultDir, currDir);
 
  if(changeToResultDir)
    {
      FILE *file = fopen("hyprpaper.conf", "w");
      if(file == NULL)
	{
	  printf("Can't open file");
	  return -1;
	}
      //first buffer;
       const char* preload = "preload = ";
       const char* bgPath = "~/backgrounds/";
       const char* img = backgrounds + ((bg - 1) * MAX_FILENAME_LEN);
       char imgPath[256];
       strcpy(imgPath, preload);
       strcat(imgPath, bgPath);
       strcat(imgPath, img);

       const char* wallpaper = "wallpaper = ";
       const char* display = "DP-1, ";
       char wpPath[512];
       strcpy(wpPath, wallpaper);
       strcat(wpPath, display);
       strcat(wpPath, bgPath);
       strcat(wpPath, img);
       fprintf(file, "%s\n",imgPath);
       fprintf(file, "%s", wpPath);
      fclose(file);
      printf("Successfully changed Wallpaper to %s. Please Restart your system or refresh your hyprpaper.conf\n", img);      
    }
  return 0;
}

int ChangeDirToLocation(const char* location, char currDir[])
{
  getcwd(currDir, MAXPATHLEN);
  if(strcmp(currDir, location) != 0)
    {
      int success = chdir(location);
      if(success == 0)
	{
	  getcwd(currDir, MAXPATHLEN);
          return 1; 
	}
    }
  return 0;
}

int FindFolder(char currDir[], const char* folderName)
{
  DIR *d;
  struct dirent *dir;
  d = opendir(currDir);
  if(d)
    {
      while((dir = readdir(d)) != NULL)
	{
	  if(strcmp(dir->d_name, folderName) == 0)
	    {
	      int success = chdir(dir->d_name);
	      if(success == 0)
		{
		  getcwd(currDir, MAXPATHLEN);
		  break;
		}
	      else
		{
		  return 0;
		}
	    }
	}
      closedir(d);
    }
  return 1;
}

void ListAllBackgrounds(char currDir[], char backgrounds[])
{
  DIR *d;
  struct dirent *dir;
  d = opendir(currDir);
  if(d)
    {
      int i = 0;
      while((dir = readdir(d)) != NULL)
	{
	  if(IsBackgroundFile(dir->d_name))
	    {
	      strcpy((backgrounds + (i * MAX_FILENAME_LEN)), dir->d_name);
	      i++;
	    }
	}
      closedir(d);
    }
   printf("Select one of the following backgrounds\n");
   for(int i = 0; i < MAX_NUM_BACKGROUNDS; i++)
    {
      printf("%d: %s\n", i + 1, backgrounds + i * MAX_FILENAME_LEN);
    }
  
  return;
}
int IsBackgroundFile(const char* name)
{

  const char *formats[] = {"png", "jpg", "jpeg"};
  const size_t size = FORMATS_SIZE(formats);
  for(size_t i = 0; i < size; i++)
    {
      const char* currFormat = formats[i];
      if(strstr(name, currFormat) != NULL)
	{
	  return 1;
	}
    }
 
  return 0;
}
