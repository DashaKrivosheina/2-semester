#include <iostream>
#include<cmath>
#include<fstream>
#include <cstdlib>
#include <string>
#include <limits>
#include <iomanip>


using namespace std;

float const f_pi = 3.14159265359f;
double const d_pi = 3.14159265359;
float const f_e = 2.718281828459f;
double const d_e = 2.718281828459;


//**********************float************
float maxwell_f(float v, float T)
{
    return powf(f_e, -v * v / T) / sqrt(T * f_pi);
}

float fill_f(float v[], float f[], float T, float v1, float v2, unsigned long n) //заполнение массивов в заданном диапазоне, возвращает dv
{
    float dv = (v2 - v1) / n;
    for (unsigned long i = 0; i < n; i++)
    {
        v[i] = abs(v1 + dv * i);
        f[i] = maxwell_f(v[i], T);
    }
    return dv;
}

float mean_f(float const v[], float const f[], float const dv, unsigned long n) //базовая функция вычисления среднего
{
    float sum = 0.f;
    for (unsigned long i = 0; i < n; i++)
        sum += v[i] * f[i];
    return sum * dv;
}

float split_sum_f(float x[], unsigned long n) //разделение массива пополам и вычисление сумм в каждой половине
{
    float sum;
    if (n > 1)
    {
        sum = split_sum_f(x, n / 2);
        for (unsigned long i = n / 2; i < n; i++)
            x[i - n / 2] = x[i];
        sum += split_sum_f(x, n - n / 2);
    }
    else sum = x[0];

    return sum;
}

float mean_di_f(float const v[], float const f[], float const dv, unsigned long n) //базовая функция вычисления среднего через рекурсивную дихотомию
{
    float* x = (float*)malloc(sizeof(float) * n);
    for (unsigned long i = 0; i < n; i++)
        x[i] = v[i] * f[i];
    return split_sum_f(x, n) * dv;
    free(x);
}

float mean2_f(float const v[], float const f[], float const dv, unsigned long n) //функция вычисления среднего с удвоением шага
{
    float* x = (float*)malloc(sizeof(float) * n);
    for (unsigned long i = 0; i < n; i++)
        x[i] = v[i] * f[i];
    unsigned long k = 2;
    while (n / k > 0)
    {
        for (unsigned long i = 0; i < n / k; i++)
            if (i * k + k / 2 < n)
                x[i * k] += x[i * k + k / 2];
        k *= 2;
    }
    if (k / 2 < n)
        x[0] += x[k / 2];
    return x[0] * dv;
    free(x);
}

float mean_kahan_f(float const v[], float const f[], float const dv, unsigned long n) //функция вычисления среднего  (Кэхэн)
{
    float sum = 0.f;
    float c = 0.f;
    for (unsigned long i = 0; i < n; i++)
    {
        float y = v[i] * f[i] - c;
        float t = sum + y;
        c = (t - sum) - y;
        sum = t;
    }

    return sum * dv;
}

float mean_fma_f(float const v[], float const f[], float const dv, unsigned long n) //функция вычисления среднего  (fma)
{
    float sum = 0.f;
    for (unsigned long i = 0; i < n; i++)
        sum = fmaf(v[i], f[i], sum);
    return sum * dv;
}

//****************double*******************
double maxwell_d(double v, double T)
{
    return pow(d_e, -v * v / T) / sqrt(T * d_pi);
}

double fill_d(double v[], double f[], double T, double v1, double v2, unsigned long n) //заполнение массивов в заданном диапазоне, возвращает dv
{
    double dv = (v2 - v1) / n;
    for (unsigned long i = 0; i < n; i++)
    {
        v[i] = abs(v1 + dv * i);
        f[i] = maxwell_d(v[i], T);
    }
    return dv;
}

double mean_d(double const v[], double const f[], double const dv, unsigned long n) //базовая функция вычисления среднего
{
    double sum = 0.0;
    for (unsigned long i = 0; i < n; i++)
        sum += v[i] * f[i];
    return sum * dv;
}

void mean_all(float T, float v1, float v2, unsigned long const n, ofstream& fout)
{
    float* v = (float*)malloc(sizeof(float) * n);
    float* f = (float*)malloc(sizeof(float) * n);
    float dv = fill_f(v, f, T, v1, v2, n);


    double* v_d = (double*)malloc(sizeof(double) * n);
    double* f_d = (double*)malloc(sizeof(double) * n);
    double dv_d = fill_d(v_d, f_d, (double)T, (double)v1, (double)v2, n);
    cout
        << std::setprecision(std::numeric_limits<float>::digits10 + 1)
        << n << "\t"
        << mean_f(v, f, dv, n) << "\t"
        << mean_di_f(v, f, dv, n) << "\t"
        << mean2_f(v, f, dv, n) << "\t"
        << mean_kahan_f(v, f, dv, n) << "\t"
        << mean_fma_f(v, f, dv, n) << "\t"
        << mean_d(v_d, f_d, dv_d, n) << "\t"
        << sqrt(T / f_pi) << endl;
    fout
        << std::setprecision(std::numeric_limits<float>::digits10 + 1)
        << n << "\t"
        << mean_f(v, f, dv, n) << "\t"
        << mean_di_f(v, f, dv, n) << "\t"
        << mean2_f(v, f, dv, n) << "\t"
        << mean_kahan_f(v, f, dv, n) << "\t"
        << mean_fma_f(v, f, dv, n) << "\t"
        << mean_d(v_d, f_d, dv_d, n) << "\t"
        << sqrt(T / f_pi) << endl;
    free(v);
    free(f);
    free(v_d);
    free(f_d);
}


int main()
{
    cout
        << "N" << "\t"
        << "Simple mean" << "\t"
        << "Dichotomy" << "\t"
        << "Double step" << "\t"
        << "Kahan sum" << "\t"
        << "FMA function" << "\t"
        << "Simple (double)" << "\t"
        << "sqrt(T/pi)" << endl;

    ofstream fout;
    fout.open("res1.txt");
    cout << "\t \t \t T = 0.3; v = [-10, 10]" << endl;
    fout << "\t \t \t T = 0.3; v = [-10, 10]" << endl;

    fout
        << "N" << "\t"
        << "Simple mean" << "\t"
        << "Dichotomy" << "\t"
        << "Double step" << "\t"
        << "Kahan sum" << "\t"
        << "FMA function" << "\t"
        << "Simple (double)" << "\t"
        << "sqrt(T/pi)" << endl;
    for (unsigned long n = 1; n < 11; n++)
        mean_all(0.3f, -10.f, 10.f, n * 10000, fout);
    fout.close();

    fout.open("res2.txt");
    cout << "\t \t \t T = 1; v = [-10, 10]" << endl;
    fout << "\t \t \t T = 1; v = [-10, 10]" << endl;
    fout
        << "N" << "\t"
        << "Simple mean" << "\t"
        << "Dichotomy" << "\t"
        << "Double step" << "\t"
        << "Kahan sum" << "\t"
        << "FMA function" << "\t"
        << "Simple (double)" << "\t"
        << "sqrt(T/pi)" << endl;
    for (unsigned long n = 1; n < 11; n++)
        mean_all(1.f, -10.f, 10.f, n * 10000, fout);
    fout.close();

    fout.open("res3.txt");
    cout << "\t \t \t T = 3; v = [-50, 50]" << endl;
    fout << "\t \t \t T = 3; v = [-50, 50]" << endl;
    fout
        << "N" << "\t"
        << "Simple mean" << "\t"
        << "Dichotomy" << "\t"
        << "Double step" << "\t"
        << "Kahan sum" << "\t"
        << "FMA function" << "\t"
        << "Simple (double)" << "\t"
        << "sqrt(T/pi)" << endl;
    for (unsigned long n = 1; n < 11; n++)
        mean_all(3.f, -50.f, 50.f, n * 10000, fout);
    fout.close();

    return 0;
}