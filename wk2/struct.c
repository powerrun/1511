#include <stdio.h>

// Define a struct outside our main
struct friendship {
    int num_beads;
    int letter_beads;
    double size;
    char initial;
};

int main(void) {
    // Declare using the struct
    struct friendship bracelet;
  
    // Assign values to variables
    bracelet.num_beads = 10;
    bracelet.letter_beads = 5;
    bracelet.size = 12.3;
    bracelet.initial = 's';
    
    printf("The friendship bracelet has %d beads\n", bracelet.num_beads);

    return 0;
}
