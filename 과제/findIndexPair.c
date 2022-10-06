#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning (disable : 4996)

#define N 8

typedef struct{
    int elem;
    int idx;
}Dict;

int partition(Dict D[], int left, int right, int k) {
    int low, high, pivot;
    low = left - 1;
    high = right;
    pivot = D[k].elem;

    do {
        do {
            low++;
        } while (D[low].elem < pivot);
        do {
            high--;
        } while (D[high].elem > pivot);

        if (low < high) {
            Dict temp = D[low];
            D[low] = D[high];
            D[high] = temp;
        }
    } while (low < high);

    Dict temp = D[low];
    D[low] = D[right];
    D[right] = temp;
   
    return low;
}

void QuickSort(Dict D[], int left, int right) {
    if (left < right) {
        int k = right;
        int q = partition(D, left, right, k);
        QuickSort(D, left, q - 1);
        QuickSort(D, q + 1, right);
    }
}

void buildDic(Dict D[], int A[]){
    for (int i = 0; i < N; i++){
        D[i].elem = A[i];
        D[i].idx = i;
    }
    QuickSort(D, 0, N-1);
}

int findElement(Dict D[], int v){
    int left = 0;
    int right = N - 1;

    while (left <= right) {
        int mid = (left + right) / 2;
        if (D[mid].elem == v)
            return D[mid].idx;
        else if (D[mid].elem < v) {
            left = mid + 1;
            continue;
        }
        else if (D[mid].elem > v) {
            right = mid - 1;
            continue;
        }
    }
    return -1;
}

void findIndexPair(Dict D[], int A[], int s){
    for (int i = 0; i < N; i++) {
        int v = s - A[i];
        int j = findElement(D, v);
        if (j != -1 && i != j) {
            printf("findindexpair : (%d, %d)\n", i, j);
            return;
        }
    }
    printf("NotFound\n");
    return;
}

int main(){
    int A[N] = { 2, 21, 8, 3, 5, 1, 13, 1 };
    Dict D[N];

    buildDic(D, A);

    for (int i = 0; i < N; i++)
        printf("(%d, %d) ", D[i].elem, D[i].idx);
    printf("\n");

    int num;
    printf("만들려는 수 : ");
    scanf("%d", &num);

    findIndexPair(D, A, num);

    return 0;
}
