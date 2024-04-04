```
Degree: Artificial Intelligence
Subject: Fundamentals of Programming 2
```
# Delivery: 3
```
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

First of all, we know that the two header files are depenencies of the C files. From the names we can infer that each one is a dependency of the C file with the same name. Checking the contents of the files we see that this is the case.

Furthermore, we see that the only `main` function is in the `sort.c`, so all of the other files are dependencies of this one, as the implementations of the sorting algorithms are in `merge.c` and `bubble.c`.

#### Part 2
We compile the program using gcc with the following command:
```bash
gcc -o app *.c
```
Where the star is there to represent any C file in the current directory.

There is no error compiling.


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

##### Question 5
The complexity of bubble sort is O(n^2) in the worst case, as it uses two loops to complete the sorting.

The number of comparisons for a natural number $N$ that is the size of the array to sort is:
$$
(N * (N - 1)) / 2
$$
Therefore the time complexity is $O(N^2)$.
> TODO: Explain why the number of comparisons is $N(N-1)/2$.

#### Part 5
##### Question 6

The following lines implement the "divide part":
```c

```
