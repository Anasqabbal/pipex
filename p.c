#include "pipex.h"

void	trivle(int p[][3][2])
{
	ft_printf("the value of p is %d\n", ***p);
}

void	douvle(int p[][2])
{
	trivle(&p);
}

int main()
{
	int a;
	int **p;

	a = 9;
	douvle(&p);
}