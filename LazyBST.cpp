#include "LazyBST.h"
#include <iostream>
#include <cstddef>

//constructor
LazyBST::LazyBST()
{
    this->m_root = NULL;
}
//destructor
LazyBST::~LazyBST()
{
  LazyBST::DeleteTree(this->m_root);
  this->m_root = NULL;
}
//cocpy constructor
LazyBST::LazyBST(const LazyBST& other)
{
    this->m_root = LazyBST::CopyTree(other.m_root);
}
//assignment operator overloading
LazyBST& LazyBST::operator=(const LazyBST& rhs)
{
    if (this == &rhs) return *this; // handle self assignment
    LazyBST::DeleteTree(this->m_root);
    this->m_root = LazyBST::CopyTree(rhs.m_root);
    return *this;
}
//CopyTree() takes a pointer node and recursively copy the subtree pointed by the pointer
//Given a root node it copy the whole tree
LazyBST::Node* LazyBST::CopyTree(Node* root){
    if(root == NULL) return NULL;
    Node* temp = new LazyBST::Node(root->m_key,root->m_height,root->m_size);
    temp->m_leftChild = LazyBST::CopyTree(root->m_leftChild);
    if(temp->m_leftChild != NULL){
        temp->m_leftChild->m_parent = temp;
    }
    temp->m_rightChild = LazyBST::CopyTree(root->m_rightChild);
    if(temp->m_rightChild != NULL){
        temp->m_rightChild->m_parent = temp;
    }
    return temp;
}
//DeleteTree() takes a pointer and delete the subtree recusively
//Given a root root node it deletes the whole tree and return a NULL pointer 
void LazyBST::DeleteTree(Node* root){
    if(root == NULL)return;
    LazyBST::DeleteTree(root->m_leftChild);
    root->m_leftChild = NULL;
    LazyBST::DeleteTree(root->m_rightChild);
    root->m_rightChild = NULL;
    delete root;
    root = NULL;
}
// insertNode() inserts a node into a tree recusively
// it check for imbalance on its wasy done, and rebalance the subtree if needed using the rebalance()
LazyBST::Node* LazyBST::insertNode(LazyBST::Node* root, int key){
  //check if rebalancing is needed

  if(root != NULL && checkBalance(root)){
    int balancedKey = root->m_key;
    bool checker = true;
    if(root->m_parent == NULL){
      checker = false;
    }
    // update the root pointer after rebalancing

    root = LazyBST::rebalance(root);
    //find the left and right nodes height to update height for the rebalanced subtree and its ancestors
    int leftHeight,rightHeight = -1;
    if(root->m_leftChild != NULL){
      leftHeight = root->m_leftChild->m_height;
    }
    if(root->m_rightChild != NULL){
      rightHeight = root->m_rightChild->m_height;
    }
    //update height of the ancestors via UpdateHeight() function
    this->m_root =(leftHeight > rightHeight) ? UpdateHeight(root->m_leftChild): UpdateHeight(root->m_rightChild);
    //if rebalanced node is a root node, insertion can continue 
    // if rebalanced node is a node of a subtree, the ancestors are already visited going down the tree, thus continue the insertion on the right subtree
    if(checker){
      if(balancedKey > root->m_key){
	root = root->m_rightChild;
      }else{
	root = root->m_leftChild;
      }
    }
  }
  //

  //root node is empty, create a node
  if(root == NULL){
    root = new Node(key);
    root->m_height++;
    root->m_size++;
  }
  //insert key to the left recusively as the key is smaller than the node
  else if(key < root->m_key){
    
        root->m_leftChild = insertNode(root->m_leftChild,key);
        root->m_leftChild->m_parent = root;
        if(root->m_height == 0){
	  root->m_height++;
        }
        else if(root->m_height == root->m_leftChild->m_height){
	  root->m_height++;
        }
	
	if(root->m_rightChild == NULL){
	  root->m_size = root->m_leftChild->m_size + 1;
        }else{
	  root->m_size = root->m_leftChild->m_size + root->m_rightChild->m_size + 1;
        }
	
  }
  //insert key to the right recursively
  else if(key > root->m_key){
    
    root->m_rightChild = insertNode(root->m_rightChild,key);
    root->m_rightChild->m_parent = root;
    if(root->m_height == 0){
      root->m_height++;
        }
    else if(root->m_height == root->m_rightChild->m_height){
      root->m_height++;
    }
    if(root->m_leftChild == NULL){
      root->m_size = root->m_rightChild->m_size + 1;
    }else{
      root->m_size = root->m_leftChild->m_size + root->m_rightChild->m_size + 1;
    }
    
  }
  
  return root;
}
// public insert function which calls the private insertNode()
void LazyBST::insert(int key){
  this->m_root = LazyBST::insertNode(this->m_root,key);
}
//update height of ancestors given a node with the right height
LazyBST::Node* LazyBST::UpdateHeight(Node* root){

  if(root == NULL)return root;
  else if(root->m_parent == NULL)return root;
  root->m_parent->m_height = root->m_height + 1;
  root = LazyBST::UpdateHeight(root->m_parent);
  return root;
}
//update height and size of ancestors after removing a node
LazyBST::Node* LazyBST::updateHeightSize(Node* root){
  
  if(root->m_parent == NULL)return root;
  // root is a left child of its parent
  if(root->m_parent->m_leftChild == root){
    // no right child, so parent's height and size is one plus the current node
    if(root->m_parent->m_rightChild == NULL){
      root->m_parent->m_height = root->m_height + 1;
      root->m_parent->m_size = root->m_size + 1;

    }else{
      //parent has both left and richt children, height of parent is the greatest of the two plus one and size is the sum plus one
      root->m_parent->m_size = root->m_parent->m_rightChild->m_size + root->m_size + 1;
      root->m_parent->m_height = (root->m_height > root->m_parent->m_rightChild->m_height ? root->m_height:root->m_parent->m_rightChild->m_height) + 1;
        }
  }else{
    //repeat the above if the root is a right child
    if(root->m_parent->m_leftChild == NULL){
      root->m_parent->m_height = root->m_height + 1;
      root->m_parent->m_size = root->m_size + 1;

        }else{
      root->m_parent->m_size = root->m_size + root->m_parent->m_leftChild->m_size + 1;
      root->m_parent->m_height = (root->m_height > root->m_parent->m_leftChild->m_height ? root->m_height : root->m_parent->m_leftChild->m_height) + 1;
    }
  }
  // update other ancestors recursively
  root = LazyBST::updateHeightSize(root->m_parent);
  return root;
}
//inorderPrint(): print the node for display
void LazyBST::inorderPrint(Node* root){
  if(root == NULL) return;
  std::cout << "(" ;
  LazyBST::inorderPrint(root->m_leftChild);
  std::cout << root->m_key << " : " << root->m_height <<" : " << root->m_size ;
  LazyBST::inorderPrint(root->m_rightChild);
  std::cout << ")";
}
//inorder(): public inorder printing function
void LazyBST::inorder(){
  LazyBST::inorderPrint(this->m_root);
}
//checkBalance() evaluate if there is imbalance at a given node
bool LazyBST::checkBalance(Node* root){
  if(root == NULL)return false;
  else if(root->m_leftChild != NULL && root->m_rightChild != NULL){
    if(((root->m_leftChild->m_size >= 2 * root->m_rightChild->m_size) && root->m_height >= 4)
       ||((root->m_rightChild->m_size >= 2 * root->m_leftChild->m_size) && root->m_height >= 4)){
      return true;
    }
  }
  else if(root->m_rightChild != NULL && root->m_leftChild == NULL){
    if(root->m_height >= 4){
      return true;
    }
  }
  else if(root->m_leftChild != NULL && root->m_rightChild == NULL){
    if(root->m_height >=4){
      return true;
    }
  }
  return false;
}

//rebalance() fixes the imbalance at the node
LazyBST::Node* LazyBST::rebalance( Node* root){
  int * ptrBegin, * ptrEnd;
  //create a dynamic array
  ptrBegin = new int[root->m_size + 1];
  // ptrEnd points to the end of the array
  ptrEnd = LazyBST::AddToArray(root,ptrBegin);
  // decrease ptrEnd to point to the lase element in the array
  ptrEnd--;
  //the root is going to be deleted, save the parent node
  Node* temp = root->m_parent;
  if(temp == NULL){
    //parent is null, this is a root node of the tree
      LazyBST::DeleteTree(this->m_root);
      this->m_root = root = NULL;
      // make a new tree using the sorted array
      this->m_root = LazyBST::ArrayToTree(this->m_root,ptrBegin,ptrEnd);
      delete[] ptrBegin;
      ptrBegin=ptrEnd = NULL;
      return this->m_root;
      // delete the leftChild which has imbalance and make a new tree and attach it to the existing tree
  }else if (temp->m_leftChild == root){
    
      LazyBST::DeleteTree(root);
      temp->m_leftChild = root = NULL;
      temp->m_leftChild = LazyBST::ArrayToTree(temp->m_leftChild,ptrBegin,ptrEnd);
      temp->m_leftChild->m_parent = temp;
  }else{
    //delete the right child which has imbalance and make a new tree and attach it to the existing tree
    LazyBST::DeleteTree(root);
    temp->m_rightChild = root = NULL;
    temp->m_rightChild = LazyBST::ArrayToTree(temp->m_rightChild,ptrBegin,ptrEnd);
      temp->m_rightChild->m_parent = temp;
  }
  //delete array
  delete[] ptrBegin;
  ptrBegin=ptrEnd = NULL;
  return temp;
}

//AddToArray(): takes a node and dynamic int array pointer
//Functions walks down a tree and put the keys in the array in inorder traveral fashion
// Returns the pointer to the end of the dynamic array
int* LazyBST::AddToArray(Node* root, int* ptr){
  
  if(root == NULL) return ptr;
    ptr=LazyBST::AddToArray(root->m_leftChild,ptr);
    *ptr = root->m_key;
    ptr++;
    ptr=LazyBST::AddToArray(root->m_rightChild,ptr);
    return ptr;
}
//ArrayToTree(): takes two pointers pointing to the beginning and end of a dynamic array
//Function takes elements in array and construct a tree
//Returns the root node of the newly constructed tree
LazyBST::Node* LazyBST::ArrayToTree(Node* root,int*ptrBegin,int*ptrEnd){
  int* midPtr = ptrBegin+(ptrEnd-ptrBegin)/2;
  if(ptrBegin == ptrEnd){
    root = LazyBST::constructNode(root,*ptrBegin);
    return root;
  }
  else if(ptrEnd == ptrBegin + 1){
    root = LazyBST::constructNode(root,*ptrBegin);
    root = LazyBST::constructNode(root,*ptrEnd);
    return root;
  }
  root = LazyBST::constructNode(root,*midPtr);
  root = LazyBST::ArrayToTree(root,ptrBegin,midPtr-1);
  root = LazyBST::ArrayToTree(root,midPtr+1,ptrEnd);
  return root;
}
//public find() function
bool LazyBST::find(int key){
  return LazyBST::find(this->m_root, key);
}
// private find() functions
// Takes a node pointer and a key, and checks if the key exists in the subtree
// Returns true if key is found else false
bool LazyBST::find(Node* root,int key){
  if(root == NULL)return false;
  if(key == root->m_key){
        return true;
  }
  else if(key < root->m_key){
    root = root->m_leftChild;
    }
  else if(key > root->m_key){
    root = root->m_rightChild;
  }
  return LazyBST::find(root,key);
}
// public remove() function
bool LazyBST::remove(int key){
  if(removeNode(this->m_root, key) == NULL){
    return false;
  }
    return true;
}
//removeNode() takes a node pointer and a key and removes the key from the tree
//Returns a pointer to a tree which has the node containing the key removed
LazyBST::Node* LazyBST::removeNode(Node* root, int key){
  // check for imbalancing walking down the tree
  //relancing same as insertion()
  if(root != NULL && checkBalance(root)){
   
    int balancedKey = root->m_key;
    bool checker = true;
    if(root->m_parent == NULL){
      checker = false;
    }
    root = LazyBST::rebalance(root);

    int leftHeight,rightHeight = -1;
    if(root->m_leftChild != NULL){
      leftHeight = root->m_leftChild->m_height;
    }
    if(root->m_rightChild != NULL){
      rightHeight = root->m_rightChild->m_height;
    }
    //update height
    this->m_root =(leftHeight > rightHeight) ? UpdateHeight(root->m_leftChild): UpdateHeight(root->m_rightChild);

    if(checker){
      if(balancedKey > root->m_key){
	root = root->m_rightChild;
      }else{
	root = root->m_leftChild;
      }
    }

  }
  //nothing to be removed return
  if(root == NULL) return NULL;
  //recusively remove from the left subtree
  else if(key < root->m_key){
    root->m_leftChild = removeNode(root->m_leftChild,key);
        
    }
  //recusively remove from the right subtree
  else if(key > root->m_key){
    root->m_rightChild = removeNode(root->m_rightChild,key);
   
  }
  else{
    //found the node to remove
    //node to be removed has no left and right childeren, just delete it
    //update the size and height of its ancestors
    if(root->m_leftChild == NULL && root->m_rightChild == NULL){
      //the node is not a root node
      if(root->m_parent != NULL){
	// the node is a left child, 
	if(root->m_parent->m_leftChild == root){
	  //parent has no right child, so decrease height and size by 1 to account for the removed node
	  if(root->m_parent->m_rightChild == NULL){
	    root->m_parent->m_height--;
	    root->m_parent->m_size--;
	    this->m_root = updateHeightSize(root->m_parent);
	  }else{
	    //parent has a right child, height and size depend on the right child
	    root->m_parent->m_height = root->m_parent->m_rightChild->m_height + 1;
	    root->m_parent->m_size = root->m_parent->m_rightChild->m_size + 1;
	    this->m_root = updateHeightSize(root->m_parent);
	  }
	}else{
	  //the node is a right child, and repeat the left child process above
	  if(root->m_parent->m_leftChild == NULL){
	    root->m_parent->m_height--;
	    root->m_parent->m_size--;
	    this->m_root = updateHeightSize(root->m_parent);
	  }else{
	    
	    root->m_parent->m_height = root->m_parent->m_leftChild->m_height + 1;
	    root->m_parent->m_size = root->m_parent->m_leftChild->m_size + 1;
	    this->m_root = updateHeightSize(root->m_parent);
	  }
	}
      }else{
	//the node to be removed is a root node of the tree
	this->m_root = NULL;
      }
      //delete node
      delete root;
      root = NULL;
    }
    //the node to be removed has a right child, connect the right child to the parent of the current node before removing
    else if(root->m_leftChild == NULL){
      root->m_rightChild->m_parent = root->m_parent;
      Node* temp = root;
      //if parent of the current node is null, then the node to be removed is a root node
      if(root->m_parent != NULL){
	if(root == root->m_parent->m_leftChild){
	  root->m_parent->m_leftChild = root->m_rightChild;
	}else{

	  root->m_parent->m_rightChild = root->m_rightChild;
	}
	updateHeightSize(root->m_rightChild);
      }else{
	//make the right child to be a root node before removing the current node
	this->m_root = root->m_rightChild;
      }
      root = root->m_rightChild;
      delete temp;
      temp = NULL;
      
      
    }
    // the node has a left child but not a right child
    else if(root->m_rightChild == NULL){
      
      root->m_leftChild->m_parent = root->m_parent;
      Node* temp = root;
      if(root->m_parent != NULL){
	if(root == root->m_parent->m_leftChild){
	  root->m_parent->m_leftChild = root->m_leftChild;
	}else{
	  
	  root->m_parent->m_rightChild = root->m_leftChild;
	}
	updateHeightSize(root->m_leftChild);
      }else{
	this->m_root = root->m_leftChild;
      }
      root = root->m_leftChild;
      delete temp;
      temp = NULL;
      
      
    }
    //the node has both right and left children
    // find the maximum node from the left subtree and replace the key value in the current node
    else{
      Node* temp = maxNode(root->m_leftChild);
      root->m_key = temp->m_key;
      //remove the node which has the maximum value from left subtree
      root->m_leftChild = removeNode(root->m_leftChild,temp->m_key);
      temp = NULL;
    }
  }
  
  return root;
}
//maxNode() takes a root node of the subtree and returns the pointer to the node with has the maximum key
LazyBST::Node* LazyBST::maxNode(Node* root){
  if(root == NULL)return root;
  else if(root->m_rightChild == NULL){
    return root;
  }
  return LazyBST::maxNode(root->m_rightChild);
}
//public locate function
bool LazyBST::locate(const char *position, int& key){
    if(locateKey(this->m_root,position,key) == NULL){
        return false;
    }
    return true;
}
//locateKey() takes a point to char and traverse the tree to the left if char points to L, to the right if char points to R
//if key is found the function returns true, otherwise false
LazyBST::Node* LazyBST::locateKey(Node* root,const char* position, int& key){
    if(root == NULL)return NULL;
    else if(*position == '\0'){
        key = root->m_key;
        return root;
    }
    else if(*position == 'L'){
        if(root->m_leftChild == NULL) return NULL;
        root = root->m_leftChild;
    }
    else if(*position == 'R'){
        if(root->m_rightChild == NULL)return NULL;
        root = root->m_rightChild;
    }
    ++position;
    return LazyBST::locateKey(root,position,key);

}
//constructNOde() inserts a node into the tree when carrying out rebalanceing
//similar structure to insert() but doesn't check if rebalancing is needed as we are constructing a tree from sorted array
LazyBST::Node* LazyBST::constructNode(Node* root, int key){
  if(root == NULL){
    root = new Node(key);
    root->m_height++;
    root->m_size++;
  }
  else if(key < root->m_key){

    root->m_leftChild = insertNode(root->m_leftChild,key);
    root->m_leftChild->m_parent = root;
    if(root->m_height == 0 || root->m_height == root->m_leftChild->m_height){
      root->m_height++;
    }
    if(root->m_rightChild == NULL){
      root->m_size = root->m_leftChild->m_size + 1;
    }else{
      root->m_size = root->m_leftChild->m_size + root->m_rightChild->m_size + 1;
    }
  }
  else if(key > root->m_key){

    root->m_rightChild = insertNode(root->m_rightChild,key);
    root->m_rightChild->m_parent = root;
    if(root->m_height == 0 || root->m_height == root->m_rightChild->m_height){
      root->m_height++;
    }
    if(root->m_leftChild == NULL){
      root->m_size = root->m_rightChild->m_size + 1;
    }else{
      root->m_size = root->m_leftChild->m_size + root->m_rightChild->m_size + 1;
    }
  }

  return root;
}
