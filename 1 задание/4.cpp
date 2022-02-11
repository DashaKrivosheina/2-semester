#include <iostream>
using namespace std;

int minsum;

int func(int N)
{
    int current;
    int max1 = 0;
    int max2 = 0;
    unsigned int min1 = 4294967295;
    unsigned int min2 = 4294967295;
    int maxsum = 0;
    for (int i = 0 ; i < N ; i++)
    {
        if (N == 2)
        {
            cout << "Enter an integer: ";
            cin >> current;
            maxsum += current;
            minsum += current;
        }
        else
        {
            cout << "Enter an integer: ";
            cin >> current;
            if (current >= max2)
            {
                max1 = max2;
                max2 = current;
            }
            if (current < max2 && current > max1)
            {
                max1 = current;
            }
            if (current <= min1)
            {
                min2 = min1;
                min1 = current;
            }
            if (current > min1 && current < min2)
            {
                min2 = current;
            }
            minsum = min1 + min2;
            maxsum = max1 + max2;
        }
    }
    return maxsum;
}

int main()
{
    int MaxSum, MinSum, n;
    cout << "Enter number of elements ";
    cin >> n;
    if (n == 1)
    {
        cout << "Not enought numbers!";
    }
    else
    {
        MaxSum = func(n);
        MinSum = minsum;
        cout << "The sum of 2 maximal elements: " << MaxSum << endl;
        cout << "The sum of 2 minimal elements: " << MinSum;
    }
}
