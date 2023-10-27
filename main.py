from flask import Flask, request
import pyautogui
import webbrowser
import time

 
app = Flask(__name__)
 
@app.route('/helloesp', methods = ['POST', 'GET'])
def helloHandler():


    if request.method == 'GET':
        
        pyautogui.hotkey('alt', 'tab')
        time.sleep(1)



        return "Sent Request"

 
app.run(host='0.0.0.0', port= 8090) 