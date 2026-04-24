# CSPB 2270 Final Project: Red-Black Tree Emergency Department Patient Triage System

**Project Overview:** This program is a simple emergency department triage system using a red-black tree to track patients arriving at the ED and prioritize them for care depending on their triage scores and wait times. Each node in the red-black tree represents a patient and contains their information, such as a patient ID, first and last name, complaint, triage score, wait time, the node’s color, and pointers to left, right, and parent nodes. Users are able to view the current triage priority, input new patients, update a patient’s priority, search for a patient, and ‘treat’ a patient (remove the highest priority patient from the tree).
### Prioritization of Nodes
Nodes are prioritized first on their triage score, from 1 to 5. Smaller numbers indicate higher medical urgency and are seen first. If patients share the same triage score, the next-highest priority is longer wait time, so that patients who have been waiting longer for treatment are seen sooner. If two patients share the same triage score and wait times, the tiebreaker is the smaller patient ID number.
### Red-Black Tree Data Structure
Red-black trees (RB trees) are self-balancing binary search trees which have worst-case complexity of O(log n) for searches, insertions, and deletions. This allows for efficient data retrieval and node tracking even with a high volume of data. Like binary search trees, RB trees maintain an ordered list of nodes, where each node can have at most two child nodes, and in every case the left child nodes are ‘less than’ and the right child nodes are ‘greater than’ the parent node. However, RB trees have certain rules regarding node color and order that distinguish them from binary search trees. These rules allow RB trees to maintain a shallow depth, and prevent them from becoming skewed or turning into linked lists. Because RB trees are self-balancing, they have several methods of maintaining the balance and structure of the tree during insertions and deletions. These methods are:
* Rotation: The nodes of the tree rotate either to the left or the right, to promote one node to the higher depth of a parent node, and related nodes will be moved around to preserve priority while maintaining RB tree properties.
* Recoloring: While changing the structure of the tree to maintain balance, some nodes are recolored from red to black or black to red to maintain the red-black properties listed above.

### Red-Black Tree Invariants
* Every node in the tree must be colored either black or red
* The root node must be black
* Red nodes cannot be adjacent, meaning red nodes cannot have red child nodes
* Every path from a node to its descendant leaves should contain the same number of black nodes
* All null leaves must be black

### Implementation
It took longer than anticipated to implement the tree rotations and correct red-black violations when deleting nodes. The rbt_delete_fixup function specifically took several days to implement due to the number of cases to keep track of in order to maintain the tree's balance. Debugging specific cases was especially hard, because one error in one case would debalance the entire tree. 
### Wait Times
I considered trying to make a separate array of the patients’ wait times, and then mapping each wait time to the associated node to attempt to update the wait times based on the number of tree traversals or patient searches by the user. I quickly scrapped this idea because it would have increased the time and space complexity of the program significantly, and I wanted to focus on creating an efficient RB tree.

### Running the Program
To set up and run the triage program:
1. Clone the repository. 
2. In a terminal, run the following lines: 
    * `g++ -c RBTree.cpp`
    * `g++ -c main.cpp`
    * `g++ RBTree.o main.o -o binary`
3. Run the binary file.
### Major Functions
* `init_node(int ID, string last, string first, string complaint, int triage_score, float wait_time)` - Initializes a new node.

* `insert(rbt_node* new_node)` - Inserts a new node into the tree based on priority. Calls insert_fix function.

* `insert_fix(rbt_node* new_node)` - Helper function which reorders and recolors nodes on insertion to maintain RB tree invariants, uses left_rotate and right_rotate functions.

* `update_priority(int ID, int triage_score, float wait_time)` - Updates a node’s triage score and wait time. In real life, this function would be used to update a patient’s priority as their condition worsens or improves (or if they’ve been waiting for treatment for an extended period of time).

* `search_patient(int ID)` - Obtains patient’s name based on ID, does not remove the node from the tree. Calls get_patient_info, a recursive private function which searches the tree.
* `get_next_patient()` - Removes and returns the highest-priority patient from the tree as though they have been treated. The rest of the tree is rotated/recolored to preserve red-black integrity and reprioritize patients.

* `print_tree()` - Prints the list of patients by order of priority. Calls a print_inorder recursive helper function.

* `rbt_delete(rbt_node*& root, rbt_node* z)` - Calls three helper functions: rbt_transplant, rbt_delete_fixup, and tree_min. The rbt_transplant function swaps out nodes in the tree and updates pointers. The rbt_delete_fixup function recolors and rebalances the tree. The tree_min function finds the furthest-left node in a right subtree.

### Node Structure
Each node represents one patient and contains:

    int ID;          //Unique six-digit patient identifier.
    string firstName;
    string lastName;
    string complaint;          //String containing patient’s reason for seeking care
    int triage_score;          //Single-digit int from 1-5 indicating condition severity
    float wait_time;          //Float indicating length of time waiting for care (in hours)
    bool is_black;          //Bool determining node color
    rbt_node* left;          //Pointer to left node
    rbt_node* right;          //Pointer to right node
    rbt_node* parent;          //Pointer to parent

