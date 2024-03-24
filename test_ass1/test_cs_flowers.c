// cs_flowers.c
//
// This program was written by [Ruikang Xiao] (z5473233)
// on March 20 2024
//
// TODO: Description of program

#include <stdio.h>
#include <stdlib.h>

// Constants

#define MAX_ROW 11
#define MAX_COL 11
#define TRUE 1
#define FALSE 0

// Struct & Enum

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

struct result
{
    int player_row;
    int player_col;
    int player_alive;
    int alert_row;
    int alert_col;
    int game_alive;
};


// Protos

// Stage 1
void print_foliage(struct tile map[MAX_ROW][MAX_COL], struct result result);
void print_branch(struct tile map[MAX_ROW][MAX_COL]);
void print_bush(struct tile map[MAX_ROW][MAX_COL]);

// Stage 2
void spawn_flowers(struct tile map[MAX_ROW][MAX_COL], struct result result);
struct result action(struct tile map[MAX_ROW][MAX_COL], struct result result);
struct result move_player(struct tile map[MAX_ROW][MAX_COL], struct result result, char command);
struct result cut_flower(struct tile map[MAX_ROW][MAX_COL], struct result result);
void alert(struct tile map[MAX_ROW][MAX_COL], int alert_row, int alert_col);

// Stage 3
int check_game_status(struct tile map[11][11], struct result result);



// Provided Function Prototypes

void initialise_map(struct tile map[MAX_ROW][MAX_COL]);
void print_map(
    struct tile map[MAX_ROW][MAX_COL], 
    int player_row, 
    int player_col
);

void print_tile(struct tile tile);
void print_flower(struct flower flower);


// Main

int main(void) {
    struct tile map[MAX_ROW][MAX_COL];
    struct result result;

    // initialize result and map
    result.alert_row = 0;
    result.alert_col = 0;
    initialise_map(map);
    result.game_alive = TRUE;    
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
    print_map(map, result.player_row, result.player_col);
    
    // Stage 1.3 - Add foliage onto the map, starting with branches
    // Prompt for how many tiles of foliage will be added onto the map.
    print_foliage(map, result);

    // stage 2.1
    spawn_flowers(map, result);
    
    // stage 2.2 - 2.3
    action(map, result);
    return 0;
}


void print_foliage(struct tile map[MAX_ROW][MAX_COL], struct result result)
{
    // variables for storing foliage type and count
    char foliage_type = ' ';
    int num_foliage;
    
    // scan in the num
    printf("How many tiles of foliage: ");
    scanf("%d", &num_foliage);

    // iterate through each foliage
    for (int count = 0; count < num_foliage; count++)
    {
        // scan in the type of foliage (branch or bush)
        scanf(" %c", &foliage_type);
        
        // // add branch if foliage type is 'b'
        if (foliage_type == 'b') {
            print_branch(map);
        }

        // // add bush if foliage type is 'u'
        else if (foliage_type == 'u') {
            print_bush(map);
        }
    }

    // update the map
    print_map(map, result.player_row, result.player_col);
}

// function to record a position of branch
void print_branch(struct tile map[MAX_ROW][MAX_COL]) {
    // variables to store the position of foliage
    int foliage_row, foliage_col;

    // scan in the position
    scanf("%d %d", &foliage_row, &foliage_col);

    // check if the position is within the map boundaries
    if (foliage_row > 0 && foliage_row < MAX_ROW - 1 && 
        foliage_col > 0 && foliage_col < MAX_COL - 1) {
        // if the position is valid, set the type of the tile to BRANCH
        map[foliage_row][foliage_col].type = BRANCH;
        printf("Branch added!\n");
    }
    else {
        // if the position is not valid, inform player and ignore the position
        printf("Invalid foliage position!\n");
    }
}

// function to record a position of bush
void print_bush(struct tile map[MAX_ROW][MAX_COL]) {
    int foliage_row, foliage_col;
    char direction;
    int num_bush;

    // scan in the position, direction, and number of bushes
    scanf("%d %d %c %d", &foliage_row, &foliage_col, &direction, &num_bush);
    
    // check if the position is within the map boundaries
    if (foliage_row > 0 && foliage_row < MAX_ROW - 1 && 
        foliage_col > 0 && foliage_col < MAX_COL - 1) {

        // if the position is valid, determine the direction and numbers of the bushes
        // if direction is h, place bushes horizontally
        if (direction == 'h') {
            for (int i = 0; i < num_bush; i++) {
                map[foliage_row][foliage_col + i].type = BUSH;
            }
        }

        // if direction is v, place bushes vertically
        else if (direction == 'v') {
            for (int i = 0; i < num_bush; i++) {
                map[foliage_row + i][foliage_col].type = BUSH;
            }
        }
        // inform the player that bushes have been added
        printf("Bush added!\n");
    }
    else {
        // if the position is not valid, inform player and ignore the position
        printf("Invalid foliage position!\n");
    }
}


// stage 2.1
// function to spawn flowers at a player-specified position
void spawn_flowers(struct tile map[MAX_ROW][MAX_COL], struct result result) {
    // variables to store the number of the flower
    int num_flower;

    // ask and scan in the number
    printf("How many flowers: ");
    scanf("%d", &num_flower);

    // When the number is greater than 25, spawn flowers at all valid positions 
    // as a maximum of 25 flowers can be spawned
    if (num_flower >= 25) {

        // spawn flowers at all (odd, odd) positions by using 2 for loops
        for (int flower_row = 1; flower_row < MAX_ROW; flower_row += 2) {
            for (int flower_col = 1; flower_col < MAX_COL; flower_col += 2) {
                // check if the tile is empty before adding a flower
                if (map[flower_row][flower_col].type == EMPTY) {    
                    // spawn a flower to the empty tile and set its state to DORMANT
                    map[flower_row][flower_col].type = FLOWER;
                    map[flower_row][flower_col].flower.state = DORMANT;
                }
            }
        }
    }
    // if the number of flowers is less then 25, spawn flowers at a player-specified position
    // and count numbers of flowers
    else {
        for (int count = 0; count < num_flower; count++) {
            int flower_row, flower_col;
            
            // scan in the position of a flower
            scanf("%d %d", &flower_row, &flower_col);

            // check if the position is valid for spawning a flower
            // if the position is valid, add a flower and set its state to DORMANT
            if (flower_row % 2 == 1 && flower_row < MAX_ROW - 1 && 
                flower_col % 2 == 1 && flower_col < MAX_COL -1 && 
                map[flower_row][flower_col].type == EMPTY)
            {
                map[flower_row][flower_col].type = FLOWER;
                map[flower_row][flower_col].flower.state = DORMANT;
            }
            // if the position is not valid, inform player and ignore the position
            else {
                printf("Invalid flower position!\n");
            }
        }
    }

    // update the map
    print_map(map, result.player_row, result.player_col);
}

// stage 2.2
// function to handle player actions (move and cut) during the game
// and determine should the game continue
struct result action(struct tile map[MAX_ROW][MAX_COL], struct result result) {
    // variable to store a player-specified command
    char command;
    printf("Game Started!\nEnter command: ");
    
    // 'scanf' scans in the first character
    // then 'return_val' store the number of items 
    // successfully matched and assigned by 'scanf'
    int return_val = scanf(" %c", &command);

    // loop commands as long as a valid input
    // ctrl + d will stop the loop
    while (return_val == 1) {
        //if command is c, call cut_flower function
        if (command == 'c') {
            result = cut_flower(map, result);
        }
        // else, call move_player function
        else {
            result = move_player(map, result, command);
        }

        // update the map
        print_map(map, result.player_row, result.player_col);

        // check game status and decide whether to continue
        result.game_alive = check_game_status(map, result);
        if (result.game_alive == TRUE) {
            printf("Enter command: ");
            return_val = scanf(" %c", &command);
        }
        // if 'result.game_alive' is FALSE, stop the game
        else {
            break;
        }
    }
    return result;
}



// Function to determine the type of tile after player's move
enum tile_type get_target_tile_type(struct tile map[MAX_ROW][MAX_COL], int player_row, int player_col, char command) {
    if (command == 'w') {
        return map[player_row - 1][player_col].type;
    } else if (command == 's') {
        return map[player_row + 1][player_col].type;
    } else if (command == 'a') {
        return map[player_row][player_col - 1].type;
    } else if (command == 'd') {
        return map[player_row][player_col + 1].type;
    } else {
    }
}

// Function to move the player based on the command
struct result move_player(struct result result, char command) {
    if (command == 'w') {
        result.player_row--;
    } else if (command == 's') {
        result.player_row++;
    } else if (command == 'a') {
        result.player_col--;
    } else if (command == 'd') {
        result.player_col++;
    }
    return result;
}








// // function to move the player on the game map based on player's command
// struct result move_player(struct tile map[MAX_ROW][MAX_COL], struct result result, char command) {
//     // check the command
//     // if command is w
//     if (command == 'w') {
//         // check is the target tile is within the boundaries and empty
//         if (result.player_row - 1 >= 0 && 
//             map[result.player_row - 1][result.player_col].type == EMPTY) {
//             // if yes, move the player to the target tile
//             result.player_row--;
//         }
//         // check is the target tile is within the boundaries and is a branch
//         else if (result.player_row - 1 >= 0 && map[result.player_row - 1][result.player_col].type == BRANCH) {
//             result.player_row--;
//             // if yes, remove the branch and move the player to the target tile
//             map[result.player_row][result.player_col].type = EMPTY;
//             // alert nearby flowers
//             alert(map, result.player_row, result.player_col);
//         }
//     }
//     else if (command == 's') {
//         if (result.player_row + 1 < MAX_ROW && map[result.player_row + 1][result.player_col].type == EMPTY) {
//             result.player_row++;
//         }
//         else if (result.player_row + 1 < MAX_ROW && map[result.player_row + 1][result.player_col].type == BRANCH) {
//             result.player_row++;
//             map[result.player_row][result.player_col].type = EMPTY;
//             alert(map, result.player_row, result.player_col);
//         }
//     }
//     else if (command == 'a') {
//         if (result.player_col - 1 >= 0 && map[result.player_row][result.player_col - 1].type == EMPTY) {
//             result.player_col--;
//         }
//         else if (result.player_col - 1 >= 0 && map[result.player_row][result.player_col - 1].type == BRANCH) {
//             result.player_col--;
//             map[result.player_row][result.player_col].type = EMPTY;
//             alert(map, result.player_row, result.player_col);
//         }
//     }
//     else if (command == 'd') {
//         if (result.player_col + 1 < MAX_COL && map[result.player_row][result.player_col + 1].type == EMPTY) {
//             result.player_col++;
//         }
//         else if (result.player_col + 1 < MAX_COL && map[result.player_row][result.player_col + 1].type == BRANCH) {
//             result.player_col++;
//             map[result.player_row][result.player_col].type = EMPTY;
//             alert(map, result.player_row, result.player_col);
//         }
//     }

//     return result;
// }

struct result cut_flower(struct tile map[MAX_ROW][MAX_COL], struct result result) {
    char command;
    int return_val = scanf(" %c", &command);
    if (return_val == 1) {
        if (command == 'w') {
            if (result.player_row - 1 >= 0 &&
                map[result.player_row - 1][result.player_col].type == FLOWER) {
                map[result.player_row - 1][result.player_col].type = EMPTY;
                alert(map, result.player_row - 1, result.player_col);
            } else if (result.player_row - 1 >= 0 &&
                       map[result.player_row - 1][result.player_col].type == BUSH) {
                map[result.player_row - 1][result.player_col].type = EMPTY;
            }
        } else if (command == 's') {
            if (result.player_row + 1 < MAX_ROW &&
                map[result.player_row + 1][result.player_col].type == FLOWER) {
                map[result.player_row + 1][result.player_col].type = EMPTY;
                alert(map, result.player_row + 1, result.player_col);
            } else if (result.player_row + 1 < MAX_ROW &&
                       map[result.player_row + 1][result.player_col].type == BUSH) {
                map[result.player_row + 1][result.player_col].type = EMPTY;
            }
        } else if (command == 'a') {
            if (result.player_col - 1 >= 0 &&
                map[result.player_row][result.player_col - 1].type == FLOWER) {
                map[result.player_row][result.player_col - 1].type = EMPTY;
                alert(map, result.player_row, result.player_col - 1);
            } else if (result.player_col - 1 >= 0 &&
                       map[result.player_row][result.player_col - 1].type == BUSH) {
                map[result.player_row][result.player_col - 1].type = EMPTY;
            }
        } else if (command == 'd') {
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

// 2.4
void alert(struct tile map[MAX_ROW][MAX_COL], int alert_row, int alert_col) {
    for (int scan_row = alert_row - 2; scan_row <= alert_row + 2; scan_row++) {
        for (int scan_col = alert_col - 2; scan_col <= alert_col + 2; scan_col++) {
            if (scan_row >= 0 && scan_row < MAX_ROW && 
                scan_col >= 0 && scan_col < MAX_COL && 
                map[scan_row][scan_col].type == FLOWER) {
                if (map[scan_row][scan_col].flower.state == DORMANT) {
                    map[scan_row][scan_col].flower.state = DISTURBED;
                }
                else {
                    map[scan_row][scan_col].flower.state = AWAKENED;
                }
            }
        }
    }
}


// Stage 3.1

int check_game_status(struct tile map[11][11], struct result result) {
    int num_flower = 0;
    for (int flower_row = 1; flower_row < MAX_ROW; flower_row = flower_row + 2) {
        for (int flower_col = 1; flower_col < MAX_COL; flower_col = flower_col + 2) {
            if (map[flower_row][flower_col].type == FLOWER) {
                num_flower++;
            }
        }
    }

    if (num_flower == 0) {
        printf("All flowers are eradicated and UNSW has been saved!\n");
        result.game_alive = FALSE;
    }
    else if (map[result.player_row][result.player_col].type == FLOWER) {
        printf("The flowers have beaten us, and UNSW is lost forever!\n");
        result.game_alive = FALSE;
    }
    return result.game_alive;
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

        for (int j = 0; j < MAX_COL;j++) {
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
