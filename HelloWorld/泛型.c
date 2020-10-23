#pragma warning (disable: 6031)

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define swapper(a, b) _Generic(a,\
	int *: swapi(a, b),\
	double *: swapd(a, b),\
	short *: swaps(a, b),\
	default: printInvalid()\
)

inline void swapi(int *, int *);
inline void swapd(double *, double *);
inline void swaps(short *, short *);
void printInvalid(void);

int main(void)
{
	int i = 2, j = 3;
	double d = 2, e = 3;
	short s = 2, t = 3;
	char *l = "a", *r = "b";
	swapper(l, r);
}

void printInvalid(void)
{
	puts("Invalid input.");
}

inline void swapi(int *l, int *r)
{
	int t = *l;
	*l = *r;
	*r = t;
}

inline void swapd(double *l, double *r)
{
	double t = *l;
	*l = *r;
	*r = t;
}

inline void swaps(short *l, short *r)
{
	short t = *l;
	*l = *r;
	*r = t;
}