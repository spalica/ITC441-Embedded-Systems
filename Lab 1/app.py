# allow threading for automatic mode
from threading import Thread

# set up flask
from flask import Flask
from flask import request
from flask import send_from_directory
from time import sleep

app = Flask(__name__)

# set things up for GPIO
import RPi.GPIO as GPIO
GPIO.setwarnings(False)
GPIO.setmode(GPIO.BCM)

RED = 23
YELLOW = 24
GREEN = 25

GPIO.setup(RED, GPIO.OUT)
GPIO.setup(YELLOW, GPIO.OUT)
GPIO.setup(GREEN, GPIO.OUT)

# set things up for control of mode on the server side so we can get out of automatic mode
global mode
mode = 'manual'

def lights(light: str):
    """Change the light to the color indicated"""
    if light == 'green':
        GPIO.output(GREEN, True)
        GPIO.output(YELLOW, False)
        GPIO.output(RED, False)
    if light == 'yellow':
        GPIO.output(GREEN, False)
        GPIO.output(YELLOW, True)
        GPIO.output(RED, False)
    if light == 'red':
        GPIO.output(GREEN, False)
        GPIO.output(YELLOW, False)
        GPIO.output(RED, True)
    if light == 'off':
        GPIO.output(GREEN, False)
        GPIO.output(YELLOW, False)
        GPIO.output(RED, False)

# a function for automatic mode
def auto(time_red: int = 15, time_yellow: int = 3, time_green: int = 15):
    """Automatically cycle between red, green, then yellow"""
    # this seems redundant, but we need to be able to stop the loop at any point.
    # if this is not completed, the loop will finish executing, leaving the light yellow
    # even if the light was manually set to another color while the loop was executing
    # before that line
    while mode == 'auto':
        if mode == 'auto':
            lights('red')
        if mode == 'auto':
            sleep(time_red)
        if mode == 'auto':
            lights('green')
        if mode == 'auto':
            sleep(time_green)
        if mode == 'auto':
            lights('yellow')
        if mode == 'auto':
            sleep(time_yellow)

# add route to serve webpage and javascript
@app.route('/<path:path>', methods=['GET'])
def home(path):
    return send_from_directory('www', path)

# add route to listen for control data from the webpage
@app.route('/control/', methods=['POST'])
def control():
    global mode
    thread = Thread(target = auto, args = ())

    # automatic mode
    if (request.json.get('mode') == 'auto'):
        mode = 'auto'
        # start the thread to control the LEDs in automatic mode without holding up the flask loop
        thread.start()
        
    # manual mode
    elif (request.json.get('mode') == 'manual'):
        mode = 'manual'
        if (request.json.get('color')):
            lights(request.json.get('color'))
    return request.json.get('mode')

# @app.route('/js/<path:path>')
# def send_js(path):
#     return send_from_directory('js', path)

if __name__ == "__main__":
    app.run(host='0.0.0.0')