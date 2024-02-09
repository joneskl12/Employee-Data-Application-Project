#define _GNU_SOURCE		
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "p2-support.h"



void create_record (char* id, char* first, char* last, char* email, double salary, date hire_date, dataBase_ptr db)
{
  

  strncpy(db->emp[db->total].ID, id, sizeof(db->emp[db->total].ID));
  strncpy(db->emp[db->total].first_name, first, sizeof(db->emp[db->total].first_name));
  strncpy(db->emp[db->total].last_name, last, sizeof(db->emp[db->total].last_name));
  strncpy(db->emp[db->total].email, email,sizeof(db->emp[db->total].email));
  db->emp[db->total].salary = salary;
  db->emp[db->total].hire_date = hire_date;
  db->total++;

}


void print_title ()
{
  printf ("No. ID    Name          Email        Salary     Hire Date\n");
  printf ("--- ----- ------------- ------------ ---------- --/--/----\n");

}



void save (dataBase_ptr db)// this function is for saving the database into a text file
{
  FILE *dbfu;
  dbfu = fopen ("database_updated", "w");//open an Std IO file to write into
  if (dbfu == NULL)
  {
    printf ("File cannot be created");
    return;
  }
  for (int i = 0; i < db->total; i++)
  {
    fprintf (dbfu,"%5s %s %s %s %.2lf %d/%d/%d\n", db->emp[i].ID, db->emp[i].first_name, db->emp[i].last_name, db->emp[i].email, db->emp[i].salary, db->emp[i].hire_date.month, db->emp[i].hire_date.day, db->emp[i].hire_date.year);

  }

  fclose (dbfu);//close file after writing
  return;

}

int cmpfunc(const void * a, const void * b){
  struct Employee* var = (struct Employee*) a;
  struct Employee* var2 = (struct Employee*) b;

  if (var->hire_date.year != var2->hire_date.year){
    return var->hire_date.year - var2->hire_date.year;
  }

  if (var->hire_date.month != var2->hire_date.month){
    return var->hire_date.month - var2->hire_date.month;
  }

  return var->hire_date.day - var2->hire_date.day;

}

int stringcompare(const void * a, const void * b){
  struct Employee* var = (struct Employee*) a;
  struct Employee* var2 = (struct Employee*) b;

  return strcmp(var->ID, var2->ID);

}

void sort_id(dataBase_ptr db){
  qsort(db->emp, db->total, sizeof(struct Employee), stringcompare);
}

void sort_hire_date(dataBase_ptr db){
  qsort(db->emp, db->total, sizeof(struct Employee), cmpfunc);
}

void display_emp(dataBase_ptr db){
  int i = 0;

  for (i = 0; i < db->total; i++){
    char fullname[24] = {0};
    strcat(fullname, db->emp[i].first_name);
    strcat(fullname, " ");
    strcat(fullname, db->emp[i].last_name);
    printf("%-3.1d %5s %-13.13s %-12.12s $%9.2lf %.2d/%.2d/%.4d\n", i, db->emp[i].ID, fullname , db->emp[i].email, db->emp[i].salary, db->emp[i].hire_date.month, db->emp[i].hire_date.day, db->emp[i].hire_date.year);
  }
}

void search_emp_id(dataBase_ptr db){
  char id[idSIZE];
  printf("Enter the ID you are searching for\n");
  scanf("%s", id);
  int i = 0;
  int j = 0;
  for (i = 0; i < db->total; i++){
    if (strstr(db->emp[i].ID, id)){

      printf("Employee found:\n");
      if (j == 0){
        print_title();
        j = 1;
      }
      char fullname[24] = {0};
      strcat(fullname, db->emp[i].first_name);
      strcat(fullname, " ");
      strcat(fullname, db->emp[i].last_name);
      printf("%-3.1d %5s %-13.13s %-12.12s $%9.2lf %.2d/%.2d/%.4d\n", i, db->emp[i].ID, fullname , db->emp[i].email, db->emp[i].salary, db->emp[i].hire_date.month, db->emp[i].hire_date.day, db->emp[i].hire_date.year);


      return;
    }
  }
  printf("Employee with ID %s is not found.\n", id);

}

void search_emp_last(dataBase_ptr db){
  char last_name[nameSIZE];
  printf("Enter the Last Name you are searching for\n");
  scanf("%s", last_name);
  int found = 0;
  int i = 0;
  print_title();
  for (i = 0; i < db->total; i++){
    if(strcasestr(db->emp[i].last_name, last_name)){
      char fullname[24] = {0};
      strcat(fullname, db->emp[i].first_name);
      strcat(fullname, " ");
      strcat(fullname, db->emp[i].last_name);
      printf("%-3.1d %5s %-13.13s %-12.12s $%9.2lf %.2d/%.2d/%.4d\n", i, db->emp[i].ID, fullname, db->emp[i].email, db->emp[i].salary, db->emp[i].hire_date.month, db->emp[i].hire_date.day, db->emp[i].hire_date.year);
      found = 1;
    }
  }
  if (!found){
    printf("Employee with Last Name %s is not found. \n", last_name);
  }

}
void delete_emp_id(dataBase_ptr db){
  char id[idSIZE];
  printf("Enter the ID you are searching for\n");
  scanf("%s", id);
  print_title();
  int i = 0;
  int z = 0;
  for (i = 0; i < db->total; i++){
    if (strstr(db->emp[i].ID, id)){
      printf("The following employee is deleted:\n");
      if (z == 0){
        print_title();
        z = 1;
      }
      char fullname[24] = {0};
      strcat(fullname, db->emp[i].first_name);
      strcat(fullname, " ");
      strcat(fullname, db->emp[i].last_name);
      printf("%-3.1d %5s %-13.13s %-12.12s $%9.2lf %.2d/%.2d/%.4d\n", i, db->emp[i].ID, fullname, db->emp[i].email, db->emp[i].salary, db->emp[i].hire_date.month, db->emp[i].hire_date.day, db->emp[i].hire_date.year);

      int j = 0;
      for (j = i; j < db->total; j++){
        strcpy(db->emp[j].ID, db->emp[j + 1].ID);
        strcpy(db->emp[j].first_name, db->emp[j + 1].first_name);
        strcpy(db->emp[j].last_name, db->emp[j + 1].last_name);
        strcpy(db->emp[j].email, db->emp[j + 1].email);
        db->emp[j].salary = db->emp[j + 1].salary;
        db->emp[j].hire_date = db->emp[j + 1].hire_date;
      }
      db->total = db->total - 1;
      printf("\n");
      return;
    }
  }
  printf("Employee with ID %s not found.\n", id);
}


void display_menu (struct DataBase *db)
{
  int input = 0;
  while (input != 8)
  {
    puts
      ("\n**************************************************************");
    printf
      (  "********** Employee Database - Total Employees: %03d **********\n", db->total);
    puts
      ("**************************************************************\n");
    puts ("Choose one of the menu options below:");
    puts ("1. Sort by ID");
    puts ("2. Sort by Hire Date");
    puts ("3. Display all employees");
    puts ("4. Search employees by ID");
    puts ("5. Search employees by Last Name");
    puts ("6. Delete employee by ID");
    puts ("7. Save");
    puts ("8. Exit");

    scanf ("%d", &input);

    switch (input)
    {
      case 1:
        //call the function sorting by ID
        sort_id(db);
        break;
      case 2:
        //call the function for sorting by Hire Date
        sort_hire_date(db);
        break;
      case 3:
        //call the function for displaying employees
        print_title();
        display_emp(db);
        break;
      case 4:
        //call the function for searching employees by ID
        search_emp_id(db);
        break;
      case 5:
        search_emp_last(db);
        break;
      case 6:
        //call the function deleting employee by ID
        delete_emp_id(db);
        break;
      case 7:
        save (db);
        break;
      case 8:
        //free all allocated memory
        free(db->emp);
        free(db);
        printf("Bye!\n");
        break;

    }
  }





}
