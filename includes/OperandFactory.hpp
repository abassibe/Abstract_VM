/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   OperandFactory.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abassibe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 13:38:14 by abassibe          #+#    #+#             */
/*   Updated: 2019/04/16 17:03:00 by abassibe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPERANDFACTORY_HPP
# define OPERANDFACTORY_HPP

# include <map>
# include <stdio.h>
# include <stdlib.h>
# include <cstdlib>
# include "Operand.hpp"

class OperandFactory
{
	public:
		OperandFactory();
		OperandFactory(OperandFactory const& copy);
		~OperandFactory();
		OperandFactory	&operator=(OperandFactory const& copy);
		IOperand const	*createOperand(eOperandType type, std::string const& value);

	private:
		IOperand const	*createInt8(std::string const& value) const;
		IOperand const	*createInt16(std::string const& value) const;
		IOperand const	*createInt32(std::string const& value) const;
		IOperand const	*createFloat(std::string const& value ) const;
		IOperand const	*createDouble(std::string const& value) const;
		std::map<eOperandType, IOperand const *(OperandFactory::*)(std::string const&) const>	_map;
};

#endif
