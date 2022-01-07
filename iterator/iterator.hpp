/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namenega <namenega@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 12:57:28 by namenega          #+#    #+#             */
/*   Updated: 2022/01/07 15:30:38 by namenega         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_HPP
# define ITERATOR_HPP

# include <iostream>
# include <cstddef> //ptrdiff_t
# include "../utils/utils.hpp"

namespace ft {
	/* ********************************************************************** */
	/* ******************** Class Template std::iterator ******************** */
	/* ********************************************************************** */

	/*	Base class template that can be used to derive iterator classes from it.
		It is not an iterator class and does not provide any of the
		functionnality an iterator is expected to have. It only provides some
		member types. Needed for the default iterator_traits class template */
	template< class Category, class T, class Distance = ptrdiff_t,
				class Pointer = T*, class Reference = T& >
	class	iterator {
		typedef	T			value_type;
		typedef	Distance	difference_type;
		typedef	Pointer		pointer;
		typedef	Reference	reference;
		typedef Category	iterator_category;
	};

	/*	From class Category */
	/* 	Empty classes to identify the category of an iterator as : */
	struct	input_iterator_tag {}; /* an input_iterator */
	struct	output_iterator_tag {}; /* 	an output_iterator. */
	struct	forward_iterator_tag : public input_iterator_tag {}; /* a forward iterator */
	struct	bidirectional_iterator_tag : public forward_iterator_tag {}; /* a bidirectional iterator */
	struct	random_access_iterator_tag : public bidirectional_iterator_tag {}; /* a random_access iterator */

	
	/* ********************************************************************** */
	/* ***************** Class Template std::iterator_traits **************** */
	/* ********************************************************************** */

	/*	Traits class defining properties of iterators.
		Standard algorithm determine certain properties of the iterators passed
		to them and the range they represent by using the members of the
		corresponding iterator_traits instantiation. */
	template< class Iterator >
	class	iterator_traits {
		typedef typename	Iterator::difference_type	difference_type;
		typedef typename	Iterator::value_type		value_type;
		typedef typename	Iterator::pointer			pointer;
		typedef typename	Iterator::reference			reference;
		typedef typename	Iterator::iterator_category	iterator_category;
	};

	template< class T >
	class	iterator_traits< T* > {
		typedef ptrdiff_t						difference_type;
		typedef T								value_type;
		typedef T*								pointer;
		typedef T&								reference;
		typedef std::random_access_iterator_tag	iterator_category;
	};

	template< class T >
	class	iterator_traits< const T* > {
		typedef	ptrdiff_t						difference_type;
		typedef	T								value_type;
		typedef const T*						pointer;
		typedef const T&						reference;
		typedef std::random_access_iterator_tag	iterator_category;
	};


	/* ********************************************************************** */
	/* **************** Class Template std::reverse_iterator **************** */
	/* ********************************************************************** */

	/*	This class reverses the direction in which a bidirectionnal or
		random_access iterator iterates through a range. */
	template< class Iterator >
	class	reverse_iterator {
		public:
			/* ************************ Member Types ************************ */
			typedef 			Iterator											iterator_type;
			typedef typename	ft::iterator_traits<Iterator>::iterator_category	iterator_category;
			typedef typename	ft::iterator_traits<Iterator>::value_type			value_type;
			typedef typename	ft::iterator_traits<Iterator>::difference_type		difference_type;
			typedef typename	ft::iterator_traits<Iterator>::pointer				pointer;
			typedef typename	ft::iterator_traits<Iterator>::reference			reference;
			
			/* ************************ Constructors ************************ */
			/*	Default Constructor */
			reverse_iterator() : current() {
			};
			/*	Initialization */
			explicit	reverse_iterator(iterator_type it) : current(it) {
			}
			/*	Copy */
			template< class Iter >
			reverse_iterator(const reverse_iterator<Iter>& rev_it) : current(rev_it.base()) {
			}

			/* ********************** Operators & Base ********************** */
			/*	Base - returns base iterator */
			iterator_type	base() const {
				return (Iterator(this->current));
			}
			/*	Operator* - Dereference iterator */
			reference	operator*() const {
				Iterator	tmp = this->current;
				return (*--tmp);
			}
			/*	Operator+ - Addition operator */
			reverse_iterator	operator+(difference_type n) const {
				return (reverse_iterator(current - n));
			}
			/*	Operator++ - Increment iterator position */
			reverse_iterator&	operator++() {
				this->current--;
				return (*this);
			}

			reverse_iterator	operator++(int) {
				reverse_iterator	tmp = *this;
				this->current--;
				return (tmp);
			}
			/*	Operator+= - Advance iterator */
			reverse_iterator&	operator+=(difference_type n) {
				this->current -= n;
				return (*this);
			}
			/*	Operator- - Substraction iterator */
			reverse_iterator	operator-(difference_type n) const {
				return (reverse_iterator(current + n));
			}
			/*	Operator-- - Decrease iterator opinion */
			reverse_iterator&	operator--() {
				this->current++;
				return (*this);
			}

			reverse_iterator	operator--(int) {
				reverse_iterator	tmp = *this;
				this->current++;
				return (*this);
			}
			/*	Operator-= - Retrocede iterator */
			reverse_iterator&	operator-=(difference_type n) {
				this->current += n;
				return (*this);
			}
			/*	Operator-> - Dereference iterator */
			pointer				operator->() const {
				return (&(reverse_iterator::operator*()));
			}
			/*	Operator[] - Dereference iterator with offset */
			reference			operator[](difference_type n) const {
				return (this->base()[-n - 1]);
			}
		protected:
			iterator_type	current;
	};

	/* *************** Non Members Reverse Iterator Functions *************** */
	/*	Operator== */
	template< class Iterator >
	bool	operator==(const ft::reverse_iterator< Iterator >& lhs,
					const ft::reverse_iterator< Iterator >& rhs) {
		return (lhs.base() == rhs.base());
	}
	/*	Operator!= */
	template< class Iterator >
	bool	operator!=(const ft::reverse_iterator< Iterator >& lhs,
					const ft::reverse_iterator< Iterator >& rhs) {
		return (lhs.base() == rhs.base());
	}
	/*	Operator< */
	template< class Iterator >
	bool	operator<(const ft::reverse_iterator< Iterator >& lhs,
					const ft::reverse_iterator< Iterator >& rhs) {
		return (lhs.base() > rhs.base());
	}
	/*	Operator<= */
	template< class Iterator >
	bool	operator<=(const ft::reverse_iterator< Iterator >& lhs,
					const ft::reverse_iterator< Iterator >& rhs) {
		return (lhs.base() >= rhs.base());
	}
	/*	Operator> */
	template< class Iterator >
	bool	operator>(const ft::reverse_iterator< Iterator >& lhs,
					const ft::reverse_iterator< Iterator >& rhs) {
		return (lhs.base() < rhs.base());
	}
	/*	Operator>= */
	template< class Iterator >
	bool	operator>=(const ft::reverse_iterator< Iterator >& lhs,
					const ft::reverse_iterator< Iterator >& rhs) {
		return (lhs.base() <= rhs.base());
	}


	/* ********************************************************************** */
	/* *************************** Vector Iterator ************************** */
	/* ********************************************************************** */

	template< class T >
	class	vector_iterator {
		public:
			/* ************************ Member Types ************************ */
			typedef typename ft::iterator_traits< T* >::iterator_category	iterator_category;
			typedef typename ft::iterator_traits< T* >::value_type			value_type;
			typedef typename ft::iterator_traits< T* >::difference_type		difference_type;
			typedef typename ft::iterator_traits< T* >::pointer				pointer;
			typedef typename ft::iterator_traits< T* >::reference			reference;

			/* ************************ Constructors ************************ */
			/*	 Default */
			vector_iterator(pointer ptr = nullptr) : _node(ptr) {
			}
			/*	Copy */
			template< class V >
			vector_iterator(const vector_iterator< V >& x) : _node(x.base()) {
			}
			/*	Destructor */
			~vector_iterator() {
				_node = nullptr;
			}

			/* ********************** Base & Operators ********************** */
			/*	Base - returns base iterator */
			pointer	base() const {
				return (this->_node);
			}
			/*	Operator* - Dereference iterator */
			reference	operator*() const {
				return (*this->_node);
			}
			/*	Operator+ - Addition operator */
			vector_iterator	operator+(difference_type n) const {
				vector_iterator	tmp = *this;
				return (tmp += n);
			}
			/*	Operator++ - Increment iterator position */
			vector_iterator&	operator++() {
				this->node++;
				return (*this);
			}

			vector_iterator	operator++(int) {
				vector_iterator	tmp = *this;
				++(*this);
				return (tmp);
			}
			/*	Operator+= - Advance iterator */
			vector_iterator&	operator+=(difference_type n) {
				this->_node += n;
				return (*this);
			}
			/*	Operator- - Substraction iterator */
			vector_iterator	operator-(difference_type n) const {
				vector_iterator	tmp = *this;
				return (tmp -= n);
			}
			/*	Operator-- - Decrease iterator opinion */
			vector_iterator&	operator--() {
				this->_node--;
				return (*this);
			}

			vector_iterator	operator--(int) {
				vector_iterator	tmp = *this;
				--(*this);
				return (tmp);
			}
			/*	Operator-= - Retrocede iterator */
			vector_iterator&	operator-=(difference_type n) {
				this->_node -= n;
				return (*this);
			}
			/*	Operator-> - Dereference iterator */
			pointer	operator->() const {
				return (this->_node);
			}
			/*	Operator[] - Dereference iterator with offset */
			reference	operator[](difference_type n) const {
				return *(this->_node + n);
			}

		private:
			pointer	_node;
	};
};

#endif
