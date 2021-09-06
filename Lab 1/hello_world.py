import flask
from flask import request
from flask import send_from_directory

app = flask(__name__)

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        return do_the_login()
    else:
        return show_the_login_form()


@app.route('/<path:path>', methods=['GET'])
def home(path):
    return send_from_directory('www', path)


@app.route('/js/<path:path>')
def send_js(path):
    return send_from_directory('js', path)

if __name__ == "__main__":
    app.run()