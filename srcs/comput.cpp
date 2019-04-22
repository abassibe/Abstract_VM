/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comput.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abassibe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 16:04:56 by abassibe          #+#    #+#             */
/*   Updated: 2019/04/22 15:08:41 by abassibe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/StackOperand.hpp"

void	stringSplit(std::list<char *> &list, char *buff)
{
	char	*pch = strtok(buff, " \t");
	while (pch != NULL)
	{
		list.push_back(pch);
		pch = strtok(NULL, " \t");
	}
}

eOperandType	getTypeValue(char *type, std::string &value)
{
	if (type[0] == ';')
		return Int8;
	char	*pch = strtok(type, "()");
	if (std::strlen(pch) == 4 && std::strcmp(pch, "int8") == 0)
	{
		pch = strtok(NULL, "()");
		if (!pch)
			throw SyntaxException();
		for (int i = 0; pch[i] != 0; i++)
		{
			if (i == 0 && (pch[i] == '-' || pch[i] == '+'))
				i++;
			if (pch[i] < '0' || pch[i] > '9')
				throw SyntaxException();
		}
		value = pch;
		return (Int8);
	}
	else if (std::strlen(pch) == 5 && std::strcmp(pch, "int16") == 0)
	{
		pch = strtok(NULL, "()");
		if (!pch)
			throw SyntaxException();
		for (int i = 0; pch[i] != 0; i++)
		{
			if (i == 0 && (pch[i] == '-' || pch[i] == '+'))
				i++;
			if (pch[i] < '0' || pch[i] > '9')
				throw SyntaxException();
		}
		value = pch;
		return (Int16);
	}
	else if (std::strlen(pch) == 5 && std::strcmp(pch, "int32") == 0)
	{
		pch = strtok(NULL, "()");
		if (!pch)
			throw SyntaxException();
		for (int i = 0; pch[i] != 0; i++)
		{
			if (i == 0 && (pch[i] == '-' || pch[i] == '+'))
				i++;
			if (pch[i] < '0' || pch[i] > '9')
				throw SyntaxException();
		}
		value = pch;
		return (Int32);
	}
	else if (std::strlen(pch) == 5 && std::strcmp(pch, "float") == 0)
	{
		pch = strtok(NULL, "()");
		if (!pch)
			throw SyntaxException();
		bool	dot = false;
		for (int i = 0; pch[i] != 0; i++)
		{
			if (i == 0 && (pch[i] == '-' || pch[i] == '+'))
				i++;
			if (((pch[i] < '0' || pch[i] > '9') && pch[i] != '.') || (pch[i] == '.' && dot == true))
				throw SyntaxException();
			if (pch[i] == '.')
				dot = true;
		}
		value = pch;
		return (Float);
	}
	else if (std::strlen(pch) == 6 && std::strcmp(pch, "double") == 0)
	{
		pch = strtok(NULL, "()");
		if (!pch)
			throw SyntaxException();
		bool	dot = false;
		for (int i = 0; pch[i] != 0; i++)
		{
			if (i == 0 && (pch[i] == '-' || pch[i] == '+'))
				i++;
			if (((pch[i] < '0' || pch[i] > '9') && pch[i] != '.') || (pch[i] == '.' && dot == true))
				throw SyntaxException();
			if (pch[i] == '.')
				dot = true;
		}
		value = pch;
		return (Double);
	}
	else
		throw SyntaxException();
}

void			computFromFile(char **av)
{
	std::fstream	fs;
	StackOperand	so;

	fs.open(av[1], std::fstream::in);
	char	buff[512];
	std::list<char *> split;
	if (fs.is_open())
	{
		int		line = 1;
		while (fs.getline(buff, 512))
		{
			std::string		saveBuff(buff);
			split.clear();
			stringSplit(split, buff);
			if (split.size() <= 0)
				continue;
			std::list<char *>::iterator it = split.begin();
			char *operation = *it;
			if (operation[0] == ';')
				continue;
			it++;
			try
			{
				std::string value;
				eOperandType type = Int8;
				if (it != split.end())
					type = getTypeValue(*it, value);
				else
					value = "NONE";
				so.computOperation(operation, value, type);
			}
			catch (OverFlowException &e)
			{
				std::cout << e.what() << "Line " << line << ": " << "\033[0;31m" << saveBuff << "\033[0;0m" << std::endl;
				exit(0);
			}
			catch (UnderFlowException &e)
			{
				std::cout << e.what() << "Line " << line << ": " << "\033[0;31m" << saveBuff << "\033[0;0m" << std::endl;
				exit(0);
			}
			catch (SyntaxException &e)
			{
				std::cout << e.what() << "Line " << line << ": " << "\033[0;31m" << saveBuff << "\033[0;0m" << std::endl;
				exit(0);
			}
			catch (FloatingPointModuloException &e)
			{
				std::cout << e.what() << "Line " << line << ": " << "\033[0;31m" << saveBuff << "\033[0;0m" << std::endl;
				exit(0);
			}
			catch (DivisionByZeroException &e)
			{
				std::cout << e.what() << "Line " << line << ": " << "\033[0;31m" << saveBuff << "\033[0;0m" << std::endl;
				exit(0);
			}
			catch (NotEnoughOperandException &e)
			{
				std::cout << e.what() << "Line " << line << ": " << "\033[0;31m" << saveBuff << "\033[0;0m" << std::endl;
				exit(0);
			}
			catch (AssertException &e)
			{
				std::cout << e.what() << "Line " << line << ": " << "\033[0;31m" << saveBuff << "\033[0;0m" << std::endl;
				exit(0);
			}
			line++;
		}
		throw NoExitException();
	}
	else
	{
		std::cout << "Error opening file" << std::endl;
		exit (0);
	}
}

void			computFromConsole()
{
	StackOperand	so;

	std::vector<std::string>	buff;
	while (1)
	{
		std::string		input;
		std::getline(std::cin, input);
		if (!std::cin)
			break;
		if (input == ";;")
			break ;
		buff.push_back(input);
	}
	std::list<char *> split;
	int		line = 1;
	for (size_t size = 0; size < buff.size(); size++)
	{
		std::string		saveBuff(buff[size]);
		split.clear();
		char	buffer[512];
		std::strcpy(buffer, buff[size].c_str());
		stringSplit(split, buffer);
		if (split.size() <= 0)
			continue;
		std::list<char *>::iterator it = split.begin();
		char *operation = *it;
		if (operation[0] == ';')
			continue;
		it++;
		try
		{
			std::string value;
			eOperandType type = Int8;
			if (it != split.end())
				type = getTypeValue(*it, value);
			else
				value = "NONE";
			so.computOperation(operation, value, type);
		}
		catch (OverFlowException &e)
		{
			std::cout << e.what() << "Line " << line << ": " << "\033[0;31m" << saveBuff << "\033[0;0m" << std::endl;
			exit(0);
		}
		catch (UnderFlowException &e)
		{
			std::cout << e.what() << "Line " << line << ": " << "\033[0;31m" << saveBuff << "\033[0;0m" << std::endl;
			exit(0);
		}
		catch (SyntaxException &e)
		{
			std::cout << e.what() << "Line " << line << ": " << "\033[0;31m" << saveBuff << "\033[0;0m" << std::endl;
			exit(0);
		}
		catch (FloatingPointModuloException &e)
		{
			std::cout << e.what() << "Line " << line << ": " << "\033[0;31m" << saveBuff << "\033[0;0m" << std::endl;
			exit(0);
		}
		catch (DivisionByZeroException &e)
		{
			std::cout << e.what() << "Line " << line << ": " << "\033[0;31m" << saveBuff << "\033[0;0m" << std::endl;
			exit(0);
		}
		catch (NotEnoughOperandException &e)
		{
			std::cout << e.what() << "Line " << line << ": " << "\033[0;31m" << saveBuff << "\033[0;0m" << std::endl;
			exit(0);
		}
		catch (AssertException &e)
		{
			std::cout << e.what() << "Line " << line << ": " << "\033[0;31m" << saveBuff << "\033[0;0m" << std::endl;
			exit(0);
		}
		line++;
	}
	throw NoExitException();
}
