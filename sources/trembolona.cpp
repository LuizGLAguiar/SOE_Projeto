#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include "matplotlibcpp.h"

namespace plt = matplotlibcpp;

struct Dados {
    int dia;
    int mes;
    int ano;
    int hora;
    int minuto;
    int quantidade;
};

int main() {
    // Vetores para armazenar os dados do arquivo
    std::vector<Dados> dados;

    // Abre o arquivo de texto
    std::ifstream arquivo("dados.txt");

    // Verifica se o arquivo foi aberto corretamente
    if (!arquivo) {
        std::cerr << "Erro ao abrir o arquivo dados.txt" << std::endl;
        return 1;
    }

    // Lê os dados do arquivo
    Dados dado;
    while (arquivo >> dado.dia >> dado.mes >> dado.ano >> dado.hora >> dado.minuto >> dado.quantidade) {
        dados.push_back(dado);
    }

    // Fecha o arquivo após a leitura
    arquivo.close();

    // Vetores para o gráfico de barras
    std::vector<double> horas;
    std::vector<double> quantidades;

    // Preenche os vetores com os dados lidos do arquivo
    for (const auto& d : dados) {
        horas.push_back(d.hora);
        quantidades.push_back(d.quantidade);
    }

    // Obter a data do primeiro registro
    int dia = dados[0].dia;
    int mes = dados[0].mes;
    int ano = dados[0].ano;

    // Criação do gráfico de barras
    plt::figure();

    // Configurações do gráfico
    std::ostringstream titulo;
    titulo << "Quantidade de Pessoas por Hora - Dia " << dia << "/" << mes << "/" << ano;
    plt::title(titulo.str());
    plt::xlabel("Hora do Dia");
    plt::ylabel("Quantidade de Pessoas");

    // Ajuste da escala do eixo y
    int max_quantidade = *max_element(quantidades.begin(), quantidades.end());
    int ylim = ((max_quantidade / 50) + 1) * 50; // Limite do eixo y para múltiplos de 50
    plt::ylim(0, ylim);
    std::vector<int> yticks;
    for (int i = 0; i <= ylim; i += 50) {
        yticks.push_back(i);
    }

    // Ativa a grade
    plt::grid(true);

    // Desenha o gráfico de barras
    plt::bar(horas, quantidades);

    plt::yticks(yticks);

    // Salvar o gráfico em um arquivo
    std::string outputFileName = "graphs.jpg";
    plt::save(outputFileName);

    return 0;
}
