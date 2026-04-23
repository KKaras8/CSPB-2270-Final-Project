#include "RBTree.h"

RBT::RBT() {
  root = nullptr;
}

RBT::~RBT() {
    delete_subtree(root);
}

void RBT::insert(rbt_node* new_node){
    rbt_node* y = nullptr;
    rbt_node* x = root;
    while (x != nullptr){
        y = x;
        if (new_node->triage_score < x->triage_score || (new_node->triage_score == x->triage_score && (new_node->wait_time > x->wait_time || (new_node->wait_time == x->wait_time && new_node->ID < x->ID)))){
            x = x->left;
        } else {
            x = x->right;
        }
    }
    new_node->parent = y;
    if (y == nullptr) {
        root = new_node;
    } else if (new_node->triage_score < y->triage_score || (new_node->triage_score == y->triage_score && (new_node->wait_time > y->wait_time || (new_node->wait_time == y->wait_time && new_node->ID < y->ID)))){
        y->left = new_node;
    } else {
        y->right = new_node;
    }
    new_node->left = new_node->right = nullptr;
    new_node->is_black = false;
    insert_fix(new_node);
}

void RBT::insert_fix(rbt_node* new_node){
    while (new_node->parent && !new_node->parent->is_black){
        rbt_node* gp = new_node->parent->parent;
        if (new_node->parent == gp->left){
            rbt_node* y = gp->right;

            if (y && !y->is_black){
                new_node->parent->is_black = true;
                y->is_black = true;
                gp->is_black = false;
                new_node = gp;
            } else{
                if (new_node == new_node->parent->right){
                    new_node = new_node->parent;
                    left_rotate(root, new_node);
                }
                new_node->parent->is_black = true;
                gp->is_black = false;
                right_rotate(root, gp);
            }
        } else {
            rbt_node* y = gp->left;

            if (y && !y->is_black){
                new_node->parent->is_black = true;
                y->is_black = true;
                gp->is_black = false;
                new_node = gp;
            } else {
                if (new_node == new_node->parent->left){
                    new_node = new_node->parent;
                    right_rotate(root, new_node);
                }
                new_node->parent->is_black = true;
                gp->is_black = false;
                left_rotate(root, gp);
            }
        }
    }
    root->is_black = true;
}

rbt_node* RBT::get_next_patient(){
    if (!root) return nullptr;
    rbt_node* next = tree_min(root);
    rbt_delete(root, next);
    return next;
}


rbt_node* RBT::init_node(int ID, string last, string first, string complaint, int triage_score, float wait_time) { 
    rbt_node* node = new rbt_node;
    node->ID = ID;
    node->lastName = last;
    node->firstName = first;
    node->complaint = complaint;
    node->triage_score = triage_score;
    node->wait_time = wait_time;
    node->is_black = false;
    node->left = node->right = node->parent = nullptr;
    return node;
    }

void RBT::left_rotate(rbt_node*& root, rbt_node* x){
    rbt_node* y = x->right;
    x->right = y->left;
    if (y->left){
        y->left->parent = x;
    }
    y->parent = x->parent;
    if (!x->parent){
        root = y;
    } else if (x == x->parent->left){
        x->parent->left = y;
    } else {
        x->parent->right = y;
    }
    y->left = x;
    x->parent = y;
}

void RBT::right_rotate(rbt_node*& root, rbt_node* y){
    rbt_node* x = y->left;
    y->left = x->right;
    if (x->right){
        x->right->parent = y;
    }
    x->parent = y->parent;
    if (!y->parent){
        root = x;
    } else if (y == y->parent->left){
        y->parent->left = x;
    } else {
        y->parent->right = x;
    }
    x->right = y;
    y->parent = x;
}

void RBT::update_priority(int ID, int triage_score, float wait_time){
    //Find the right node, return if not found
    rbt_node* node = get_patient_info(root, ID);
    if (!node) return;
    //Delete from tree
    rbt_delete(root, node);
    
    //Update
    node->triage_score = triage_score;
    node->wait_time = wait_time;

    //Reinsert
    insert(node);
}
    
rbt_node* RBT::get_patient_info(rbt_node* node, int ID){
    if (!node) return nullptr;
    
    //check current node
    if (node->ID == ID){
        return node;
    }

    //Search left
    rbt_node* left = get_patient_info(node->left, ID);
    if (left) return left;
    
    //Search right
    return get_patient_info(node->right, ID);
}

rbt_node* RBT::search_patient(int ID){
    return get_patient_info(root, ID);
}

void RBT::print_tree(){
    print_inorder(root);
}

void RBT:: print_inorder(rbt_node* node){
    if (!node){
        return;
    }
    print_inorder(node->left);
    cout << node->lastName << ", " << node->firstName << " | ID: " << node->ID << " | Triage Score: " << node->triage_score << " | Wait Time: " << node->wait_time << endl;
    print_inorder(node->right);
}

void RBT::rbt_transplant(rbt_node*& root, rbt_node* u, rbt_node* v){
    if (!u->parent){
        root = v;
    } else if (u == u->parent->left){
        u->parent->left = v;
    } else {
        u->parent->right = v;
    }
    if (v){
        v->parent = u->parent;
    }
}

void RBT::rbt_delete(rbt_node*& root, rbt_node* z){
    rbt_node* y = z;
    rbt_node* x = nullptr;
    bool y_orig_color = y->is_black;

    //No left child
    if (!z->left){
        x = z->right;
        rbt_transplant(root, z, z->right);
    }
    //No right child
    else if (!z->right){
        x = z->left;
        rbt_transplant(root, z, z->left);
    }
    else {
        y = tree_min(z->right);
        y_orig_color = y->is_black;
        x = y->right;

        if (y->parent != z){
            rbt_transplant(root, y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        rbt_transplant(root, z, y);
        y->left = z->left;
        y->left->parent = y;
        y->is_black = z->is_black;
    }

    if (y_orig_color){
        rbt_delete_fixup(root, x);
    }
}

rbt_node* RBT::tree_min(rbt_node* node){
    while (node->left) {
        node = node->left;
    }
    return node;
}

void RBT::rbt_delete_fixup(rbt_node*& root, rbt_node* x){
    while (x != root && (x == nullptr || x->is_black == true)){
        if (!x || !x->parent){
            break;
        }
        if (x == x->parent->left){
            rbt_node* w = x->parent->right;

            if (w && w->is_black == false){
                w->is_black = true;
                x->parent->is_black = false;
                left_rotate(root, x->parent);
                w = x->parent->right;
            }

            if (!w || ((w->left == nullptr || w->left->is_black == true) && (w->right == nullptr || w->right->is_black == true))){
                w->is_black = false;
                x = x->parent;
            }
            else{
                if (w->right == nullptr || w->right->is_black == true){
                    if (w->left){
                        w->left->is_black = true;
                    }
                    w->is_black = false;
                    right_rotate(root, w);
                    w = x->parent->right;
                }

                w->is_black = x->parent->is_black;
                x->parent->is_black = true;
                if (w->right){
                    w->right->is_black = true;
                }
                left_rotate(root, x->parent);
                x = root;
                }
        }
        else {
            rbt_node* w = x->parent->left;

            if (w && w->is_black == false){
                w->is_black = true;
                x->parent->is_black = false;
                right_rotate(root, x->parent);
                w = x->parent->left;
            }

            if (!w || ((w->right == nullptr || w->right->is_black == true) && (w->left == nullptr || w->left->is_black == true))){
                w->is_black = false;
                x = x->parent;
            }
            else{
                if (w->left == nullptr || w->left->is_black){
                    if (w->right){
                        w->right->is_black = true;
                    }
                    w->is_black = false;
                    left_rotate(root, w);
                    w = x->parent->left;
                }
                w->is_black = x->parent->is_black;
                x->parent->is_black = true;
                if (w->left){
                    w->left->is_black = true;
                }
                right_rotate(root, x->parent);
                x = root;
            }
        }
    }
    if (x) {
        x->is_black = true;
    }
}

void RBT::delete_subtree(rbt_node* node){
    if (!node)return;
    delete_subtree(node->left);
    delete_subtree(node->right);
    delete node;
}





