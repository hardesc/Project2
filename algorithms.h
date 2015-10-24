//
//  algorithms.h
//  MMS
//
//  Created by Charles Hardes on 10/14/15.
//  Copyright (c) 2015 Charles Hardes. All rights reserved.
//

#ifndef __MMS__algorithms__
#define __MMS__algorithms__

#include <stdio.h>

void algorithm(int *arr, int size, int value, int version, FILE *file);


void print_results(int *arr, int size, int print_option, FILE *file);

int *algorithm_1(int *arr, int *outputArr, int size, int value);

int *algorithm_2(int *arr, int *outputArr, int size, int value);

int sumArray(int *arr, int size);

int isCoin(int *arr, int size, int v);

int *createArr(int size);

void initArr(int *arr, int size);

void initMaxArr(int *arr, int size);

void copyArr(int *sourceArr, int *destArr, int size);

void addArr(int *arr1, int *arr2, int *arr3, int size);

int coinCheck(int *arr, int *inputArr, int size, int value);

#endif /* defined(__MMS__algorithms__) */
