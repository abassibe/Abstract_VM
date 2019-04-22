/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   StackOperand.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abassibe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 16:01:01 by abassibe          #+#    #+#             */
/*   Updated: 2019/04/22 15:16:45 by abassibe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/StackOperand.hpp"

StackOperand::StackOperand()
{
}

StackOperand::StackOperand(StackOperand const& copy) : _stack(copy._stack)
{
}

StackOperand::~StackOperand()
{
}

StackOperand	&StackOperand::operator=(StackOperand const& copy)
{
	_stack = copy._stack;
	return (*this);
}

void			StackOperand::push(std::string const& copy, eOperandType type)
{
	_stack.push_back(_of.createOperand(type, copy));
}

void				StackOperand::pop()
{
	if (_stack.size() == 0)
		throw NotEnoughOperandException();
	IOperand const	*toDelete = _stack.back();
	delete (toDelete);
	_stack.pop_back();
}

void			StackOperand::dump()
{
	if (_stack.size() == 0)
		throw NotEnoughOperandException();
	std::vector<IOperand const*>::const_reverse_iterator	rit = _stack.rbegin();

	for (; rit != _stack.rend(); rit++)
	{
		char *str = new char;
		std::string		tmp((*rit)->toString());
		tmp.append("\n");
		std::strcpy(str, tmp.c_str());
		_outputBuffer.push_back(str);
	}
}

void			StackOperand::assert(std::string const& copy, eOperandType type)
{
	if (_stack.size() == 0)
		throw NotEnoughOperandException();
	IOperand const* tmp = _of.createOperand(type, copy);
	IOperand const* tmp2 = _stack.back();
	try
	{
		if (tmp->getType() != tmp2->getType() || std::strcmp(tmp->toString().c_str(), tmp2->toString().c_str()))
			throw AssertException();
	}
	catch (OverFlowException &e)
	{
		std::cout << e.what() << "\033[0;31m" << copy << std::endl << "\033[0;0m";
		exit(0);
	}
	catch (UnderFlowException &e)
	{
		std::cout << e.what() << "\033[0;31m" << copy << std::endl << "\033[0;0m";
		exit(0);
	}
	catch (AssertException &e)
	{
		std::cout << e.what() << tmp->toString() << " != " << tmp2->toString() << std::endl;
		exit(0);
	}
}

void			StackOperand::add()
{
	if (_stack.size() < 2)
		throw NotEnoughOperandException();
	IOperand const*		op1 = _stack.back();
	_stack.pop_back();
	IOperand const*		op2 = _stack.back();
	_stack.pop_back();
	try
	{
		_stack.push_back(*op2 + *op1);
		delete op1;
		delete op2;
	}
	catch (OverFlowException &e)
	{
		std::cout << e.what() << "\033[0;31m" << op2->toString() << " + " << op1->toString() << "\033[0;0m" << std::endl;
		exit(0);
	}
	catch (UnderFlowException &e)
	{
		std::cout << e.what() << "\033[0;31m" << op2->toString() << " + " << op1->toString() << "\033[0;0m" << std::endl;
		exit(0);
	}
	catch (SyntaxException &e)
	{
		std::cout << e.what() << std::endl;
		exit(0);
	}
}

void			StackOperand::sub()
{
	if (_stack.size() < 2)
		throw NotEnoughOperandException();
	IOperand const*		op1 = _stack.back();
	_stack.pop_back();
	IOperand const*		op2 = _stack.back();
	_stack.pop_back();
	try
	{
		_stack.push_back(*op2 - *op1);
		delete op1;
		delete op2;
	}
	catch (OverFlowException &e)
	{
		std::cout << e.what() << "\033[0;31m" << op2->toString() << " - " << op1->toString() << "\033[0;0m" << std::endl;
		exit(0);
	}
	catch (UnderFlowException &e)
	{
		std::cout << e.what() << "\033[0;31m" << op2->toString() << " - " << op1->toString() << "\033[0;0m" << std::endl;
		exit(0);
	}
	catch (SyntaxException &e)
	{
		std::cout << e.what() << std::endl;
		exit(0);
	}
}

void			StackOperand::mul()
{
	if (_stack.size() < 2)
		throw NotEnoughOperandException();
	IOperand const*		op1 = _stack.back();
	_stack.pop_back();
	IOperand const*		op2 = _stack.back();
	_stack.pop_back();
	try
	{
		_stack.push_back(*op2 * *op1);
		delete op1;
		delete op2;
	}
	catch (OverFlowException &e)
	{
		std::cout << e.what() << "\033[0;31m" << op2->toString() << " * " << op1->toString() << "\033[0;0m" << std::endl;
		exit(0);
	}
	catch (UnderFlowException &e)
	{
		std::cout << e.what() << "\033[0;31m" << op2->toString() << " * " << op1->toString() << "\033[0;0m" << std::endl;
		exit(0);
	}
	catch (SyntaxException &e)
	{
		std::cout << e.what() << std::endl;
		exit(0);
	}
}

void			StackOperand::div()
{
	if (_stack.size() < 2)
		throw NotEnoughOperandException();
	IOperand const*		op1 = _stack.back();
	_stack.pop_back();
	IOperand const*		op2 = _stack.back();
	_stack.pop_back();
	try
	{
		_stack.push_back(*op2 / *op1);
		delete op1;
		delete op2;
	}
	catch (DivisionByZeroException &e)
	{
		std::cout << e.what() << "\033[0;31m" << op2->toString() << " / " << op1->toString() << "\033[0;0m" << std::endl;
		exit(0);
	}
	catch (OverFlowException &e)
	{
		std::cout << e.what() << "\033[0;31m" << op2->toString() << " / " << op1->toString() << "\033[0;0m" << std::endl;
		exit(0);
	}
	catch (UnderFlowException &e)
	{
		std::cout << e.what() << "\033[0;31m" << op2->toString() << " / " << op1->toString() << "\033[0;0m" << std::endl;
		exit(0);
	}
	catch (SyntaxException &e)
	{
		std::cout << e.what() << std::endl;
		exit(0);
	}
}

void			StackOperand::mod()
{
	if (_stack.size() < 2)
		throw NotEnoughOperandException();
	IOperand const*		op1 = _stack.back();
	_stack.pop_back();
	IOperand const*		op2 = _stack.back();
	_stack.pop_back();
	try
	{
		_stack.push_back(*op2 % *op1);
		delete op1;
		delete op2;
	}
	catch (FloatingPointModuloException &e)
	{
		std::cout << e.what() << "\033[0;31m" << op2->toString() << " % " << op1->toString() << "\033[0;0m" << std::endl;
		exit(0);
	}
	catch (DivisionByZeroException &e)
	{
		std::cout << e.what() << "\033[0;31m" << op2->toString() << " % " << op1->toString() << "\033[0;0m" << std::endl;
		exit(0);
	}
	catch (OverFlowException &e)
	{
		std::cout << e.what() << "\033[0;31m" << op2->toString() << " % " << op1->toString() << "\033[0;0m" << std::endl;
		exit(0);
	}
	catch (UnderFlowException &e)
	{
		std::cout << e.what() << "\033[0;31m" << op2->toString() << " % " << op1->toString() << "\033[0;0m" << std::endl;
		exit(0);
	}
	catch (SyntaxException &e)
	{
		std::cout << e.what() << std::endl;
		exit(0);
	}
}

void			StackOperand::print()
{
	if (_stack.size() == 0)
		throw NotEnoughOperandException();
	IOperand const*		op = _stack.back();
	if (op->getType() != Int8)
		throw SyntaxException();
	char *c = new char;
	c[0] = static_cast<char>(atoi(op->toString().c_str()));
	_outputBuffer.push_back(c);
}

void			StackOperand::exitCmd()
{
	for (std::vector<char const*>::const_iterator it = _outputBuffer.begin(); it != _outputBuffer.end(); it++)
		std::cout << *it;
	exit(0);
}

void			StackOperand::computOperation(std::string operation, std::string const& value, eOperandType type)
{
	if (operation.find(';') != std::string::npos)
		operation.erase(operation.find(';'));
	if (std::strcmp(operation.c_str(), "push") == 0)
	{
		if (value == "NONE")
			throw SyntaxException();
		push(value, type);
	}
	else if (std::strcmp(operation.c_str(), "pop") == 0)
		pop();
	else if (std::strcmp(operation.c_str(), "dump") == 0)
		dump();
	else if (std::strcmp(operation.c_str(), "assert") == 0)
	{
		if (value == "NONE")
			throw SyntaxException();
		assert(value, type);
	}
	else if (std::strcmp(operation.c_str(), "add") == 0)
		add();
	else if (std::strcmp(operation.c_str(), "sub") == 0)
		sub();
	else if (std::strcmp(operation.c_str(), "mul") == 0)
		mul();
	else if (std::strcmp(operation.c_str(), "div") == 0)
		div();
	else if (std::strcmp(operation.c_str(), "mod") == 0)
		mod();
	else if (std::strcmp(operation.c_str(), "print") == 0)
		print();
	else if (std::strcmp(operation.c_str(), "exit") == 0)
		exitCmd();
	else
		throw SyntaxException();
}
