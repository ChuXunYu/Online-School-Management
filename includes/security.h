#ifndef SECURITY_H
#define SECURITY_H

#include <stdio.h>
#include <stdlib.h>
#include "student.h"
#include "teacher.h"

#define P 10007
#define Q 10009
#define E 65537
#define N (P * Q)
#define PHI ((P - 1) * (Q - 1))
#define D 35910881

#define DIRECT_ID 114514 
#define DIRECT_PASSWORD 1919810
#define FACILITY_RESERVE_COST 5

long long quick_pow(long long base, long long power, long long mod);
long long encrypt(long long original_password);
long long decrypt(long long ciphertext);

void Inital_password(Student* students, int student_number, Teacher* teachers, int teacher_number);
void Read_Password(Student* students, int student_number, Teacher* teachers, int teacher_number, TreeNode* root);
void Read_Money(Student* students, int student_number, Teacher* teachers, int teacher_number, TreeNode* root);

#endif 