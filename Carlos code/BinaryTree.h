#pragma once
#include <iostream>
#include <queue> // [ADDED] Needed for level-order traversal (Part 2 of Lab)

class TreeNode
{
public:
    TreeNode(int number = 0, TreeNode* prev_node = nullptr, TreeNode* left_node = nullptr, TreeNode* right_node = nullptr);
    ~TreeNode();
    void set_left(TreeNode* Node);
    void set_right(TreeNode* Node);
    void set_value(int Thevalue);
    void set_prev(TreeNode* Node);
    void set_height(int h);
    TreeNode* get_prev();
    TreeNode* get_left();
    TreeNode* get_right();
    int get_value();
    int get_height();

    // void swap(TreeNode* Node1, TreeNode* Node2); // [REMOVED] Unused on individual node instances
private:
    TreeNode* left;
    TreeNode* right;
    TreeNode* prev;
    int height;
    int value;
};

class BinaryTree
{
public:
    BinaryTree(TreeNode* Node = nullptr);
    ~BinaryTree();

    void set_root(TreeNode* Node);
    TreeNode* get_root();
    void insertNode(int x);

    // [MODIFIED] Simplified signature: height depends on children, not a whole-tree direction flag
    void Update(TreeNode* Node);
    // void Update(TreeNode* Node, bool left_or_right); // [REMOVED] Replaced by the 1-parameter version above
    // int UpdateCount(TreeNode* Node, int counting);   // [REMOVED] Replaced by O(1) height update in Update()

    // [ADDED] Safe balance factor checker: returns (left height - right height)
    int getBalance(TreeNode* Node);

    // [MODIFIED] Dispatches balance checks and climbs up the tree using get_prev()
    void rotate(TreeNode* Node);
    // void rotate(TreeNode* parent, TreeNode* child); // [REMOVED]

    // [ADDED] Displays tree per level using BFS queue (Lab Part 2 requirement)
    void displayLevelOrder();

    // void swap(TreeNode* NodePrev, TreeNode* NodeNext); // [REMOVED] Logic split into dedicated rotateLeft and rotateRight

private:
    TreeNode* root;

    // int leftHeight = 0;  // [REMOVED] Global heights cannot track balance in deeper subtrees
    // int rightHeight = 0; // [REMOVED] Each TreeNode already tracks its own height

    // [MODIFIED] Core rotation primitives (take the parent where imbalance occurs)
    void rotateLeft(TreeNode* parent);
    void rotateRight(TreeNode* parent);
    // void rotateLeft(TreeNode* parent, TreeNode* child);  // [REMOVED]
    // void rotateRight(TreeNode* parent, TreeNode* child); // [REMOVED]
};

/*#pragma once
class TreeNode
{
public:
	TreeNode(int number = 0, TreeNode* prev_node = nullptr, TreeNode* left_node = nullptr, TreeNode* right_node = nullptr);
	~TreeNode();
	void set_left(TreeNode* Node);
	void set_right(TreeNode* Node);
	void set_value(int Thevalue);
	void set_prev(TreeNode* Node);
	void set_height(int h);
	TreeNode* get_prev();
	TreeNode* get_left();
	TreeNode* get_right();
	int get_value();
	int get_height();

	void swap(TreeNode* Node1, TreeNode* Node2);
private:
	TreeNode* left;
	TreeNode* right;
	TreeNode* prev;
	int height;
	int value;
};

class BinaryTree
{
public:
	BinaryTree(TreeNode* Node = nullptr);
	~BinaryTree();

	void set_root(TreeNode* Node);
	TreeNode* get_root();
	void insertNode(int x);
	void Update(TreeNode* Node, bool left_or_right);

	int getBalance(TreeNode *Node);

	int UpdateCount(TreeNode* Node, int counting);
	void swap(TreeNode* NodePrev, TreeNode* NodeNext);
	void rotate(TreeNode* parent, TreeNode* child);

private:

	TreeNode* root;
	int leftHeight = 0;
	int rightHeight = 0;
	void rotateLeft(TreeNode* parent, TreeNode* child);
	void rotateRight(TreeNode* parent, TreeNode* child);
};

*/

