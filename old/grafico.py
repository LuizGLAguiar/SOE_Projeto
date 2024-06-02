import numpy as np
import matplotlib.pyplot as plt

Qnt = [0, 100, 200, 300, 400, 500, 600]
Período = ['08:00','09:00','010:00','11:00','12:00','13:00','14:00','15:00','16:00','17:00','18:00']


plt.bar(Período, Qnt, color="red")

plt.xticks(Período)

plt.ylabel('Quantidade de pessoas')

plt.xlabel('Período')

plt.title('Quantidade de pessoas X Período')

plt.show()
