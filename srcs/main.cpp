/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abassibe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 15:48:46 by abassibe          #+#    #+#             */
/*   Updated: 2019/04/19 17:24:16 by abassibe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Operand.hpp"
#include "../includes/OperandFactory.hpp"
#include "../includes/StackOperand.hpp"

void	computFromConsole();
void	computFromFile(char **av);

int		main(int ac, char **av)
{
	if (ac == 1)
	{
		try
		{
			computFromConsole();
		}
		catch (NoExitException &e)
		{
			std::cout << e.what()<< std::endl;
			return (0);
		}
	}
	else if (ac ==2)
	{
		try
		{
			computFromFile(av);
		}
		catch (NoExitException &e)
		{
			std::cout << e.what()<< std::endl;
			return (0);
		}
	}
	else
	{
		std::cout << "Usage: ./avm\n    or ./avm FILEPATH\n";
		return (0);
	}
}
