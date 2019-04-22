/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Operand.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abassibe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 13:51:39 by abassibe          #+#    #+#             */
/*   Updated: 2019/04/19 17:03:09 by abassibe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPERAND_HPP
# define OPERAND_HPP

# include <stdexcept>
# include <exception>
# include <cfloat>
# include "IOperand.hpp"

struct OverFlowException : public std::overflow_error
{
	public:
		OverFlowException() throw() : std::overflow_error("Overflow error: ") {}
};

struct UnderFlowException : public std::underflow_error
{
	public:
		UnderFlowException() throw() : std::underflow_error("Underflow error: ") {}
};

struct SyntaxException : public std::invalid_argument
{
	public:
		SyntaxException() throw() : std::invalid_argument("Invalid argument error: ") {}
};

struct FloatingPointModuloException : public std::invalid_argument
{
	public:
		FloatingPointModuloException() throw() : std::invalid_argument("Invalid operand for modulo: ") {}
};

struct DivisionByZeroException : public std::logic_error
{
	public:
		DivisionByZeroException() throw() : std::logic_error("Division by zero error: ") {}
};

struct NotEnoughOperandException : public std::logic_error
{
	public:
		NotEnoughOperandException() throw() : std::logic_error("Not enough operand or empty stack: ") {}
};

struct AssertException : public std::logic_error
{
	public:
		AssertException() throw() : std::logic_error("Assert error: ") {}
};

struct NoExitException : public std::logic_error
{
	public:
		NoExitException() throw() : std::logic_error("No exit command found.") {}
};


template <typename T>
class	Operand : public IOperand
{
	public:
		Operand<T>(T operande, eOperandType type)
		{
			switch (type)
			{
				case Int8:
					if (operande > INT8_MAX)
						throw OverFlowException();
					if (operande < INT8_MIN)
						throw UnderFlowException();
					_operande = operande;
					_type = type;
					_precision = type;
					_opString = std::to_string(_operande);
					break;
				case Int16:
					if (operande > INT16_MAX)
						throw OverFlowException();
					if (operande < INT16_MIN)
						throw UnderFlowException();
					_operande = operande;
					_type = type;
					_precision = type;
					_opString = std::to_string(_operande);
					break;
				case Int32:
					if (operande > INT32_MAX)
						throw OverFlowException();
					if (operande < INT32_MIN)
						throw UnderFlowException();
					_operande = operande;
					_type = type;
					_precision = type;
					_opString = std::to_string(_operande);
					break;
				case Float:
					_operande = operande;
					_type = type;
					_precision = type;
					_opString = std::to_string(_operande);
					break;
				case Double:
					_operande = operande;
					_type = type;
					_precision = type;
					_opString = std::to_string(_operande);
					break;
				default:
					throw SyntaxException();
			}

		}
		Operand(Operand const& copy) : _operande(copy._operande), _precision(copy._precision),
		_type(copy._type), _opString(copy._opString) {}
		virtual ~Operand() {}
		Operand					&operator=(Operand const& copy)
		{
			_operande = copy._operande;
			_precision = copy._precision;
			_type = copy._type;
			_opString = copy._opString;
			return (*this);
		}
		virtual int					getPrecision() const { return (_precision); }
		virtual eOperandType		getType() const { return (_type); }
		virtual IOperand const		*operator+(IOperand const& rhs) const
		{
			int		hightestPrecision = this->getPrecision() > rhs.getPrecision() ? this->getPrecision() : rhs.getPrecision();
			switch (hightestPrecision)
			{
				case Int8:
					{
						long	rhsInt8 = atol(rhs.toString().c_str());
						long	lhsInt8 = static_cast<long>(this->_operande);
						if (lhsInt8 + rhsInt8 > INT8_MAX)
							throw OverFlowException();
						if (lhsInt8 + rhsInt8 < INT8_MIN)
							throw UnderFlowException();
						return (new Operand<int8_t>(lhsInt8 + rhsInt8, Int8));
					}
				case Int16:
					{
						long	rhsInt16 = atol(rhs.toString().c_str());
						long	lhsInt16 = static_cast<long>(this->_operande);
						if (lhsInt16 + rhsInt16 > INT16_MAX)
							throw OverFlowException();
						if (lhsInt16 + rhsInt16 < INT16_MIN)
							throw UnderFlowException();
						return (new Operand<int16_t>(lhsInt16 + rhsInt16, Int16));
					}
				case Int32:
					{
						long	rhsInt32 = atol(rhs.toString().c_str());
						long	lhsInt32 = static_cast<long>(this->_operande);
						if (lhsInt32 + rhsInt32 > INT32_MAX)
							throw OverFlowException();
						if (lhsInt32 + rhsInt32 < INT32_MIN)
							throw UnderFlowException();
						return (new Operand<int32_t>(lhsInt32 + rhsInt32, Int32));
					}
				case Float:
					{
						float	rhsFloat = strtof(rhs.toString().c_str(), NULL);
						float	lhsFloat = static_cast<float>(this->_operande);
						return (new Operand<float>(lhsFloat + rhsFloat, Float));
					}
				case Double:
					{
						double	rhsDouble = strtod(rhs.toString().c_str(), NULL);
						double	lhsDouble = static_cast<double>(this->_operande);
						return (new Operand<double>(lhsDouble + rhsDouble, Double));
					}
				default:
					throw SyntaxException();
			}
		}
		virtual IOperand const		*operator-(IOperand const& rhs) const
		{
			int		hightestPrecision = this->getPrecision() > rhs.getPrecision() ? this->getPrecision() : rhs.getPrecision();
			switch (hightestPrecision)
			{
				case Int8:
					{
						long	rhsInt8 = atol(rhs.toString().c_str());
						long	lhsInt8 = static_cast<long>(this->_operande);
						if (lhsInt8 - rhsInt8 > INT8_MAX)
							throw OverFlowException();
						if (lhsInt8 - rhsInt8 < INT8_MIN)
							throw UnderFlowException();
						return (new Operand<int8_t>(lhsInt8 - rhsInt8, Int8));
					}
				case Int16:
					{
						long	rhsInt16 = atol(rhs.toString().c_str());
						long	lhsInt16 = static_cast<long>(this->_operande);
						if (lhsInt16 - rhsInt16 > INT16_MAX)
							throw OverFlowException();
						if (lhsInt16 - rhsInt16 < INT16_MIN)
							throw UnderFlowException();
						return (new Operand<int16_t>(lhsInt16 - rhsInt16, Int16));
					}
				case Int32:
					{
						long	rhsInt32 = atol(rhs.toString().c_str());
						long	lhsInt32 = static_cast<long>(this->_operande);
						if (lhsInt32 - rhsInt32 > INT32_MAX)
							throw OverFlowException();
						if (lhsInt32 - rhsInt32 < INT32_MIN)
							throw UnderFlowException();
						return (new Operand<int32_t>(lhsInt32 - rhsInt32, Int32));
					}
				case Float:
					{
						float	rhsFloat = strtof(rhs.toString().c_str(), NULL);
						float	lhsFloat = static_cast<float>(this->_operande);
						return (new Operand<float>(lhsFloat - rhsFloat, Float));
					}
				case Double:
					{
						double	rhsDouble = strtod(rhs.toString().c_str(), NULL);
						double	lhsDouble = static_cast<double>(this->_operande);
						return (new Operand<double>(lhsDouble - rhsDouble, Double));
					}
				default:
					throw SyntaxException();
			}
		}
		virtual IOperand const		*operator*(IOperand const& rhs) const
		{
			int		hightestPrecision = this->getPrecision() > rhs.getPrecision() ? this->getPrecision() : rhs.getPrecision();
			switch (hightestPrecision)
			{
				case Int8:
					{
						long	rhsInt8 = atol(rhs.toString().c_str());
						long	lhsInt8 = static_cast<long>(this->_operande);
						if (lhsInt8 * rhsInt8 > INT8_MAX)
							throw OverFlowException();
						if (lhsInt8 * rhsInt8 < INT8_MIN)
							throw UnderFlowException();
						return (new Operand<int8_t>(lhsInt8 * rhsInt8, Int8));
					}
				case Int16:
					{
						long	rhsInt16 = atol(rhs.toString().c_str());
						long	lhsInt16 = static_cast<long>(this->_operande);
						if (lhsInt16 * rhsInt16 > INT16_MAX)
							throw OverFlowException();
						if (lhsInt16 * rhsInt16 < INT16_MIN)
							throw UnderFlowException();
						return (new Operand<int16_t>(lhsInt16 * rhsInt16, Int16));
					}
				case Int32:
					{
						long	rhsInt32 = atol(rhs.toString().c_str());
						long	lhsInt32 = static_cast<long>(this->_operande);
						if (lhsInt32 * rhsInt32 > INT32_MAX)
							throw OverFlowException();
						if (lhsInt32 * rhsInt32 < INT32_MIN)
							throw UnderFlowException();
						return (new Operand<int32_t>(lhsInt32 * rhsInt32, Int32));
					}
				case Float:
					{
						float	rhsFloat = strtof(rhs.toString().c_str(), NULL);
						float	lhsFloat = static_cast<float>(this->_operande);
						return (new Operand<float>(lhsFloat * rhsFloat, Float));
					}
				case Double:
					{
						double	rhsDouble = strtod(rhs.toString().c_str(), NULL);
						double	lhsDouble = static_cast<double>(this->_operande);
						return (new Operand<double>(lhsDouble * rhsDouble, Double));
					}
				default:
					throw SyntaxException();
			}
		}
		virtual IOperand const		*operator/(IOperand const& rhs) const
		{
			int		hightestPrecision = this->getPrecision() > rhs.getPrecision() ? this->getPrecision() : rhs.getPrecision();
			switch (hightestPrecision)
			{
				case Int8:
					{
						long	rhsInt8 = atol(rhs.toString().c_str());
						long	lhsInt8 = static_cast<long>(this->_operande);
						if (rhsInt8 == 0 || lhsInt8 == 0)
							throw DivisionByZeroException();
						if (lhsInt8 / rhsInt8 > INT8_MAX)
							throw OverFlowException();
						if (lhsInt8 / rhsInt8 < INT8_MIN)
							throw UnderFlowException();
						return (new Operand<int8_t>(lhsInt8 / rhsInt8, Int8));
					}
				case Int16:
					{
						long	rhsInt16 = atol(rhs.toString().c_str());
						long	lhsInt16 = static_cast<long>(this->_operande);
						if (rhsInt16 == 0 || lhsInt16 == 0)
							throw DivisionByZeroException();
						if (lhsInt16 / rhsInt16 > INT16_MAX)
							throw OverFlowException();
						if (lhsInt16 / rhsInt16 < INT16_MIN)
							throw UnderFlowException();
						return (new Operand<int16_t>(lhsInt16 / rhsInt16, Int16));
					}
				case Int32:
					{
						long	rhsInt32 = atol(rhs.toString().c_str());
						long	lhsInt32 = static_cast<long>(this->_operande);
						if (rhsInt32 == 0 || rhsInt32 == 0)
							throw DivisionByZeroException();
						if (lhsInt32 / rhsInt32 > INT32_MAX)
							throw OverFlowException();
						if (lhsInt32 / rhsInt32 < INT32_MIN)
							throw UnderFlowException();
						return (new Operand<int32_t>(lhsInt32 / rhsInt32, Int32));
					}
				case Float:
					{
						float	rhsFloat = strtof(rhs.toString().c_str(), NULL);
						float	lhsFloat = static_cast<float>(this->_operande);
						if (rhsFloat == 0 || lhsFloat == 0)
							throw DivisionByZeroException();
						return (new Operand<float>(lhsFloat / rhsFloat, Float));
					}
				case Double:
					{
						double	rhsDouble = strtod(rhs.toString().c_str(), NULL);
						double	lhsDouble = static_cast<double>(this->_operande);
						if (rhsDouble == 0 || lhsDouble == 0)
							throw DivisionByZeroException();
						return (new Operand<double>(lhsDouble / rhsDouble, Double));
					}
				default:
					throw SyntaxException();
			}
		}
		virtual IOperand const		*operator%(IOperand const& rhs) const
		{
			int		hightestPrecision = this->getPrecision() > rhs.getPrecision() ? this->getPrecision() : rhs.getPrecision();
			switch (hightestPrecision)
			{
				case Int8:
					{
						long	rhsInt8 = atol(rhs.toString().c_str());
						long	lhsInt8 = static_cast<long>(this->_operande);
						if (rhsInt8 == 0)
							throw DivisionByZeroException();
						if (lhsInt8 % rhsInt8 > INT8_MAX)
							throw OverFlowException();
						if (lhsInt8 % rhsInt8 < INT8_MIN)
							throw UnderFlowException();
						return (new Operand<int8_t>(lhsInt8 % rhsInt8, Int8));
					}
				case Int16:
					{
						long	rhsInt16 = atol(rhs.toString().c_str());
						long	lhsInt16 = static_cast<long>(this->_operande);
						if (rhsInt16 == 0)
							throw DivisionByZeroException();
						if (lhsInt16 % rhsInt16 > INT16_MAX)
							throw OverFlowException();
						if (lhsInt16 % rhsInt16 < INT16_MIN)
							throw UnderFlowException();
						return (new Operand<int16_t>(lhsInt16 % rhsInt16, Int16));
					}
				case Int32:
					{
						long	rhsInt32 = atol(rhs.toString().c_str());
						long	lhsInt32 = static_cast<long>(this->_operande);
						if (rhsInt32 == 0)
							throw DivisionByZeroException();
						if (lhsInt32 % rhsInt32 > INT32_MAX)
							throw OverFlowException();
						if (lhsInt32 % rhsInt32 < INT32_MIN)
							throw UnderFlowException();
						return (new Operand<int32_t>(lhsInt32 % rhsInt32, Int32));
					}
				case Float:
					throw FloatingPointModuloException();
				case Double:
					throw FloatingPointModuloException();
				default:
					throw SyntaxException();
			}
		}
		virtual std::string const	&toString() const { return (_opString); }
		T							getOperande() const { return (_operande); }

	private:
		Operand() {}
		T				_operande;
		int				_precision;
		eOperandType	_type;
		std::string		_opString;
};

#endif
