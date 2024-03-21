#include <stdio.h>

enum eras {
    DEBUT,
    FEARLESS,
    SPEAK_NOW,
    RED,
    ERA_1989,
    REPUTATION,
    LOVER,
    FOLKLORE,
    EVERMORE,
    MIDNIGHTS,
    INVALID_ERA
};

int main(void){
    printf("Enter a Tay tay era (0..10): ");
    int scanned_era;
    scanf("%d", &scanned_era);

    enum eras era = scanned_era; 

     if (era == DEBUT) {
        printf("This era was 2006-2009\n");
    } else if (era == FEARLESS) {
        printf("This era was 2009-2010\n"); 
    } else if (era == SPEAK_NOW){
        printf("This era was 2010-2012\n");
    } else if (era == RED){
        printf("This era was 2012-2014\n");
    } else if (era == ERA_1989){
        printf("This era was 2014-2017\n");
    } else if (era == REPUTATION){
        printf("This era was 2017-2018\n");
    } else if (era == LOVER){
         printf("This era was 2018-2020\n");
    } else if (era == FOLKLORE){
         printf("This era was 2020-2022\n");
    } else if (era == EVERMORE){
         printf("This era was 2020-2022\n");
    } else if (era == MIDNIGHTS){
         printf("This era was 2022-now\n");
    } else {
        printf("That is not a valid era, the best is yet to come\n");
    }


    return 0;
}
