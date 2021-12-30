/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namenega <namenega@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 12:45:40 by namenega          #+#    #+#             */
/*   Updated: 2021/12/30 18:48:51 by namenega         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	VECTOR_HPP
# define VECTOR_HPP

# include <memory>
# include "../iterator/iterator.hpp"

namespace ft {
	template< class T, class Alloc = std::allocator<T> >
	class vector {
		private:
			size_type		_size; //size_type = long unsigned int
			size_type		_capacity;
			pointer			_ptr;
			allocator_type	_base;

		public:
			/* ************************** Typedef *************************** */
			typedef				T													value_type;
			typedef				Alloc												allocator_type;
			typedef				size_t												size_type;
			typedef typename	allocator_type::reference							reference;
			typedef typename	allocator_type::const_reference						const_reference;
			typedef typename	allocator_type::pointer								pointer;
			typedef typename	allocator_type::const_pointer						const_pointer;

			typedef				ft::vector_iterator< value_type >					iterator;
			typedef				ft::vector_iterator< const value_type >				const_iterator;
			typedef				ft::reverse_iterator< iterator >					reverse_iterator;
			typedef				ft::reverse_iterator< const_iterator >				const_reverse_iterator;
			typedef typename	ft::iterator_traits< iterator >::difference_type	difference_type;

			/* ************************************************************** */
			/* ****************** Constructors, Destructors ***************** */
			/* ************************************************************** */

			/* ************************** Default *************************** */
			/*	Constructs an empty container, with no elements */
			explicit	vector(const allocator_type& alloc = allocator_type()) :
			_size(0), _capacity(0), _base(alloc) {
				this->_ptr = this->_base.allocate(0);
			}

			/* **************************** Fill **************************** */
			/*	Constructs a container with n elements.
				Each element is a copy of val */
			explicit	vector(size_t n, const value_type& val = value_type(),
							const allocator_type& alloc = allocator_type()) :
			_size(n), _capacity(n), _base(alloc) {
				this->_ptr = this->_base.allocate(n);
				for (size_t i; i < n; i++) {
					this->_base.construct(this->_ptr + i, val);
				}
			}

			/* *************************** Range **************************** */
			/*	Constructs a container with as many elements as the range
				[first, last] with each element constructed from
				its corresponding in that range, in the same order. */
			template < class InputIterator >
			vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type(),
				typename ft::enable_if< !ft::is_integral< InputIterator >::value,
				InputIterator>::type* = nullptr) :
			_size(0), _capacity(0), _base(alloc) {
				while (first < last) {
					this->_size++;
					first++;
				}
				this->_capacity = this->_size;
				this->_ptr = this->_base.allocate(this->_size);
				for (size_t i = 0; i < this->_size; i++)
					this->_base.construct(this->_ptr + i, *(first + i));
			}

			/* **************************** Copy **************************** */
			/*	Constructs a container with a copy of each of the elements
				in x, in the same order */
			vector (const vector & x) {

			}

			/* ************************* Destructor ************************* */
			/*	Destroys all container elements, and deallocates
				all the storage capacity allocated by the vector using
				its allocator */
			virtual ~vector() {

			}

			/* ************************** Operator= ************************* */
			/*	Copies all the elements from x into the container.
				The container preserves its current allocator, which is used
				to allocate storage in case of reallocation. */
			vector&		operator=(const vector & x) {

			}


			/* ************************************************************** */
			/* ************************** Iterators ************************* */
			/* ************************************************************** */

			/* ************************** Begin() *************************** */
			/*	Return an iterator pointing to the 1st element in the vector.
				If the container is empty, the returned iterator value shall not
				be dereferenced */
			iterator	begin() {
				return (iterator(this->_ptr));
			}

			const_iterator	begin() const {

			}

			/* **************************** End() *************************** */
			/*	Returns an iterator reffering to the past-the-end
				in the vector container. The p-t-e element is the theoretical
				element that would follow the last element in the vector.
				It does not point to any element, and thus shall not be
				dereferenced.
				If the container is empty, the function returns the same
				as vector::begin(). */
			iterator	end() {

			}

			const_iterator	end() const {

			}

			/* ************************** Rbegin() ************************** */
			/*	Returns a reverse iterator pointing to the last element
				in the vector right before the one pointed by end().
				It iterates backwards. */
			reverse_iterator	rbegin() {
				
			}

			const_reverse_iterator	rbegin() const {

			}

			/* *************************** Rend() *************************** */
			/*	Returns a reverse iterator pointing to the theoretical element
				preceding the first element in the vector. */
			reverse_iterator	rend() {

			}

			const_reverse_iterator	rend() const {

			}

			
			/* ************************************************************** */
			/* ************************** Capacity ************************** */
			/* ************************************************************** */

			/* *************************** Size() *************************** */
			/*	Returns the number of elements in the vector (which is not
				necessarily equal to its storage capacity!) */
			size_type	size() const {

			}

			/* ************************* MaxSize() ************************** */
			/*	Returns the maximum number of elements that the vector
				can hold. It is the maximum potential size the container
				can reach due to known systeem or library implementation
				limitations. */
			size_type	max_size() const {

			}

			/* ************************** Resize() ************************** */
			/*	Resizes the container so that it contains n elements.
				If n is smaller than the current size, the content is reduced
				to its first n elements, removing those beyond (+ destroy).
				If n is greater than current container size, the content
				is expanded by inserting at the end as many elements
				as needed to reach a size of n.
				If val is specified, the new elements are initialized
				as copies of val.
				If n is also greater than CAPACITY, an automatic reallocation
				of the allocated storage space takes place. */
			void	resize(size_type n, value_type val = value_type()) {

			}

			/* ************************* Capacity() ************************* */
			/*	Return the size of the storage space currently allocated
				for the vector, expressed in terms of elements. It can be
				equal or greater than the vector SIZE*/
			__SIZE_TYPE__	capacity() const {

			}

			/* *************************** Empty() ************************** */
			/*	Returns whether the vector is empty or not. */
			bool	empty() const {

			}

			/* ************************** Reserve() ************************* */
			/*	Requests that the vector capacity be at least enough
				to contain n elements. If n is greater than the current vector
				capacity, the function causes the container to reallocate
				its storage increasing its capacity to n (or greater).
				No effect on the vector size/elements. */
			void	reserve(size_type n) {

			}


			/* ************************************************************** */
			/* *********************** Elements Access ********************** */
			/* ************************************************************** */

			/* ************************ Operator[]() ************************ */
			/*	Returns a reference to the element at position n in the vector
				container. Similar as at() except at() is bound-checked and
				signals if the request position is out of range
				by throwing an exception. */
			reference	operator[](size_type n) {

			}

			const_reference	operator[](size_type n) const {
				
			}

			/* **************************** At() **************************** */
			/*	Returns a reference to the element at position n in the vector.
				The function checks whether n is within the bounds of
				valid elements in the vector, throwing an out_of_range
				exception if not. */
			reference	at(size_type n) {

			}

			const_reference	at(size_type n) const {

			}

			/* ************************** Front() *************************** */
			/*	Returns a reference to the first element in the vector.
				Unlike begin(), which returns an iterator to the same element,
				this function returns a direct reference. Calling on an empty
				container causes undefined behaviour. */
			reference	front() {

			}

			const_reference	front() const {

			}

			/* *************************** Back() *************************** */
			/*	Returns a reference to the last element in the vector.
				Unlike end(), which returns an iterator just past this element,
				this function returns a direct reference. Calling on an empty
				container causes undefined behaviour. */
			reference	back() {

			}

			const_reference	back() const {

			}


			/* ************************************************************** */
			/* ************************** Modifiers ************************* */
			/* ************************************************************** */

			/* ************************** Assign() ************************** */
			/*	Assign new contents to the vector, replacing its current
				contents and modifying its size accordingly.  Any elements held
				in the container before the call are destroyed and replaced
				by newly constructed elements. This causes an reallocation of
				the allocated storage space if the new vector size
				surpasses the current vector capacity. */
			/*	Range - The new contents are elements constructed from each of
				the elements on the range between first and last,
				in the same order. */
			template< class InputIterator >
			void	assign(InputIterator first, InputIterator last) {

			}

			/*	Fill - The new contents are n elements, each initialized to
				a copy of val. */
			void	assign(size_type n, const value_type& val) {

			}

			/* ************************* Push_back() ************************ */
			/*	Adds a new element at the end of the vector, after
				its current last element. The content of val is copied
				(or moved) to new element. This increases the container size
				by 1, which causes a reallocation of the allocated storage space
				if the new vector size surpasses the current vector capacity. */
			void	push_back(const value_type& val) {

			}

			/* ************************* Pop_back() ************************* */
			/*	Removes the last element in the vector, effectively reducing
				the container size by 1. This destroys the removed element. */
			void	pop_back() {

			}

			/* ************************** Insert() ************************** */
			/*	The vector is extended by inserting new elements before
				the element at the specified position, effectively increasing
				the container size by the number of elements inserted. This
				causes a reallocation of the allocated storage space if
				the new vector size surpasses the current vector capacity. */
			/*	Single element */
			iterator	insert(iterator position, const value_type& val) {

			}

			/*	Fill */
			void	insert(iterator position, size_type n, const value_type& val) {

			}

			/*	Range */
			template< class InputIterator >
			void	insert(iterator position, InputIterator first, InputIterator last) {
				
			}
			
			/* ************************** Erase() *************************** */
			/*	Removes from the vector a single element (position). This
				effectively reduces the container size by the number of
				the elements removed, which are destroyed. */
			iterator	erase(iterator position) {

			}

			/*	Removes from the vector a range of elements ([first, last]). */
			iterator	erase(iterator first, iterator last) {

			}

			/* *************************** Swap() *************************** */
			/*	Exchange the content of the container vy the content of x,
				which is another vector object of the same type.
				Sizes may differ. After the call, the elements in this
				container are those which were in x before, and the elements
				of x are those which where in this. (clear+realloc)*/
			void	swap(vector& x) {

			}

			/* ************************** Clear() *************************** */
			/*	Removes all elements from the vector (which are destroyed),
				leaving the container with a size of 0.
				No reallocation, no change of capacity */
			void	clear() {

			}


			/* ************************************************************** */
			/* ************************** Allocator ************************* */
			/* ************************************************************** */

			/* *********************** Get_allocator() ********************** */
			/*	Returns a copy of the allocator object associated with
				the vector. */
			allocator_type	get_allocator() const {

			}
	};


	/* ********************************************************************** */
	/* ************************ Non Member Operators ************************ */
	/* ********************************************************************** */

	/* **************************** Operator==() **************************** */
	/*	Check if the content of lhs and rhs are equal. If they have
		the same number of elements and each elements in lhs compares equal
		with elements in rhs at the same position.
		Return true if they are equal. */

	template< class T, class Alloc >
	bool	operator==(	const vector< T, Alloc >& lhs,
						const vector< T, Alloc >& rhs) {

	}

	/* **************************** Operator!=() **************************** */
	/*	Check if the content of lhs and rhs are different.
		Return true if they are not equal. */
	template< class T, class Alloc >
	bool	operator!=(	const vector< T, Alloc >& lhs,
						const vector< T, Alloc >& rhs) {

	}

	/* **************************** Operator<() ***************************** */
	/*	Compares the content of lhs and rhs lexicographically.
		Returns true if lhs < rhs */
	template< class T, class Alloc >
	bool	operator<(	const vector< T, Alloc >& lhs,
						const vector< T, Alloc >& rhs) {

	}

	/* **************************** Operator<=() **************************** */
	/*	Compares the content of lhs and rhs lexicographically.
		Returns true if lhs <= rhs */
	template< class T, class Alloc >
	bool	operator<=(	const vector< T, Alloc >& lhs,
						const vector< T, Alloc >& rhs) {

	}

	/* **************************** Operator>() ***************************** */
	/*	Compares the content of lhs and rhs lexicographically.
		Returns true if lhs > rhs */
	template< class T, class Alloc >
	bool	operator>(	const vector< T, Alloc >& lhs,
						const vector< T, Alloc >& rhs) {

	}

	/* **************************** Operator>=() **************************** */
	/*	Compares the content of lhs and rhs lexicographically.
		Returns true if lhs >= rhs */
	template< class T, class Alloc >
	bool	operator>=(	const vector< T, Alloc >& lhs,
						const vector< T, Alloc >& rhs) {

	}


	/* ********************************************************************** */
	/* ************************ Non Member Functions ************************ */
	/* ********************************************************************** */

	/* ******************************* Swap() ******************************* */
	/*	The contents of container x are exchanged with thos of y. Both container
		objects must be of the same type, although size may differ.
		This is an overload of the generic algorithm swap() that improves
		its performance by mutually transferring ownership over their assets
		to the other container.
		Same as x.swap(y) */
	template< class T, class Alloc >
	void	swap(vector< T, Alloc >& x, vector< T, Alloc >& y) {
		x.swap(y);
	}
}


#endif
