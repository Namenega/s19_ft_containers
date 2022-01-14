/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namenega <namenega@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 13:10:18 by namenega          #+#    #+#             */
/*   Updated: 2022/01/14 15:16:12 by namenega         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_HPP
# define STACK_HPP

# include "../vector/vector.hpp"
# include <iostream>

namespace ft {
	template< class T, class Container = ft::vector<T> >
	class stack {
		public:
			/* ************************** Typedef *************************** */
			typedef T			value_type;
			typedef Container	container_type;
			typedef size_t		size_type;

			/* ************************************************************** */
			/* ****************** Constructors, Destructors ***************** */
			/* ************************************************************** */
			/*	Constructs a stack container adaptor object.
				A container adaptor keeps internally a container object as data.
				This contaainer object is a copy of the ctnr arg passed to the
				constructor, if any, otherwise it is an empty container. */
			explicit	stack(const container_type& ctnr = container_type()) : _c(ctnr) {}
			
			/*	Destructor */
			virtual		~stack() {};

			/* ************************** Operator= ************************* */
			stack &		operator=(const stack & x) {
				if (this != &x)
					this->_c = x.c;
				return (*this);
			}

			/* ************************************************************** */
			/* ********************** Member functions ********************** */
			/* ************************************************************** */
			/*	Returns wether the stack is empty. */
			bool	empty(void) const {
				return (this->_c.empty());
			}

			/*	Return the number of elements in the stack. */
			size_type	size() const {
				return (this->_c.size());
			}

			/*	Returns a reference to the top element in the stack. Since stack
				are last-in first-out containers, the top element is the last
				element inserted into the stack. */
			value_type &	top() {
				return (this->_c.back());
			}

			const value_type &	top() const {
				return (this->_c.back());
			}

			/*	Insert a new element at the top of the stack, above its current
			top element. The content of this new element is initialized to
			a copy of 'val'. */
			void	push(const value_type & val) {
				return (this->_c.push_back(val));
			}

			/*	Removes the element on top of the stack, effectively reducing
				its size by one. The element removed is the latest element
				inserted into the stack. */
			void	pop(void) {
				return (this->_c.pop_back());
			}
		private:
			/* ************************************************************** */
			/* ******************** Non Member functions ******************** */
			/* ************************************************************** */
			/*	Use of friend because we use the member _c. */
			friend bool	operator==(const stack< T, Container >& lhs, const stack< T, Container >& rhs) {
				return (lhs._c == rhs._c); }
			friend bool	operator!=(const stack< T, Container >& lhs, const stack< T, Container >& rhs) {
				return (lhs._c != rhs._c); }
			friend bool	operator<(const stack< T, Container >& lhs, const stack< T, Container >& rhs) {
				return (lhs._c < rhs._c); }
			friend bool	operator<=(const stack< T, Container >& lhs, const stack< T, Container >& rhs) {
				return (lhs._c <= rhs._c); }
			friend bool	operator>(const stack< T, Container >& lhs, const stack< T, Container >& rhs) {
				return (lhs._c > rhs._c); }
			friend bool	operator>=(const stack< T, Container >& lhs, const stack< T, Container >& rhs) {
				return (lhs._c >= rhs._c); }
		protected:
			container_type	_c;
	};
}

void	stack_testing(void);

#endif
