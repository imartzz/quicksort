#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Função para trocar dois elementos
void swap(int* a, int* b) {
    int t = *a;
    *a = *b;
    *b = t;
}

// Função para escolher o pivô como mediana de três
int medianOfThree(int arr[], int left, int right) {
    int mid = left + (right - left) / 2;
    if (arr[left] > arr[mid])
        swap(&arr[left], &arr[mid]);
    if (arr[left] > arr[right])
        swap(&arr[left], &arr[right]);
    if (arr[mid] > arr[right])
        swap(&arr[mid], &arr[right]);
    return mid;
}

/* ================================================================== */
/* 1. IMPLEMENTAÇÃO COM PIVÔ NO PRIMEIRO ELEMENTO         */
/* ================================================================== */
int partitionFirst(int arr[], int left, int right) {
    int pivot = arr[left];
    int i = left;
    for (int j = left + 1; j <= right; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[left], &arr[i]);
    return i;
}

void QuickSortFirstPivot(int arr[], int left, int right) {
    if (left < right) {
        int pi = partitionFirst(arr, left, right);
        QuickSortFirstPivot(arr, left, pi - 1);
        QuickSortFirstPivot(arr, pi + 1, right);
    }
}

/* ================================================================== */
/* 2. IMPLEMENTAÇÃO COM PIVÔ NO ÚLTIMO ELEMENTO          */
/* ================================================================== */
int partitionLast(int arr[], int left, int right) {
    int pivot = arr[right];
    int i = (left - 1);
    for (int j = left; j <= right - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[right]);
    return (i + 1);
}

void QuickSortLastPivot(int arr[], int left, int right) {
    if (left < right) {
        int pi = partitionLast(arr, left, right);
        QuickSortLastPivot(arr, left, pi - 1);
        QuickSortLastPivot(arr, pi + 1, right);
    }
}

/* ================================================================== */
/* 3. IMPLEMENTAÇÃO COM PIVÔ ALEATÓRIO                 */
/* ================================================================== */
int partitionRandom(int arr[], int left, int right) {
    int random = left + rand() % (right - left + 1); // +1 para incluir o right
    swap(&arr[random], &arr[right]);
    return partitionLast(arr, left, right);
}

void QuickSortRandomPivot(int arr[], int left, int right) {
    if (left < right) {
        int pi = partitionRandom(arr, left, right);
        QuickSortRandomPivot(arr, left, pi - 1);
        QuickSortRandomPivot(arr, pi + 1, right);
    }
}

/* ================================================================== */
/* 4. IMPLEMENTAÇÃO COM PIVÔ MEDIANA DE TRÊS                */
/* ================================================================== */
int partitionMedianOfThree(int arr[], int left, int right) {
    int pivotIndex = medianOfThree(arr, left, right);
    swap(&arr[pivotIndex], &arr[right]); // Coloca o pivô no final para usar a lógica de partição `partitionLast`
    return partitionLast(arr, left, right);
}

void QuickSortMedianOfThree(int arr[], int left, int right) {
    if (left < right) {
        int pi = partitionMedianOfThree(arr, left, right);
        QuickSortMedianOfThree(arr, left, pi - 1);
        QuickSortMedianOfThree(arr, pi + 1, right);
    }
}


/* ================================================================== */
/* FUNÇÕES AUXILIARES PARA TESTES                */
/* ================================================================== */

// Cria um array com valores aleatórios
void createRandomArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        arr[i] = rand() % size;
    }
}

// Cria um array já ordenado
void createSortedArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        arr[i] = i;
    }
}

// Cria um array quase ordenado
void createNearlySortedArray(int arr[], int size) {
    createSortedArray(arr, size);
    for (int i = 0; i < size / 10; i++) { // Desordena 10% dos elementos
        swap(&arr[rand() % size], &arr[rand() % size]);
    }
}



int main() {
    
    const int size = 100000; 
    int arr[size];

    // Escolha qual tipo de array criar:
    srand(time(NULL));
    //createRandomArray(arr, size); 
     //createSortedArray(arr, size); 
      createNearlySortedArray(arr, size);

    // Criar cópias do array original para cada teste
    int arrFirst[size];
    int arrLast[size];
    int arrRandom[size];
    int arrMedian[size];

    for (int i = 0; i < size; i++) {
        arrFirst[i]  = arr[i];
        arrLast[i]   = arr[i];
        arrRandom[i] = arr[i];
        arrMedian[i] = arr[i];
    }

    clock_t start, end;
    double cpu_time_used;

    printf("Testando com array de tamanho %d...\n", size);

    // QuickSort com pivô no primeiro elemento
    start = clock();
    QuickSortFirstPivot(arrFirst, 0, size - 1);
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Tempo (Primeiro Pivo): %f segundos\n", cpu_time_used);

    // QuickSort com pivô no último elemento
    start = clock();
    QuickSortLastPivot(arrLast, 0, size - 1);
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Tempo (ultimo Pivo): %f segundos\n", cpu_time_used);

    // QuickSort com pivô aleatório
    start = clock();
    QuickSortRandomPivot(arrRandom, 0, size - 1);
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Tempo (Pivo Aleatorio): %f segundos\n", cpu_time_used);

    // QuickSort com pivô mediana de três
    start = clock();
    QuickSortMedianOfThree(arrMedian, 0, size - 1);
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Tempo (Mediana de Tres): %f segundos\n", cpu_time_used);

    

    return 0;
}
