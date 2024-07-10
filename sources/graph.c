#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

#define MAX_ENTRIES 100

typedef struct {
    int dia;
    int mes;
    int ano;
    int hora;
    int minuto;
    int numPessoas;
} Entry;

typedef struct {
    int hora;
    int minuto;
    int numPessoas;
} DailyData;

typedef struct {
    int dia;
    int mes;
    int numPessoas;
} WeeklyData;

int main() {
    FILE *file;
    FILE *gnuplotPipe;
    char *filename = "dados.txt";
    char *gnuplotFilename = "plot_commands.txt";
    char buffer[256];
    Entry entries[MAX_ENTRIES];
    int count = 0;

    // Criar a pasta ../graphs se não existir
    mkdir("../graphs", 0777);

    // Abrir o arquivo de texto para leitura
    file = fopen(filename, "r");
    if (file == NULL) {
        perror("Erro ao abrir o arquivo");
        return 1;
    }

    // Ler os valores do arquivo de texto
    while (fgets(buffer, sizeof(buffer), file) && count < MAX_ENTRIES) {
        if (sscanf(buffer, "%d %d %d %d %d %d", 
                   &entries[count].dia, 
                   &entries[count].mes, 
                   &entries[count].ano, 
                   &entries[count].hora, 
                   &entries[count].minuto, 
                   &entries[count].numPessoas) == 6) {
            count++;
        }
    }
    fclose(file);

    // Encontrar o último dia registrado
    int lastDay = entries[count - 1].dia;
    int lastMonth = entries[count - 1].mes;
    int lastYear = entries[count - 1].ano;

    // Somar os dados do último dia
    DailyData dailyData[24] = {0}; // 24 horas no dia
    for (int i = 0; i < count; i++) {
        if (entries[i].dia == lastDay && entries[i].mes == lastMonth && entries[i].ano == lastYear) {
            int hour = entries[i].hora;
            dailyData[hour].hora = hour;
            dailyData[hour].minuto = entries[i].minuto;
            dailyData[hour].numPessoas += entries[i].numPessoas;
        }
    }

    // Gerar o script do gnuplot para o gráfico diário
    FILE *gnuplotScript = fopen(gnuplotFilename, "w");
    if (gnuplotScript == NULL) {
        perror("Erro ao criar o arquivo de script do gnuplot");
        return 1;
    }

    fprintf(gnuplotScript, "set terminal png size 1920,1080\n");
    fprintf(gnuplotScript, "set output '../graphs/dia.png'\n");
    fprintf(gnuplotScript, "set title 'Número de Pessoas por Hora - Último Dia'\n");
    fprintf(gnuplotScript, "set xlabel 'Hora'\n");
    fprintf(gnuplotScript, "set ylabel 'Número de Pessoas'\n");
    fprintf(gnuplotScript, "set ytics 25\n");
    fprintf(gnuplotScript, "set style data histograms\n");
    fprintf(gnuplotScript, "set style fill solid 1.0 border -1\n");
    fprintf(gnuplotScript, "set xtics rotate by -45\n");
    fprintf(gnuplotScript, "set grid\n");
    fprintf(gnuplotScript, "set key inside right top vertical Right noreverse enhanced autotitles box linetype -1 linewidth 1.000\n");
    fprintf(gnuplotScript, "plot '-' using 2:xtic(1) title 'Número de Pessoas' linecolor rgb 'purple'\n");

    for (int i = 0; i < 24; i++) {
        if (dailyData[i].numPessoas > 0) {
            fprintf(gnuplotScript, "%02d:%02d %d\n", 
                    dailyData[i].hora, 
                    dailyData[i].minuto, 
                    dailyData[i].numPessoas);
        }
    }
    fprintf(gnuplotScript, "e\n");

    // Somar os dados dos últimos 7 dias
    WeeklyData weeklyData[7] = {0};
    int dayIndex = 0;
    for (int i = count - 1; i >= 0 && dayIndex < 7; i--) {
        int found = 0;
        for (int j = 0; j < dayIndex; j++) {
            if (weeklyData[j].dia == entries[i].dia && weeklyData[j].mes == entries[i].mes) {
                weeklyData[j].numPessoas += entries[i].numPessoas;
                found = 1;
                break;
            }
        }
        if (!found) {
            weeklyData[dayIndex].dia = entries[i].dia;
            weeklyData[dayIndex].mes = entries[i].mes;
            weeklyData[dayIndex].numPessoas = entries[i].numPessoas;
            dayIndex++;
        }
    }

    // Gerar o script do gnuplot para o gráfico semanal
    fprintf(gnuplotScript, "set output '../graphs/semana.png'\n");
    fprintf(gnuplotScript, "set title 'Número de Pessoas por Dia - Últimos 7 Dias'\n");
    fprintf(gnuplotScript, "set xlabel 'Dia'\n");
    fprintf(gnuplotScript, "set ylabel 'Número de Pessoas'\n");
    fprintf(gnuplotScript, "set style data histograms\n");
    fprintf(gnuplotScript, "set style fill solid 1.0 border -1\n");
    fprintf(gnuplotScript, "set xtics rotate by -45\n");
    fprintf(gnuplotScript, "set grid\n");
    fprintf(gnuplotScript, "set key inside right top vertical Right noreverse enhanced autotitles box linetype -1 linewidth 1.000\n");
    fprintf(gnuplotScript, "plot '-' using 2:xtic(1) title 'Número de Pessoas' linecolor rgb 'blue'\n");

    for (int i = dayIndex - 1; i >= 0; i--) {
        fprintf(gnuplotScript, "%02d/%02d %d\n", 
                weeklyData[i].dia, 
                weeklyData[i].mes, 
                weeklyData[i].numPessoas);
    }
    fprintf(gnuplotScript, "e\n");

    fclose(gnuplotScript);

    // Executar o script do gnuplot
    gnuplotPipe = popen("gnuplot plot_commands.txt", "w");
    if (gnuplotPipe == NULL) {
        perror("Erro ao executar o gnuplot");
        return 1;
    }

    pclose(gnuplotPipe);

    printf("Gráficos gerados como '../graphs/dia.png' e '../graphs/semana.png'\n");

    return 0;
}
