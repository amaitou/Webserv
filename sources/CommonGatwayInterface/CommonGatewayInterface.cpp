/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommonGatewayInterface.cpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-amin <ael-amin@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 18:09:55 by ael-amin          #+#    #+#             */
/*   Updated: 2024/05/16 16:51:22 by amait-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/CommonGatewayInterface.hpp"


CgiHandler::CgiHandler(const std::string& path) : cgiPath(path) {}

CgiHandler::~CgiHandler() {}

void CgiHandler::executeCgi(const std::string& scriptPath, const std::string& requestMethod, const std::string& requestBody)
{
	(void) requestMethod;

	int pipeIn[2];
	int pipeOut[2];
	pid_t pid;
	char buffer[4096];
	int status;

	if (pipe(pipeIn) == -1 || pipe(pipeOut) == -1) {
		std::cerr << "Error: pipe failed" << std::endl;
		exit(1);
	}

	pid = fork();
	if (pid == -1)
	{
		std::cerr << "Error: fork failed" << std::endl;
		exit(1);
	}
	if (pid == 0)
	{
		close(pipeIn[1]);
		close(pipeOut[0]);
		dup2(pipeIn[0], 0);
		close(pipeIn[0]);
		dup2(pipeOut[1], 1);
		close(pipeOut[1]);


		std::vector<const char*> args;
		args.push_back(scriptPath.c_str());
		args.push_back(NULL);

		std::vector<const char*> env;
		env.push_back(NULL);

		execve(scriptPath.c_str(), (char* const*)args.data(), (char* const*)env.data());
		std::cerr << "Error: execve failed" << std::endl;
		exit(1);
	}
	else
	{
		close(pipeIn[0]);
		close(pipeOut[1]);
		write(pipeIn[1], requestBody.c_str(), requestBody.size());
		close(pipeIn[1]);
		waitpid(pid, &status, 0);
		while (read(pipeOut[0], buffer, 4096) > 0)
		{
			std::cout << buffer;
		}
		close(pipeOut[0]);
	}
}

void CgiHandler::handleRequest(const std::string& method, const std::string& url, const std::string& body)
{
	std::string extension = url.substr(url.find_last_of(".") + 1);

	if (extension == "py" || extension == "php" )
	{
		std::string scriptPath = cgiPath + url;
		executeCgi(scriptPath, method, body);
	}
}

