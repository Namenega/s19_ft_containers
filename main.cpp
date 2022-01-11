/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namenega <namenega@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 12:44:31 by namenega          #+#    #+#             */
/*   Updated: 2022/01/11 11:30:46 by namenega         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "./iterator/iterator.hpp"
#include "./vector/vector.hpp"
// #include "./map/map.hpp"
// #include "./stack/stack.hpp"
#include <iostream>

int		main() {
	/* ********************************************************************** */
	/* **************************** TESTS VECTOR **************************** */
	/* ********************************************************************** */
	std::cout << "\033[1;34m/* ***************************************** */\033[0m" << std::endl;
	std::cout << "\033[1;34m/* ************** TEST VECTORS ************* */\033[0m" << std::endl;
	std::cout << "\033[1;34m/* ***************************************** */\033[0m" << std::endl;
	std::cout << std::endl;

	vector_testing();


	/* ********************************************************************** */
	/* **************************** TESTS STACK ***************************** */
	/* ********************************************************************** */
	std::cout << "\033[1;34m/* ***************************************** */\033[0m" << std::endl;
	std::cout << "\033[1;34m/* ************** TEST STACK *************** */\033[0m" << std::endl;
	std::cout << "\033[1;34m/* ***************************************** */\033[0m" << std::endl;
	std::cout << std::endl;

	// stack_testing();


	/* ********************************************************************** */
	/* ***************************** TESTS MAP ****************************** */
	/* ********************************************************************** */
	std::cout << "\033[1;34m/* ***************************************** */\033[0m" << std::endl;
	std::cout << "\033[1;34m/* ************** TEST MAP ***************** */\033[0m" << std::endl;
	std::cout << "\033[1;34m/* ***************************************** */\033[0m" << std::endl;
	std::cout << std::endl;

	// map_testing();

}
