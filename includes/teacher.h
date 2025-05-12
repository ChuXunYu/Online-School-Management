#ifndef TEACHER_H
#define TEACHER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "student.h"

#define TEACHER_DATA_URL "data/teacher/Teachers_data.txt" 
#define TEACHER_NUMBER_URL "data/teacher/Teacher_number.txt"
#define TEACHER_PASSWORD_URL "data/teacher/teacher_password.txt"

typedef struct _Courses{
    float credit;
    char name[20];
}Course;

typedef struct _Teacher {
    char gender[3];
    int id;
    int teaching_class;
    long long password;
    char name[10];
    char course[20];
    char college[23];
    struct _Teacher *next;
}Teacher;

void Read_File_Teacher_Number(int* teacher_number);
void Write_File_Teacher_Number(int teacher_number);
Teacher* Read_Teachers(int teacher_number);
bool Teacher_Login(Teacher* teachers, Teacher *target_teacher, int teacher_number);
void Teacher_Import_Grade(Student* students, int student_number, Teacher *teacher, int teacher_number, Course courses[]);

double Total_GPA_Calculation(Student* student, Course courses[], int student_number);
void Update_GPA(Student* student, Course courses[], int student_number);

#endif 