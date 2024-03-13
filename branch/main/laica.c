#include <stdio.h>
#include <conio.h>
#define g gotoxy

main()
{
    // initializing of values bhieee, alam mo na yan
    int Quantity, Choice;
    int Num = 1, C = 1, E = 1;
    int Price[4] = {"",25, 50, 15};
    int SB[4] = {"",100, 100, 100};
    char ans;
    char *Products[4] = {"","Hamburger   ", "French Fries", "Coke        "};
    float T[4] = {0}, GrandTotal = 0, SubTotal;
    
    // loop sa printing ng menu, kaartehan sa bohai lol
    EnterChoice:
    g(1,1);printf("Order No. %d\n", C);
    g(1,2);printf("Products        Price        Stocks\n");
    for (Num = 1; Num < 4; Num++)
    {
        printf("[%d] %s  %d           %d\n", Num , Products[Num], Price[Num], SB[Num]);
    }
    
    g(1,6);printf("[4] Exit\n");
    g(1,7);printf("Enter choice: ");
    g(14,7);scanf("%d", &Choice);
}