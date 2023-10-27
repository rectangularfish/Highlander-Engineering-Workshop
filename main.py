# Import the Flask web framework and other required libraries
from flask import Flask, request
import pyautogui  # Import the pyautogui library for simulating keyboard and mouse actions
import time  # Import the time library for adding delays

# Create a Flask web application instance
app = Flask(__name__)

# Define a route for handling HTTP requests at the '/helloesp' URL
@app.route('/helloesp', methods=['POST', 'GET'])
def helloHandler():
    # Check if the incoming request method is 'GET'
    if request.method == 'GET':
        # Simulate pressing the Alt+Tab keys to switch between applications
        pyautogui.hotkey('alt', 'tab')
        time.sleep(1)  # Pause the program for 1 second

        # Return a response indicating that a request has been sent
        return "Sent Request"

# Start the Flask application and listen on all available network interfaces at port 8090
app.run(host='0.0.0.0', port=8090)