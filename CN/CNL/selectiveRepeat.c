/*
Code :- Implementing the Selective Repeat Protocol
Date :- 27/07/2026
Name :- Shubham Khedkar
*/
#include <stdio.h>
#include <windows.h>
int main()
{
    int totalpackets , windowsize;
    int i , j , start = 1;
    int lostpacket;

    print("selective repeat protocol\n");

    printf("Enter total number of packets : ");
    scanf("%d" , &totalpackets);

    printf("Enter window size : ");
    scanf("%d" , &windowsize);

    while(start <= totalpackets)
    {
        printf("\nsending window : ");
        for(i = start ; i < start + windowsize && i <= totalpackets ; i++)
        {
            printf("%d" , i);
            Sleep(500);
        }
        printf("\n");

        printf("Enter lost packet number (0 if none) : ");
        scanf("%d" , &lostpacket);

        if(lostpacket == 0)
        {
            printf("All packets acknowledged\n");
            start += windowsize;
        }
        else
        {
            printf("\nPacket %d lost!\n" , lostpacket);
            printf("Retransmitting packet : %d\n" , lostpacket);
            Sleep(500);
            printf("Packet %d acknowledged\n" , lostpacket);
            start += windowsize;
        }
        printf("transmission complete\n");
        return 0;
        
    }
}