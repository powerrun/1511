#include <stdio.h>

#define MAX_HEALTH 50.0
#define MAX_ATTACK 10

// Provided fighter struct
struct fighter {
    int attack;
    double health;
    char attack_command;
};

int main(void) {
    printf("Welcome to Street Fighter!\n");
    printf("\n");

    struct fighter fighter1;
    fighter1.health = MAX_HEALTH;
    double attack1 = 0.0;

    struct fighter fighter2;
    fighter2.health = MAX_HEALTH;
    double attack2 = 0.0;

    ///////////////////////// Fighter 1 Creation ///////////////////////////////

    // TODO: prompt and scan for fighter1's attack power and command. 
    // Initialise fighter1's health to MAX_HEALTH
    printf("Enter Fighter 1's attack power (1-10): ");
    scanf("%d", &fighter1.attack);

    printf("Enter an ascii character for Fighter 1's attack command: ");
    scanf(" %c", &fighter1.attack_command);
    printf("\n");

    ///////////////////////// Fighter 2 Creation ///////////////////////////////

    printf("Enter Fighter 2's attack power (1-10): ");
    scanf("%d", &fighter2.attack);
    
    printf("Enter an ascii character for Fighter 2's attack command: ");
    scanf(" %c", &fighter2.attack_command);
    printf("\n");

    //////////////////////////////// Fight Loop ////////////////////////////////

    // TODO: create a loop until one of the fighters loses all their health
    // prompt the fighter to attack and print remaining health after 
    // each round

    printf("FIGHT!\n\n");

    while (fighter1.health > 0 && fighter2.health > 0)
    {
        // 1's round
        printf("Fighter 1, press %c to attack: ", fighter1.attack_command);
        scanf(" %c", &fighter1.attack_command);
        printf("Fighter 1 attacks!\n");

        // 2's round
        printf("Fighter 2, press %c to attack: ", fighter2.attack_command);
        scanf(" %c", &fighter2.attack_command);
        printf("Fighter 2 attacks!\n\n");

        // round subtotal
        if (fighter1.health >= 25) {
            attack1 = fighter1.attack;
        }
        else if (fighter1.health < 25) {
            attack1 = 1.5 * fighter1.attack;
        }
        fighter2.health -= attack1;

        if (fighter2.health >= 25) {
            attack2 = fighter2.attack;
        }
        else if (fighter2.health < 25) {
            attack2 = 1.5 * fighter2.attack;
        }
        fighter1.health -= attack2;

        printf("Fighter 1's health: %.1f\n", fighter1.health);
        printf("Fighter 2's health: %.1f\n", fighter2.health);
    }
    
    printf("\n");

    ////////////////////////////// Fight Results ///////////////////////////////

    //  TODO: Print the results of the fight

    if ((fighter1.health == 0) && (fighter2.health == 0))
    {
        printf("It's a draw!\n");
    }
    else if (fighter1.health < 0 && fighter2.health < 0)
    {
        printf("It's a draw!\n");
    }
    else if (fighter1.health > fighter2.health)
    {
        printf("Fighter 1 wins!\n");
    }
    else if (fighter1.health < fighter2.health)
    {
        printf("Fighter 2 wins!\n");
    }

    printf("GAME OVER\n");
    return 0;
}