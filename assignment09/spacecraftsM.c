/*
Compile: make spacecrafts
Run: ./spacecrafts
Compile & run: make spacecrafts && ./spacecrafts
*/

#include "base.h"

#define N 5

// struct of a spacecraft
typedef struct Spacecraft{
	char* name;
	int passengers;
	double reach;
	double load_capacity;
}Spacecraft;

// struct of the fleet.
typedef struct Fleet{
	Spacecraft** ships;
	int maximum_count; //initialize to N, size of ships
	int current_count; //current count of spacecrafts in ships
}Fleet;


// returns a pointer to a dynamically allocated ship
Spacecraft* new_spacecraft(int passengers, double reach, double load_capacity, char* name){
	Spacecraft *spc = xmalloc(sizeof(Spacecraft));
	spc->passengers = passengers;
	spc->reach = reach;
	spc->load_capacity = load_capacity;
	spc->name = s_copy(name);
	return spc;
}

// prints a spacecraft
void print_spacecraft(Spacecraft* spc){
	printf("%12s with %3d passengers, a reach of %8.1f au and a load capacity of %4.1f t\n", spc->name, spc->passengers, spc->reach, spc->load_capacity);
}

/* Aufgabe E
Wenn ein Raumschiff auf ein nicht existierenden Index entfernt wird
tritt ein memory segmentation fault auf, also einer Art outofbounds Exception
wie in Java. Darum ist die Abfrage auf Gültigkeit eines Indizes in diesem
Falle wichtig!
*/
void free_ships(Fleet* fls, int index){
    if(index >= fls->current_count || index < 0){
        printf("No ships at that position in Formation!\n");
        return;
    }
    free(fls->ships[index]->name);
    free(fls->ships[index]);

	int i = index;

	for(; i < fls->current_count - 1; i++)
	{
		fls->ships[i] = fls->ships[i + 1];
	}

	fls->ships[i] = NULL;
	fls->current_count--;
}

void free_fleet_ships(Fleet* fl){
    while(fl->current_count > 0) free_ships(fl, fl->current_count - 1);
    //}
    free(fl->ships);
//    free(fl);
}

void free_ships_names(char* c){
    if(c != NULL){
        free(c);
    }
}

Fleet* spacecraft_values(char* s, Fleet* fl, int ships){
    int j = 0, i = 0, passengers = 0, n = 3;
    double reach = 0.0, load_capacity = 0.0;

    char* name;
    char* s2;
    char* token;
    String* pn;

    while (*s != '\n') s++;
    s++;

    Spacecraft* spct = NULL;

    while(*s != '\0'){
		if(*s == '\0')
			break;
        if(j == 0){
            s2 = s;
            while (*s != ' ' && *s != '\n') s++;

            token = xmalloc(s - s2 + 1);

            i = 0;
            while (s2 < s){
                token[i] = *s2;
                i++;
                s2++;
            }
            token[i]= '\0';
            pn = &token;
            //printf("%s, %d", *pn, pn);
            //break;
            name = *pn;
            j++;
            //free(token);
        }
        if(j > 0){
            while(*s == ' ') s++;

            s2 = s;
            while (*s != ' ' && *s != '\n') s++;

            token = xmalloc(s - s2 + 1);
            i = 0;
            while (s2 < s){
                token[i] = *s2;
                i++;
                s2++;
            }
            token[i]= '\0';

            if(j == 3){
                load_capacity = d_of_s(token);
                free_ships_names(token);
                j++;
            }
            if(j == 2){
                reach = d_of_s(token);
                free_ships_names(token);
                j++;
            }
            if(j == 1){
                passengers = i_of_s(token);
                free_ships_names(token);
                j++;
            }
            if(j == 4){
                spct = new_spacecraft(passengers, reach, load_capacity, name);
                fl->ships[n-ships] = spct;
                ships--;
                j = 0;
                s++;
                free_ships_names(name);
            }
        }
    }
    return fl;
}

char* spacecraft_buffered_values(char** s){
    int i = 0;
    char* s2 = *s;
    char* token;

    while (**s != ' ' && **s != '\n') (*s)++;

    token = xmalloc((*s) - s2 + 1);

    i = 0;
    while (s2 < (*s)){
        token[i] = *s2;
        i++;
        s2++;
    }
    token[i]= '\0';

    return token;
}

int spacecraft_buffered_int_values(char** s){
    char* token;
    int int_token;

	token = spacecraft_buffered_values(s);

	int_token = i_of_s(token);

	free(token);

	return int_token;
}

double spacecraft_buffered_double_values(char** s){
	char* token;
	double double_token;

	token = spacecraft_buffered_values(s);

	double_token = d_of_s(token);

	free(token);

	return double_token;
}

Fleet* make_fleet(int curr_count, int max_count){
    Fleet *fleet = malloc(sizeof(Fleet));
	fleet->current_count = curr_count;
	fleet->maximum_count = max_count;
	fleet->ships = xcalloc(max_count, sizeof(Spacecraft));
	return fleet;
}

// imports spacecrafts from file.
Fleet* read_spacecrafts(char* file_name){
	char* rfile = s_read_file(file_name);

	char* s = rfile;

	Fleet* fleet;
	char* start = s;

    int ships = -1;
	while (*start != '\0'){
		if(*start == '\n')
			ships++;
		start++;
	}
	//free_ships_names(start);
	/*Fleet *fleet = malloc(sizeof(Fleet));
	fleet->current_count = ships;
	fleet->maximum_count = N;
	fleet->ships = xcalloc(N, sizeof(Spacecraft));*/

    fleet = make_fleet(ships, N);

    fleet = spacecraft_values(s, fleet, ships);

    free(rfile);

    return fleet;

	//Fleet* my_fleet = new_fleet(*Spacecraft, N, ships);

	/*while(*s != '\0'){
    //printf("%s", s);
    //break;
	Spacecraft *spc = NULL; //creates a new Spacecraft with a pointer pointing at null!

		//skip until line end
		while (*s != '\n') s++;

		s++;

		if(*s == '\0') //if String s ends at String termination '\0' then break!
			break;

		char* s2 = s;
		//printf("%s, %s", s, s2);
		while (*s != ' ' && *s != '\n') s++;
        //printf("%s, %s", s, s2);
        //break;
		char* token = xmalloc(s - s2 + 1);
		int i = 0;
		while (s2 < s){
            token[i] = *s2;
			i++;
			s2++;
		}
		token[i]= '\0';
        //printf("%s", token);
        //break;
		char* name = token;
		//free(token);

		while(*s == ' ') s++;

		s2 = s;
		while (*s != ' ' && *s != '\n') s++;

		token = xmalloc(s - s2 + 1);
		i = 0;
		while (s2 < s){
			token[i] = *s2;
			i++;
			s2++;
		}
		token[i]= '\0';
        //printf("%s", token);
        //break;
		int passengers = i_of_s(token);
		free(token);

		while(*s == ' ') s++;
		s2 = s;
		while (*s != ' ' && *s != '\n') s++;

		token = xmalloc(s - s2 + 1);
		i = 0;
		while (s2 < s){
			token[i] = *s2;
			i++;
			s2++;
		}
		token[i]= '\0';

		double reach = d_of_s(token);
		free(token);

		while(*s == ' ') s++;
		s2 = s;
		while (*s != ' ' && *s != '\n') s++;

		token = xmalloc(s - s2 + 1);
		i = 0;
		while (s2 < s){
			token[i] = *s2;
			i++;
			s2++;

		}
		token[i]= '\0';

		double load_capacity = d_of_s(token);
        free(token);
        //printf("%s", s);
        //break;
		spc = new_spacecraft(passengers, reach, load_capacity, name);
		//print_spacecraft(spc);

		fleet->ships[ships-1] = spc;
		ships--;
        //printf("%d\n", fleet->current_count);
	}*/
    //return fleet;
}

// prints the fleet.
void print_spacecrafts(Fleet* f){
	for(int i = 0; i< f->maximum_count; i++){
		if(f->ships[i]){
			printf("%2d\t", i);
			Spacecraft* spc = f->ships[i];
			printf("%12s with %3d passengers, a reach of %8.1f au and a load capacity of %4.1f t\n", spc->name, spc->passengers, spc->reach, spc->load_capacity);

		}
	}
}

// Entry point with command line arguments.
int main(int argc, String argv[]) {
	base_init();
    base_set_memory_check(true);

	Fleet* fleet = NULL;

	if(argc > 1){
		fleet = read_spacecrafts(argv[1]);
	}else{
		fleet = read_spacecrafts("spacecrafts.txt");
	}

	char buffer[256];
	for(int i = 0; i< 256; i++){
		buffer[i] = '\0';
	}

	int c = '\0';
	printf("Your fleet: \n");
    print_spacecrafts(fleet);

	while((c = getchar()) != 'p'){
        if (c == 'q'){
            free_fleet_ships(fleet);
            //for (int i = 0; i < fleet->current_count; i++){
                //free_ships_names(fleet->ships[i]->name);
                //free_ships_values(fleet->ships[i].load_capacity);
                //free_ships(fleet->ships[i]);
            //}
            //printf("%s, %s, %s, %d\n", fleet->ships[0]->name, fleet->ships[1]->name, fleet->ships[2]->name, fleet->current_count);
            exit(1);
        }
		if (c == 's'){
			//send out a ship, remove it from the fleet
			//example: s1
			//removes ship of index 1
            /* Aufgabe C
			Im ganzen ist es nicht gut gelöst, da beim entfernen eines Schiffs,
			im Array der Index auf Null gesetzt wird und die Anzahl an Schiffen
			durch ships-- um 1 reduziert wird. Dadurch entstehen Lücken im Array
			und der Speicher selbst wird nicht mehr freigegeben. Die Anzahl bestimmt
			leider auch nicht den letzten Index eines Schiffes.
			*/

			int index = getchar() - '0';
			free_ships(fleet, index);
			/*if(fleet->ships[index] == NULL){
                printf("No ship at position %s!\n", fleet->ships[index]);
			}
			else{
                fleet->ships[index] = NULL;
                fleet->current_count--;
			}
			//printf("%s, %s, %s, %d\n", fleet->ships[0]->name, fleet->ships[1], fleet->ships[2]->name, fleet->current_count);
			//printf("%d\n", --fleet->current_count);
			for(int i = 0; i < fleet->current_count + 1; i++){
                if(fleet->ships[i] == NULL){
                    fleet->ships[i] = fleet->ships[i+1];
                    fleet->ships[i+1] = NULL;
                }
			}*/
		}else if (c == 'n'){
			//change name of ship
			//example: n1 Enterprise
			//renames ship at index 1 to Enterprise
			int index = getchar() - '0';
			getchar();
			int i = 0;
			while ((c = getchar()) != '\n'){
				buffer[i] = c;
				i++;
			}
			buffer[i] = '\0';

            free(fleet->ships[index]->name);
			fleet->ships[index]->name = s_copy(buffer);
            //free_fleet_ships(fleet);
            /*for (int i = 0; i < fleet->current_count; i++){
                if(buffer[i] != '\0'){
                    free_ships_names(fleet->ships[i]->name);
                    free_ships(fleet->ships[i]);
                }
            }*/
                //printf("%s, %s, %s, %d\n", fleet->ships[0]->name, fleet->ships[1]->name, fleet->ships[2]->name, fleet->current_count);
		}else if (c == 'a'){
			//add ship
			//example: a Amagedon 34 500.3 2000.0
			getchar(); // char f =
            int i = 0;
            while ((c = getchar()) != '\n'){
                buffer[i] = c;
                i++;
            }
            buffer[i] = '\0';

            char* bp = buffer;

            char* name = spacecraft_buffered_values(&bp);
            bp++;

            int passengers = spacecraft_buffered_int_values(&bp);
            bp++;

            double reach = spacecraft_buffered_double_values(&bp);
            bp++;

            double load_capacity = spacecraft_buffered_double_values(&bp);
            bp++;

            /*char* name = NULL;
            i = 0;
            for(; i< s_length(buffer); i++){
                if(buffer[i] == ' '){
                    break;
                }
            }

            name = s_sub(buffer, 0, i);
            i++;
            int j = i;
            printf("Char: '%c'\n", buffer[j]);
            for(; j< s_length(buffer); j++){
                if(buffer[j] == ' '){
                    break;
                }
            }
            printf("String: %s\n", s_sub(buffer, i, j));

            int passengers = i_of_s(s_sub(buffer, i, j));
            i = j++;
            for(; j< s_length(buffer); j++){
                if(buffer[j] == ' '){
                    break;
                }
            }

            double reach = d_of_s(s_sub(buffer, i, j));
            i = j++;
            for(; j < s_length(buffer); j++){
                if(buffer[j] == ' '){
                    break;
                }
            }

            double load_capacity =  d_of_s(s_sub(buffer, i, j));*/

            //printf("(%d, %d)\n", fleet->current_count, fleet->maximum_count);
            if(fleet->current_count >= fleet->maximum_count){
                printf("Current fleet amount %d exceeds max allowed fleet count of %d\n", fleet->current_count, fleet->maximum_count);
                free(name);
                //fleet->current_count--;
                //printf("(%d, %d)\n", fleet->current_count, fleet->maximum_count);
			}
			else{
                Spacecraft* spc = new_spacecraft(passengers, reach, load_capacity, name);
                free(name);
                fleet->ships[fleet->current_count] = spc;
                fleet->current_count++;
			}
			//free_ships_names(name);
			//free(name);
		}
		if(c == '\n'){
			printf("Your fleet: \n");
			print_spacecrafts(fleet);
		}
	}
	free_fleet_ships(fleet);
    return 0;
}
