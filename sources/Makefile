all:
	g++ -o people_detection.out people_detection.cpp `pkg-config --cflags --libs opencv4`
	g++ -o plot.out plot.cpp -std=c++11 -I/usr/include/python3.11 -lpython3.11
	g++ -o telegram_bot.out telegram_bot.c telegram-funcs.c -std=c++23 -lTgBot  -lpthread -lssl -lcrypto
plot:
	g++ -o plot.out plot.cpp -std=c++11 -I/usr/include/python3.11 -lpython3.11
telegram:
	g++ -o telegram_bot.out telegram_bot.c telegram-funcs.c -std=c++23 -lTgBot  -lpthread -lssl -lcrypto
detection:
	g++ -o people_detection.out people_detection.cpp `pkg-config --cflags --libs opencv4`
clean:
	rm *.out ../photos/pics_taken/* ../photos/pics_analyzed/*
