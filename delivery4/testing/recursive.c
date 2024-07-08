#include <stdio.h>
#include <stdlib.h>

int Foo(int v[], int n) {
    if (n == 0)
        return 0;
    return Foo(v, n - 1) * 10 + v[n - 1];
}

int main(int argc, char *argv[]) {
    int SIZE = atoi(argv[1]);

    int v[SIZE];
    for (int i = 0; i < SIZE; i++) {
        v[i] = i;
    }

    printf("%d\n", Foo(v, SIZE));
}
