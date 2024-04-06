// Assignment 2 24T1 COMP1511: Crepe Stand
// crepe_stand.c
//
// This program was written by z5555555
// on YYYY-MM-DD
//
// Version 1.0.0: Assignment released.
//
// DESCRIPTION OF YOUR PROGRAM HERE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "crepe_stand.h"

#define SIG_STRAWBERRY 's'
#define SIG_MATCHA 'm'
#define SIG_CHOCOLATE 'c'
#define NO_SIG_SOLD 'n'
#define NO_SIG_MOST_POP 'N'

// Add any extra #includes your code needs here.


// Your enums go here:


// Add your own #defines here:


////////////////////////////////////////////////////////////////////////////////

// A single crepe
//      Stores all the information about a single crepe.
//      Forms a linked list of crepes by pointing to the next one (or NULL).
struct crepe {
    // Name of the customer who ordered the crepe
    char customer_name[MAX_STR_LEN];

    // The batter the crepe will be made out of
    // ORIGINAL, CHOCOLATE or MATCHA
    enum batter_type batter;

    // There can be no topping or one topping
    // NO_TOPPING, BANANA, STRAWBERRY, NUTELLA
    enum topping_type topping;

    // Whether or not the crepe is gluten free;
    // Can be 1 or 0
    int is_gluten_free;

    // Size of the crepe in centimeters
    int diameter_cm;

    // A pointer to the next crepe in the orders list
    // Is NULL if this crepe is the tail of the list.
    struct crepe *next;
};

// A particular day’s list of orders
struct day {
    // Date of the day as a struct day, with fields year, month, day
    struct date date;

    // A pointer to the start of the list of this day's orders
    struct crepe *orders;

    // The total income for the day
    // i.e. the total summed price of all crepes
    double income;

    // A pointer to the next day's orders
    // Is NULL if this day is the tail of the list.
    struct day *next;
};

// Add any other structs you define here.

////////////////////////////////////////////////////////////////////////////////

// Add prototypes for any extra functions you create here.

// Stage 1


// Creates a new custom crepe
//
// Parameters:
//      customer_name - name of customer ordering
//      batter - batter base of crepe
//      topping - topping for the crepe
//      is_gluten_free - 1 if it is GF, 0 if not
//      diameter_cm - how large crepe is in cm
// Returns:
//      pointer to newly created struct crepe
//
struct crepe *create_crepe(char *customer_name,
                           enum batter_type batter,
                           enum topping_type topping,
                           int is_gluten_free,
                           int diameter_cm);


// Stage 2


// Stage 3


// Stage 4


// You need to implement the following functions.
// You can find descriptions of what each function
// should do in crepe_stand.h

//////////////////////////////////////////////////////////////////////
//                        Stage 1 Functions                         //
//////////////////////////////////////////////////////////////////////

// Provided Function stubs:

struct day *create_day(struct date new_date) {
    // TODO: implement this function
    printf("Create Day not yet implemented.\n");
    exit(1);
}

struct crepe *create_crepe(char *customer_name,
                           enum batter_type batter,
                           enum topping_type topping,
                           int is_gluten_free,
                           int diameter_cm) {
    // TODO: implement this function
    printf("Create Crepe not yet implemented.\n");
    exit(1);
}

int append_crepe_custom(struct day *current_day,
                        char *customer_name,
                        enum batter_type batter,
                        enum topping_type topping,
                        int is_gluten_free,
                        int diameter_cm) {
    // TODO: implement this function
    printf("Append Crepe Custom not yet implemented.\n");
    exit(1);
}

int append_crepe_signature(struct day *current_day,
                           char *customer_name,
                           char *crepe_type) {
    // TODO: implement this function
    printf("Append Crepe Signature not yet implemented.\n");
    exit(1);
}

void print_crepes(struct day *current_day) {
    // TODO: implement this function
    printf("Print Crepes not yet implemented.\n");
    exit(1);
}

int count_crepes(struct day *current_day) {
    // TODO: implement this function
    printf("Count Crepes not yet implemented.\n");
    exit(1);
}

// Your functions go here (include function comments):


//////////////////////////////////////////////////////////////////////
//                        Stage 2 Functions                         //
//////////////////////////////////////////////////////////////////////

// Provided function stubs:

int insert_crepe_custom(struct day *current_day,
                        int position,
                        char *customer_name,
                        enum batter_type batter,
                        enum topping_type topping,
                        int is_gluten_free,
                        int diameter_cm) {
    // TODO: implement this function
    printf("Insert Crepe Custom not yet implemented.\n");
    exit(1);
}

int insert_crepe_signature(struct day *current_day,
                           int position,
                           char *customer_name,
                           char *crepe_type) {
    // TODO: implement this function
    printf("Insert Crepe Signature not yet implemented.\n");
    exit(1);
}

struct stats get_stats(struct day *current_day) {
    // TODO: implement this function
    printf("Get Stats not yet implemented.\n");
    exit(1);
}

double calculate_price(struct day *current_day, int position) {
    // TODO: implement this function
    printf("Calculate Price not yet implemented.\n");
    exit(1);
}

double total_income(struct day *current_day) {
    // TODO: implement this function
    printf("Total Income not yet implemented.\n");
    exit(1);
}

struct bill customer_bill(struct day *current_day, char *customer_name) {
    // TODO: implement this function
    printf("Customer Bill not yet implemented.\n");
    exit(1);
}

// Your functions go here (include function comments):


//////////////////////////////////////////////////////////////////////
//                        Stage 3 Functions                         //
//////////////////////////////////////////////////////////////////////

// Provided function stubs:

struct day *new_day(struct day *day_one, struct date date) {
    // TODO: implement this function
    printf("New Day not yet implemented.\n");
    exit(1);
}

void display_days(struct day *day_one, struct day *current_day) {
    // TODO: implement this function
    printf("Display Days not yet implemented.\n");
    exit(1);
}

struct day *cycle_days(char command,
                       struct day *day_one,
                       struct day *current_day) {
    // TODO: implement this function
    printf("Cycle Days not yet implemented.\n");
    exit(1);
}

int remove_crepe(struct day *current_day, int position) {
    // TODO: implement this function
    printf("Remove Crepe not yet implemented.\n");
    exit(1);
}

struct day *remove_day(struct day *day_one,
                       struct day **current_day,
                       struct date date) {
    // TODO: implement this function
    printf("Remove Day not yet implemented.\n");
    exit(1);
}

void free_crepe_stand(struct day *day_one) {
    // TODO: implement this function
}

// Your functions here (include function comments):


//////////////////////////////////////////////////////////////////////
//                        Stage 4 Functions                         //
//////////////////////////////////////////////////////////////////////

// Provided function stubs:

struct profits compare_weekday_end(struct day *day_one) {
    // TODO: implement this function
    printf("Compare Weekday end not yet implemented.\n");
    exit(1);
}

struct max_profit max_profit_period(struct day *day_one, int year) {
    // TODO: implement this function
    printf("Max Profit Period not yet implemented.\n");
    exit(1);
}

// Your functions here (include function comments):


//////////////////////////////////////////////////////////////////////
//                         Helper Functions                         //
//////////////////////////////////////////////////////////////////////

void print_single_crepe(struct crepe *crepe, int position) {
    printf("---------------------\n");
    printf("%d. %s's crepe\n", position, crepe->customer_name);

    if (crepe->batter == ORIGINAL) {
        printf("Original flavour\n");
    } else if (crepe->batter == MATCHA) {
        printf("Matcha flavour\n");
    } else {
        printf("Chocolate flavour\n");
    }

    printf("Toppings: ");
    if (crepe->topping == NO_TOPPING) {
        printf("none\n");
    } else if (crepe->topping == BANANA) {
        printf("bananas\n");
    } else if (crepe->topping == STRAWBERRY) {
        printf("strawberries\n");
    } else if (crepe->topping == NUTELLA) {
        printf("nutella\n");
    }

    printf("gluten free? ");
    if (crepe->is_gluten_free) {
        printf("yes\n");
    } else {
        printf("no\n");
    }

    printf("Size: %dcm\n", crepe->diameter_cm);
    printf("---------------------\n");
}

void print_arrow(void) {
    printf("\t|\n\tv\n");
}

void print_no_crepes(void) {
    printf("No crepes have been ordered yet!\n");
}

void print_single_day(int is_current_day,
                      struct date date,
                      char most_pop,
                      double income) {
    printf("---------------------\n");
    if (is_current_day) {
        printf("!CURRENT DAY!\n");
    }
    printf("Date: %04d-%02d-%02d\n", date.year, date.month, date.day);
    if (most_pop == SIG_STRAWBERRY) {
        printf("Most popular signature crepe: Strawberry Special\n");
    } else if (most_pop == SIG_MATCHA) {
        printf("Most popular signature crepe: Matcha Madness\n");
    } else if (most_pop == SIG_CHOCOLATE) {
        printf("Most popular signature crepe: Chocolate Connoisseur\n");
    } else if (most_pop == NO_SIG_SOLD) {
        printf("There were no signature crepes sold!\n");
    } else if (most_pop == NO_SIG_MOST_POP) {
        printf("No signature crepe was more popular than another!\n");
    } else {
        printf("ERROR: %c, unknown most popular character\n", most_pop);
    }
    printf("Total income: $%.2lf\n", income);
    printf("---------------------\n");
}
