# set up flask

from flask import Flask
from flask import request
from flask import send_from_directory
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



@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        return do_the_login()
    else:
        return show_the_login_form()

# add route to serve webpage and javascript
@app.route('/<path:path>', methods=['GET'])
def home(path):
    return send_from_directory('www', path)

@app.route('/control/', methods=['POST'])
def control():
    print('************************************')

    # automatic mode
    if (request.json.get('mode') == 'auto'):
        pass

    # manual mode
    if (request.json.get('mode') == 'manual'):
        if (request.json.get('color')):
            lights(request.json.get('color'))


    print('************************************')

    return request.json.get('mode')
    # return request.json['hi']


@app.route('/js/<path:path>')
def send_js(path):
    return send_from_directory('js', path)

if __name__ == "__main__":
    app.run(host='0.0.0.0')