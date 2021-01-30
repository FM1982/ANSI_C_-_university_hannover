/*
Compile: make integer_tree_test
Run: ./integer_tree_test
make integer_tree_test && ./integer_tree_test
*/

#include "integer_tree.h"

Node* get_interval_rec(BTNode* tree, int lower, int upper, Node* result) {
    // (d) todo: implement
    //printf("%d", tree->value);
    if(tree == NULL){
        return result;
    }
    if(tree->value >= lower && tree->value <= upper){
        result = insert_ordered(result, tree->value);
        //result = result->next;
    }
    result = get_interval_rec(tree->left, lower, upper, result);
    result = get_interval_rec(tree->right, lower, upper, result);

    return result;
}

Node* get_interval(BTNode* tree, int lower, int upper) {
    return get_interval_rec(tree, lower, upper, NULL);
}

bool in_interval(int element, void* x) {
    // (e) todo: implement
    int* limits = (int*) x;

    if(element <= limits[1] && element >= limits[0]){
        return true;
    }
    else{
        return false;
    }
}

// check whether for each node the values of the children are larger
// than the value of the node
// return true for the empty tree
bool is_monotone(BTNode* t) {
    // (f) todo: implement
    bool tree_res = false;

    if(t == NULL || (t->left == NULL && t->right == NULL)) tree_res = true;

    if(t->left == NULL && t->right != NULL){
        if(t->right->value > t->value){
            tree_res = true && is_monotone(t->right);
        }
        else{
            tree_res = false;
        }
    }

    if(t->left != NULL && t->right == NULL){
        if(t->left->value > t->value){
            tree_res = true && is_monotone(t->left);
        }
        else{
            tree_res = false;
        }
    }

    if(t->left != NULL && t->right != NULL){
        if(t->left->value > t->value && t->right->value > t->value){
            tree_res = true && is_monotone(t->left) && is_monotone(t->right);
        }
        else{
            tree_res = false;
        }
    }

    return tree_res;
}

int main(void) {
    base_init();
    base_set_memory_check(true);

    int values[] = { 22, 44, 19, 8, 97, 36, 56, 33, 29 };
    int n = sizeof(values) / sizeof(int);

    // (a) todo: implement
    BTNode* t = NULL;
    // ...

    for(int i = 0; i < n; i++){
        t = insert_ordered_tree(t, values[i]);
    }
    println_tree(t);
    println_inorder(t);

    BTNode* t2 = new_btnode(0, new_btnode(1, new_btnode(11, NULL, NULL), new_btnode(12, NULL, NULL)), new_btnode(2, NULL, new_btnode(7, NULL, NULL)));
    println_tree(t2);
    free_tree(t2);

    Node* list = get_interval(t, 29, 56);
    println_list(list);
    free_list(list);

    int bounds[] = { 29, 56 };
    list = filter_tree(t, in_interval, bounds, NULL);
    println_list(list);
    free_list(list);

    BTNode* t3 = new_btnode(10,
        new_btnode(11,
            new_btnode(20,
                new_btnode(21, NULL, NULL),
                new_btnode(21, NULL, NULL)),
            new_btnode(30,
                new_btnode(31, NULL, NULL),
                NULL)),
        new_btnode(20,
            new_btnode(40,
                new_btnode(50, NULL, NULL),
                NULL),
            new_btnode(30,
                NULL,
                new_btnode(100, NULL, NULL))));
    printbln(is_monotone(t3));
    test_equal_b(is_monotone(t3), true);
    free_tree(t3);

    BTNode* t4 = new_btnode(10,
        new_btnode(11,
            new_btnode(20,
                new_btnode(21, NULL, NULL),
                new_btnode(20, NULL, NULL)),
            new_btnode(30,
                new_btnode(31, NULL, NULL),
                NULL)),
        new_btnode(20,
            new_btnode(40,
                new_btnode(50, NULL, NULL),
                NULL),
            new_btnode(30,
                NULL,
                new_btnode(100, NULL, NULL))));
    printbln(is_monotone(t4));
    test_equal_b(is_monotone(t4), false);
    free_tree(t4);

    free_tree(t);

    return 0;
}
