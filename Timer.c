#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

char getTime(char date[10]){
	time_t timer;
	struct tm* t;

	// 시간을 구해와서 t에 저장
	timer = time(NULL);
	t = localtime(&timer);

	// 구해온 int type의 사간을 char 타입으로 변환해서 저장하기 위한 공간
	char* years[4];
	char* months[2];
	char* days[2];
	char dot[] = ".";

	memset(years, 0x00, sizeof(years));
	memset(months, 0x00, sizeof(months));
	memset(days, 0x00, sizeof(days));

	char year[10];
	char month[10];
	char day[10];

	sprintf(year, "%d", t->tm_year + 1900 - 2000);
	sprintf(month, "%d", t->tm_mon + 1);
	sprintf(day, "%d", t->tm_mday);

	strncpy(years, year, 2);
	strncpy(months, month, 2);
	strncpy(days, day, 2);

	strcat(date, year);
	strcat(date, dot);
	strcat(date, month);
	strcat(date, dot);
	strcat(date, day);

	return time;
}
