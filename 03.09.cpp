#include <iostream>

int funccmp(const void* val1, const void* val2) {
    int x = *(int*)val1;
    int y = *(int*)val2;
    //return (*(int*)val1 - *(int*)val2);
    return x - y;
}

void swap(void* val1, void* val2, size_t size) {
    void* box = malloc(size);
    memcpy(box, val2, size);
    memcpy(val2, val1, size);
    memcpy(val1, box, size);
    free(box);
}

void qsort(void* first, size_t number, size_t size, int (*comparator)(const void*, const void*)) {
    if (number == 0) {
        return;
    }
    auto left = first;
    auto right = (char*)first + (number - 1) * size;
    size_t currnum = (number - 1) / 2;
    auto curr = (char*)first + currnum*size;

    while (funccmp(left, curr) < 0) {
        left = (char*)left + size;
    }
    while (funccmp(right, curr) > 0) {
        right = (char*)right - size;
    }
    if (left <= right) {
        if (funccmp(left, right) > 0) {
            swap(left, right, size);
        }
        left = (char*)left + size;
        right = (char*)right - size;
    }
    
    while (funccmp(left, right) <= 0 ){
        while (funccmp(left, curr) < 0) {
            left = (char*)left + size;
        }
        while (funccmp(right, curr) > 0) {
            right = (char*)right - size;
        }
        if (left <= right) {
            if (funccmp(left, right) > 0) {
                swap(left, right, size);
            }
            left = (char*)left + size;
            right = (char*)right - size;
        }

    }
    if (first < right) {
        size_t divnum = ((char*)right - (char*)first) / size + 1;
        qsort(first, divnum, size, funccmp);
    }
    if (left < (char*)first + (number - 1) * size) {
        size_t divnum = ((char*)first + (number - 1) * size - (char*)left) / size + 1;
        qsort(left, divnum, size, funccmp);
    }
    
}


int main()
{
    int mass[] = { 4, 5, 8, 2, 0, 21, 1 };
    qsort(mass, 7, sizeof(int), funccmp);
    for (int j = 0; j < 7; j++) {
        std::cout << mass[j] << " ";
    }
}
