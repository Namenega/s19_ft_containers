/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_testing.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namenega <namenega@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 13:09:59 by namenega          #+#    #+#             */
/*   Updated: 2022/01/14 15:15:54 by namenega         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stack.hpp"
#include <iostream>

#ifndef FT
 #define FT ft
#endif

void	stack_empty_test(void) {
	FT::stack<int>		st;
	int					sum = 0;

	for (int i = 1; i <= 10; i++)
		st.push(i);
	while (!st.empty()) {
		sum += st.top();
		st.pop();
	}
	std::cout << "Total: " << sum << std::endl;
}

void	stack_size_test(void) {
	FT::stack<int>		tab;

	std::cout << "0. Size : " << tab.size() << std::endl;
	for (int i = 0; i < 5; i++)
		tab.push(i);
	std::cout << "1. Size : " << tab.size() << std::endl;
	tab.pop();
	std::cout << "2. Size : " << tab.size() << std::endl;
}

void	stack_top_test(void) {
	FT::stack<int>		tab;

	tab.push(10);
	tab.push(50);

	tab.top() -= 5;
	std::cout << "Tab.top() is now " << tab.top() << std::endl << std::endl;
}

void	stack_testing(void) {
	std::cout << "\033[1;31m/* ******** Stack Empty Test *************** */\033[0m" << std::endl;
	std::cout << std::endl;
	stack_empty_test();

	std::cout << std::endl;
	std::cout << "\033[1;31m/* ******** Stack Size Test **************** */\033[0m" << std::endl;
	std::cout << std::endl;
	stack_size_test();

	std::cout << std::endl;
	std::cout << "\033[1;31m/* ******** Stack Top Test ***************** */\033[0m" << std::endl;
	std::cout << std::endl;
	stack_top_test();
}
