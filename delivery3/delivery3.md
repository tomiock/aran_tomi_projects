# Delivery 3
```
Degree: Artificial Intelligence
Subject: Fundamentals of Programming 2

Authors:
    Name: Ockier Poblet, Tomas      NIU: 1707185
    Name: Oliveras Sanchez, Aran    NIU: 1708069
```

## Exercise 1
The complexity of the program is $O(2n)$ because the program has two bucles.
## Exercise 2

#### Part 1
List of the provided files:
- `bubble.h`
- `bubble.c`
- `merge.h`
- `merge.c`
- `sort.c`

First of all, we know that the two header files are dependencies of the C files. From the names we can infer that each one is a dependency of the C file with the same name. Checking the contents of the files we see that this is the case.

Furthermore, we see that the only `main` function is in the `sort.c`, so all of the other files are dependencies of this one, as the implementations of the sorting algorithms are in `merge.c` and `bubble.c`.

#### Part 2
We compile the program using `gcc` with the following command:
```bash
gcc -o app *.c
```
Where the star is there to represent any C file in the current directory.

There is no error compiling. However, if we have done the first exercise first, then there is an extra C file called `search.c` that if its in the same directory as the other ones, the above command will give error in compile time. This is because there are two `main` functions provided one in `sort.c` and the other in `search.c`.

To overcome this issue we need to change the directory of the `search.c` file or run the following command, that specifies the files that we want to compile:
```bash
gcc -o app bubble.c merge.c sort.c
```

#### Part 3
To figure out the needed arguments we can look at the `checkArguments` in the file `sort.c`.

We see that there is an error message if we do not give it arguments that explains the format of the arguments"
```
Error...
Format: program sortType size
sortType: 0 or 1 (0 bubble sort, 1 merge sort)
size: number of elements you want to sort (integer)
```
Looking at the code we can see that this message comes from the `checkArguments` function, which is called in the `main` function.

##### Question 1
To run the program with bubble sort and 10 elements we can use the following command:
```bash
./app 0 10
```
Where `app` is the name of the compiled program that we decided.

To run the program with merge sort and 1000 elements we can use the following command:
```bash
./app 1 1000
```

#### Part 4
Out implementation of bubble sort is in the file `bubble.c`. Here is the function:
```c
void bubbleSort(int arr[], int n)
{
    int i, j;
    for (i = 0; i < n - 1; i++) {
        // Last i elements are already in place
        for (j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1])
                swap_int(&arr[j], &arr[j + 1]);
        }
    }
}
```

We also need the function that swaps two integers using their pointers:
```c
void swap_int(int *xp, int *yp)
{
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}
```

##### Question 2
The complexity of bubble sort is O(n^2) in the worst case, as it uses two loops to complete the sorting.

The number of comparisons for a natural number $N$ that is the size of the array to sort is:
$$
(N * (N - 1)) / 2
$$
Therefore the time complexity is $O(N^2)$.

#### Part 5
##### Question 3
The key fact that we have to notice is that the arrays are created using pivots that are in the middle of the array. From this pivot, two sub arrays are defined from which we divide the original array. The two array are called `a` and `aux`, the algorithm works with this arrays just as addresses in memory, just redefining how large they are or how many elements they have.

We can see that the arrays are only dealt with inside of for loops.

The following lines implement the "divide part":
```c
for (k = i; k <= j; k++) {
    if (pointer_left == mid + 1) {      // left pointer has reached the limit
        aux[k] = a[pointer_right];
        pointer_right++;
    } else if (pointer_right == j + 1) {        // right pointer has reached the limit
        aux[k] = a[pointer_left];
        pointer_left++;
    } else if (a[pointer_left] < a[pointer_right]) {        // pointer left points to smaller element
        aux[k] = a[pointer_left];
        pointer_left++;
    } else {        // pointer right points to smaller element
        aux[k] = a[pointer_right];
        pointer_right++;
    }
}
```
The following lines implement the "conquer part":
```c
for (k = i; k <= j; k++) {
    a[k] = aux[k];
}
```
Which corresponds to the other for loop on the program.
#### Part 6
##### Question 4

The first function provided, `cp_Wtime_sec_micro()`, returns the seconds and the microseconds.

The second function, `cp_Wtime_micro()`, returns only the microseconds.

The third one, `cp_Wtime_sec()`, returns the seconds.


```c
int first_time = cp_Wtime_micro();
if (type==0)
    bubbleSort(array, size);
else //if (type==1)
{
    int * arrayAux=malloc(sizeof(int)*size);
    mergeSort(0, size-1, array, arrayAux);
    freeArray(arrayAux);
}
int second_time = cp_Wtime_micro();
printArray(array, type, size);
freeArray(array);
printf("First time: %d and second time: %d\n", first_time, second_time);
printf("It has take %d microseconds.\n", second_time-first_time);

``` 

#### Part 7
##### Question 5
Table with to compare how much each algorithm takes. Note that the main bottleneck that they have is the printing of the solution. It is the part of the program that takes the most time. Initially the program did not compile with large numbers, therefore we too out the printing function.

| Sort        | 100 Numbers | 1000 Numbers | 10000 Numbers | 100000 Numbers | 1000000 Numbers |
| ----------- | ----------- | ------------ | ------------- | -------------- | --------------- |
| Bubble Sort | 54$\mu$s    | 3251$\mu$s   | 109075$\mu$s  | 18s            | 2106s           |
| Merge Sort  | 8$\mu$s     | 97$\mu$s     | 3093$\mu$s    | 14227$\mu$s    | 132629$\mu$s    |

We also have exchange the time units from microseconds to seconds depending on the size of the numbers. This does not change the execution time in any meaningful way.

> $\mu$s = microseconds

