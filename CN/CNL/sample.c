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

    printf("\n--- Go-Back-N ARQ Simulation ---\n");

    i = 1;

    while (i <= totalFrames) {

        printf("\nSending Window: ");

        for (j = i; j < i + windowSize && j <= totalFrames; j++) {
            printf("%d ", j);
        }

        printf("\n");

        int lost = 0;

        for (j = i; j < i + windowSize && j <= totalFrames; j++) {

            if (!lost && rand() % 5 == 0) {   // 20% chance of frame loss
                printf("Frame %d Lost!\n", j);
                printf("Go Back and Resend from Frame %d\n", j);
                i = j;
                lost = 1;
                break;
            }
            else {
                printf("Frame %d Acknowledged.\n", j);
            }
        }

        if (!lost)
            i += windowSize;
    }

    printf("\nAll Frames Successfully Transmitted.\n");

    return 0;
}