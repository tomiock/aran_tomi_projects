#include <stdio.h>
#include <stdlib.h>

int CountNegativeValues(int arr[])
{
    int neg_num = 0;            //1
    for(int i=0; i<10; i++)     //2n+2
    {
        if(arr[i]<0)            //n
        {
            neg_num++;          //worst case: n
        }
    }
    return neg_num;             //1
}

int FindMax(int arr[])          //
{
    int max = arr[0];           //1
    for(int i=1; i<10; i++)     //2n+2
    {
        if(arr[i]>max)          //n
        {  
            max=arr[i];         //worst case: n
        }
    }
    return max;                 //1
}

int main()
{
    int vector[10]={2,-6,-1,4,-7,8,-3,3,2,-6};
    printf("The input array is: %d", vector[0]);
    for(int i=1; i<10; i++)
    {
        printf(",%d", vector[i]);
    }
    printf("\nAnd there are %d negative numbers.\n", CountNegativeValues(vector));
    printf("The max value on the array is: %d\n", FindMax(vector));
    printf("The complexity of the program is O(2n) because the program has two bucles.\n");
    return 0;
}