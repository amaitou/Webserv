import requests

def send_chunked_request():
    # Set the target URL
    url = "http://localhost:8000"

    # Define your payload data
    payload_data ="26\r\nname=mohamed amine amazzal&Developer=4111\r\n20\r\nNetwork=1337&value=42\r\n0\r\n\r\n"

    # Split the payload into chunks
    chunk_size = 5
    chunks = [payload_data[i:i+chunk_size] for i in range(0, len(payload_data), chunk_size)]

    # Join the chunks into a single string
    payload = ''.join(chunks)

    # Set headers for chunked request
    headers = {
        'Content-Type': 'application/octet-stream',
        'Transfer-Encoding': 'chunked'
    }

    try:
        # Send chunked request
        with requests.post(url, data=payload, headers=headers) as response:
            print("Response status code:", response.status_code)
            print("Response content:", response.text)

    except requests.RequestException as e:
        print("Error:", e)

if __name__ == "__main__":
    send_chunked_request()