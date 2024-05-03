import matplotlib.pyplot as plt

periodo = ['8:00','9:00','10:00','11:00','12:00']
qnt = [100,200,300,400,500]

plt.bar(periodo, qnt, color="red")

plt.xticks(periodo)
plt.ylabel('Quantidade de pessoas')
plt.xlabel('Horários')
plt.title('Quantidade de pessoas X Horário na UnB')
plt.show()
