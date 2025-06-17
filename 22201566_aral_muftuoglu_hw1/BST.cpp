/**
** Title: BST
** Author : Aral Muftuoglu
** ID: 22201566
** Section : 3
** Homework : 1
** Description : BST class implementation using LinkedQueue class
*/

#include "BST.h"
#include "LinkedQueue.h"
using namespace std;

// getter function for root
BSTNode *BST::getRoot() {
    return root;
}

// constructor
BST::BST(int keys[], int size) {
    BSTsize = size;

    if (size < 1) {
        root = nullptr;
    } else {
        root = new BSTNode(keys[0], nullptr, nullptr);

        //insert every new element with insertKey
        for (int i = 1; i < size; i++) {
            constructKey(keys[i]);
        }
        cout << "BST with size " << size << " created." << endl;
    }
}

//default constructor
BST::BST() {
    BSTsize = 0;
    root = nullptr;
}


// construct key method
void BST::constructKey(int key) {
    root = constructKeyHelper(root, key);
}
// recursive helper method for construct key
BSTNode *BST::constructKeyHelper(BSTNode *current, int key) {
    // empty spot for new node
    if (current == nullptr) {
        return new BSTNode(key, nullptr, nullptr);
    }

    // check for bst already has the same key
    if (key == (*current).getItem()) {
        cout << "Key " << key << " is not added.";
        cout << "It already exists in the BST." << endl;
        return current; // no insertion happens
    }

    // keep searching for proper position
    // if key is smaller than current node go on with left subtree, else go on with right subtree
    if (key < (*current).getItem()) {
        (*current).setLeftChild(constructKeyHelper((*current).getLeftChild(), key));
    } else {
        (*current).setRightChild(constructKeyHelper((*current).getRightChild(), key));
    }
    return current;
}

// destructor
BST::~BST() {
    destroyTree(root);
}
// recursive helper method for destructor
void BST::destroyTree(BSTNode * &treePtr) {
    if (treePtr != nullptr) {
        BSTNode *rightChild = (*treePtr).getRightChild();
        BSTNode *leftChild = (*treePtr).getLeftChild();

        // recursively go to subtrees
        destroyTree(rightChild);
        destroyTree(leftChild);

        // delete the pointer properly
        delete treePtr;
        treePtr = nullptr;
    }
}

// insert key method
void BST::insertKey(int key) {
    root = insertKeyHelper(root, key);
}
// recursive helper method for insert key
BSTNode *BST::insertKeyHelper(BSTNode *current, int key) {
    // empty spot for new node
    if (current == nullptr) {
        cout << "Key " << key << " is added!" << endl;
        return new BSTNode(key, nullptr, nullptr);
    }

    // check for bst already has the same key
    if (key == (*current).getItem()) {
        // print the proper result working with user interface
        cout << "Key " << key << " is not added! ";
        cout << "It already exists in the BST." << endl;
        return current; // no insertion happens
    }

    // keep searching for proper position
    // if key is smaller than current node go on with left subtree, else go on with right subtree
    if (key < (*current).getItem()) {
        (*current).setLeftChild(insertKeyHelper((*current).getLeftChild(), key));
    } else {
        (*current).setRightChild(insertKeyHelper((*current).getRightChild(), key));
    }
    return current;
}

// delete key method
void BST::deleteKey(int key) {
    // check for empty tree
    if (root == nullptr) {
        cout << "Key " << key << " is not deleted! ";
        cout << "BST is empty." << endl;
        return;
    }
    deleteItem(root, key);
}
// recursive helper delete method
void BST::deleteItem(BSTNode * &treePtr, int key) {
    // in case of not having the key
    if (treePtr == nullptr) {
        // print the proper output
        cout << "Key " << key << " is not deleted. ";
        cout << "It does not exist in the BST." << endl;
        return;
    }

    // if the current node is the key delete it
    if (key == (*treePtr).getItem()) {
        deleteNode(treePtr);
        cout << "Key " << key << " is deleted." << endl;
    }
    // if key value is smaller than current one keep searching with left subtree, else go on with right subtree
    else if (key < (*treePtr).getItem()) {
        BSTNode *leftChild = (*treePtr).getLeftChild();
        deleteItem(leftChild, key);
        (*treePtr).setLeftChild(leftChild);
    } else {
        BSTNode *rightChild = (*treePtr).getRightChild();
        deleteItem(rightChild, key);
        (*treePtr).setRightChild(rightChild);
    }
}
// helper method for deleting node
void BST::deleteNode(BSTNode * &nodePtr) {
    BSTNode *delPtr;
    int replacementItem;

    // check if the node is leaf (has no right and left child)
    if (((*nodePtr).getLeftChild() == nullptr) &&
        ((*nodePtr).getRightChild() == nullptr)) {
        delete nodePtr;
        nodePtr = nullptr;
    }
    // check if it has no left child
    else if ((*nodePtr).getLeftChild() == nullptr) {
        delPtr = nodePtr;
        nodePtr = (*nodePtr).getRightChild();
        delete delPtr;
    }
    // check if it has no right child
    else if ((*nodePtr).getRightChild() == nullptr) {
        delPtr = nodePtr;
        nodePtr = (*nodePtr).getLeftChild();
        delete delPtr;
    }
    // condition that it has two children
    // retrieve and delete the inorder successor
    else {
        BSTNode *rightChild = (*nodePtr).getRightChild();
        processLeftmost(rightChild, replacementItem);
        (*nodePtr).setRightChild(rightChild);
        (*nodePtr).setItem(replacementItem);
    }
}
// processLeftMost method
void BST::processLeftmost(BSTNode * &nodePtr, int &replacementItem) {
    if ((*nodePtr).getLeftChild() == nullptr) {
        replacementItem = (*nodePtr).getItem();
        BSTNode *delPtr = nodePtr;
        nodePtr = (*nodePtr).getRightChild();
        delete delPtr;
    } else {
        BSTNode *leftChild = (*nodePtr).getLeftChild();
        processLeftmost(leftChild, replacementItem);
        (*nodePtr).setLeftChild(leftChild);
    }
}

// key level method
void BST::keyLevel(int key) {
    int level = findLevelHelper(root, key, 1);

    // if level is equal to -1 that means key is not found in the tree, otherwise if it is not print the result
    if (level == -1) {
        cout << "Key " << key << " not found in the BST." << endl;
    } else {
        cout << "The level of key " << key << " is: " << level << endl;
    }
}
//recursive helper method
int BST::findLevelHelper(BSTNode *node, int key, int level) {
    // base case for not finding the key
    if (node == nullptr) {
        return -1;
    }

    // key is found, now return the level
    if ((*node).getItem() == key) {
        return level;
    }

    // if key is smaller than current node, go on with left child
    if (key < (*node).getItem()) {
        return findLevelHelper((*node).getLeftChild(), key, level + 1);
    }

    // if key is greater than current node, go on with right child
    return findLevelHelper((*node).getRightChild(), key, level + 1);
}


// display inorder method
void BST::displayInorder() {
    // check for empty tree
    if (root == nullptr) {
        cout << "The tree is empty." << endl;
        return;
    }

    // flag printing coma properly
    bool first = true;

    // print the result display
    cout << "Inorder display is: ";
    displayInorderHelper(root, first);
    cout << endl;
}
// recursive helper method
void BST::displayInorderHelper(BSTNode *node, bool &isFirst) {
    if (node != nullptr) {
        displayInorderHelper((*node).getLeftChild(), isFirst);

        // if it is first don't print comma, else print comma before item
        if (isFirst) {
            cout << (*node).getItem();
            isFirst = false;
        } else {
            cout << ", " << (*node).getItem();
        }
        displayInorderHelper((*node).getRightChild(), isFirst);
    }
}

// display postorder method
void BST::displayPostorder() {
    // check for empty tree
    if (root == nullptr) {
        cout << "The tree is empty." << endl;
        return;
    }

    // flag for printing comma between numbers
    bool first = true;
    // print the results
    cout << "Postorder display is: ";
    displayPostorderHelper(root, first);
    cout << endl;
}
// recursive helper method
void BST::displayPostorderHelper(BSTNode *node, bool &isFirst) {
    if (node != nullptr) {
        displayPostorderHelper((*node).getLeftChild(), isFirst);
        displayPostorderHelper((*node).getRightChild(), isFirst);

        // if it is first don't print comma, else print comma before item
        if (isFirst) {
            cout << (*node).getItem();
            isFirst = false;
        } else {
            cout << ", " << (*node).getItem();
        }
    }
}

// lowest common ancestor method
void BST::lowestCommonAncestor(int A, int B) {
    // check the case of empty tree
    if (root == nullptr) {
        cout << "The tree is empty." << endl;
        return;
    }

    if (nodeExists(root, A) && nodeExists(root, B)) {
        // if it is not null print it, else print the not found result
        if (lowestCommonAncestorHelper(root, A, B) != nullptr) {
            cout << "Lowest common ancestor of " << A << " and " << B << " is: " << (*lowestCommonAncestorHelper(root, A, B)).getItem() << endl;
        } else {
            cout << "No common ancestor found." << endl;
        }
    } else {
        cout << "Key does not exist." << endl;
    }
}
// helper for check the existence of the nodes (for the case if there is a problem with existence of the nodes)
bool BST::nodeExists(BSTNode *current, int key) {
    // if there is no more node that is not null return false
    if (current == nullptr) {
        return false;
    }
    // if found the key return true
    if ((*current).getItem() == key) {
        return true;
    }

    // recursive approach for go on with subtrees
    bool found = nodeExists((*current).getLeftChild(), key) || nodeExists((*current).getRightChild(), key);
    return found;
}
// recursive helper function
BSTNode *BST::lowestCommonAncestorHelper(BSTNode *current, int A, int B) {
    // check for null pointer
    if (current == nullptr) {
        return current;
    }
    // get the current value from the pointer
    int currentValue = (*current).getItem();

    // if it is smaller than a and b look for right subtree
    if (currentValue < A && currentValue < B) {
        return lowestCommonAncestorHelper((*current).getRightChild(), A, B);
    }

    // if it is greater than a and b look for left subtree
    if (currentValue > A && currentValue > B) {
        return lowestCommonAncestorHelper((*current).getLeftChild(), A, B);
    }

    // if they are at opposite sides Lowest Common Ancestor is found.
    return current;
}

// maximumSumPath method
void BST::maximumSumPath() {
    // check for empty tree
    if (root == nullptr) {
        cout << "The tree is empty." << endl;
        return;
    }

    // initialize max sum with the smallest possible integer value
    int maxSum = -2147483648;
    // result string
    string maxPath = "";

    // call helper method to find max sum path
    maximumSumPathHelper(root, 0, maxSum, "", maxPath);

    // print the final results
    cout << "Maximum sum path is: " << maxPath << endl;
}
// recursive helper method
void BST::maximumSumPathHelper(BSTNode *TreeNode, int currentSum, int &maxSum, string currentPath, string &maxPath) {

    // base case check for null node
    if (TreeNode == nullptr) {
        return;
    }
    // add current node value to sum
    currentSum = currentSum + (*TreeNode).getItem();

    // update current path
    if (currentPath.empty()) {
        currentPath = to_string((*TreeNode).getItem());
    } else {
        currentPath += ", " + to_string((*TreeNode).getItem());
    }

    // check if it is a leaf node
    if ((*TreeNode).getLeftChild() == nullptr && (*TreeNode).getRightChild() == nullptr) {
        // update the max sum in case of new max is found
        if (currentSum > maxSum) {
            maxPath = currentPath;
            maxSum = currentSum;
        }
    }

    // recursively go on with left and right subtrees
    maximumSumPathHelper((*TreeNode).getLeftChild(), currentSum, maxSum, currentPath, maxPath);
    maximumSumPathHelper((*TreeNode).getRightChild(), currentSum, maxSum, currentPath, maxPath);
}

//maximum width method
void BST::maximumWidth() {
    // check for empty tree conditions
    if (root == nullptr) {
        cout << "The tree is empty." << endl;
        return;
    }

    // use a queue for traversal of ordered levels
    LinkedQueue<BSTNode *> nodeQueue;
    nodeQueue.enqueue(root);

    int widestLevelNodeCount = 0;
    int currentTreeLevel = 1;
    // store the wides level elements
    BSTNode **widestLevelNodes = nullptr;

    while (!nodeQueue.isEmpty()) {
        // get number of nodes at current level
        int nodesAtCurrentLevel = nodeQueue.getSize();

        // if this level has more nodes, update the widest level info
        if (nodesAtCurrentLevel > widestLevelNodeCount) {
            widestLevelNodeCount = nodesAtCurrentLevel;

            // free the old ones
            delete[] widestLevelNodes;
            widestLevelNodes = new BSTNode *[nodesAtCurrentLevel];

            // store nodes of this level
            int index = 0;
            // copying the queue
            LinkedQueue<BSTNode *> tempQueue = nodeQueue;
            while (!tempQueue.isEmpty()) {
                widestLevelNodes[index] = tempQueue.peekFront();
                index++;
                tempQueue.dequeue();
            }
        }

        // process all nodes at current level
        for (int i = 0; i < nodesAtCurrentLevel; i++) {
            BSTNode *currentNode = nodeQueue.peekFront();
            nodeQueue.dequeue();

            // enqueue children
            if ((*currentNode).getRightChild() != nullptr) {
                nodeQueue.enqueue((*currentNode).getRightChild());
            }
            if ((*currentNode).getLeftChild() != nullptr) {
                nodeQueue.enqueue((*currentNode).getLeftChild());
            }
        }

        // move to next level
        currentTreeLevel++;
    }

    // display the maximum width level's keys
    cout << "Maximum width level is: ";
    for (int i = widestLevelNodeCount - 1; i >= 0; i--) {
        if (i < widestLevelNodeCount - 1) {
            cout << ", ";
        }
        cout << (*widestLevelNodes[i]).getItem();
    }
    cout << endl;

    //clean the memory
    delete[] widestLevelNodes;
}

// findFullBTLevel method
void BST::findFullBTLevel() {
    if (root == nullptr) {
        cout << "The tree is empty." << endl;
        return;
    }

    // use queue for bst pointers
    LinkedQueue<BSTNode *> nodeQueue;
    // add root firstly
    nodeQueue.enqueue(root);

    int currentLevel = 1;
    // start with root level = 1 assume that root itself is at the level 1
    int maxFullLevel = 1;

    // iterate until it is empty
    while (!(nodeQueue.isEmpty())) {
        int levelSize = nodeQueue.getSize();
        int completeNodes = 0;
        int totalNodesWithChildren = 0;

        // initialize the counter
        int i = 0;
        // iterate all the nodes at that level
        while (i < levelSize) {
            BSTNode *current = nodeQueue.peekFront();
            nodeQueue.dequeue();

            // copy the right and left child
            BSTNode *rightChild = (*current).getRightChild();
            BSTNode *leftChild = (*current).getLeftChild();

            // count the nodes with complete children
            if (rightChild != nullptr && leftChild != nullptr) {
                // enqueue children bot right and left
                nodeQueue.enqueue(leftChild);
                nodeQueue.enqueue(rightChild);

                completeNodes++;
                totalNodesWithChildren++;
            }
            // count nodes which don't have children (leaf condition)
            else if (rightChild == nullptr && leftChild == nullptr) {
                continue;
            }
            // nodes that have only one child are not proper
            else {
                // print the result
                cout << "Full binary tree level is: " << maxFullLevel << endl;
                return;
            }
            // increase the counter
            i++;
        }

        // if all nodes at that level have two children make an update
        if (levelSize == completeNodes) {
            maxFullLevel = currentLevel + 1;
        }
        currentLevel = currentLevel + 1;
    }

    // print the result
    cout << "Full binary tree level is: " << maxFullLevel << endl;
}

// bstHeight method
int BST::bstHeight(BSTNode *root) {
    // empty tree condition
    if (root == nullptr) {
        return 0;
    }

    // recursively go on with right and left subtrees
    int leftHeight = bstHeight((*root).getLeftChild());
    int rightHeight = bstHeight((*root).getRightChild());

    // determine max height
    int maxHeight;
    if (leftHeight > rightHeight) {
        maxHeight = leftHeight;
    } else {
        maxHeight = rightHeight;
    }

    // return the height of the tree and add 1 for current node
    return maxHeight + 1;
}