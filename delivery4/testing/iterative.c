#include <stdio.h>
#include <stdlib.h>

int Foo(int v[], int n) {
  int result = 0;
  for (int i = 0; i < n; i++) {
    result = result * 10 + v[i];
  }
  return result;
}

int main(int argc, char *argv[]) {
    int SIZE = atoi(argv[1]);

    int v[SIZE];
    for (int i = 0; i < SIZE; i++) {
        v[i] = i;
    }

    printf("%d\n", Foo(v, SIZE));
}
