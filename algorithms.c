//
//  algorithms.c
//  MMS
//
//  Created by Charles Hardes on 10/14/15.
//  Copyright (c) 2015 Charles Hardes. All rights reserved.
//

#include "algorithms.h"
#include <stdlib.h>
#include <time.h>
#include <limits.h>

void algorithm(int *arr, int size, int value, int version, FILE *file) {

    clock_t T1, T2;
    double time;
    int *outputArr;
    
    outputArr = createArr(size);
    initArr(outputArr, size);
    
    T1 = clock();//start timer
    
    //Call the appropriate algorithm on the array
    switch (version) {
        case 1 :
            outputArr = algorithm_1(arr, outputArr, size, value);
            break;
        case 2 :
            outputArr = algorithm_2(arr, outputArr, size, value);
            break;
        case 3 :
            outputArr = algorithm_3(arr, outputArr, size, value);
            break;
    }
    
    T2 = clock();//end timer
    time = (double)(T2 - T1) / CLOCKS_PER_SEC;//get total time
    
    value = sumArray(outputArr, size);
    print_results(outputArr, size, value, file);
    
    fprintf(file, "Time to execute: %fs\n", time);
    
    free(outputArr);
}


void print_results(int *arr, int size, int value, FILE *file) {
    
    int i;

    //print original array
    fprintf(file, "[");
    for (i = 0; i < size - 1; i++) {
        fprintf(file, "%d, ", arr[i]);
    }
    fprintf(file, "%d]\n", arr[size - 1]);//print last element with closing bracket
    
    fprintf(file, "%d\n", value);//print value

}

int *algorithm_1(int *arr, int *outputArr, int size, int value) {
    
    int i, k, *tempArr1, *tempArr2, *tempArr3;
    k = value;
    
    if (k == 1) {
        outputArr[0]++;
        return outputArr;
    }
    else if ((i = isCoin(arr, size, k))) {
        outputArr[i]++;
        return outputArr;
    }
    else {
        //loop through every integer from 1 to "value"
        for (i = 1; i < k; i++) {
            
            //create and initilize three temprorary arrays of size "size" to all 0's
            tempArr1 = createArr(size);
            tempArr2 = createArr(size);
            tempArr3 = createArr(size);
            initArr(tempArr1, size);
            initArr(tempArr2, size);
            initArr(tempArr3, size);
            
            //recursively call algorithm_1 on array from 1 -> i and i + 1 -> "value"
            tempArr1 = algorithm_1(arr, tempArr1, size, i);
            tempArr2 = algorithm_1(arr, tempArr2, size, k - i);
            
            //add the sum of all elements at each index of tempArr1 and temArr2 together, assign to tempArr3
            addArr(tempArr1, tempArr2, tempArr3, size);
            
            //if this new sum of elements array (tempArr3) is less than the running min (outputArr) or the current output array is not a solution, then replace outputArr with tempArr3
            if ((sumArray(tempArr3, size) < sumArray(outputArr, size)) || !coinCheck(outputArr, arr, size, k)) {
                copyArr(tempArr3, outputArr, size);
            }
            
            free(tempArr1);
            free(tempArr2);
            free(tempArr3);
        }
    }
    
    return outputArr;
    
}

int *algorithm_2(int *arr, int *outputArr, int size, int value) {
    
    int index;
    
    //set index to largest coin value
    index = size - 1;
    
    while (index >= 0) {
        if (arr[index] <= value) {
            outputArr[index] = value / arr[index];
            value -= arr[index] * outputArr[index];
        }
        index--;
    }
    return outputArr;
}

int *algorithm_3(int *arr, int *outputArr, int size, int value) {
    int i, p, min, C[value], TempArr[value], min_count=0, index, n, j;

    C[0] = 0;
    for(p=1;p<=value;p++)
    {
        min = INT_MAX; //maximum integer current machine supports
        for(i=0;i<size;i++)
        {
            if(arr[i] <= p)
            {
                if(1+C[p-arr[i]]<min)
                {
                    min = 1+C[p-arr[i]];
                } //end if(1+outputArr...)
            } //end if(arr[i] <= p)
        } //end for(i)
        C[p] = min;
    } //end for(p)
    min_count = C[p-1];
    index = p-1;
    n = 0;
    for(i=value;i>=0;i--)
    {
        if(C[i] < C[index])
        {
            for(j=0;j<size;j++)
            {
                if( (index-i) == arr[j])
                {
                    TempArr[n] = index-i;
                    index = i;
                    n++;
                }
            }
        }
    }
    for(i=0;i<size;i++)
    {
        for(j=0;j<min_count;j++)
        {
            if(TempArr[j] == arr[i])
            {
                outputArr[i]++;
            }
        }
    }
    return outputArr;
}


//returns the sum of all elements in the array of ints
int sumArray(int *arr, int size) {
    
    int i, sum;
    
    sum = 0;
    for (i = 0; i < size; i++) {
        sum += arr[i];
    }
    return sum;
}

//returns the index of the coin value that matches the value passed, if it doesn't match, returns 0
int isCoin(int *arr, int size, int v) {
    
    int i;
    
    for (i =0; i < size; i++) {
        if (arr[i] == v) {
            return i;
        }
    }
    return 0;
}

//dynamically creates an array of size "size"
int *createArr(int size) {
    
    int *newArr;
    
    newArr = (int *)malloc(sizeof(int) * size);
    
    return newArr;
}

//initializes an int array of size "size" with all 0's
void initArr(int *arr, int size) {
    
    int i;
    
    for (i = 0; i < size; i++) {
        arr[i] = 0;
    }
}

//initializes an int array of size "size" with all equal values so that the sum is MAX_INT (2147483647)
void initMaxArr(int *arr, int size) {
    
    int i, max;
    
    max = 2147483647 / size;
    for (i = 0; i < size; i++) {
        
        arr[i] = max;
    }
}


//copies an array into another array of the same size
void copyArr(int *sourceArr, int *destArr, int size) {
    
    int i;
    
    for (i = 0; i < size; i++) {
        destArr[i] = sourceArr[i];
    }
}

//return an array of the sums of the elements at each index of two arrays
void addArr(int *arr1, int *arr2, int *arr3, int size) {
    
    int i;
    for (i = 0; i < size; i++) {
        arr3[i] = arr1[i] + arr2[i];
    }
}

//ensure that the array of coin values multiplied by their value adds up to the value
int coinCheck(int *arr, int *inputArr, int size, int value) {
    
    int i, sum;
    sum = 0;
    for (i = 0; i < size; i++) {
        sum += arr[i] * inputArr[i];
    }
    
    return (sum == value);
}
