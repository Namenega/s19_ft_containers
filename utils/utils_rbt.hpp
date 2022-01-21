/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_rbt.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namenega <namenega@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 17:32:23 by namenega          #+#    #+#             */
/*   Updated: 2022/01/21 12:21:50 by namenega         ###   ########.fr       */
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
		Node(const Node & x) : data(x.data), parent(x.parent), left(x.left),
							right(x.right), color(x.color) {}
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
			return (*this);
		}
	};

	template< class T, class U >
	struct	pair {
		typedef	T	first_type;
		typedef	U	second_type;

		first_type	first;
		second_type	second;

		/* ************************** Constructors ************************** */
		/*	Default */
		pair() : first(first_type()), second(second_type()) {}
		
		/*	Copy */
		template< class V, class W >
		pair (const pair<V,W>& x) : first(x.first), second(x.second) {}

		pair (const first_type &a, const second_type & b) {
			first = a;
			second = b;
		}

		/*	Operator= */
		pair & operator=(const pair & x) {
			if (this != &x) {
				first = x.first;
				second = x.second;
			}
			return (*this);
		}
	};

	/* ********************** Non Member Pair Function ********************** */

	template<class T, class U >
	bool	operator==(const pair<T,U> & lhs, const pair<T,U> & rhs) {
		return (lhs.first == rhs.first && lhs.second == rhs.second);
	}
	template<class T, class U >
	bool	operator!=(const pair<T,U> & lhs, const pair<T,U> & rhs) {
		return (!(lhs == rhs));
	}
	template< class T, class U >
	bool	operator<(const pair<T,U> & lhs, const pair<T,U> & rhs) {
		return (lhs.first < rhs.first || (!(rhs.first < lhs.first) && lhs.second < rhs.second));
	}
	template< class T, class U >
	bool	operator<=(const pair<T,U> & lhs, const pair<T,U> & rhs) {
		return (!(rhs < lhs));
	}
	template< class T, class U >
	bool	operator>(const pair<T,U> & lhs, const pair<T,U> & rhs) {
		return (rhs < lhs);
	}
	template< class T, class U>
	bool	operator>=(const pair<T,U> & lhs, const pair<T,U> & rhs) {
		return (!(lhs < rhs));
	}
	template< class T, class U >
	pair<T,U>	make_pair(T x, U y) {
		return (pair<T,U>(x, y));
	}

	template< class Key, class T >
	class RBTree {
		public:
			/* ************************** Typedef *************************** */
			typedef	size_t									size_type;
			typedef	T										mapped_type;
			typedef	Key										key_type;
			typedef	ft::pair<const key_type, mapped_type>	value_type;
			typedef	std::allocator< Node<value_type> >		node_allocator;
			typedef	ft::Node<value_type>*					node_pointer;
			typedef	ft::Node<value_type>					node_type;

			/* ************************ Constructors ************************ */
			/*	Default */
			RBTree() {
				end = node_allocator().allocate(1);
				node_allocator().construct(end, node_type());
				end->parent = u_nullptr;
				end->left = u_nullptr;
				end->right = u_nullptr;
				end->color = 0;
				root = end;
				size = 0;
			}
			/*	Copy */
			RBTree(const RBTree & x) : root(x.root), end(x.end), size(x.size) {
				this->clear(this->root);
				this->insertAll(x.root);
			}
			/*	Operator= */
			RBTree &	operator=(const RBTree & x) {
				if (this != x) {
					this->clear(this->root);
					this->insertAll(x.root);
					this->root = x.root;
					this->end = x.end;
					this->size = x.size;
				}
				return (*this);
			}
			/*	Destructor */
			~RBTree() {
				node_allocator().destroy(end);
				node_allocator().deallocate(end, 1);
				end = nullptr;
			}

			/* ************************************************************** */
			/* ********************** Member Functions ********************** */
			/* ************************************************************** */

			/* ************************************************************** */
			/* ************************** Accessors ************************* */
			/* ************************************************************** */
			node_pointer	getEnd() const {
				return (this->end);
			}
			node_pointer	getRoot() const {
				return (this->root);
			}
			size_type	getSize() const {
				return (this->size);
			}

			node_pointer	search(const key-type & key) const {
				node_pointer	tmp = this->root;

				while (tmp != end) {
					if (tmp->data.first == key)
						return (tmp);
					else if (key < tmp->data.first)
						tmp = tmp->left;
					else
						tmp = tmp->right;
				}
				return (u_nullptr);
			}

			node_pointer	firstNode() const {
				node_pointer	tmp = root;

				if (tmp == end)
					return (end);
				while (tmp->left != end)
					tmp = tmp->left;
				return (tmp);	
			}

			node_pointer	lastNode() const {
				node_pointer	tmp = root;

				if (tmp == end)
					return (end);
				while (tmp->right != end)
					tmp = tmp->right;
				return (tmp);	
			}

			/* ************************************************************** */
			/* ************************** Modifiers ************************* */
			/* ************************************************************** */

			/*	Insert the key to the tree in its appropriate position and fix
				the tree. */
			node_pointer	insertNode(const value_type& val) {
				node_pointer	x;

				if ((x = search(val.first)) != u_nullptr)
					return (x);
				node_pointer	node = node_allocator().allocate(1);
				node_allocator().construct(node, node_type(ft::make_pair<key_type, mapped_type>(val.first, val.second)));
				node->parent = u_nullptr;
				node->left = end;
				node->right = end;
				node->color = 1; /* new node is red */
				size++;
				node_pointer y = null_ptr;
				node_pointer x = this->root;

				while (x != end) {
					y = x;
					if (node->data < x->data)
						x = x->left;
					else
						x = x->right;
				}
				node->parent = y; /* y is parent of x */
				if (y == u_nullptr)
					root = node;
				else if (node->data < y->data)
					y->left = node;
				else
					y->right = node;
				
				/*	If new node is a root node, simply return */
				if (node->parent == u_nullptr) {
					node->color = 0;
					indexEnd();
					return (node);
				}
				if (node->parent->parent == u_nullptr) {
					indexEnd();
					return (node);
				}
				/*	Fix the tree */
				fixInsert(node); /* fixInsert(node) */
				indexEnd();
				return (node);
			}

			void	insertAll(node_pointer node) {
				if (node == u_nullptr)
					return ;
				insertAll(node->left);
				insertAll(node->right);
				insertNode(node->data);
			}

			__SIZE_TYPE__	deleteNode(node_pointer node, const key_type & key) {
				node_pointer	x, y, z = end;

				/*	Find the node containing the key */
				while (node != end) {
					if (node->data.first == key) {
						z = node;
					}
					if (node->data <= key)
						node = node->right;
					else
						node = node->left;
				}
				if (z == end)
					return (0);
				y = z;
				int	y_original_color = y->color;
				if (z->left == end) {
					x = z->right;
					rbTransplant(z, z->right);
				} else if (z->right == end) {
					x = z->left;
					rbTransplant(z, z->left);
				} else {
					y = minimum(z->right);
					y_original_color = y->color;
					x = y->right;
					if (y->parent == z)
						x->parent = y;
					else {
						rbTransplant(y, y->right);
						y->right = z->right;
						y->right->parent = y;
					}
					rbTransplant(z, y);
					y->left = z->left;
					y->left->parent = y;
					y->color = z->color;
				}
				node_allocator().destroy(z);
				node_allocator().deallocate(z, 1);
				size--;
				if (y_original_color == 0)
					fixDelete(x); /* fixDelete(x) */
				indexEnd();
				return (1);
			}

			void	clear(node_pointer node) {
				if (node == end)
					return ;
				clear(node->left);
				clear(node->right);
				node_allocator().destroy(node);
				node_allocator().deallocate(node, 1);
				node = null_ptr;
			}

			void	swap(RBTree & x) {
				size_type		s_size;
				node_pointer	s_root;
				node_pointer	s_end;

				s_size = x.size;
				s_root = x.root;
				s_end = x.end;
				x.size = this->size;
				x.root = this->root;
				x.end = this->end;
				this->size = s_size;
				this->root = s_root;
				this->end = s_end;
			}

		private:
			node_pointer	root;
			node_pointer	end;
			size_type		size;

			void	indexEnd() {
				end->left = firstNode();
				end->right = lastNode;
			}

			node_pointer	minimum(node_pointer node) {
				while (node->left != end)
					node = node->left;
				return (node);
			}

			void	rbTransplant(node_pointer u, node_pointer v) {
				if (u->parent == u_nullptr)
					root = v;
				else if (u == u->parent->left)
					u->parent->left = v;
				else
					u->parent->right = v;
				v->parent = u->parent;
			}

			void	leftRotate(node_pointer x) {
				node_pointer	y = x->right;
				x->right = y->left;
				if (y->left != end)
					y->left->parent = x;
				y->parent = x->parent;
				if (x->parent == u_nullptr)
					this->root = y;
				else if (x == x->parent->left)
					x->parent->left = y;
				else
					x->parent->right = y;
				y->left = x;
				x->parent = y;
			}

			void	rightRotate(node_pointer x) {
				node_pointer	y = x->left;
				x->left = y->right;
				if (y->right != end)
					y->right->parent = x;
				y->parent = x->parent;
				if (x->parent == u_nullptr)
					this->root = y;
				else if (x == x->parent->right)
					x->parent->right = y;
				else
					x->parent->left = y;
				y->right = x;
				x->parent = y;
			}

			/* Fix the RBTree after inserting an element */
			void	fixInsert(node_pointer k) {
				node_pointer	u;

				while (k->parent->color == 1) {
					if (k->parent == k->parent->parent->right) {
						u = k->parent->parent->left; /* Uncle */
						if (u->color == 1) {
							/* case 3.1 */
							u->color = 0;
							k->parent->color = 0;
							k->parent->parent->color = 1;
							k = k->parent->parent;
						} else {
							if (k == k->parent->left) {
								/* case 3.2.2 */
								k = k->parent;
								rightRotate(k);
							}
							/* case 3.2.1 */
							k->parent->color = 0;
							k->parent->parent->color = 1;
							leftRotate(k->parent->parent);
						}
					} else {
						u = k->parent->parent->right; /* Uncle */
						if (u->color == 1) {
							/* mirror case 3.1 */
							u->color = 0;
							k->parent->color = 0;
							k->parent->parent->color = 1;
							k = k->parent->parent;
						} else {
							if (k == k->parent->right) {
								/* mirror case 3.2.2 */
								k = k->parent;
								leftRotate(k);
							}
							/* mirror case 3.2.1 */
							k->parent->color = 0;
							k->parent->parent->color = 1;
							rightRotate(k->parent->parent);
						}
					}
					if (k == root)
						break ;
				}
				root->color = 0;
			}

			/* Fix the RBTree after deleting a element */
			void	fixDelete(node_pointer x) {
				node_pointer	s;
				while (x != root && x->color == 0) {
					if (x == x->parent->left) {
						s = x->parent->right;
						if (s->color == 1) {
							/* case 3.1 */
							s->color = 0;
							x->parent->color = 1;
							leftRotate(x->parent);
							s = x->parent->right;
						}
						if (s->left->color == 0 && s->right->color == 0) {
							/* case 3.2 */
							s->color = 1;
							x = x->parent;
						} else {
							if (s->right->color == 0) {
								/* case 3.3 */
								s->left->color = 0;
								s->color = 1;
								rightRotate(s);
								s = x->parent->right;
							}
							/* case 3.4 */
							s->color = x->parent->color;
							x->aprent->color = 0;
							s->right->color = 0;
							leftRotate(x->parent);
							x = root;
						}
					} else {
						s = x->parent->left;
						if (s->color == 1) {
							/* case 3.1 */
							s->color = 0;
							x->parent->color = 1;
							rightRotate(x->parent);
							s = x->parent->left;
						}
						if (s->left->color == 0 && s->right->color == 0) {
							/* case 3.2 */
							s->color = 1;
							x = x->parent;
						} else {
							if (s->left->color == 0) {
								/* case 3.3 */
								s->right->color = 0;
								s->color = 1;
								leftRotate(s);
								s = x->parent->left;
							}
							/* case 3.4 */
							s->color = x->parent->color;
							x->parent->color = 0;
							s->left->color = 0;
							rightRotate(x->parent);
							x = root;
						}
					}
				}
				x->color = 0;
			}
	};
}

#endif
