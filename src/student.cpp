#include "student.h"
#include "bus.h"
#include "security.h"
#include "main.h"
#include <windows.h>
#include <ctype.h>

#define MATH_SCORE_URL "data/student/Math.txt"
#define ENGLISH_SCORE_URL "data/student/English.txt"
#define COMPUTER_SCORE_URL "data/student/Computer.txt"
#define POLITICS_SCORE_URL "data/student/Politics.txt"

extern int INDEX;

void Read_File_Student_Number(int* student_number)
{
    FILE *fp = fopen(STUDENT_NUMBER_URL, "r");
    if(fp)
    {
        if(fscanf(fp,"%d",student_number)!=1)
        {
            *student_number = 0;
        }
        fclose(fp);
    }
    else
    {
        *student_number = 0;
    }
    
}

void Write_File_Student_Number(int student_number)
{
    FILE *fp = fopen(STUDENT_NUMBER_URL, "w");
    if(fp)
    {
        fprintf(fp,"%d",student_number);
    }
    fclose(fp);
}

Student* Read_Students(int student_number)
{
    Student* students = (Student*)malloc(sizeof(Student)*(student_number+1));
    FILE* fp = fopen(STUDENT_DATA_URL,"r");
    if(fp)
    {
        for(int i=0;i<student_number;i++)
        {
            fscanf(fp,"%d %s %s %s %s %d\n",&students[i].id,students[i].name,students[i].gender,
            &students[i].college,&students[i].major,&students[i].Class);
        }
    }
    fclose(fp);
    return students;
}

void Undefined_Inital_Stu(Student* students,int student_number)
{
    for(int i=0;i<student_number;i++)
    {
        students[i].money=0;
        students[i].dorm_index=-1;
        students[i].scores.Computer=-1;
        students[i].scores.English=-1;
        students[i].scores.Math=-1;
        students[i].scores.Politics=-1;
        students[i].GPA = -1;
    }
}

bool Student_Login(Student* students, Student *target_student, int student_number)
{
    int count = 0;
    printf("请输入八位数的学生学号，例如：东北大学浑南校区计算机专业2024级5班第65号学生（考号对应：20245865）\n");
    while(true)
    {
        if(count==3)
        {
            printf("登录尝试次数过多，退出登录\n");
            return false;
        }
        int id;
        printf("请输入8位学号：");
        scanf("%d",&id);
        long long password;
        printf("请输入密码（初始密码为学号）：");
        scanf("%lld",&password);
        for(int i=0;i<student_number;i++)
        {
            if(students[i].id == id && students[i].password == password)
            {
                printf("登录成功！\n");
                *target_student = students[i];
                return true;
            }
        }
        ++count;
        printf("用户名或密码错误，请重试\n");
    }
}

void Student_Watch_Grade(Student* student)
{
    printf("学生：%d %s的成绩\n",student->id,student->name);
    student->scores.Math!=(-1)?printf("Math    : %d\n", student->scores.Math):printf("Math: 未录入\n");
    student->scores.English!=(-1)?printf("English : %d\n", student->scores.English):printf("English: 未录入\n");
    student->scores.Computer!=(-1)?printf("Computer: %d\n", student->scores.Computer):printf("Computer: 未录入\n");
    student->scores.Politics!=(-1)?printf("Politics: %d\n", student->scores.Politics):printf("Politics: 未录入\n");
    student->GPA!=(-1)?printf("GPA     : %.2f\n", student->GPA):printf("GPA: 暂无或未计算\n");
}

void assignDormitory(Student *students, int numStudents) 
{
    int index=0;
    for(int a=1;a<=6;a++)//楼号 
    {
        for(int b=1;b<=2;b++)//1为A楼，2为B楼 
        {
            for(int c=1;c<=6;c++)//宿舍区号
            {
                for(int d=1;d<=35;d++)//宿舍房号 
                {
                    for(int e=1;e<=4;e++)//床位 
                    {
                        if(index>=numStudents)
                            return;
                        students[index].dorm_index=a*100000+
                        b*10000+c*1000+d*10+e;  //生成宿舍号码 
                        index++;
                    }
                }
            }
        }
    }        
}

void Moneys_System(Student* student, int student_number, BusSchedule *b1, BusSchedule *b2, int bn1, int bn2)
{
    printf("余额：%.2lf\n",student->money);
    printf("请选择进行何种操作：\n");
    printf("1.买\n");
    printf("2.退出\n");
    int choice;
    scanf("%d",&choice);
    switch(choice)
    {
        case 1:
        {
            printf("请选择购买项目：\n");
            printf("1.校车票\n2.退出\n");

            int choice_buy;
            scanf("%d",&choice_buy);
            switch(choice_buy)
            {
                case 1:
                {
                    int abc;
                    printf("请选择您要预定的校车路线：\n");
                    printf("1.南湖-浑南\n2.浑南-南湖\n3.退出\n");
                    scanf("%d",&abc);
                    if(abc==1)
                    {
                        printf("路线一的时间安排：\n");
                        Print_Bus_Conditions(BUS_ROUTE_ONE);
                    }
                    else if(abc==2)
                    {
                        printf("路线二的时间安排：\n");
                        Print_Bus_Conditions(BUS_ROUTE_TWO);
                    }
                    else
                    {
                        printf("回到上级菜单！\n");
                        break;
                    }
                    printf("请选择您要预定的校车班次（输入编号）：\n");
                    int choice_bus;
                    scanf("%d",&choice_bus);
                    
                    printf("预定成功\n");
                    //扣费
                    student->money-=BUS_RESERVE_COST;
                    //保存到文件中
                    FILE* fMoney = fopen(MONEY_URL,"a+");
                    fprintf(fMoney,"%d %.2lf\n",student->id,student->money);
                    fclose(fMoney);
                    printf("当前余额：%.2lf\n",student->money);
                    break;
                }
                case 2:
                {
                    printf("退出购买\n");
                    Sleep(1000);
                    system("cls");
                    break;
                }
                default:
                {
                    printf("无效选择，请重试\n");
                    break;
                }
            }
            break;
        }
        case 2:
        {
            printf("退出系统\n");
            Sleep(1000);
            system("cls");
            break;
        }
        default:
        {
            printf("无效选择，请重试\n");
            break;
        }
    }
}

TreeNode* insert(TreeNode* root, Student* student) 
{
    if (root == NULL) 
    {
        TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
        newNode->student = student;
        newNode->left = NULL;
        newNode->right = NULL;
        return newNode;
    }

    if (student->id < root->student->id) 
    {
        root->left = insert(root->left, student);
    } 
    else 
    {
        root->right = insert(root->right, student);
    }
    return root;
}

TreeNode* createBinaryTree(Student* students, int size) {
    TreeNode* root = NULL;
    for (int i = 0; i < size; i++) 
    {
        root = insert(root, &students[i]);
    }
    return root;
}

void printInOrder(TreeNode* node) {
    if (node != NULL) {
        printInOrder(node->left);
        printf("ID: %d, Name: %s, Money: %.2f\n", node->student->id, node->student->name, node->student->money);
        printInOrder(node->right);
    }
}

void freeTree(TreeNode* node) {
    if (node != NULL) {
        freeTree(node->left);
        freeTree(node->right);
        free(node);
    }
}

TreeNode* find(TreeNode* root, int id) {
    if (root == NULL || root->student->id == id) {
        return root;
    }

    if (id < root->student->id) {
        return find(root->left, id);
    } else {
        return find(root->right, id);
    }
}

int hashFunction(int id) 
{
    int hashValue = 3;
    const int prime = 31;
    hashValue = (hashValue ^ (id & 0xffff)) * prime;
    hashValue = (hashValue ^ ((id >> 2) & 0xffff)) * prime;
    hashValue = (hashValue ^ (id >> 1)) * prime;
    return hashValue % TABLE_SIZE;
}

HashTable* createHashTable(void) 
{
    HashTable* table = (HashTable*)malloc(sizeof(HashTable));
    if (table) 
    {
        for(int i=0;i<TABLE_SIZE;i++) 
        {
            table->students[i]=NULL;
        }
    }
    return table;
}

bool insertStudent(HashTable* table, Student* student) 
{
    if(!table || !student)
        return false;
    int index = hashFunction(student->id);
    if(!table->students[index]) //未发生碰撞，直接存入哈希位置 
    {
        table->students[index] = student;
        student->next = NULL; 
    }
    else
    {
        Student* current = table->students[index];
        while(current->next!=NULL)
        {
            current = current->next;
        } 
        current->next = student;
        student->next = NULL; 
    }   
    return true;
}

Student* findStudent(HashTable* table, int id) 
{
    if (!table) 
        return NULL;
    int index = hashFunction(id);
    Student* current = table->students[index];
    if(current==NULL)
        return NULL;
    while (current!= NULL) 
    {
        if (current->id == id) 
        {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

bool deleteStudent(HashTable* table, int id) 
{
    if (!table) 
        return false;
    Student* theStudent = findStudent(table,id);
    if(theStudent==NULL)
        return false;//未找到该学生
    //已找到要删除的学生
    int index = hashFunction(id);
    if(table->students[index]==theStudent)
    {
        table->students[index] = theStudent->next;
    }
    else
    {
        Student* current = table->students[index];
        while(current->next != theStudent)
        {
            current = current->next;
        }
        current->next = theStudent->next;
    }
    free(theStudent);
    return true;
}

bool freeHashTable(HashTable* table) 
{
    if(!table) 
        return false;
    for(int i=0;i<TABLE_SIZE;i++)
    {
        Student* current = table->students[i];
        current = current->next;
        while(current!=NULL)
        {
            Student* temp = current;
            current = current->next;
            free(temp);
        }
    }
    free(table);
    return true;
}

int getCourseScore(Student* student, const char* courseName) 
{
    if (strcmp(courseName, "Math") == 0) 
    {
        return student->scores.Math;
    } 
    else if (strcmp(courseName, "English") == 0)
    {
        return student->scores.English;
    } 
    else if (strcmp(courseName, "Computer") == 0) 
    {
        return student->scores.Computer;
    } 
    else if (strcmp(courseName, "Politics") == 0) 
    {
        return student->scores.Politics;
    }
    else if (strcmp(courseName,"GPA")==0)
    {
        return student->GPA;
    }
    else if (strcmp(courseName,"id")==0)
    {
        return student->id;
    }
    else if (strcmp(courseName,"Class")==0)
    {
        return student->Class;
    }
    return -1;
}

int compareStudents(Student* student1, Student* student2, const char* courseName) {
    int score1 = getCourseScore(student1, courseName);
    int score2 = getCourseScore(student2, courseName);

    if (score1 == -1 && score2 == -1) 
    {
        return 0;
    }
    if (score1 == -1) return INDEX;
    if (score2 == -1) return -1*INDEX;
    
    if (score1 < score2) 
    {
        return INDEX;
    } 
    else if (score1 > score2) 
    {
        return (-1)*INDEX;
    }
    return 0;
}

void merge(Student* array, int left, int mid, int right, const char* courseName) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    
    Student* leftArray = (Student*)malloc(n1 * sizeof(Student));
    Student* rightArray = (Student*)malloc(n2 * sizeof(Student));
    for (int i = 0; i < n1; i++) 
    {
        leftArray[i] = array[left + i];
    }
    for (int j = 0; j < n2; j++) 
    {
        rightArray[j] = array[mid + 1 + j];
    }
    int i=0, j=0, k=left;
    
    while (i<n1&&j<n2)
    {
        if(compareStudents(&leftArray[i],&rightArray[j],courseName)<=0) 
        {
            array[k] = leftArray[i];
            i++;
        } 
        else 
        {
            array[k]=rightArray[j];
            j++;
        }
        k++;
    }
    
    while(i<n1)
    {
        array[k]=leftArray[i];
        i++;
        k++;
    }
    while(j<n2)
    {
        array[k]=rightArray[j];
        j++;
        k++;
    }
    
    free(leftArray);
    free(rightArray);
}

void mergeSort(Student* array, int left, int right, const char* courseName) {
    if (left<right) 
    {
        int mid=left+(right-left)/2;
        
        mergeSort(array, left, mid, courseName);
        mergeSort(array, mid + 1, right, courseName);
        
        merge(array, left, mid, right, courseName);
    }
}

void sortByCourseScore(Student* students, int size, const char* courseName) {
    mergeSort(students,0,size-1,courseName);

    printf("\n按%s排序的学生成绩列表（-1表示成绩未录入）\n",courseName);
    for (int i=0;i<size;i++)
    {
        int score = getCourseScore(&students[i],courseName);
        if(strcmp(courseName,"id")==0)
        {
            printf("ID: %08d, Name: %-12s,Class: %08d\n", students[i].id, students[i].name,score);
        }
        else if(strcmp(courseName,"Math")==0||strcmp(courseName,"English")==0||strcmp(courseName,"Computer")==0)
        {
            printf("ID: %08d, Name: %-12s, Class: %5d, %s Score: %3d\n", students[i].id, students[i].name, students[i].Class,courseName, score);
        }
        else if(strcmp(courseName,"Class")==0)
        {
            printf("ID: %08d, Name: %-12s, Class: %5d\n", students[i].id, students[i].name, students[i].Class);
        }
    }
}

void Students_Read_Grade_File(TreeNode* root, int student_number)
{
    int temp_id;
    int temp_score;
    FILE* fMath = fopen(MATH_SCORE_URL, "r");
    int status;
    if(fMath!=NULL)
    {
        while((status = fscanf(fMath, "%d %d", &temp_id, &temp_score))!=EOF && status==2)
        {
            TreeNode* result = find(root, temp_id);
            if (result!=NULL)
            {
                result->student->scores.Math = temp_score;
            } 
        }    
        fclose(fMath);
    }

    status=0;
    FILE* fEnglish = fopen(ENGLISH_SCORE_URL, "r");
    if(fEnglish!=NULL)
    {
        while((status = fscanf(fEnglish, "%d %d", &temp_id, &temp_score))!=EOF && status==2)
        {
            TreeNode* result = find(root, temp_id);
            if (result!=NULL) 
            {
                result->student->scores.English = temp_score;
            }
        }    
        fclose(fEnglish);
    }

    status=0;
    FILE* fComputer = fopen(COMPUTER_SCORE_URL, "r");
    if(fComputer!=NULL)
    {
        while((status = fscanf(fComputer, "%d %d", &temp_id, &temp_score))!=EOF && status==2)
        {
            TreeNode* result = find(root, temp_id);
            if (result!=NULL) 
            {
                result->student->scores.Computer = temp_score;
            }
        }    
        fclose(fComputer);
    }
    status=0;
    FILE* fPolitics = fopen(POLITICS_SCORE_URL, "r");
    if(fPolitics!=NULL)
    {
        while((status = fscanf(fPolitics, "%d %d", &temp_id, &temp_score))!=EOF && status==2)
        {
            TreeNode* result = find(root, temp_id);
            if (result!=NULL) 
            {
                result->student->scores.Politics = temp_score;
            }
        }    
        fclose(fPolitics);
    }
} 