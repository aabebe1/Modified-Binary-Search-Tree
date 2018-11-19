#ifndef LAZYBST_H
#define LAZYBST_H
#include <cstddef>

class LazyBST
{
    class Node;
    public:
        //Default constructor of LazyBST class   
        LazyBST();
	//Destructor 
        ~LazyBST();
	//copy constructor
        LazyBST(const LazyBST& other);
	// overloaded assignment operator
        LazyBST& operator=(const LazyBST& other);
	//insert() inserts a key to LazyBST
	//checks for imbalance walking down a tree
	//Doesn't allow duplicate entry, but check for rebalancing if invoked with a duplicate key
        void insert (int key);
	//remove() member function that finds and removes an item with the given key value, if the key exists in LazyBST
	//checks for imbalance walking down a tree
	//if invoked with a none existing key, does nothing
        bool remove(int key);
	//find() reports whether the given key is stored in the tree
        bool find(int key);
	//performs an inorder walk of the LazyBST and at each node, 
	//prints out the key followed by a : followed by the height of the node followed by another : 
	//followed by the size of the subtree rooted at that node between paranthesis
	//if invoked with empty tree, nothing prints
        void inorder();
	// returns whether there is a node in a position given by C string of the LazyBST and stores the key in the reference parameter.
        bool locate(const char *position, int& key);
    private:
        class Node{
        public:
            int m_key;
            Node* m_parent;
            Node* m_rightChild;
            Node* m_leftChild;
            int m_height;
            int m_size;
            friend class LazyBST;
	    //constructors for Node class
            Node(int key):m_key(key),m_parent(NULL),m_rightChild(NULL),m_leftChild(NULL),m_height(-1),m_size(0){}
            Node(int key, int height,int sizeTree): m_key(key),m_parent(NULL),m_rightChild(NULL),m_leftChild(NULL),m_height(height),m_size(sizeTree){}
        };
        Node* m_root;
	//DeleteTree() takes a pointer and delete the subtree recusively
	//Given a root root node it deletes the whole tree and return a NULL pointer
	//used by destructor and during rebalancing an imbalanced tree 
        void DeleteTree(Node* root);
	//CopyTree() takes a pointer node and recursively copy the subtree pointed by the pointer
	//Given a root node it copy the whole tree
	//used by copy constructor
        Node* CopyTree(Node* root);
	//used by the public insert()
	// insertNode() inserts a node into a tree recusively
	// it check for imbalance on its wasy done, and rebalance the subtree if needed using the rebalance()
	Node* insertNode(Node* root, int key);
	//locateKey() takes a point to char and traverse the tree to the left if char points to L, to the right if char points to R
	//if key is found the function returns true, otherwise false
        bool find(Node* root, int key);
	//UpdateHeight() update height of ancestors given a node with the right height
        Node* UpdateHeight(Node* root);
	//updateHeightSize()update height and size of ancestors a node which has been removed
	//takes the parent of the deleted node to recursively update height and size
        Node* updateHeightSize(Node* root);
	//removeNode() takes a node pointer and a key and removes the key from the tree
	//Returns a pointer to a tree which has the node containing the key removed
	Node* removeNode(Node* root, int key);
	//maxNode() takes a root node of the subtree and returns the pointer to the node with has the maximum key
        Node* maxNode(Node* root);
	//inoderPrint() executes the actual printing performed by inorder()
	void inorderPrint(Node* root);
	//locateKey() executes the actual task of locate()
	//returns a node pointer if the key is found in the provided C string position
        Node* locateKey(Node* root, const char* position,int& key);
	//rebalance(): balances a tree during insertion or removal of a node
	//function is invoked during inseriton or removal
        Node* rebalance(Node* root);
	//checkBalance(): checks if there is imbalance at a given node
        bool checkBalance(Node* root);
	//ArrayToTree(): takes two pointers pointing to the beginning and end of a dynamic array
	//Function takes elements in array and construct a tree
	//Returns the root node of the newly constructed tree
	Node* ArrayToTree(Node* root,int* ptrBegin,int* ptrEnd);
	//AddToArray(): takes a node and dynamic int array pointer
	//Functions walks down a tree and put the keys in the array in inorder traveral fashion
	// Returns the pointer to the end of the dynamic array
	int* AddToArray(Node* root, int* ptr);
	//constructNOde() inserts a node into the tree when carrying out rebalanceing
	//similar structure to insert() but doesn't check if rebalancing is needed as we are constructing a tree from sorted array
	Node* constructNode(Node* root, int key);
};

#endif // LAZYBST_H
