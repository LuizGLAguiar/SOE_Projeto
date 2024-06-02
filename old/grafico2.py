import matplotlib.pyplot as plt

# Dados para o eixo x
x = [1, 2, 3, 4, 5]

# Dados para o eixo y
y = [2, 3, 5, 7, 11]

# Criar o gráfico de linha
plt.plot(x, y)

# Adicionar título e rótulos aos eixos
plt.title('Gráfico Simples')
plt.xlabel('Eixo X')
plt.ylabel('Eixo Y')

# Exibir o gráfico
plt.show()
