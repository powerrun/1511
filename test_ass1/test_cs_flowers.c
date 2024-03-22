// cs_flowers.c
//
// This program was written by [Ruikang Xiao] (z5473233)
// on March 20 2024
//
// TODO: Description of program

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

struct position
{
    int row;
    int col;
};


////////////////////////////////


//     ██████   ██████     ██████    ████████    ██████ 
//     ██  ██   ██   ██   ██    ██      ██      ██    ██
//     ██████   ██████    ██    ██      ██      ██    ██
//     ██       ██   ██   ██    ██      ██      ██    ██
//     ██       ██   ██    ██████       ██       ██████ 
// 
// Stage 1
void print_foliage(struct tile map[MAX_ROW][MAX_COL], struct position player);
void print_branch(struct tile map[MAX_ROW][MAX_COL]);
void print_bush(struct tile map[MAX_ROW][MAX_COL]);

// Stage 2
void spawn_flowers(struct tile map[MAX_ROW][MAX_COL], struct position player);

void action(struct tile map[MAX_ROW][MAX_COL], struct position player);

struct position move_player(struct tile map[MAX_ROW][MAX_COL], struct position player, char command);

struct position cut_flower(struct tile map[MAX_ROW][MAX_COL], struct position player);

struct tile alert_branch(struct tile map[MAX_ROW][MAX_COL], struct position player);

struct tile alert_flower(struct tile map[MAX_ROW][MAX_COL], struct position player, char command);






//--------------------------------
// Provided Function Prototypes
//--------------------------------

void initialise_map(struct tile map[MAX_ROW][MAX_COL]);
void print_map(
    struct tile map[MAX_ROW][MAX_COL], 
    int player_row, 
    int player_col
);

void print_tile(struct tile tile);
void print_flower(struct flower flower);



//    ███    ███     █████     ██████    ███    ██ 
//    ████  ████    ██   ██      ██      ████   ██ 
//    ██ ████ ██    ███████      ██      ██ ██  ██ 
//    ██  ██  ██    ██   ██      ██      ██  ██ ██ 
//    ██      ██    ██   ██    ██████    ██   ████ 


int main(void) {
    struct tile map[MAX_ROW][MAX_COL];
    struct position player;
    initialise_map(map);
    
    printf("Welcome to CS Flowers!\n");

    // Stage 1.1: Scan in the player position and print out the map
    printf("Player's starting position: ");
    
    scanf("%d %d", &player.row, &player.col);

    // Stage 1.2: Validate the player's spawn and re-scan if invalid
    // write boolean expression for when the position is invalid
    while (player.row > 0 && player.row < MAX_ROW - 1 &&
           player.col > 0 && player.col < MAX_COL - 1) {
        printf("Invalid starting position!\n");
        printf("Re-enter starting position: ");
        scanf("%d %d", &player.row, &player.col);
    }
    print_map(map, player.row, player.col);
    
    // Stage 1.3 - Add foliage onto the map, starting with branches
    // Prompt for how many tiles of foliage will be added onto the map.
    print_foliage(map, player);


    // stage 2.1
    spawn_flowers(map, player);
    
    // stage 2.2 - 2.3
    action(map, player);


    return 0;
}


//     ███████   ██    ██   ███    ██    ██████   ████████
//     ██        ██    ██   ████   ██   ██           ██   
//     █████     ██    ██   ██ ██  ██   ██           ██   
//     ██        ██    ██   ██  ██ ██   ██           ██   
//     ██         ██████    ██   ████    ██████      ██   

// stage 1.3 - 1.4

void print_foliage(struct tile map[MAX_ROW][MAX_COL], struct position player)
{
    char foliage_type = ' ';
    int num_foliage;
    printf("How many tiles of foliage: ");
    scanf("%d", &num_foliage);

    for (int count = 0; count < num_foliage; count++)
    {
        // ask type
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
    print_map(map, player.row, player.col);
}

void print_branch(struct tile map[MAX_ROW][MAX_COL]) {
    int foliage_row, foliage_col;
    scanf("%d %d", &foliage_row, &foliage_col);
    if (foliage_row > 0 && foliage_row < MAX_ROW - 1 && 
        foliage_col > 0 && foliage_col < MAX_COL - 1) {
        map[foliage_row][foliage_col].type = BRANCH;
        printf("Branch added!\n");
    }
    else {
        printf("Invalid foliage position!\n");
    }
}

void print_bush(struct tile map[MAX_ROW][MAX_COL]) {
    int foliage_row, foliage_col;
    char direction;
    int num_bush;

    scanf("%d %d %c %d", &foliage_row, &foliage_col, &direction, &num_bush);
    if (foliage_row > 0 && foliage_row < MAX_ROW - 1 && 
        foliage_col > 0 && foliage_col < MAX_COL - 1) {
        if (direction == 'h') {
            for (int i = 0; i < num_bush; i++) {
                map[foliage_row][foliage_col + i].type = BUSH;
            }
        }
        else if (direction == 'v') {
            for (int i = 0; i < num_bush; i++) {
                map[foliage_row + i][foliage_col].type = BUSH;
            }
        }
        printf("Bush added!\n");
    }
    else {
        printf("Invalid foliage position!\n");
    }
}


// stage 2.1

void spawn_flowers(struct tile map[MAX_ROW][MAX_COL], struct position player) {
    int num_flower;
    printf("How many flowers: ");
    scanf("%d", &num_flower);
    
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
    else {
        for (int count = 0; count < num_flower; count++) {
            int flower_row, flower_col;
            scanf("%d %d", &flower_row, &flower_col);

            if (flower_row % 2 == 1 && flower_row < MAX_ROW - 1 && 
                flower_col % 2 == 1 && flower_col < MAX_COL -1 && 
                map[flower_row][flower_col].type == EMPTY)
            {
                map[flower_row][flower_col].type = FLOWER;
                map[flower_row][flower_col].flower.state = DORMANT;
            }
            else {
                printf("Invalid flower position!\n");
            }
        }
    }

    print_map(map, player.row, player.col);
}

// stage 2.2

void action(struct tile map[MAX_ROW][MAX_COL], struct position player) {
    char command;
    printf("Game Started!\nEnter command: ");
    int return_val = scanf(" %c", &command);

    while (return_val == 1) {
        if (command == 'c') {
            player = cut_flower(map, player);
            alert_branch(map, player);
        }
        else {
            player = move_player(map, player, command);
            alert_flower(map, player, command);
        }
        print_map(map, player.row, player.col);

        printf("Enter command: ");
        return_val = scanf(" %c", &command);
    }
}

struct position move_player(struct tile map[MAX_ROW][MAX_COL], struct position player, char command) {
    if (command == 'w') {
        if (player.row - 1 >= 0 && map[player.row - 1][player.col].type == EMPTY) {
            player.row--;
        }
        else if (player.row - 1 >= 0 && map[player.row - 1][player.col].type == BRANCH) {
            map[player.row - 1][player.col].type = EMPTY;
            player.row--;
        }
    }

    else if (command == 's') {
        if (player.row + 1 < MAX_ROW && map[player.row + 1][player.col].type == EMPTY) {
            player.row++;
        }
        else if (player.row + 1 < MAX_ROW && map[player.row + 1][player.col].type == BRANCH) {
            map[player.row + 1][player.col].type = EMPTY;
            player.row++;
        }
    }

    else if (command == 'a') {
        if (player.col - 1 >= 0 && map[player.row][player.col - 1].type == EMPTY) {
            player.col--;
        }
        else if (player.col - 1 >= 0 && map[player.row][player.col - 1].type == BRANCH) {
            map[player.row][player.col - 1].type = EMPTY;
            player.col--;
        }
    }

    else if (command == 'd') {
        if (player.col + 1 < MAX_COL && map[player.row][player.col + 1].type == EMPTY) {
            player.col++;
        }
        else if (player.col + 1 < MAX_COL && map[player.row][player.col + 1].type == BRANCH) {
            map[player.row][player.col + 1].type = EMPTY;
            player.col++;
        }
    }

    return player;
}

struct position cut_flower(struct tile map[MAX_ROW][MAX_COL], struct position player) {
    char command;
    scanf(" %c", &command);
    if (command == 'w') {
        if (player.row - 1 >= 0 && map[player.row - 1][player.col].type == FLOWER) {
            map[player.row - 1][player.col].type = EMPTY;
        }
        else if (player.row - 1 >= 0 && map[player.row - 1][player.col].type == BUSH) {
            map[player.row - 1][player.col].type = EMPTY;
        }
    }

    else if (command == 's') {
        if (player.row + 1 < MAX_ROW && map[player.row + 1][player.col].type == FLOWER) {
            map[player.row + 1][player.col].type = EMPTY;
        }
        else if (player.row + 1 < MAX_ROW && map[player.row + 1][player.col].type == BUSH) {
            map[player.row + 1][player.col].type = EMPTY;
        }
    }

    else if (command == 'a') {
        if (player.col - 1 >= 0 && map[player.row][player.col - 1].type == FLOWER) {
            map[player.row][player.col - 1].type = EMPTY;
        }
        else if (player.col - 1 >= 0 && map[player.row][player.col - 1].type == BUSH) {
            map[player.row][player.col - 1].type = EMPTY;
        }
    }

    else if (command == 'd') {
        if (player.col + 1 < MAX_COL && map[player.row][player.col + 1].type == FLOWER) {
            map[player.row][player.col + 1].type = EMPTY;
        }
        else if (player.col + 1 < MAX_COL && map[player.row][player.col + 1].type == BUSH) {
            map[player.row][player.col + 1].type = EMPTY;
        }
    }

    return player;
}

// 2.4
struct tile alert_branch(struct tile map[MAX_ROW][MAX_COL], struct position player) {
    if (map[player.row][player.col].type == BRANCH) {
        for (int alert_row = player.row - 2; alert_row <= player.row + 2; alert_row++) {
            for (int alert_col = player.col - 2; alert_col <= player.row + 2; alert_col++) {
                if (alert_row >= 0 && alert_row < MAX_ROW && alert_col >= 0 && 
                    alert_col < MAX_COL && map[alert_row][alert_col].type == FLOWER ) 
                {
                    if (map[alert_row][alert_col].flower.state == DORMANT) {
                        map[alert_row][alert_col].flower.state = DISTURBED;
                    }
                    else if (map[alert_row][alert_col].flower.state == DISTURBED) {
                        map[alert_row][alert_col].flower.state = AWAKENED;
                    }
                }
            }
        }
    }

    return map[player.row][player.col];
}

struct tile alert_flower(struct tile map[MAX_ROW][MAX_COL], struct position player, char command)
{
    int alert_row = -1, alert_col = -1;
    if (command == 'w') {
        alert_row = player.row - 1;
        alert_col = player.col;
    }
    else if (command == 's') {
        alert_row = player.row + 1;
        alert_col = player.col;
    }
    else if (command == 'a') {
        alert_row = player.row;
        alert_col = player.col - 1;
    }
    else if (command == 'd') {
        alert_row = player.row;
        alert_col = player.col + 1;
    }

    if (map[alert_row][alert_col].type == FLOWER) {
        for (alert_row = alert_row - 2; alert_row <= player.row + 2; alert_row++) {
            for (alert_col = player.col - 2; alert_col <= player.row + 2; alert_col++) {
                if (alert_row >= 0 && alert_row < MAX_ROW && alert_col >= 0 && 
                    alert_col < MAX_COL && map[alert_row][alert_col].type == FLOWER ) 
                {
                    if (map[alert_row][alert_col].flower.state == DORMANT) {
                        map[alert_row][alert_col].flower.state = DISTURBED;
                    }
                    else if (map[alert_row][alert_col].flower.state == DISTURBED) {
                        map[alert_row][alert_col].flower.state = AWAKENED;
                    }
                }
            }
        }
    }

    return map[player.row][player.col];
}







































// Provided Functions

//       ██████     ██████    ███████    ████████
//      ██            ██      ██            ██   
//      ██   ███      ██      █████         ██   
//      ██    ██      ██      ██            ██   
//       ██████     ██████    ██            ██   


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

