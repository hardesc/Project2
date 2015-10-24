#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<time.h>
#include "algorithms.h"

int main(int argc, char **argv) {
    
    FILE *ifp, *ofp;
    ifp = fopen(argv[1], "r");//for command line
    //ifp = fopen("/Users/charleshardes/Documents/XCode Workspace/Project2/Project2/test.txt", "r");//for XCode
    char line[200], *token;
    int denomArray[10][100], valueArray[10], option, i, j, k, n, m;
    const char s[3] = ", ";
    
    if (ifp == NULL) {
        fprintf(stderr, "Can't open input file!\n");
        exit(1);
    }
    
    ofp = fopen("Coin1_change.txt", "w");//for command line
    //ofp = fopen("/Users/charleshardes/Documents/XCode Workspace/Project2/Project2/Coin1_change.txt", "w");//for XCode
    
    if (ofp == NULL) {
        fprintf(stderr, "Can't open output file!\n");
        exit(1);
    }
    j = 0;
    while (1) {
        i = 0;
        if (fgets(line, 200, ifp) == NULL){break;}//if no more input, stop
        
        //condition that input is an array
        if (line[0] == '[') {
            memmove(line, line + 1, strlen(line));//strip leading '['
            line[strlen(line) - 2] = ' ';//strip trailing ']'
            token = strtok(line, s);//break up string into tokens
            while (token != NULL) {
                denomArray[j][i] = atoi(token);//convert token to int
                token = strtok(NULL, s);
                i++;
            }
            denomArray[j][i - 1] = 1111111111;//marks end of input
        }
        
        //condition that input is a single value
        else {
            valueArray[j] = atoi(line);
            j++;
        }
    }
    n = j;
    
    //loop through arrays to print outputs
    for (j = 0; j < n; j++){
        k = 0;

        //loop through array elements
        while (denomArray[j][k] != 1111111111) {
            
            option = atoi(argv[2]);//                                   FOR COMMAND LINE
            
            k++;
        }
        int *newArr, temp;
        newArr = (int *) malloc(sizeof(int) * (k));
        
        //copy to new array to be passed to computing function
        for (m = 0; m < k; m++) {
            temp = denomArray[j][m];//for debugging
            newArr[m] = denomArray[j][m];
        }
        
        //option = 1;//                                                   FOR XCODE
        
        algorithm(newArr, k, valueArray[j], option, ofp);

        free(newArr);
        printf("\n\n");
    }
    
    fclose(ifp);
    fclose(ofp);
    
    return 0;
}
