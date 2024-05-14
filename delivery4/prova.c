#include <stdlib.h>
#include <stdio.h>

int Foo (int v[], int n)
{
    if (n == 0)
        return 0;
    else
    {
        return Foo (v, n-1)*10+v[n-1];
    }
}

int FooIt (int v[], int n)
{
    int res = 0;
    for (int i=0; i<n; i++)
    {
        res = res*10 + v[i];
    }
    return res;
}

int main()
{
    int v[] = {3,5,7,4,6};
    int n = 5;
    printf("%d\n", Foo(v, n));
    printf("%d\n", FooIt(v, n));
    return 0;
}