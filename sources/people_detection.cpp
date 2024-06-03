// https://lindevs.com/yolov4-object-detection-using-opencv

#include <iostream>
#include <cmath>
#include <ctime>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h> 
#include <fstream>
#include <stdio.h>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace dnn;

int main(int argc, char *argv[])
{
	if(argc<2)
	{
		std::cout << "Indique a imagem a ser analisada.\n";
		return -1;
	}

	int fd = open("/home/luiz/Desktop/SOE_Projeto/sources/dados.txt", O_WRONLY | O_APPEND | O_CREAT, S_IRUSR | S_IWUSR);
	if(fd == -1)
	{
		printf("Erro na abertura do arquivo.\n");
		exit(-1);
	}

	std::vector<std::string> classes;
	std::ifstream file("/home/luiz/Desktop/SOE_Projeto/sources/files/coco.names");
	std::string line;
	while (std::getline(file, line)) {
		classes.push_back(line);
	}

	Net net = readNetFromDarknet("/home/luiz/Desktop/SOE_Projeto/sources/files/yolov4.cfg", "/home/luiz/Desktop/SOE_Projeto/sources/files/yolov4.weights");

	DetectionModel model = DetectionModel(net);
	model.setInputParams(1 / 255.0, Size(416, 416), Scalar(), true);

	std::vector<int> classIds;
	std::vector<float> scores;
	std::vector<Rect> boxes;

	float media = 0;

	// Contagem de pessoas nas fotos
	for(int i = 1; i < argc; i++)
	{
		Mat img = imread(argv[i]);

		model.detect(img, classIds, scores, boxes, 0.6, 0.4);

		for(int i = 0; i < classIds.size(); i++) {
			rectangle(img, boxes[i], Scalar(0, 255, 0), 2);

			char text[100];
			snprintf(text, sizeof(text), "%s: %.2f", classes[classIds[i]].c_str(), scores[i]);
			printf("%s: %s\n", argv[1], text);
			putText(img, text, Point(boxes[i].x, boxes[i].y - 5), cv::FONT_HERSHEY_SIMPLEX, 1,
					Scalar(0, 255, 0), 2);
		}	
		media += classIds.size();
		char filename[100];
		sprintf(filename,"/home/luiz/Desktop/SOE_Projeto/photos/pics_analyzed/foto_%d.jpg", i);
		imwrite(filename, img);
	}

	media = std::ceil(media/argc);
	std::time_t t = std::time(nullptr);
    
    // Converte para tempo local
    std::tm* agora = std::localtime(&t);
    
    // Obtém as partes individuais do tempo
    int ano = agora->tm_year + 1900;  // tm_year é o número de anos desde 1900
    int mes = agora->tm_mon + 1;     // tm_mon é o número de meses desde janeiro (0-11)
    int dia = agora->tm_mday;          // Dia do mês
    int hora = agora->tm_hour;         // Hora (0-23)
    int minuto = agora->tm_min;        // Minutos (0-59)

    char text_dados[100];
    sprintf(text_dados, "%d %d %d %d %d %.0f", dia, mes, ano, hora, minuto, media);
    write(fd, text_dados, strlen(text_dados));
    write(fd, "\n", 1);

	close(fd);

	return 0;
}
