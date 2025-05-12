#include "bus.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void inputBusSchedule(BusSchedule *schedule) 
{
    printf("请输入校车日期：");
    scanf("%s",schedule->date);
    printf("请输入校车时间：");
    scanf("%s",schedule->time);
}

void saveBusScheduleToFile(const BusSchedule *schedule, const char *filename, int counter) 
{
    FILE *file = fopen(filename,"a+");
    fprintf(file,"%d. ",counter);
    fprintf(file,"%s ",schedule->date);
    fprintf(file,"%s",schedule->time);
    fprintf(file,"\n");
    printf("添加校车成功\n"); 
    fclose(file);
}

int Counter(const char *filename) 
{
    FILE *file=fopen(filename, "a+");
    int maxCounter=0;
    int currentCounter;
    while(fscanf(file,"%d.",&currentCounter)==1) 
    {
        if(currentCounter>maxCounter) 
        {
            maxCounter=currentCounter;
        }
        fscanf(file,"%*s %*s\n");
    }
    fclose(file);
    return maxCounter;
}

BusSchedule* Print_Bus_Conditions(const char *filename)
{
    FILE*fp = fopen(filename,"a+");
    fclose(fp);
    fp = fopen(filename,"r");
    int maxCount=0;
    char Date[30];
    char Time[30];
    int status;
    int Total_Counter = 0;
    Total_Counter=Counter(filename);
    BusSchedule* busSchedule = (BusSchedule*)malloc(sizeof(BusSchedule)*(Total_Counter+1));
    while(fscanf(fp,"%d. %s %s",&maxCount,Date,Time)==3)
    {
        busSchedule[maxCount-1].index = maxCount;
        strcpy(busSchedule[maxCount-1].date,Date);
        strcpy(busSchedule[maxCount-1].time,Time);
        printf("%d.%s %s\n",maxCount,Date,Time);
    }    
    return busSchedule;
} 

void inputSiteSchedule(siteSchedule *schedule) 
{
    printf("请输入场地类型名称：");
    scanf("%s",schedule->siteType);
    printf("请输入预约日期：");
    scanf("%s",schedule->date);
    printf("请输入预约时间：");
    scanf("%s",schedule->time);
}

void saveSiteScheduleToFile(const siteSchedule *schedule, const char *filename, int counter) 
{
    FILE *file = fopen(filename,"a+");
    fprintf(file,"%d. ",counter);
    fprintf(file,"%s ",schedule->date);
    fprintf(file,"%s",schedule->time);
    fprintf(file,"\n");
    printf("添加场地预约成功\n"); 
    fclose(file);
} 