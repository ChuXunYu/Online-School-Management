#ifndef COLLEGE_H
#define COLLEGE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "student.h"
#include "teacher.h"

#define COLLEGE_URL "data/college/colleges.txt"
#define COLLEGE_NUMBER_URL "data/college/College_number.txt"
#define MAJOR_URL "data/college/majors.txt"
#define MAJOR_NUMBER_URL "data/college/Major_number.txt"

typedef struct _Colleges{
    int id;
    char college_name[23];
}Colleges;

typedef struct _Major{
    int college_id;
    int id;
    char name[23];
}Major;

void Admin_College(int* number);
void Write_File_College_Number(int number);
void Read_File_College_Number(int* number);
Colleges* Read_College(int college_number);
void Print_College(Colleges* colleges, int college_number);

void Read_File_Major_Number(int *major_number);
void Admin_Major(Colleges* colleges, int college_number, int* major_number);
void Write_File_Major_Number(int number);
Major* Read_Major(int major_number);

bool select_college(Colleges* colleges, int college_number, char* college);
bool select_major(Colleges* colleges, int college_number, Major* majors, int major_number, char* college, char* major);

void inputStudentInfo(Colleges* colleges, int college_number, Major* majors, int major_number, int* student_number);
void inputTeacherInfo(Colleges* colleges, Course courses[], int college_number, int* teacher_number);

#endif 