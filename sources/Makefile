all:
	g++ -o people_detection.out people_detection.cpp `pkg-config --cflags --libs opencv4`
	gcc -o graph.out graph.c
	g++ -o telegram_bot.out telegram_bot.c telegram-funcs.c -std=c++23 -lTgBot  -lpthread -lssl -lcrypto
graph:
	gcc -o graph.out graph.c
telegram:
	g++ -o telegram_bot.out telegram_bot.c telegram-funcs.c -std=c++23 -lTgBot  -lpthread -lssl -lcrypto
detection:
	g++ -o people_detection.out people_detection.cpp `pkg-config --cflags --libs opencv4`
clean-all:
	rm *.out ../photos/pics_taken/* ../photos/pics_analyzed/*
clean:
	rm *.out
