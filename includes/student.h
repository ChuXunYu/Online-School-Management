#ifndef STUDENT_H
#define STUDENT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define STUDENT_DATA_URL "data/student/Students_data.txt" 
#define STUDENT_NUMBER_URL "data/student/Student_number.txt"
#define STUDENT_PASSWORD_URL "data/student/student_password.txt"
#define MONEY_URL "data/student/money.txt"
#define ROOM_CHANGE_REQUESTS_URL "data/student/room_change_request.txt"
#define ROOM_LEAVE_REQUESTS_URL "data/student/room_leave_request.txt"

struct _BusSchedule;

typedef struct _Scores{
    int Math;
    int English;
    int Computer;
    int Politics;
}Scores;

typedef struct _Student {
    int Class;
    char gender[3];
    int id; 
    int dorm_index;
    double money;
    double GPA;
    long long password;
    char name[10];
    char major[20];
    char college[23];
    Scores scores;
    struct _Student *next;
}Student;

typedef struct TreeNode{
    Student* student;
    struct TreeNode* left;
    struct TreeNode* right;
}TreeNode;

typedef struct _HashTable {
    Student* students[10003];  
}HashTable;

void Read_File_Student_Number(int* student_number);
void Write_File_Student_Number(int student_number);
Student* Read_Students(int student_number);
void Undefined_Inital_Stu(Student* students, int student_number);
bool Student_Login(Student* students, Student *target_student, int student_number);
void Student_Watch_Grade(Student* student);
void assignDormitory(Student* students, int numStudents);
void Moneys_System(Student* student, int student_number, struct _BusSchedule *b1, struct _BusSchedule *b2, int bn1, int bn2);
void Students_Read_Grade_File(TreeNode* root, int student_number);

TreeNode* insert(TreeNode* root, Student* student);
TreeNode* createBinaryTree(Student* students, int size);
void printInOrder(TreeNode* node);
void freeTree(TreeNode* node);
TreeNode* find(TreeNode* root, int id);

int hashFunction(int id);
HashTable* createHashTable(void);
bool insertStudent(HashTable* table, Student* student);
Student* findStudent(HashTable* table, int id);
bool deleteStudent(HashTable* table, int id);
bool freeHashTable(HashTable* table);

int getCourseScore(Student* student, const char* courseName);
int compareStudents(Student* student1, Student* student2, const char* courseName);
void merge(Student* array, int left, int mid, int right, const char* courseName);
void mergeSort(Student* array, int left, int right, const char* courseName);
void sortByCourseScore(Student* students, int size, const char* courseName);

#endif 