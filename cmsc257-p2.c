#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "p2-support.h"

FILE* dbf;//File structure for Standard I/O

int main (int argc, char* argv[]){
  dbf = NULL;

  //Read file if a file name is entered 
  if(argc == 2)
    dbf = fopen ("argv[1]", "r");
  //Read database file if no file name is entered
  else if (argc ==1)
    dbf = fopen ("database", "r");
  else
    printf("Program can read one file only at a time");

  if (dbf ==NULL)
  {
    printf("File does not exist. \nEnter a valid file name when running the program. Such as: ./p2 database");
    return 0; 
  }

  struct DataBase* db; 
  db = malloc(sizeof(struct DataBase));
  initialize (db);
  display_menu (db);
  fclose (dbf);//close file
  return 0;
}

void initialize (struct DataBase *db)
{
  db->emp = malloc (sizeof (struct Employee) * 100);
  db->total = 0;
  char ID[idSIZE];
  char first_name[nameSIZE];
  char last_name[nameSIZE];
  char email[emailSIZE];
  double salary;
  char line[100];
  date hire_date;

  for (;;)
  {
    fgets (line, 100, dbf);// get a line from the file
    sscanf (line, "%s %s %s %s %lf %d/%d/%d\n", ID, first_name, last_name,
        email, &salary, &hire_date.month, &hire_date.day,
        &hire_date.year);
    create_record (ID, first_name, last_name, email, salary, hire_date, db);
    if (feof (dbf))
      break;
  }
}
