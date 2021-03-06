/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namenega <namenega@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 12:44:31 by namenega          #+#    #+#             */
/*   Updated: 2022/02/15 10:34:29 by namenega         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "./iterator/iterator.hpp"
#include "./vector/vector.hpp"
#include "./map/map.hpp"
#include "./stack/stack.hpp"
#include <iostream>

#define RESET "\033[0m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN "\033[36m"

void	map_script(void) {
	std::cout << "\033[1;34m/* ***************************************** */\033[0m" << std::endl;
	std::cout << "\033[1;34m/* ************** TEST MAP ***************** */\033[0m" << std::endl;
	std::cout << "\033[1;34m/* ***************************************** */\033[0m" << std::endl;
	std::cout << std::endl;

	map_testing();
}

void	vector_script(void) {
	std::cout << "\033[1;34m/* ***************************************** */\033[0m" << std::endl;
	std::cout << "\033[1;34m/* ************** TEST VECTORS ************* */\033[0m" << std::endl;
	std::cout << "\033[1;34m/* ***************************************** */\033[0m" << std::endl;
	std::cout << std::endl;

	vector_testing();
}

void	stack_script(void) {
	std::cout << "\033[1;34m/* ***************************************** */\033[0m" << std::endl;
	std::cout << "\033[1;34m/* ************** TEST STACK *************** */\033[0m" << std::endl;
	std::cout << "\033[1;34m/* ***************************************** */\033[0m" << std::endl;
	std::cout << std::endl;

	stack_testing();
}

void	print(std::string str, std::string col, std::string reset) {
	std::cout << col << str << reset << std::endl;
}

int		main() {
	std::string		line;

	print("Hello and welcome to FT_CONTAINERS.", GREEN, RESET);
	print("What container do you want to see ?", GREEN, RESET);
	std::cout << std::endl;
	print("1. Stack", RED, RESET);
	print("2. Vector", MAGENTA, RESET);
	print("3. Map", CYAN, RESET);
	print("4. End", BLUE, RESET);
	std::cout << std::endl;
	while (1) {
		print("Select the number (1/2/3/4) :", GREEN, RESET);
		if (!getline(std::cin, line))
			print("Select the number (1/2/3/4) :", GREEN, RESET);
		if (line == "1")
			stack_script();
		else if (line == "2")
			vector_script();
		else if (line == "3")
			map_script();
		else if (line == "4") {
			print("Thank you ! See you soon.", BLUE, RESET);
			break;
		}

	}
	return (0);
}
