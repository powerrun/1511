// Assignment 2 24T1 COMP1511: Crepe Stand
// crepe_stand.c
//
// DESCRIPTION:
// This is a crepe order tracker that records and provides information about
// the daily sales of crepes, the amount sold, and the bills.
// The programme also provides operations on date and orders.
// Furthermore, this program can provide some insights on profits
// by asking Zeller and his formula.
// :)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "crepe_stand.h"


#define SIG_STRAWBERRY 's'
#define SIG_MATCHA 'm'
#define SIG_CHOCOLATE 'c'
#define NO_SIG_SOLD 'n'
#define NO_SIG_MOST_POP 'N'

#define ZERO 0
#define FIRST 1
#define TRUE 1
#define FALSE 0

#define ALL_TOPPING_TYPES 4
#define MEDIUM 25
#define SIZE_10CM 10
#define SIZE_20CM 20
#define SIZE_30CM 30
#define SIZE_40CM 40

#define PRICE_BASIC_BATTER 8
#define PRICE_MATCHA_BATTER 9.5
#define PRICE_FRUIT_TOPPING 2
#define PRICE_NUTELLA_TOPPING 3.5
#define PRICE_GFO 0.6
#define PRICE_MEDIUM_SIZE 2.5
#define PRICE_LARGE_SIZE 3.5

#define NEXT_DAY '>'
#define PREV_DAY '<'

#define MONDAY 2
#define FRIDAY 6

#define WEEKDAY_COST 35
#define WEEKEND_COST 50


// Structs

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

// Prototypes:

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

int validate_crepe(enum batter_type batter,
                   enum topping_type topping,
                   int is_gluten_free,
                   int diameter_cm);

int valid_batter(enum batter_type batter);

int valid_topping(enum topping_type topping);

int valid_gfo(int is_gluten_free);

int valid_size(int diameter_cm);

struct crepe *create_sig_crepe(char *customer_name, char *crepe_type);

int append_crepe(struct day *current_day,
                 struct crepe *current_crepe,
                 struct crepe *new_crepe);

int insert_order_specific_position(struct day *current_day,
                                   struct crepe *new_crepe,
                                   int position);

struct stats count_batter(struct stats *stats, struct crepe *current_crepe);

struct stats count_size(struct stats *stats, struct crepe *current_crepe);

struct stats count_gluten_free(struct stats *stats,
                               struct crepe *current_crepe);

struct stats find_pop_topping(struct stats *stats, int *topping_counts);

double get_crepe_price(struct crepe *current_crepe);

void count_signature_crepe(struct crepe *current_crepe,
                           int *strawberry_count,
                           int *matcha_count,
                           int *chocolate_count);

char find_most_pop_sig(int strawberry_count,
                       int matcha_count,
                       int chocolate_count);

int is_date_equal(struct date date1, struct date date2);

int ask_zeller_weekend(struct day *current_day);

struct profits calculate_profit(struct profits profit,
                                int is_weekend,
                                double income);

// Functions:

// Create a new day with the given date
struct day *create_day(struct date new_date) {
    struct day *new_day = malloc(sizeof(struct day));

    // Initialize values of new_day
    new_day->date = new_date;
    new_day->orders = NULL;
    new_day->income = ZERO;
    new_day->next = NULL;

    return new_day;
}

// Add a new custom crepe to the end of the orders list
struct crepe *create_crepe(char *customer_name,
                           enum batter_type batter,
                           enum topping_type topping,
                           int is_gluten_free,
                           int diameter_cm) {
    struct crepe *new_crepe = malloc(sizeof(struct crepe));

    // Copy the customer name into the new crepe
    strcpy(new_crepe->customer_name, customer_name);

    // Initialize other values of new_crepe
    new_crepe->batter = batter;
    new_crepe->topping = topping;
    new_crepe->is_gluten_free = is_gluten_free;
    new_crepe->diameter_cm = diameter_cm;
    new_crepe->next = NULL;

    return new_crepe;
}

// Append a new custom crepe to the end of the orders list
int append_crepe_custom(struct day *current_day,
                        char *customer_name,
                        enum batter_type batter,
                        enum topping_type topping,
                        int is_gluten_free,
                        int diameter_cm) {

    // Validate values of the crepe
    int validation = validate_crepe(batter,
                                    topping,
                                    is_gluten_free,
                                    diameter_cm);
    if (validation != VALID_CREPE) {
        return validation;
    }

    // Create a new crepe
    struct crepe *current_crepe = current_day->orders;
    struct crepe *new_crepe = create_crepe(customer_name,
                                           batter,
                                           topping,
                                           is_gluten_free,
                                           diameter_cm);

    return append_crepe(current_day, current_crepe, new_crepe);
}

// Append a new signature crepe to the end of the orders list
int append_crepe_signature(struct day *current_day,
                           char *customer_name,
                           char *crepe_type) {
    struct crepe *new_crepe = create_sig_crepe(customer_name, crepe_type);
    struct crepe *current_crepe = current_day->orders;

    // Append new signature crepe
    return append_crepe(current_day, current_crepe, new_crepe);
}

// Print all the crepes orders at a given day
void print_crepes(struct day *current_day) {
    // Point to the first crepe
    struct crepe *current_crepe = current_day->orders;

    // If there are no crepes, print a message and return
    if (current_crepe == NULL) {
        print_no_crepes();
    }

    int position = FIRST;

    // Print each crepe in the list
    while (current_crepe != NULL) {
        print_single_crepe(current_crepe, position);

        // Print arrow(s) for multiple crepes
        if (current_crepe->next != NULL) {
            print_arrow();
        }

        // Move to the next crepe
        current_crepe = current_crepe->next;
        position++;
    }
}

// Count the number of crepes in the orders list
int count_crepes(struct day *current_day) {
    // Get the first crepe in the list
    struct crepe *current_crepe = current_day->orders;
    int count;

    // Count the number of crepes
    for (count = ZERO; current_crepe != NULL; count++) {
        current_crepe = current_crepe->next;
    }
    return count;
}

// Create a new signature crepe based on the matched type
struct crepe *create_sig_crepe(char *customer_name, char *crepe_type) {
    if (strcmp(crepe_type, "matcha") == SUCCESS) {
        return create_crepe(customer_name,
                            MATCHA,
                            STRAWBERRY,
                            FALSE,
                            MEDIUM);
    }

    if (strcmp(crepe_type, "strawberry") == SUCCESS) {
        return create_crepe(customer_name,
                            ORIGINAL,
                            STRAWBERRY,
                            TRUE,
                            MEDIUM);
    }

    if (strcmp(crepe_type, "chocolate") == SUCCESS) {
        return create_crepe(customer_name,
                            CHOCOLATE,
                            NUTELLA,
                            FALSE,
                            MEDIUM);
    }

    return NULL;
}

// Validate values of the crepe
int validate_crepe(enum batter_type batter,
                   enum topping_type topping,
                   int is_gluten_free,
                   int diameter_cm) {

    if (!valid_batter(batter)) {
        return INVALID_BATTER;
    }

    if (!valid_topping(topping)) {
        return INVALID_TOPPING;
    }

    if (!valid_gfo(is_gluten_free)) {
        return INVALID_GFO;
    }

    if (!valid_size(diameter_cm)) {
        return INVALID_SIZE;
    }

    // If all values are valid, return VALID_CREPE
    return VALID_CREPE;
}

// Validate the batter type
int valid_batter(enum batter_type batter) {
    return (batter == ORIGINAL || batter == CHOCOLATE || batter == MATCHA);
}

// Validate the topping type
int valid_topping(enum topping_type topping) {
    return (topping == NO_TOPPING || topping == BANANA ||
            topping == STRAWBERRY || topping == NUTELLA);
}

// Validate the gluten free option
int valid_gfo(int is_gluten_free) {
    return (is_gluten_free == TRUE || is_gluten_free == FALSE);
}

// Validate size of the crepe
int valid_size(int diameter_cm) {
    return (diameter_cm >= SIZE_10CM && diameter_cm <= SIZE_40CM);
}

// Append a new crepe to the end of the orders list
int append_crepe(struct day *current_day,
                 struct crepe *current_crepe,
                 struct crepe *new_crepe) {

    // If there are no crepes, just append the new crepe
    if (current_crepe == NULL) {
        current_day->orders = new_crepe;
    } else {
        // else find the last crepe then add new_crepe
        while (current_crepe->next != NULL) {
            current_crepe = current_crepe->next;
        }

        // Append the new crepe
        current_crepe->next = new_crepe;
    }

    return VALID_CREPE;
}

// Insert a new custom crepe based on a given position
int insert_crepe_custom(struct day *current_day,
                        int position,
                        char *customer_name,
                        enum batter_type batter,
                        enum topping_type topping,
                        int is_gluten_free,
                        int diameter_cm) {
    // Validate the position and crepe
    if (position < FIRST) {
        return INVALID_POSITION;
    }

    int validation = validate_crepe(batter,
                                    topping,
                                    is_gluten_free,
                                    diameter_cm);
    if (validation != VALID_CREPE) {
        return validation;
    }

    // Create a new crepe based on provided values
    struct crepe *new_crepe = create_crepe(customer_name,
                                           batter,
                                           topping,
                                           is_gluten_free,
                                           diameter_cm);

    // If position is greater than the number of crepes,
    // just append at the end.
    if (position > count_crepes(current_day)) {
        append_crepe(current_day, current_day->orders, new_crepe);
        return VALID_CREPE;
    }

    // Insert at the position that between 1 and crepes number
    return insert_order_specific_position(current_day, new_crepe, position);
}

// Insert a new signature crepe based on a given position
int insert_crepe_signature(struct day *current_day,
                           int position,
                           char *customer_name,
                           char *crepe_type) {
    // Validate the position
    if (position < 1) {
        return INVALID_POSITION;
    }

    // Create a new_crepe
    struct crepe *new_crepe = create_sig_crepe(customer_name, crepe_type);

    // If position is greater than the number of crepes,
    // append at the end
    if (position > count_crepes(current_day)) {
        append_crepe_signature(current_day, customer_name, crepe_type);
        return VALID_CREPE;
    }

    // Insert at the position that between 1 and crepes number
    return insert_order_specific_position(current_day, new_crepe, position);
}

// Statistics for the day
struct stats get_stats(struct day *current_day) {
    struct stats stats = {ZERO};
    int topping_counts[ALL_TOPPING_TYPES] = {ZERO};

    // Traverse list and update stats
    struct crepe *current_crepe = current_day->orders;

    // Count the number of crepes
    while (current_crepe != NULL) {

        // Count the number of crepes
        stats.total_crepes++;

        // Count the number of each batter
        stats = count_batter(&stats, current_crepe);

        // Count the number of gluten free crepes
        stats = count_gluten_free(&stats, current_crepe);

        // Count the number of toppings
        topping_counts[current_crepe->topping]++;

        // Count the number of each topping
        stats = count_size(&stats, current_crepe);

        // Move forward
        current_crepe = current_crepe->next;
    }

    // Find the most popular topping
    stats = find_pop_topping(&stats, topping_counts);

    return stats;
}

// Calculates the price of a crepe at a given position
double calculate_price(struct day *current_day, int position) {
    // Validate the position
    if (position < FIRST || position > count_crepes(current_day)) {
        return INVALID_POSITION;
    }

    // Find the crepe at the given position
    int count = FIRST;
    struct crepe *current_crepe = current_day->orders;

    while (count != position) {
        current_crepe = current_crepe->next;
        count++;
    }

    // Return the price
    return get_crepe_price(current_crepe);
}

// Calculates total income of a day
double total_income(struct day *current_day) {
    struct crepe *current_crepe = current_day->orders;
    double income = ZERO;
    int position = FIRST;

    while (current_crepe != NULL) {
        income += calculate_price(current_day, position);
        // Move forward
        position++;
        current_crepe = current_crepe->next;
    }
    return income;
}

// Calculate bill for a customer
struct bill customer_bill(struct day *current_day, char *customer_name) {
    struct crepe *current_crepe = current_day->orders;
    int position = ZERO;
    struct bill bill;
    bill.total_price = ZERO;
    bill.crepe_count = ZERO;

    // Traverse the list
    while (current_crepe != NULL) {
        position++;

        // Calculate the price and crepe amount for matched customer
        if (strcmp(current_crepe->customer_name, customer_name) == SUCCESS) {
            bill.total_price += calculate_price(current_day, position);
            bill.crepe_count++;
        }
        current_crepe = current_crepe->next;
    }

    return bill;
}

// Insert a new crepe into the list
int insert_order_specific_position(struct day *current_day,
                                   struct crepe *new_crepe,
                                   int position) {
    // If position is 1, insert at head
    if (position == FIRST) {
        new_crepe->next = current_day->orders;
        current_day->orders = new_crepe;
        return VALID_CREPE;
    }

    // Else find the position then insert it
    struct crepe *current_crepe = current_day->orders;
    struct crepe *prev_crepe = NULL;
    int count = 1;

    // Find the correct position
    while (current_crepe != NULL && count < position) {
        prev_crepe = current_crepe;
        current_crepe = current_crepe->next;
        count++;
    }

    // Insert the crepe
    new_crepe->next = current_crepe;
    if (prev_crepe != NULL) {
        prev_crepe->next = new_crepe;
    }

    return VALID_CREPE;
}

// Count the number of batter
struct stats count_batter(struct stats *stats, struct crepe *current_crepe) {
    // Count the number of ORIGINAL batter
    if (current_crepe->batter == ORIGINAL) {
        stats->original++;
    }

    // Count the number of CHOCOLATE batter
    if (current_crepe->batter == CHOCOLATE) {
        stats->chocolate++;
    }

    // Count the number of MATCHA batter
    if (current_crepe->batter == MATCHA) {
        stats->matcha++;
    }

    return (*stats);
}

// Count the number of size
struct stats count_size(struct stats *stats, struct crepe *current_crepe) {
    if (current_crepe->diameter_cm < SIZE_20CM) {
        stats->small++;
    } else if (current_crepe->diameter_cm < SIZE_30CM) {
        stats->medium++;
    } else {
        stats->large++;
    }

    return (*stats);
}

// Count the number of gluten free crepes
struct stats count_gluten_free(struct stats *stats,
                               struct crepe *current_crepe) {
    if (current_crepe->is_gluten_free) {
        stats->gluten_free++;
    }

    return (*stats);
}

// Find the most popular topping
struct stats find_pop_topping(struct stats *stats, int *topping_counts) {
    int pop_index = ZERO;

    for (int i = ZERO; i < ALL_TOPPING_TYPES; i++) {

        // Find the most popular topping
        // Set popular_topping to NO_TOPPING is there are multiple most popular
        // toppings or no toppings.
        if (topping_counts[i] > topping_counts[pop_index]) {
            pop_index = i;
            stats->popular_topping = pop_index;
        }
        else if (topping_counts[i] == topping_counts[pop_index]) {
            stats->popular_topping = NO_TOPPING;
        }
    }

    return (*stats);
}

// Calculate the price of a crepe
double get_crepe_price(struct crepe *current_crepe) {
    double price = ZERO;

    // Determine the price of batter
    if (current_crepe->batter == ORIGINAL ||
        current_crepe->batter == CHOCOLATE) {
        price += PRICE_BASIC_BATTER;
    } else {
        price += PRICE_MATCHA_BATTER;
    }

    // Determine the price of topping
    if (current_crepe->topping == BANANA ||
        current_crepe->topping == STRAWBERRY) {
        price += PRICE_FRUIT_TOPPING;
    } else if (current_crepe->topping == NUTELLA) {
        price += PRICE_NUTELLA_TOPPING;
    }

    // Determine the price of gluten free
    if (current_crepe->is_gluten_free == TRUE) {
        price += PRICE_GFO;
    }

    // Determine the price of size
    if (current_crepe->diameter_cm >= SIZE_20CM &&
        current_crepe->diameter_cm < SIZE_30CM) {
        price += PRICE_MEDIUM_SIZE;
    } else if (current_crepe->diameter_cm >= SIZE_30CM &&
               current_crepe->diameter_cm < SIZE_40CM) {
        price += PRICE_LARGE_SIZE;
    }

    return price;
}

// Create a new day with a date
struct day *new_day(struct day *day_one, struct date date) {
    // Create day directly if there is no day
    if (day_one == NULL) {
        day_one = create_day(date);
        return day_one;
    }

    // Create a new day that will be inserted
    struct day *current = day_one;
    struct day *previous = NULL;
    struct day *new_day = create_day(date);

    // Check if the day already exists
    if (is_date_equal(current->date, date)) {
        return NULL;
    }

    // Find the correct position to insert the new day
    int finish = FALSE;
    while (current != NULL && finish == FALSE) {
        if (current->date.year > date.year ||
            (current->date.year == date.year &&
             current->date.month > date.month) ||
            (current->date.year == date.year &&
             current->date.month == date.month &&
             current->date.day > date.day)) {
            finish = TRUE;
        }
    

        // Move forward
        if (finish == FALSE) {
            previous = current;
            current = current->next;
        }
    }

    new_day->next = current;

    // Insert the new day
    if (previous == NULL) {
        day_one = new_day;
    } else {
        previous->next = new_day;
    }

    return day_one;
}

// Display information of days
// (Date, Most popular signature crepe, Total income)
void display_days(struct day *day_one, struct day *current_day) {
    struct day *current_position = day_one;

    // Traverse the list
    while (current_position != NULL) {

        // Check if the current day is the current day :)
        int is_current_day = is_date_equal(current_day->date,
                                           current_position->date);
        int strawberry_count = ZERO;
        int matcha_count = ZERO;
        int chocolate_count = ZERO;

        struct crepe *current_crepe = current_position->orders;

        // Count signature crepe
        count_signature_crepe(current_crepe,
                              &strawberry_count,
                              &matcha_count,
                              &chocolate_count);

        // Find most pop signature crepe
        char most_popular_sig = find_most_pop_sig(strawberry_count,
                                                  matcha_count,
                                                  chocolate_count);

        // Calculate the day income
        double income = total_income(current_position);

        // Print the day information
        print_single_day(is_current_day,
                         current_position->date,
                         most_popular_sig,
                         income);

        // Move forward
        current_position = current_position->next;

        // Print arrow(s) for multiple days
        if (current_position != NULL) {
            print_arrow();
        }
    }
}

// Cycle days between days according to left and right instructions
struct day *cycle_days(char command,
                       struct day *day_one,
                       struct day *current_day) {
    // check next day
    if (command == NEXT_DAY) {
        // when traverse to the tail
        if (current_day->next == NULL) {
            return day_one;
            // when traverse between head and tail
        } else {
            return current_day->next;
        }
    }

    // check previous day
    if (command == PREV_DAY) {
        // when traverse to the head
        if (current_day == day_one) {
            // find the tail
            while (current_day->next != NULL) {
                current_day = current_day->next;
            }
            return current_day;
            // when traverse between head and tail
        } else {
            struct day *previous_day = day_one;
            while (previous_day->next != current_day) {
                previous_day = previous_day->next;
            }
            return previous_day;
        }
    }
    return NULL;
}

// Remove a crepe from the list
int remove_crepe(struct day *current_day, int position) {
    struct crepe *current_crepe = current_day->orders;
    // Count number of crepes
    int count = count_crepes(current_day);

    // Handling errors
    if (current_crepe == NULL || position < FIRST || position > count) {
        return INVALID_POSITION;
    }

    struct crepe *prev_crepe = NULL;
    int current_position = 1;

    // Find the correct position
    while (current_position < position && current_crepe != NULL) {
        prev_crepe = current_crepe;
        current_crepe = current_crepe->next;
        current_position++;
    }

    // Remove the order and update the linked list
    if (prev_crepe != NULL) {
        // Link previous crepe to the next of current crepe
        prev_crepe->next = current_crepe->next;
    } else {
        // Let the head point to the next crepe
        current_day->orders = current_crepe->next;
    }

    // Free the removed crepe
    free(current_crepe);

    return VALID_CREPE;
}

// Removes a day from the list
struct day *remove_day(struct day *day_one,
                       struct day **current_day,
                       struct date date) {
    struct day *current = day_one;
    struct day *previous = NULL;

    // Traverse the list to find the correct day
    while (current != NULL && !is_date_equal(current->date, date)) {
        previous = current;
        current = current->next;
    }

    // If the day does not exist, return NULL
    if (current == NULL) {
        return NULL;
    }

    // Update the current day
    if (*current_day == current) {
        if (current->next) {
            *current_day = current->next;
        } else {
            *current_day = NULL;
        }
    }

    // Update the linked list
    if (previous) {
        previous->next = current->next;
    } else {
        day_one = current->next;
    }

    // Free removed node
    struct crepe *crepe = current->orders;
    while (crepe != NULL) {
        struct crepe *next_crepe = crepe->next;
        free(crepe);
        crepe = next_crepe;
    }
    free(current);

    // Create the default day if the list is empty
    if (day_one == NULL) {
        struct date default_date = {2024, 1, 1};
        day_one = create_day(default_date);
        *current_day = day_one;
    }

    // Return the head of the list
    return day_one;
}

// Free the memory of the linked list
void free_crepe_stand(struct day *day_one) {
    // Traverse the list and free all nodes
    while (day_one != NULL) {
        // point to the new next day
        struct day *next_day = day_one->next;

        // Free all crepes for the current day
        struct crepe *crepe = day_one->orders;
        while (crepe != NULL) {
            struct crepe *next_crepe = crepe->next;
            free(crepe);
            crepe = next_crepe;
        }

        // Free the day_one then move to the next day
        free(day_one);
        day_one = next_day;
    }
}

// Compare if two dates are equal
int is_date_equal(struct date date1, struct date date2) {
    return (date1.year == date2.year &&
            date1.month == date2.month &&
            date1.day == date2.day);
}

// Counts the number of each signature crepe
void count_signature_crepe(struct crepe *current_crepe,
                           int *strawberry_count,
                           int *matcha_count,
                           int *chocolate_count) {
    while (current_crepe != NULL) {
        // Count the number of STRAWBERRY sig crepe
        if (current_crepe->batter == ORIGINAL &&
            current_crepe->topping == STRAWBERRY &&
            current_crepe->is_gluten_free == TRUE &&
            current_crepe->diameter_cm == MEDIUM) {
            (*strawberry_count)++;
        }

        // Count the number of MATCHA sig crepe
        if (current_crepe->batter == MATCHA &&
            current_crepe->topping == STRAWBERRY &&
            current_crepe->is_gluten_free == FALSE &&
            current_crepe->diameter_cm == MEDIUM) {
            (*matcha_count)++;
        }

        // Count the number of CHOCOLATE sig crepe
        if (current_crepe->batter == CHOCOLATE &&
            current_crepe->topping == NUTELLA &&
            current_crepe->is_gluten_free == FALSE &&
            current_crepe->diameter_cm == MEDIUM) {
            (*chocolate_count)++;
        }
        // Move forward
        current_crepe = current_crepe->next;
    }
}

// Find the most popular signature crepe
char find_most_pop_sig(int strawberry_count,
                       int matcha_count,
                       int chocolate_count) {
    // MATCHA is the most popular
    if (matcha_count > strawberry_count &&
        matcha_count > chocolate_count) {
        return SIG_MATCHA;
    }

    // STRAWBERRY is the most popular
    if (strawberry_count > matcha_count &&
        strawberry_count > chocolate_count) {
        return SIG_STRAWBERRY;
    }

    // CHOCOLATE is the most popular
    if (chocolate_count > strawberry_count &&
        chocolate_count > matcha_count) {
        return SIG_CHOCOLATE;
    }

    // No signature crepe was sold or no crepe was more popular than another
    if (chocolate_count == ZERO &&
        strawberry_count == ZERO &&
        matcha_count == ZERO) {
        return NO_SIG_SOLD;
    } else {
        return NO_SIG_MOST_POP;
    }
}

// Calculate the total profits during all weekdays
// and all weekends separately
struct profits compare_weekday_end(struct day *day_one) {
    struct profits profit = {ZERO, ZERO};
    struct day *current_day = day_one;

    while (current_day != NULL) {

        // Find out if a day is a weekend by asking Zeller and his formula :)
        int is_weekend = ask_zeller_weekend(current_day);

        // Calculate the total income of the day
        double income = total_income(current_day);

        // Calculate the profit
        profit = calculate_profit(profit, is_weekend, income);

        current_day = current_day->next;
    }

    return profit;
}

// Traverse the list of days to find the maximum profit period
struct max_profit max_profit_period(struct day *day_one, int year) {
    exit(1);
}

// Calculate the day of the week then return whether the day is a weekend
int ask_zeller_weekend(struct day *current_day) {
    // Calculate the day of the week by Common simplification form of
    // Zeller's Congruence.
    // https://en.wikipedia.org/wiki/Zeller%27s_congruence
    int day = current_day->date.day;
    int month = current_day->date.month + 12;
    int year = current_day->date.year - 1;
    int day_of_week = (day + (13 * (month + 1) / 5) + year + (year / 4) -
                       (year / 100) + (year / 400)) % 7;

    // Determine if the day is a weekend
    // 0 = Saturday, 1 = Sunday
    // 2 = Monday, ..., 6 = Friday
    if (day_of_week >= MONDAY && day_of_week <= FRIDAY) {
        return FALSE;
    } else {
        return TRUE;
    }
}

// Calculate the profit of a day and based on the income
// and whether the day is a weekend
struct profits calculate_profit(struct profits profit,
                                int is_weekend,
                                double income) {
    if (is_weekend) {
        profit.weekend += (income - WEEKEND_COST);
    } else {
        profit.weekday += (income - WEEKDAY_COST);
    }
    return profit;
}

// Helper Functions

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
