#include "teacher.h"
#include "security.h"
#include <windows.h>
#include <ctype.h>

void Read_File_Teacher_Number(int* teacher_number)
{
    FILE *fp = fopen(TEACHER_NUMBER_URL, "r");
    if(fp)
    {
        if(fscanf(fp,"%d",teacher_number)!=1)
        {
            *teacher_number = 0;
        }
    }
    else
    {
        *teacher_number = 0;
    }
    fclose(fp);
}

void Write_File_Teacher_Number(int teacher_number)
{
    FILE *fp = fopen(TEACHER_NUMBER_URL, "w");
    if(fp)
    {
        fprintf(fp,"%d",teacher_number);
    }
}

Teacher* Read_Teachers(int teacher_number)
{
    Teacher* teachers = (Teacher*)malloc(sizeof(Teacher)*(teacher_number+1));
    FILE* fp = fopen(TEACHER_DATA_URL,"r");
    if(fp)
    {
        for(int i=0;i<teacher_number;i++)
        {
            fscanf(fp,"%d %s %s %s %s %d\n",&teachers[i].id,teachers[i].name,teachers[i].gender,
            &teachers[i].college,teachers[i].course,&teachers[i].teaching_class);
        }
        fclose(fp);
        return teachers;
    }
    return NULL;
}

bool Teacher_Login(Teacher* teachers, Teacher *target_teacher, int teacher_number)
{
    int count = 0;
    printf("请输入八位数的教工号，如：大连理工大学教工号（当然这里完全是瞎编的，跟实际情况完全不符合）00010001：\n");
    while(true)
    {
        if(count==3)
        {
            printf("登录尝试次数过多，退出登录\n");
            return false;
        }
        int id;
        printf("请输入教工号：");
        scanf("%d",&id);
        long long password;
        printf("请输入密码（初始密码为教工号）：");
        scanf("%lld",&password);
        for(int i=0;i<teacher_number;i++)
        {
            if(teachers[i].id == id && teachers[i].password == password)
            {
                printf("登录成功！\n");
                *target_teacher = teachers[i];
                return true;
            }
        }
        ++count;
        printf("用户名或密码错误，请重试\n");
    }
}

void Teacher_Import_Grade(Student* students, int student_number, Teacher *teacher, int teacher_number, Course courses[])
{
    char temp_course_url[50];
    sprintf(temp_course_url,"data/student/%s.txt",teacher->course);
    FILE* fp = fopen(temp_course_url,"a+");
    for(int i=0;i<student_number;i++)
    {
        if(students[i].Class == teacher->teaching_class)
        {
            if(strcmp(teacher->course,"Math")==0)
            {
                if(students[i].scores.Math == (-1))
                {
                    printf("%d %s 的 数学课 成绩：",students[i].id,students[i].name);
                    scanf("%d",&students[i].scores.Math);
                    fprintf(fp,"%d %d\n",students[i].id,students[i].scores.Math);
                }
                else continue;
            }
            else if(strcmp(teacher->course,"Politics")==0)
            {
                if(students[i].scores.Politics == (-1))
                {
                    printf("%d %s 的 政治课程 成绩：",students[i].id,students[i].name);
                    scanf("%d",&students[i].scores.Politics);
                    fprintf(fp,"%d %d\n",students[i].id,students[i].scores.Politics);
                }
                else continue;
            }
            else if(strcmp(teacher->course,"English")==0)
            {
                if(students[i].scores.English == (-1))
                {
                    printf("%d %s 的 英语课 成绩：",students[i].id,students[i].name);
                    scanf("%d",&students[i].scores.English);
                    fprintf(fp,"%d %d\n",students[i].id,students[i].scores.English);
                }
                else continue;
            }
            else if(strcmp(teacher->course,"Computer")==0)
            {
                if(students[i].scores.Computer == (-1))
                {
                    printf("%d %s 的 计算机课程 成绩：",students[i].id,students[i].name);
                    scanf("%d",&students[i].scores.Computer);
                    fprintf(fp,"%d %d\n",students[i].id,students[i].scores.Computer);
                }
                else continue;
            }
            Update_GPA(&students[i],courses,student_number);
        }
    }
    fclose(fp);
    printf("成绩录入完成\n");
}

double Total_GPA_Calculation(Student* student, Course courses[], int student_number)
{
    double total_credit = 0;
    total_credit+=(student->scores.Math!=(-1)?courses[0].credit:0); 
    total_credit+=(student->scores.English!=(-1)?courses[1].credit:0);
    total_credit+=(student->scores.Computer!=(-1)?courses[2].credit:0);
    total_credit+=(student->scores.Politics!=(-1)?courses[3].credit:0);
    if(total_credit==0) 
        return 0;
    double total_grade = 0;
    total_grade+=courses[0].credit*(student->scores.Math>=60?(student->scores.Math/10.0-5):0); 
    total_grade+=courses[1].credit*(student->scores.English>=60?(student->scores.English/10.0-5):0);
    total_grade+=courses[2].credit*(student->scores.Computer>=60?(student->scores.Computer/10.0-5):0);
    total_grade+=courses[3].credit*(student->scores.Politics>=60?(student->scores.Politics/10.0-5):0);
    if(total_grade==0) 
        return 0;
    return total_grade/total_credit;
}

void Update_GPA(Student* student, Course courses[], int student_number)
{
    double temp_GPA = Total_GPA_Calculation(student,courses,student_number);
    student->GPA = temp_GPA;
} 