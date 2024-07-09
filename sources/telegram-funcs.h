#ifndef TELEGRAM_FUNCS_H
#define TELEGRAM_FUNCS_H

#include <string>
#include <vector>
#include <tgbot/tgbot.h>

class TelegramFuncs {
public:
    TelegramFuncs(const std::string &token);
    ~TelegramFuncs();
    TgBot::Bot* getBot() const;

    // Funções
    void sendMessage(const std::string &chatId, const std::string &text);
    void sendPhoto(const std::string &chatId, const std::string &filePath);
    void sendFile(const std::string &chatId, const std::string &filePath);


    // Getters and Setters
    std::string getLastMessage();
    void setMessage(std::string message);
    std::string getLastChatID();
    void setChatID(int64_t id);

private:
    std::string botToken;
    TgBot::Bot* bot;
    std::string receivedMessage = "";
    std::string chatID = "";
};

void processMessage(TgBot::Message::Ptr message, TelegramFuncs& telegramFuncs);


#endif // TELEGRAM_FUNCS_H
