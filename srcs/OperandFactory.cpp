/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   OperandFactory.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abassibe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 13:43:50 by abassibe          #+#    #+#             */
/*   Updated: 2019/04/19 18:10:58 by abassibe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/OperandFactory.hpp"

OperandFactory::OperandFactory()
{
	_map.insert(std::pair<eOperandType, IOperand const *(OperandFactory::*)(std::string const&) const>(Int8, &OperandFactory::createInt8));
	_map.insert(std::pair<eOperandType, IOperand const *(OperandFactory::*)(std::string const&) const>(Int16, &OperandFactory::createInt16));
	_map.insert(std::pair<eOperandType, IOperand const *(OperandFactory::*)(std::string const&) const>(Int32, &OperandFactory::createInt32));
	_map.insert(std::pair<eOperandType, IOperand const *(OperandFactory::*)(std::string const&) const>(Float, &OperandFactory::createFloat));
	_map.insert(std::pair<eOperandType, IOperand const *(OperandFactory::*)(std::string const&) const>(Double, &OperandFactory::createDouble));
}

OperandFactory::OperandFactory(OperandFactory const& copy)
{
	(void)copy;
}

OperandFactory::~OperandFactory()
{
}

OperandFactory	&OperandFactory::operator=(OperandFactory const& copy)
{
	(void) copy;
	return (*this);
}

IOperand const	*OperandFactory::createInt8(std::string const& value) const
{
	long op = atol(value.c_str());
	if (op > INT8_MAX)
		throw OverFlowException();
	if (op < INT8_MIN)
		throw UnderFlowException();
	return (new Operand<int8_t>(op, Int8));
}

IOperand const	*OperandFactory::createInt16(std::string const& value) const
{
	long op = atol(value.c_str());
	if (op > INT16_MAX)
		throw OverFlowException();
	if (op < INT16_MIN)
		throw UnderFlowException();
	return (new Operand<int16_t>(op, Int16));
}

IOperand const	*OperandFactory::createInt32(std::string const& value) const
{
	long op = atol(value.c_str());
	if (op > INT32_MAX)
		throw OverFlowException();
	if (op < INT32_MIN)
		throw UnderFlowException();
	return (new Operand<int32_t>(op, Int32));
}

IOperand const	*OperandFactory::createFloat(std::string const& value) const
{
	return (new Operand<float>(strtod(value.c_str(), NULL), Float));
}

IOperand const	*OperandFactory::createDouble(std::string const& value) const
{
	return (new Operand<double>(strtod(value.c_str(), NULL), Double));
}

IOperand const	*OperandFactory::createOperand(eOperandType type, std::string const& value)
{
	return ((this->*_map[type])(value));
}
