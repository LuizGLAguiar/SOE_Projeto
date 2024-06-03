import matplotlib.pyplot as plt
import datetime
import os

def ler_dados_arquivo(caminho_arquivo):
    dados = []
    try:
        with open(caminho_arquivo, 'r') as arquivo:
            conteudo = arquivo.read().strip()
            partes = conteudo.split()
            for i in range(0, len(partes), 6):
                dia, mes, ano, hora, minuto, media = map(int, partes[i:i+6])
                dados.append((dia, mes, ano, hora, minuto, media))
    except FileNotFoundError:
        print(f"Arquivo {caminho_arquivo} não encontrado.")
    except Exception as e:
        print(f"Ocorreu um erro ao ler o arquivo: {e}")
    return dados

def agrupar_dados_por_dia(dados):
    dados_por_dia = {}
    for dia, mes, ano, hora, minuto, media in dados:
        data = f'{dia:02d}/{mes:02d}/{ano}'
        if data not in dados_por_dia:
            dados_por_dia[data] = []
        dados_por_dia[data].append((hora, media))
    return dados_por_dia

def agrupar_dados_por_semana(dados):
    dias_da_semana = ['Domingo', 'Segunda', 'Terça', 'Quarta', 'Quinta', 'Sexta', 'Sábado']
    dados_por_semana = {dia: 0 for dia in dias_da_semana}
    for dia, mes, ano, hora, minuto, media in dados:
        dia_semana = datetime.date(ano, mes, dia).weekday()
        dados_por_semana[dias_da_semana[dia_semana]] += media
    return dados_por_semana

def gerar_grafico_dia(dados_por_dia, caminho_saida):
    periodos = ['8:00', '9:00', '10:00', '11:00', '12:00', '13:00', '14:00', '15:00', '16:00', '17:00', '18:00']
    for data, registros in dados_por_dia.items():
        qnt = [0] * len(periodos)
        for hora, media in registros:
            hora_formatada = f'{hora}:00'
            if hora_formatada in periodos:
                index = periodos.index(hora_formatada)
                qnt[index] = media
        
        # Cria o diretório de saída se ele não existir
        os.makedirs(caminho_saida, exist_ok=True)
        
        plt.figure(figsize=(10, 5))
        plt.bar(periodos, qnt, color="red")
        plt.xticks(periodos)
        plt.ylabel('Quantidade de pessoas')
        plt.xlabel('Horários')
        plt.title(f'Quantidade de pessoas X Horários - {data}')
        plt.savefig(os.path.join(caminho_saida, 'dia.jpg'))
        plt.close()

def gerar_grafico_semana(dados_por_semana, caminho_saida):
    dias_da_semana = ['Domingo', 'Segunda', 'Terça', 'Quarta', 'Quinta', 'Sexta', 'Sábado']
    qnt = [dados_por_semana[dia] for dia in dias_da_semana]
    
    plt.figure(figsize=(10, 5))
    plt.bar(dias_da_semana, qnt, color='red')
    plt.xticks(dias_da_semana)
    plt.ylabel('Quantidade de pessoas')
    plt.xlabel('Dias da Semana')
    plt.title('Quantidade de pessoas X Semana')
    plt.savefig(f'{caminho_saida}/semana.jpg')
    plt.close()

def main(caminho_arquivo, caminho_saida):
    dados = ler_dados_arquivo(caminho_arquivo)
    if not dados:
        print("Nenhum dado válido foi encontrado.")
        return
    
    dados_por_dia = agrupar_dados_por_dia(dados)
    dados_por_semana = agrupar_dados_por_semana(dados)
    
    gerar_grafico_dia(dados_por_dia, caminho_saida)
    gerar_grafico_semana(dados_por_semana, caminho_saida)
    print("Gráficos gerados com sucesso!")

# Exemplo de uso
caminho_arquivo = 'dados.txt'  # Arquivo de dados
caminho_saida = '../graphs'  # Diretório de saída para os gráficos
main(caminho_arquivo, caminho_saida)
