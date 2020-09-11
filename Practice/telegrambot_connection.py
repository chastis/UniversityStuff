import telebot
import requests
from predict import predict

TOKEN = "token"

bot = telebot.TeleBot(token=TOKEN)

@bot.message_handler(commands=['is_cat'])
def cat_check(message):
        reply = message.reply_to_message
        if (reply and reply.photo and reply.photo[0]):
                        raw = reply.photo[0].file_id
                        path = 'photos/'+raw+".jpg"
                        file_info = bot.get_file(raw)
                        downloaded_file = bot.download_file(file_info.file_path)
                        with open(path,'wb') as new_file:
                                new_file.write(downloaded_file)
                                is_cat = predict(path)
                                if is_cat:
                                        bot.reply_to(message, "Да, я щитаю это кот")
                                else:
                                        bot.reply_to(message, "Вообще не очень похож на кота, но я не ручаюсь")

bot.polling(none_stop=False, interval=1, timeout=1)


