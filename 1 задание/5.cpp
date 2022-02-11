#include <iostream>
using namespace std;

void func(float a1, float b1, float c1, float a2, float b2, float c2)
{
    if ( a2 != 0)
    {   
        if (a1 / a2 == b1 / b2)
        {
            if (c1 == a1 / a2 * c2)
            {
                cout << "Lines coincide";
            }
            else
            {
                cout << "No";
            }
        }
        else
        {
            float x, y;
            x = (c2 * b1 / b2 - c1) / (a1 - b1 * a2 / b2);
            y = -c2 / b2 - a2 / b2 * x;
            cout << "Coordinates of intersection point: ( " << x << " , " << y << " )";
        }
    }
    else
    {
        float y = -c2 / b2;   
        if (a1 == 0)    
        {    
            if (c1 / b1 == c2 / b2)
            {    
                cout << "Lines coincide";
            }
            else
            {
                cout << "No";
            }
        }
        else
        {    
            float x = (b1 / b2 * c2 - c1) / a1;
            cout << "Coordinates of intersection point: ( " << x << " , " << y << " )";
        }
    }
}

int main()
{
    float a1, b1, c1, a2, b2, c2;
    cout << "Enter parameters or 1 line: ";
    cin >> a1 >> b1 >> c1;
    cout << "Enter parameters or 2 line: ";
    cin >> a2 >> b2 >> c2;
    if (b2 == 0)
    {
        cout << "From problem statement b2 is not 0!";
    }
    func(a1, b1, c1, a2, b2, c2);
}
