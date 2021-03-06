/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IOperand.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abassibe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 13:51:39 by abassibe          #+#    #+#             */
/*   Updated: 2019/04/16 15:13:00 by abassibe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IOPERAND_HPP
# define IOPERAND_HPP

# include <iostream>

enum eOperandType {
	Int8 = 0,
	Int16 = 1,
	Int32 = 2,
	Float = 3,
	Double = 4};

class	IOperand
{
	public:
		virtual int					getPrecision() const = 0;
		virtual eOperandType		getType() const = 0;
		virtual IOperand const		*operator+(IOperand const& rhs) const = 0;
		virtual IOperand const		*operator-(IOperand const& rhs) const = 0;
		virtual IOperand const		*operator*(IOperand const& rhs) const = 0;
		virtual IOperand const		*operator/(IOperand const& rhs) const = 0;
		virtual IOperand const		*operator%(IOperand const& rhs) const = 0;
		virtual std::string const	&toString() const = 0;
		virtual ~IOperand() {}
};

#endif
