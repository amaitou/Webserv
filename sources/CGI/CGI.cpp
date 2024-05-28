#include "../../includes/CGI.hpp"


CgiHandler::CgiHandler(std::string _path, std::string _method, std::string _extention, std::string _body, std::map<std::string, std::string> _headers) {
    this->cgiPath = _path;
    this->requestMethod = _method;
    this->cgiExtention = _extention;
    this->requestBody = _body;
    this->statusCode = 200;
    this->headers = _headers;
}

CgiHandler::~CgiHandler()
{
	if(cgiPid != -1)
	{
		kill(cgiPid, SIGKILL);
		waitpid(cgiPid, NULL , 0);
	}
}

std::string	CgiHandler::getResponseBody() const { return responseBody; }

int		CgiHandler::getStatusCode() const { return statusCode; }

void	CgiHandler::executeCgi()
{
	int pipeIn[2];
	int pipeOut[2];
	int pipeErr[2];
	char buffer[4096];
	int status;

	if (pipe(pipeIn) == -1 || pipe(pipeOut) == -1 || pipe(pipeErr) == -1)
	{
		statusCode = 500;
		return;
	}

	cgiPid = fork();
	if (cgiPid == -1) {
		statusCode = 500;
		return;
	}
	if (cgiPid == 0) {
		close(pipeIn[1]);
		close(pipeOut[0]);
		close(pipeErr[0]);

		dup2(pipeIn[0], 0);
		close(pipeIn[0]);

		dup2(pipeOut[1], 1);
		close(pipeOut[1]);

		dup2(pipeErr[1], 2);
		close(pipeErr[1]);

		std::vector<const char*> args;
		if (cgiExtention == "py")
			args.push_back("/usr/bin/python3");
		else if (cgiExtention == "php")
			args.push_back("/usr/bin/php");
		else if (cgiExtention == "bash")
			args.push_back("/bin/bash");
		args.push_back(cgiPath.c_str());
		args.push_back(NULL);

		std::vector<const char*> env;
		env.push_back("GATEWAY_INTERFACE=CGI/1.1");
		env.push_back(("REQUEST_METHOD=" + requestMethod).c_str());
		std::string contentType = "CONTENT_TYPE=" + headers["Content-Type"];
		env.push_back(("CONTENT_LENGTH=" + headers["Content-Length"]).c_str());
		env.push_back(contentType.c_str());
		env.push_back(NULL);

		execve(args[0], (char* const*)args.data(), (char* const*)env.data());
		statusCode = 400;
		std::exit(1);
	} else {

		close(pipeIn[0]);
		close(pipeOut[1]);
		close(pipeErr[1]);
		write(pipeIn[1], requestBody.c_str(), requestBody.size());
		close(pipeIn[1]);

		startTime = std::time(NULL);

		std::string output;
		ssize_t bytesRead;
		while ((bytesRead = read(pipeOut[0], buffer, sizeof(buffer) - 1)) > 0) {
			buffer[bytesRead] = '\0';
			output += buffer;

			checkTimeout();
		}
		close(pipeOut[0]);

		std::string errOutput;
		while ((bytesRead = read(pipeErr[0], buffer, sizeof(buffer) - 1)) > 0)
		{
			buffer[bytesRead] = '\0';
			errOutput += buffer;
		}
		close(pipeErr[0]);

		waitpid(cgiPid, &status, 0);

		if (WIFEXITED(status) && WEXITSTATUS(status) == 0)
		{
			responseBody = output;
		}
		else
		{
			responseBody = errOutput;
		}
	}
}

// Vérifier si le timeout est dépassé
void CgiHandler::checkTimeout()
{
	const int TIMEOUT_LIMIT = 5;
	time_t currentTime = std::time(NULL);
	if (currentTime - startTime >= TIMEOUT_LIMIT)
	{
		kill(cgiPid, SIGKILL);
		statusCode = 408;
	}
}

void CgiHandler::handleRequest() {

	executeCgi();
}
