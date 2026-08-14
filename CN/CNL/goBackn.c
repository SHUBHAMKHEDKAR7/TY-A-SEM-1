/*
Code :- Implementing the goBackn 
Date :- 27/07/2026
Name :- Shubham Khedkar
*/
#include <stdio.h>
#include <windows.h>

int main()
{
    int totalPackets, windowSize;
    int i, start = 1;
    int lostPacket;

    printf("Enter Total Number of Packets: ");
    scanf("%d", &totalPackets);

    printf("Enter Window Size: ");
    scanf("%d", &windowSize);

    while (start <= totalPackets)
    {
        printf("\nSending Window: ");

        for (i = start; i < start + windowSize && i <= totalPackets; i++)
        {
            printf("%d ", i);
            Sleep(500);
        }

        printf("\n");

        printf("Enter Lost Packet Number (0 if none): ");
        scanf("%d", &lostPacket);

        if (lostPacket == 0)
        {
            printf("All Packets Acknowledged.\n");
            start += windowSize;
        }
        else
        {
            printf("\nPacket %d Lost!\n", lostPacket);

            printf("Retransmitting Packets: ");

            for (i = lostPacket; i < start + windowSize && i <= totalPackets; i++)
            {
                printf("%d ", i);
                Sleep(500);
            }

            printf("\n");

            start += windowSize;
        }
    }

    printf("\nTransmission Complete.\n");

    return 0;
}