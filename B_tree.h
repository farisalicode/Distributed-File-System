#pragma once
#include <iostream>
#include "BigHex.h"
#include "File_Handling.h"
#include "File.h"
using namespace std;





class node {
private:
public:
	File* data;
	node** arr;
	int count;
	node(int m) {
		this->data = new File[m];
		int i = m + 1;
		this->arr = new node * [i];
		for (int j = 0; j < i; j++)
			this->arr[j] = NULL;
		this->count = 0;
	}
};

class B_tree {
private:
public:
	node* rt;
	int m_arr;
	int min_k;
	B_tree(int m = 3) {
		this->rt = NULL;
		this->m_arr = m;
		if (m % 2) {
			this->min_k = m / 2;
		}
		else {
			this->min_k = (m / 2) - 1;
		}
	}
	void set_order(int m = 3)
	{
		this->rt = NULL;
		this->m_arr = m;
		if (m % 2)
		{
			this->min_k = m / 2;
		}
		else
		{
			this->min_k = (m / 2) - 1;
		}
		return;
	}
	void insert(File data) {
		if (this->rt == NULL) {
			this->rt = new node(this->m_arr);
			this->rt->data[this->rt->count] = data;
			this->rt->count++;
		}
		else {
			this->rt = insrt_hlp(data, this->rt);
		}
	}
	node* insrt_hlp(File data, node* t) {
		if (t == NULL) {
			t = new node(this->m_arr);
			t->data[t->count] = data;
			t->count++;
		}
		else if (t->arr[0] == NULL && t->arr[1] == NULL) {
			for (int i = 0; i < t->count; i++) {
				if (t->data[i] == data) {
					t->data[i].insert_next(data);
					return t;
				}
			}
			t->data[t->count] = data;
			t->count++;
			sort(t);
			//check if we exceeded the capcity of the node
			if (t->count == m_arr) {
				node* tmp1 = new node(m_arr); //level above
				node* tmp2 = new node(m_arr); //split and join
				int mid;
				//finds the middle key
				if (m_arr % 2) {
					mid = m_arr / 2;
				}
				else {
					mid = (m_arr / 2) - 1;
				}
				//middle key gets copied to tmp1 to go up a level
				tmp1->data[tmp1->count] = t->data[mid];
				tmp1->count++;
				//the node that is going to level above
				//it's left and right child are being attached
				tmp1->arr[0] = t;
				tmp1->arr[1] = tmp2;
				//middle key is being freed up
				t->data[mid] = garbage;
				t->count--;
				for (int i = mid + 1; i < m_arr; i++) {
					tmp2->data[tmp2->count] = t->data[i];
					tmp2->count++;
					t->data[i] = garbage;
					t->count--;
				}
				////prints the level up node
				//cout << "Level UP Node: ";
				//for (int i = 0; i < tmp1->count; i++)
				//	cout << "   " << tmp1->data[i]<<" ";
				//cout << endl;
				//cout << "Left Node: ";
				////prints the left node
				//for (int i = 0; i < t->count; i++)
				//	cout << t->data[i] << " ";
				//cout << "Right Node: ";
				////prints the right node
				//for (int i = 0; i < tmp2->count; i++)
				//	cout << tmp2->data[i] << " ";
				//cout << endl;
				return tmp1;
				//its left child contains the node having all the data that is less than the middle value
				//its right child contains the node having all the data that is greater than the middle value

			}
			//cout << "Node had space: ";
			////prints the node if the node had available space to insert new data
			//for (int i = 0; i < t->count; i++)
			//	cout << t->data[i] << " ";
			//cout << endl;
			return t;
		}
		else if (t->arr[0] && t->arr[1]) {
			for (int i = 0; i < t->count; i++) {
				if (t->data[i] == data) {
					t->data[i].insert_next(data);
					return t;
				}
			}
			int idx = 0;//helps in identifying which child subtree to move to
			for (int i = 0; i < m_arr; i++) {
				if (t->data[i] > data) { //left child subtree
					break;
				}
				else if (t->data[i] < data && (t->data[i + 1].file_ID.hex == garbage || t->data[i + 1] > data)) {
					//right child subtree
					idx++;
					break;
				}
				idx++;
			}
			node* tmp = insrt_hlp(data, t->arr[idx]);
			//checks splitting happened on its child node
			if (tmp != t->arr[idx] && t->count < (m_arr - 1)) {
				t->data[t->count] = tmp->data[0];
				t->count++;
				sort(t);
				//adjustment of lvl up node child in the current node
				t->arr[idx] = tmp->arr[0];
				t->arr[idx + 1] = tmp->arr[1];
				//free memory
				delete[] tmp->data;
				delete tmp->arr;
				delete tmp;
				////parent node had space
				//cout << "parent node had space: ";
				//for (int i = 0; i < t->count; i++)
				//	cout << t->data[i]<<" ";
				//cout << endl;
				return t;
			}
			else if (tmp != t->arr[idx] && t->count == (m_arr - 1)) {
				t->data[t->count] = tmp->data[0];
				t->count++;
				sort(t);
				t->arr[idx] = tmp->arr[0];
				t->arr[idx + 1] = tmp->arr[1];

				node* tmp1 = new node(m_arr); //level above
				node* tmp2 = new node(m_arr); //split and join

				int mid;
				if (m_arr % 2) {
					mid = m_arr / 2;
				}
				else {
					mid = (m_arr / 2) - 1;
				}
				tmp1->data[tmp1->count] = t->data[mid];
				tmp1->count++;
				tmp1->arr[0] = t;
				tmp1->arr[1] = tmp2;
				t->data[mid] = garbage;
				t->count--;

				for (int i = mid + 1; i < m_arr; i++) {
					tmp2->data[tmp2->count] = t->data[i];
					tmp2->arr[tmp2->count] = t->arr[i];
					tmp2->count++;
					t->arr[i] = NULL;
					t->data[i] = garbage;
					t->count--;
				}
				tmp2->arr[tmp2->count] = t->arr[m_arr];
				t->arr[m_arr] = NULL;
				//free memory
				delete[] tmp->data;
				delete tmp->arr;
				delete tmp;
				//cout << "Level UP Node: ";
				//for (int i = 0; i < tmp1->count; i++)
				//	cout << "   " << tmp1->data[i] << " ";
				//cout << endl;
				//cout << "Left Node: ";
				////prints the left node
				//for (int i = 0; i < t->count; i++)
				//	cout << t->data[i] << " ";
				//cout << "Right Node: ";
				////prints the right node
				//for (int i = 0; i < tmp2->count; i++)
				//	cout << tmp2->data[i] << " ";
				//cout << endl;

				return tmp1;
			}
		}
		return t;
	}
	void sort(node* t) {
		bool flag = true;
		while (flag) {
			flag = false;
			for (int i = 0; i < t->count - 1; i++) {
				if (t->data[i] > t->data[i + 1]) {
					flag = true;
					File tmp1 = t->data[i];
					t->data[i] = t->data[i + 1];
					t->data[i + 1] = tmp1;
					node* tmp = t->arr[i + 1];
					t->arr[i + 1] = t->arr[i];
					t->arr[i + 2] = tmp;
				}
			}
		}
	}
	void del(File val) {
		if (this->search_b_tree_ret_bool(val)) {
			if (this->rt->arr[0] == NULL) {
				bool flag = false;
				int i = 0;
				for (; i < this->rt->count; i++) {
					if (this->rt->data[i] == val) {
						flag = true;
						break;
					}
				}
				if (flag) {
					this->rt->count--;
					l_shift(this->rt, i);
					if (this->rt->count == 0) {
						this->rt->data[0].del_nxt();
						delete[] this->rt->data;
						delete[] this->rt->arr;
						delete this->rt;
						this->rt = NULL;
					}
				}
			}
			else {
				bool flag = false;
				int i = 0;
				for (; i < this->rt->count; i++) {
					if (this->rt->data[i] == val) {
						flag = true;
						break;
					}
				}
				if (flag) {
					File value = this->find_max(this->rt->arr[i]);
					this->rt->data[i] = value;
					this->rt = del_hlp(value, this->rt);
				}
				else {
					this->rt = del_hlp(val, this->rt);
				}

			}
		}

	}
	node* del_hlp(File val, node* t) {
		if (t == NULL) {
			return t;
		}
		else {
			//loop below finds the value in the child node
			//and records the in which child and at which data arr position
			bool flg_fnd_in_chld = false;
			int i = 0, j = 0;
			for (; i <= t->count; i++) {
				for (; j < t->arr[i]->count; j++) {
					if (t->arr[i]->data[j] == val) {
						flg_fnd_in_chld = true;
						break;
					}
				}
				if (flg_fnd_in_chld) {
					break;
				}
				else {
					j = 0;
				}
			}
			//if the data was not found in immediate children
			if (flg_fnd_in_chld == false) {
				int idx = 0;
				//in here we find in which child should we move
				//and record the index in idx
				for (; idx < t->count; idx++) {
					if (t->data[idx] >= val) {
						break;
					}
					else if (t->data[idx] < val && (t->data[idx + 1].file_ID.hex == garbage || t->data[idx] > val)) {
						idx++;
						break;
					}
				}
				t->arr[idx] = del_hlp(val, t->arr[idx]);
				//don't return check if it's child are valid or not from there return
			}
			else {
				//if the value found is at leaf node
				if (t->arr[i]->arr[0] == NULL) {
					//checks if that leaf node have more keys 
					// then minimum keys required per node
					if (t->arr[i]->count > this->min_k) {
						t->arr[i]->data[j].del_nxt();
						t->arr[i]->count--;
						this->l_shift(t->arr[i], j);
						return t;
					}
					else {
						//here we check if left sibling have enough keys to share
						if (i != 0 && t->arr[i - 1]->count > this->min_k) {
							File tmp = t->arr[i - 1]->data[t->arr[i - 1]->count - 1];
							t->arr[i - 1]->count--;
							this->l_shift(t->arr[i - 1], t->arr[i - 1]->count);
							//frees up the chain if exist
							t->arr[i]->data[j].del_nxt();
							t->arr[i]->count--;
							this->l_shift(t->arr[i], j);
							t->arr[i]->data[t->arr[i]->count] = t->data[i - 1];
							t->arr[i]->count++;
							this->sort(t->arr[i]);
							t->data[i - 1] = tmp;
							return t;
						}
						//check if right sibling have enough keys to share
						else if (i != t->count && (t->arr[i + 1]->count > this->min_k)) {
							File tmp = t->arr[i + 1]->data[0];
							t->arr[i + 1]->count--;
							this->l_shift(t->arr[i + 1], 0);
							//frees up the next chain if exist
							t->arr[i]->data[j].del_nxt();
							t->arr[i]->count--;
							this->l_shift(t->arr[i], j);
							t->arr[i]->data[t->arr[i]->count] = t->data[i];
							t->arr[i]->count++;
							t->data[i] = tmp;
							return t;
						}
						else {
							//if sharing is not possible
							// we merge the nodes including the median value
							if (i == 0) {
								//if we are at the left most child 
								// we will only merge with the right sibling
								//median parent is apparent
								node* tmp = t->arr[i + 1];
								tmp->data[tmp->count] = t->data[i];
								tmp->count++;
								this->sort(tmp);
								for (int k = 0; k < t->arr[i]->count; k++) {
									if (t->arr[i]->data[k] != val) {
										tmp->data[tmp->count] = t->arr[i]->data[k];
										tmp->count++;
										this->sort(tmp);
									}
								}
								t->count--;
								//here we check if the median parent merge was the only key that parent node had
								if (t == this->rt && t->count == 0) {
									//first clear the child node data members dma
									//frees up the chain first
									t->arr[i]->data[j].del_nxt();
									delete[] t->arr[i]->data;
									delete[] t->arr[i]->arr;
									//then clear that child from parent
									delete t->arr[i];
									//clear parent key data array
									delete[] t->data;
									// only delete two d pointer
									delete[] t->arr;
									delete t;
									//return the newly merged node back from where it was called and attached itself there
									return tmp;
								}
								else {
									//first clear the child node data members dma
									//frees up the chain first
									t->arr[i]->data[j].del_nxt();
									delete[] t->arr[i]->data;
									delete[] t->arr[i]->arr;
									//then clear that child from parent
									delete t->arr[i];
									t->arr[i] = NULL;
									//all the keys to the right of median parent shifts left along with the child arr
									this->l_shift(t, i);
									return t;
								}
							}
							else if (i != t->count) {
								//if we are in somewhere between not at the end
								//then we will merge node with the left sibling
								node* tmp = t->arr[i - 1];
								//we first remove the targeted key
								//frees up the chain first
								t->arr[i]->data[j].del_nxt();
								t->arr[i]->count--;
								this->l_shift(t->arr[i], j);
								//then we copy the median key parent in the same node
								t->arr[i]->data[t->arr[i]->count] = t->data[i - 1];
								t->arr[i]->count++;
								//and call sort
								this->sort(t->arr[i]);
								//then we start copying left sibling keys in the same node
								// one by one and also sort on each key copy
								for (int k = 0; k < t->arr[i - 1]->count; k++) {
									t->arr[i]->data[t->arr[i]->count] = tmp->data[k];
									t->arr[i]->count++;
									this->sort(t->arr[i]);

								}
								tmp->count--;
								//first clear the child node data members dma
								//frees up the chain first
								t->arr[i - 1]->data[j].del_nxt();
								delete[] tmp->data;
								delete[] tmp->arr;
								//then clear that child from parent
								delete t->arr[i - 1];
								t->arr[i - 1] = NULL;
								t->count--;
								//all the keys to the right of median parent shifts left along with the child arr
								this->l_shift(t, i - 1);
								return t;
							}
							else {
								//if we are the right most child
								//we will only merge with the immediate left sibling
								node* tmp = t->arr[i - 1];
								//here we are freeing targeted key chain
								t->arr[i]->data[j].del_nxt();
								//here we are freeing up the targeted key fron data array
								t->arr[i]->count--;
								this->l_shift(t->arr[i], j);
								//here we are making space fro the median key parent to come at the start of targeted node's data array
								this->r_shift(t->arr[i], 0);
								//here we are copying median key parent in the targeted node at the start of data array 
								// because median parent is smallest as we are moving parent to its right child's node
								t->arr[i]->data[0] = t->data[i - 1];
								//no need to sort cause median parent will be in correct position in left child
								t->arr[i]->count++;
								//here we copy left child keys into the  right child 
								// no need to sort cause all the keys are greater then left child keys
								for (int k = 0; k < tmp->count; k++) {
									t->arr[i]->data[t->arr[i]->count] = tmp->data[k];
									t->arr[i]->count++;
								}
								//here we consider the possible effect or removing median parent
								t->count--;
								//if the node had only median parent
								//we will now have new parent 
								// which would be the newly merged node
								if (t == this->rt && t->count == 0) {
									// free up the left child data members
									delete[] tmp->data;
									delete[] tmp->arr;
									// free up the right child node
									delete t->arr[i - 1];
									//here we copy the pointer of only node left so that it can be sent as a return paramete
									tmp = t->arr[i];
									//clear parent key data array
									delete[] t->data;
									// only delete two d pointer
									delete[] t->arr;
									//delete the parent node
									delete t;
									//return the newly merged node back from where it was called and attached itself there
									return tmp;
								}
								else {
									// free up the left child data members

									delete[] tmp->data;
									delete[] tmp->arr;
									// free up the right child node
									delete t->arr[i - 1];
									t->arr[i - 1] = NULL;
									//moves every key to the left so to fill space of previously occupied median parent
									this->l_shift(t, i - 1);
									return t;
								}
							}
						}
					}
				}
				else {
					//if the targeted key found is internal node
					//then find the max value from the left child of the targeted key
					File value = this->find_max(t->arr[i]->arr[j]);
					//override the targeted value that max value
					t->arr[i]->data[j] = value;
					//call del_hlp to delete that max val from leaf node
					node* tmp = this->del_hlp(value, t->arr[i]);
					//as leaf key was deleted was from left child of that targeted key
					//hence it should be reattached with the left child of that internal targeted key
					t->arr[i] = tmp;
				}

			}
			bool flag_1 = false;
			int m = 0;
			//here we check if the child/internal/nodes have atleast min number of keys
			for (; m <= t->count; m++) {
				if (t->arr[m]->count < this->min_k) {
					flag_1 = true;
					break;
				}
			}
			if (flag_1) {
				//invalid node is not at the start (it is at middle or last)
				// then first check if sharing can be done with the left sibling 
				if (m != 0 && (t->arr[m - 1]->count > this->min_k)) {
					node* tmp = t->arr[m - 1];
					//this makes room for the median parent key to come at the start of data array of right child
					// and also makes room for the median parent key's left child's highest key's right child's pointer
					//at the start of the median parent key's right child's 2D array 
					this->r_shift(t->arr[m], 0);
					//here we set the median parent key at the start of data array
					t->arr[m]->data[0] = t->data[m - 1];
					//here we set the median parent key's left child's highest key's right child's pointer
					//at the start of the median parent key's right child's 2D array
					t->arr[m]->arr[0] = tmp->arr[tmp->count];
					t->arr[m]->count++;
					//here we overrides the median parent key with its left child's highest key
					t->data[m - 1] = tmp->data[tmp->count - 1];
					//empties the left child's highest key and highest child
					tmp->arr[tmp->count] = NULL;
					tmp->data[tmp->count - 1] = garbage;
					tmp->count--;
					return t;

				}
				//invalid node is not at the end (it is at middle or first)
				//then check if sharing can be done with the right sibling
				else if (m != t->count && (t->arr[m + 1]->count > this->min_k)) {
					node* tmp = t->arr[m + 1];
					//sets the median parent key to end of invalid node
					t->arr[m]->data[t->arr[m]->count] = t->data[m];
					t->arr[m]->count++;
					//sets the median parent key's left child's lowest key's left child's pointer
					//at the end of the  median parent key's left child's 2D array
					t->arr[m]->arr[t->arr[m]->count] = tmp->arr[0];
					t->data[m] = tmp->data[0];
					//empties the right child's lowest key
					tmp->count--;
					this->l_shift(tmp, 0);
					return t;
				}
				else {
					//if sharing is not possible among internal nodes
					if (m == 0) {
						//if the left most child is invalid
						//merge with the immediate right child
						node* tmp = t->arr[m + 1];
						//sets the median parent key at the end of its left child's data array
						t->arr[m]->data[t->arr[m]->count] = t->data[m];
						t->arr[m]->count++;
						bool flag_once_2 = true;
						//copies right child keys and 2d array into left child's data array and 2D array
						for (int g = 0; g < tmp->count; g++) {
							t->arr[m]->data[t->arr[m]->count] = tmp->data[g];
							if (flag_once_2) {
								t->arr[m]->arr[t->arr[m]->count] = tmp->arr[g];
								flag_once_2 = false;
							}
							t->arr[m]->count++;
							t->arr[m]->arr[t->arr[m]->count] = tmp->arr[g + 1];
						}
						t->count--;
						//if median was the only key 
						//then t->arr[m] is the new child if its grandparent
						if (t == this->rt && t->count == 0) {
							node* tmp_1 = t->arr[m];
							delete[] tmp->data;
							delete[] tmp->arr;
							delete	tmp;
							//frees up the chain first
							t->data[0].del_nxt();
							delete[] t->data;
							delete[] t->arr;
							delete t;
							return tmp_1;
						}
						else {
							delete[] tmp->data;
							delete[] tmp->arr;
							delete	tmp;
							//it transfers the all the nodes data of left child to the right child 
							//so to accomodate l_shift functionality
							t->arr[m + 1] = t->arr[m];
							//keys of node of previously median parent, is shift left  
							this->l_shift(t, m);
							return t;
						}
					}
					else if (m != t->count) {
						//if invalid node is at somewhere in the middle
						//we'll merge with the left child
						node* tmp = t->arr[m - 1];
						//sets the median parent key at the end of its left child's data array
						tmp->data[tmp->count] = t->data[m - 1];
						tmp->count++;
						bool flag_2 = true;
						//copies right child keys and 2d array into left child's data array and 2D array
						for (int g = 0; g < t->arr[m]->count; g++) {
							tmp->data[tmp->count] = t->arr[m]->data[g];
							if (flag_2) {
								tmp->arr[tmp->count] = t->arr[m]->arr[g];
								flag_2 = false;
							}
							tmp->count++;
							tmp->arr[tmp->count] = t->arr[m]->arr[g + 1];

						}
						//frees up the memory of invalid node
						delete[] t->arr[m]->data;
						delete[] t->arr[m]->arr;
						delete t->arr[m];
						//sets the newly merged node in place of invalid node
						t->arr[m] = tmp;
						t->count--;
						this->l_shift(t, m - 1);
						return t;
					}
					else {
						//if invalid node is at somewhere in the middle
						//we'll merge with the left child
						node* tmp = t->arr[m - 1];
						//sets the median parent key at the end of its left child's data array
						tmp->data[tmp->count] = t->data[m - 1];
						tmp->count++;
						bool flag_2 = true;
						//copies right child keys and 2d array into left child's data array and 2D array
						for (int g = 0; g < t->arr[m]->count; g++) {
							tmp->data[tmp->count] = t->arr[m]->data[g];
							if (flag_2) {
								tmp->arr[tmp->count] = t->arr[m]->arr[g];
								flag_2 = false;
							}
							tmp->count++;
							tmp->arr[tmp->count] = t->arr[m]->arr[g + 1];
						}
						t->count--;
						//if median was the only key 
						//then t->arr[m] is the new child if its grandparent
						if (t == this->rt && t->count == 0) {
							delete[] t->arr[m]->data;
							delete[] t->arr[m]->arr;
							delete	t->arr[m];
							//frees up the chain first
							t->data[0].del_nxt();
							delete[] t->data;
							delete[] t->arr;
							delete t;
							return tmp;
						}
						else {
							delete[] t->arr[m]->data;
							delete[] t->arr[m]->arr;
							delete	t->arr[m];
							t->arr[m] = tmp;
							//keys of node of previously median parent, is shift left 
							this->l_shift(t, m - 1);
							return t;
						}
					}
				}
			}
			else {
				return t;
			}


		}
	}
	File& find_max(node* t) {
		while (t->arr[0]) {
			t = t->arr[t->count];
		}
		return t->data[t->count - 1];
	}
	void r_shift(node* t, int i) {
		bool flag_once = true;
		for (int k = t->count - 1; k >= i; k--) {
			t->data[k + 1] = t->data[k];
			if (flag_once) {
				t->arr[k + 2] = t->arr[k + 1];
				flag_once = false;
			}
			t->arr[k + 1] = t->arr[k];
		}
	}
	void l_shift(node* t, int i) {
		bool flag_once = true;
		int j = i;
		for (; j <= t->count; j++) {
			t->data[j] = t->data[j + 1];
			if (flag_once) {
				t->arr[j] = t->arr[j + 1];
				flag_once = false;
			}
			t->arr[j + 1] = t->arr[j + 2];
		}

	}
	void print_b_tree()
	{
		cout << "\nPrinting B-tree;" << '\n';
		inorder_traversal(this->rt);
	}
	void inorder_traversal(node* t)
	{
		if (t == nullptr)
		{
			return;
		}
		else
		{
			if (t->arr[0])
			{
				for (int i = 0; i < t->count; i++)
				{
					if (i == 0)
					{
						inorder_traversal(t->arr[i]);
					}
					t->data[i].print_file();
					cout << "\n";
					inorder_traversal(t->arr[i + 1]);
				}
			}
			else
			{
				//here we print all the files that are at the leaf node
				for (int j = 0; j < t->count; j++)
				{
					t->data[j].print_file();
					cout << "\n";
				}
			}

		}
	}
	bool src_ret_bool(node* t, File val) {
		if (t == NULL) {
			return false;
		}
		else {
			//here we check if the targeted file is in the current node or not
			for (int i = 0; i < t->count; i++) {
				if (t->data[i] == val) {
					return true;
				}
			}
			//we wil only get out of upper loop file not found in the current node

			//below we finds the right direction to move to
			int j = 0;
			for (; j < t->count; j++) {
				if (t->data[j] > val) {
					break;
				}
				else if (t->data[j] < val && (t->data[j + 1] > val || t->data[j + 1].file_ID.hex == garbage)) {
					j++;
					break;
				}
			}
			return this->src_ret_bool(t->arr[j], val);
		}
	}
	bool search_b_tree_ret_bool(File val) {
		return src_ret_bool(this->rt, val);
	}
	File* src_ret_file(node* t, File val) {

		//here we check if the targeted file is in the current node or not
		for (int i = 0; i < t->count; i++) {
			if (t->data[i] == val) {
				return (t->data+i);
			}
		}
		//we wil only get out of upper loop file not found in the current node

		//below we finds the right direction to move to
		int j = 0;
		for (; j < t->count; j++) {
			if (t->data[j] > val) {
				break;
			}
			else if (t->data[j] < val && (t->data[j + 1] > val || t->data[j + 1].file_ID.hex == garbage)) {
				j++;
				break;
			}
		}
		return this->src_ret_file(t->arr[j], val);

	}
	File* search_b_tree_ret_file(File val) {
		if (this->search_b_tree_ret_bool(val)) {
			return src_ret_file(this->rt, val);
		}
		else {
			return nullptr;
		}

	}


};

void share_file_insertion(B_tree& b_t, File file, node* t,string const_new_path) {
	if (t == nullptr)
	{
		return;
	}
	else
	{
		if (t->arr[0])
		{
			for (int i = 0; i < t->count; i++)
			{
				if (i == 0)
				{
					share_file_insertion(b_t, file, t->arr[i], const_new_path);
				}
				if (t->data[i] <= file) {
					t->data[i].transfer(const_new_path);
					b_t.insert(t->data[i]);
				}
				share_file_insertion(b_t, file, t->arr[i + 1], const_new_path);
			}
		}
		else
		{
			//here we print all the files that are at the leaf node
			for (int j = 0; j < t->count; j++)
			{
				if (t->data[j] <= file) {
					t->data[j].transfer(const_new_path);
					b_t.insert(t->data[j]);
				}
			}
		}

	}

}

void share_file_deletion(B_tree& b_t, node* t) {
	if (t == nullptr)
	{
		return;
	}
	else
	{
		if (t->arr[0])
		{
			for (int i = 0; i < t->count; i++)
			{
				if (i == 0)
				{
					share_file_deletion(b_t, t->arr[i]);
				}
				b_t.del(t->data[i]);

				share_file_deletion(b_t, t->arr[i + 1]);
			}
		}
		else
		{
			//here we print all the files that are at the leaf node
			for (int j = 0; j < t->count; j++)
			{
				b_t.del(t->data[j]);
			}
		}

	}

}


void share_file_to_head_insertion(B_tree& b_t, node* t, string const_new_path) {
	if (t == nullptr) {
		return;
	}
	else
	{
		if (t->arr[0])
		{
			for (int i = 0; i < t->count; i++)
			{
				if (i == 0)
				{
					share_file_to_head_insertion(b_t, t->arr[i], const_new_path);
				}
				
				t->data[i].transfer(const_new_path);
					b_t.insert(t->data[i]);
				
					share_file_to_head_insertion(b_t, t->arr[i + 1], const_new_path);
			}
		}
		else
		{
			//here we print all the files that are at the leaf node
			for (int j = 0; j < t->count; j++)
			{
				t->data[j].transfer(const_new_path);
					b_t.insert(t->data[j]);
			}
		}

	}
}

void share_file_to_head_tail_insertion(B_tree& b_t, File tail_id, File curr_id, node* t, string const_new_path) {
	if (t == nullptr)
	{
		return;
	}
	else
	{
		if (t->arr[0])
		{
			for (int i = 0; i < t->count; i++)
			{
				if (i == 0)
				{
					share_file_to_head_tail_insertion(b_t, tail_id, curr_id, t->arr[i], const_new_path);
				}
				if (t->data[i] <= curr_id && t->data[i]>tail_id) {
					t->data[i].transfer(const_new_path);
					b_t.insert(t->data[i]);
				}
				share_file_to_head_tail_insertion(b_t, tail_id, curr_id, t->arr[i+1], const_new_path);
			}
		}
		else
		{
			//here we print all the files that are at the leaf node
			for (int j = 0; j < t->count; j++)
			{
				if (t->data[j] <= curr_id && t->data[j] > tail_id) {
					t->data[j].transfer(const_new_path);
					b_t.insert(t->data[j]);
				}
			}
		}

	}

}
void share_file_to_head_insertion(B_tree& b_t, File tail_id, File curr_id, node* t, string const_new_path) {
	if (t == nullptr)
	{
		return;
	}
	else
	{
		if (t->arr[0])
		{
			for (int i = 0; i < t->count; i++)
			{
				if (i == 0)
				{
					share_file_to_head_tail_insertion(b_t, tail_id, curr_id, t->arr[i], const_new_path);
				}
				if (t->data[i] <= curr_id || t->data[i] > tail_id) {
					t->data[i].transfer(const_new_path);
					b_t.insert(t->data[i]);
				}
				share_file_to_head_tail_insertion(b_t, tail_id, curr_id, t->arr[i + 1], const_new_path);
			}
		}
		else
		{
			//here we print all the files that are at the leaf node
			for (int j = 0; j < t->count; j++)
			{
				if (t->data[j] <= curr_id || t->data[j] > tail_id) {
					t->data[j].transfer(const_new_path);
					b_t.insert(t->data[j]);
				}
			}
		}

	}
}


void transfer_b_tree_files(B_tree& b_t_0, File file, B_tree& b_t_1, string const_new_path) {
	if (b_t_1.rt!=NULL) {
		share_file_insertion(b_t_0, file, b_t_1.rt, const_new_path);
		share_file_deletion(b_t_1, b_t_0.rt);
	}
	
}

void transfer_file_tail_head(B_tree& b_t_0, B_tree& b_t_1, string const_new_path) {
	if (b_t_1.rt != NULL) {
	share_file_to_head_insertion(b_t_0,  b_t_1.rt, const_new_path);
	share_file_deletion(b_t_1, b_t_0.rt);
	}
}

//if machine is added to tail then
//the files in head which are greater then tail's id and less then or equal to new machine id
//are inserted to new machine   
void transfer_file_to_new_tail_head(B_tree& b_t_0,File tail_id,File curr_id,B_tree& b_t_1,string const_new_path) {
	if (b_t_1.rt != NULL) {
		share_file_to_head_tail_insertion(b_t_0, tail_id,curr_id, b_t_1.rt, const_new_path);
		share_file_deletion(b_t_1, b_t_0.rt);
	}
}
void transfer_file_to_new_head(B_tree& b_t_0, File tail_id, File curr_id, B_tree& b_t_1, string const_new_path) {
	if (b_t_1.rt != NULL) {
		share_file_to_head_insertion(b_t_0, tail_id, curr_id, b_t_1.rt, const_new_path);
		share_file_deletion(b_t_1, b_t_0.rt);
	}
}