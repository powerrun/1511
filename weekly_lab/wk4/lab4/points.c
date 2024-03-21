// points.c
//
// Complete the C program points.c, so that it scans in all the points of a shape
// into an array of structs. It should then print out the points that were given.
//
// First, it scans in the number of points that the shape has. 
// Then, it scans in the coordinates of each point. 
// Afterwards, it prints out the points in order.
//

#include <stdio.h>

#define MAX_POINTS 10

struct point {
    // TODO: fill this in so that the struct can hold an x and y position
    double x;
    double y;

};

// Prints a point out.
void print_point(int point_no, double x, double y);

int main(void) {
    // TODO: Declare an array of points of size MAX_POINTS
    int count;
    int i;
    struct point coordinates[MAX_POINTS];

    printf("How many points in the shape? ");
    // TODO: scan in number of points in the shape
    scanf("%d", &count);

    printf("Enter points:\n");
    // TODO: scan in the details of each point into the array
    for (i = 1; i <= count; i++) {
        scanf("%lf %lf", &coordinates[i].x, &coordinates[i].y);
    }

    printf("\nShape Points:\n");
    // TODO: print all the points
    for (i = 1; i <= count; i++) {
        print_point(i, coordinates[i].x, coordinates[i].y);
    }
    return 0;
}

//  Prints a single point in the correct format.
//
// Parameters:
// - `point_no` -- The point number
// - `x`        -- The x-coordinate of the point
// - `y`        -- The y-coordinate of the point
//
// Returns: nothing.
void print_point(int point_no, double x, double y) {
    printf("%2d: x = %.3lf, y = %.3lf\n", point_no, x, y);
}
