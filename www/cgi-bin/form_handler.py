#!/usr/bin/env python3

import cgi
import cgitb

cgitb.enable()  # Enable CGI error reporting

form = cgi.FieldStorage()

name = form.getvalue("name")

print()
print("<html><head>")
print("<title>Form Handler</title>")
print("</head><body>")
if name:
    print(f"<h1>Hello, {name}!</h1>")
else:
    print("<h1>Please enter your name.</h1>")
print("</body></html>")

