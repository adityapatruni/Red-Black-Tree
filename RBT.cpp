//CSE674 HW6  Due: 11:59PM, Nov. 26 (Tuesday)
#include <iostream>
using namespace std;
class node {
public:
	node* p_parent;
	node* p_Lchild;
	node* p_Rchild;
	int value;
	bool color; //true: red, false: black
	node() { p_parent = p_Lchild = p_Rchild = nullptr; }
	node(int i) { value = i; p_parent = p_Lchild = p_Rchild = nullptr; }
};

class tree {
public:
	node* root;
	tree() { root = nullptr; }

	//For insert, the new node should be the last of nodes with the same value in the order of 
	//inorder traversal.  (The same as HW5.)
	void insert_node(int i) {
		if (root) {
			bool colorswap = NULL;
			node* n = new node(i);
			node* refroot = new node();
			node* faultnode = new node();
			refroot = root;
			node* cursor = new node();
			while (1) {
				node* uncle = new node();
				node* grandparent = new node();
				if (i >= refroot->value) {
					if (refroot->p_Rchild == nullptr) {
						n->p_parent = refroot;
						n->color = true;
						refroot->p_Rchild = n;
						if (n->p_parent->color) {
							if (n->p_parent->p_parent != nullptr && n->p_parent->color) {
								grandparent = n->p_parent->p_parent;
								if (n->p_parent == grandparent->p_Lchild) {
									uncle = grandparent->p_Rchild;
									if (uncle != nullptr) {
										if (uncle->color) {
											uncle->color = false;
											n->p_parent->color = false;
											grandparent->color = true;
											n = grandparent;
										}
										else {
											//Left-Right CASE
											insert_L_rotate(n);
											insert_R_rotate(n);
											colorswap = n->p_parent->color;
											n->p_parent->color = grandparent->color;
											grandparent->color = colorswap;

										}

									}
									return;
								}
								else if (n->p_parent == grandparent->p_Rchild) {
									if (grandparent->p_Lchild != nullptr) {
										uncle = n->p_parent->p_parent->p_Lchild;
										if (uncle->color) {
											uncle->color = false;
											n->p_parent->color = false;
											grandparent->color = true;
										}
										else {
											//Right-Right CASE
											insert_L_rotate(n);
											colorswap = n->p_parent->color;
											n->p_parent->color = grandparent->color;
											grandparent->color = colorswap;
										}
										return;
									}
									else {
										return;
									}

								}
							}
						}
						else {
							return;
						}
					}
					else {
						refroot = refroot->p_Rchild;
					}
				}
				else {
					if (refroot->p_Lchild == nullptr) {
						n->p_parent = refroot;
						n->color = true;
						refroot->p_Lchild = n;
						if (n->p_parent->color) {
							if (n->p_parent->p_parent != nullptr && n->p_parent->color) {
								if (n->p_parent == n->p_parent->p_parent->p_Lchild) {
									if (n->p_parent->p_parent->p_Rchild != nullptr) {
										if (n->p_parent->p_parent->p_Rchild->color) {
											n->p_parent->p_parent->p_Rchild->color = false;
											n->p_parent->color = false;
											grandparent->color = true;
										}
										else {
											//Left-Left CASE
											insert_R_rotate(n);
											colorswap = n->p_parent->color;
											n->p_parent->color = grandparent->color;
											grandparent->color = colorswap;
										}
										return;
									}
								}
								else if (n->p_parent == grandparent->p_Rchild) {
									if (n->p_parent->p_parent->p_Lchild != nullptr) {
										if (n->p_parent->p_parent->p_Lchild->color) {
											n->p_parent->p_parent->p_Lchild->color = false;
											n->p_parent->color = false;
											grandparent->color = true;
										}
										else {
											//Right-Left CASE
											insert_R_rotate(n);
											insert_L_rotate(n);
											colorswap = n->p_parent->color;
											n->p_parent->color = grandparent->color;
											grandparent->color = colorswap;
										}
										return;
									}

								}
							}
							else {
								return;
							}
						}
						else {
							return;
						}

					}
					else {
						refroot = refroot->p_Lchild;
					}
				}
			}

		}
		else {
			root = new node(i);
			root->color = false;
			return;
		}
	};
	void insert_R_rotate(node* p) {
		node* badnode;
		node* replacement;
		node* temp;
		if (p != root) {
			if (p == p->p_parent->p_Lchild) {
				if (p->p_Lchild->p_Rchild == nullptr) {
					temp = p->p_parent;
					p->p_Lchild->p_parent = temp;
					replacement = p->p_Lchild;
					p->p_parent->p_Lchild = nullptr;
					p->p_Lchild = nullptr;
					temp->p_Lchild = replacement;
					p->p_parent = replacement;
					replacement->p_Rchild = p;

				}
				else {
					temp = p->p_parent;
					p->p_Lchild->p_parent = temp;
					replacement = p->p_Lchild;
					badnode = p->p_Lchild->p_Rchild;
					replacement->p_Rchild = nullptr;
					temp->p_Lchild = replacement;
					p->p_parent->p_Rchild = nullptr;
					p->p_Lchild = nullptr;
					p->p_parent = replacement;
					p->p_Lchild = badnode;
					badnode->p_parent = p;
					replacement->p_Rchild = p;
				}
			}
			else if (p == p->p_parent->p_Rchild) {
				if (p->p_Lchild == nullptr) {

				}
				if (p->p_Lchild->p_Rchild == nullptr) {
					temp = p->p_parent;
					replacement = p->p_Lchild;
					replacement->p_parent = temp;
					temp->p_Rchild = replacement;
					p->p_Lchild = nullptr;
					p->p_parent = replacement;
					replacement->p_Rchild = p;
					//height_update(p);
				}
				else {
					temp = p->p_parent;
					p->p_Lchild->p_parent = temp;
					replacement = p->p_Lchild;
					badnode = p->p_Lchild->p_Rchild;
					replacement->p_Rchild = nullptr;
					temp->p_Rchild = replacement;
					p->p_parent->p_Rchild = nullptr;
					p->p_Lchild = nullptr;
					p->p_parent = replacement;
					p->p_Lchild = badnode;
					badnode->p_parent = p;
					replacement->p_Rchild = p;
				}
			}
		}
		else {
			if (p->p_Lchild->p_Rchild == nullptr) {
				root = p->p_Lchild;
				root->p_parent = nullptr;
				p->p_Lchild = nullptr;
				root->p_Rchild = p;
				p->p_parent = root;
				//height_update(p);
			}
			else {
				root = p->p_Lchild;
				root->p_parent = nullptr;
				p->p_Lchild = nullptr;
				root->p_Rchild = p;
				p->p_parent = root;
				badnode = p->p_Lchild->p_Rchild;
				badnode->p_parent = p;
				p->p_Lchild = badnode;

			}
		}
	};//For insert_node, R-rotate at node pointed by p
	void insert_L_rotate(node* p) {
		node* badnode;
		node* replacement;
		node* temp;
		if (p != root) {
			if (p == p->p_parent->p_Rchild) {
				if (p->p_Rchild->p_Lchild == nullptr) {
					temp = p->p_parent;
					p->p_Rchild->p_parent = temp;
					replacement = p->p_Rchild;
					p->p_parent->p_Rchild = nullptr;
					p->p_Rchild = nullptr;
					temp->p_Rchild = replacement;
					p->p_parent = replacement;
					replacement->p_Lchild = p;
				}
				else {
					temp = p->p_parent;
					p->p_Rchild->p_parent = temp;
					replacement = p->p_Rchild;
					badnode = p->p_Rchild->p_Lchild;
					replacement->p_Lchild = nullptr;
					temp->p_Rchild = replacement;
					p->p_parent = replacement;
					p->p_Rchild = badnode;
					badnode->p_parent = p;
					replacement->p_Lchild = p;

				}
			}
			else if (p == p->p_parent->p_Lchild) {
				if (p->p_Rchild->p_Lchild == nullptr) {
					temp = p->p_parent;
					p->p_Rchild->p_parent = temp;
					replacement = p->p_Rchild;
					p->p_Rchild = nullptr;
					temp->p_Lchild = replacement;
					p->p_parent = replacement;
					replacement->p_Lchild = p;
				}
				else {
					temp = p->p_parent;
					p->p_Rchild->p_parent = temp;
					replacement = p->p_Rchild;
					badnode = p->p_Rchild->p_Lchild;
					replacement->p_Lchild = nullptr;
					temp->p_Lchild = replacement;
					p->p_parent->p_Lchild = nullptr;
					p->p_Rchild = nullptr;
					p->p_parent = replacement;
					p->p_Rchild = badnode;
					badnode->p_parent = p;
					replacement->p_Lchild = p;
				}
			}
		}
		else {
			if (p->p_Rchild->p_Lchild == nullptr) {
				root = p->p_Rchild;
				root->p_parent = nullptr;
				p->p_Rchild = nullptr;
				root->p_Lchild = p;
				p->p_parent = root;
			}
			else {
				root = p->p_Rchild;
				root->p_parent = nullptr;
				badnode = root->p_Lchild;
				badnode->p_parent = p;
				p->p_Rchild = badnode;
				root->p_Lchild = p;
				p->p_parent = root;
			}
		}
	};//for insert_node, L-rotate at node pointed by p
	//All other siutions of insert_node should be directly implemented inside add_node


	//For delete, the deleted node shoud be the first of nodes with the same value in the order of
	//inorder traversal. (The same as HW5).
	//For replacement, always recursively replace it with predecessor, unless there is no predecessor. (In this
	//case, replace it with sucessor.)


	void delete_node(int i) {
		node* cursor = root;
		node* parentcopy = new node();
		node* childcopy = new node();
		node* lchildcopy = new node();
		node* rchildcopy = new node();
		node* faultnode = new node();
		node* replacement = new node();
		int lheight, rheight = 0;
		if (i != root->value) {
			node* nodetodelete = new node();
			while (1) {
				if (i > cursor->value&& cursor->p_Rchild == nullptr) {
					return;
				}
				else if (i < cursor->value && cursor->p_Lchild == nullptr) {
					return;
				}
				else if (i > cursor->value&& cursor->p_Rchild != nullptr) {
					cursor = cursor->p_Rchild;
				}
				else if (i < cursor->value && cursor->p_Lchild != nullptr) {
					cursor = cursor->p_Lchild;
				}
				else if (i == cursor->value) {
					nodetodelete = cursor;

					if (cursor->p_Lchild != nullptr && cursor->p_Rchild != nullptr) {
						if ((cursor->p_Rchild->color == false && cursor->p_Rchild->value == NULL) || (cursor->p_Lchild->color == false && cursor->p_Lchild->value == NULL)) {

							//delete_2A(cursor); //sibling of double black is black and has no red child
							//return;
						}
						cursor = cursor->p_Lchild;
						while (1) {

							if (cursor->p_Rchild == nullptr) {
								replacement = cursor;
								break;
							}
							cursor = cursor->p_Rchild;
						}
						nodetodelete->value = replacement->value;
						if (replacement->color) {
							parentcopy = replacement->p_parent;
							if (replacement->p_Lchild == nullptr && replacement->p_Rchild == nullptr) {
								if (parentcopy->p_Lchild == replacement) {
									parentcopy->p_Lchild = nullptr;
								}
								else if (parentcopy->p_Rchild == replacement) {
									parentcopy->p_Rchild = nullptr;
								}
								replacement = nullptr;
							}
							else if (replacement->p_Lchild != nullptr && replacement->p_Lchild->color == false) {

							}
							else if (replacement->p_Rchild != nullptr && replacement->p_Rchild->color == false) {

							}
							nodetodelete->value = replacement->value;
							replacement = nullptr;
						}
						else {
							parentcopy = replacement->p_parent;
							if (replacement->p_Lchild == nullptr && replacement->p_Rchild == nullptr) {
								nodetodelete->value = replacement->value;
								nodetodelete->color = false;
								replacement->value = NULL;
								replacement->color = false;
							}
							else if (replacement->p_Lchild != nullptr) {
								if (replacement->p_Lchild->color) {
									replacement->value = replacement->p_Lchild->value;
									if (parentcopy->p_Lchild == replacement) {
										parentcopy->p_Lchild = nullptr;
									}
									else if (parentcopy->p_Rchild == replacement) {
										parentcopy->p_Rchild = nullptr;
									}
									replacement = nullptr;
									replacement->p_Lchild = nullptr;
								}
							}
							else if (replacement->p_Rchild != nullptr) {
								if (replacement->p_Rchild->color) {
									replacement->value = replacement->p_Rchild->value;
									replacement->p_Rchild = nullptr;
								}

							}

						}
					}
					else if (cursor->p_Lchild == nullptr && cursor->p_Rchild != nullptr) {

						cursor = cursor->p_Rchild;
						while (1) {
							if (cursor->p_Lchild == nullptr) {
								replacement = cursor;
								break;
							}
							cursor = cursor->p_Lchild;
						}
						if (replacement->color) {
							nodetodelete->value = replacement->value;

							replacement = nullptr;
						}
						else {
							if (replacement->p_Lchild == nullptr && replacement->p_Rchild == nullptr) {

							}
							else if (replacement->p_Lchild != nullptr && replacement->p_Rchild == nullptr) {
								if (replacement->p_Lchild->color == false) {
									//CASES
								}
							}
							else if (replacement->p_Rchild != nullptr && replacement->p_Lchild == nullptr) {
								if (replacement->p_Rchild->color == false) {
									//CASES
								}
							}
						}
					}
					if (nodetodelete->color && nodetodelete->p_Lchild == nullptr && nodetodelete->p_Rchild == nullptr) {
						nodetodelete = nullptr;
					}
					else if (nodetodelete->color == false && nodetodelete->p_Lchild == nullptr && nodetodelete->p_Rchild == nullptr) {
						replacement->value = NULL;
						replacement->color = false;
						nodetodelete = replacement;
						nodetodelete->p_Lchild->value = NULL;
						nodetodelete->p_Rchild->value = NULL;
						nodetodelete->p_Lchild->color = false;
						nodetodelete->p_Rchild->color = false;

					}
					else if (nodetodelete->color == false && nodetodelete->p_Lchild == nullptr && nodetodelete->p_Rchild != nullptr) {

					}

				}
			}

		}
		else {
			cursor = root;
			if (cursor->p_Lchild != nullptr && cursor->p_Rchild != nullptr) {
				cursor = cursor->p_Lchild;
				while (1) {

					if (cursor->p_Rchild == nullptr) {
						replacement = cursor;
						break;
					}
					cursor = cursor->p_Rchild;
				}
				root->value = replacement->value;
				if (replacement->color) {
					if (replacement->p_Lchild == nullptr && replacement->p_Rchild == nullptr) {
						parentcopy = replacement->p_parent;
						if (parentcopy->p_Lchild == replacement) {
							parentcopy->p_Lchild = nullptr;
						}
						else if (parentcopy->p_Rchild == replacement) {
							parentcopy->p_Rchild = nullptr;
						}
						replacement = nullptr;
					}
					else if (replacement->p_Lchild != nullptr && replacement->p_Lchild->color == false) {

					}
					else if (replacement->p_Rchild != nullptr && replacement->p_Rchild->color == false) {

					}
					root->value = replacement->value;
					replacement = nullptr;
				}
				else {
					if (replacement->p_Lchild == nullptr && replacement->p_Rchild == nullptr) {
						root->value = replacement->value;
						root->color = false;
						replacement->value = NULL;
						replacement->color = false;
						//CASES
					}
					else if (replacement->p_Lchild != nullptr) {
						if (replacement->p_Lchild->color) {
							root->value = replacement->value;
							root->color = false;
							replacement->value = replacement->p_Lchild->value;
							replacement->p_Lchild = nullptr;
						}
					}
					else if (replacement->p_Rchild != nullptr) {
						if (replacement->p_Rchild->color) {
							root->value = replacement->value;
							root->color = false;
							replacement->value = replacement->p_Rchild->value;
							replacement->p_Rchild = nullptr;
						}

					}

				}
			}
		}
	};
	void delete_1(node* p); //case 1 of delete_node; p points to the parent of double black node
	void delete_1_R_rotate(node* p);//R_totate used in case 1 of delete_node; p points to the parent of double black node
	void delete_1_L_rotate(node* p);//L_totate used in case 1 of delete_node; p points to the parent of double black node
	void delete_2A(node* p); //case 2A of delete_node; p points to the parent of double black node
	void delete_2B(node* p);//case 2B of delete_node; p points to the parent of double black node
	void delete_3(node* p);//case 3 of delete_node; p points to the parent of double black node
	//All other cases of delete_node should be directly implemented inside the delete_node.

	//For the following, during traveral, print (value, color) of each node.
	void InorderPrint(node* p) {
		if (p == nullptr) {
			return;
		}
		node* cursor = p;
		InorderPrint(cursor->p_Lchild);
		if (p->color) {
			cout << p->value << " red" << endl;
		}
		else {
			cout << p->value << " black" << endl;
		}

		InorderPrint(cursor->p_Rchild);

	};
	void PostorderPrint(node* p) {
		if (p == nullptr) {
			return;
		}
		node* cursor = p;
		PostorderPrint(cursor->p_Lchild);
		PostorderPrint(cursor->p_Rchild);
		if (p->color) {
			cout << p->value << " red" << endl;
		}
		else {
			cout << p->value << " black" << endl;
		}
	};
	void PreorderPrint(node* p) {
		if (p == nullptr) {
			return;
		}
		node* cursor = p;
		if (p->color) {
			cout << p->value << " red" << endl;
		}
		else {
			cout << p->value << " black" << endl;
		}

		PreorderPrint(cursor->p_Lchild);
		PreorderPrint(cursor->p_Rchild);
	};
};

int main() {
	tree t1;
	t1.insert_node(45);
	//t1.in_order_traversal(t1.root);
	t1.insert_node(50);
	//t1.in_order_traversal(t1.root);
	t1.insert_node(40);
	//t1.in_order_traversal(t1.root);
	t1.insert_node(30);
	//t1.InorderPrint(t1.root);
	t1.insert_node(30);
	//t1.InorderPrint(t1.root);
	t1.insert_node(30);
	//t1.InorderPrint(t1.root);
	t1.insert_node(30);
	//t1.InorderPrint(t1.root);
	t1.insert_node(30);
	//t1.InorderPrint(t1.root);
	t1.insert_node(30);
	//t1.InorderPrint(t1.root);
	t1.insert_node(30);
	////t1.InorderPrint(t1.root);
	t1.insert_node(30);
	////t1.InorderPrint(t1.root);
	t1.insert_node(30);
	////t1.InorderPrint(t1.root);
	t1.insert_node(80);
	//t1.InorderPrint(t1.root);
	t1.insert_node(100);
	//t1.delete_node(45);
	t1.InorderPrint(t1.root);
	t1.delete_node(50);
	t1.InorderPrint(t1.root);
	t1.delete_node(40);
	t1.InorderPrint(t1.root);
	t1.delete_node(30);
	t1.InorderPrint(t1.root);
	t1.delete_node(30);
	t1.InorderPrint(t1.root);
	t1.delete_node(30);
	t1.delete_node(30);
	t1.InorderPrint(t1.root);
	t1.delete_node(30);
	t1.delete_node(30);
	t1.delete_node(30);
}
