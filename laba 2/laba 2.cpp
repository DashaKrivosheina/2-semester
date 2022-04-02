#include <iostream>
#include <cmath>
#include <numbers>
#include <fstream>
#include <algorithm>
#include <iomanip>

using namespace std;

float const f_pi = 3.14159265359f;
double const d_pi = 3.14159265359;
float const f_e = 2.718281828459f;
double const d_e = 2.718281828459;

float maxwell_f(float v,float T){//распределение максвелла
    return exp(- v * v / T) / sqrt(T * f_pi);
}
float dist_f(float psi[], float pdf[], float v1, float v2, float T, float size) {//заполняем psi и pdf
    float dv = abs(v2 - v1) / size;
    for (int i = 0; i < size; i++) {
        psi[i] = fabs(v1+dv*i);
        pdf[i] = maxwell_f(psi[i],T);
    }
    return dv;
}

float mean_f(float const psi[], float const pdf[], float const dv, unsigned size) {//наивная реализация
    float sum = 0.f;
    for (unsigned idx = 0; idx != size; ++idx)
        sum += psi[idx] * pdf[idx];
    return dv * sum;
}


float mean_rec_f(float const psi[], float const pdf[], float const dv, unsigned size) {//рекурсивная функция суммирования.psi - массив значений величины, pdf - массив значений функции распределения, dv - интервал между соседнми аргументами, size - количество значений
    if (size == 1) {
        return dv * psi[0] * pdf[0] ;
    }
    else {
        return (mean_rec_f(psi, pdf, dv, size / 2) + mean_rec_f(psi + size / 2, pdf + size / 2, dv, size - size / 2));
    }
}

float mean_2_f(float const psi[], float const pdf[], float const dv, unsigned size) {
    float* sum = new float[size];
    for (int i = 0; i < size; i++) {
        sum[i] = psi[i] * pdf[i];
    }
    unsigned d = 2;
    while (size / d > 0) {
        for (int j = 0; j < size / d; j++) {
            if (j * d + d / 2 < size) {
                sum[j * d] += sum[j * d + d / 2];
            }
        }
        d *= 2;
    }
    if (d / 2 < size) {
        sum[0] += sum[d / 2];
    }
    return dv * sum[0];
    delete[] sum;
}

float kahan(float const psi[], float const pdf[], float const dv, unsigned size) {
    float sum = 0.f;
    float c = 0.f;
    for (int i = 0; i < size; i++) {
        float y = psi[i] * pdf[i] - c;
        float t = sum + y;
        c = (t - sum) - y;
        sum = t;
    }
    return sum * dv;
}

float fma_f(float const psi[], float const pdf[], float const dv, unsigned size) {
    float sum = 0.f;
    for (int i = 0; i< size; i++) {
        sum = fmaf(psi[i], pdf[i], sum);
    }
    return dv * sum;
}
//

double maxwell_d(double v, double T) {//распределение максвелла
    return pow(f_e, -v * v / T) / sqrt(T * f_pi);
}
double dist_d(double psi[], double pdf[], double v1, double v2, double T, double size) {//заполняем psi и pdf
    double dv = abs(v2 - v1) / size;
    for (int i = 0; i < size;i++) {
        psi[i] = abs(v1+dv*i);
        pdf[i] = maxwell_d(psi[i], T);
    }
    return dv;
}

double mean_d(double const psi[], double const pdf[], double const dv, unsigned size) {//наивная реализация
    double sum = 0;
    for (unsigned idx = 0; idx != size; ++idx)
        sum += psi[idx] * pdf[idx];
    return dv * sum;
}


double mean_rec_d(double const psi[], double const pdf[], double const dv, unsigned size) {//рекурсивная функция суммирования.psi - массив значений величины, pdf - массив значений функции распределения, dv - интервал между соседнми аргументами, size - количество значений
    if (size == 1) {
        return psi[0] * pdf[0] * dv;
    }
    else {
        return mean_rec_d(psi, pdf, dv, size / 2) + mean_rec_d(psi + size / 2, pdf + size / 2, dv, size - size / 2);
    }
}

double mean_2_d(double const psi[], double const pdf[], double const dv, unsigned size) {
    double* sum = new double[size];
    for (int i = 0; i < size; i++) {
        sum[i] = psi[i] * pdf[i];
    }
    unsigned d = 2;
    while (size / d > 0) {
        for (int j = 0; j < size / d; j++) {
            if (j * d + d / 2 < size) {
                sum[j * d] += sum[j * d + d / 2];
            }
        }
        d *= 2;
    }
    if (d / 2 < size) {
        sum[0] += sum[d / 2];
    }
    return dv * sum[0];
    delete[] sum;
}

double kahan_d(double const psi[], double const pdf[], double const dv, unsigned size) {
    double sum = 0;
    double c = 0;
    for (int i = 0; i < size; i++) {
        double y = psi[i] * pdf[i] - c;
        double t = sum + y;
        c = (t - sum) - y;
        sum = t;
    }
    return sum * dv;
}

double fma_d(double const psi[], double const pdf[], double const dv, unsigned size) {
    double sum = 0;
    for (int i = 0; i, size; i++) {
        sum = fma(psi[i], pdf[i], sum);
    }
    return dv * sum;
}

void print(float* begin, float* end) {
    while (begin != end)
        cout << *(begin++) << " ";
    cout << "\n";
}

int main()
{
    float v1 = -200, v2 = 200;
    float T = 1;
    double v11 = -200, v22 = 200;
    double T1 = 1;
    const char* header[6] = {"Naive", "Recursive", "Split", "Kahan", "FMA", "Double"};
    cout << left << setw(6) << "N";
    for (int i = 0; i < 6; i ++)
        cout << "  " << setw(11) << header[i];
    cout << "\n------------------------------------------------------------------------------------------\n";
    for (int size = 500; size < 100000; size *= 2) {
        cout.precision(9);
        float* psi = new float[size];
        float* pdf = new float[size];
        double* psi_d = new double[size];
        double* pdf_d = new double[size];
        float dv = dist_f(psi, pdf, v1, v2, T, size);
        double dv_d = dist_d(psi_d, pdf_d, v11, v22, T1, size);
        //print(psi, psi + size);
        //print(pdf, pdf + size);
        cout << setw(6) << size << "  ";
        cout << mean_f(psi, pdf, dv, size) << "  ";
        cout << mean_rec_f(psi, pdf, dv, size) << "  ";
        cout << mean_2_f(psi, pdf, dv, size) << "  ";
        cout << kahan(psi, pdf, dv, size) << "  ";
        cout << fma_f(psi, pdf, dv, size) << "  ";
        cout << mean_d(psi_d, pdf_d, dv_d, size) << "\n";
        delete[] psi;
        delete[] pdf;
        delete[] psi_d;
        delete[] pdf_d;
    }
    /*
    double v11 = -20000, v22 = 20000;
    double T1 = 1;

    for (int size = 10000; size < 10000; size *= 2) {
        double* psi = new double[size];
        double* pdf = new double[size];
        double dv = dist_d(psi, pdf, v11, v22, T1, size);
        cout << size << "\n";
        cout << mean_d(psi, pdf, dv, size) << "\n";
        cout << mean_rec_d(psi, pdf, dv, size) << "\n";
        delete[] psi;
        delete[] pdf;
    }
    */
}
