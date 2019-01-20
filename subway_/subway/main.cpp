#define _CRT_SECURE_NO_WARNINGS
#include "subway.h"

using namespace std;

int main(int argc, char *argv[])
{
	
	Subway();
	char c[20];
	if (argv[1][1] == 'l') {
		strcpy(c, argv[2]);
		printLine(c);
	}
	else if (argv[1][1] == 'a') {  //»´±È¿˙£¨ªª≥À’æ∂ÓÕ‚+3
		char start[20];
		strcpy(start, argv[2]);
		searchAll(start);
	}
	else if (argv[1][1] == 'z') {  //≤‚ ‘
		char f[50];
		strcpy(f, argv[2]);
		Test(f);
	}
	return 0;
}