#include<stdio.h>
#include "AStack.c"


 int main(){
	char s[256];
	fgets(s, 256, stdin);
	s[strlen(s)] = '\0';
	printf("%.2f", chuoi(s));

	return 0;
 }

