from flask import Flask, request

# Initialize the Flask application
app = Flask(__name__)


@app.route('/', methods=['POST'])
def handle_request():
    '''
    Handle incoming POST requests to the root URL ('/').
    
    This function expects the request to contain form data with a 'value' key.
    It prints the received value and returns a success message along with a
    HTTP 200 status code.
    
    Returns:
        str: A success message indicating the request was received.
        int: HTTP status code 200 indicating successful handling of the request.
    '''
    # Parse the 'value' from the form data
    value = request.form.get('value')
    
    print(f"Received value: {value}")

    # Return a success message with an HTTP 200 status code
    return "Request received successfully", 200


if __name__ == '__main__':
    # Runs the Flask server on the local machine (127.0.0.1) at port 8080
    app.run(host='127.0.0.1', port=8080, debug=True)
