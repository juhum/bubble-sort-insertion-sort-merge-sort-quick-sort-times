//#define N 8000
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <windows.h>
#include <vector>
#include <cmath>
#include <fstream>


void print(int A[], int n) {
    for (int i = 0; i < n; i++) {
        std::cout << A[i] <<std::endl;
    }
}
/////////////////
int partition(int A[],int left,int right){
    int pivot = A[right];

    int i = (left - 1);
    for (int j = left; j < right; j++) {
        if (A[j] <= pivot) {
            i++;
            std::swap(A[i], A[j]);
        }
    }

    std::swap(A[i + 1], A[right]);

    return (i + 1);
}

void quickSort(int A[], int p, int r) {
    if (p < r) {
        int q = partition(A, p, r);
        quickSort(A, p, q - 1);
        quickSort(A, q + 1, r);
    }
}

///////////////////

void bubbleSort(int arr[], int n)
{
    int i, j;
    for (i = 0; i < n - 1; i++)
        for (j = 0; j < n - i - 1; j++)
            if (arr[j] > arr[j + 1])
                std::swap(arr[j], arr[j + 1]);
}
///////////////////

void insertionSort(int arr[], int n)
{
    int i, key, j;
    for (i = 1; i < n; i++)
    {
        key = arr[i];
        j = i - 1;

        while (j >= 0 && arr[j] > key)
        {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

/////////////////


void merge(int arr[], int p, int q, int r) {

    const int n1 = q - p + 1;
    const int n2 = r - q;

    int L[n1], M[n2];

    for (int i = 0; i < n1; i++)
        L[i] = arr[p + i];
    for (int j = 0; j < n2; j++)
        M[j] = arr[q + 1 + j];

    int i =0;
    int j = 0;
    int k = p;
    while (i < n1 && j < n2) {
        if (L[i] <= M[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = M[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = M[j];
        j++;
        k++;
    }
}

void mergeSort(int arr[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;

        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);

        merge(arr, l, m, r);
    }
}

/////

int main() {
    srand(time(NULL));
    LARGE_INTEGER t1, t2, f, diff;
    std::vector<double>q,m,b,in,sizes;
    int inc = 10;
    int N = 5;
    int count =0;
    for (int j=1;j<2000;j++){

        count++;
        int *A = new int[N];
        for(int i = 0; i < N; i++) {
            A[i] = rand();
        }

        int *B = new int[N];
        int *C = new int[N];
        int *D = new int[N];
        for (int i = 0; i < N; i++) {
            B[i] = A[i];
            C[i] = A[i];
            D[i] = A[i];
        }


        QueryPerformanceCounter(&t1);
            bubbleSort(C, N);
        QueryPerformanceCounter(&t2);
        diff.QuadPart = (t2.QuadPart - t1.QuadPart);
        b.push_back(diff.QuadPart / float(N));

        QueryPerformanceCounter(&t1);
            insertionSort(D, N);
        QueryPerformanceCounter(&t2);
        diff.QuadPart = (t2.QuadPart - t1.QuadPart);
        in.push_back(diff.QuadPart / float(N));

        QueryPerformanceCounter(&t1);
            mergeSort(B, 0, N - 1);
        QueryPerformanceCounter(&t2);
        diff.QuadPart = (t2.QuadPart - t1.QuadPart);
        m.push_back(diff.QuadPart / float(N));

        QueryPerformanceCounter(&t1);
            quickSort(A, 0, N - 1);
        QueryPerformanceCounter(&t2);
        diff.QuadPart = (t2.QuadPart - t1.QuadPart);
        q.push_back(diff.QuadPart / float(N));



        sizes.push_back(N);
       N = N + inc;

        delete[] A;
        delete[] B;
        delete[] C;
        delete[] D;


    }



    std::ofstream of("r.txt", std::ofstream::out);
    of << "size\tquick\tmerge\tbubble\tinsertion\n";
    for (int i = 0; i < q.size(); i++) {
        of << sizes[i]
           << '\t'
           << floor(q[i]) << ',' << floor((q[i] - floor(q[i]))*1000+0.5)
           << '\t'
           << floor(m[i]) << ',' << floor((m[i] - floor(m[i])) * 1000 + 0.5)
           << '\t'
           << floor(b[i]) << ',' << floor((b[i] - floor(b[i])) * 1000 + 0.5)
           << '\t'
           << floor(in[i]) << ',' << floor((in[i] - floor(in[i])) * 1000 + 0.5)
           << '\n';
    }
    of.close();
    system("START \"\" \"C:\\Program Files\\Microsoft Office\\root\\Office16\\EXCEL.EXE\" r.txt");


    return 0;
}
