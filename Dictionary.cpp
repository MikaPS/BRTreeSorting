//-----------------------------------------------------------------------------
// Mika Peer Shalem, mpeersha
// 2023 Winter CSE101, PA8
// Dictionary.cpp
// Implements a Dictionary ADT that includes access and manipulation functions. 
// Dict has a node that repreesnts its key and a node for the value.
//-----------------------------------------------------------------------------
#include<iostream>
#include<string>
#include "Dictionary.h"
using namespace std;

#define RED 1
#define BLACK 2

// Exported types -------------------------------------------------------------
typedef std::string keyType;  // must be comparable using <, <=, >, >=, ==, !=
typedef int         valType;

Dictionary::Node::Node(keyType k, valType v) {
   key = k;
   val = v;
   color = BLACK;
   parent = nullptr;
   left = nullptr;
   right = nullptr;
}

// Helper Functions (Optional) ---------------------------------------------

// inOrderString()
// Appends a string representation of the tree rooted at R to string s. The
// string appended consists of: "key : value \n" for each key-value pair in
// tree R, arranged in order by keys.
void Dictionary::inOrderString(std::string& s, Node* R) const {
   if (R != nullptr && R != nil) {
      inOrderString(s, R->left);
      s += R->key + " : " + std::to_string(R->val) + "\n";
      inOrderString(s, R->right);
   }
}

// preOrderString()
// Appends a string representation of the tree rooted at R to s. The appended
// string consists of keys only, separated by "\n", with the order determined
// by a pre-order tree walk.
void Dictionary::preOrderString(std::string& s, Node* R) const {
   if (R!=nil && R!=nullptr) {
      s += R->key + "\n";
      preOrderString(s, R->left);
      preOrderString(s, R->right);
   }
}

// preOrderCopy()
// Recursively inserts a deep copy of the subtree rooted at R into this 
// Dictionary. Recursion terminates at N.
void Dictionary::preOrderCopy(Node* R, Node* N) {
   if (R!=nil && R!=nullptr && R != N) {
      setValue(R->key, R->val);
      preOrderCopy(R->left, N);
      preOrderCopy(R->right, N);
   }
}

// postOrderDelete()
// Deletes all Nodes in the subtree rooted at R, sets R to nil.
void Dictionary::postOrderDelete(Node* R) {
   if (R != nil && R != nullptr) {
      postOrderDelete(R->left);
      postOrderDelete(R->right);
      if (current->key == R->key) {
         current = nil;
      }
      num_pairs -= 1;
      if (R->left == nil || R->left == nullptr) {
         transplant(R, R->right);
      } else if (R->right == nil || R->right == nullptr) {
         transplant(R, R->left);
      } else {
         Node * y = findMin(R->right);
         if (y->parent != R) {
            transplant(y, y->right);
            y->right = R->right;
            y->right->parent = y;
         }
         transplant(R, y);
         y->left = R->left;
         y->left->parent = y;
      }
      delete R;
      R = nullptr;
   }
}

// search()
// Searches the subtree rooted at R for a Node with key==k. Returns
// the address of the Node if it exists, returns nil otherwise.
Dictionary::Node* Dictionary::search(Node* R, keyType k) const {
   if ((R == nullptr) || (R == nil)) {
      return nil;
   } 
   int cmp = k.compare(R->key);
   if (cmp == 0) {
      return R;
   } else if (cmp < 0) {
      return search(R->left, k);
   } else { // k > R->key
      return search(R->right, k);
   }
   return nil;
}

// findMin()
// If the subtree rooted at R is not empty, returns a pointer to the 
// leftmost Node in that subtree, otherwise returns nil.
Dictionary::Node* Dictionary::findMin(Node* R) {
   // cout << "R in find min is " << R->val << endl;
   while (R->left != nil && R->left != nullptr) {
      // cout << "R in find min is " << R->val << endl;
      R = R->left;
   }
   if (R == nullptr) { return nil; }
   // cout << "R in find min is " << R->val << endl;
   return R;
}

// findMax()
// If the subtree rooted at R is not empty, returns a pointer to the 
// rightmost Node in that subtree, otherwise returns nil.
Dictionary::Node* Dictionary::findMax(Node* R) {
   while (R->right != nil && R->right != nullptr) {
      R = R->right;
   }
   if (R == nullptr) { return nil; }
   return R;
}

// findNext()
// If N does not point to the rightmost Node, returns a pointer to the
// Node after N in an in-order tree walk.  If N points to the rightmost 
// Node, or is nil, returns nil. 
Dictionary::Node* Dictionary::findNext(Node* N) {
   if (N->right != nil && N->right != nullptr) {
      return findMin(N->right);
   }
   Node *Y = N->parent;
   while (Y != nil && Y != nullptr && N == Y->right) {
      N = Y;
      Y = Y->parent;
   }
   if (Y == nullptr) { return nil; }
   return Y;
}

// findPrev()
// If N does not point to the leftmost Node, returns a pointer to the
// Node before N in an in-order tree walk.  If N points to the leftmost 
// Node, or is nil, returns nil.
Dictionary::Node* Dictionary::findPrev(Node* N) {
   if (N->left != nil && N->left != nullptr) {
      return findMax(N->left);
   }
   Node *Y = N->parent;
   while (Y != nil && Y != nullptr && N == Y->left) {
      N = Y;
      Y = Y->parent;
   }
   if (Y == nullptr) { return nil; }
   return Y;
}

// Class Constructors & Destructors ----------------------------------------

// Creates new Dictionary in the empty state. 
Dictionary::Dictionary() {
   nil = new Node("", -1);
   root = nil;
   root->parent = nil;
   // root->left = nil;
   // root->right = nil;
   current = nil;
   num_pairs = 0;
}

// Copy constructor.
Dictionary::Dictionary(const Dictionary& D) {
   // Make an empty dict
   nil = new Node("", -1);
   root = nil;
   root->parent = nil;
   current = nil;
   num_pairs = 0;
   // Load elements of D into the dict
   preOrderCopy(D.root, D.nil);
}

// Destructor
Dictionary::~Dictionary() {
   // cout << "\nDES Root is " << root->key << " Color " << root->color << endl;
   // cout << "DES Child is " << root->left->key << " Color " << root->left->color << endl;
   // cout << "DES right Child is " << root->right->key << " Color " << root->right->color << endl;
   // cout << "DES right Child is " << root->right->right->key << " Color " << root->right->right->color << endl;
   // cout << "IN DESTRCUTOR" << endl;
   // printf("IN HEREH %d\n", num_pairs);
   clear();
   delete nil;
   nil = nullptr;
}


// RBT Helper Functions (Optional) -----------------------------------------
   
// LeftRotate()
void Dictionary::LeftRotate(Node* N) {
   // set y
   Node *y = N->right;

   // turn y's left subtree into N's right subtree
   N->right = y->left;
   if (y->left != nullptr && y->left != nil) {
      y->left->parent = N;
   }

   // link y's parent to N
   y->parent = N->parent;
   // cout << "y is " << y->val << endl;
   if (N->parent == nullptr || N->parent == nil) {
      root = y;
   } else if (N == N->parent->left) {
      N->parent->left = y;
   } else {
      N->parent->right = y;
   }

   // put N on y's left
   y->left = N;
   N->parent = y;
}

// RightRotate()
void Dictionary::RightRotate(Node* N) {
   // set y
   Node *y = N->left;

   // turn y's right subtree into N's left subtree
   N->left = y->right;
   if (y->right != nil && y->right != nullptr) {
      y->right->parent = N;
   }

   // link y's parent to N
   y->parent = N->parent;
   if (N->parent == nullptr || N->parent == nil) {
      root = y;
   } else if (N == N->parent->right) {
      N->parent->right = y;
   } else {
      N->parent->left = y;
   }

   // put N on y's right
   y->right = N;
   N->parent = y;
}

// RB_Transplant()
void Dictionary::RB_Transplant(Node* u, Node* v) {
   if (u->parent == nil || u->parent == nullptr) {
      root = v;
   } else if (u == u->parent->left) {
      u->parent->left = v;
   } else {
      u->parent->right = v;
   }
   v->parent = u->parent;
}

// RB_DeleteFixUp()
void Dictionary::RB_DeleteFixUp(Node* N) {
   while (N != root && N->color == BLACK) {
      if (N == N->parent->left) {
         // printf("CASES 1-4\n");
         Node * w = N->parent->right;
         if (w->color == RED) {
            // Case 1
            // printf("case 1\n");
            w->color = BLACK;
            N->parent->color = RED;
            LeftRotate(N->parent);
            w = N->parent->right;
         }
         if (w->left->color == BLACK && w->right->color == BLACK) {
            // Case 2
            // printf("case 2\n");
            w->color = RED;
            // if (N->left == nil && N->right == nil) {
            //    N->left = nullptr;
            //    N->right = nullptr;
            // }
            N = N->parent;
         } else {
            // Case 3
            if (w->right->color == BLACK) {
               // printf("case 3\n");
               w->left->color = BLACK;
               w->color = RED;
               RightRotate(w);
               w = N->parent->right;
            }
            // Case 4
            // printf("case 4\n");
            w->color = N->parent->color;
            N->parent->color = BLACK;
            w->right->color = BLACK;
            LeftRotate(N->parent);
            N = root;
         }
      } else {
         // printf("CASES 5-8\n");
         // Case 5
         Node * w = N->parent->left;
         if (w->color == RED) {
            w->color = BLACK;
            N->parent->color = RED;
            RightRotate(N->parent);
            w = N->parent->left;
         }
         if (w->right->color == BLACK && w->left->color == BLACK) {
            // Case 6
            w->color = RED;
            N = N->parent;
         } else {
            // Case 7
            if (w->left->color == BLACK) {
               w->right->color = BLACK;
               w->color = RED;
               LeftRotate(w);
               w = N->parent->left;
            }
            // Case 8
            w->color = N->parent->color;
            N->parent->color = BLACK;
            w->left->color = BLACK;
            RightRotate(N->parent);
            N = root;
         }
      }
   }
   N->color = BLACK;
}

// RB_Delete()
void Dictionary::RB_Delete(Node* N) {
   Node * y = N;
   Node * x;
   int y_original_color = y->color;
   if (N->left == nil || N->left == nullptr) {
      x = N->right;
      RB_Transplant(N, N->right);
   } else if (N->right == nil || N->right == nullptr) {
      x = N->left;
      RB_Transplant(N, N->left);
   } else {
      y = findMin(N->right);
      y_original_color = y->color;
      x = y->right;
      if (y->parent == N) {
         x->parent = y;
      } else {
         RB_Transplant(y, y->right);
         y->right = N->right;
         y->right->parent = y;
      }
      RB_Transplant(N, y);
      y->left = N->left;
      y->left->parent = y;
      y->color = N->color;
   }
   if (y_original_color == BLACK) {
      RB_DeleteFixUp(x);
   }
}

// Access functions --------------------------------------------------------

// size()
// Returns the size of this Dictionary.
int Dictionary::size() const {
   return num_pairs;
}

// contains()
// Returns true if there exists a pair such that key==k, and returns false
// otherwise.
bool Dictionary::contains(keyType k) const {
   if (root != nullptr && root != nil) {
      Node * s = search(root, k);
      if (s == nil) { return false; }
      else { return true; }
   }
   return false;
}

// getValue()
// Returns a reference to the value corresponding to key k.
// Pre: contains(k)
valType& Dictionary::getValue(keyType k) const {
   Node * N = search(root, k);
   if (N == nil) {
      throw std::logic_error("Dictionary: getValue(): key \"" + k + "\" does not exist");
   }
   return N->val;
}

// hasCurrent()
// Returns true if the current iterator is defined, and returns false 
// otherwise.
bool Dictionary::hasCurrent() const {
   if (current != nil && current != nullptr) { return true; }
   return false;
}

// currentKey()
// Returns the current key.
// Pre: hasCurrent() 
keyType Dictionary::currentKey() const {
   if (!hasCurrent()) {
      throw std::logic_error("Dictionary: currentKey(): current undefined");
   }
   return current->key;
}

// currentVal()
// Returns a reference to the current value.
// Pre: hasCurrent()
valType& Dictionary::currentVal() const {
   if (!hasCurrent()) {
      throw std::logic_error("Dictionary: currentVal(): current undefined");
   }
   return current->val;
}


// Manipulation procedures -------------------------------------------------

// clear()
// Resets this Dictionary to the empty state, containing no pairs.
void Dictionary::clear() {
   // cout << "\nCLEAR Root is " << root->key << " Color " << root->color << endl;
   // cout << "CLEAR Child is " << root->left->key << " Color " << root->left->color << endl;
   // cout << "CLEAR right Child is " << root->right->key << " Color " << root->right->color << endl;
   // cout << "CLEAR right Child is " << root->right->right->key << " Color " << root->right->right->color << endl;
   if (num_pairs > 0) {
      // delete root->parent;
      // root->parent = nullptr;
      postOrderDelete(root);
   }
   root = nil;
   current = nil;
   num_pairs = 0;
}

// RB_InsertFixUP()
void Dictionary::RB_InsertFixUp(Node* N) {
   Node * y;
   while (N->parent->color == RED) {
      if (N->parent == N->parent->parent->left) { // uncle is right side
         // printf("CASES 1-3\n");
         y = N->parent->parent->right; // y = uncle
         // printf("before\n");
         // cout << "Y val " << y->val << " color  " << y->color << endl;
         // printf("after\n");
         // Case 1
         if (y->color == RED) {
            // printf("case 1\n");
            N->parent->color = BLACK;
            y->color = BLACK;
            N->parent->parent->color = RED;
            N = N->parent->parent;
            // break;
         } else {
            // Case 2
            if (N == N->parent->right) {
               // printf("case 2\n");
               N = N->parent;
               LeftRotate(N);
            }
            // Case 3
            // printf("case 3\n");
            N->parent->color = BLACK;
            N->parent->parent->color = RED;
            RightRotate(N->parent->parent);
         }
      } else {
         y = N->parent->parent->left;
         // printf("cases 4-6\n");
         // cout << "y color: " << y->color << endl;
         // Case 4
         if (y->color == RED) {
            // printf("case 4\n");
            N->parent->color = BLACK;
            y->color = BLACK;
            N->parent->parent->color = RED;
            N = N->parent->parent;
            // break;
         } else {
            // Case 5
            if (N == N->parent->left) {
               // printf("case 5\n");
               N = N->parent;
               RightRotate(N);
            }
            // Case 6
            // printf("case 6\n");
            N->parent->color = BLACK;
            N->parent->parent->color = RED;
            LeftRotate(N->parent->parent);
         }
      }
   }
   root->color = BLACK;
   // printf("END\n");
   // cout << "\nfixup Root is " << root->key << " Color " << root->color << endl;
   //  cout << "FIXUP Child is " << root->left->key << " Color " << root->left->color << endl;
}

// setValue()
// If a pair with key==k exists, overwrites the corresponding value with v, 
// otherwise inserts the new pair (k, v).
void Dictionary::setValue(keyType k, valType v) {
   // cout << "v is " << v << " key is " << k << endl;
   Node * y = nil;
   Node * x = root;
   while (x != nil) {
      y = x;
      int cmp = (k).compare(x->key);
      if (cmp == 0) {
         x->val = v;
         return;
      } 
      else if (cmp < 0) {
         x = x->left;
      } else {
         x = x->right;
      }
   }
   Node * z = new Node(k, v); 
   num_pairs += 1;
   z->left = nil;
   z->right = nil;
   z->parent = y;
   // tree was empty
   if (y == nil) {
      root = z;
      return;
   } else if (z->key < y->key) {
      y->left = z;
   } else {
      y->right = z;
   }
   z->color = RED;
   // cout << "before Z is " << z->val << endl;
   // cout << "z left " << z->left->val << " z right " << z->right->val << endl;
   // cout << "INSERT Root is " << root->val << endl;
   // if (num_pairs >= 3) {
   RB_InsertFixUp(z);
   // cout << "\nINSERT Root is " << root->key << " Color " << root->color << endl;
   //    if (num_pairs >= 3) {
   //       cout << "INSERT left child is " << root->left->key << " Color " << root->left->color << endl;
   //   cout << "INSERT right Child is " << root->right->key << " Color " << root->right->color << endl;
   //   cout << "INSERT rr Child is " << root->right->right->key << " Color " << root->right->right->color << endl;
   //      cout << "INSERT rl Child is " << root->right->left->key << " Color " << root->right->left->color << endl;
   //   cout << "INSERT lr Child is " << root->left->right->key << " Color " << root->left->right->color << endl;
   //      cout << "INSERT ll Child is " << root->left->left->key << " Color " << root->left->left->color << endl;
   // }
}

// transplant()
// Swaps two nodes
void Dictionary::transplant(Node *u, Node *v) {
   if (u->parent == nil || u->parent == nullptr) {
      root = v;
   } else if (u == u->parent->left) {
      u->parent->left = v;
   } else {
      u->parent->right = v;
   }
   if (v != nil && v != nullptr) {
      v->parent = u->parent;
   }
}

// remove()
// Deletes the pair for which key==k. If that pair is current, then current
// becomes undefined.
// Pre: contains(k).
void Dictionary::remove(keyType k) {
//   if (num_pairs == 0) { return; }
   Node * z = search(root, k);
   if (z == nil) {
      throw std::logic_error("Dictionary: remove(): key \"" + k + "\" does not exist");
   }
   if (current->key == k) {
      current = nil;
   }
   num_pairs -= 1;

   RB_Delete(z);
   // if (z->left == nil) {
   //    z->left = nullptr;
   // }
   // if (z->right == nil) {
   //    z->right = nullptr;
   // }
   delete z;
   z = nullptr;
   // cout << "Tree is: " << to_string() << endl;
   // cout << "REMOVE Root is " << root->key << " Color " << root->color << endl;
   // cout << "REMOVE left Child is " << root->left->key << " Color " << root->left->color << endl;
   // cout << "REMOVE ll Child is " << root->left->left->val << " Color " << root->left->left->color << endl;
   // cout << "REMOVE lr Child is " << root->left->right->val << " Color " << root->left->right->color << endl;
   // cout << "REMOVE right Child is " << root->right->key << " Color " << root->right->color << endl;
   // cout << "REMOVE rl Child is " << root->right->left->key << " Color " << root->right->left->color << endl;
   // cout << "REMOVE rr Child is " << root->right->right->key << " Color " << root->right->right->color << endl;
}

// begin()
// If non-empty, places current iterator at the first (key, value) pair
// (as defined by the order operator < on keys), otherwise does nothing. 
void Dictionary::begin() {
   if (num_pairs > 0) {
      // printf("here\n");
      // cout << "root val" << root->val << endl;
      current = findMin(root); // In BST, the root has the smallest value
      // cout << "Current val" << current->val << endl;
   }
}

// end()
// If non-empty, places current iterator at the last (key, value) pair
// (as defined by the order operator < on keys), otherwise does nothing. 
void Dictionary::end() {
   if (num_pairs > 0) {
      current = findMax(root); // IN BST, largest value is the end node
   }
}

// next()
// If the current iterator is not at the last pair, advances current 
// to the next pair (as defined by the order operator < on keys). If 
// the current iterator is at the last pair, makes current undefined.
// Pre: hasCurrent()
void Dictionary::next() {
   if (!hasCurrent()) {
      throw std::logic_error("Dictionary: next(): current undefined");
   }
   if (current != findMax(root)) {
      current = findNext(current);
   } else {
      current = nil;
   }
}

// prev()
// If the current iterator is not at the first pair, moves current to  
// the previous pair (as defined by the order operator < on keys). If 
// the current iterator is at the first pair, makes current undefined.
// Pre: hasCurrent()
void Dictionary::prev() {
   if (!hasCurrent()) {
      throw std::logic_error("Dictionary: prev(): current undefined");
   }
   if (current != findMin(root)) {
      current = findPrev(current);
   } else {
      current = nil;
   }
}


// Other Functions ---------------------------------------------------------

// to_string()
// Returns a string representation of this Dictionary. Consecutive (key, value)
// pairs are separated by a newline "\n" character, and the items key and value 
// are separated by the sequence space-colon-space " : ". The pairs are arranged 
// in order, as defined by the order operator <.
std::string Dictionary::to_string() const {
   std::string s;
   inOrderString(s, root);
   return s; 
}

// pre_string()
// Returns a string consisting of all keys in this Dictionary. Consecutive
// keys are separated by newline "\n" characters. The key order is given
// by a pre-order tree walk.
std::string Dictionary::pre_string() const {
   std::string s;
   preOrderString(s, root);
   return s; 
}

// equals()
// Returns true if and only if this Dictionary contains the same (key, value)
// pairs as Dictionary D.
bool Dictionary::equals(const Dictionary& D) const {
   std::string s; 
   std::string s1;
   Dictionary copy = D;
   if (num_pairs==0 && D.num_pairs==0) { return true; }
   if (num_pairs != D.num_pairs) { return false; }
   inOrderString(s, root);
   copy.inOrderString(s1, copy.root);
   return (s==s1);
}

// Overloaded Operators ----------------------------------------------------

// operator<<()
// Inserts string representation of Dictionary D into stream, as defined by
// member function to_string().
std::ostream& operator<<( std::ostream& stream, Dictionary& D ) {
   return stream << D.Dictionary::to_string();
}

// operator==()
// Returns true if and only if Dictionary A equals Dictionary B, as defined
// by member function equals(). 
bool operator==( const Dictionary& A, const Dictionary& B ) {
   return A.equals(B);
}

// operator=()
// Overwrites the state of this Dictionary with state of D, and returns a
// reference to this Dictionary.
Dictionary& Dictionary::operator=( const Dictionary& D ) {
   if (this != &D) {
        // Make a copy of D
        Dictionary temp = D;
        // Swap the copy's fields with fields of this
        std::swap(nil, temp.nil);
        std::swap(root, temp.root);
        std::swap(current, temp.current);
        std::swap(num_pairs, temp.num_pairs);
    }
    // return this with the new data installed
    return *this;
}
