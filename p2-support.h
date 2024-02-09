////////////////////////////////////////////////////////////////////////
//
// File           : p2-support.h
// Description    : Header file for project2 
// Author         : ***Type Author Name ***
// Date           : ***Type the date Date you completed***
// Notes          : ***Type bug fixes/other with dates for your records 

#ifndef P2Header //To prevent double inclusion of header
#define P2Header //To prevent double inclusion of header

#include <stdio.h>
#define byID 1
#define byNAME 2
#define dbSIZE 100
#define idSIZE 6
#define nameSIZE 10
#define emailSIZE 20


typedef struct date// do not modify
{
  int day; 
  int month;
  int year;
}date;

typedef struct Employee
{
  char ID[idSIZE];
  char first_name[nameSIZE];
  char last_name[nameSIZE];
  char email[emailSIZE];
  double salary;
  date hire_date;

}employee, *employee_ptr;

typedef struct DataBase
{
  //a pointer to first element of empoloyee array
  employee_ptr emp; 
  //number of employees in database
  int total;
}*dataBase_ptr;

// Functional Prototypes

// Function     : initialize
// Description  : This function creates an array in the database
//                then initalializes each array elemet with the data 
//                in the given file
// Inputs       : a pointer to DataBase struct
// Output       : none
void initialize (struct DataBase *db);
//Write formal comments for each function header. 
//In the same format with the initialize function
// Function    : create_record
// Description : This function creates the record of an employee and adds the record to the data base.
//
//
// Inputs      : employee struct members, and database struct
// Output      : none
void create_record (char* id, char* first, char* last, char* email, double salary, date hire_date,struct DataBase *db);//specify parameters types. Clues are in the initalize function.



// Funtcion    : print_title
// Description : This function prints the top title or header of the database 
//
//
// Input       : none
// Output      : none
void print_title ();


// Function    : display_menu
// Description : this function displays a numbered menu which will display specific filters based on a value the user inputs 
//
//
// Input       : a database pointer
// Output      : none
void display_menu (dataBase_ptr);

//other function headers here

//Function     : save
//Description  : this function saves the current data from database into a  file
//
//
//Input        : a database pointer
//Output       : none

void save(dataBase_ptr);


void sort_id(dataBase_ptr db);


void sort_hire_date(dataBase_ptr db);


void display_emp(dataBase_ptr db);


void search_emp_id(dataBase_ptr db);


void search_emp_last(dataBase_ptr db);


void delete_emp_id(dataBase_ptr db);



#endif //To prevent double inclusion of header
