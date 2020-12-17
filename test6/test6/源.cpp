#include<stdio.h>
int main()
{
	int x, y;
	printf("enter x:");
	scanf_s("%d", &x);
	if (x>1)
		if(x>=10)
			y = x+x+x-11;
		else
			y = x+x-1;
	
	else y = x;
	printf("x=%d,y=%d\n", x, y);
	return 0;
}