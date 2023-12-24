# Webserv
This project is here to make you write your own HTTP server. You will be able to test it with a real browser. HTTP is one of the most used protocol on internet. Knowing its arcane will be useful, even if you won't be working on a website.


# HTTP

HTTP stands for Hypertext Transfer Protocol, and it is the foundation of data communication on the World Wide Web. It is an application layer protocol that allows web browsers and servers to communicate and exchange information. When you see "https" in a URL, it stands for Hypertext Transfer Protocol Secure.

HTTPS is the secure version of HTTP. It adds a layer of encryption using SSL/TLS (Secure Sockets Layer/Transport Layer Security) protocols to ensure that the data exchanged between a user's web browser and a website's server is encrypted and secure. This encryption helps protect sensitive information, such as login credentials, credit card numbers, and other personal data, from being intercepted by malicious entities.

Whenever you visit a page on the web, your computer uses the Hypertext Transfer Protocol (HTTP) to download that page from another computer somewhere on the Internet.

Here is the process of the mechanism behind HTTP:

- Client Request (Direct browser to URL)
	> The process begins when a user enters a URL (Uniform Resource Locator) into the address bar of a web browser or clicks on a link, then the browser initiates an HTTP request to the server associated with the specified URL.

	---

-  DNS Resolution (Browser looks up IP)
	> If the URL contains a domain name, the browser performs a Domain Name System (DNS) lookup to obtain the server's IP address. The DNS translates the human-readable domain name into an IP address that the computer can use to locate the server on the Internet.

	---

- HTTP Request (Browser sends HTTP request)
	> The browser sends an HTTP request to the server. This request includes information such as the method (e.g., GET, POST), the requested resource (e.g., a specific web page), and other headers providing additional details.

	---

- Server Processing
	> The server receives the HTTP request and processes it. This may involve fetching data, executing scripts, or accessing databases to generate a response.

	---

-  HTTP Response (Host sends back HTTP response)
	> The server sends back an HTTP response to the client. This response includes a status code indicating the success or failure of the request, along with the requested data (e.g., HTML content, images, etc.).

	The HTTP response starts similarly to the request:
	```
	HTTP/1.1 200 OK
	```
	The response begins with the protocol and version, "HTTP/1.1". <br />

	The next number is the very important `HTTP status code`, and in this case, it's 200. That code represents a successful retrieval of the document ("OK").  <br />

	The next part of an HTTP response are the headers. They give the browser additional details and help the browser to render the content.

	---

- Content Rendering (The browser renders the response)
	> The browser receives the HTTP response and interprets the received data. It may render HTML, execute scripts, and fetch additional resources (such as images, stylesheets, and scripts) referenced in the HTML.