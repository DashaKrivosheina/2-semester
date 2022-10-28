#include <iostream>
using namespace std;

template<typename T>
struct Comparator {
    virtual bool operator() (T const&, T const&) const = 0;
};

struct IntComparator final : Comparator<int> {
    bool operator() (int const& lha, int const& rha) const override {
        return lha < rha;
    }
};

template <typename T>
void my_swap(T& a, T& b) {
    T temp;
    temp = a;
    a = b;
    b = temp;
}


template<typename T>
void qsort(T* first, size_t number, Comparator<T>& cmp) {
    if (number == 0 || number ==1) {
        //std::cout << number << std::endl;
        return;
    }
    auto curr = (number - 1) / 2;
    auto l = 0;
    auto r = number - 1;
    if (number == 2) { 
        if (cmp(first[l], first[r])) {
            return;
        }
        else {
            my_swap(first[l], first[r]);
            return;
        }
    }

    while (l <= r) {
        //std::cout << l << " " << curr << " " << r << " " << number << " " << first[l] << " " << first[r] << std::endl;
        while (cmp(first[l], first[curr])) l++;
        while (cmp(first[curr], first[r])) r--;
        if (l <= r) {
            my_swap(first[l], first[r]);
            if (l == curr) curr = r;
            if (r == curr) curr = l;
            l++;
            r--;
        }
    }
    
    if (l <= number - 1) {
        qsort((T*)first + (l) * sizeof(char), number - l, cmp);
    }
    if (r > 0) {
        qsort(first, r + 1, cmp);
    }
}

int main()
{
    int* mass = new int[9] { 4, 500, 8, -2, 0, 21, 1 ,3,20};
    int* m = new int[4]{ 1, -1, -3,-5};
    IntComparator cmp;
    //qsort<int>(mass, 7, cmp);
    qsort<int>(mass, 9, cmp);
    for (int i = 0; i < 9; i++)
    {
        cout << mass[i] << " ";
    }
    delete[] mass,m;
}