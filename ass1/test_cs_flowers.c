// cs_flowers.c
//
// This program was written by [Ruikang Xiao] (z5473233)
// on March 20 2024
//
// CS Flower is an action turn-based game. As the player,
// you have to move on the lawn and cut down all the flowers.
// When you cut them down, however, the flowers will wake up,
// evolve, and take revenge on you.
// You can win the game only if you survive and all the flowers are cut down.


#include <stdio.h>

//------------------------------------------------------------------------------
// Constants
//------------------------------------------------------------------------------

#define MAX_ROW 11
#define MAX_COL 11
#define TRUE 1
#define FALSE 0

// TODO: put your constants here

//------------------------------------------------------------------------------
// Struct & Enum
//------------------------------------------------------------------------------

enum flower_state {
    NONE,
    DORMANT,
    DISTURBED,
    AWAKENED,
    ANXIOUS,
    ENERGETIC
};

struct flower {
    enum flower_state state;
    // TODO: You will need to add more to this struct in Stage 3
    int place_protection;
};

enum tile_type {
    EMPTY,
    BUSH,
    BRANCH,
    DANGER,
    ROOT,
    POLLEN,
    SEEDLING,
    FLOWER,
};

struct tile {
    enum tile_type type;
    struct flower flower;
};

// TODO: Put your structs here

struct result {
    int player_row;
    int player_col;
    int player_alive;
    int alert_row;
    int alert_col;
    int game_alive;
};


// ------------------------ Proto  -----------------------------------

// stage 1

struct result spawn_player(struct tile map[MAX_ROW][MAX_COL], struct result result);

void print_foliage(struct tile map[MAX_ROW][MAX_COL], struct result result);

void print_branch(struct tile map[MAX_ROW][MAX_COL]);

void print_bush(struct tile map[MAX_ROW][MAX_COL]);


// stage 2

void spawn_flowers(struct tile map[MAX_ROW][MAX_COL], struct result result);

struct result action(struct tile map[MAX_ROW][MAX_COL], struct result result);

struct result move_player(struct tile map[MAX_ROW][MAX_COL], struct result result, char command);

struct result cut_flower_bush(struct tile map[MAX_ROW][MAX_COL], struct result result);

void alert(struct tile map[MAX_ROW][MAX_COL], int alert_row, int alert_col);

// stage 3

int check_game_status(struct tile map[MAX_ROW][MAX_COL], struct result result);

void find_dormant_flower(struct tile map[MAX_ROW][MAX_COL]);

void place_protection(struct tile map[MAX_ROW][MAX_COL], int flower_row, int flower_col);

// -----------------------------------------------------------------------


//--------------------------------
// Provided Function Prototypes
//--------------------------------

void initialise_map(struct tile map[MAX_ROW][MAX_COL]);

void print_map(
        struct tile map[MAX_ROW][MAX_COL],
        int player_row,
        int player_col);

void print_tile(struct tile tile);

void print_flower(struct flower flower);


//----------------  Main Function  ---------------------

int main(void) {
    // initialize result and map
    struct tile map[MAX_ROW][MAX_COL];
    struct result result = {
        .player_row = 0,
        .player_col = 0,
        .player_alive = TRUE,
        .alert_row = 0,
        .alert_col = 0,
        .game_alive = TRUE
    };
    initialise_map(map);

    // stage 1.1 - 1.2: scan in the player position and
    result = spawn_player(map, result);
    print_map(map, result.player_row, result.player_col);

    // stage 1.3 - add foliage onto the map
    print_foliage(map, result);

    // stage 2.1 - spawn flowers
    spawn_flowers(map, result);

    // stage 2.2 - 2.3: start the game
    action(map, result);
    
    return 0;

}


//-----------  my functions   -------------------------

//start the game and record the player's position
struct result spawn_player(struct tile map[MAX_ROW][MAX_COL], struct result result) {
    printf("Welcome to CS Flowers!\n");
    // Stage 1.1: Scan in the player position and print out the map
    printf("Player's starting position: ");

    scanf("%d %d", &result.player_row, &result.player_col);

    // Stage 1.2: Validate the player's spawn and re-scan if invalid
    // write boolean expression for when the position is invalid
    while (result.player_row > 0 && result.player_row < MAX_ROW - 1 &&
           result.player_col > 0 && result.player_col < MAX_COL - 1) {
        printf("Invalid starting position!\n");
        printf("Re-enter starting position: ");
        scanf("%d %d", &result.player_row, &result.player_col);
    }
    result.player_alive = TRUE;

    return result;
}

// print foliage on the map
void print_foliage(struct tile map[MAX_ROW][MAX_COL], struct result result) {
    char foliage_type = ' ';
    int num_foliage;
    printf("How many tiles of foliage: ");
    scanf("%d", &num_foliage);

    for (int count = 0; count < num_foliage; count++) {
        // scan in the type of foliage
        scanf(" %c", &foliage_type);
        // branch
        if (foliage_type == 'b') {
            print_branch(map);
        }
            // bush
        else if (foliage_type == 'u') {
            print_bush(map);
        }
    }
    print_map(map, result.player_row, result.player_col);
}

// print valid branch
void print_branch(struct tile map[MAX_ROW][MAX_COL]) {
    int foliage_row, foliage_col;

    // scan in the position of the branch
    scanf("%d %d", &foliage_row, &foliage_col);

    // check if the position is valid
    if (foliage_row > 0 && foliage_row < MAX_ROW - 1 &&
        foliage_col > 0 && foliage_col < MAX_COL - 1) {
        // add branch
        map[foliage_row][foliage_col].type = BRANCH;
        printf("Branch added!\n");
    } else {
        printf("Invalid foliage position!\n");
    }
}

// print valid bushes
void print_bush(struct tile map[MAX_ROW][MAX_COL]) {
    int foliage_row, foliage_col;
    char direction;
    int num_bush;

    // scan in the position of the bush
    scanf("%d %d %c %d", &foliage_row, &foliage_col, &direction, &num_bush);

    // check if the position is valid
    if (foliage_row > 0 && foliage_row < MAX_ROW - 1 &&
        foliage_col > 0 && foliage_col < MAX_COL - 1) {
        if (direction == 'h') {
            for (int i = 0; i < num_bush; i++) {
                map[foliage_row][foliage_col + i].type = BUSH;
            }
        } else if (direction == 'v') {
            for (int i = 0; i < num_bush; i++) {
                map[foliage_row + i][foliage_col].type = BUSH;
            }
        }
        printf("Bush added!\n");
    } else {
        printf("Invalid foliage position!\n");
    }
}

// print valid flowers
void spawn_flowers(struct tile map[MAX_ROW][MAX_COL], struct result result) {
    int num_flower;
    printf("How many flowers: ");
    scanf("%d", &num_flower);

    // print all flowers as because there are up to 25 valid flowers by using iterating over odd rows and columns
    if (num_flower >= 25) {
        for (int flower_row = 1; flower_row < MAX_ROW; flower_row += 2) {
            for (int flower_col = 1; flower_col < MAX_COL; flower_col += 2) {
                if (map[flower_row][flower_col].type == EMPTY) {
                    map[flower_row][flower_col].type = FLOWER;
                    map[flower_row][flower_col].flower.state = DORMANT;
                }
            }
        }
    }
    
    // if the number of flowers is less than 25
    else {
        for (int count = 0; count < num_flower; count++) {
            int flower_row, flower_col;
            scanf("%d %d", &flower_row, &flower_col);

            // check if the position is valid for spawning a flower
            // if the position is valid, spawn a flower 
            // and set its state to dormant
            // if not, print an error message
            if (flower_row % 2 == 1 && flower_row < MAX_ROW - 1 &&
                flower_col % 2 == 1 && flower_col < MAX_COL - 1 &&
                map[flower_row][flower_col].type == EMPTY) {
                map[flower_row][flower_col].type = FLOWER;
                map[flower_row][flower_col].flower.state = DORMANT;
            } else {
                printf("Invalid flower position!\n");
            }
        }
    }

    print_map(map, result.player_row, result.player_col);
}

struct result action(struct tile map[MAX_ROW][MAX_COL], struct result result) {
    char command;
    printf("Game Started!\nEnter command: ");

    // Read user input for the command
    int return_val = scanf(" %c", &command);

    // check whether the command is valid
    while (return_val == 1) {
        // check the command: cut or move
        if (command == 'c') {
            // if command is 'c', execute 'cut_flower'
            result = cut_flower_bush(map, result);
        } else {
            // if command is other than 'c', execute 'move_player'
            result = move_player(map, result, command);
        }

        print_map(map, result.player_row, result.player_col);

        // find dormant flowers on the map
        find_dormant_flower(map);

        // check game status and decide whether to continue
        result.game_alive = check_game_status(map, result);
        if (result.game_alive == TRUE) {
            // if game is still alive, start next round
            printf("Enter command: ");
            return_val = scanf(" %c", &command);
        } else {
            // if game is over, break the loop
            break;
        }
    }
    return result;
}

// moving players, if the tile is a branch, may alert flowers
struct result move_player(struct tile map[MAX_ROW][MAX_COL],
                          struct result result, char command) {

    // move the player up, and alert flowers if the tile is a branch
    if (command == 'w') {
        if (result.player_row - 1 >= 0 &&
            map[result.player_row - 1][result.player_col].type == EMPTY) {
            result.player_row--;
        } else if (result.player_row - 1 >= 0 &&
                   map[result.player_row - 1][result.player_col].type == BRANCH) {
            result.player_row--;
            map[result.player_row][result.player_col].type = EMPTY;
            alert(map, result.player_row, result.player_col);
        }
    }

    // move the player down, and alert flowers if the tile is a branch
    else if (command == 's') {
        if (result.player_row + 1 < MAX_ROW &&
            map[result.player_row + 1][result.player_col].type == EMPTY) {
            result.player_row++;
        } else if (result.player_row + 1 < MAX_ROW &&
                   map[result.player_row + 1][result.player_col].type == BRANCH) {
            result.player_row++;
            map[result.player_row][result.player_col].type = EMPTY;
            alert(map, result.player_row, result.player_col);
        }
    }

    // move the player left, and alert flowers if the tile is a branch
    else if (command == 'a') {
        if (result.player_col - 1 >= 0 &&
            map[result.player_row][result.player_col - 1].type == EMPTY) {
            result.player_col--;
        } else if (result.player_col - 1 >= 0 &&
                   map[result.player_row][result.player_col - 1].type == BRANCH) {
            result.player_col--;
            map[result.player_row][result.player_col].type = EMPTY;
            alert(map, result.player_row, result.player_col);
        }
    }

    // move the player right, and alert flowers if the tile is a branch
    else if (command == 'd') {
        if (result.player_col + 1 < MAX_COL &&
            map[result.player_row][result.player_col + 1].type == EMPTY) {
            result.player_col++;
        } else if (result.player_col + 1 < MAX_COL &&
                   map[result.player_row][result.player_col + 1].type == BRANCH) {
            result.player_col++;
            map[result.player_row][result.player_col].type = EMPTY;
            alert(map, result.player_row, result.player_col);
        }
    }

    return result;
}

// cut a flower or bush
struct result cut_flower_bush(struct tile map[MAX_ROW][MAX_COL], struct result result) {
    char command;
    int return_val = scanf(" %c", &command);

    // check whether the command is valid
    if (return_val == 1) {
        // if command is w, cut the flower above the player
        if (command == 'w') {
            // check whether the command is valid and if the tile above is a flower
            if (result.player_row - 1 >= 0 &&
                map[result.player_row - 1][result.player_col].type == FLOWER) {
                // cut it and alert the flowers around it
                map[result.player_row - 1][result.player_col].type = EMPTY;
                alert(map, result.player_row - 1, result.player_col);
            }
                // check whether the command is valid and if the tile above is a bush
            else if (result.player_row - 1 >= 0 &&
                     map[result.player_row - 1][result.player_col].type == BUSH) {
                // cut it
                map[result.player_row - 1][result.player_col].type = EMPTY;
            }
        } 
        
        // Similar to the case where command is s
        else if (command == 's') {
            if (result.player_row + 1 < MAX_ROW &&
                map[result.player_row + 1][result.player_col].type == FLOWER) {
                map[result.player_row + 1][result.player_col].type = EMPTY;
                alert(map, result.player_row + 1, result.player_col);
            } else if (result.player_row + 1 < MAX_ROW &&
                       map[result.player_row + 1][result.player_col].type == BUSH) {
                map[result.player_row + 1][result.player_col].type = EMPTY;
            }
        } 
        
        // Similar to the case where command is s
        else if (command == 'a') {
            if (result.player_col - 1 >= 0 &&
                map[result.player_row][result.player_col - 1].type == FLOWER) {
                map[result.player_row][result.player_col - 1].type = EMPTY;
                alert(map, result.player_row, result.player_col - 1);
            } else if (result.player_col - 1 >= 0 &&
                       map[result.player_row][result.player_col - 1].type == BUSH) {
                map[result.player_row][result.player_col - 1].type = EMPTY;
            }
        } 
        
        // Similar to the case where command is s
        else if (command == 'd') {
            if (result.player_col + 1 < MAX_COL &&
                map[result.player_row][result.player_col + 1].type == FLOWER) {
                map[result.player_row][result.player_col + 1].type = EMPTY;
                alert(map, result.player_row, result.player_col + 1);
            } else if (result.player_col + 1 < MAX_COL &&
                       map[result.player_row][result.player_col + 1].type == BUSH) {
                map[result.player_row][result.player_col + 1].type = EMPTY;
            }
        }
    }
    return result;
}

// alert nearby flowers
void alert(struct tile map[MAX_ROW][MAX_COL], int alert_row, int alert_col) {
    for (int scan_row = alert_row - 2; scan_row <= alert_row + 2; scan_row++) {
        for (int scan_col = alert_col - 2; scan_col <= alert_col + 2; scan_col++) {

            // check if the position is within the map boundaries
            if (scan_row >= 0 && scan_row < MAX_ROW &&
                scan_col >= 0 && scan_col < MAX_COL &&
                map[scan_row][scan_col].type == FLOWER) {
                
                // if the flower state is dormant, change it to disturbed
                if (map[scan_row][scan_col].flower.state == DORMANT) 
                {
                    map[scan_row][scan_col].flower.state = DISTURBED;
                } 
                
                // if the flower state is disturbed, change it to awakened
                else 
                {    
                    map[scan_row][scan_col].flower.state = AWAKENED;
                }
            }
        }
    }
}

// check status of the game
int check_game_status(struct tile map[MAX_ROW][MAX_COL], struct result result) {
    int num_flower = 0;

    // iterate over all possible locations of flowers
    for (int flower_row = 1; flower_row < MAX_ROW; flower_row = flower_row + 2) {
        for (int flower_col = 1; flower_col < MAX_COL; flower_col = flower_col + 2) {

            // increment the flower counter if the scanned tile contains a flower
            if (map[flower_row][flower_col].type == FLOWER) {
                num_flower++;
            }
        }
    }

    // check win or lose
    if (num_flower == 0) {
        printf("All flowers are eradicated and UNSW has been saved!\n");
        result.game_alive = FALSE;
    } else if (map[result.player_row][result.player_col].type == FLOWER) {
        printf("The flowers have beaten us, and UNSW is lost forever!\n");
        result.game_alive = FALSE;
    }
    return result.game_alive;
}

// find dormant flowers and change their protection status
void find_dormant_flower(struct tile map[MAX_ROW][MAX_COL]) {
    
    // iterate over all possible locations of flowers
    for (int scan_row = 1; scan_row < MAX_ROW; scan_row++) {
        for (int scan_col = 1; scan_col < MAX_COL; scan_col++) {
    
            // check if the scanned tile contains a flower
            if (map[scan_row][scan_col].type == FLOWER &&
                map[scan_row][scan_col].flower.state != DORMANT) {
    
                // check if the scanned tile contains a flower
                if (map[scan_row][scan_col].flower.place_protection) {
    
                    // if the flower has place protection, set it to FALSE
                    map[scan_row][scan_col].flower.place_protection = FALSE;
                } else {
    
                    // place a protection
                    place_protection(map, scan_row, scan_col);
                }
            }
        }
    }
}

// place protection around a flower
void place_protection(struct tile map[MAX_ROW][MAX_COL], int flower_row, int flower_col) {
    
    // define weak points around a flower
    int weak_point[4][2];

    weak_point[0][0] = flower_row + 1;
    weak_point[0][1] = flower_col;

    weak_point[1][0] = flower_row;
    weak_point[1][1] = flower_col + 1;

    weak_point[2][0] = flower_row - 1;
    weak_point[2][1] = flower_col;

    weak_point[3][0] = flower_row;
    weak_point[3][1] = flower_col - 1;

    // iterate over each weak point
    for (int count = 0; count < 4; count++) {
        int weak_row = weak_point[count][0];
        int weak_col = weak_point[count][1];

        // check if a weak point is within the map boundries and is a branch
        if (weak_row >= 0 && weak_row < MAX_ROW &&
            weak_col >= 0 && weak_col < MAX_COL &&
            map[weak_row][weak_col].type == BRANCH) {
            // if the weak point is a branch, update it to a bush
            // and set protection to TRUE
            map[weak_row][weak_col].type = BUSH;
            map[flower_row][flower_col].flower.place_protection = TRUE;
        }
        
        // check if a weak point is within the map boundries and is empty
        else if (weak_row >= 0 && weak_row < MAX_ROW &&
                 weak_col >= 0 && weak_col < MAX_COL &&
                 map[weak_row][weak_col].type == EMPTY) {
            // if the weak point is empty, update it to a bush, set protection to TRUE,
            // then exit the loop
            map[weak_row][weak_col].type = BUSH;
            map[flower_row][flower_col].flower.place_protection = TRUE;
            break;
        }
    }
}

// Provided Functions

/**
 * Initialises the game map with empty tiles, setting the type of each tile to
 * `EMPTY` and initialising flower-related properties.
 *
 * @param map: The 2D array of `struct tile` representing the game map
 *
 * @returns None
 *
**/

void initialise_map(struct tile map[MAX_ROW][MAX_COL]) {
    for (int row = 0; row < MAX_ROW; row++) {
        for (int col = 0; col < MAX_COL; col++) {
            map[row][col].type = EMPTY;
            map[row][col].flower.state = NONE;
            map[row][col].flower.place_protection = FALSE;
        }
    }
}


/**
 * Prints the game map
 *
 * @param map: The 2D array of `struct tile` representing the game map.
 * @param player_row: The row coordinate of the player.
 * @param player_col: The column coordinate of the player.
 *
 * @returns None
**/

void print_map(
        struct tile map[MAX_ROW][MAX_COL],
        int player_row,
        int player_col
) {
    for (int i = 0; i < MAX_ROW; i++) {
        for (int j = 0; j < MAX_COL; j++) {
            printf("+---");
        }
        printf("+\n");

        for (int j = 0; j < MAX_COL; j++) {
            printf("|");
            if (player_row != i || player_col != j) {
                print_tile(map[i][j]);
            } else if (map[i][j].type == EMPTY) {
                printf(" P ");
            } else if (map[i][j].type == DANGER) {
                printf("<P>");
            }
        }

        printf("|\n");
    }

    for (int j = 0; j < MAX_COL; j++) {
        printf("+---");
    }
    printf("+\n");
}


/**
 * Helper function which prints the representation of a single tile
 * based on its type.
 *
 * @params tile: The `struct tile` to be printed.
 *
 * @returns None
**/

void print_tile(struct tile tile) {
    if (tile.type == EMPTY) {
        printf("   ");
    } else if (tile.type == BUSH) {
        printf("###");
    } else if (tile.type == BRANCH) {
        printf("_/-");
    } else if (tile.type == DANGER) {
        printf("< >");
    } else if (tile.type == ROOT) {
        printf("<^>");
    } else if (tile.type == POLLEN) {
        printf(":::");
    } else if (tile.type == FLOWER) {
        print_flower(tile.flower);
    }
}

/**
 * Helper function which prints a visual representation of the
 * flower face based on its state.
 *
 * @params flower: The `struct flower` containing the state of the flower.
 *
 * @returns None
 *
**/

void print_flower(struct flower flower) {
    if (flower.state == DORMANT) {
        printf("uwu");
    } else if (flower.state == DISTURBED) {
        printf("uwo");
    } else if (flower.state == AWAKENED) {
        printf("owo");
    } else if (flower.state == ANXIOUS) {
        printf("o~o");
    } else if (flower.state == ENERGETIC) {
        printf("*w*");
    }
}

