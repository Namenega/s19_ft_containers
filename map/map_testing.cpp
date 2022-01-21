/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_testing.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namenega <namenega@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 13:37:22 by namenega          #+#    #+#             */
/*   Updated: 2022/01/21 17:05:19 by namenega         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.hpp"
#include <iostream>

#ifndef FT
 #define FT ft
#endif

bool	fncomp(char lhs, char rhs) {
	return (lhs < rhs);
}

struct	classComp {
	bool	operator()(const char &lhs, const char &rhs) const {
		return (lhs < rhs);
	}
};

void	map_constructor_test(void) {
	FT::map<char, int>	first;

	first['a'] = 10;
	first['b'] = 30;
	first['c'] = 50;
	first['d'] = 17;
	std::cout << "Map first contains :\n";
	for (FT::map<char, int>::iterator it = first.begin(); it != first.end(); ++it)
		std::cout << "[ " << it->first << " : " << it->second << " ]" << std::endl;
	std::cout << std::endl;

	FT::map<char, int>	second(first.begin(), first.end());
	std::cout << "Map second contains :\n";
	for (FT::map<char, int>::iterator it = second.begin(); it != second.end(); ++it)
		std::cout << "[ " << it->first << " : " << it->second << " ]" << std::endl;
	std::cout << std::endl;

	FT::map<char, int>	third(second);
	std::cout << "Map third contains :\n";
	for (FT::map<char, int>::iterator it = third.begin(); it != third.end(); ++it)
		std::cout << "[ " << it->first << " : " << it->second << " ]" << std::endl;
	// std::cout << std::endl;

	// FT::map<char, int, classComp>	fourth;
	// std::cout << "Map fourth contains :\n";
	// for (FT::map<char, int>::iterator it = fourth.begin(); it != fourth.end(); ++it)
	// 	std::cout << "key : " << it->first << " --> value : " << it->second << std::endl;
}

void	map_operator_test(void) {
	FT::map<char, int>	first;
	FT::map<char, int>	second;

	first['x'] = 8;
	first['y'] = 16;
	first['z'] = 32;

	second = first;
	first = FT::map<char, int>();

	std::cout << "Size first : " << first.size() << std::endl;
	std::cout << "Size second : " << second.size() << std::endl;
}

void	map_begin_end_test() {
	FT::map<char, int>	mapp;

	mapp['x'] = 8;
	mapp['y'] = 16;
	mapp['z'] = 32;
	std::cout << "Mapp contains :\n";
	for (FT::map<char, int>::iterator it = mapp.begin(); it != mapp.end(); ++it)
		std::cout << "[ " << it->first << " : " << it->second << " ]" << std::endl;
	std::cout << std::endl;

}

void	map_rbegin_rend_test() {
	FT::map<char, int>	mapp;

	mapp['x'] = 8;
	mapp['y'] = 16;
	mapp['z'] = 32;
	std::cout << "Mapp contains :\n";

	FT::map<char, int>::reverse_iterator rit = mapp.rbegin();
	FT::map<char, int>::reverse_iterator rit2 = mapp.rend();
	std::cout << "Beg. [ " << rit->first << " : " << rit->second << " ]" << std::endl;
	std::cout << "End. [ " << rit2->first << " : " << rit2->second << " ]" << std::endl;



	for (FT::map<char, int>::reverse_iterator rit = mapp.rbegin(); rit != mapp.rend(); ++rit) {
		std::cout << "yo " << std::endl;
		std::cout << "[ " << rit->first << " : " << rit->second << " ]" << std::endl;
	}
		std::cout << "yo2" << std::endl;
	std::cout << std::endl;
}

void	map_testing(void) {
	std::cout << "\033[1;36m/* ******** Map Constructor Test *********** */\033[0m" << std::endl;
	std::cout << std::endl;
	map_constructor_test();

	std::cout << std::endl;
	std::cout << "\033[1;36m/* ******** Map Operators Test ************* */\033[0m" << std::endl;
	std::cout << std::endl;
	map_operator_test();

	std::cout << std::endl;
	std::cout << "\033[1;36m/* ******** Map Begin/End Test ************* */\033[0m" << std::endl;
	std::cout << std::endl;
	map_begin_end_test();

	std::cout << std::endl;
	std::cout << "\033[1;36m/* ******** Map Rbegin/Rend Test *********** */\033[0m" << std::endl;
	std::cout << std::endl;
	map_rbegin_rend_test();

















}
