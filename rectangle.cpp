#include <iostream>
#include <string>
#include<sstream>
#include<vector>
using namespace std;

struct Point{
    unsigned long long const x , y;
    Point(unsigned long long x, unsigned long long y) :
        x(x), y(y) { }
        Point minx(Point const & rha) const {
        return Point(rha.x < x ? rha.x : x, y);
    }
        Point miny(Point const & rha) const {
        return Point(x, rha.y < y ? rha.y : y);
    }
        Point maxx(Point const & rha) const {
        return Point(rha.x > x ? rha.x : x, y);
    }
        Point maxy(Point const & rha) const {
        return Point(x, rha.y > y ? rha.y : y);
    }
        void print() const {
        std :: cout << '(' << x << ', ' << y << ') ';
    }
};

struct Rectangle {
    unsigned long long const x, y;
    Rectangle() :x(0), y(0) {}
    Rectangle(unsigned long long _x, unsigned long long _y ) : x(_x), y(_y) {}
    Rectangle(Point const & a) : x(a.x), y(a.y) {}

    Rectangle operator+(Rectangle const& rha) const {
        unsigned long long maxx = 0;
        unsigned long long maxy = 0;
        if (rha.x > x) {
            maxx = rha.x;
        }
        else {
            maxx = x;
        }
        if (rha.y > y) {
            maxy = rha.y;
        }
        else {
            maxy = y;
        }
        Rectangle r(maxx, maxy);
        return r;
    }
    Rectangle operator*(Rectangle const& rha) const {
        unsigned long long minx = 0;
        unsigned long long miny = 0;
        if (rha.x < x) {
            minx = rha.x;
        }
        else minx = x;
        if (rha.y < y) {
            miny = rha.y;
        }
        else miny = y;
        Rectangle r(minx, miny);
        return r;
    }
    void print() const {
        std::cout << x << y;
    }
};

int main()
{
    string expression;
    getline(cin, expression);
    int l = expression.size();
    int count = 0;
    char m[20]={0};
    vector <int> d(l);
    string x = "0";
    for (int i = 0; i < l; i++) {
        if (expression[i] == '(') {
            i++;
            while (expression[i] != ',') {
                x += expression[i];
                i++;
            }
            d[count] = stoi(x);
            x = "0";
            count++;
            i++;
            while (expression[i] != ')') {
                x += expression[i];
                i++;
            }
            d[count] = stoi(x);
            x = "0";
            count++;
            i++;
            if (expression[i] == '+') {
                m[count - 1] = '+';
            }
            else if (expression[i] == '*') {
                m[count - 1] = '*';
            }
            else {
                m[count - 1] = '0';
            }
        }
    }
    int h = l;
    for (int k = 0; k < h; k++) {
        if (m[k] == '*') {
            Rectangle t1(d[k - 1], d[k]);
            Rectangle t2(d[k + 1], d[k + 2]);
            Rectangle t3 = t1.operator*(t2);
            d[k + 1] = t3.x;
            d[k + 2] = t3.y;
            d.erase(d.begin() + k);
            d.erase(d.begin() + k - 1);
            h = h - 2;
            for (int g = 0; g < h; g++) {
                m[g] = m[g + 2];
            }
            for (int g = h+2; g >h ; g--) {
                m[g] = '0';
            }
        }
    }
    if (h > 2) {
        for (int k = 0; k < h; k++) {
            if (m[k] == '+') {
                Rectangle t1(d[k - 1], d[k]);
                Rectangle t2(d[k + 1], d[k + 2]);
                Rectangle t3 = t1.operator+(t2);
                d[k + 1] = t3.x;
                d[k + 2] = t3.y;
                d.erase(d.begin() + k);
                d.erase(d.begin() + k - 1);
                h = h - 2;
                for (int g = 0; g < h; g++) {
                    m[g] = m[g + 2];
                }
                for (int g = h+2; g > h; g--) {
                    m[g] = '0';
                }
            }
        }
    }
    cout << '(' << d[0] << ',' << d[1] << ')';
}
