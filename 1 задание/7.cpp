#include <iostream>
using namespace std;

float max(float a, float b)
{
    if (a > b)
    {
        return a;
    }
    else
    {
        return b;
    }
}

void func(int n)
{
    int I = 0;
    int II = 0;
    int III = 0;
    int IV = 0;
    for (int i = 0; i < n; i++)
    {
        cout << "Enter coordanates: ";
        float x, y;
        cin >> x >> y;
        if (x > 0 && y > 0)
        {
            I++;
        }
        else if (x < 0 && y > 0)
        {
            II++;
        }
        else if (x < 0 && y < 0)
        {
            III++;
        }
        else if (x > 0 && y < 0)
        {
            IV++;
        }
    }
    int C;
    C = max(max(I, II), max(III, IV));
    if (I != II && II != III && III != IV)
    {
        if (I == C)
        {
            cout << "Most of dots are in the I quarter" << endl;
        }
        else if (II == C)
        {
            cout << "Most of dots are in the II quarter" << endl;
        }
        else if (III == C)
        {
            cout << "Most of dots are in the III quarter" << endl;
        }
        else if (IV == C)
        {
            cout << "Most of dots are in the IV quarter" << endl;
        }
    }
    else
    {
        cout << "Two or more quarters have equal amount of dots" << endl;
    }
    cout << "Amount of dots: " << C;
}

int main()
{
    int N;
    cout << "Enter number of dots: ";
    cin >> N;
    func(N);
}
