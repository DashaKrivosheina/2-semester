#include <iostream>
using namespace std;

void heapify(int arr[], int n, int i) { //i - узел ветки, которую мы рассматриваем
    int largest = i;
    int L = 2 * i + 1;
    int R = 2 * i + 2;
    if ((L < n) && (arr[L] > arr[largest])) { largest = L; }
    if ((R < n) && (arr[R] > arr[largest])) { largest = R; }
    if (largest != i) {
        swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

void HeapSort(int arr[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--) { //постройка дерева, начиная с ветки с номером n / 2 - 1
        heapify(arr, n, i);
    }
    for (int i = n - 1; i >= 0; i--) {
        swap(arr[i], arr[0]); //обмен местами узлового и последнего элементов
        heapify(arr, i, 0); //уменьшаем рассматриваемый массив
    }
}

int main()
{
    int n; //размер массива
    cin >> n;
    int arr[1000];
    cout << "enter an array of " << n << " elements \n";
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }
    HeapSort(arr, n);
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
}