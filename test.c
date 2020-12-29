
#include <stdio.h>
 #include <stdlib.h>

void fill(char *str)
{
	str[0] = 'k';
}
int main(int argv, char **ag)
{
	char *ok = malloc(sizeof(char) * 3);
	ok[2] = '\0';
	fill(ok);
	printf("%s\n", ok);
}