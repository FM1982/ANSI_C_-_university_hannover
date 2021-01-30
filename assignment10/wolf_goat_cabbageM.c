/*
Compile: make wolf_goat_cabbage
Run: ./wolf_goat_cabbage
make wolf_goat_cabbage && ./wolf_goat_cabbage
*/

#include "base.h"
#include <stdio.h>

// Represents a single list node. The value is dynamically allocated. The node
// is the owner of the value and has to free it when itself is released.
struct Node {
    String value; // dynamically allocated string, release memory!
    struct Node* next; // self-reference
};
typedef struct Node Node;

// Create a list node. Copies the value (into dynamically allocated storage).
Node* new_node(String value, Node* next) {
    Node* node = xcalloc(1, sizeof(Node));
    node->value = s_copy(value); // s_copy performs dynamic allocation
    node->next = next;
    return node;
}

// Prints the components of the given list.
void print_list(Node* list) {
    if (list == NULL) {
        printf("[]");
    } else {
        printf("[%s", list->value);
        for (Node* n = list->next; n != NULL; n = n->next) {
            printf(" %s", n->value);
        }
        printf("]");
    }
}

// Print list followed by a newline.
void println_list(Node* list) {
    print_list(list);
    printsln("");
}

// Free all nodes of the list, including the values it contains.
void free_list(Node* list) {
    // todo: implement (Aufgabe 1)
    // (there will be memory leaks if this function is not yet implemented)
    Node* node_next = NULL;
    for(Node* node = list; node != NULL; node = node_next){
        node_next = node->next;
        free(node->value);
        free(node);
    }
}


bool test_equal_lists(int line, Node* list1, Node* list2);

/*
Example calls for test_equal_lists.
Expected output (line numbers may differ):
Line 63: The lists are equal.
Line 66: The lists are equal.
Line 70: The lists are equal.
Line 74: The values at node 0 differ: hello <-> you.
Line 78: The lists are equal.
Line 82: The values at node 1 differ: second <-> hello.
Line 86: list1 is shorter than list2.
Line 90: list1 is longer than list2.
*/
void test_equal_lists_test(void) {
    Node* list1 = NULL;
    Node* list2 = NULL;
    test_equal_lists(__LINE__, list1, list2);
    list1 = new_node("hello", NULL);
    list2 = list1;
    test_equal_lists(__LINE__, list1, list2);
    free_list(list1);
    list1 = new_node("hello", NULL);
    list2 = new_node("hello", NULL);
    test_equal_lists(__LINE__, list1, list2);
    free_list(list1); free_list(list2);
    list1 = new_node("hello", NULL);
    list2 = new_node("you", NULL);
    test_equal_lists(__LINE__, list1, list2);
    free_list(list1); free_list(list2);
    list1 = new_node("first", new_node("second", NULL));
    list2 = new_node("first", new_node("second", NULL));
    test_equal_lists(__LINE__, list1, list2);
    free_list(list1); free_list(list2);
    list1 = new_node("first", new_node("second", NULL));
    list2 = new_node("first", new_node("hello", NULL));
    test_equal_lists(__LINE__, list1, list2);
    free_list(list1); free_list(list2);
    list1 = new_node("first", new_node("second", NULL));
    list2 = new_node("first", new_node("second", new_node("third", NULL)));
    test_equal_lists(__LINE__, list1, list2);
    free_list(list1); free_list(list2);
    list1 = new_node("first", new_node("second", new_node("third", NULL)));
    list2 = new_node("first", new_node("second", NULL));
    test_equal_lists(__LINE__, list1, list2);
    free_list(list1); free_list(list2);
}

int length_list(Node* list);

// Example calls for length_list (below).
void length_list_test(void) {
    // todo: implement (Aufgabe 1)
    // todo: at least 3 checks, with test_equal_i(actual, expected);
    Node* my_List1 = new_node("hallo", NULL);
    Node* my_List2 = new_node("hallo", new_node("me", NULL));
    Node* my_List3 = new_node("hallo", new_node("bla", new_node("me", NULL)));
    Node* my_List4 = new_node("hallo", new_node("bli", new_node("bla", NULL)));
    Node* my_List5 = new_node("hallo", new_node("bli", new_node("bla", new_node("me", NULL))));
    Node* my_List6 = new_node("hallo", new_node("bli", new_node("bla", new_node("me", new_node("blub", NULL)))));
    test_equal_i(length_list(my_List1),1);
    test_equal_i(length_list(my_List2),2);
    test_equal_i(length_list(my_List3),3);
    test_equal_i(length_list(my_List4),3);
    test_equal_i(length_list(my_List5),4);
    test_equal_i(length_list(my_List6),5);
    free_list(my_List1);
    free_list(my_List2);
    free_list(my_List3);
    free_list(my_List4);
    free_list(my_List5);
    free_list(my_List6);
}

// Number of elements of the list.
int length_list(Node* list) {
    int n = 0;
    for (Node* node = list; node != NULL; node = node->next) n++;
    return n;
}

// Checking whether two string lists are equal.
bool test_equal_lists(int line, Node* list1, Node* list2) {
    // todo: implement (Aufgabe 1)
     if(list1 == NULL && list2 == NULL){
        printf("Line %d: The lists are equal.\n",line);
        return true;
    }
    if(length_list(list1) < length_list(list2)){
        printf("Line %d: list1 is shorter than list2.\n",line);
        return false;
    }
    if(length_list(list1) > length_list(list2)){
        printf("Line %d: list1 is longer than list2.\n",line);
        return false;
    }

    //iteration of lists
    for(Node* node1 = list1; node1 != NULL; node1 = node1->next){
        for(Node* node2 = list2; node2 != NULL; node2 = node2->next){
            if(length_list(node1) == length_list(node2) && (s_compare(node1->value,node2->value) == 0)){ // && (s_compare(node1->value,node2->value) == 0 && node1->next == node2->next) // && list1->next == list2->next
                if(node1->next == NULL && node2->next == NULL){
                    printf("Line %d: The lists are equal.\n",line);
                    return true;
                }
            }
            if(length_list(node1) == length_list(node2) && (s_compare(node1->value,node2->value) == -1)){ // && list1->next == list2->next
                printf("Line %d: The values at node 0 differ: %s <-> %s.\n", line,node1->value,node2->value);
                return false;
            }
            if(length_list(node1) == length_list(node2) && (s_compare(node1->value,node2->value) == 1)){ // && list1->next == list2->next
                printf("Line %d: The values at node 1 differ: %s <-> %s.\n", line,node1->value,node2->value);
                return false;
            }
            if((length_list(node1) == length_list(node2)) && (s_compare(node1->value,node2->value) == 1 && node1->next != node2->next)){ // && list1->next == list2->next
                printf("Line %d: The values at node 1 differ: %s <-> %s.\n", line,node1->value,node2->value);
                return false;
            }
        }
    }
    return false;
}

int index_list(Node* list, String s);

// Example calls for index_list (below).
void index_list_test(void) {
    // todo: implement (Aufgabe 1)
    // todo: at least 3 checks, with test_equal_i(actual, expected);
    Node* my_List = NULL;
    Node* my_List1 = new_node("hallo", NULL);
    Node* my_List2 = new_node("hallo", new_node("me", NULL));
    Node* my_List3 = new_node("hallo", new_node("bla", new_node("me", NULL)));
    Node* my_List4 = new_node("hallo", new_node("bli", new_node("bla", NULL)));
    Node* my_List5 = new_node("hallo", new_node("bli", new_node("bla", new_node("me", NULL))));
    Node* my_List6 = new_node("hallo", new_node("bli", new_node("bla", new_node("me", new_node("blub", NULL)))));
    test_equal_i(index_list(my_List,"me"),-1);
    test_equal_i(index_list(my_List1,"me"),-1);
    test_equal_i(index_list(my_List2,"hallo"),0);
    test_equal_i(index_list(my_List3,"me"),2);
    test_equal_i(index_list(my_List4,"bli"),1);
    test_equal_i(index_list(my_List5,"me"),3);
    test_equal_i(index_list(my_List6,"blub"),4);
    free_list(my_List);
    free_list(my_List1);
    free_list(my_List2);
    free_list(my_List3);
    free_list(my_List4);
    free_list(my_List5);
    free_list(my_List6);
}
int i = 0; //stacked value
int y = 0; //value defined for result of index_list -> without memory problems!
// Return index of s in list, or -1 if s is not in list.
int index_list(Node* list, String s) {
    // todo: implement (Aufgabe 1)
    if(list == NULL){
        i = 0;
        return -1;
    }
    else {
        if(s_compare(list->value,s) == EQ){ //list->value == s
            y = i; //stacked value needs to be deleted
            i = 0; //stacked value at 0 again!
            return y; //is a value that is somewhere in the memory and therefore not explicitly deletable in terms of C Memory Management!
        }
        else {
            i++;
            return index_list(list->next,s);
        }
    }
}

// Check whether list contains s.
bool contains_list(Node* list, String s) {
    return index_list(list, s) >= 0;
}

Node* remove_list(Node* list, int index);

// Example calls for remove_list (below).
void remove_list_test(void) {
    // todo: implement (Aufgabe 1)
    // todo: at least 3 checks, with test_equal_lists(__LINE__, actual, expected);
    Node* my_List = new_node("hallo", NULL);
    Node* my_List1 = new_node("hallo", new_node("me", NULL));
    Node* my_List2 = new_node("hallo", new_node("bla", new_node("me", NULL)));
    Node* my_List3 = new_node("hallo", new_node("bli", new_node("bla", NULL)));
    Node* my_List4 = new_node("hallo", new_node("bli", new_node("bla", new_node("me", NULL))));
    Node* my_List5 = new_node("hallo", new_node("bli", new_node("bla", new_node("me", new_node("blub", NULL)))));

    Node* removed_List = remove_list(my_List1,1);
    test_equal_lists(__LINE__,removed_List,my_List);
    free_list(removed_List);
    removed_List = remove_list(my_List2,1);
    test_equal_lists(__LINE__,my_List1,removed_List);
    free_list(removed_List);
    removed_List = remove_list(my_List5,3);
    test_equal_lists(__LINE__,removed_List,removed_List);
    free_list(removed_List);
    removed_List = remove_list(my_List4,2);
    test_equal_lists(__LINE__,my_List3,removed_List);
    free_list(removed_List);
    removed_List = remove_list(my_List5,3);
    test_equal_lists(__LINE__,my_List4,removed_List);
    free_list(removed_List);
    removed_List = remove_list(my_List,0);
    test_equal_lists(__LINE__,my_List1,removed_List);
    free_list(removed_List);
    Node* removed_List1 = remove_list(my_List3,2);
    Node* removed_List2 = remove_list(my_List4,1);
    test_equal_lists(__LINE__,removed_List1,removed_List2);
    free_list(removed_List1);
    free_list(removed_List2);

    free_list(my_List);
    free_list(my_List1);
    free_list(my_List2);
    free_list(my_List3);
    free_list(my_List4);
    free_list(my_List5);
}

Node* last_node(Node* list) {
    if (list->next == NULL) { // last element?
        return list;
    } else {
        return last_node(list->next); // recursive call
    }
}

Node* append_list(Node* list, String value) {
    if (list == NULL) { // empty list
        return new_node(value, NULL);
    } else { // non-empty list
        last_node(list)->next = new_node(value, NULL);
        return list;
    }
}

// Remove element at position index from list. The element at index has to be deleted.
Node* remove_list(Node* list, int index) {
    // todo: implement (Aufgabe 1)
    if(index < 0 || list == NULL) return list;

    if(index == 0 && (list->value != NULL && list->next == NULL)){ //
        list = NULL;
        return list;
    }
    int i = 0;

    if(index >= 0 && list->next != NULL){
        Node* finished_List = NULL;
        for(Node* node = list; node != NULL; node = node->next){
            if(i < index){ //&& (node != NULL && node->next != NULL)
                finished_List = append_list(finished_List, node->value);
            }
            if(i == index && node->next != NULL){
                for(Node* first = node->next; first != NULL; first = first->next) finished_List = append_list(finished_List,first->value);
                list = finished_List;
                return list;
            }
            if(i == index && node->next == NULL){
                list = finished_List;
                return list;
            }
            i++;
        }
        free_list(finished_List);
    }
    return list;
}

///////////////////////////////////////////////////////////////////////////

// The boat may either be at the left or right river bank.
// We don't care for the transition (boat crossing the river).
enum Position {
    LEFT, RIGHT
};

// The data that represents the state of the puzzle.
typedef struct {
    // List of objects on the left river bank.
    Node* left;

    // List of objects on the right river bank.
    Node* right;

    // List of objects in the boat. The boat has a capacity of one object only.
    Node* boat;

    // Current boat position.
    enum Position position;
} Puzzle;

// Initialize the state of the puzzle.
Puzzle make_puzzle(void) {
    Puzzle p = { new_node("Wolf", new_node("Ziege", new_node("Kohl", NULL))), NULL, NULL, LEFT };
    return p;
}
//int z = 0;
//bool left_done = false;
//bool boat_done = false;
//bool right_done = false;
// Print the current state of the puzzle.
void print_puzzle(Puzzle* p) {
    // todo: implement (Aufgabe 2)
    print_list(p->left);
    if(p->position == RIGHT) printf("     ");
    print_list(p->boat);
    if(p->position == LEFT) printf("     ");
    print_list(p->right);
    printf("\n");

    /*if(z == 0 && p->left != NULL && !left_done){
        printf("[");
        z++;
    }
    if(p->left == NULL && !left_done){
        printf("[]");
        left_done = true;
    }
    else{
        if(p->left != NULL){
            if(p->left->next != NULL){
                printf("%s ", p->left->value);
                p->left = p->left->next;
                return print_puzzle(p);
            }
            else{
                printf("%s]", p->left->value);
                p->left = p->left->next;
                z--;
                left_done = true;
                return print_puzzle(p);
            }
        }
    }
    if(z == 0 && p->boat != NULL && !boat_done){
        if(p->position == RIGHT) printf("     ");
        printf("[");
        z++;
    }
    if(p->boat == NULL && !boat_done){
        if(p->position == RIGHT) printf("     ");
        printf("[]");
        if(p->position == LEFT) printf("     ");
        boat_done = true;
    }
    else{
        if(p->boat != NULL){
            if(p->boat->next != NULL){
                printf("%s ", p->boat->value);
                p->boat = p->boat->next;
                return print_puzzle(p);
            }
            else{
                printf("%s]", p->boat->value);
                if(p->position == LEFT) printf("     ");
                p->boat = p->boat->next;
                z--;
                boat_done = true;
                return print_puzzle(p);
            }
        }
    }
    if(z == 0 && p->right != NULL && !right_done){
        printf("[");
        z++;
    }
    if(p->right == NULL && !right_done){
        printf("[]\n");
        right_done = true;
    }
    else{
        if(p->right != NULL){
            if(p->right->next != NULL){
                printf("%s ", p->right->value);
                p->right = p->right->next;
                return print_puzzle(p);
            }
            else{
                printf("%s]\n", p->right->value);
                p->right = p->right->next;
                z--;
                right_done = true;
                return print_puzzle(p);
            }
        }
    }
    if(left_done && boat_done && right_done){
        left_done = false;
        boat_done = false;
        right_done = false;
    }*/
    /*if(p->left == NULL){
        printf("]");
        if(p->position == RIGHT) printf("     ");
        printf("[");
        if(p->boat != NULL){
            for(; p != NULL; p->boat = p->boat->next){
                if(p->boat->next != NULL){
                    printf("%s ", p->boat->value);
                }
                else{
                    printf("%s", p->boat->value);
                }
                if(p->boat->next == NULL){
                    printf("]");
                    if(p->position == LEFT) printf("     ");
                    printf("[");
                    if(p->right != NULL){
                        for(; p != NULL; p->right = p->right->next){
                            if(p->right->next != NULL){
                                printf("%s ", p->right->value);
                            }
                            else{
                                printf("%s", p->right->value);
                            }
                            if(p->right->next == NULL){
                                printf("]\n");
                            }
                        }
                    }
                    else{
                        printf("]\n");
                    }
                }
            }
        }
        else{
            printf("]");
            if(p->position == LEFT) printf("     ");
            printf("[");
            if(p->right != NULL){
                for(; p != NULL; p->right = p->right->next){
                    if(p->right->next != NULL){
                        printf("%s ", p->right->value);
                    }
                    else{
                        printf("%s", p->right->value);
                    }
                    if(p->right->next == NULL){
                        printf("]\n");
                    }
                }
            }
            else{
                printf("]\n");
            }
        }
    }
    for(; p != NULL; p->left = p->left->next){
        if(p->left->next != NULL){
            printf("%s ", p->left->value);
        }
        else{
            printf("%s", p->left->value);
        }
        if(p->left->next == NULL){
            printf("]");
            if(p->position == RIGHT) printf("     ");
            printf("[");
            if(p->boat != NULL){
                for(; p != NULL; p->boat = p->boat->next){
                    if(p->boat->next != NULL){
                        printf("%s ", p->boat->value);
                    }
                    else{
                        printf("%s", p->boat->value);
                    }
                    if(p->boat->next == NULL){
                        printf("]");
                        if(p->position == LEFT) printf("     ");
                        printf("[");
                        if(p->right != NULL){
                            for(; p != NULL; p->right = p->right->next){
                                if(p->right->next != NULL){
                                    printf("%s ", p->right->value);
                                }
                                else{
                                    printf("%s", p->right->value);
                                }
                                if(p->right->next == NULL){
                                    printf("]\n");
                                }
                            }
                        }
                        else{
                            printf("]\n");
                        }
                    }
                }
            }
            else{
                printf("]");
                if(p->position == LEFT) printf("     ");
                printf("[");
                if(p->right != NULL){
                    for(; p != NULL; p->right = p->right->next){
                        if(p->right->next != NULL){
                            printf("%s ", p->right->value);
                        }
                        else{
                            printf("%s", p->right->value);
                        }
                        if(p->right->next == NULL){
                            printf("]\n");
                        }
                    }
                }
                else{
                    printf("]\n");
                }
            }
        }
    }*/
}

// Release memory and quit.
void finish_puzzle(Puzzle* p) {
    // todo: implement (Aufgabe 2)
    free_list(p->left);
    free_list(p->right);
    free_list(p->boat);
    exit(0);
}

void evaluate_puzzle(Puzzle* p) {
    // todo: implement (Aufgabe 2)
    if(length_list(p->right) == 3){
        print_puzzle(p);
        printf("Herzlichen Glueckwunsch! Das Minispiel ist erfolgreich beendet!");
        finish_puzzle(p);
    }
    else{
        if(length_list(p->left) == 2 && p->position == RIGHT){
            if(contains_list(p->left, "Wolf") && contains_list(p->left, "Ziege")){
                print_puzzle(p);
                printf("Kritische Situation! Wolf und Ziege sind am linken Ufer alleine!\n Wolf frisst Ziege!");
                finish_puzzle(p);
            }
            if(contains_list(p->left, "Ziege") && contains_list(p->left, "Kohl")){
                print_puzzle(p);
                printf("Kritische Situation! Ziege und Kohl sind am linken Ufer alleine!\n Ziege frisst Kohl!");
                finish_puzzle(p);
            }
        }
        if(length_list(p->right) == 2 && p->position == LEFT){
            if(contains_list(p->right, "Wolf") && contains_list(p->right, "Ziege")){
                print_puzzle(p);
                printf("Kritische Situation! Wolf und Ziege sind am rechten Ufer alleine!\n Wolf frisst Ziege!");
                finish_puzzle(p);
            }
            if(contains_list(p->right, "Ziege") && contains_list(p->right, "Kohl")){
                print_puzzle(p);
                printf("Kritische Situation! Ziege und Kohl sind am rechten Ufer alleine!\n Ziege frisst Kohl!");
                finish_puzzle(p);
            }
        }
        print_puzzle(p);
    }
}

void play_puzzle(Puzzle* p) {
    // todo: implement (Aufgabe 2)
    print_puzzle(p);
    String my_str = "";
    String temp_str = "";
    Node* temp_list = NULL;
    while(!s_equals(my_str, "q")){
        if(s_equals(my_str, "Wolf")){
            if(p->position == LEFT){
                if(contains_list(p->boat, my_str)){
                    temp_list = p->boat;
                    p->boat = remove_list(p->boat, index_list(p->boat, my_str));
                    free_list(temp_list);
                    p->left = append_list(p->left, my_str);
                    evaluate_puzzle(p);
                }else{
                    if(contains_list(p->left, my_str)){
                        temp_list = p->left;
                        p->left = remove_list(p->left, index_list(p->left, my_str));
                        free_list(temp_list);
                        p->boat = append_list(p->boat, my_str);
                        evaluate_puzzle(p);
                    }
                }
            }
            if(p->position == RIGHT){
                if(contains_list(p->right, my_str)){
                    temp_list = p->right;
                    p->right = remove_list(p->right, index_list(p->right, my_str));
                    free_list(temp_list);
                    p->boat = append_list(p->boat, my_str);
                    evaluate_puzzle(p);
                }
                else{
                    if(contains_list(p->boat, my_str)){
                        temp_list = p->boat;
                        p->boat = remove_list(p->boat, index_list(p->boat, my_str));
                        free_list(temp_list);
                        p->right = append_list(p->right, my_str);
                        evaluate_puzzle(p);
                    }
                }
            }
        }
        if(s_equals(my_str, "Ziege")){
            if(p->position == LEFT){
                if(contains_list(p->boat, my_str)){
                    temp_list = p->boat;
                    p->boat = remove_list(p->boat, index_list(p->boat, my_str));
                    free_list(temp_list);
                    p->left = append_list(p->left, my_str);
                    evaluate_puzzle(p);
                }
                else{
                    if(contains_list(p->left, my_str)){
                        temp_list = p->left;
                        p->left = remove_list(p->left, index_list(p->left, my_str));
                        free_list(temp_list);
                        p->boat = append_list(p->boat, my_str);
                        evaluate_puzzle(p);
                    }
                }
            }
            if(p->position == RIGHT){
                if(contains_list(p->right, my_str)){
                    temp_list = p->right;
                    p->right = remove_list(p->right, index_list(p->right, my_str));
                    free_list(temp_list);
                    p->boat = append_list(p->boat, my_str);
                    evaluate_puzzle(p);
                }
                else{
                    if(contains_list(p->boat, my_str)){
                        temp_list = p->boat;
                        p->boat = remove_list(p->boat, index_list(p->boat, my_str));
                        free_list(temp_list);
                        p->right = append_list(p->right, my_str);
                        if(length_list(p->left) == 0 && length_list(p->boat) == 0) free(my_str);
                        evaluate_puzzle(p);
                    }
                }
            }
        }
        if(s_equals(my_str, "Kohl")){
            if(p->position == LEFT){
                if(contains_list(p->boat, my_str)){
                    temp_list = p->boat;
                    p->boat = remove_list(p->boat, index_list(p->boat, my_str));
                    free_list(temp_list);
                    p->left = append_list(p->left, my_str);
                    evaluate_puzzle(p);
                }
                else{
                    if(contains_list(p->left, my_str)){
                        temp_list = p->left;
                        p->left = remove_list(p->left, index_list(p->left, my_str));
                        free_list(temp_list);
                        p->boat = append_list(p->boat, my_str);
                        evaluate_puzzle(p);
                    }
                }
            }
            if(p->position == RIGHT){
                if(contains_list(p->right, my_str)){
                    temp_list = p->right;
                    p->right = remove_list(p->right, index_list(p->right, my_str));
                    free_list(temp_list);
                    p->boat = append_list(p->boat, my_str);
                    evaluate_puzzle(p);
                }
                else{
                    if(contains_list(p->boat, my_str)){
                        temp_list = p->boat;
                        p->boat = remove_list(p->boat, index_list(p->boat, my_str));
                        free_list(temp_list);
                        p->right = append_list(p->right, my_str);
                        evaluate_puzzle(p);
                    }
                }
            }
        }
        if(s_equals(my_str, "l")){
            p->position = LEFT;
            if(contains_list(p->right, "Wolf") && contains_list(p->right, "Ziege")) free(my_str);
            if(contains_list(p->right, "Ziege") && contains_list(p->right, "Kohl")) free(my_str);
            evaluate_puzzle(p);
        }
        if(s_equals(my_str, "r")){
            p->position = RIGHT;
            if(contains_list(p->left, "Wolf") && contains_list(p->left, "Ziege")) free(my_str);
            if(contains_list(p->left, "Ziege") && contains_list(p->left, "Kohl")) free(my_str);
            evaluate_puzzle(p);
        }
        if(!s_equals(my_str, "")){
            temp_str = my_str;
            free(temp_str);
        }
        my_str = s_input(25);
        if(s_equals(my_str, "q")) free(my_str);
        if(s_equals(my_str, "q")) finish_puzzle(p);
    }
}

///////////////////////////////////////////////////////////////////////////

int main(void) {
    base_init();
    base_set_memory_check(true);

    test_equal_lists_test();
    length_list_test();
    index_list_test();
    remove_list_test();

    Puzzle p = make_puzzle();
    play_puzzle(&p);
    return 0;
}
