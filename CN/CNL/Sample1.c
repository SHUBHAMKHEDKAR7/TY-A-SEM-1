#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    int totalFrames, windowSize;
    int i, j;

    printf("Enter Total Number of Frames: ");
    scanf("%d", &totalFrames);

    printf("Enter Window Size: ");
    scanf("%d", &windowSize);

    srand(time(NULL));

    printf("\n--- Selective Repeat ARQ Simulation ---\n");

    for (i = 1; i <= totalFrames; i += windowSize) {

        printf("\nSending Window: ");

        for (j = i; j < i + windowSize && j <= totalFrames; j++) {
            printf("%d ", j);
        }

        printf("\n");

        for (j = i; j < i + windowSize && j <= totalFrames; j++) {

            if (rand() % 5 == 0) {      // 20% chance of frame loss
                printf("Frame %d Lost!\n", j);
                printf("Retransmitting Frame %d...\n", j);
                printf("Frame %d Acknowledged.\n", j);
            }
            else {
                printf("Frame %d Acknowledged.\n", j);
            }
        }
    }

    printf("\nAll Frames Successfully Transmitted.\n");

    return 0;
}