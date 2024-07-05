#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <map>
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

    // Ordena os dados por data (do mais recente para o mais antigo)
    std::sort(dados.begin(), dados.end(), [](const Dados& a, const Dados& b) {
        return std::tie(b.ano, b.mes, b.dia) < std::tie(a.ano, a.mes, a.dia);
    });

    // Mapa para acumular as quantidades por dia
    std::map<std::string, double> acumulado_por_dia;

    // Acumula as quantidades por dia
    for (const auto& d : dados) {
        std::ostringstream chave;
        chave << d.dia << "/" << d.mes << "/" << d.ano;
        acumulado_por_dia[chave.str()] += d.quantidade;
    }

    // Vetores para o gráfico de barras da semana
    std::vector<std::string> dias;
    std::vector<double> quantidades_semana;

    // Preenche os vetores com os dados acumulados por dia
    for (const auto& par : acumulado_por_dia) {
        dias.push_back(par.first);
        quantidades_semana.push_back(par.second);
    }

    // Limitar a apenas os últimos 7 dias, se houver mais que 7 dias
    int dias_a_mostrar = std::min(7, static_cast<int>(dias.size()));
    dias.erase(dias.begin(), dias.end() - dias_a_mostrar);
    quantidades_semana.erase(quantidades_semana.begin(), quantidades_semana.end() - dias_a_mostrar);

    // Reverter os vetores para que os dias mais recentes fiquem primeiro
    std::reverse(dias.begin(), dias.end());
    std::reverse(quantidades_semana.begin(), quantidades_semana.end());

    // Criação do gráfico de barras da semana
    plt::figure();

    // Configurações do gráfico da semana
    std::ostringstream titulo_semana;
    titulo_semana << "Quantidade de Pessoas Dos Últimos 7 dias";
    plt::title(titulo_semana.str());
    plt::xlabel("Dia");
    plt::ylabel("Quantidade de Pessoas");

    // Ajuste da escala do eixo y para o gráfico da semana
    int max_quantidade_semana = *std::max_element(quantidades_semana.begin(), quantidades_semana.end());
    int ylim_semana = ((max_quantidade_semana / 100) + 1) * 100; // Limite do eixo y para múltiplos de 100
    plt::ylim(0, ylim_semana);
    std::vector<int> yticks_semana;
    for (int i = 0; i <= ylim_semana; i += 100) {
        yticks_semana.push_back(i);
    }

    // Converte o vetor de dias para um vetor de índices para o eixo x
    std::vector<double> indices_dias(dias.size());
    std::iota(indices_dias.begin(), indices_dias.end(), -1);

    // Desenha o gráfico de barras da semana
    plt::bar(indices_dias, quantidades_semana);

    // Define os rótulos do eixo x como os dias formatados
    plt::xticks(indices_dias, dias);
    plt::yticks(yticks_semana);

    // Salvar o gráfico da semana em um arquivo
    std::string outputFileName_semana = "../graphs/semana.jpg";
    plt::save(outputFileName_semana);

    // Mapa para acumular as quantidades por hora do dia mais recente
    std::map<int, double> acumulado_por_hora;

    // Filtrar dados apenas do dia mais recente
    if (!dados.empty()) {
        int dia_recente = dados.front().dia;
        int mes_recente = dados.front().mes;
        int ano_recente = dados.front().ano;

        for (const auto& d : dados) {
            if (d.dia == dia_recente && d.mes == mes_recente && d.ano == ano_recente) {
                acumulado_por_hora[d.hora] += d.quantidade;
            }
        }
    }

    // Vetores para o gráfico de barras do dia
    std::vector<double> horas;
    std::vector<double> quantidades_dia;

    // Preenche os vetores com os dados acumulados por hora
    for (const auto& par : acumulado_por_hora) {
        horas.push_back(par.first);
        quantidades_dia.push_back(par.second);
    }

    // Criação do gráfico de barras do dia
    plt::figure();

    // Configurações do gráfico do dia
    std::ostringstream titulo_dia;
    titulo_dia << "Quantidade de Pessoas por Hora - Dia " << dados.front().dia << "/" << dados.front().mes << "/" << dados.front().ano;
    plt::title(titulo_dia.str());
    plt::xlabel("Hora do Dia");
    plt::ylabel("Quantidade de Pessoas");

    // Ajuste da escala do eixo y para o gráfico do dia
    int max_quantidade_dia = *std::max_element(quantidades_dia.begin(), quantidades_dia.end());
    int ylim_dia = ((max_quantidade_dia / 50) + 1) * 50; // Limite do eixo y para múltiplos de 50
    plt::ylim(0, ylim_dia);
    std::vector<int> yticks_dia;
    for (int i = 0; i <= ylim_dia; i += 50) {
        yticks_dia.push_back(i);
    }

    // Ajuste da escala do eixo x para mostrar de hora em hora
    std::vector<int> xticks_dia;
    for (int i = 0; i <= 23; ++i) {
        xticks_dia.push_back(i);
    }

    // Ativa a grade e coloca as barras sobre a grade
    plt::grid(true);

    // Desenha o gráfico de barras do dia
    plt::bar(horas, quantidades_dia);

    // Define os ticks do eixo x como as horas
    plt::xticks(xticks_dia);
    plt::yticks(yticks_dia);

    // Salvar o gráfico do dia em um arquivo
    std::string outputFileName_dia = "../graphs/dia.jpg";
    plt::save(outputFileName_dia);

    return 0;
}
