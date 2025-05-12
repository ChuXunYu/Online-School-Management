#include "main.h"

int INDEX = 1;

int main() 
{
    int college_number = 0; 
    bool first = false;
    int major_number = 0;
    Colleges* colleges;	
    Major* majors;
    BusSchedule *bus_schedule1;
    BusSchedule *bus_schedule2;
    BusSchedule schedule;
    int student_number = 0;
    Student* students; 
    int teacher_number = 0;
    Teacher* teachers;
    TreeNode* root;
    Student target_student;	
    target_student.money = 48.0;
    
    Course courses[] = {{5,"Math"}, {3.5,"English"}, {3,"Computer"}, {3,"Politics"}};
    
    printf("系统初始化中...\n");
    Sleep(2000);
    system("cls"); 
    
start:
    printf("选择登录方式（请输入对应数字）:\n1.教师登录（教工号）\n2.学生登录（学生学号）\n3.管理员登录\n\n"
           "对于1选项教师登录后:\n1.录入成绩\n2.查询学生\n3.修改成绩\n4.修改登录密码\n5.排序查询\n6.退出登录\n\n"
           "对于2选项学生登录后学生登录后:\n1.课程查询\n2.宿舍管理\n3.财政查询（校车预定）\n4.修改登录密码\n5.退出登录\n\n"
           "对于3行政管理员登录:\n1.处理校车及宿舍管理问题\n\n选择4退出\n\n");
www:
    printf("若是系统初次运行，请输入0；若已经初始化过，则直接输入上述对应数字进行操作。");
    int login_choice;
    if(!first)
    {
        system("pause"); 
        system("cls"); 
        printf("欢迎来到东北大学在线校园管理系统，首次运行需要录入初始数据\n");
        printf(("1.添加学院功能：\n2.添加专业功能：\n3.添加教师功能：\n"));
        printf("请依次添加学院、专业、学生和教师等基本信息，添加完毕后系统会自动将学生分配到宿舍\n");
        printf("请继续添加学院信息\n");
        system("pause");
        system("cls");
        printf("1.添加学院\n"); 
        printf("请依次输入学院，每行一个，输入完成后按Ctrl+Z结束\n");		
        Read_File_College_Number(&college_number);
        Admin_College(&college_number);
        Write_File_College_Number(college_number);
        colleges = Read_College(college_number);
        printf("学院添加完成\n");
        Sleep(500);
        system("cls"); 				
        printf("接下来进行步骤2.添加专业\n");
        Print_College(colleges,college_number);
        printf("请输入专业所属学院id和专业名，每行一个，输入完成后按Ctrl+Z结束\n"); 
        Read_File_Major_Number(&major_number);
        Admin_Major(colleges,college_number,&major_number);
        Write_File_Major_Number(major_number);
        majors = Read_Major(major_number);
        printf("专业添加完成\n");
        Sleep(500);
        system("cls"); 
        Sleep(500);	
        
        printf("接下来添加学生和教师信息\n");
        Sleep(1000);
        system("cls");
        
        Read_File_Student_Number(&student_number);
        inputStudentInfo(colleges,college_number,majors,major_number,&student_number);
        Write_File_Student_Number(student_number);			
        Sleep(500);
        system("cls");
        Sleep(500);
        
        Read_File_Teacher_Number(&teacher_number);
        inputTeacherInfo(colleges,courses,college_number,&teacher_number);
        Write_File_Teacher_Number(teacher_number);
        students = Read_Students(student_number);
        Undefined_Inital_Stu(students,student_number);
        assignDormitory(students,student_number); 
        
        teachers = Read_Teachers(teacher_number);
        Inital_password(students,student_number,teachers,teacher_number); 
        
        Sleep(500);
        system("cls");
        Sleep(500);
        
        root = createBinaryTree(students,student_number);
        Read_Password(students,student_number,teachers,teacher_number,root);
        Students_Read_Grade_File(root,student_number);
        Read_Money(students,student_number,teachers,teacher_number,root);
        printf("数据初始化完成\n");
        
        int choice_buses;
        printf("南湖 --> 浑南校区\n");
        bus_schedule1=Print_Bus_Conditions(BUS_ROUTE_ONE);
        
        printf("浑南 --> 南湖校区\n");
        bus_schedule2=Print_Bus_Conditions(BUS_ROUTE_TWO);	
        
        while (true) 
        {
            printf("请选择要添加的校车路线\n");
            printf("1. 南湖 --> 浑南\n");
            printf("2. 浑南 --> 南湖\n");
            printf("3. 退出\n");
            printf("请输入选择（数字）：");
            scanf("%d",&choice_buses);        
            if (choice_buses==3) 
            {
                break; 
            }
            if(choice_buses==1) 
            {
                inputBusSchedule(&schedule);
                int NanhuCounter=Counter(BUS_ROUTE_ONE)+1;    
                saveBusScheduleToFile(&schedule,BUS_ROUTE_ONE,NanhuCounter);
                Sleep(1000);
                system("cls");
            } 
            else if(choice_buses==2) 
            {
                inputBusSchedule(&schedule);
                int HunnanCounter=Counter(BUS_ROUTE_TWO)+1;
                saveBusScheduleToFile(&schedule,BUS_ROUTE_TWO,HunnanCounter);
                Sleep(1000);
                system("cls");
            }
            else 
            {
                printf("无效选择，请重新输入\n");
                Sleep(1000);
                system("cls");
            }
        }
        first=true;
        Sleep(1000);
        system("cls");
        goto start; 
    } 
    scanf("%d",&login_choice);
    system("cls");
    
    switch(login_choice)
    {
        case 1:		
            printf("请输入教师登录信息\n");
            Teacher target_teacher;
            if(Teacher_Login(teachers,&target_teacher,teacher_number))
            {
                printf("工号：%08d\n姓名：%s\n性别：%s\n所属学院：%s\n教学课程：%s\n教学班级：%d\n",
                        target_teacher.id,target_teacher.name,target_teacher.gender,
                        target_teacher.college,target_teacher.course,target_teacher.teaching_class);
                system("pause");
                system("cls");
asd:
                printf("选择操作\n1.录入成绩\n2.查询学生\n3.修改成绩\n4.修改登录密码\n5.排序查询\n6.退出登录\n");
                int bb;
                scanf("%d",&bb);
                if(bb==1)
                {
                    bool jutice = true;
                    while(true)
                    {
                        printf("是否需要为%d班级%s课程录入成绩？1表是0表否：",target_teacher.teaching_class,target_teacher.course);
                        int choice_grade_enter;
                        scanf("%d",&choice_grade_enter);
                        if(choice_grade_enter==0)
                        {
                            jutice=false;
                            break;
                        }
                        else if(choice_grade_enter==1)
                        {
                            jutice=true;
                            break;
                        }
                        else
                        {
                            printf("\n请输入有效的选择（0或1）\n"); 
                            continue;
                        }
                    }
                    system("cls");
                    if(jutice)
                    {
                        printf("正在准备录入成绩功能......\n");
                        Sleep(1000);
                        printf("请为相应班级的学生录入成绩，未录入的成绩会显示为-1......\n"); 
                        Sleep(2000);
                        system("cls");
                        Teacher_Import_Grade(students,student_number,&target_teacher,teacher_number,courses);
                    }
                }
                else if(bb==2)
                {
                    printf("正在准备查询学生功能......\n");
                    Sleep(1000);
                    printf("请输入所要查询学生的信息，系统将会显示该生的成绩情况......\n"); 
                    Sleep(2000);
                    system("cls");
                    printf("请输入所要查询学生的ID：");
                    int to_find_student_id;
                    scanf("%d",&to_find_student_id);
                    TreeNode* target_student = find(root,to_find_student_id);
                    if(target_student!=NULL)
                    {
                        Student_Watch_Grade(target_student->student);
                    }
                } 
                else if(bb==3)
                {
                    printf("正在准备修改成绩功能......\n");
                    Sleep(1000);
                    printf("请输入所要修改学生的信息，系统将会为该生的成绩进行修改......\n"); 
                    Sleep(2000);
                    system("cls");
                    printf("请输入所要修改成绩学生的ID：");
                    int to_find_student_id;
                    scanf("%d",&to_find_student_id);
                    TreeNode* target_student = find(root,to_find_student_id);
                    if(target_student!=NULL)
                    {
                        char temp_course_url[50];
                        sprintf(temp_course_url,"data/student/%s.txt",target_teacher.course);
                        FILE* fp = fopen(temp_course_url,"a+");
                        if(fp==NULL)
                        {
                            printf("文件打开失败\n");
                            return 0;
                        }
                        printf("请输入修改后的成绩：");
                        int grade_to_change;
                        scanf("%d",&grade_to_change);
                        fprintf(fp,"%d %d\n",to_find_student_id,grade_to_change);
                        fclose(fp);
                        printf("成绩修改完成！\n");
                        Sleep(2000);
                        system("cls");
                    }
                    else
                    {
                        printf("未找到该学生信息\n");
                        Sleep(2000);
                        system("cls");
                    }
                }
                else if(bb==4)
                {
                    int time_count=0;
password_enter:
                    printf("请输入原密码进行验证：");
                    long long former_password;
                    scanf("%lld",&former_password);
                    if(former_password==target_teacher.password)
                    {
                        printf("请输入新的密码：");
                        long long new_password;
                        scanf("%lld",&new_password);
                        target_teacher.password = new_password;
                        FILE* fTeacher= fopen(TEACHER_PASSWORD_URL,"a+");
                        fprintf(fTeacher,"%d %lld\n",target_teacher.id,encrypt(target_teacher.password));
                        fclose(fTeacher);
                        printf("密码修改完成！\n");
                        Sleep(2000);
                        system("cls");
                    }
                    else
                    {
                        printf("密码验证失败\n");
                        time_count++;
                        if(time_count>3)
                        {
                            printf("密码验证次数过多，退出\n");
                            Sleep(2000);
                            system("cls");
                            goto choice_one;
                        }
jjj:
                        int a;
                        printf("是否继续尝试？输入1继续，0退出：");
                        scanf("%d",&a);
                        if(a==1)
                        {
                            goto password_enter;
                        }
                        else if(a==0)
                        {
                            system("cls");
                        }
                        else
                        {
                            printf("请输入有效的选择（0或1）\n");
                            goto jjj;
                        }
                    }
                }
                else if(bb==5)
                {
                    printf("是否需要进行成绩排序？输入1进行排序，0退出：");
                    int choice_sort;
                    scanf("%d",&choice_sort);
                    if(choice_sort==1)
                    {
                        Sleep(500);
                        system("cls");  
                        printf("可排序的项目有：\n请输入排序依据\nMath\nEnglish\nComputer\nPolitics\n");
                        printf("GPA\nid\nClass\n请输入排序依据：");
                        char choices[20];
                        scanf("%s",choices);
                        while(true)
                        {
                            if(strcmp(choices,"Math")!=0&&strcmp(choices,"English")!=0&&strcmp(choices,"Computer")!=0&&strcmp(choices,"Politics")!=0&&strcmp(choices,"GPA")!=0&&strcmp(choices,"id")!=0&&strcmp(choices,"Class")!=0)
                            {
                                printf("请输入有效的排序依据：");
                                continue;
                            }
                            else
                            {
                                break;
                            }
                        }
                        printf("请输入排序方式1递增排序，-1递减排序：");
                        while(true)
                        {
                            int order;
                            scanf("%d",&order);
                            Sleep(500); 
                            system("cls");
                            if(order==1||order==(-1))
                            {
                                INDEX=order;
                                sortByCourseScore(students,student_number,choices);
                                INDEX=1;
                                break;
                            }
                            else
                            {
                                printf("请输入有效的排序方式：");
                                continue;
                            }
                        }
                    }
                    else if(choice_sort==0)
                    {
                        printf("退出排序功能\n");
                        Sleep(2000);
                        system("cls");
                    }
                    else
                    {
                        printf("请输入有效的选择（0或1）");
                        Sleep(2000);
                        system("cls");
                        goto choice_start;
                    }
                }
                else if(bb==6)
                {
                    printf("退出登录成功\n");
                    Sleep(2000);
                    system("cls");
                }
                else
                {
                    printf("请输入有效的选择（1-6）\n");
                    goto asd;
                }
        
            int a1;
choice_one:
            printf("是否继续执行其他操作？输入1继续，0退出：");
            scanf("%d",&a1);
            if(a1==1)
            {
                system("cls");
                goto start;
            }
            else if(a1==0)
            {
                system("cls");
            }
            else
            {
                printf("请输入有效的选择（0或1）\n"); 
                goto choice_one;
            }
            break;		
        case 2:
            printf("请输入学生登录信息：\n");
            
            if(Student_Login(students,&target_student,student_number))
            {
                printf("学号：%08d\n姓名：%s\n性别：%s\n所属学院：%s\n所属专业：%s\n所属班级：%d\n",
                        target_student.id,target_student.name,target_student.gender,
                        target_student.college,target_student.major,target_student.Class);
                system("pause");
                system("cls");
ggg:
                printf("1.课程查询\n2.宿舍管理\n3.财政查询（校车预定）\n4.修改登录密码\n5.退出登录\n"); 
                printf("请输入要执行的操作：");
                int op;
                scanf("%d",&op);
                if(op==1)
                {
                    printf("正在准备课程查询功能......\n");
                    Sleep(1000);
                    printf("正在查找您所学课程的成绩情况......\n");
                    Sleep(2000);
                    system("cls");
                    Student_Watch_Grade(&target_student);
                    system("pause");	
                }
                else if(op==2)
                {
                    int location = target_student.dorm_index;
                    int bed = location%10;
                    location/=10;
                    int area = location%1000;
                    location/=1000;
                    int AB = location%10;
                    char ab; 
                    if(AB==1)
                        ab='A';
                    else if(AB==2)
                        ab='B';
                    int buliding = location/10;
                    printf("您的宿舍位置：%d号楼 %c%d %d号床\n",buliding,ab,area,bed);
ops:
                    printf("宿舍管理有两项功能：请选择校内住宿功能：1.调换宿舍  2.不进行操作：");
                    int opt;
                    scanf("%d",&opt);
                    if(opt==1)
                    {
                        FILE* Out_live=fopen(ROOM_CHANGE_REQUESTS_URL,"a+");
                        rewind(Out_live); 
                        int stud_id;
                        char reason[50];
                        char answer[10];
                        int result;
                        bool whether_find=false;
                        bool whether_reply=false; 
                        while ((result = fscanf(Out_live,"%d %s %s",&stud_id,reason,answer))==3)
                        {
                            if(stud_id==target_student.id)
                            {
                                whether_find=true;
                                size_t len=strcspn(answer, "\n");
                                answer[len]='\0';
                                if (strcmp(answer,"IamML")!=0)
                                {
                                    whether_reply = true;
                                }
                                break;
                            }
                        } 
                        if (whether_find) 
                        {
                            if (whether_reply) 
                            {
                                printf("Has been replied, please check\n");
                            } else 
                            {
                                printf("Has been submitted, but no answer yet, please wait\n");
                            }
                        } 
                        else 
                        {
                            printf("Hasn't submit\n");
                            char reasons[50];
                            printf("请输入调换原因（20字以内）：");
                            scanf("%s", reasons);
                            fprintf(Out_live, "%d %s IamML\n", target_student.id, reasons);
                            printf("调换申请已提交！\n");
                        }
                        fclose(Out_live);
                    }
                    else if(opt==2)
                    {
                        printf("退出宿舍功能\n");
                    }
                    else if(opt!=1&&opt!=2)
                    {
                        printf("请输入有效的选择（1或2）\n");
                        goto ops;
                    }
                }
                else if(op==3)
                {
                    printf("正在准备财政查询功能......\n");
                    Sleep(1000);
                    system("pause");
                    system("cls");
                    int bn1 = Counter(BUS_ROUTE_ONE);
                    int bn2 = Counter(BUS_ROUTE_TWO);
                    Moneys_System(&target_student,student_number,bus_schedule1,bus_schedule2,bn1,bn2);
                }
                else if(op==4)
                {
                    int time_count=0;
password_enter1:
                    printf("请输入原密码进行验证：");
                    long long former_password;
                    scanf("%lld",&former_password);
                    if(former_password==target_student.password)
                    {
                        printf("请输入新的密码：");
                        long long new_password;
                        scanf("%lld",&new_password);
                        target_student.password = new_password;
                        FILE* fStudent= fopen(STUDENT_PASSWORD_URL,"a+");
                        fprintf(fStudent,"%d %lld\n",target_student.id,encrypt(target_student.password));
                        fclose(fStudent);
                        printf("密码修改完成！\n");
                        Sleep(2000);
                        system("cls");
                    }
                    else
                    {
                        printf("密码验证失败\n");
                        time_count++;
                        if(time_count>3)
                        {
                            printf("密码验证次数过多，退出\n");
                            Sleep(2000);
                            system("cls");
                            goto choice_two;
                        }
jjj1:
                        int b;
                        printf("是否继续尝试？输入1继续，0退出：");
                        scanf("%d",&b);
                        if(b==1)
                        {
                            goto password_enter1;
                        }
                        else if(b==0)
                        {
                            system("cls");
                        }
                        else
                        {
                            printf("请输入有效的选择（0或1）\n");
                            goto jjj1;
                        }
                    }
                }
                else if(op==5)
                {
                    printf("退出登录成功\n");
                    Sleep(2000);
                    system("cls");
                }
                else
                {
                    printf("请输入有效的选择（1-5）\n");
                    goto ggg;
                }
            }
choice_two:
            int a2;
            printf("是否继续执行其他操作？输入1继续，0退出：");
            scanf("%d",&a2);
            if(a2==1)
            {
                system("cls");
                goto start;
            }
            else if(a2==0)
            {
                system("cls");
            }
            else
            {
                printf("请输入有效的选择（0或1）\n"); 
                goto choice_two;
            }
            break;
        case 3:
            printf("欢迎行政管理员，您将有学校最高权限，您可以处理校园内重要事物。\n");
            printf("请输入管理员账号：114514：");
            int Direct_id;
            long long Direct_password;
            scanf("%d",&Direct_id); 
            printf("请输入管理员密码：1919810：");
            scanf("%lld",&Direct_password);
            if(Direct_id==DIRECT_ID&&Direct_password==DIRECT_PASSWORD)
            {
                printf("登录成功！\n");
                Sleep(2000);
                system("cls");
                printf("正在加载管理功能...");
                Sleep(2000);
                system("cls");
                printf("1.处理宿舍申请  2.退出登录\n");
                printf("请输入要执行的操作：");
                int op3;
tar:
                scanf("%d",&op3);
                if(op3==1)
                { 
                    int student_id;
                    char reason[50];
                    char reply[50];
                    int result;
                    int choice1;
                    FILE* fp = fopen(ROOM_CHANGE_REQUESTS_URL,"r+");
                    FILE *temp_fp = fopen("data/temp/temp.txt","a+");
                    printf("下面是未处理的宿舍调换申请：\n");
                    while(fscanf(fp,"%d %s %s",&student_id,reason,reply)==3)
                    {
                        if(strcmp(reply,"IamML")!=0)
                        {
                            continue;
                        }
                        else
                        {
                            printf("学号:%d    原因:%s\n",student_id,reason);
                            do{
                                printf("是否同意ta的申请？同意1 拒绝0：");
                                scanf("%d",&choice1);
                                if(!(choice1==0 || choice1==1))
                                {
                                    printf("请输入有效的选择（0或1）\n");
                                }
                                else if(choice1==1)
                                {
                                    strcpy(reply,"同意");
                                    fprintf(temp_fp,"%d %s %s\n",student_id,reason,reply);
                                }
                                else
                                {
                                    strcpy(reply,"拒绝申请"); 
                                    fprintf(temp_fp,"%d %s %s\n",student_id,reason,reply);
                                }
                            }while(choice1!=0 && choice1!=1); 		 
                        } 
                    }
                    fclose(fp);
                    fclose(temp_fp);
                    remove(ROOM_CHANGE_REQUESTS_URL);
                    rename("data/temp/temp.txt",ROOM_CHANGE_REQUESTS_URL);
                }
                else if (op3==2)
                {
                    printf("退出登录\n");
                }
                else
                {
                    printf("请输入有效的选择（1或2）\n");
                    goto tar;
                }
            }
choice_three:
            int a3;
            printf("是否继续执行其他操作？输入1继续，0退出：");
            scanf("%d",&a3);
            if(a3==1)
            {
                system("cls");
                goto start;
            }
            else if(a3==0)
            {
                system("cls");
            }
            else
            {
                printf("请输入有效的选择（0或1）\n"); 
                goto choice_three;
            }
        case 4:
            printf("程序退出\n");
            break;
    }
    
choice_start:
    printf("欢迎使用教务管理排序功能，可对全校学生按成绩排序\n");
    printf("是否要使用教务管理排序功能？输入1使用排序，0退出：");
    int choice_sort;
    scanf("%d",&choice_sort);
    if(choice_sort==1)
    {
        Sleep(500);
        system("cls");  
        printf("可排序的项目有：\n请输入排序依据\nMath\nEnglish\nComputer\nPolitics\n");
        printf("GPA\nid\nClass\n请输入排序依据：");
        char choices[20];
        scanf("%s",choices);
        while(true)
        {
            if(strcmp(choices,"Math")!=0&&strcmp(choices,"English")!=0&&strcmp(choices,"Computer")!=0&&strcmp(choices,"Politics")!=0&&strcmp(choices,"GPA")!=0&&strcmp(choices,"id")!=0&&strcmp(choices,"Class")!=0)
            {
                printf("请输入有效的排序依据：");
                continue;
            }
            else
            {
                break;
            }
        }
        printf("请输入排序方式1递增排序，-1递减排序：");
        while(true)
        {
            int order;
            scanf("%d",&order);
            Sleep(500); 
            system("cls");
            if(order==1||order==(-1))
            {
                INDEX=order;
                sortByCourseScore(students,student_number,choices);
                INDEX=1;
                break;
            }
            else
            {
                printf("请输入有效的排序方式：");
                continue;
            }
        }
    }
    else if(choice_sort==0)
    {
        printf("退出排序功能\n");
        Sleep(2000);
        system("cls");
    }
    else
    {
        printf("请输入有效的选择（0或1）");
        Sleep(2000);
        system("cls");
        goto choice_start;
    }

    freeTree(root);
    free(students);
    free(teachers);
    free(colleges);
    free(majors);
    system("pause"); 
    return 0;
} 