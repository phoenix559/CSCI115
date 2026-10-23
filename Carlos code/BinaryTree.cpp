#include <iostream>
#include <queue> // [ADDED] For displayLevelOrder queue operations
#include "BinaryTree.h"

// ==========================================
// TreeNode Implementation
// ==========================================

TreeNode::TreeNode(int number, TreeNode* prev_node, TreeNode* left_node, TreeNode* right_node)
{
    value = number;
    left = left_node;
    right = right_node;
    prev = prev_node;
    height = 1; // [ADDED] Newly created nodes start as leaves with height 1
}

TreeNode::~TreeNode()
{
}

void TreeNode::set_left(TreeNode* Node) {
    left = Node;
}

void TreeNode::set_right(TreeNode* Node) {
    right = Node;
}

void TreeNode::set_value(int Thevalue) {
    value = Thevalue;
}

TreeNode* TreeNode::get_left() {
    return left;
}

TreeNode* TreeNode::get_right() {
    return right;
}

int TreeNode::get_value() {
    return value;
}

int TreeNode::get_height() {
    return height;
}

void TreeNode::set_prev(TreeNode* Node) {
    prev = Node;
}

void TreeNode::set_height(int h) {
    height = h;
}

TreeNode* TreeNode::get_prev() {
    return prev;
}

// [Reasoning for TreeNode Changes]:
// Added `height = 1;` in the constructor. In an AVL tree, every newly inserted leaf
// starts with a base height of 1 so ancestor heights can be computed bottom-up.


// ==========================================
// BinaryTree Constructors & Basic Getters
// ==========================================

BinaryTree::BinaryTree(TreeNode* Node)
{
    // Node = root; // [REMOVED] Assignment order was inverted
    root = Node;    // [MODIFIED] Assign incoming Node into member variable root
}
// [Reasoning for Constructor]:
// In C++, assignments copy right-to-left (`destination = source`).
// Writing `Node = root;` overwrote the local parameter with uninitialized data, leaving `root` unassigned.

BinaryTree::~BinaryTree()
{
}

void BinaryTree::set_root(TreeNode* Node) {
    root = Node;
}

TreeNode* BinaryTree::get_root() {
    return root;
}


// ==========================================
// Height Calculation & Balancing Helpers
// ==========================================

void BinaryTree::Update(TreeNode* Node) {
    if (Node == nullptr) {
        return;
    }

    int leftH = 0;
    int rightH = 0;

    TreeNode* tempLeft = Node->get_left();
    if (tempLeft != nullptr) {
        leftH = tempLeft->get_height();
    }

    TreeNode* tempRight = Node->get_right();
    if (tempRight != nullptr) {
        rightH = tempRight->get_height();
    }

    if (leftH > rightH) {
        Node->set_height(leftH + 1);
    }
    else {
        Node->set_height(rightH + 1);
    }
}
// [Reasoning for Update]:
// Replaced the old Update/UpdateCount. Tree height is not "depth from root", but
// "distance to the furthest leaf below". We safely read the heights of left and right
// children (defaulting to 0 if null) and set `height = 1 + max(leftH, rightH)`.

/* [REMOVED OLD UPDATE & UPDATECOUNT]
void BinaryTree::Update(TreeNode* Node, bool left_or_right) {
    int update_count = UpdateCount(Node, 0);
    if (left_or_right == 0) {
        if (update_count > leftHeight) {
            leftHeight = update_count;
            return;
        }
        else { return; }
    }
    else {
        if (update_count > rightHeight) {
            rightHeight = update_count;
            return;
        }
        else { return; }
    }
}

int BinaryTree::UpdateCount(TreeNode* Node, int counting) {
    if (Node->get_prev() != nullptr) {
        return counting;
    }
    int count = UpdateCount(Node, counting + 1);
    return count;
}
// Reasoning for removal:
// UpdateCount caused an infinite recursive loop (and stack overflow) when Node->get_prev()
// was nullptr because it passed the exact same Node repeatedly. Additionally, tracking
// global leftHeight/rightHeight cannot detect unbalances in nested subtrees.
*/

int BinaryTree::getBalance(TreeNode* Node) {
    if (Node == nullptr) {
        return 0;
    }

    int leftH = 0;
    int rightH = 0;

    TreeNode* tempLeft = Node->get_left();
    if (tempLeft != nullptr) {
        leftH = tempLeft->get_height();
    }

    TreeNode* tempRight = Node->get_right();
    if (tempRight != nullptr) {
        rightH = tempRight->get_height();
    }

    return leftH - rightH;
}
// [Reasoning for getBalance]:
// Balance Factor = leftHeight - rightHeight.
// A node is balanced if BF is -1, 0, or 1.
// If BF > 1, the node is Left-Heavy. If BF < -1, it is Right-Heavy.


// ==========================================
// Rotation Primitives
// ==========================================

void BinaryTree::rotateRight(TreeNode* parent) {
    if (parent == nullptr) {
        return;
    }

    TreeNode* child = parent->get_left();
    if (child == nullptr) {
        return;
    }

    TreeNode* NodePrevPrev = parent->get_prev();
    TreeNode* temp = child->get_right();

    // 1. Move child's right subtree to parent's left
    child->set_right(parent);
    parent->set_left(temp);

    // 2. Fix floating inner subtree's parent link
    if (temp != nullptr) {
        temp->set_prev(parent);
    }

    // 3. Connect parent and child vertical pointers
    parent->set_prev(child);
    child->set_prev(NodePrevPrev);

    // 4. Connect grandparent to promoted child (or update root)
    if (NodePrevPrev != nullptr) {
        if (NodePrevPrev->get_left() == parent) {
            NodePrevPrev->set_left(child);
        }
        else {
            NodePrevPrev->set_right(child);
        }
    }
    else {
        root = child;
    }

    // 5. Update heights (demoted parent first, then promoted child)
    Update(parent);
    Update(child);
}
// [Reasoning for rotateRight]:
// Pulls the left child up to take the parent's place.
// The inner child (`temp = child->get_right()`) is adopted by `parent->left`.
// Crucially, `temp->set_prev(parent)` and `NodePrevPrev->set_left/right(child)`
// ensure every parent link is updated so climbing back up the tree remains unbroken.

void BinaryTree::rotateLeft(TreeNode* parent) {
    if (parent == nullptr) {
        return;
    }

    TreeNode* child = parent->get_right();
    if (child == nullptr) {
        return;
    }

    TreeNode* NodePrevPrev = parent->get_prev();
    TreeNode* temp = child->get_left();

    // 1. Move child's left subtree to parent's right
    child->set_left(parent);
    parent->set_right(temp);

    // 2. Fix floating inner subtree's parent link
    if (temp != nullptr) {
        temp->set_prev(parent);
    }

    // 3. Connect parent and child vertical pointers
    parent->set_prev(child);
    child->set_prev(NodePrevPrev);

    // 4. Connect grandparent to promoted child (or update root)
    if (NodePrevPrev != nullptr) {
        if (NodePrevPrev->get_left() == parent) {
            NodePrevPrev->set_left(child);
        }
        else {
            NodePrevPrev->set_right(child);
        }
    }
    else {
        root = child;
    }

    // 5. Update heights (demoted parent first, then promoted child)
    Update(parent);
    Update(child);
}
// [Reasoning for rotateLeft]:
// Mirror of rotateRight: pulls right child up, hands off child's left subtree to
// parent's right, and patches grandparent + parent links.


// ==========================================
// Rotation Dispatcher
// ==========================================

void BinaryTree::rotate(TreeNode* Node) {
    if (Node == nullptr) {
        return;
    }

    // [ADDED]: Refresh heights recursively bottom-up from children before checking balance,
    // since insertNode does not auto-balance or update heights automatically on insertion.
    if (Node->get_left() != nullptr) {
        TreeNode* leftSub = Node->get_left();
        if (leftSub->get_left() != nullptr)  Update(leftSub->get_left());
        if (leftSub->get_right() != nullptr) Update(leftSub->get_right());
        Update(leftSub);
    }
    if (Node->get_right() != nullptr) {
        TreeNode* rightSub = Node->get_right();
        if (rightSub->get_left() != nullptr)  Update(rightSub->get_left());
        if (rightSub->get_right() != nullptr) Update(rightSub->get_right());
        Update(rightSub);
    }
    Update(Node);

    int balance = getBalance(Node);

    // Case 1 & 2: Left-Heavy
    if (balance > 1) {
        TreeNode* leftChild = Node->get_left();

        if (getBalance(leftChild) < 0) {
            // Left-Right case: rotate child left first
            rotateLeft(leftChild);
        }
        // Left-Left case (or 2nd step of Left-Right): rotate parent right
        rotateRight(Node);
    }
    // Case 3 & 4: Right-Heavy
    else if (balance < -1) {
        TreeNode* rightChild = Node->get_right();

        if (getBalance(rightChild) > 0) {
            // Right-Left case: rotate child right first
            rotateRight(rightChild);
        }
        // Right-Right case (or 2nd step of Right-Left): rotate parent left
        rotateLeft(Node);
    }
}
// [Reasoning for rotate]:
// When called on `tree.get_root()` in `main()`, it recalculates child and root heights,
// computes the balance factor, and triggers the appropriate rotation (LL, RR, LR, or RL).


// ==========================================
// Insertion
// ==========================================

void BinaryTree::insertNode(int x) {
    if (root == nullptr) {
        root = new TreeNode(x);
        return; // [ADDED] Exit early once root is created
    }

    TreeNode* Temp = root;
    TreeNode* Curr = nullptr;
    bool word = false;

    while (Temp != nullptr)
    {
        // [REMOVED CRASHING CHECKS]:
        // if (x > Temp->get_left()->get_value())
        // else if(x < Temp->get_right()->get_value())
        // Reasoning: Calling get_left()->get_value() crashed immediately with a segfault
        // whenever get_left() was null. Standard BST compares against Temp itself.

        Curr = Temp;

        if (x < Temp->get_value()) // [MODIFIED] Go left if smaller
        {
            Temp = Temp->get_left();
            word = true;
        }
        else if (x > Temp->get_value()) // [MODIFIED] Go right if larger
        {
            Temp = Temp->get_right();
            word = false;
        }
        else {
            // [REMOVED]: delete Curr; delete Temp;
            // Value already exists: do not insert duplicates
            return;
        }
    }

    TreeNode* newNode = new TreeNode(x, Curr);

    if (word == true) {
        Curr->set_left(newNode);
        // delete Curr; // [REMOVED] Deallocating Curr destroyed the node just linked into the tree!
        // delete Temp; // [REMOVED]
    }
    else
    {
        Curr->set_right(newNode);
        // delete Curr; // [REMOVED]
        // delete Temp; // [REMOVED]
    }

    // [INTENTIONALLY COMMENTED OUT FOR BEFORE/AFTER DEMO]:
    // rotate(newNode);
    // Reasoning: If we auto-balance on insert, the tree is already balanced before
    // displayLevelOrder() can be called in main. Leaving this off keeps the tree in its raw
    // unbalanced state so you can display the "Before" tree, call rotate manually,
    // and then display the "After" tree.
}
// [Reasoning for insertNode Changes]:
// 1. Removed `delete Curr` and `delete Temp` to prevent freeing active heap nodes.
// 2. Fixed comparisons to evaluate `Temp->get_value()` safely.
// 3. Stored `Curr` as the new node's `prev` parent pointer.
// 4. Left the tree in pure BST state (no auto-balance) to satisfy Part 4's Before/After output requirement.


// ==========================================
// Level-Order Traversal (Lab Requirement 2 & 4)
// ==========================================

void BinaryTree::displayLevelOrder() {
    if (root == nullptr) {
        std::cout << "(Tree is empty)\n";
        return;
    }

    std::queue<TreeNode*> q;
    q.push(root);

    while (!q.empty()) {
        int levelSize = q.size();

        for (int i = 0; i < levelSize; i++) {
            TreeNode* current = q.front();
            q.pop();

            std::cout << current->get_value() << " ";

            if (current->get_left() != nullptr) {
                q.push(current->get_left());
            }
            if (current->get_right() != nullptr) {
                q.push(current->get_right());
            }
        }
        std::cout << "\n"; // Newline after each level
    }
}
// [Reasoning for displayLevelOrder]:
// Uses a standard queue to print nodes level by level. By measuring `q.size()` at the start
// of each loop, it knows exactly how many nodes exist on that level and outputs a newline
// between levels, matching the display requirement of Lab 8.


// ==========================================
// Main Function (Lab 8 Part 4 Test Cases)
// ==========================================

int main() {
    std::cout << "====================================================\n";
    std::cout << "  LAB 8: BST TO AVL ROTATIONS (PER-LEVEL DISPLAY)   \n";
    std::cout << "====================================================\n\n";

    // -------------------------------------------------------------
    // Sequence 1: 20, 10, 15 (Left-Right Case -> LR Double Rotation)
    // -------------------------------------------------------------
    std::cout << "----------------------------------------------------\n";
    std::cout << "Sequence 1: 20, 10, 15\n";
    std::cout << "----------------------------------------------------\n";
    BinaryTree tree1;
    tree1.insertNode(20);
    tree1.insertNode(10);
    tree1.insertNode(15);

    std::cout << "BEFORE balancing (Level-order):\n";
    tree1.displayLevelOrder();

    tree1.rotate(tree1.get_root());

    std::cout << "\nAFTER balancing (LR Rotation):\n";
    tree1.displayLevelOrder();
    std::cout << "\n";


    // -------------------------------------------------------------
    // Sequence 2: 10, 5, 1 (Left-Left Case -> Single Right Rotation)
    // -------------------------------------------------------------
    std::cout << "----------------------------------------------------\n";
    std::cout << "Sequence 2: 10, 5, 1\n";
    std::cout << "----------------------------------------------------\n";
    BinaryTree tree2;
    tree2.insertNode(10);
    tree2.insertNode(5);
    tree2.insertNode(1);

    std::cout << "BEFORE balancing (Level-order):\n";
    tree2.displayLevelOrder();

    tree2.rotate(tree2.get_root());

    std::cout << "\nAFTER balancing (Right Rotation):\n";
    tree2.displayLevelOrder();
    std::cout << "\n";


    // -------------------------------------------------------------
    // Sequence 3: 10, 20, 30 (Right-Right Case -> Single Left Rotation)
    // -------------------------------------------------------------
    std::cout << "----------------------------------------------------\n";
    std::cout << "Sequence 3: 10, 20, 30\n";
    std::cout << "----------------------------------------------------\n";
    BinaryTree tree3;
    tree3.insertNode(10);
    tree3.insertNode(20);
    tree3.insertNode(30);

    std::cout << "BEFORE balancing (Level-order):\n";
    tree3.displayLevelOrder();

    tree3.rotate(tree3.get_root());

    std::cout << "\nAFTER balancing (Left Rotation):\n";
    tree3.displayLevelOrder();
    std::cout << "\n";


    // -------------------------------------------------------------
    // Sequence 4: 10, 20, 50 (Right-Right Case -> Single Left Rotation)
    // -------------------------------------------------------------
    std::cout << "----------------------------------------------------\n";
    std::cout << "Sequence 4: 10, 20, 50\n";
    std::cout << "----------------------------------------------------\n";
    BinaryTree tree4;
    tree4.insertNode(10);
    tree4.insertNode(20);
    tree4.insertNode(50);

    std::cout << "BEFORE balancing (Level-order):\n";
    tree4.displayLevelOrder();

    tree4.rotate(tree4.get_root());

    std::cout << "\nAFTER balancing (Left Rotation):\n";
    tree4.displayLevelOrder();
    std::cout << "\n";

    return 0;
}
// [Reasoning for main]:
// Tests the four prompt sequences using independent tree instances. For each case,
// it inserts the raw elements, calls displayLevelOrder() for the "Before" view,
// invokes tree.rotate() on the root, and prints the balanced "After" view.