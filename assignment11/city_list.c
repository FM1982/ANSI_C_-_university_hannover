/*
Compile: make city_list
Run: ./city_list
make city_list && ./city_list
*/

#include "pointer_list.h"

// Data definition for a city.
typedef struct {
    String name;
    int inhabitants;
    double area; // km^2
} City;

// String, int, double -> City*
// Create a city (constructor).
City* new_city(String name, int inhabitants, double area) {
    City* c = xcalloc(1, sizeof(City));
    c->name = s_copy(name);
    c->inhabitants = inhabitants;
    c->area = area;
    return c;
}

// City* -> City*
// Create a copy of city.
void* copy_city(void* x) {
    // todo: implement (a)
    City* cc = (City*)x;
    return new_city(cc->name,cc->inhabitants,cc->area);
}

// City* -> void
// Releases memory of a city.
void free_city(void* x) {
    // todo: implement (a)
    City* fc = (City*)x;
    free(fc->name);
    free(fc);
}

// City* -> String
// String representation of city in the form:
// c has i inhabitants and an area of a km^2
String city_to_string(void* x) {
    if (x == NULL) return s_copy("(NULL)");
    City* c = (City*) x;
    int n = s_length(c->name) + 100;
    String s = xmalloc(n);
    snprintf(s, n, "%s has %d inhabitants and an area of %.2f km^2", c->name, c->inhabitants, c->area);
    return s;
}

// City* -> bool
// Returns true if number of inhabitants is below 100000.
bool small_city(void* element, int i, void* x) {
    // todo: implement (b)
    City* sc = (City*)element;
    int inh = 100000;
    if(sc->inhabitants < inh){
        return true;
    }
    else
    {
        return false;
    }
}

// City* -> bool
// Returns true if area is below *x.
bool area_less_than(void* element, int i, void* x) {
    // todo: explain each line (c)
    City* c = (City*)element; // Hier wird der allgemeine void* als ein City-Objekt festgelegt
    double* area = (double*)x; // Hier wird analog dasselbe mit dem allgemeinen void* x Wert getan und wird als double festgelegt
    return c->area < *area; // Ausgegeben werden soll dann die Fläche des übergebenen City-Objekts das kleine als der Wert gespeichert in *area ist.
}

// City* -> String
// Maps a city to its name.
void* city_name(void* element, int i, void* x) {
    // todo: implement (d)
    City* cn = (City*)element;
    if(cn->name == NULL) return "unknown";
    String s = cn->name;
    return s;
    //return "unknown";
}

// City*, int, double* -> City*
// Creates a new city with multiplied number of inhabitants.
void* multiply_inhabitants(void* element, int i, void* x) {
    // todo: implement (e)
    City* cmi = (City*)element;
    double* factor = (double*)x;
    cmi->inhabitants *= *factor;
    return copy_city(element);
    //return element;
}

// double*, City*, int -> void
// Adds city area to state.
void add_area(void* state, void* element, int index) {
    // todo: explain each line
    double* a = (double*)state; // Hier wird ein void* state als ein Double deklariert und festgelegt!
    City* c = (City*)element; // Hier wird analog ein void* element als ein City-Objekt festgelegt!
    *a = *a + c->area; // Hier wird dann die Fläche der City->areas zusammenaddiert und dann in *a gespeichert!
}

// City**, City*, int -> void
// Compares the number of inhabitants of *state and element
// and replaces *state by the larger of the two.
void larger_city(void* state, void* element, int index) {
    // todo: explain each line
    City** s = (City**) state; // Legt für den void* state ein City Pointer auf einen Pointer als City-Objekt
    City* e = (City*) element; // Legt für den void* element ebenfalls einen Pointer auf ein City-Objekt
    if (*s == NULL || e->inhabitants > (*s)->inhabitants) { // Diese Bedingung checkt ob der State entweder NULL ist oder die Einwohnerzahl von element > ist als die Einwohnerzahl vom state
        *s = e; // Falls dem so ist, s.o. wird e auf *s gesetzt!
    }
}

// City*, City* -> { -1, 0, 1 }
// Returns =0 if x and y are equal, <0 if x smaller than y, >0 otherwise.
int cmp_city_inhabitants(void* x, void* y) {
    // todo: implement (h)
    City* c1 = (City*)x;
    City* c2 = (City*)y;
    if(c1->inhabitants < c2->inhabitants) return -1;
    if(c1->inhabitants == c2->inhabitants) return 0;
    if(c1->inhabitants > c2->inhabitants) return 1;
    return 0;
}

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

int main(void) {
    base_init();
    base_set_memory_check(true);

    City* c1 = new_city("Berlin", 3520031, 891.68);
    City* c2 = new_city("Hannover", 532163, 204.14);
    City* c3 = new_city("Celle", 69748, 175.04);
    City* c4 = new_city("Laatzen", 40939, 34.06);

    Node* list = new_node(c1, new_node(c2, new_node(c3, new_node(c4, NULL))));
    println_list(list, city_to_string);

    // todo: (b) find first city with less than 100000 inhabitants,
    // use find_list, print result, if any
    printsln("first small city:");
    City* found_city_inh = find_list(list, small_city, NULL);
    Node* small_cities = new_node(found_city_inh,NULL);
    println_list(small_cities,city_to_string);
    free_list(small_cities,NULL);
    // City* found_city = find_list(list, small_city, NULL);
    // ...

    // todo: (c) find the first city with a given maximum area, use find_list
    // print result, if any
    printsln("first city with an area less than max_area:");
    double max_area = 300;
    City* found_city_area = find_list(list, area_less_than, &max_area);
    Node* area_cities = new_node(found_city_area,NULL);
    println_list(area_cities,city_to_string);
    free_list(area_cities,NULL);
    // found_city = find_list(list, ...);
    // ...

    // (d) map the list of cities to a list of city names
    printsln("city names:");
    Node* names = map_list(list, city_name, NULL);
    println_list(names, string_to_string);
    free_list(names, NULL);

    // (e) increase number of inhabitants by 15%
    // create a new list, do not modify original list elements, use map_list
    printsln("increased inhabitants:");
    double factor = 1.15;
    Node* list2 = map_list(list, multiply_inhabitants, &factor);
    println_list(list2, city_to_string);
    free_list(list2, free_city);

    // todo: (f) find all small cities, use filter_list
    printsln("small cities:");
    Node* selected_cities = filter_list(list, small_city, NULL);
    println_list(selected_cities, city_to_string);
    free_list(selected_cities, NULL);
    // Node* selected_cities = filter_list(list, ...;
    // ...
    // todo: (f) produce a list of the names of all small cities, use filter_map_list
    printsln("names of small cities:");
    Node* nosc = filter_map_list(list, small_city, city_name, NULL);
    println_list(nosc, string_to_string);
    free_list(nosc, NULL);
    // names = filter_map_list(list, ...);
    // ...

    // (g) compute the sum of the area of all cities, use reduce_list
    printsln("total area:");
    double total_area = 0;
    reduce_list(list, add_area, &total_area);
    printdln(total_area);

    // (g) find largest city (most inhabitants), use reduce_list
    City* largest_city = NULL;
    reduce_list(list, larger_city, &largest_city);
    if (largest_city != NULL) {
        String s = city_to_string(largest_city);
        printf("the largest city is: %s\n", s);
        free(s);
    }

    // (h) sort the cities by number of inhabitants, in increasing order
    // use insert_ordered, do not modify the original list, do not copy the cities
    Node* sorted_list = NULL;
    for (Node* n = list; n != NULL; n = n->next) {
        sorted_list = insert_ordered(sorted_list, n->value, cmp_city_inhabitants);
    }
    printsln("sorted cities:");
    if (sorted_list != NULL) {
        println_list(sorted_list, city_to_string);
        free_list(sorted_list, NULL);
    }

    // free all memory
    free_list(list, free_city);
    //getch();
    return 0;
}
