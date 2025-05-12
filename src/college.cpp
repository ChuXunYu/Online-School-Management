#include "college.h"
#include <ctype.h>
#include <windows.h>

void Admin_College(int* number) 
{
    int college_number = *number+1;
    FILE *college_file = fopen(COLLEGE_URL,"a+");
    char college_name[25];
    while (scanf("%s",college_name)==1)
    {
        int has_digit=0;
        for (int i=0;i<strlen(college_name);i++) 
        {
            if(isdigit(college_name[i]))
            {
                has_digit=1;
                break;
            }
        }
        if (!has_digit) 
        { 
            fprintf(college_file,"%d %s\n",college_number*1000,college_name);
            college_number++;
        }
    }
    fclose(college_file);
    college_number-=1;
    (*number)=college_number;
}

void Write_File_College_Number(int number)
{
    FILE* fp = fopen(COLLEGE_NUMBER_URL,"w+");
    fprintf(fp,"%d",number);
    fclose(fp);
}

void Read_File_College_Number(int *number)
{
    FILE *fp = fopen(COLLEGE_NUMBER_URL, "r+");
    if(fp) 
    {
        int result = fscanf(fp, "%d", number);
        if (result == 1)
        {
            return;
        }
        else
        {
            *number = 0;
        }
        fclose(fp);
    } 
    else
    {
        *number = 0;
    }
}

Colleges* Read_College(int college_number) 
{
    FILE *college_file=fopen(COLLEGE_URL,"r");
    if(college_file==NULL) 
    {
        perror("文件打开失败");
        return NULL;
    }
    Colleges* colleges = (Colleges*)malloc(sizeof(Colleges) * (college_number));
    if(colleges==NULL)
    {
        perror("内存分配失败");
        fclose(college_file);
        return NULL;
    }
    for(int i=0;i<college_number;i++) 
    {
        if (fscanf(college_file, "%d %s", &colleges[i].id, colleges[i].college_name) != 2) 
        {
            perror("读取文件失败");
            free(colleges);
            fclose(college_file);
            return NULL;
        }
    }
    fclose(college_file);
    return colleges;
}

void Print_College(Colleges* colleges, int college_number)
{
    printf("已添加的学院列表：\n");
    for(int i=0;i<college_number;i++)
    {
        printf("%05d %s\n",colleges[i].id,colleges[i].college_name);
    }
}

void Read_File_Major_Number(int *major_number) 
{
    FILE *fp = fopen(MAJOR_NUMBER_URL, "r");
    if (fp) 
    {
        if(fscanf(fp, "%d",major_number)!=1)
        {
            *major_number=0;
        }
    } 
    else 
    {
        *major_number = 0;
    }
    fclose(fp);
}

void Admin_Major(Colleges* colleges, int college_number, int* major_number)
{
    FILE *major_file = fopen(MAJOR_URL, "a+"); 
    if(!major_file){
        perror("文件打开失败");
        return;
    }
    int major_counter=*major_number;
    int college_id;
    char major_name[23];
    while(scanf("%d %s",&college_id,major_name)==2)
    {
        int valid_college=0;
        for(int i=0;i<college_number;i++) 
        {
            if(college_id==colleges[i].id) 
            {
                valid_college=1;
                ++major_counter;
                fprintf(major_file, "%d %s %d\n",college_id+(major_counter),
                        major_name,college_id);
                break;
            }
        }
        if(!valid_college){
            printf("Invalid college ID. Please enter a valid college ID.\n");
        }
    }
    fclose(major_file);
    *major_number = major_counter;
}

void Write_File_Major_Number(int number)
{
    FILE* fp = fopen(MAJOR_NUMBER_URL, "w");
    if (!fp)
    {
        perror("Failed to open Major_number.txt for writing");
        exit(EXIT_FAILURE);
    }
    fprintf(fp,"%d",number);
    fclose(fp);
}

Major* Read_Major(int major_number) 
{
    FILE *file = fopen(MAJOR_URL,"r");
    if(!file){
        perror("文件打开失败");
        return NULL;
    }
    Major* majors = (Major*)malloc(sizeof(Major)*major_number);
    if (!majors){
        perror("内存分配失败");
        return NULL;
    }
    for (int i = 0; i <major_number;i++) {
        fscanf(file, "%d %s %d", &majors[i].id, majors[i].name, &majors[i].college_id);
    }
    fclose(file);
    return majors;
}

bool select_college(Colleges* colleges, int college_number, char* college)
{
    Print_College(colleges,college_number);
    printf("请在上述学院中选择一个学院（输入学院编号）\n");
    int choice;
    scanf("%d",&choice); 
    for(int i=0;i<college_number;i++)
    {
        if(colleges[i].id == choice)
        {
            strcpy(college,colleges[i].college_name);
            return true;
        }
    }
    return false;
}

bool select_major(Colleges* colleges, int college_number, Major* majors, int major_number, char* college, char* major)
{
    int college_index = 0;
    for(int j=0;j<college_number;j++)
    {
        if(strcmp(colleges[j].college_name,college)==0)
        {
            college_index = colleges[j].id;
        } 
    } 
    printf("该学院下的专业列表：\n");
    for(int i=0;i<major_number;i++)
    {
        if(majors[i].college_id == college_index)
        {
            printf("%05d %s : %05d %s\n",colleges[i].id,colleges[i].college_name,
                majors[i].id,majors[i].name);
        }
    }
    printf("请在上述专业中选择一个专业（输入专业编号）\n");
    int choice;
    scanf("%d",&choice); 
    for(int i=0;i<major_number;i++)
    {
        if(majors[i].id == choice)
        {
            strcpy(major,majors[i].name);
            return true;
        }
    }
    return false;
}

void inputStudentInfo(Colleges* colleges, int college_number, Major* majors, int major_number, int* student_number) 
{
    int n;
    printf("请输入要添加的学生数量（整数）: ");
    scanf("%d", &n);
    Student* students = (Student*)malloc(sizeof(Student) * n);
    *student_number += n;
    for (int i=0; i<n; i++)
    {
        printf("\n请输入第 %d 名学生信息:\n",i+1);
        printf("ID: ");
        scanf("%d", &students[i].id);
        printf("姓名: ");
        scanf("%s", students[i].name);
        printf("性别（男生或女生）：");
        char gender[3];
        while(true)
        {
            scanf("%s", gender);
            if(strcmp(gender,"男生")==0 || strcmp(gender,"女生")==0)
            {
                strcpy(students[i].gender,gender);
                break;
            }
            else
            {
                printf("请输入有效的性别：");
            }
        }
        select_college(colleges,college_number,students[i].college);
        select_major(colleges,college_number,majors,major_number,
                        students[i].college,students[i].major);
        printf("班级ID（四位有效整数）：");
        int class_id;
        while(true)
        {
            scanf("%d", &class_id);
            if(class_id>=1000 && class_id<=9999)
            {
                students[i].Class = class_id;
                break;
            }
            else
            {
                printf("请输入有效的班级ID：");
            }
        }
        students[i].money = 0;
        students[i].password = students[i].id; 
        FILE* fp = fopen(STUDENT_DATA_URL,"a+");
        if(fp)
        {
            fprintf(fp,"%d %s %s %s %s %d\n",students[i].id,students[i].name,students[i].gender,
            students[i].college,students[i].major,students[i].Class);
        }
        fclose(fp);
        free(students);
    }
}

void inputTeacherInfo(Colleges* colleges, Course courses[], int college_number, int* teacher_number)
{
    int n;
    printf("请输入要添加的教师数量（整数）: ");
    scanf("%d", &n);
    *teacher_number += n;
    Teacher* teachers=NULL;
    if(n>0) 
        teachers = (Teacher*)malloc(sizeof(Teacher) * n);
    for (int i=0;i<n;i++)
    {
        printf("\n请输入第 %d 名教师信息:\n",i+1);

        printf("ID: ");
        scanf("%d", &teachers[i].id);
        printf("姓名: ");
        scanf("%s", teachers[i].name);
        printf("性别（男生或女生）：");
        char gender[3];
        while(true)
        {
            scanf("%s", gender);
            if(strcmp(gender,"男生")==0 || strcmp(gender,"女生")==0)
            {
                strcpy(teachers[i].gender,gender);
                break;
            }
            else
            {
                printf("请输入有效的性别：");
            }
        }
        select_college(colleges,college_number,teachers[i].college);
        printf("以下是可教授的课程: \n");
        for(int j=0;j<4;j++)
        {
            printf("%s\n",courses[j].name);
        }
        while(true)
        {
            printf("请从上述课程中选择一个（输入课程名）：");
            char course_name[20]; 
            scanf("%s", course_name);
            bool result = false;
            for(int j=0;j<4;j++)
            {
                if(strcmp(course_name,courses[j].name)==0)
                {
                    strcpy(teachers[i].course,courses[j].name);
                    result = true;
                    break;
                }
            }
            if(result) break;
        }
        while(true)
        {
            printf("请输入教授的四位班级编号：");
            scanf("%d",&teachers[i].teaching_class);
            if(teachers[i].teaching_class>=1000 && teachers[i].teaching_class<=9999)
            {
                break;
            }
            else
            {
                printf("请输入有效的班级编号：");
            }
        }
        teachers[i].password = teachers[i].id;
        FILE* fp = fopen(TEACHER_DATA_URL,"a+");
        if(fp)
        {
            fprintf(fp,"%d %s %s %s %s %d\n",teachers[i].id,teachers[i].name,teachers[i].gender,
            teachers[i].college,teachers[i].course,teachers[i].teaching_class);
        }
        fclose(fp);
    }
    if(teachers!=NULL)
        free(teachers);
} 