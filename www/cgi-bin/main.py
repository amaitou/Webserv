import os
import re
import sys
import uuid


def parse_filename(content):
    filename_pattern = r'filename="([^"]+)"'
    match = re.search(filename_pattern, content, re.IGNORECASE)
    return match.group(1).strip() if match else ""


def handle_upload(request_body, upload_dir):
    boundary = os.environ.get("CONTENT_TYPE", "").split("boundary=")[-1]
    
    if not boundary:
        return "<h1>Error: Could not find boundary in Content-Type</h1>"

    parts = request_body.split(boundary.encode())[1:-1]

    for part in parts:
        header, data = part.split(b'\r\n\r\n', 1)

        filename = parse_filename(header.decode())
        if not filename:
            continue
    
        filename, file_extension = os.path.splitext(filename)
        filename = f"{filename}{file_extension}"
        file_path = os.path.join(upload_dir,filename)

        try:
            with open(file_path, "wb") as f:
                data = data.split(b'\r\n--', 1)[0]
                f.write(data)
            return f"<h1>201 - Created</h1><h3>{filename} has been uploaded successfully!</h3><h3>Go to upload directory to see your file</h3>"
        except Exception as e:
            return f"<h1>Error during upload: {str(e)}</h1>"

    return "<h1>No file found in upload data</h1>"



def main():
    method = os.environ.get("REQUEST_METHOD", "")
    if method != "POST":
        exit(1)

    content_length = os.environ.get("CONTENT_LENGTH", "")
    if not content_length:
        print("Error: Invalid request")
        exit(0)

    upload_dir = "/Users/rlabbiz/Desktop/branch/www/"

    if not upload_dir:
        print("Error: Upload directory not set")
        exit(0)

    # Read the entire request body
    try:
        request_body = sys.stdin.buffer.read()
    except Exception as e:
        exit(1)

    response_body = "<!DOCTYPE html><html><head><title>Upload</title><meta charset=\"UTF-8\" />"
    response_body += "<style>body { font-family: sans-serif; background-color: #141615; color: #3a87ff; font-size: 2em; text-align: center; }</style>"
    response_body += "</head><body>"
    data = handle_upload(request_body, upload_dir)
    if data[:7] == "<h1>201":
        status = "201 Created"
    else:
        status = "400 Bad Request"
    response_body += data
    response_body += "</body></html>"
    print(response_body)

if __name__ == "__main__":
    main()
