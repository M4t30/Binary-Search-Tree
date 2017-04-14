#include <iostream>
#include <cmath>
#include <ctime>
#include <string>
using namespace std;

//************************************************************************************************************************

struct node;

void insertNode(node * &Root, int x, node *prev, int &size);
void insertNNodesWithRandomValues(node* &Root, node *prev, int &size, int x);
void deleteEntireTree(node* &Root);
void inOrder(node *Root);
node* findNodeWithMinimumValue(node *Root);
node* findNodeWithMaximumValue(node *Root);
node* findSuccessorMinimum(node* Root);
node* FindPredecessor(node *Root, int x);
node* findSuccessor(node *Root, int x);
node* FindNodeWithSetValue(node *Root, int x);
void DSW(node* &Root, int size);
void deleteChosenNode(node* &Root, int x);
void show(string sp, string sn, node *Root);
void rotateRight(node* &Root);
void rotateLeft(node* &Root);

//************************************************************************************************************************

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                                                                                                             
struct node
{
	int val;
	node *prev;
	node *left;
	node *right;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

string cr, cl, cp;

//************************************************************************************************************************
                                                                                                                    
int main()
{
	cr = cl = cp = "  ";
	cr[0] = 218; cr[1] = 196;
	cl[0] = 192; cl[1] = 196;
	cp[0] = 179;

	int x, size = 0;
	node *Root = NULL;
	node *a = NULL;
	int choice;
	int choice2;
	cout << "[BINARY TREE]";
	do
	{
		cout << "\n1. Show menu" << endl
			 << "2. Run functions" << endl;
		cin >> choice;
		switch (choice)
		{
		case 1:
			cout << "1. Add element" << endl
				 << "2. Add n elements with random values" << endl
				 << "3. Delete every node in tree" << endl
				 << "4. Find node with minimum value" << endl
				 << "5. Find node with maximum value" << endl
				 << "6. Find successor of node with minimum value" << endl
				 << "7. Find predecessor of any element" << endl
				 << "8. Find successor of any element" << endl
			     << "9. Find element with set value" << endl
				 << "10. Rownowazenie drzewa binarnego" << endl
			     << "11. Day-Stout-Warren algorithm"<< endl
				 << "12. Show tree (in-order)" << endl
				 << "13. Show tree" << endl
				 << "0. Exit" << endl;
			break;

		case 2:
			cout << "Chose function: ";
			cin >> choice2;
			switch (choice2)
			{
			case 1:
				cout << "Enter element value: ";
				cin >> x;
				insertNode(Root, x, NULL, size);                                                         
				break;

			case 2:
				cout << "Enter amount of elements which you want to add: ";           
				cin >> x;
				insertNNodesWithRandomValues(Root, NULL, size, x);
				break;

			case 3:
				deleteEntireTree(Root);                                                              
				break;

			case 4:
				a = findNodeWithMinimumValue(Root);                                               
				break;

			case 5:
				a = findNodeWithMaximumValue(Root);                                                
				break;

			case 6:
				a = findSuccessorMinimum(Root);                                    
				cout << a->val;
				break;

			case 7:
				cout << "Enter element value for which would you like to find predecessor: ";
				cin >> x;
				a = FindPredecessor(Root, x);                                         
				break;

			case 8:
				cout << "Enter element value for which would you like to find successor: ";
				cin >> x;
				a = findSuccessor(Root, x);                                         
				break;

			case 9:
				cout << "Enter element value which would you like to find: ";                   
				cin >> x;
				a = FindNodeWithSetValue(Root, x);
				cout << a->val;
				break;

			case 10:
				DSW(Root, size);                                                           
				break;

			case 11:
				cout << "Enter element value which would you like to deletec: ";                     
				cin >> x;
				deleteChosenNode(Root, x);
				break;

			case 12:
				inOrder(Root);                                                                         
				break;

			case 13:
				show("", "", Root);                                                                    
				break;
			}
		}

	} while (choice != 0);
}

//************************************************************************************************************************
                                                                                              
void insertNode(node * &Root, int x, node *prev, int &size)
{
	if (Root == NULL)
	{
		Root = new node;
		Root->val = x;
		Root->prev = prev;
		Root->left = NULL;
		Root->right = NULL;
		if (prev != NULL && prev->val < Root->val)
			prev->right = Root;
		if(prev != NULL && prev->val > Root->val)
			prev->left = Root;
		size++;
	}

	else
	{
		if (x < Root->val)
			insertNode(Root->left, x, Root, size);

		else
			insertNode(Root->right, x, Root, size);
	}
}

//************************************************************************************************************************
                                                                                
void insertNNodesWithRandomValues(node* &Root, node* prev, int &size, int x)
{
	srand(time(NULL));

	while (x > 0)
	{
		if (Root == NULL)
		{
			Root = new node;
			Root->val = rand()%1000;
			Root->prev = prev;
			Root->left = NULL;
			Root->right = NULL;
			if (prev != NULL && prev->val < Root->val)
				prev->right = Root;
			if (prev != NULL && prev->val > Root->val)
				prev->left = Root;
			size++;
		}

		else
		{
			if (x < Root->val)
				insertNode(Root->left, x, Root, size);

			else
				insertNode(Root->right, x, Root, size);
		}

		x--;
	}
}

//************************************************************************************************************************
                                                                                                        
void deleteEntireTree(node* &Root)
{
	if (Root != NULL)
	{
		deleteEntireTree(Root->left);
		deleteEntireTree(Root->right);
		delete Root;
	}
	Root = NULL;
}

//************************************************************************************************************************
                                                                                  
node* findNodeWithMinimumValue(node *Root)
{
	if (Root != NULL)
	{
		if (Root->left != NULL)
			findNodeWithMinimumValue(Root->left);

		else
			return Root;
	}

	else
		return Root;
}

//************************************************************************************************************************
                                                                                  
node* findNodeWithMaximumValue(node *Root)
{
	if (Root != NULL)
	{
		if (Root->right != NULL)
			findNodeWithMaximumValue(Root->right);

		else
			return Root;
	}

	else
		return Root;
}

//************************************************************************************************************************
                                                                                          
node* findSuccessorMinimum(node* Root)
{
	if (Root != NULL)
	{
		if (Root->right != NULL)
			return findNodeWithMinimumValue(Root->right);

		else
		{
			node * tmp = findNodeWithMinimumValue(Root);
			tmp = tmp->prev;
			Root = tmp->left;

			while (tmp != NULL && tmp->left != Root)
			{
				Root = tmp;
				tmp = tmp->prev;
			}

			return tmp;
		}
	}

	else
		return Root;
}

//************************************************************************************************************************
                                                                                                       
node* FindPredecessor(node *Root, int x)
{
	if (Root != NULL)
	{
		node *tmp = FindNodeWithSetValue(Root, x);

		if (tmp->left != NULL)
		{
			tmp = findNodeWithMaximumValue(tmp->left);
			return tmp;
		}

		if (tmp->left == NULL)
		{
			node *tmp_prev = tmp->prev;

			while (tmp_prev != NULL && tmp_prev->right != tmp)
			{
				tmp = tmp_prev;
				tmp_prev = tmp_prev->prev;
			}

			return tmp_prev;
		}
	}

	else
		return NULL;
}

//************************************************************************************************************************
                                                                                                        
node* findSuccessor(node *Root, int x)
{
	if (Root != NULL)
	{
		node *tmp = FindNodeWithSetValue(Root, x);

		if (tmp->right != NULL)
		{
			tmp = findNodeWithMinimumValue(tmp->right);
			return tmp;
		}

		if (tmp->right == NULL)
		{
			node *tmp_prev = tmp->prev;

			while (tmp_prev != NULL && tmp_prev->left != tmp)
			{
				tmp = tmp_prev;
				tmp_prev = tmp_prev->prev;
			}

			return tmp_prev;
		}
	}

	else
		return NULL;
}

//************************************************************************************************************************
                                                                                             
node* FindNodeWithSetValue(node* Root, int x)
{
	if (Root != NULL)
	{
		if (Root->val == x)
			return Root;
		
		else
		{
			if (Root->val < x)
				FindNodeWithSetValue(Root->right, x);

			else
				FindNodeWithSetValue(Root->left, x);
		}
	}

	else
		return NULL;
}

//************************************************************************************************************************
                                                                                           
void DSW(node* &Root, int size)
{
	if (Root != NULL)
	{
		node *tmp = Root;
		while (tmp->left != NULL || tmp->right != NULL)
		{
			if (tmp->left != NULL)
			{
				rotateRight(tmp);
			}

			else
				tmp = tmp->right;
		}

		int change_counter = size + 1 - log2(size + 1);
		
		while (tmp->prev != NULL)
			tmp = tmp->prev;

		for (int i = 0; i < change_counter; i++)
			if (tmp->right != NULL)
				rotateLeft(tmp);

		while (tmp->prev != NULL)
			tmp = tmp->prev;

		size = size - change_counter;

		while (size > 1)
		{
			size >>= 1;
			tmp = Root;

			for (int i = 0; i < size; i++)
			{
				if (tmp->right != NULL)
					rotateLeft(tmp);
			}
		}

		while (tmp->prev != NULL)
			tmp = tmp->prev;

		Root = tmp;
	}	
}

//************************************************************************************************************************
                                                                                            
void deleteChosenNode(node* &Root, int x)
{
	if (Root != NULL)
	{
		node *tmp = FindNodeWithSetValue(Root, x);
		
		if (tmp->left == NULL && tmp->right == NULL)
		{
			if (tmp->prev != NULL && tmp->prev->left == tmp)
				tmp->prev->left = NULL;

			if (tmp->prev != NULL && tmp->prev->right == tmp)
				tmp->prev->right = NULL;

			if (tmp == Root)
				Root = NULL;
		}

		if ((tmp->left == NULL && tmp->right != NULL) || (tmp->left != NULL && tmp->right == NULL))
		{
			if (tmp->prev != NULL && tmp->prev->left == tmp)
			{
				if (tmp->right != NULL)
				{
					tmp->prev->left = tmp->right;
					tmp->right->prev = tmp->prev;
				}

				else
				{
					tmp->prev->left = tmp->left;
					tmp->left->prev = tmp->prev;
				}
			}

			if (tmp->prev != NULL && tmp->prev->right == tmp)
			{
				if (tmp->right != NULL)
				{
					tmp->prev->right = tmp->right;
					tmp->right->prev = tmp->prev;
				}

				else
				{
					tmp->prev->right = tmp->left;
					tmp->left->prev = tmp->prev;
				}
			}

			if (tmp == Root)
			{
				if (Root->left != NULL)
				{
					Root = Root->left;
					Root->prev = NULL;
				}

				else
				{
					Root = Root->right;
					Root->prev = NULL;
				}

			}
		}

		if (tmp->left != NULL && tmp->right != NULL)
		{
			node *tmp_heir = findSuccessor(Root, x);
			if (tmp_heir->right != NULL)
			{
				if (tmp_heir->prev->right == tmp_heir)
					tmp_heir->prev->right = tmp_heir->right;
				
				else
					tmp_heir->prev->left = tmp_heir->right;
			}

			else
			{
				if (tmp_heir->prev->left == tmp_heir)
					tmp_heir->prev->left = NULL;

				else
					tmp_heir->prev->right = NULL;
			}

			tmp_heir->left = tmp->left;
			tmp_heir->right = tmp->right;
			tmp_heir->prev = tmp->prev;
			
			if (tmp->prev != NULL && tmp->prev->left == tmp)
				tmp->prev->left = tmp_heir;

			if (tmp->prev != NULL && tmp->prev->right == tmp)
				tmp->prev->right = tmp_heir;

			if (tmp->right != NULL)
				tmp->right->prev = tmp_heir;

			if (tmp->left != NULL)
				tmp->left->prev = tmp_heir;

			if (tmp == Root)
				Root = tmp_heir;
		}

		delete tmp;
	}
}

//************************************************************************************************************************
                                                                                                      
void inOrder(node *Root)
{
	if (Root != NULL)
	{
		if (Root->left != NULL)
		{
			inOrder(Root->left);
		}

		cout << Root->val << " ";

		if (Root->right != NULL)
		{
			inOrder(Root->right);
		}
	}
}

//************************************************************************************************************************
                                                                                                     
void show(string sp, string sn, node *Root)
{
	string s;

	if (Root != NULL)
	{
		s = sp;
		if (sn == cr) s[s.length() - 2] = ' ';
		show(s + cp, cr, Root->right);

		s = s.substr(0, sp.length() - 2);
		cout << s << sn << Root->val << endl;

		s = sp;
		if (sn == cl) s[s.length() - 2] = ' ';
		show(s + cp, cl, Root->left);
	}
}

//************************************************************************************************************************
                                                                                                            
void rotateRight(node* &Root)
{
	node *tmp = Root;

	node *tmp_left = tmp->left;
	tmp_left->prev = tmp->prev;
	tmp->prev = tmp_left;
	tmp->left = tmp_left->right;
	tmp_left->right = tmp;
	tmp = tmp_left;
	if (tmp->prev != NULL)
		tmp->prev->right = tmp;	
}

//************************************************************************************************************************
																										   
void rotateLeft(node* &Root)
{
	node *tmp = Root;

	node *tmp_right = tmp->right;
	tmp_right->prev = tmp->prev;
	tmp->prev = tmp_right;
	tmp->right = tmp_right->left;
	tmp_right->left = tmp;

	if (tmp_right->prev != NULL)
		tmp_right->prev->right = tmp_right;

	if (tmp_right->right != NULL)
		tmp = tmp_right->right;
}

//************************************************************************************************************************