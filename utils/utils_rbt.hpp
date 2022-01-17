/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_rbt.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namenega <namenega@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 17:32:23 by namenega          #+#    #+#             */
/*   Updated: 2022/01/17 19:23:03 by namenega         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_RBT_HPP
# define UTILS_RBT_HPP

# include "utils.hpp"

namespace ft {
	template< class T >
	struct	Node {
		typedef	T	value_type;

		value_type		data;		/* Holds the key */
		int				color;		/* 1 = Red, 0 = Black */
		Node*			parent;		/* Pointer to the parent */
		Node*			left;		/* Pointer to the left child */
		Node*			right;		/* Pointer to the right child */

		/* ************************** Constructors ************************** */
		/*	Default */
		Node() : data(value_type()) {}
		Node(const value_type & val) : data(val) {}
		/*	Copy */
		Node(const Node & x) : data(x.data), parent(x.parent), left(x.left) {}
		/*	Destructor */
		~Node() {}
		/*	Operator= */
		Node &	operator=(const Node & x) {
			if (this != &x) {
				this->data = x.data;
				this->color = x.color;
				this->parent = x.parent;
				this->left = x.left;
				this->right = x.right;
			}
		}
	};

}

#endif
