// stellar_information.c
//
// This program simulates a star system in space
//
// Written by Ruikang Xiao, z5473233

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CONVERSION_CONSTANT 9.461e12
#define LIGHT_SPEED 299792.458

// Done: TASK 1
struct star {
    char name[50];
    double distance;
    char spectral_type;
};

void print_star_information(struct star *star);
void input_star_information(struct star *star);
double time_travel(struct star *star);
void remove_newline_char(char *str);

int main() {
    // Done: TASK 2
    struct star *star_ptr;

    star_ptr = malloc(sizeof(struct star));

    input_star_information(star_ptr);
    print_star_information(star_ptr);

    return 0;
}

// Takes in the stars information
void input_star_information(struct star *star) {
    // Done: TASK 3
    printf("Enter the star's name: ");
    fgets(star->name, sizeof(star->name), stdin);

    remove_newline_char(star->name);
    printf("Enter the star's distance from Earth (in light-years): ");
    
    scanf("%lf", &(star->distance));
    printf("Enter the star's spectral type: ");
    
    scanf(" %c", &(star->spectral_type));
}

// Estimate travel time from Earth to the star based on star's distance
double time_travel(struct star *star) {
    // Done: TASK 4
    double distance_km = star->distance * CONVERSION_CONSTANT;
    double travel_time = distance_km / LIGHT_SPEED;
    return travel_time;
}


// Prints the stars information
void print_star_information(struct star *star) {
    // Done: TASK 5
    double travel_time = time_travel(star);
    printf("\nStar's Information:\n");
    printf("Name: %s\n", star->name);
    printf("Distance: %.6lf light-years\n", star->distance);
    printf("Spectral Type: %c\n", star->spectral_type);
    printf("Estimated travel time from Earth: %.2lf seconds\n", travel_time);
}

void remove_newline_char(char *str) {
    if (str[strlen(str) - 1] == '\n') {
        str[strlen(str) - 1] = '\0';
    }
}