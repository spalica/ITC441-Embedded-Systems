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

GPIO.setup(23, GPIO.OUT)
GPIO.setup(24, GPIO.OUT)
GPIO.setup(25, GPIO.OUT)

# set things up for control
global mode
mode = 'manual'

def lights(light):
    light = str(light)
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
def auto():
    print('starting thread!')
    print('mode is:')
    print(mode)
    while mode == 'auto':
        print("running auto loop")
        lights('red')
        sleep(1)
        lights('green')
        sleep(1)
        lights('yellow')
        sleep(.5)


# add route to serve webpage and javascript
@app.route('/<path:path>', methods=['GET'])
def home(path):
    return send_from_directory('www', path)

@app.route('/control/', methods=['POST'])
def control():
    global mode
    thread = Thread(target = auto, args = ())
    # automatic mode
    if (request.json.get('mode') == 'auto'):
        
        mode = 'auto'
        # start the thread
        print('got auto request!')
        thread.start()
        
    # manual mode
    elif (request.json.get('mode') == 'manual'):
        mode = 'manual'
        # rejoin the thread
        print('rejoining thread')
        thread.join()
        if (request.json.get('color')):
            lights(request.json.get('color'))

    return request.json.get('mode')
    # return request.json['hi']


@app.route('/js/<path:path>')
def send_js(path):
    return send_from_directory('js', path)

if __name__ == "__main__":
    app.run(host='0.0.0.0')