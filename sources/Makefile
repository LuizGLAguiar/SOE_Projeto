all:
	g++ people_detection.cpp -o people_detection.out  `pkg-config --cflags --libs opencv4`
	g++ -std=c++11 plot.cpp -I/usr/include/python3.10 -lpython3.10 -o plot.out
	g++ -o telegram_bot.out telegram_bot.c telegram-funcs.c -std=c++23 -lTgBot  -lpthread -lssl -lcrypto
graficos:
	g++ -std=c++11 plot.cpp -I/usr/include/python3.10 -lpython3.10 -o plot.out
telegram:
	g++ -o telegram_bot.out telegram_bot.c telegram-funcs.c -std=c++23 -lTgBot  -lpthread -lssl -lcrypto
detection:
	g++ people_detection.cpp -o people_detection.out  `pkg-config --cflags --libs opencv4`
clean:
	rm people_detection.out ../photos/pics_taken/* ../photos/pics_analyzed/*
