#include <stdio.h>
#include <stdlib.h>

#define MAX_ENTRIES 100

typedef struct {
    int dia;
    int mes;
    int ano;
    int hora;
    int minuto;
    int numPessoas;
} Entry;

int main() {
    FILE *file;
    FILE *gnuplotPipe;
    char *filename = "dados.txt";
    char *gnuplotFilename = "plot_commands.txt";
    char buffer[256];
    Entry entries[MAX_ENTRIES];
    int count = 0;

    // Abrir o arquivo de texto para leitura
    file = fopen(filename, "r");
    if (file == NULL) {
        perror("Erro ao abrir o arquivo");
        return 1;
    }

    // Ler os valores do arquivo de texto
    while (fgets(buffer, sizeof(buffer), file) && count < MAX_ENTRIES) {
        // Verificar se a linha contém dados válidos
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

    // Gerar o script do gnuplot
    FILE *gnuplotScript = fopen(gnuplotFilename, "w");
    if (gnuplotScript == NULL) {
        perror("Erro ao criar o arquivo de script do gnuplot");
        return 1;
    }

    fprintf(gnuplotScript, "set terminal png size 1920,1080\n");
    fprintf(gnuplotScript, "set output 'grafico.jpg'\n");
    fprintf(gnuplotScript, "set xlabel 'Hora'\n");
    fprintf(gnuplotScript, "set ylabel 'Número de Pessoas'\n");
    fprintf(gnuplotScript, "set ytics 25\n"); // Ajuste para incrementar de 25 em 25
    fprintf(gnuplotScript, "set style data histograms\n");
    fprintf(gnuplotScript, "set style fill solid 1.0 border -1\n");
    fprintf(gnuplotScript, "set xtics rotate by -45\n");
    fprintf(gnuplotScript, "set key inside right top vertical Right noreverse enhanced autotitles box linetype -1 linewidth 1.000\n");
    fprintf(gnuplotScript, "plot '-' using 2:xtic(1) title 'Número de Pessoas' linecolor rgb 'purple'\n");

    for (int i = 0; i < count; i++) {
        fprintf(gnuplotScript, "%02d:%02d %d\n", 
                entries[i].hora, 
                entries[i].minuto, 
                entries[i].numPessoas);
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

    printf("Gráfico gerado como 'grafico.jpg'\n");

    return 0;
}