import matplotlib.pyplot as plt
from matplotlib.ticker import (AutoMinorLocator, MultipleLocator)
import numpy as np

with open("task2.txt", "r") as f:
    x0=[]
    y0=[]
    x1=[]
    y1=[]
    for line in f:
        data=line.split(" ")
        x0.append(float(data[0]))
        y0.append(float(data[1]))
    for i in range(1, 201, 1):
        b = 0
        for j in range(100):
            b += y0[j+100*(i-1)]/100
        y1.append(b)
        x1.append(i)

# Диапазон осей
X_LIM_BOTTOM = 0
Y_LIM_BOTTOM = 0

X_LIM_UP = 200
Y_LIM_UP = 60000

fig, ax = plt.subplots(figsize=(10, 8))

# Диапазоны осей
ax.set_xlim(X_LIM_BOTTOM, X_LIM_UP)
ax.set_ylim(Y_LIM_BOTTOM, Y_LIM_UP)

# Шаг сетки для главных делений
ax.xaxis.set_major_locator(MultipleLocator(50))
ax.yaxis.set_major_locator(MultipleLocator(10000))

# Количество промежутков между главными делениями
ax.xaxis.set_minor_locator(AutoMinorLocator(5))
ax.yaxis.set_minor_locator(AutoMinorLocator(5))

# Сетка для главных и дополнительных делений
ax.grid(which='major', color='#CCCCCC', linestyle='--')
ax.grid(which='minor', color='#CCCCCC', linestyle=':')

# Отображение крестов погрешности
# ax.errorbar(x1, y1, fmt = '.k', ecolor='#666666', capthick=1)

# Подписи осей
plt.xlabel('n')
plt.ylabel('T')

# Название графика
plt.title('Зависимость времени достижения края кристалла от размера дислокаций')


h1 = np.arange(X_LIM_BOTTOM, X_LIM_UP, (X_LIM_UP-X_LIM_BOTTOM)/100)
p1, cov1= np.polyfit(x1, y1, 1, rcond=None, full=False, w=None, cov=True)
# plt.plot(h1, h1*p1[0]+p1[1], color = '#a0a0a0')
plt.plot(x1, y1, 'o', markersize = 3, color = '#000000')


print('k4 =', p1[0], ' b4 =', p1[1])
#print(cov1)
print('σ(k4) =', cov1[0][0]**0.5, ' σ(b4) =',  cov1[1][1]**0.5)

plt.show()
