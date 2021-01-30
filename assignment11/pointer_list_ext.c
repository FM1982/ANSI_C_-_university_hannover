/*
Compile: make pointer_list_ext
Run: ./pointer_list_ext
make pointer_list_ext && ./pointer_list_ext
*/

#include "pointer_list.h"

// String -> String
// Copies a string for printing (and later release).
String string_to_string(void* x) {
    return s_copy(x);
}

// String -> void
// Releases a string.
void free_string(void* x) {
    free(x);
}

// Create a list consisting of the first n nodes of list.
Node* take_list(Node* list, int n) {
    int i = 0;
    Node* finished_List = NULL;
    for(Node* node = list; node != NULL; node = node->next){
        if(i < n){
            finished_List = append_list(finished_List, node->value);
            list = finished_List;
        }
        i++;
    }
    return list; // todo; implement (a)
}

// Create a list consisting of nodes of list, except the first n.
Node* drop_list(Node* list, int n) {
    int i = 0;
    Node* finished_List = NULL;
    for(Node* node = list; node != NULL; node = node->next){
        if(i >= n){
            finished_List = append_list(finished_List, node->value);
            list = finished_List;
        }
        i++;
    }
    return list; // todo; implement (b)
}

// Take alternatingly from list1 and list2 until all data is collected in the result.
Node* interleave(Node* list1, Node* list2) {
    Node* finished_List1 = NULL;
    Node* finished_List2 = list2;
    Node* finished_List3 = NULL;

    int i = 0;
    for(Node* node1 = list1; node1 != NULL; node1 = node1->next){
        finished_List1 = append_list(finished_List1, node1->value);
        while(i < length_list(list2)){
            finished_List1 = append_list(finished_List1, finished_List2->value);
            i++;
            finished_List2 = finished_List2->next;
            break;
        }
        if(node1->next == NULL) finished_List3 = node1->next;
    }
    if(finished_List3 == NULL && finished_List2 != NULL){
        while(i < length_list(list2)){
            finished_List1 = append_list(finished_List1, finished_List2->value);
            i++;
            finished_List2 = finished_List2->next;
            break;
        }
    }

    list1 = finished_List1;
    return list1; // todo; implement (c)
}

// typedef bool (*EqualFun)(void* element1, void* element2);

bool group_by_length(void* element1, void* element2) {
    String s1 = element1;
    String s2 = element2;
    return s_length(s1) == s_length(s2);
}

// Group elements in list. Equivalent elements (for which equivalent is true) are put
// in the same group. The result is a list of groups. Each group is itself a list.
// Each group contains items that are equivalend.
Node* group_list(Node* list, EqualFun equivalent) {
    Node* finished_List = NULL;
    Node* temp_data = NULL;
    Node* temp_values = NULL;
    int solitary_values = 3;

    for(Node* node = list; node != NULL; node = node->next){
        temp_data = node->next;
        while(temp_data != NULL){
            //printf("%s", ((Node*) temp_data->value)->value);
            //exit(0);
            if(equivalent(node->value, temp_data->value)){
                if(temp_values == NULL){
                    temp_values = new_node(node->value, NULL);
                    temp_values = append_list(temp_values, temp_data->value);
                }
                else{
                    temp_values = append_list(temp_values, temp_data->value);
                }
                if(!contains_list(finished_List, temp_values, NULL)){
                    finished_List = append_list(finished_List, temp_values);
                }
                else{
                    continue;
                }
            }
            if(temp_data->next == NULL){
                if(!contains_list(finished_List, node->value, NULL) && s_length(node->value) >= solitary_values){
                    temp_values = new_node(node->value, NULL);
                    finished_List = append_list(finished_List, temp_values);
                }
            }
            temp_data = temp_data->next;
        }
        temp_values = NULL;
    }

    list = finished_List;

    return list; // todo; implement (d)
}

void free_group(void* x) {
    Node* list = x;
    free_list(list, NULL);
}

int main(void) {
    base_init();
    base_set_memory_check(true);

    Node* list = new_node("a", new_node("bb", new_node("ccc", new_node("dd", new_node("e", NULL)))));
    println_list(list, string_to_string);

    prints("take_list: ");
    Node* list2 = take_list(list, 3);
    println_list(list2, string_to_string);

    prints("drop_list: ");
    Node* list3 = drop_list(list, 3);
    println_list(list3, string_to_string);

    prints("interleave: ");
    Node* list4 = interleave(list2, list3);
    println_list(list4, string_to_string);

    Node* groups = group_list(list, group_by_length);
    printf("%d groups:\n", length_list(groups));
    for (Node* n = groups; n != NULL; n = n->next) {
        if (n->value != NULL) {
            println_list(n->value, string_to_string);
        }
    }

    free_list(list, NULL);
    free_list(list2, NULL);
    free_list(list3, NULL);
    free_list(list4, NULL);
    free_list(groups, free_group);

    return 0;
}
