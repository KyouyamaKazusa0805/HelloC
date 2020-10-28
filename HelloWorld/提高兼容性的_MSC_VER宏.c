#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	int i;
#ifdef _MSC_VER
	scanf_s("%d", &i);
	printf("scanf_s result: ");
#else
	scanf("%d", &i);
	printf("scanf result: ");
#endif // _MSC_VER

	printf("%d\n", i);
}
