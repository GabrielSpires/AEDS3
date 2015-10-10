#include <stdio.h>

int main(int argc, char const *argv[])
{
	int i, n, m, achou;

	for (i = 0; i < (n-m); ++i)
	{
		achou = 1;
		if (T[i+j] != p[j])
		{
			achou = 0;
		}
		if (achou)
		{
			return i;
		}
	}
	return 0;
}