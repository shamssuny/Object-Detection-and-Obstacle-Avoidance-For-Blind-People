# from gtts import gTTS
# import os
# tts = gTTS(text='Good morning', lang='en')
# tts.save("good.mp3")
# os.system("mpg3 good.mp3")

import win32com.client
speaker = win32com.client.Dispatch("SAPI.SpVoice")
speaker.Speak("Hi Shahana, how are you? Do yo love Tofajjal now?")