/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namenega <namenega@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 12:45:40 by namenega          #+#    #+#             */
/*   Updated: 2022/01/01 17:13:47 by namenega         ###   ########.fr       */
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
			vector (const vector & x) :
			_size(x._size), _capacity(x._capacity), _base(x._base) {
				this->_ptr = this->_base.allocate(0);
				*this = x;
			}

			/* ************************* Destructor ************************* */
			/*	Destroys all container elements, and deallocates
				all the storage capacity allocated by the vector using
				its allocator */
			virtual ~vector() {
				this->clear();
				this->_base.deallocate(this->_ptr, this->_capacity);
			}

			/* ************************** Operator= ************************* */
			/*	Copies all the elements from x into the container.
				The container preserves its current allocator, which is used
				to allocate storage in case of reallocation. */
			vector&		operator=(const vector & x) {
				if (this != &x) {
					this->clear();
					this->_base.deallocate(this->_ptr, this->_capacity);
					this->_ptr = this->_base.allocate(x._capacity);
					for (size_t i = 0; i < x._size; i++)
						this->_base.construct(this->_ptr + i, *(x._ptr + i));
					this->_size = x._size;
					this->_capacity = x._capacity;
				}
				return (*this);
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
				return (const_iterator(this->_ptr));
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
				return (iterator(this->_ptr + this->_size))
			}

			const_iterator	end() const {
				return (const_iterator(this->_ptr + this->_size))
			}

			/* ************************** Rbegin() ************************** */
			/*	Returns a reverse iterator pointing to the last element
				in the vector right before the one pointed by end().
				It iterates backwards. */
			reverse_iterator	rbegin() {
				return (reverse_iterator(this->_ptr + this->_size));
			}

			const_reverse_iterator	rbegin() const {
				return (const_reverse_iterator(this->_ptr + this->_size));
			}

			/* *************************** Rend() *************************** */
			/*	Returns a reverse iterator pointing to the theoretical element
				preceding the first element in the vector. */
			reverse_iterator	rend() {
				return (reverse_iterator(this->_ptr));
			}

			const_reverse_iterator	rend() const {
				return (const_reverse_iterator(this->_ptr));
			}

			
			/* ************************************************************** */
			/* ************************** Capacity ************************** */
			/* ************************************************************** */

			/* *************************** Size() *************************** */
			/*	Returns the number of elements in the vector (which is not
				necessarily equal to its storage capacity!) */
			size_type	size() const {
				return (this->_size);
			}

			/* ************************* MaxSize() ************************** */
			/*	Returns the maximum number of elements that the vector
				can hold. It is the maximum potential size the container
				can reach due to known systeem or library implementation
				limitations. */
			size_type	max_size() const {
				return (this->_base.max_size());
			}

			/* ************************** Resize() ************************** */
			/*	Resizes the container so that it contains n elements.
				1. If n is smaller than the current size, the content is reduced
				to its first n elements, removing those beyond (+ destroy).
				2. If n is greater than current container size, the content
				is expanded by inserting at the end as many elements
				as needed to reach a size of n.
				If val is specified, the new elements are initialized
				as copies of val.
				3. If n is also greater than CAPACITY, an automatic reallocation
				of the allocated storage space takes place. */
			void	resize(size_type n, value_type val = value_type()) {
				if (n < this->_size) {
					for (size_t i = n; i < this->_size; i++)
						this->_base.destroy(this->_ptr + i);
				}
				else if (n > this->_size && n <= this->_capacity) {
					for (size_t i = this->_size; i < n; i++)
						this->_base.construct(this->_ptr + i, val);
				}
				else if (n > this->_size && n > this->_capacity) {
					if (n < this->_capacity * 2)
						reserve(this->_capacity * 2);
					else
						reserve(n);
					for (size_t i = this->_size; i < n; i++)
						this->_base.construct(this->_ptr + i, val);
				}
			}

			/* ************************* Capacity() ************************* */
			/*	Return the size of the storage space currently allocated
				for the vector, expressed in terms of elements. It can be
				equal or greater than the vector SIZE*/
			__SIZE_TYPE__	capacity() const {
				return (this->_capacity);
			}

			/* *************************** Empty() ************************** */
			/*	Returns whether the vector is empty or not. */
			bool	empty() const {
				if (this->_size == 0)
					return (true);
				return (false);
			}

			/* ************************** Reserve() ************************* */
			/*	Requests that the vector capacity be at least enough
				to contain n elements. If n is greater than the current vector
				capacity, the function causes the container to reallocate
				its storage increasing its capacity to n (or greater).
				No effect on the vector size/elements. */
			void	reserve(size_type n) {
				if (n > this->_capacity) {
					vector	tmp;

					tmp = *this;
					this->clear();
					this->_base.deallocate(this->_ptr, this->_capacity);
					this->_ptr = this->_base.allocate(n);
					for (size_t i = 0; i < tmp._size; i++)
						this->_base.construct(this->_ptr + i, *(tmp._ptr + i));
					this->_size = tmp._size;
					this->_capacity = n;
				}
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
				return (this->_ptr[n]);
			}

			const_reference	operator[](size_type n) const {
				return (this->_ptr[n]);
			}

			/* **************************** At() **************************** */
			/*	Returns a reference to the element at position n in the vector.
				The function checks whether n is within the bounds of
				valid elements in the vector, throwing an out_of_range
				exception if not. */
			reference	at(size_type n) {
				if (n >= this->_size)
					throw std::out_of_range("Vector at().");
				return (*(this->_ptr[n]));
			}

			const_reference	at(size_type n) const {
				if (n >= this->_size)
					throw std::out_of_range("Vector const at().");
				return (*(this->_ptr[n]));
			}

			/* ************************** Front() *************************** */
			/*	Returns a reference to the first element in the vector.
				Unlike begin(), which returns an iterator to the same element,
				this function returns a direct reference. Calling on an empty
				container causes undefined behaviour. */
			reference	front() {
				return (*this->_ptr);
			}

			const_reference	front() const {
				return (*this->_ptr);
			}

			/* *************************** Back() *************************** */
			/*	Returns a reference to the last element in the vector.
				Unlike end(), which returns an iterator just past this element,
				this function returns a direct reference. Calling on an empty
				container causes undefined behaviour. */
			reference	back() {
				return (*(this->_ptr + this->_size - 1));
			}

			const_reference	back() const {
				return (*(this->_ptr + this->_size - 1));
			}


			/* ************************************************************** */
			/* ************************** Modifiers ************************* */
			/* ************************************************************** */

			/* ************************** Assign() ************************** */
			/*	Assign new contents to the vector, replacing its current
				contents and modifying its size accordingly. Any elements held
				in the container before the call are destroyed and replaced
				by newly constructed elements. This causes an reallocation of
				the allocated storage space if the new vector size
				surpasses the current vector capacity. */
			/*	Range - The new contents are elements constructed from each of
				the elements on the range between first and last,
				in the same order. */
			template< class InputIterator >
			void	assign(InputIterator first, InputIterator last,
					typename ft::enable_if< !ft::is_integral< InputIterator >::value,
					InputIterator>::type* = nullptr) {
				this->clear();
				this->insert(begin(), first, last);
				this->_capacity = this->_size;
			}

			/*	Fill - The new contents are n elements, each initialized to
				a copy of val. */
			void	assign(size_type n, const value_type& val) {
				this->clear();
				for  (size_t i = 0; i < n; i++)
					push_back(val);
			}

			/* ************************* Push_back() ************************ */
			/*	Adds a new element at the end of the vector, after
				its current last element. The content of val is copied
				(or moved) to new element. This increases the container size
				by 1, which causes a reallocation of the allocated storage space
				if the new vector size surpasses the current vector capacity. */
			void	push_back(const value_type& val) {
				resize(this->_size + 1, val);
			}

			/* ************************* Pop_back() ************************* */
			/*	Removes the last element in the vector, effectively reducing
				the container size by 1. This destroys the removed element. */
			void	pop_back() {
				resize(this->size - 1, value_type());
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
