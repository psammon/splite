#ifndef BST_H
#define BST_H

#include <iostream>
#include <cstdlib>

using namespace std;

class node;

template<typename T> class BSTree{
	
	private:
		class node{
			public:
				T key;
				node* left;
				node* right;
		};

		node* root;

		void AddLeafPrivate(T key, node* Ptr);
		node* searchPrivate(T key, node* Ptr);
		void removeNodePrivate(T key, node* parent);
		void removeRootMatch();
		void removeMatch(node* parent, node* match, bool left);
		T findSmallestPrivate(node* Ptr);
		void printInOrderPrivate(node* Ptr);
		void removeSubtree(node* Ptr);		//helps the deconstructor

	public:
		BSTree<T>();
		~BSTree<T>();
		node* CreateLeaf(T key);
		void AddLeaf(T key);	//insertion
		node* search(T key);	//search
		void removeNode(T key);	//deletion
		T findSmallest();
		void printInOrder();
		T& returnNodeValue(T key);

};


template<typename T>
BSTree<T>::BSTree(){
	root = NULL;
}

template<typename T>
BSTree<T>::~BSTree(){
	removeSubtree(root);
}

template<typename T>
void BSTree<T>::removeSubtree(node* Ptr){
	if(Ptr != NULL){
        if(Ptr->left != NULL){
            removeSubtree(Ptr->left);
        }
        if(Ptr->right != NULL){
            removeSubtree(Ptr->right);
        }
 
        delete Ptr;
 
    }
}

template<typename T> 
typename BSTree<T>::node* BSTree<T>::CreateLeaf(T key){
	node* n = new node;
	n->key = key;
	n->left = NULL;
	n->right = NULL;

	return n;
}

template<typename T> 
void BSTree<T>::AddLeaf(T key){
	AddLeafPrivate(key, root);
}

template<typename T> 
void BSTree<T>::AddLeafPrivate(T key, node* Ptr){
	if(root == NULL){
		root = CreateLeaf(key);
	}
	else if(key < Ptr->key){
		if(Ptr->left != NULL){
			AddLeafPrivate(key, Ptr->left);
		}
		else{
			Ptr->left = CreateLeaf(key);
		}
	}
	else if(key > Ptr->key){
		if(Ptr->right != NULL){
			AddLeafPrivate(key, Ptr->right);
		}
		else{
			Ptr->right = CreateLeaf(key);
		}
	}
	else{
		cout << "The key " << key << " has already been added to the tree\n";
	}
}

template<typename T> 
typename BSTree<T>::node* BSTree<T>::search(T key){
	return searchPrivate(key, root);
}

template<typename T> 
typename BSTree<T>::node* BSTree<T>::searchPrivate(T key, node* Ptr){
	if(Ptr != NULL){
		if(Ptr->key == key){
			return Ptr;
		}
		else{
			if(key < Ptr->key){
				return searchPrivate(key, Ptr->left);
			}
			else{
				return searchPrivate(key, Ptr->right);
			}
		}
	}
	else{
		return NULL;
	}
}

template<typename T> 
void BSTree<T>::removeNode(T key){
	removeNodePrivate(key, root);
}

template<typename T> 
void BSTree<T>::removeNodePrivate(T key, node* parent){
	if(root != NULL){
		if(root->key == key){
			removeRootMatch();
		}
		else{
			if(key < parent->key && parent->left != NULL){
				parent->left->key == key ?
				removeMatch(parent, parent->left, true) :
				removeNodePrivate(key, parent->left);
			}
			else if(key > parent->key && parent->right != NULL){
				parent->right->key == key ?
				removeMatch(parent, parent->right, false) :
				removeNodePrivate(key, parent->right);
			}
			else{
				cout << "The key " << key << " was not found in the tree\n";
			}
		}
	}
	else{
		cout << "The tree is empty\n";
	}
}

template<typename T> 
void BSTree<T>::removeRootMatch(){
	if(root != NULL){
		node* delPtr = root;
		T rootKey = root->key;
		T smallestInRightSubtree;

		//Case 0 children
		if(root->left == NULL && root->right == NULL){
			root = NULL;
			delete delPtr;
		}	
		
		//Case 1 child
		else if(root->left == NULL && root->right != NULL){
			root = root->right;
			delPtr->right = NULL;
			delete delPtr;
			cout << "Root node with key" << rootKey << " was deleted. " << "The new root contains key " << root-> key << endl;
		}
		else if(root->left != NULL && root->right == NULL){
			root = root->left;
			delPtr->left = NULL;
			delete delPtr;
			cout << "Root node with key" << rootKey << " was deleted. " << "The new root contains key " << root-> key << endl;
		}
		
		//Case 2 children
		else{
			smallestInRightSubtree = findSmallestPrivate(root->right);
			removeNodePrivate(smallestInRightSubtree, root);
			root->key = smallestInRightSubtree;
			cout << "The root key containing key " << rootKey << " was overwritten with key " << root->key << endl;
		}
	}
	else{
		cout << "Can not remove root. The tree is empty\n";
	}
}

template<typename T> 
T BSTree<T>::findSmallest(){
	findSmallestPrivate(root);
}

template<typename T> 
T BSTree<T>::findSmallestPrivate(node* Ptr){
	//if(root == NULL){
		//cout << "Tree is empty\n";
		//return -1000;
	//}
	//else{
		if(Ptr->left != NULL){
			return findSmallestPrivate(Ptr->left);
		}
		else{
			return Ptr->key;
		}
	//}
}

template<typename T> 
void BSTree<T>::removeMatch(node* parent, node* match, bool left){
	if(root != NULL){
		node* delPtr;
		T matchKey = match->key;
		T smallestInRightSubtree;

		if(match->left == NULL && match->right == NULL){
			delPtr = match;
			left == true ? parent -> left = NULL : parent -> right = NULL;
			delete delPtr;
			cout << "The node containing key " << matchKey << " was removed\n";
		}
		
		else if(match->left == NULL && match->right != NULL){
			left == true ? parent->left = match->right : parent->right = match->right;
			match->right = NULL;
			delPtr = match;
			delete delPtr;
			cout << "The node containing key " << matchKey << " was removed\n";
		}
		else if(match->left != NULL && match->right == NULL){
			left == true ? parent->left = match->left : parent->right = match->left;
			match->left = NULL;
			delPtr = match;
			delete delPtr;
			cout << "The node containing key " << matchKey << " was removed\n";
		}

		else{
			smallestInRightSubtree = findSmallestPrivate(match->right);
			removeNodePrivate(smallestInRightSubtree, match);
			match->key = smallestInRightSubtree;	
		}
	}
	else{
		cout << "Can not remove match. The tree is empty\n";
	}
}

template<typename T> 
T& BSTree<T>::returnNodeValue(T key){
	return (search(key))->key;
}

template<typename T> 
void BSTree<T>::printInOrder(){
	printInOrderPrivate(root);
}

template<typename T>
void BSTree<T>::printInOrderPrivate(node* Ptr){
	if(root != NULL){
		if(Ptr->left != NULL){
			printInOrderPrivate(Ptr->left);
		}
		cout << Ptr->key << "\n";
		if(Ptr->right != NULL){
			printInOrderPrivate(Ptr->right);
		}
	}
	else{
		cout << "The tree is empty\n";
	}
}

#endif







