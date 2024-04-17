// Function to place protection around a flower
void place_protection(struct tile map[MAX_ROW][MAX_COL], int flower_row, int flower_col) {
    // Define weak points around a flower
    int weak_point[4][2];

    // Define weak points around the flower by adjusting row and column coordinates
    weak_point[0][0] = flower_row + 1;
    weak_point[0][1] = flower_col;

    weak_point[1][0] = flower_row;
    weak_point[1][1] = flower_col + 1;

    weak_point[2][0] = flower_row - 1;
    weak_point[2][1] = flower_col;

    weak_point[3][0] = flower_row;
    weak_point[3][1] = flower_col - 1;

    // Iterate over each weak point
    for (int count = 0; count < 4; count++) {
        int weak_row = weak_point[count][0];
        int weak_col = weak_point[count][1];

        // Check if a weak point is within the map boundaries and is a branch
        if (weak_row >= 0 && weak_row < MAX_ROW &&
            weak_col >= 0 && weak_col < MAX_COL &&
            map[weak_row][weak_col].type == BRANCH) {
            // If the weak point is a branch, update it to a bush
            // and set protection around the flower to TRUE
            map[weak_row][weak_col].type = BUSH;
            map[flower_row][flower_col].flower.place_protection = TRUE;
        }
        // Check if a weak point is within the map boundaries and is empty
        else if (weak_row >= 0 && weak_row < MAX_ROW &&
                 weak_col >= 0 && weak_col < MAX_COL &&
                 map[weak_row][weak_col].type == EMPTY) {
            // If the weak point is empty, update it to a bush, set protection around the flower to TRUE,
            // then exit the loop as protection is placed
            map[weak_row][weak_col].type = BUSH;
            map[flower_row][flower_col].flower.place_protection = TRUE;
            break;
        }
    }
}
