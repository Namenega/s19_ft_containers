/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   notions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namenega <namenega@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 13:04:17 by namenega          #+#    #+#             */
/*   Updated: 2022/01/17 18:32:38 by namenega         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*	If doing the function inside the template, the function acquires the
	implicit inline property. */

/* ************************************************************************** */
/* ***************************** UTILS/UTILS.HPP **************************** */
/* ************************************************************************** */

/*	Traits */
/*	The default traits class template is empty. It allows, when compiling,
	to get informations about data types on a generic base. It is a double
	abstraction. */

/*	Enable if */
/*	It is a trait that allows to control SFINAE application. It's defined on
	a static condition of a type (enable_if< bool,T=void >)
	std::enable_if< true, T >::type is equal to T.
	std::enable_if< false, T >::type is undefined which means that it eliminates
	a template among the examinated template to generate code.
	The type T is enabled as member type 'enable_if::type' if condition is true. 
	*/

/*	integral_constant */
/*	This template is designed to provide compile-time constants as types.
	It is used as the base class for trait types, especially in their bool
	variant. */

/*	is_integral */
/*	template<class T> struct is_integral.
	Trait class identifies whether T is an integral type. It inherits from
	integral_constant as being either true_type or false_type, depending on
	whether T is an integral type. */

/* ************************************************************************** */
/* ************************** ITERATOR/ITERATOR.HPP ************************* */
/* ************************************************************************** */

/*	ptrdiff_t */
/*	It is the signed integer type of the result of subtracting two pointers
	The bit width is not less than 17.
	It is used for pointer arithmetic and array indexing, if negative values
	are possible.
	Working with c++ container lib, the proper type for the difference between
	iterators is the member 'typedef difference_type'.
	https://en.cppreference.com/w/cpp/types/ptrdiff_t */

/*	iterator_traits */
/*	 */


/* ************************************************************************** */
/* **************************** VECTOR/VECTOR.HPP *************************** */
/* ************************************************************************** */

/*	A vector is a sequence container that encapsulates dynamic size arrays.
	If we reach the size of the array and want to put more data in it, it will
	expand the size by finding memory larger than the occupied size. It will
	copy the entire content on the larger space memory. If there is a pointer on
	an existing element and the content is copied somewhere else, the pointer
	will be completely invalid.
	Arrays have contiguous data (l'une a coté de l'autre) */

/* ***************************** std::allocator ***************************** */
/*	allocate() */
/*	pointer allocate(size_type n); <memory>; Attempts to allocate a block of
	storage with a size large enough to contain n elements of member type
	sizeof(value_type), and returns a pointers to the first element. */
/*	construct() */
/*	void construct(pointer p, const_reference val); Construct an object of
	type T in allocated storage pointed to by 'p', using placement-new.
	p = pointer to allocated uninitialized storage
	val = the value to use as the copy constructor argument. */
/*	explicit */
/*	The explicit keyword to the constructor prevents the compiler from using
	that constructor for implicit conversion. */

/* ************************************************************************** */
/* ******************************* MAP/MAP.HPP ****************************** */
/* ************************************************************************** */

/*	Red black tree */
/*	https://algorithmtutor.com/Data-Structures/Tree/Red-Black-Trees/ */
/*	[see the link for picture about RBT] */
/*	A RBT is a binary search tree having following five additional properties :
		1. Every node in T is either black or red.
		2. The root node of T is black.
		3. Every NULL node is black. NULL nodes are the leaf nodes.
			They do not contain any keys.
		4. If a node is red, both of its children are black. This means no two
			nodes on a path can be red nodes.
		5. Every path from a root node to a NULL node has the same number of
			black nodes.
	
	Among all dynamics set operations (search, predecessor, successor, insert,
	delete, etc), there are 2 operations that may violate the invariants listed
	above. These are insertion and deletion.
	Therefore, after every insertion/deletion, we check if the operation violated
	any of the properties : if it did, we need to restructure the tree to keep
	the invariants intact. Three tools :
		1. Left_rotate(T, x) : The left rotation at node X makes X goes down in
			the left direction, and as a result, it's right child goes up. [link]
		2. Right_rotate(T, y) : The right rotation at node X makes X goes down
			in the right direction and as a result, its left child goes up. [link]
		3. Recolor : recolor flips the color of a node. If it's red, it becomes
			blac, and vice-versa.
	We call a RBT a balanced search tree because its height is always in the
	order of 0(log n) (Complexity level).

	Insertion : to insert a node K into a red black tree T, we do the following :
		1. Insert K using an ordinary BST insertion operation.
		2. Color K in red
		3. Check if the insertion violated the RBT properties. If yes : fix it.
	Lets suppose about node K in tree T:
	- P = parent node
	- U = uncle node
	- S = sibling node
	- G = grandparent node

	Case 1. T is empty : we make K the root of the tree and color it black.
	Case 2. P is black : it can not violate any of the properties. Therefore, in
			this case, we do not need to do anything.
	Case 3. P is red : This violates property[4]. P and K are now both red. The
			G must be black -> check whether U is red or black.

		3.1 P is red and U is red : flip the color of P, U, G. P becomes black,
			U becomes black and G becomes red (only if it's not the root).
		3.2 P is red and U is black (or NULL) : we need single or double tree
			rotations depending upon whether K is left or right child of P.
			3.2.1 - P is right of G and K is right of P : left rotation at G
				that makes G the new S of K. Next, change the color of S to red
				and P to black.
			3.2.2 - P is right of G and K is left of P : right rotation at P and
				then apply 3.2.1.
			3.2.3 - P is left of G and K is left of P : symetric solution of 3.2.1
			3.2.4 - P is left of G and K is right of P : symetric to 3.2.2

	Deletion : first we follow the ordinary BST deletion process, which makes sure
		that X is either a leaf node or a single child.
	
	Case 1. X is a red node : we simply delete X since deleting a red node doesnt
			violates any property.
	Case 2. X has a red child : we replace X by its red child and change the color
			of the child.
	Case 3. X is a black node : deleting a black node violates propery[5], so we
			add an extra black node to the deleted node and call it a double black
			node. Now we need to convert this double black into a single black.
		3.1 S is red : we switch the color of S and P and perform the left rotation
			on P.
		3.2 S is black and both of S children are black : switch S color to red,
			if P color is red, we change its color to black and this becomes the
			terminal case. Otherwise, we make P a new X and repeat process (?)
		3.3 S is black, S left child is red and right child black : switch color
			of S and left child of S, right rotation on S (it's 3.4 tree) 
		3.4 S is black, S right child is red : switch color of right child to
			black, P to black and left rotation on P 

	*/

/* ************************************************************************** */
/* ***************************** STACK/STACK.HPP **************************** */
/* ************************************************************************** */

/*	Stacks are a type of container adaptor, specifically designed to operate in
	a LIFO context, where elements are inserted and extracted only from one end
	of the container.
	Container adaptor are classes the use an encapsulated object of a specific
	container class as its underlying container, providing a specific set of
	member functions to access its elements. */

/*	friend */
/*	In some circonstances, it is more convenient to grant member level access
	to functions that are not members of a class. Only the class implementer
	ca declare who its friends are. In a class definition, use the 'friend'
	keyword and the name of a non member function to grant it access to the
	and protected members of your class. In a template definition, a type
	parameter can be declared as a friend.
	
	I you declare a friend function that was not previously declared, that
	function is exported to the enclosing non-class scope. */
