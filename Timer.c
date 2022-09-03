
#include <time.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>

char getTime(char date[10]){
	time_t timer;
	struct tm* t;

	timer = time(NULL);

	t = localtime(&timer);

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

	// sprintf(year, "%d", t->tm_year + 1900 - 2000);
	// sprintf(month, "%d", t->tm_mon + 1);
	// sprintf(day, "%d", t->tm_mday);

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
