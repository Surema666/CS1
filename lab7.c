
#include <stdio.h>
#include <stdlib.h>

void swap(int *a, int *b){
    int tmp = *a;
    *a = *b;
    *b = tmp;

}

void swapcheck(int *arr[], int size,int *itter){



for (int i = 0; i < size; i++)
{
    int swaps = 0;
    for(int j = 0;j < size;j++){
        if (arr[j] > arr[j+1])
    {
        swap(&arr[j],&arr[j+1]);
        *itter = *itter + 1;
        swaps++;
    }
    }
    printf("index %d swaps:%d\n", i, swaps);
}


}

void print(int arr[],int size){

    for (size_t i = 0; i < size; i++)
    {
        if(i != size - 1){
        printf("%d,", arr[i]);
        }else{
        printf("%d", arr[i]);
        }
    }
    printf("\n");

}

int main(void){
    int array[] = {97,16,45,63,13,22,7,58,72};
    int arrSize = 9;
    int itteration =0;
    printf("array before:");
    print(array, arrSize);
    printf("array itterations:\n");
    swapcheck(array,arrSize,&itteration);
    printf("array after:");
    print(array, arrSize);
    printf("number of itterations: %d", itteration);
    return 0;
}