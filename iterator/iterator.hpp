/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namenega <namenega@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 12:57:28 by namenega          #+#    #+#             */
/*   Updated: 2022/01/21 16:58:45 by namenega         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_HPP
# define ITERATOR_HPP

# include <iostream>
# include <cstddef> //ptrdiff_t
# include "../utils/utils.hpp"
# include "../utils/utils_rbt.hpp"

namespace ft {
	/* ********************************************************************** */
	/* ******************** Class Template std::iterator ******************** */
	/* ********************************************************************** */

	/*	From class Category */
	/* 	Empty classes to identify the category of an iterator as : */
	struct	input_iterator_tag {}; /* an input_iterator */
	struct	output_iterator_tag {}; /* 	an output_iterator. */
	struct	forward_iterator_tag : public input_iterator_tag {}; /* a forward iterator */
	struct	bidirectional_iterator_tag : public forward_iterator_tag {}; /* a bidirectional iterator */
	struct	random_access_iterator_tag : public bidirectional_iterator_tag {}; /* a random_access iterator */


	/*	Base class template that can be used to derive iterator classes from it.
		It is not an iterator class and does not provide any of the
		functionnality an iterator is expected to have. It only provides some
		member types. Needed for the default iterator_traits class template. */
	template< class Category, class T, class Distance = ptrdiff_t,
				class Pointer = T*, class Reference = T& >
	struct	iterator {
		typedef	T			value_type;
		typedef	Distance	difference_type;
		typedef	Pointer		pointer;
		typedef	Reference	reference;
		typedef Category	iterator_category;
	};
	
	/* ********************************************************************** */
	/* ***************** Class Template std::iterator_traits **************** */
	/* ********************************************************************** */

	/*	Traits class defining properties of iterators.
		Standard algorithm determine certain properties of the iterators passed
		to them and the range they represent by using the members of the
		corresponding iterator_traits instanciation. */
	template< class Iterator >
	struct	iterator_traits {
		typedef typename	Iterator::difference_type	difference_type;
		typedef typename	Iterator::value_type		value_type;
		typedef typename	Iterator::pointer			pointer;
		typedef typename	Iterator::reference			reference;
		typedef typename	Iterator::iterator_category	iterator_category;
	};

	template< class T >
	struct	iterator_traits< T* > {
		typedef ptrdiff_t						difference_type;
		typedef T								value_type;
		typedef T*								pointer;
		typedef T&								reference;
		typedef std::random_access_iterator_tag	iterator_category;
	};

	template< class T >
	struct	iterator_traits< const T* > {
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
			/*	Operator= */
			template< class U >
			reverse_iterator &	operator=(const reverse_iterator<U> & rev_it) {
				if (this != &rev_it) {
					this->current = rev_it.current;
				}
				return (*this);
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
	template< class Iterator, class Iterator2 >
	bool	operator==(const ft::reverse_iterator< Iterator >& lhs,
					const ft::reverse_iterator< Iterator2 >& rhs) {
		return (lhs.base() == rhs.base());
	}
	/*	Operator!= */
	template< class Iterator >
	bool	operator!=(const ft::reverse_iterator< Iterator >& lhs,
					const ft::reverse_iterator< Iterator >& rhs) {
		return (lhs.base() == rhs.base());
	}
	template< class Iterator, class Iterator2 >
	bool	operator!=(const ft::reverse_iterator< Iterator >& lhs,
					const ft::reverse_iterator< Iterator2 >& rhs) {
		return (lhs.base() == rhs.base());
	}
	/*	Operator< */
	template< class Iterator >
	bool	operator<(const ft::reverse_iterator< Iterator >& lhs,
					const ft::reverse_iterator< Iterator >& rhs) {
		return (lhs.base() > rhs.base());
	}
	template< class Iterator, class Iterator2 >
	bool	operator<(const ft::reverse_iterator< Iterator >& lhs,
					const ft::reverse_iterator< Iterator2 >& rhs) {
		return (lhs.base() > rhs.base());
	}
	/*	Operator<= */
	template< class Iterator >
	bool	operator<=(const ft::reverse_iterator< Iterator >& lhs,
					const ft::reverse_iterator< Iterator >& rhs) {
		return (lhs.base() >= rhs.base());
	}
	template< class Iterator, class Iterator2 >
	bool	operator<=(const ft::reverse_iterator< Iterator >& lhs,
					const ft::reverse_iterator< Iterator2 >& rhs) {
		return (lhs.base() >= rhs.base());
	}
	/*	Operator> */
	template< class Iterator >
	bool	operator>(const ft::reverse_iterator< Iterator >& lhs,
					const ft::reverse_iterator< Iterator >& rhs) {
		return (lhs.base() < rhs.base());
	}
	template< class Iterator, class Iterator2 >
	bool	operator>(const ft::reverse_iterator< Iterator >& lhs,
					const ft::reverse_iterator< Iterator2 >& rhs) {
		return (lhs.base() < rhs.base());
	}
	/*	Operator>= */
	template< class Iterator >
	bool	operator>=(const ft::reverse_iterator< Iterator >& lhs,
					const ft::reverse_iterator< Iterator >& rhs) {
		return (lhs.base() <= rhs.base());
	}
	template< class Iterator, class Iterator2 >
	bool	operator>=(const ft::reverse_iterator< Iterator >& lhs,
					const ft::reverse_iterator< Iterator2 >& rhs) {
		return (lhs.base() <= rhs.base());
	}
	/*	Operator+ */
	template< class Iterator >
	reverse_iterator<Iterator>	operator+(typename reverse_iterator<Iterator>::difference_type n,
										const reverse_iterator<Iterator>& it) {
		return (reverse_iterator<Iterator>(it.base() - n));
	}
	/*	Operator- */
	template < class Iterator >
    typename reverse_iterator<Iterator>::difference_type	operator-(const reverse_iterator<Iterator>& lhs,
																	const reverse_iterator<Iterator>& rhs) {
		return (rhs.base() - lhs.base());
	}
    template < class Iterator, class Iterator2 >
    typename reverse_iterator<Iterator>::difference_type	operator-(const reverse_iterator<Iterator>& lhs,
																	const reverse_iterator<Iterator2>& rhs) {
		return (rhs.base() - lhs.base());
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
			vector_iterator(pointer ptr = nullptr) : _node(ptr) {}
			/*	Copy */
			template< class V >
			vector_iterator(const vector_iterator<V>& x) : _node(x.base()) {}
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
				this->_node++;
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

	/* *************** Non Members Vector Iterator Functions **************** */
	// Operator==
	template< class T >
	bool	operator==(const ft::vector_iterator<T> & lhs, const ft::vector_iterator<T> & rhs) {
		return (lhs.base() == rhs.base());
	}
	template< class T, class U >
	bool	operator==(const ft::vector_iterator<T> & lhs, const ft::vector_iterator<U> & rhs) {
		return (lhs.base() == rhs.base());
	}

	// Operator !=
	template< class T >
	bool	operator!=(const ft::vector_iterator<T> & lhs, const ft::vector_iterator<T> & rhs) {
		return (lhs.base() != rhs.base());
	}
	template< class T, class U >
	bool	operator!=(const ft::vector_iterator<T> & lhs, const ft::vector_iterator<U> & rhs) {
		return (lhs.base() != rhs.base());
	}

	// Operator<
	template< class T >
	bool	operator<(const ft::vector_iterator<T> & lhs, const ft::vector_iterator<T> & rhs) {
		return (lhs.base() < rhs.base());
	}
	template< class T, class U >
	bool	operator<(const ft::vector_iterator<T> & lhs, const ft::vector_iterator<U> & rhs) {
		return (lhs.base() < rhs.base());
	}

	// Operator<=
	template< class T >
	bool	operator<=(const ft::vector_iterator<T> & lhs, const ft::vector_iterator<T> & rhs) {
		return (lhs.base() <= rhs.base());
	}
	template< class T, class U >
	bool	operator<=(const ft::vector_iterator<T> & lhs, const ft::vector_iterator<U> & rhs) {
		return (lhs.base() <= rhs.base());
	}

	// Operator>
	template< class T >
	bool	operator>(const ft::vector_iterator<T> & lhs, const ft::vector_iterator<T> & rhs) {
		return (lhs.base() > rhs.base());
	}
	template< class T, class U >
	bool	operator>(const ft::vector_iterator<T> & lhs, const ft::vector_iterator<U> & rhs) {
		return (lhs.base() > rhs.base());
	}

	// Operator>=
	template< class T >
	bool	operator>=(const ft::vector_iterator<T> & lhs, const ft::vector_iterator<T> & rhs) {
		return (lhs.base() >= rhs.base());
	}
	template< class T, class U >
	bool	operator>=(const ft::vector_iterator<T> & lhs, const ft::vector_iterator<U> & rhs) {
		return (lhs.base() >= rhs.base());
	}

	// Operator+
	template< class T >
	vector_iterator<T>	operator+(typename ft::vector_iterator<T>::difference_type n, const ft::vector_iterator<T> & iter) {
		return (vector_iterator<T>(iter.base() + n));
	}

	// Operator-
	template< class T >
	typename ft::vector_iterator<T>::diffrence_type	operator-(const vector_iterator<T> & lhs, const ft::vector_iterator<T> & rhs) {
		return (lhs.base() - rhs.base());
	}
	template< class T, class U >
	typename ft::vector_iterator<T>::difference_type	operator-(const vector_iterator<T> & lhs, const ft::vector_iterator<U> & rhs) {
		return (lhs.base() - rhs.base());
	}


	/* ********************************************************************** */
	/* **************************** Map Iterator **************************** */
	/* ********************************************************************** */

	template< typename T >
	class map_iterator {
		public:
			/* ************************ Member Types ************************ */
			typedef typename	ft::iterator_traits< ft::iterator< ft::bidirectional_iterator_tag, T> >::iterator_category	iterator_category;
			typedef typename	ft::iterator_traits< ft::iterator< ft::bidirectional_iterator_tag, T> >::value_type			value_type;
			typedef typename	ft::iterator_traits< ft::iterator< ft::bidirectional_iterator_tag, T> >::difference_type	difference_type;
			typedef typename	ft::iterator_traits< ft::iterator< ft::bidirectional_iterator_tag, T> >::pointer			pointer;
			typedef typename	ft::iterator_traits< ft::iterator< ft::bidirectional_iterator_tag, T> >::reference			reference;
			typedef				ft::Node< T >																				node_reference;
			typedef				ft::Node< T >*																				node_pointer;

			/* ************************ Constructors ************************ */
			/*	Default */
			map_iterator() : _node(u_nullptr), _end(u_nullptr) {}
			map_iterator(node_pointer node, node_pointer end) : _node(node), _end(end) {}

			/*	Copy */
			template< class U >
			map_iterator(const map_iterator< U >& x) : _node(x._node), _end(x._end) {}

			/*	Operator= */
			template< class U >
			map_iterator & operator=(const map_iterator & x) {
				if (this != &x) {
					this->_node = x._node;
					this->_end = x._end;
					this->_comp = x.comp;
				}
			}

			/*	Destructor */
			~map_iterator() {}

			/* ********************** Base & Operators ********************** */
			/*	Base - returns base iterator */
			node_pointer	base() const {
				return (this->_node);
			}
			/*	Operator* - Dereference iterator */
			reference	operator*() const {
				return (this->_node->data);
			}
			/*	Operator++ - Increment iterator position */
			map_iterator &		operator++(void) {
				node_pointer	cursor = _node;

				if (_node->right == _end) {
					cursor = _node->parent;
					while (cursor != u_nullptr && cursor != _end && cursor->data.first < _node->data.first)
						cursor = cursor->parent;
					if (cursor == 0)
						_node = _end;
					else
						_node = cursor;
				} else if (cursor == _end) {
					_node = _end;
				} else {
					cursor = _node->right;
					if (cursor == _end->parent && cursor->right == _end)
						_node = cursor;
					else {
						while (cursor->left != _end)
							cursor = cursor->left;
					}
					_node = cursor;
				}
				return (*this);
			}

			map_iterator			operator++(int) {
				map_iterator	tmp(*this);

				operator++();
				return (tmp);
			}
			/*	Operator-- - Decrease iterator opinion */
			map_iterator &		operator--(void) {
				node_pointer	cursor = _node;

				if (_node->left == _end) {
					cursor = _node->parent;
					while (cursor != u_nullptr && cursor != _end && cursor->data.first > _node->data.first)
						cursor = cursor->parent;
					_node = cursor;
					if (cursor == 0)
						_node = _end->right;
					else
						_node = cursor;
				} else if (cursor == _end) {
					_node = _end->right;
				} else {
					cursor = _node->left;
					if (cursor == _end->parent && cursor->left == _end)
						_node = cursor;
					else {
						while (cursor->right != _end)
							cursor = cursor->right;
					}
					_node = cursor;
				}
				return (*this);
			}

			map_iterator			operator--(int) {
				map_iterator	tmp(*this);

				operator--();
				return (tmp);
			}
			/*	Operator-> - Dereference iterator */
			pointer		operator->() const {
				return (&this->_node->data);
			}

		private:
			node_pointer	_node;
			node_pointer	_end;
	};
	
	/* *************** Non Members Map Iterator Functions **************** */
	template< class T >
	bool	operator==(const ft::map_iterator< T >& lhs, const ft::map_iterator< T >& rhs) {
		return (lhs.base() == rhs.base());
	}
	template< class T, class U >
	bool	operator==(const ft::map_iterator< T >& lhs, const ft::map_iterator< U >& rhs) {
		return (lhs.base() == rhs.base());
	}
	template< class T >
	bool	operator!=(const ft::map_iterator< T >& lhs, const ft::map_iterator< T >& rhs) {
		return (lhs.base() != rhs.base());
	}
	template< class T, class U >
	bool	operator!=(const ft::map_iterator< T >& lhs, const ft::map_iterator< U >& rhs) {
		return (lhs.base() != rhs.base());
	}
}

#endif
