/*
Compile: make memory_game
Run: ./memory_game 2 3
Compile & run: make memory_game && ./memory_game 2 3
*/

#include "base.h"
#include "clrscr.h"
#include <stdio.h>

#ifdef _WIN32
	#define WIN_TESTS true
	#define LINUX_TESTS false
#elif __linux__
	#define LINUX_TESTS true
	#define WIN_TESTS false
#else
	#define WIN_TESTS false
	#define LINUX_TESTS false
#endif

// Represents the state of the memory game.
typedef struct {
    char *cards; // array of cards, each card is one character, row-wise
    int ncards; // number of cards in array
    int rows; // number of rows of the board
    int cols; // number of columns of the board
    int points; // number of points the player has earned
    int turns; // number of card turns the player has made
} Board;

// Shuffles the array.
void shuffle(char *a, int n) {
    // a) todo: explain
    for (int i = n - 1; i > 0; i--) {
        int r = rand() % (i + 1); // random number in interval [0,i]
        char c = a[r];
        a[r] = a[i];
        a[i] = c;
    }
}

// Initializes the board with shuffled cards. Empty places are represented as ' '.
// Open places are represented as the respective character, e.g., 'A'.
// Hidden places are represented as negative characters, e.g., -'A'.
// The cards are initially hidden (negative).
// Only initializes the elements of the cards array. Assumes that cards points to
// an existing array and that ncards, rows, cols, points, and turns are already set.
void init_cards(Board *b) {
    // b) todo: implement
    // access to board elements: b->ncards, b->cards[i], b->rows, b->cols
    int upper_case_letters_start = 65;
    int upper_case_letters_end = 90;
    bool randomizer = false;
    int j = b->rows * b->cols, k = 0;
    for(int i = 0; i < j; i++){
        if(randomizer){
            if(i < (j / 2)){
                b->cards[i] = -((rand() % (upper_case_letters_end + 1 - upper_case_letters_start)) + upper_case_letters_start);
            }
            else{
                b->cards[i] = b->cards[i - (j / 2)];
            }
        }
        else{
            k++;
            if(k > 2){
                upper_case_letters_start++;
                k = 0;
                i--;
            }
            else{
                b->cards[i] = -upper_case_letters_start;
            }
        }
    }
    shuffle(b->cards, b->ncards);
}

// Prints the board. Hidden cards are shown as '#'. The following shows an output example:
/*
  1 2 3 4           <-- four columns
1   # #             <-- row 1: 1st and 4th card taken, 2nd and 3rd card hidden
2 # D # #           <-- row 2: 2nd card open
3 # # A #           <-- row 3: 3rd card open
1 points, 2 turns   <-- the player got 1 point in 2 turns
*/
// The row and column numbers are printed to facilitate input.
void print_board(Board *b) {
    // c) todo: implement
    // access to board elements: b->ncards, b->cards[i], b->rows, b->cols
    int j = 0, k = 1, m = 1, r = 0;
    for(int l = 0; l < b->cols; l++){
        if(l == 0) printf("  ");
        printf("%d ", m++);
        if(l == b->cols-1) printf("\n");
    }
    for(int i = 0; b->cards[i] != '\0'; i++, j++){
        if(j == b->cols - 1){
            if(b->cards[i] < 0){
                printf("%c \n", '#'); //b->cards[i]);
                j = -1;
                r++;
            }
            if(b->cards[i] > 0){
                printf("%c \n", b->cards[i]); //b->cards[i]);
                j = -1;
                r++;
            }
        }
        else{
            if(i >= b->rows*b->cols){ //b->cards[i] < 65 || b->cards[i] > 90
                continue;
            }
            else{
                if(j == 0 && r != b->rows){
                    printf("%d ", k);
                    k++;
                }
                if(i == b->cols * b->rows){
                    continue;
                }
                else{
                    //printf("%c ", '#'); //b->cards[i]);
                    if(b->cards[i] < 0){
                        printf("%c ", '#'); //b->cards[i]);
                    }
                    if(b->cards[i] > 0){
                        printf("%c ", b->cards[i]); //b->cards[i]);
                    }
                }
            }
        }
    }
    printf("%d points, %d turns \n", b->points, b->turns);
}

// Returns the array index of row r, column c. Stops the program if r or c are not valid.
int array_index(Board *b, int r, int c) {
    // d) todo: implement
    // access to board elements: b->rows, b->cols
    if((r > b->rows || r < 0) && (c > b->cols || c < 0)) exit(1);
    for(int i = 0; i <= r; i++){
        for(int j = 0; j <= c; j++){
            if(r == 0 && c == 0) return 0;
            if(r == b->rows - 1 && c == b->cols - 1) return b->rows * b->cols - 1;
            if(r >= 0 && c >= 0){
                if(r == 0 && c == j){
                    return j;
                }
                if(r > 0 && c >= 0){
                    if(r == i && c == j) return i * b->rows + i + j;
                }
            }
        }
    }
    return 0;
}

// Gets value at row r, column c. Stops the program if r or c are not valid.
char get(Board *b, int r, int c) {
    // e) todo: implement
    if((r >= b->rows || r < 0) && (c >= b->cols || c < 0)) exit(1);
    int j = 0;
    for(int i = 0; b->cards[i] != '\0'; i++){
        if(array_index(b, r, c) == i){
            j = b->cards[i];
            return j;
        }
    }
    return '#';
}

// Sets value at row r, column c to x. Stops the program if r or c are not valid.
void set(Board *b, int r, int c, char x) {
    // e) todo: implement
    if((r >= b->rows || r < 0) && (c >= b->cols || c < 0)) exit(1);
    for(int i = 0; b->cards[i] != '\0'; i++){
        if(array_index(b, r, c) == i){
            b->cards[i] = x;
        }
    }
}

// Turns over card in row r, column c. Stops the program if r or c are not valid.
void turn(Board *b, int r, int c) {
    // e) todo: implement
    if((r >= b->rows || r < 0) && (c >= b->cols || c < 0)) exit(1);
    for(int i = 0; b->cards[i] != '\0'; i++){
        if(array_index(b, r, c) == i){
            b->cards[i] = -(b->cards[i]);
        }
    }
}

// Prints a prompt to wait and wait for return key.
void prompt(void) {
    printf("press <return> to continue\n");
    char line[8];
    get_line(line, 8);
}

// Gets user input of the form <row-digit><column-digit> to let the user specify
// the row and column of a card. Example: Input 13 specifies row 0, column 2.
// Because the function returns three values, row and col are pointers to int
// variables to be set by the function. The return value indicates whether the
// position is valid (true) or not (false), given the current board state.
bool read_coords(/*IN*/Board *b, /*OUT*/int *row, /*OUT*/int *col) {
    char line[8];
    get_line(line, 8); // read input from terminal into line array
    int r = line[0] - '1'; // input '1' corresponds to row 0, '2' --> 1, etc.
    int c = line[1] - '1';
    if (r < 0 || r >= b->rows || c < 0 || c >= b->cols || get(b, r, c) == ' ') {
        return false; // position not valid
    }
    *row = r;
    *col = c;
    return true; // position valid
}

// Restricts x to the interval [low, high].
int clamp(int x, int low, int high) {
    // f) todo: implement
    if(x >= low && x <= high){
        return x;
    }
    else{
        if(x < low) return low;
        if(x > high) return high;
    }
    return x;
}

// Does a single move. It consists of turning over two cards. If they are equal,
// they get removed from the board and a point for the collected pair is given
// to the player. Otherwise, they are turned over again (backside up).
// The input format is: 12<return> to open a card in row 0, column 1.
void do_move(Board *b) { // g) todo: explain
    int r1, c1;
    while (!read_coords(b, &r1, &c1)) {
        printf("Illegal move.\n");
    }
    turn(b, r1, c1);
    b->turns++;
    clear_screen();
    print_board(b);

    int r2, c2;
    while (!read_coords(b, &r2, &c2) || (r1 == r2 && c1 == c2)) {
        printf("Illegal move.\n");
    }
    turn(b, r2, c2);
    b->turns++;
    clear_screen();
    print_board(b);

    prompt();
    char card1 = get(b, r1, c1);
    char card2 = get(b, r2, c2);
    assert(card1 > 0 && card2 > 0 && card1 != ' ');
    if (card1 == card2) {
        b->points++;
        set(b, r1, c1, ' ');
        set(b, r2, c2, ' ');
    } else {
        turn(b, r1, c1);
        turn(b, r2, c2);
    }
    clear_screen();
    print_board(b);
}

// Tests.
void tests(void) {
    test_equal_i(clamp(1, 2, 4), 2);
    test_equal_i(clamp(2, 2, 4), 2);
    test_equal_i(clamp(3, 2, 4), 3);
    test_equal_i(clamp(4, 2, 4), 4);
    test_equal_i(clamp(5, 2, 4), 4);

    // test with a 3x4 board (3 rows, 4 columns)
    char a[3*4];
    Board b = { a, 12, 3, 4, 10, 20 };
    srand(123); // initialize random number generator to fixed seed to always get the same test numbers
    init_cards(&b);

    print_board(&b); // ensure that output is equal to testsout1_want.txt

    test_equal_i(array_index(&b, 0, 0), 0);
    test_equal_i(array_index(&b, 0, 1), 1);
    test_equal_i(array_index(&b, 0, 2), 2);
    test_equal_i(array_index(&b, 1, 0), 4);
    test_equal_i(array_index(&b, 1, 1), 5);
    test_equal_i(array_index(&b, 2, 0), 8);
    test_equal_i(array_index(&b, 2, 1), 9);

    if(WIN_TESTS){
		test_equal_i(get(&b, 0, 0), -67);
		test_equal_i(get(&b, 0, 1), -70);
		test_equal_i(get(&b, 0, 2), -66);
		test_equal_i(get(&b, 1, 0), -68);
		test_equal_i(get(&b, 1, 1), -69);
		test_equal_i(get(&b, 2, 0), -65);
		test_equal_i(get(&b, 2, 1), -67);
	}else if(LINUX_TESTS){
		test_equal_i(get(&b, 0, 0), -67);
		test_equal_i(get(&b, 0, 1), -68);
		test_equal_i(get(&b, 0, 2), -65);
		test_equal_i(get(&b, 1, 0), -66);
		test_equal_i(get(&b, 1, 1), -70);
		test_equal_i(get(&b, 2, 0), -69);
		test_equal_i(get(&b, 2, 1), -66);
	}else{
	    test_equal_i(get(&b, 0, 0), -66);
		test_equal_i(get(&b, 0, 1), -68);
		test_equal_i(get(&b, 0, 2), -67);
		test_equal_i(get(&b, 1, 0), -66);
		test_equal_i(get(&b, 1, 1), -70);
		test_equal_i(get(&b, 2, 0), -65);
		test_equal_i(get(&b, 2, 1), -67);
	}

    turn(&b, 0, 0);
    turn(&b, 0, 2);
    turn(&b, 1, 0);
    turn(&b, 2, 1);

    if(WIN_TESTS){
		test_equal_i(get(&b, 0, 0), 67);
		test_equal_i(get(&b, 0, 2), 66);
		test_equal_i(get(&b, 1, 0), 68);
		test_equal_i(get(&b, 2, 1), 67);
	}else if(LINUX_TESTS){
		test_equal_i(get(&b, 0, 0), 67);
		test_equal_i(get(&b, 0, 2), 65);
		test_equal_i(get(&b, 1, 0), 66);
		test_equal_i(get(&b, 2, 1), 66);
	}else{
		test_equal_i(get(&b, 0, 0), 66);
		test_equal_i(get(&b, 0, 2), 67);
		test_equal_i(get(&b, 1, 0), 66);
		test_equal_i(get(&b, 2, 1), 67);
	}

    print_board(&b); // ensure that output is equal to testsout2_want.txt

    set(&b, 0, 0, '1');
    set(&b, 0, 2, '2');
    set(&b, 1, 0, '3');
    set(&b, 2, 1, '4');

    test_equal_i(get(&b, 0, 0), '1');
    test_equal_i(get(&b, 0, 2), '2');
    test_equal_i(get(&b, 1, 0), '3');
    test_equal_i(get(&b, 2, 1), '4');

    print_board(&b); // ensure that output is equal to testsout3_want.txt

    srand(time(NULL) << 10);
}

// Entry point with command line arguments.
int main(int argc, String argv[]) {
    if (argc != 3) {
        printf("Usage: memory_game <rows> <cols>\n");
        printf("Example: memory_game 2 3\n");
        exit(1);
    }

    tests();
    prompt();

    Board b;
    b.rows = clamp(atoi(argv[1]), 2, 9); // atoi converts strings to integers (if possible)
    b.cols = clamp(atoi(argv[2]), 2, 9);
    printf("creating a memory board with %d rows and %d cols\n", b.rows, b.cols);
    int pairs = b.rows * b.cols / 2;
    printf("%d pairs\n", pairs);
    b.ncards = 2 * pairs;
    printf("%d cards\n", b.ncards);
    char cards[b.ncards];
    b.cards = cards;
    b.points = 0;
    b.turns = 0;
    init_cards(&b);

    clear_screen();
    print_board(&b);
    while (2 * b.points < b.ncards) {
        do_move(&b);
    }

    return 0;
}

/*
Example sequence:
-----------------

  1 2 3
1 # # #
2 # # #
0 points, 0 turns
11

  1 2 3
1 B # #
2 # # #
0 points, 1 turns
12

  1 2 3
1 B C #
2 # # #
0 points, 2 turns
press <return> to continue

  1 2 3
1 # # #
2 # # #
0 points, 2 turns
21

  1 2 3
1 # # #
2 A # #
0 points, 3 turns
22

  1 2 3
1 # # #
2 A C #
0 points, 4 turns
press <return> to continue

  1 2 3
1 # # #
2 # # #
0 points, 4 turns
12

  1 2 3
1 # C #
2 # # #
0 points, 5 turns
22

  1 2 3
1 # C #
2 # C #
0 points, 6 turns
press <return> to continue

  1 2 3
1 #   #
2 #   #
1 points, 6 turns
23

  1 2 3
1 #   #
2 #   A
1 points, 7 turns
21

  1 2 3
1 #   #
2 A   A
1 points, 8 turns
press <return> to continue

  1 2 3
1 #   #
2
2 points, 8 turns
11

  1 2 3
1 B   #
2
2 points, 9 turns
13

  1 2 3
1 B   B
2
2 points, 10 turns
press <return> to continue

  1 2 3
1
2
3 points, 10 turns
*/
