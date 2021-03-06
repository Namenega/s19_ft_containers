/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namenega <namenega@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/15 22:02:18 by namenega          #+#    #+#             */
/*   Updated: 2022/01/24 17:29:10 by namenega         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
# define MAP_HPP

# include "../iterator/iterator.hpp"
# include "../utils/utils.hpp"
# include "../utils/utils_rbt.hpp"


namespace ft {
	template< class Key, class T, class Compare = ft::less<Key>, class Alloc =
			std::allocator<ft::pair<const Key, T> > >
	class map {
		public:
			/* ************************** Typedef *************************** */
			typedef				Key															key_type;
			typedef				T															mapped_type;
			typedef				ft::pair<const key_type, mapped_type>						value_type;
			typedef				ptrdiff_t													difference_type;
			/*	Member type key_compare is the internal comparison object type
				used by the container. */
			typedef				Compare														key_compare;
			/*	Member type allocator_type is the internal allocator type used
				by the container */
			typedef				Alloc														allocator_type;
			typedef				size_t														size_type;
			typedef				value_type &												reference;
			typedef				const value_type &											const_reference;
			typedef typename	allocator_type::pointer										pointer;
			typedef typename	allocator_type::const_pointer								const_pointer;

			typedef				ft::map_iterator< value_type >								iterator;
			typedef				ft::map_iterator< value_type >								const_iterator;
			typedef				ft::reverse_iterator< iterator >							reverse_iterator;
			typedef				ft::reverse_iterator< const_iterator >						const_reverse_iterator;
			typedef typename	allocator_type::template rebind< Node<value_type> >::other	node_allocator;

			class	value_compare : ft::binary_function<value_type, value_type, bool> {
				friend class	map<key_type, mapped_type, key_compare, allocator_type>;
				protected:
					Compare			comp;
					value_compare	(Compare c) : comp(c) {}

				public:
					typedef	bool		result_type;
					typedef	value_type	first_argument_type;
					typedef	value_type	second_argument_type;

					bool	operator()(const value_type & x, const value_type & y) const {
						return (comp(x.first, y.first));
					}
			};

			/* ************************************************************** */
			/* ****************** Constructors, Destructors ***************** */
			/* ************************************************************** */
			/*	Parameters :
				Comp = binary predicate that, taking two element kays as argument,
					returns true if the first argument goes before the second
					argument in the strict weak ordering it defines, and false
					otherwise. This shall be a function pointer/object.
				Alloc = the container keeps and use an internal copy of this
					allocator.
				First & last = Input iterators to the initial and final position
					in a range. The range used is [first,last], which includes
					all the elements between first and last, including the
					element pointed by first but not the element pointed by
					last. */

			/* ************************** Default *************************** */
			/*	Constructs an empty container, with no elements. */
			explicit	map(const key_compare & comp = key_compare(),
							const allocator_type & alloc = allocator_type())
			: _alloc(alloc), _comp(comp), _rbt() {}


			/* *************************** Range **************************** */
			/*	Constructs a container with as many elements as the range
				[first, last], with each element constructed from its corresponding
				element in that range. */
			template< class InputIterator >
			map(InputIterator first, InputIterator last, const key_compare & comp
				= key_compare(), const allocator_type & alloc = allocator_type())
			: _alloc(alloc), _comp(comp), _rbt() {
				this->insert(first, last);
			}

			/* **************************** Copy **************************** */
			/*	Constructs a container with a copy of each of the elements
				in x. */
			map(const map& x) : _alloc(x._alloc), _comp(x._comp), _rbt() {
				this->insert(x.begin(), x.end());
			}

			/* ************************* Destructor ************************* */
			/*	Destroys all container elements, and deallocates all the storage
				capacity allocated by the map container using its allocator. */
			~map() {
				_rbt.clear(_rbt.getRoot());
			}
			
			/* ************************* Operator=() ************************ */
			/*	Assign new contents to the container, replacing its current
				content. */
			map &	operator=(const map & x) {
				if (this != &x) {
					this->clear();
					this->insert(x.begin(), x.end());
					this->_alloc= x._alloc;
					this->_comp = x._comp;
				}
				return (*this);
			}


			/* ************************************************************** */
			/* ************************** Iterators ************************* */
			/* ************************************************************** */

			/* ************************** Begin() *************************** */
			/*	Returns an iterator referring to the first element in the map
				container. Because map containers keep their elements ordered
				at all times, begin() points to the element that goes first
				following the container's sorting criterion. [see key_comp()]
				If the container is empty, the returned iterator value shall not
				be dereferenced. */
			iterator	begin() {
				return (iterator(_rbt.firstNode(), _rbt.getEnd()));
			}

			const_iterator	begin() const {
				return (const_iterator(_rbt.firstNode(), _rbt.getEnd()));
			}

			/* *************************** End() **************************** */
			/*	Returns an iterator referring to the past-the-end element in the
				map container. It is the theoretical element that would follow
				the last element in the container. It does not point to any
				element, and thus shall not be dereferenced. */
			iterator	end() {
				return (iterator(_rbt.getEnd(), _rbt.getEnd()));
			}

			const_iterator	end() const {
				return (const_iterator(_rbt.getEnd(), _rbt.getEnd()));
			}

			/* ************************** Rbegin() ************************** */
			/*	Returns a reverse iterator pointing to the last element in the
				container. Reverse iterator iterate backwards: increasing them
				moves them towards the beginning of the container. rbegin points
				to the element preceding the one that would be pointer to by
				member end. */
			reverse_iterator	rbegin() {
				return (reverse_iterator(iterator(_rbt.getEnd(), _rbt.getEnd())));
			}

			const_reverse_iterator	rbegin() const {
				return (const_reverse_iterator(iterator(_rbt.getEnd(), _rbt.getEnd())));
			}

			/* *************************** Rend() *************************** */
			/*	Returns an iterator pointing to the theoretical element right
				before the first element in the map container. The range between
				mapp:rbegin() & map::rend() contains all the elements of the
				container in reverse order. */
			reverse_iterator	rend() {
				return (reverse_iterator(iterator(this->begin())));
			}

			const_reverse_iterator	rend() const {
				return (const_reverse_iterator(this->begin()));
			}

			// reverse_iterator rbegin() { return (reverse_iterator(iterator(_rbt.getEnd(), _rbt.getEnd()))); }
            // const_reverse_iterator rbegin() const { return (const_reverse_iterator(iterator(_rbt.getEnd(), _rbt.getEnd()))); }
            // reverse_iterator rend() { return (reverse_iterator(this->begin())); }
            // const_reverse_iterator rend() const { return (const_reverse_iterator(this->begin())); }

			/* ************************************************************** */
			/* ************************** Capacity ************************** */
			/* ************************************************************** */

			/* ************************** Empty() *************************** */
			/*	Returns wether the map container is empty (i.e wether its size
				is 0). This function doesn't modify the container in any way. */
			bool	empty() const {
				return (_rbt.getSize() == 0 ? true : false);
			}

			/* *************************** Size() *************************** */
			/*	Returns the number of elements in the map container. */
			__SIZE_TYPE__	size() const {
				return (_rbt.getSize());
			}

			/* ************************* Max_size() ************************* */
			/*	Returns the maximum number of elements that the map container
				hold. This is the maximmum potential size the container can
				reach due to known system/lib implementation limitations, but
				the container is by no means guarnteed to be able to reach that
				size. It can still fail to allocate storage at any point before
				that size is reached. */
			__SIZE_TYPE__	max_size() const {
				return (allocator_type().max_size() * 2);
			}


			/* ************************************************************** */
			/* *********************** Elements Access ********************** */
			/* ************************************************************** */

			/* ************************ Operator[]() ************************ */
			/*	Acces element.
				If 'k' matches the key of an element in the container, the
				function returns a reference to its mapped value.
				If 'k' doesn't match the key of any element in the container,
				the function inserts a new element with that key and returns a
				reference to its mapped value. Notice that this always increased
				the container size by one, even if no mapped value is assigned
				to the element. (the element is constructed using its default
				constructor) */
			mapped_type &	operator[](const key_type& k) {
				ft::Node<value_type>*	ptr = _rbt.search(k);

				if (ptr == u_nullptr)
					ptr = _rbt.insertNode(ft::make_pair<key_type, mapped_type>(k, mapped_type()));
				return (ptr->data.second);
			}


			/* ************************************************************** */
			/* ************************** Modifiers ************************* */
			/* ************************************************************** */

			/* ************************** Insert() ************************** */
			/*	Extends the container by inserting new elements, effectively
				increasing the container size by the number of elements inserted.
				Because element keys in map are unique, the insertion operation
				checks wether each inserted element has a key equivalent to the
				one of an element already in the container, and if so, the
				element is not inserted, returning an iterator to this existing
				element. */
			/*	Single element */
			pair<iterator, bool>	insert(const value_type & val) {
				ft::Node<value_type>*	ptr;
				bool					find = true;

				if ((ptr = _rbt.search(val.first)) != u_nullptr)
					find = false;
				ptr = _rbt.insertNode(val);
				return (ft::make_pair<iterator, bool>(iterator(ptr, _rbt.getEnd()), find));
			}

			/*	With hint */
			iterator	insert(iterator position, const value_type & val) {
				(void)position;
				return (iterator(_rbt.insertNode(val), _rbt.getEnd()));
			}
			
			/*	Range */
			template< class InputIterator >
			void	insert(InputIterator first, InputIterator last) {
				while (first != last) {
					_rbt.insertNode(*first);
					first++;
				}
			}

			/* ************************** Erase() *************************** */
			/*	Removes from the map container either a single element or a
				range of elements. This effectively reduces the container size
				by the number of elements removed, which are destroyed. */
			void	erase(iterator position) {
				iterator	it = this->begin();

				while (it != position)
					it++;
				if (it == position)
					_rbt.deleteNode(it.base(), it->first);
			}

			__SIZE_TYPE__	erase(const key_type& key) {
				return (_rbt.deleteNode(_rbt.getRoot(), key));
			}

			void	erase(iterator first, iterator last) {
				map	x(first, last);

				first = x.begin();
				last = x.end();
				while (first != last) {
					_rbt.deleteNode(_rbt.getRoot(), first->first);
					first++;
				}
			}

			/* *************************** Swap() *************************** */
			/*	Exchange the content of the container by the content of x, which
				is another map of the same type. Sizes may differ.
				After the call to this member function, the elements in this
				container are those which were in x before the call, and the 
				elements of x are those which were in this. All iterators,
				references and pointers remains valid for the swapped objects. */
			void	swap(map& x) {
				_rbt.swap(x._rbt);
			}

			/* ************************** Clear() *************************** */
			/*	Removes all elements from the map container (which are
				destroyed), leaving the container with a size of 0. */
			void	clear() {
				erase(begin(), end());
			}


			/* ************************************************************** */
			/* ************************** Observers ************************* */
			/* ************************************************************** */

			/* ************************* Key_comp() ************************* */
			/*	Returns a copy of the comparison object used by the container to
				compare keys. The comparison object of a map object is set on
				construction. Its type is the third template parameter of the
				map template. By default, this is a 'less' object, which returns
				the same as operator<.
				This object determines the order of the elements in
				the container: it is a function pointer or a function object
				that takes two arguments of the same type as the element keys,
				and returns 'true' if the first argument is considered to go
				before the second in the strict weak ordering it defines, and
				false otherwise. */
			key_compare	key_comp() const {
				return (_comp);
			}
			
			/* ************************ Value_comp() ************************ */
			/*	Returns comparison object that can be used to compare two
				elements to get whether the key of the first one goes before the
				second.
				The arguments taken by this function object are of member type
				value_type, but the mapped_type part of the value is not taken
				into consideration in this comparison.
				This comparison object returned is an object of the member type
				map::value_compare, which is a nested class that uses the
				internal comparison object to generate the appropriate comparison
				functional class. */
			value_compare	value_comp() const {
				return (value_compare(key_compare()));
			}


			/* ************************************************************** */
			/* ************************* Operations ************************* */
			/* ************************************************************** */
			
			/* *************************** Find() *************************** */
			/*	Searches the container for an element with a key equivalent to k
				and returns an iterator to it if found, otherwise it returns an
				iterator to end().
				Two keya are considered equivalent if the container's comparison
				object returns false. */
			iterator	find(const key_type& k) {
				ft::Node<value_type>*	find;

				if ((find = _rbt.search(k)) == u_nullptr)
					find = _rbt.getEnd();
				return (iterator(find, _rbt.getEnd()));
			}

			const_iterator	find(const key_type & k) const {
				ft::Node<value_type>*	find;

				if ((find = _rbt.search(k)) == u_nullptr)
					find = _rbt.getEnd();
				return (iterator(find, _rbt.getEnd()));
			}

			/* ************************** Count() *************************** */
			/*	Searches the container for elements with a key equivalent to k
				and returns the number of matches.
				Because all elements in a map container are unique, the function
				can only return 1 (if the element is found) or 0. */
			__SIZE_TYPE__	count(const key_type & k) const {
				return (_rbt.search(k) == u_nullptr ? 0 : 1);
			}
			
			/* *********************** Lower_bound() ************************ */
			/*	Returns an iterator pointing to the first element of the
				container whose key is not considered to go before k.
				The function uses its internal comparison object (key_comp) to
				determine this, returning an iterator to the first element for
				which key_comp(element_key, k) would return false. */
			iterator	lower_bound(const key_type & k) {
				iterator	it = begin();

				while (it != end()) {
					if (_comp(it->first, k) == false)
						break ;
					it++;
				}
				return (it);
			}

			const_iterator	lower_bound(const key_type & k) const {
				iterator	it = begin();

				while (it != end()) {
					if (_comp(it->first, k) == false)
						break ;
					it++;
				}
				return (it);
			}

			/* *********************** Upper_bound() ************************ */
			/*	Returns an iterator pointing to the first element in the
				container whose key is considered to go after k.
				The function uses its internal comparison object (key_comp) to
				determine this, returning an iterator to the first element for
				which key_comp(element_key, k) would return true. */
			iterator	upper_bound(const key_type & k) {
				iterator	it = begin();

				while (it != end()) {
					if (_comp(k, it->first) == true)
						break ;
					it++;
				}
				return (it);
			}

			const_iterator	upper_bound(const key_type & k) const {
				const_iterator	it = begin();

				while (it != end()) {
					if (_comp(k, it->first) == true)
						break ;
					it++;
				}
				return (it);
			}

			/* *********************** Equal_range() ************************ */
			/*	Returns the bounds of a range that includes all the elements in
				the container which have a key equivalent to k.
				Because the elements in a map container have unique key, the
				range returned will contain a single element at most.
				If not matches are found, the range returned has a length of 0,
				with both iterators pointing to the first element that has a key
				considered to go after k according to the container's internal
				comparison object (key_comp). */
			pair<iterator,iterator>	equal_range(const key_type & k) {
				return (ft::make_pair<iterator,iterator>(lower_bound(k),upper_bound(k)));
			}

			pair<const_iterator,const_iterator>	equal_range(const key_type & k) const {
				return (ft::make_pair<iterator,iterator>(lower_bound(k),upper_bound(k)));
			}

			/* ************************************************************** */
			/* ************************** Allocator ************************* */
			/* ************************************************************** */

			/* *********************** Equal_range() ************************ */
			/*	Returns a copy of the allocator object associated with the
				map. */
			allocator_type	get_allocator() const {
				return (allocator_type());
			}

		private:
			allocator_type							_alloc;
			key_compare								_comp;
			ft::RBTree< key_type, mapped_type >		_rbt;
	};


	/* ********************************************************************** */
	/* ************************ Non Member Operators ************************ */
	/* ********************************************************************** */

	/* **************************** Operator==() **************************** */
	template< class Key, class T, class Compare, class Alloc >
	bool	operator==(const map< Key, T, Compare, Alloc >& lhs,
						const map< Key, T, Compare, Alloc >& rhs) {
		return (lhs.size() == rhs.size());
	}

	/* **************************** Operator!=() **************************** */
	template< class Key, class T, class Compare, class Alloc >
	bool	operator!=(const map< Key, T, Compare, Alloc >& lhs,
						const map< Key, T, Compare, Alloc >& rhs) {
		return (!(lhs.size() == rhs.size()));
	}

	/* **************************** Operator<() ***************************** */
	template< class Key, class T, class Compare, class Alloc >
	bool	operator<(const map< Key, T, Compare, Alloc >& lhs,
						const map< Key, T, Compare, Alloc >& rhs) {
		return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}

	/* **************************** Operator<=() **************************** */
	template< class Key, class T, class Compare, class Alloc >
	bool	operator<=(const map< Key, T, Compare, Alloc >& lhs,
						const map< Key, T, Compare, Alloc >& rhs) {
		return (!(rhs < lhs));
	}

	/* **************************** Operator>() ***************************** */
	template< class Key, class T, class Compare, class Alloc >
	bool	operator>(const map< Key, T, Compare, Alloc >& lhs,
						const map< Key, T, Compare, Alloc >& rhs) {
		return (rhs < lhs);
	}

	/* **************************** Operator>=() **************************** */
	template< class Key, class T, class Compare, class Alloc >
	bool	operator>=(const map< Key, T, Compare, Alloc >& lhs,
						const map< Key, T, Compare, Alloc >& rhs) {
		return (!(lhs < rhs));
	}

	/* ********************************************************************** */
	/* ************************ Non Member Functions ************************ */
	/* ********************************************************************** */

	/* ******************************* Swap() ******************************* */
	template< class Key, class T, class Compare, class Alloc >
	void	swap(map< Key, T, Compare, Alloc >& lhs,
					map< Key, T, Compare, Alloc >& rhs) {
		lhs.swap(rhs);
	}
}

void	map_testing(void);

#endif
