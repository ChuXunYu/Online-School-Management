#ifndef BUS_H
#define BUS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUS_ROUTE_ONE "data/bus/南湖-浑南.txt"
#define BUS_ROUTE_TWO "data/bus/浑南-南湖.txt"
#define BUS_RESERVE_COST 2

typedef struct _BusSchedule{
    int index;
    char date[40];
    char time[40];
}BusSchedule;

typedef struct _siteSchedule{
    char siteType[100];
    char date[100];
    char time[100];
}siteSchedule;

void inputBusSchedule(BusSchedule *schedule);
void saveBusScheduleToFile(const BusSchedule *schedule, const char *filename, int counter);
int Counter(const char *filename);
BusSchedule* Print_Bus_Conditions(const char *filename);

void inputSiteSchedule(siteSchedule *schedule);
void saveSiteScheduleToFile(const siteSchedule *schedule, const char *filename, int counter);

#endif 