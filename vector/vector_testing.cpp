/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_testing.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namenega <namenega@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 11:15:34 by namenega          #+#    #+#             */
/*   Updated: 2022/01/11 18:49:47 by namenega         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.hpp"
#include <iostream>

#ifndef NAMESPACE
 #define NAMESPACE ft
#endif

void	vector_constructor_test(void) {
	NAMESPACE::vector<int>	first;									// empty vector of int
	NAMESPACE::vector<int>	second((size_t)4, 100);					// 4 int of value 100
	NAMESPACE::vector<int>	third(second.begin(), second.end());	// iterating through second
	NAMESPACE::vector<int>	fourth(third);							// copy of third

	//iterator constructor can also be used to construct from arrays
	int	tab[] = {15, 3, 50, 30};
	NAMESPACE::vector<int>	fifth(tab, tab + sizeof(tab) / sizeof(int));

	std::cout << "vector 'first' values :" << std::endl;
	for (NAMESPACE::vector<int>::iterator it = first.begin(); it != first.end(); ++it)
		std::cout << *it << ' ';
	std::cout << std::endl;

	std::cout << "vector 'fourth' values :" << std::endl;
	for (NAMESPACE::vector<int>::iterator it = fourth.begin(); it != fourth.end(); ++it)
		std::cout << *it << ' ';
	std::cout << std::endl;

	std::cout << "vector 'fifth' values :" << std::endl;
	for (NAMESPACE::vector<int>::iterator it = fifth.begin(); it != fifth.end(); ++it)
		std::cout << *it << ' ';
	std::cout << std::endl;
}

void	vector_operator_test(void) {
	NAMESPACE::vector<int>	first(3, 0);
	NAMESPACE::vector<int>	second(5, 0);

	second = first;
	first = NAMESPACE::vector<int>();
	std::cout << "Size of first : " << int(first.size()) << std::endl;
	std::cout << "Size of second : " << int(second.size()) << std::endl;
}

void	vector_begin_test(void) {
	NAMESPACE::vector<int>	vec;
	for (int i = 1; i <= 5; i++)
		vec.push_back(i);
	
	std::cout << "Vec contains :" << std::endl;
	for (NAMESPACE::vector<int>::iterator it = vec.begin(); it != vec.end(); ++it) {
		std::cout << *it << ' ';
	}
	std::cout << std::endl;
}

void	vector_end_test(void) {
	NAMESPACE::vector<int>	vec;
	for (int i = 1; i <= 5; i++)
		vec.push_back(i);
	
	std::cout << "Vec contains :" << std::endl;
	for (NAMESPACE::vector<int>::iterator it = vec.begin(); it != vec.end(); ++it) {
		std::cout << *it << ' ';
	}
	std::cout << std::endl;
}

void	vector_rbegin_test(void) {
	NAMESPACE::vector<int>	vec;	// 5 default constructor int.
	vec.push_back(3);
	vec.push_back(6);
	vec.push_back(2);
	vec.push_back(7);
	int						i = 0;
	
	for (NAMESPACE::vector<int>::reverse_iterator rit = vec.rbegin(); rit != vec.rend(); ++rit)
		*rit = ++i;
	
	std::cout << "Vec contains :" << std::endl;
	for (NAMESPACE::vector<int>::iterator it = vec.begin(); it != vec.end(); it++)
		std::cout << *it << ' ';
	std::cout << std::endl;
}

void	vector_rend_test(void) {
	NAMESPACE::vector<int>	vec;	// 5 default constructor int.
	vec.push_back(5);
	vec.push_back(6);
	vec.push_back(2);
	vec.push_back(7);
	int						i = 0;
	
	for (NAMESPACE::vector<int>::reverse_iterator rit = vec.rbegin(); rit != vec.rend(); ++rit)
		*rit = ++i;
	
	std::cout << "Vec contains :" << std::endl;
	for (NAMESPACE::vector<int>::iterator it = vec.begin(); it != vec.end(); it++)
		std::cout << *it << ' ';
	std::cout << std::endl;
}

void	vector_size_test(void) {
	NAMESPACE::vector<int>	vec;
	std::cout << "A. size = " << vec.size() << std::endl;

	for (int i = 0; i < 10; i++) {
		vec.push_back(i);
	}
	std::cout << "B. size = " << vec.size() << std::endl;

	vec.insert(vec.end(), 10, 100);
	std::cout << "C. size = " << vec.size() << std::endl;
	
	vec.pop_back();
	std::cout << "D. size = " << vec.size() << std::endl;
}

void	vector_testing() {
	std::cout << "\033[1;35m/* ******** Vector Constructor Test ******** */\033[0m" << std::endl;
	std::cout << std::endl;
	vector_constructor_test();

	std::cout << std::endl;
	std::cout << "\033[1;35m/* ******** Vector Operators Test ********** */\033[0m" << std::endl;
	std::cout << std::endl;
	vector_operator_test();
	
	/* ****************************** Iterators ***************************** */
	std::cout << std::endl;
	std::cout << "\033[1;35m/* ******** Vector Begin Test ************** */\033[0m" << std::endl;
	std::cout << std::endl;
	vector_begin_test();

	std::cout << std::endl;
	std::cout << "\033[1;35m/* ******** Vector End Test **************** */\033[0m" << std::endl;
	std::cout << std::endl;
	vector_end_test();

	std::cout << std::endl;
	std::cout << "\033[1;35m/* ******** Vector Rbegin Test ************* */\033[0m" << std::endl;
	std::cout << std::endl;
	vector_rbegin_test();

	std::cout << std::endl;
	std::cout << "\033[1;35m/* ******** Vector Rend Test *************** */\033[0m" << std::endl;
	std::cout << std::endl;
	vector_rend_test();

	/* ****************************** Capacity ****************************** */
	std::cout << std::endl;
	std::cout << "\033[1;35m/* ******** Vector Size Test *************** */\033[0m" << std::endl;
	std::cout << std::endl;
	vector_size_test();

	std::cout << std::endl;
	std::cout << "\033[1;35m/* ******** Vector Maxsize Test ************ */\033[0m" << std::endl;
	std::cout << std::endl;
	// vector_maxsize_test();

	std::cout << std::endl;
	std::cout << "\033[1;35m/* ******** Vector Resize Test ************* */\033[0m" << std::endl;
	std::cout << std::endl;
	// vector_resize_test();

	std::cout << std::endl;
	std::cout << "\033[1;35m/* ******** Vector Capacity Test *********** */\033[0m" << std::endl;
	std::cout << std::endl;
	// vector_capacity_test();

	std::cout << std::endl;
	std::cout << "\033[1;35m/* ******** Vector Empty Test ************** */\033[0m" << std::endl;
	std::cout << std::endl;
	// vector_empty_test();

	std::cout << std::endl;
	std::cout << "\033[1;35m/* ******** Vector Reserve Test ************ */\033[0m" << std::endl;
	std::cout << std::endl;
	// vector_reserve_test();

	/* *************************** Element Access *************************** */
	std::cout << std::endl;
	std::cout << "\033[1;35m/* ******** Vector Subscript Operator Test * */\033[0m" << std::endl;
	std::cout << std::endl;
	// vector_subscript_operator_test();

	std::cout << std::endl;
	std::cout << "\033[1;35m/* ******** Vector At Test ***************** */\033[0m" << std::endl;
	std::cout << std::endl;
	// vector_at_test();

	std::cout << std::endl;
	std::cout << "\033[1;35m/* ******** Vector Front Test ************** */\033[0m" << std::endl;
	std::cout << std::endl;
	// vector_front_test();

	std::cout << std::endl;
	std::cout << "\033[1;35m/* ******** Vector Back Test *************** */\033[0m" << std::endl;
	std::cout << std::endl;
	// vector_back_test();

	/* ****************************** Modifiers ***************************** */
	std::cout << std::endl;
	std::cout << "\033[1;35m/* ******** Vector Assign Test ************* */\033[0m" << std::endl;
	std::cout << std::endl;
	// vector_assign_test();

	std::cout << std::endl;
	std::cout << "\033[1;35m/* ******** Vector Push_back Test ********** */\033[0m" << std::endl;
	std::cout << std::endl;
	// vector_push_back_test();

	std::cout << std::endl;
	std::cout << "\033[1;35m/* ******** Vector Pop_back Test *********** */\033[0m" << std::endl;
	std::cout << std::endl;
	// vector_pop_back_test();










	std::cout << std::endl;
}
