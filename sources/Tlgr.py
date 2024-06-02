import telebot
import requests
import datetime
import time
today=datetime.datetime.now()
TOKEN = "7015240751:AAFVwD-Vm6CZWRgik4bs3DJ3UpTNdYwATU0"
CHAT_ID = "-4281086814"
bot = telebot.TeleBot(TOKEN)

bot.send_message(CHAT_ID, text= "Olá, seja bem-vindo!\n\nPor favor faça em click /Dia para obter o gráfico do dia ou em /Semana para o gráfico da semana")

@bot.message_handler(commands= ["Dia"])
def enviar_mensagem(mensagem):
    bot.reply_to(mensagem, "O gráfico do dia é o seguinte:\n")
    files = {'photo':open('../graphs/dia.jpg','rb')}
    resp =  requests.post ('https://api.telegram.org/bot7015240751:AAFVwD-Vm6CZWRgik4bs3DJ3UpTNdYwATU0/sendPhoto?chat_id=-4281086814&caption=GRÁFICO DE LOTAÇÃO ATUAL\n{}'.format(today), files = files)
    time.sleep(5)
    bot.send_message(CHAT_ID, text= "Olá, seja bem-vindo!\n\nPor favor faça em click /Dia para obter o gráfico do dia ou em /Semana para o gráfico da semana")

@bot.message_handler(commands= ["Semana"])
def enviar_mensagem(mensagem):
    bot.reply_to(mensagem, "O gráfico da semana é a seguinte:\n")
    files = {'photo':open('../graphs/semana.jpg','rb')}
    resp =  requests.post ('https://api.telegram.org/bot7015240751:AAFVwD-Vm6CZWRgik4bs3DJ3UpTNdYwATU0/sendPhoto?chat_id=-4281086814&caption=GRÁFICO DE LOTAÇÃO SEMANAL', files = files)
    time.sleep(5)
    bot.send_message(CHAT_ID, text= "Olá, seja bem-vindo!\n\nPor favor faça em click /Dia para obter o gráfico do dia ou em /Semana para o gráfico da semana")
 

bot.infinity_polling()
