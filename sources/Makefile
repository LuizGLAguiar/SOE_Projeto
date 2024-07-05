all:
	g++ people_detection.cpp -o people_detection.out  `pkg-config --cflags --libs opencv4`
	g++ -std=c++11 trembolona.cpp -I/usr/include/python3.10 -lpython3.10 -o grafico.out
	
graficos:
	g++ -std=c++11 trembolona.cpp -I/usr/include/python3.10 -lpython3.10 -o grafico.out
clean:
	rm people_detection.out ../photos/pics_taken/* ../photos/pics_analyzed/*
