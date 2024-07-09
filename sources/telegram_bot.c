#include "telegram-funcs.h"
#include <tgbot/tgbot.h>
#include <cstdio>
#include <csignal>

#define TOKEN "7015240751:AAFVwD-Vm6CZWRgik4bs3DJ3UpTNdYwATU0"

void delay(int milliseconds) {
    std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
}
int main() {
    TelegramFuncs telegramBot(TOKEN);
    TgBot::TgLongPoll longPoll(*telegramBot.getBot());
	
	telegramBot.sendMessage("-4281086814", "Olá, seja bem-vindo!\nPor favor faça click em /Dia para obter o gráfico do dia ou em /Semana para o gráfico da semana");
	
	while (true) {
        longPoll.start();
        if (!strcmp(telegramBot.getLastMessage().c_str(), "/Dia"))
        {   
            telegramBot.sendMessage(telegramBot.getLastChatID(), "O gráfico do dia é o seguinte:\n");
			std::string photoPath = "../graphs/dia.png"; 
            telegramBot.sendPhoto(telegramBot.getLastChatID(), photoPath);
			delay(5000);
			telegramBot.sendMessage(telegramBot.getLastChatID(), "Olá, seja bem-vindo!\nPor favor faça click em /Dia para obter o gráfico do dia ou em /Semana para o gráfico da semana");
			telegramBot.setMessage("");
        }
		else if (!strcmp(telegramBot.getLastMessage().c_str(), "/Semana"))
        {   
            telegramBot.sendMessage(telegramBot.getLastChatID(), "O gráfico da semana é o seguinte:\n");
			std::string photoPath = "../graphs/semana.png"; 
            telegramBot.sendPhoto(telegramBot.getLastChatID(), photoPath);
			delay(5000);
			telegramBot.sendMessage(telegramBot.getLastChatID(), "Olá, seja bem-vindo!\nPor favor faça click em /Dia para obter o gráfico do dia ou em /Semana para o gráfico da semana");
			telegramBot.setMessage("");
        }
    }


    return 0;
}
