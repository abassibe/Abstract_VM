/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   StackOperand.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abassibe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 15:56:57 by abassibe          #+#    #+#             */
/*   Updated: 2019/04/22 15:15:40 by abassibe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACKOPERAND_HPP
# define STACKOPERAND_HPP

# include <vector>
# include <list>
# include <fstream>
# include "Operand.hpp"
# include "OperandFactory.hpp"

class StackOperand
{
	public:
		StackOperand();
		StackOperand(StackOperand const& copy);
		~StackOperand();
		StackOperand	&operator=(StackOperand const& copy);
		void			push(std::string const& value, eOperandType type);
		void			pop();
		void			dump();
		void			assert(std::string const& value, eOperandType type);
		void			add();
		void			sub();
		void			mul();
		void			div();
		void			mod();
		void			print();
		void			exitCmd();
		void			computOperation(std::string operation, std::string const& value = NULL, eOperandType type = Int8);

	private:
		std::vector<IOperand const*>	_stack;
		OperandFactory					_of;
		std::vector<char const*>				_outputBuffer;
};

#endif
