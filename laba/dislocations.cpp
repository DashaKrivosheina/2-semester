#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
using namespace std;

//генерация рандомных чисел
int random(int k) {
    int f = (rand() % k);
    return f;
}

int func() {
    srand(static_cast<unsigned int>(time(0)));
    ofstream outf("task2.txt", ios::app);
    const int n = 400;
    const int d = 200;
    int A[n][n];
    int D[d][d];
    int step = -1;
    for (int j = 1; j < d + 1; ++j) {//количество дислокаций
        for (int k = 0; k < 100; ++k) { //количество повторений для каждого значения дислокаций
            for (int i = 0; i < n; ++i) {
                for (int l = 0; l < n; ++l) {
                    A[i][l] = 1;
                }
            }
            step = -1;
            int t = 0;
            while (t < j) {
                int x = random(n);
                int y = random(n);
                if (A[x][y] == 1) {
                    A[x][y] = 0;
                    D[t][0] = x;
                    D[t][1] = y;
                    ++t;
                }
            }
            int motion = t;
            while (motion != 0) {
                for (int f = 0; f < t; ++f) {// проверка на стоянку
                    if (A[D[f][0]][D[f][1]] != 2 && ((D[f][0] == 0) || (D[f][0] == n - 1) || (D[f][1] == 0) || (D[f][1] == n - 1))) {
                        A[D[f][0]][D[f][1]] = 2; // дислокация больше не передвигается
                        motion--;
                    }
                }
                for (int a = 0; a < t; ++a) {

                    if (A[D[a][0]][D[a][1]] == 0) {
                        if (A[D[a][0] + 1][D[a][1]] != 1 || A[D[a][0] - 1][D[a][1]] != 1 || A[D[a][0]][D[a][1] + 1] != 1 || A[D[a][0]][D[a][1] - 1] != 1) {
                            A[D[a][0]][D[a][1]] = 2;
                            motion--;
                        }
                        else {
                            int v = random(4);
                            if (v == 0) {
                                D[a][0]++;
                                A[D[a][0]][D[a][1]] = 0;
                                A[D[a][0] - 1][D[a][1]] = 1;
                            }
                            if (v == 1) {
                                D[a][0]--;
                                A[D[a][0]][D[a][1]] = 0;
                                A[D[a][0] + 1][D[a][1]] = 1;
                            }
                            if (v == 2) {
                                D[a][1]++;
                                A[D[a][0]][D[a][1]] = 0;
                                A[D[a][0]][D[a][1] - 1] = 1;
                            }
                            if (v == 3) {
                                D[a][1]--;
                                A[D[a][0]][D[a][1]] = 0;
                                A[D[a][0]][D[a][1] + 1] = 1;
                            }
                        }
                    }

                }
                step++;  
            }
            outf << j << " " << step << "\n";
        }    
    } 
    return step;
}

int main()
{
    func();
}