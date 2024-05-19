from flask import Flask, request

app = Flask(__name__)

@app.route('/cgi-bin', methods=['POST'])
def submit():
    if request.method == 'POST':
        name = request.form.get('name')  # Get the value of the 'name' field from the POST request
        if name:
            print("Name:", name)  # Print the value of the 'name' field
            return "Name received: " + name
        else:
            return "No name provided in the request"
    else:
        return "Only POST requests are accepted"

if __name__ == '__main__':
    app.run(debug=True)  # Run the Flask app in debug mode

