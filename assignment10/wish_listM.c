/*
Compile: make WishList
Run: ./WishList
Compile & run: make WishList && ./WishList
*/

#include "base.h"

#define WISH_COUNT 3
#define MAX_COUNT_OF_PRINTED_WISHES 4


// Nodes store the wish of a child in value and have a count. For a child a wish will always have a count of 1. But the structure is also used for the statistic. Therefor it stores a wish and it's frequency over all children.
typedef struct Node {
    char* value;
    int count;
    struct Node *next;
} Node;

// A list with a head structure, storing the name of the child and a pointer to the first node. The structure is also used for the statistic.
typedef struct WishList {
    Node *first;
    char *name;
} WishList;

// A list without a head structure. Used to store a wish list.
typedef struct Lnode{
    WishList* value;
    struct Lnode* next;
} Lnode;

//todo: a)
    /*
    Lnode enthält jeweils Wunschlisten. Jeder dieser Wunschlisten in Lnode selber wiederrum hat einen Pointer auf eine Wunschliste
    und enthält einen weiteren next Pointer zum nächsten Wunschlisten Element. Jede Wishlist selber hat einen Namen bspw. Anton und
    besitzt einen Pointer first auf die jeweilige Node, die die Wünsche aufgereiht enthält.
    Innerhalb der Node wird die Menge über count und der Name über value des Wunsches festgehalten und mit dem next Pointer zeigt der
    Wunsch auf den nächsten Wunsch der jeweiligen Wunschliste.
    */
Lnode* new_lnode(WishList* value, Lnode* next){
    Lnode* lnode = xcalloc(1, sizeof(Lnode));
    lnode->value = value;
    lnode->next = next;
    return lnode;
}


WishList* new_wish_list(char* name, Node* node) {
    WishList* list = xcalloc(1, sizeof(WishList));
    list->name = s_copy(name);
    list->first = node;
    return list;
}

Node* new_node(char* value, int count, Node* next) {
    Node* node = xcalloc(1, sizeof(Node));
    node->value = s_copy(value);
    node->count = count;
    node->next = next;
    return node;
}



void free_node(Node* node){
    //todo:
    if(node == NULL){
        return;
    }
    else{
        free(node->value);
        free_node(node->next);
    }
    free(node);
}

void free_wish_list(WishList* list){
    //todo:
    free_node(list->first);
	free(list->name);
	free(list);
}

void free_lnode(Lnode* lnode){
    //todo
    if(lnode == NULL){
        return;
    }
    else{
        free_wish_list(lnode->value);
        free_lnode(lnode->next);
    }
    free(lnode);
}


Node* contains(Node* n, char* value){
    //todo: rekursive
    if(n == NULL){
        return NULL;
    }
    else if(strcmp(n->value, value) == 0){
        return n;
    }
    else{
        return contains(n->next, value);
    }
    //return NULL;
}

void remove_node(WishList* list, Node* m){
    Node* x = list->first;
    if(x == m){
        //Remove first element.
        list->first = m->next;
    }else{
        //If m is not at the beginning of the list, find it and remove it.
        //Find predecessor of m.
        while(x != NULL && m != x->next){
            x = x->next;
        }
        x->next = m->next;
    }
}


void test_contains(){
    Node* a = NULL;

    test_equal_b(contains(a, "") == NULL, true);

    a = new_node("a", 1, NULL);

    test_equal_b(contains(a, "a") == a, true);
    test_equal_b(contains(a, "b") == NULL, true);

    Node* b = new_node("b", 1, a);
    Node* c = new_node("c ist toll.", 1, b);
    Node* d = new_node("d ist besser.", 1, c);
    Node* e = new_node("e ist am Besten.", 1, d);

    test_equal_b(contains(e, "F ist cool") == NULL, true);
    test_equal_b(contains(e, "e ist am Besten.") == e, true);
    test_equal_b(contains(e, "a") == a, true);
    test_equal_b(contains(e, "g") == NULL, true);

    free_node(e);
}

/*todo a)
    Stellt die Länge einer Wunschliste fest indem über alle Elemente iterativ durchgegangen wird und über einen length Wert bei jedem
    Durchlauf um 1 inkrementiert wird.
*/
int wish_list_length(WishList* list){
    if(list == NULL){
        return 0;
    }
    int length = 0;
    for(Node* n = list->first; n != NULL; n = n->next){
        length++;
    }
    return length;
}



// Skips the rest of the current line.
char* skip_line(char* s) {
    while (*s != '\n' && *s != '\0') s++;
    if (*s == '\n') s++;
    return s;
}


// Skips the current token.
char* skip_token(char* s) {
    while (*s != ',' && *s != '\n' && *s != '\0') s++;
    return s;
}

// Skips spaces.
char* skip_spaces_and_commas(char* s) {
    while (*s == ' ' || *s == ',') s++;
    return s;
}


// Create a new token from s (inclusive) to t (exclusive).
char* new_token(char* s, char* t) {
    char* token = xmalloc(t - s + 1);
    int i = 0;
    while (s < t) {
        token[i] = *s;
        i++;
        s++;
    }
    token[i]= '\0';
    return token;
}

// Returns a new token by first skipping spaces and commas and then reading the token.
// Sets *s to the first character after the token.
char* next_token(/*INOUT*/char** s) {
    *s = skip_spaces_and_commas(*s);
    char* t = skip_token(*s);
    char* token = new_token(*s, t);
    *s = t; // set *s to the character after the token
    return token;
}


/* todo a)
    Liest eine Wunschliste aus indem es sich ein Token erschafft, dieses bis zum Komma einließt und dann in Name speichert.
    Dann gilt das bis zum Zeilenumbruch oder dem Dateiende die Kommas und Leerzeichen für die Wünsche geskipped werden und
    daraufhin ein neues token bis zum nächsten Komma eingelesen wird.
*/
WishList* read_wish_list(char** s){
    char* name = next_token(s);
    Node* node_list = NULL;

    while(**s != '\0' && **s != '\n'){
        char* token = next_token(s);
        *s = skip_spaces_and_commas(*s);

        Node* node = new_node(token, 1, node_list);
        free(token);
        node_list = node;
    }
    WishList* list = new_wish_list(name, node_list);
    free(name);
    return list;
}

/*    todo a)
    Diese Funktion liest alle Wunschlisten einer Datei aus. Dabei gilt, das solange die Funktion read_wish_list aufgerufen wird,
    um dann in die nächste Zeile überzugehen. Dies geschieht solange bis nicht das Dateiende erreicht wurde.
*/
Lnode* read_wishes(char* filename){
    Lnode* list = NULL;
    char* file = s_read_file(filename);
    char* s = file;
    s = skip_line(s);
    while(*s != '\0'){
        Lnode* lnode = new_lnode(read_wish_list(&s), list);
        s = skip_line(s);
        list = lnode;

    }
    free(file);
    return list;
}

void print_wish_list(WishList* wishes, int max_wishes_to_print){
    if(wishes == NULL){
        return;
    }
    printf("%10s:\t", wishes->name);
    int i = 0;
    for(Node* n = wishes->first; n != NULL && (i < max_wishes_to_print || max_wishes_to_print < 0); n = n->next){
        printf("%dx %s", n->count, n->value);
        if(n->next){
            printf(", ");
        }
        i++;
        if(i == max_wishes_to_print && n->next != NULL){
            printf("...");
        }
    }
    printf("\n");
}

void print_wish_list_as_statistic(WishList* wishes){
    if(wishes == NULL){
        return;
    }
    printf("%s\n", wishes->name);
    for(Node* n = wishes->first; n != NULL; n = n->next){
        printf("%2dx %s\n", n->count, n->value);
    }
    printf("\n");
}

void print_lnodes(Lnode* lnode){
    for(; lnode != NULL; lnode= lnode->next){
        print_wish_list(lnode->value, MAX_COUNT_OF_PRINTED_WISHES);
    }
}

bool is_sorted(WishList* list){
    //todo: is sorted
    int an_arbitrary_nr = 1000000000;
    int i = an_arbitrary_nr;
    int j = i;
    for(Node* a_node = list->first; a_node != NULL; j = a_node->count, a_node = a_node->next){
        if(j < a_node->count){
            return false;
        }
    }
    return true;
}

void test_is_sorted(){
    WishList* w = new_wish_list("Test_list", NULL);

    test_equal_b(is_sorted(w), true);

    Node* a = new_node("a", 1, NULL);
    w->first = a;
    test_equal_b(is_sorted(w), true);


    Node* b = new_node("b", 1, a);
    Node* c = new_node("c ist toll.", 1, b);
    Node* d = new_node("d ist besser.", 1, c);
    Node* e = new_node("e ist am Besten.", 1, d);

    w->first = e;

    test_equal_b(is_sorted(w), true);
    e->count = 5;
    test_equal_b(is_sorted(w), true);
    a->count = 3;
    test_equal_b(is_sorted(w), false);
    b->count = 3;
    c->count = 4;
    d->count = 5;
    test_equal_b(is_sorted(w), true);
    free_wish_list(w);

}

/* todo a)
    Tauscht Node n mit Node m mithilfe zweier temporärer Variablen x und s. Dabei erhalten x und s jeweils die Werte für n
    und m überschreibt dann n während die vorhin gespeicherten Variablen x und s jeweils dann wiederrum m überschreiben.
*/
void swap(Node* n, Node* m){
    int x = n->count;
    char* s = n->value;

    n->count = m->count;
    n->value = m->value;

    m->count = x;
    m->value = s;
}

void sort(WishList* list){
    if(list == NULL){
        return;
    }
    while(!is_sorted(list)){
        for(Node* n = list->first;n != NULL; n= n->next){
            Node* m = n->next;
            if(m != NULL && n->count < m->count){
                swap(n, m);
            }
        }
    }
}

WishList* create_wish_statistics(Lnode* lnode){
    //todo
    WishList* stats = new_wish_list("Statistics", NULL);

    for(Lnode* my_lnode = lnode; my_lnode != NULL; my_lnode = my_lnode->next){
        //printf("%s, %s, %d\n", my_lnode->value->name, my_lnode->value->first->value, my_lnode->value->first->count);
        WishList* wish_list = my_lnode->value;
        for(Node* my_node = wish_list->first; my_node != NULL; my_node = my_node->next){
            //printf("%s, %d, %d\n", my_node->value, my_node->count, my_node->next);
            Node* st_node = contains(stats->first, my_node->value);
            if(st_node != NULL){
                st_node->count++;
            }
            else{
                stats->first = new_node(my_node->value, my_node->count, stats->first);
            }
        }
    }
    return stats;
}

void three_wishes_per_child(Lnode* lnode, WishList* stats){

    for(;lnode!= NULL; lnode = lnode->next){
        int length = wish_list_length(lnode->value);
        WishList* current = lnode->value;
        //printf("%d, %s, %s\n", current->first->next->next->count, current->first->next->next->value, current->name);
        /*for(WishList* my_st = stats; my_st != NULL; my_st->first = my_st->first->next){
            printf("%dx %s\n", my_st->first->count, my_st->first->value);
        }*/
        Node* nodes = stats->first;
        Node* my_curr_n = NULL;
        int nodes_count = 1;

        if(length < WISH_COUNT){
            //append wishes

            //todo:
            while(length < WISH_COUNT){
                while((my_curr_n = contains(current->first, nodes->value)) != NULL){
                    nodes = nodes->next;
				}
                current->first = new_node(nodes->value, nodes_count, current->first);
                ++length;
            }
            //end todo

        }else if(length > WISH_COUNT){
            //remove wishes
            //todo:
            while(length > WISH_COUNT){
                while((my_curr_n = contains(current->first, nodes->value)) == NULL){
                    nodes = nodes->next;
                }
                remove_node(current, my_curr_n);
                free(my_curr_n->value);
                free(my_curr_n);
                --length;
            }
            //end todo
        }else{
            //everything is fine
        }
    }
}

int main(void){
    base_init();
    base_set_memory_check(true);

    test_contains();
    test_is_sorted();

    Lnode* list_of_wishes = read_wishes("wishes.txt");

    WishList* stats = create_wish_statistics(list_of_wishes);
    //Prints the wish lists of the children. The number of maximum printed wishes is set at the beginning of the file.
    print_lnodes(list_of_wishes);

    //Sorting the stats.
    sort(stats);
    //And printing them.
    print_wish_list_as_statistic(stats);

    /*The Output of stats should look like the following:

        Statistics
        30x Spin Master Monster Jam - Grave Digger
        26x Lego Millenium Falcon
        26x Barbie und Ken Geschenkset mit Huendchen
        25x myToys Holzeisenbahn
        25x My Fairy Garden
        24x Hasbro Kroko Doc
        24x myToys-Collection Puppenwagen Trendy
        23x Play-Doh Verrueckte Haufen
        22x Schleich Mobile Tieraerztin
        22x Barbie Meerjungfrau
        22x Haarkreide
        21x myToys Puppenhaus mit Garten und Moebel
        21x Lego Das Disney Schloss
        21x Mattel Exklusiv Hot Wheels Doppel-Looping Wettrennen
        20x Pop up Pirate
        20x Tonies 30 Lieblings-Kinderlieder
        19x Piano Matte
        19x PLAYMOBIL Polizei-Einsatzwagen
        17x Nintendo Switch
        17x Kidisecrets

    */

    // Append or remove wishes from the lists of the children. Each child should have 3 wishes after the call.
    three_wishes_per_child(list_of_wishes, stats);
    // Prints the remaining three wishes.
    print_lnodes(list_of_wishes);

    /*The Output of list_of_wishes should look like the following:
             Anton:     1x Mattel Exklusiv Hot Wheels Doppel-Looping Wettrennen, 1x Kidisecrets, 1x myToys-Collection Puppenwagen Trendy
            Annika:     1x Nintendo Switch, 1x PLAYMOBIL Polizei-Einsatzwagen, 1x Piano Matte
         Alexander:     1x myToys Holzeisenbahn, 1x My Fairy Garden, 1x Hasbro Kroko Doc
           Susanne:     1x myToys-Collection Puppenwagen Trendy, 1x Kidisecrets, 1x Hasbro Kroko Doc
          Johannes:     1x Spin Master Monster Jam - Grave Digger, 1x Mattel Exklusiv Hot Wheels Doppel-Looping Wettrennen, 1x Kidisecrets
             Meike:     1x Piano Matte, 1x Nintendo Switch, 1x Tonies 30 Lieblings-Kinderlieder
              Paul:     1x Lego Millenium Falcon, 1x Spin Master Monster Jam - Grave Digger, 1x Schleich Mobile Tieraerztin
             Elena:     1x myToys Puppenhaus mit Garten und Moebel, 1x Barbie Meerjungfrau, 1x Pop up Pirate
           Quentin:     1x PLAYMOBIL Polizei-Einsatzwagen, 1x Nintendo Switch, 1x Kidisecrets
            Simone:     1x Lego Millenium Falcon, 1x Spin Master Monster Jam - Grave Digger, 1x Pop up Pirate
             Linus:     1x Piano Matte, 1x Spin Master Monster Jam - Grave Digger, 1x Pop up Pirate
          Berenike:     1x Tonies 30 Lieblings-Kinderlieder, 1x Kidisecrets, 1x PLAYMOBIL Polizei-Einsatzwagen
              Liam:     1x Piano Matte, 1x PLAYMOBIL Polizei-Einsatzwagen, 1x Nintendo Switch
             Flora:     1x Schleich Mobile Tieraerztin, 1x myToys-Collection Puppenwagen Trendy, 1x Haarkreide
            Quirin:     1x Kidisecrets, 1x Nintendo Switch, 1x PLAYMOBIL Polizei-Einsatzwagen
              Edda:     1x Lego Millenium Falcon, 1x Spin Master Monster Jam - Grave Digger, 1x Hasbro Kroko Doc
             Peter:     1x Lego Millenium Falcon, 1x Spin Master Monster Jam - Grave Digger, 1x myToys Puppenhaus mit Garten und Moebel
             Selma:     1x Tonies 30 Lieblings-Kinderlieder, 1x Kidisecrets, 1x PLAYMOBIL Polizei-Einsatzwagen
         Friedrich:     1x Piano Matte, 1x PLAYMOBIL Polizei-Einsatzwagen, 1x Tonies 30 Lieblings-Kinderlieder
              Maya:     1x Barbie und Ken Geschenkset mit Huendchen, 1x Schleich Mobile Tieraerztin, 1x Kidisecrets
              Karl:     1x Kidisecrets, 1x Piano Matte, 1x Nintendo Switch
               Mia:     1x Play-Doh Verrueckte Haufen, 1x Lego Das Disney Schloss, 1x Piano Matte
              Rosa:     1x Nintendo Switch, 1x PLAYMOBIL Polizei-Einsatzwagen, 1x Pop up Pirate
             Henry:     1x myToys Puppenhaus mit Garten und Moebel, 1x Pop up Pirate, 1x PLAYMOBIL Polizei-Einsatzwagen
         Elisabeth:     1x Piano Matte, 1x Pop up Pirate, 1x Barbie Meerjungfrau
        Maximilian:     1x Kidisecrets, 1x Pop up Pirate, 1x Tonies 30 Lieblings-Kinderlieder
           Paulina:     1x Tonies 30 Lieblings-Kinderlieder, 1x Lego Das Disney Schloss, 1x Nintendo Switch
            Julian:     1x Pop up Pirate, 1x PLAYMOBIL Polizei-Einsatzwagen, 1x Lego Das Disney Schloss
             Carla:     1x Pop up Pirate, 1x Piano Matte, 1x Kidisecrets
             Felix:     1x Tonies 30 Lieblings-Kinderlieder, 1x Kidisecrets, 1x PLAYMOBIL Polizei-Einsatzwagen
              Anna:     1x Pop up Pirate, 1x Tonies 30 Lieblings-Kinderlieder, 1x Barbie Meerjungfrau
              Finn:     1x Piano Matte, 1x Kidisecrets, 1x Tonies 30 Lieblings-Kinderlieder
             Julia:     1x myToys Puppenhaus mit Garten und Moebel, 1x Hasbro Kroko Doc, 1x Barbie und Ken Geschenkset mit Huendchen
              Paul:     1x Haarkreide, 1x Tonies 30 Lieblings-Kinderlieder, 1x Barbie Meerjungfrau
               Eva:     1x Spin Master Monster Jam - Grave Digger, 1x Lego Millenium Falcon, 1x My Fairy Garden
              Luis:     1x Tonies 30 Lieblings-Kinderlieder, 1x Lego Das Disney Schloss, 1x Mattel Exklusiv Hot Wheels Doppel-Looping Wettrennen
           Theresa:     1x Lego Das Disney Schloss, 1x Kidisecrets, 1x Piano Matte
              Noah:     1x My Fairy Garden, 1x Barbie Meerjungfrau, 1x Lego Millenium Falcon
              Juna:     1x PLAYMOBIL Polizei-Einsatzwagen, 1x Tonies 30 Lieblings-Kinderlieder, 1x Piano Matte
              Leon:     1x Lego Millenium Falcon, 1x Barbie Meerjungfrau, 1x Spin Master Monster Jam - Grave Digger
              Romy:     1x PLAYMOBIL Polizei-Einsatzwagen, 1x Barbie Meerjungfrau, 1x Schleich Mobile Tieraerztin
           Philipp:     1x Tonies 30 Lieblings-Kinderlieder, 1x Piano Matte, 1x PLAYMOBIL Polizei-Einsatzwagen
         Katharina:     1x Spin Master Monster Jam - Grave Digger, 1x myToys Puppenhaus mit Garten und Moebel, 1x Nintendo Switch
             Oskar:     1x Lego Millenium Falcon, 1x myToys-Collection Puppenwagen Trendy, 1x Schleich Mobile Tieraerztin
            Frieda:     1x Spin Master Monster Jam - Grave Digger, 1x Mattel Exklusiv Hot Wheels Doppel-Looping Wettrennen, 1x Lego Das Disney Schloss
             David:     1x Nintendo Switch, 1x PLAYMOBIL Polizei-Einsatzwagen, 1x Piano Matte
             Luise:     1x Kidisecrets, 1x Piano Matte, 1x PLAYMOBIL Polizei-Einsatzwagen
            Niklas:     1x Play-Doh Verrueckte Haufen, 1x Barbie Meerjungfrau, 1x myToys-Collection Puppenwagen Trendy
            Amelie:     1x Nintendo Switch, 1x myToys Puppenhaus mit Garten und Moebel, 1x Play-Doh Verrueckte Haufen
             Elias:     1x Tonies 30 Lieblings-Kinderlieder, 1x Lego Das Disney Schloss, 1x Pop up Pirate
             Finja:     1x Schleich Mobile Tieraerztin, 1x Nintendo Switch, 1x myToys Puppenhaus mit Garten und Moebel
             Jonas:     1x Pop up Pirate, 1x Piano Matte, 1x Mattel Exklusiv Hot Wheels Doppel-Looping Wettrennen
             Emely:     1x Tonies 30 Lieblings-Kinderlieder, 1x Mattel Exklusiv Hot Wheels Doppel-Looping Wettrennen, 1x Kidisecrets
               Ben:     1x Piano Matte, 1x PLAYMOBIL Polizei-Einsatzwagen, 1x Nintendo Switch
               Amy:     1x myToys Puppenhaus mit Garten und Moebel, 1x Nintendo Switch, 1x Haarkreide
        Konstantin:     1x Pop up Pirate, 1x PLAYMOBIL Polizei-Einsatzwagen, 1x Piano Matte
              Ella:     1x Tonies 30 Lieblings-Kinderlieder, 1x PLAYMOBIL Polizei-Einsatzwagen, 1x Nintendo Switch
             Lukas:     1x Mattel Exklusiv Hot Wheels Doppel-Looping Wettrennen, 1x Nintendo Switch, 1x Kidisecrets
              Lucy:     1x Spin Master Monster Jam - Grave Digger, 1x Play-Doh Verrueckte Haufen, 1x Lego Millenium Falcon
          Benjamin:     1x Nintendo Switch, 1x myToys Puppenhaus mit Garten und Moebel, 1x myToys Holzeisenbahn
    */

    //Create the stats over the new wish lists.
    WishList* stats2 = create_wish_statistics(list_of_wishes);
    //Sort them.
    sort(stats2);
    //And print them.
    print_wish_list_as_statistic(stats2);

    /*The Output of stats should look like the following:

        Statistics
        19x PLAYMOBIL Polizei-Einsatzwagen
        18x Piano Matte
        17x Nintendo Switch
        17x Kidisecrets
        16x Tonies 30 Lieblings-Kinderlieder
        13x Pop up Pirate
        11x Spin Master Monster Jam - Grave Digger
         9x myToys Puppenhaus mit Garten und Moebel
         9x Lego Millenium Falcon
         8x Barbie Meerjungfrau
         7x Lego Das Disney Schloss
         7x Mattel Exklusiv Hot Wheels Doppel-Looping Wettrennen
         6x Schleich Mobile Tieraerztin
         5x myToys-Collection Puppenwagen Trendy
         4x Play-Doh Verrueckte Haufen
         4x Hasbro Kroko Doc
         3x Haarkreide
         3x My Fairy Garden
         2x Barbie und Ken Geschenkset mit Huendchen
         2x myToys Holzeisenbahn
    */

    free_lnode(list_of_wishes);
    free_wish_list(stats);
    free_wish_list(stats2);

}

