// Planter
// planter.c
//
// This program was written by Ruikang Xiao (z5473233)
// on 20 March 2024
//
// The program is a garden simulator that uses a 2D array


/*

*/
#include <stdio.h>

#define GARDEN_ROWS 5
#define GARDEN_COLS 5
#define TRUE 1
#define FALSE 0

/*
Provided enum flowers
DO NOT MODIFY THIS ENUM
*/
enum flowers {
    EMPTY,
    DAISY,
    ROSE,
    TULIP
};

/*
Provided struct garden 
DO NOT MODIFY THIS STRUCT
*/
struct garden {
    enum flowers flower;
    int bloom_countdown;
    int is_gardener;
};


/*
provided function prototypes
DO NOT MODIFY THESE FUNCTION PROTOTYPES
*/
void print_garden(struct garden garden[GARDEN_ROWS][GARDEN_COLS]);
int grow_garden(struct garden garden[GARDEN_ROWS][GARDEN_COLS]);

int main(void)
{
    struct garden garden_case[GARDEN_ROWS][GARDEN_COLS];
    int option;
    int flower_row = 0;
    int flower_col = 0;
    printf("Welcome to the planter!\n");

    for (flower_row = 0; flower_row < GARDEN_ROWS; flower_row++)
    {
        for (flower_col = 0; flower_col < GARDEN_COLS; flower_col++)
        {
            garden_case[flower_row][flower_col].flower = EMPTY;
            garden_case[flower_row][flower_col].bloom_countdown = 0;
            garden_case[flower_row][flower_col].is_gardener = FALSE;
        }
    }

    int flower_status = 0;

    for (flower_row = 0; flower_row < GARDEN_ROWS; flower_row++)
    {
        garden_case[flower_row][0].is_gardener = TRUE;

        print_garden(garden_case);
        // Provided printf statements to help you get started
        printf(
            "0. Nothing\n"
            "1. Daisy\n"
            "2. Rose\n"
            "3. Tulip\n"
            "Which Flower would you like to plant in this row? ");

        scanf("%d", &option);

        if (option == 0)
        {
            garden_case[flower_row][0].is_gardener = FALSE;
        }
        else if (option == 1)
        {
            for (int flower_col = 0; flower_col < GARDEN_COLS; flower_col++)
            {
                garden_case[flower_row][flower_col].flower = DAISY;
                garden_case[flower_row][flower_col].bloom_countdown = 4;
            }
        }
        else if (option == 2)
        {
            for (int flower_col = 0; flower_col < GARDEN_COLS; flower_col++)
            {
                garden_case[flower_row][flower_col].flower = ROSE;
                garden_case[flower_row][flower_col].bloom_countdown = 4;
            }
        }
        else if (option == 3)
        {
            for (int flower_col = 0; flower_col < GARDEN_COLS; flower_col++)
            {
                garden_case[flower_row][flower_col].flower = TULIP;
                garden_case[flower_row][flower_col].bloom_countdown = 4;
            }
        }

        flower_status = grow_garden(garden_case);
        garden_case[flower_row][0].is_gardener = FALSE;
    }
    print_garden(garden_case);

    while (flower_status != 1)
    {
        if (grow_garden(garden_case) == 1)
        {
            printf("Waiting for flowers to bloom...\n");
            print_garden(garden_case);
            break;
        }

        printf("Waiting for flowers to bloom...\n");

        print_garden(garden_case);
    }

    return 0;
}



/*
    Decreases the bloom_countdown for all flowers in the garden
    Parameters:
        garden: a 2D array of struct garden
    Returns:
        int: returns 1 if a flower has grown, 0 otherwise
*/

int grow_garden(struct garden garden[GARDEN_ROWS][GARDEN_COLS]) {
    int count = 0;
    for (int garden_col = 0; garden_col < GARDEN_ROWS; garden_col++) {
        for (int garden_rows = 0; garden_rows < GARDEN_COLS; garden_rows++) {
            if (garden[garden_col][garden_rows].bloom_countdown > 0) {
                garden[garden_col][garden_rows].bloom_countdown = garden[garden_col][garden_rows].bloom_countdown - 1;
            }
            count = count + garden[garden_col][garden_rows].bloom_countdown;
        }
    }
    if (count == 0) {
        return 1;
    }

    return 0;
}


/////////////////////////////////////////////////////////////////////////////
//////////////////// DO NOT MODIFY ANYTHING BELOW THIS LINE ////////////////////
////////////////////////////////////////////////////////////////////////////////

/*
    Prints the garden to the terminal
    Parameters:
        garden: a 2D array of struct garden
    Returns:
        void
*/
void print_garden(struct garden garden[GARDEN_ROWS][GARDEN_COLS]) {
    printf("\n");
    for (int i = 0; i < GARDEN_ROWS; i++) {
        for (int j = 0; j < GARDEN_COLS; j++) {
            if (garden[i][j].is_gardener) {
                printf("# ");
            } else if (garden[i][j].flower == EMPTY) {
                printf(". ");
            } else if (garden[i][j].bloom_countdown > 0) {
                printf("%d ", garden[i][j].bloom_countdown);
            } else if (garden[i][j].flower == DAISY) {
                printf("D ");
            } else if (garden[i][j].flower == ROSE) {
                printf("R ");
            } else if (garden[i][j].flower == TULIP) {
                printf("T ");
            } else {
                printf(". ");
            }
        }
        printf("\n");
    }
    printf("\n");
}