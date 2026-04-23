#ifndef RBTREE_H
#define RBTREE_H

#include <memory>
#include <string>
#include <iostream>

using namespace std;

// rbt_node structure
struct rbt_node {
    int ID;
    string firstName;
    string lastName;
    string complaint;
    int triage_score;
    float wait_time;
    bool is_black;
    rbt_node* left;
    rbt_node* right;
    rbt_node* parent;
};

class RBT {
public:
  //Constructor
  RBT();

  //Destructor
  ~RBT();

  //Initializes a new node and returns a pointer to it - each node represents one patient!
  rbt_node* init_node(int ID, string lastName, string firstName, string complaint, int triage_score, float wait_time);

  //GENERAL FUNCTIONS ------------------------
  //New patient
  void insert(rbt_node* new_node);

  //Updates triage score and wait time on patient node
  void update_priority(int ID, int triage_score, float wait_time);

  //Obtains next patient depending on triage_score, and wait_time - ID# is tiebreaker. Removes patient from tree as though they have been treated.
  rbt_node* get_next_patient();

  //Obtains patient name based on ID, does not remove patient from tree.
  rbt_node* search_patient(int ID);

  //Print list of patients by order of priority
  void print_tree();


private:
  rbt_node* root;
  //INTERNAL TREE FUNCTIONS AND HELPERS ----------------------------
  //Recolors and rotates tree after an insertion to match RBT rules - no double red nodes, ect.
  void insert_fix(rbt_node* new_node);

  //Rotation functions
  void left_rotate(rbt_node*& root, rbt_node* x);
  void right_rotate(rbt_node*& root, rbt_node* y);

  //Helper function to find the most left node in the right subtree - maintains RBT order while deleting a node
  rbt_node* tree_min(rbt_node* node);

  //Swaps out nodes in the tree, updates pointers
  void rbt_transplant(rbt_node*& root, rbt_node* u, rbt_node* v);

  //Delete node function
  void rbt_delete(rbt_node*& root, rbt_node* z);

  //Delete helper function - fixes colors and rebalances the tree
  void rbt_delete_fixup(rbt_node*& root, rbt_node* x);

  //Recursive helper function for patient search
  rbt_node* get_patient_info(rbt_node* node, int ID);

  //Recursive helper function for print_tree
  void print_inorder(rbt_node* node);

  //Recursive destructor helper function
  void delete_subtree(rbt_node* node);
};

#endif // RBTree.h
