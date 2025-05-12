#include "security.h"
#include "student.h"
#include "teacher.h"

long long quick_pow(long long base, long long power, long long mod) 
{
    long long result = 1;
    base = base%mod;
    while (power>0)
    {
        if (power%2==1)
        {
            result=(result * base) % mod;
        }
        power = power >> 1;
        base = (base * base) % mod;
    }
    return result;
}

long long encrypt(long long original_password) 
{
    return quick_pow(original_password, E, N);
}

long long decrypt(long long ciphertext)
{
    return quick_pow(ciphertext, D, N);
}

void Inital_password(Student* students, int student_number, Teacher* teachers, int teacher_number)
{
    for(int i=0;i<student_number;i++)
    {
        students[i].password = students[i].id;
    }
    for(int i=0;i<teacher_number;i++)
    {
        teachers[i].password = teachers[i].id;
    }
}

void Read_Password(Student* students, int student_number, Teacher* teachers, int teacher_number, TreeNode* root)
{
    FILE* fStudent = fopen(STUDENT_PASSWORD_URL, "a");
    fclose(fStudent);
    fStudent = fopen(STUDENT_PASSWORD_URL, "r");
    if(fStudent!=NULL)
    {
        int id;
        long long public_key;
        while(fscanf(fStudent,"%d %lld",&id,&public_key)==2)
        {
            TreeNode* target_stu = find(root,id);
            if(target_stu!=NULL)
            {
                target_stu->student->password = decrypt(public_key);
            }
        }
        fclose(fStudent);
    }
    
    FILE* fTeacher = fopen(TEACHER_PASSWORD_URL, "a");
    fclose(fTeacher);
    fTeacher = fopen(TEACHER_PASSWORD_URL, "r");
    if(fTeacher!=NULL)
    {
        int id;
        long long public_key;
        while(fscanf(fTeacher,"%d %lld",&id,&public_key)==2)
        {
            for(int i=0;i<teacher_number;i++)
            {
                if(teachers[i].id==id)
                {
                    teachers[i].password = decrypt(public_key);
                }
            }
        }
        fclose(fTeacher);
    }
}

void Read_Money(Student* students, int student_number, Teacher* teachers, int teacher_number, TreeNode* root)
{
    FILE* fMoney = fopen(MONEY_URL,"a");
    fclose(fMoney);
    fMoney = fopen(MONEY_URL,"r");
    if(fMoney!=NULL)
    {
        int id;
        double money;
        while(fscanf(fMoney,"%d %lf",&id,&money)==2)
        {
            TreeNode* target = find(root,id);
            if(target!=NULL)
            {
                target->student->money = money;
            }
        }
        fclose(fMoney);
    }
} 