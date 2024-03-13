#include <stdio.h>
#define p printf
#define s scanf
#define g gotoxy

int box(int col1, int col2, int row1, int row2) {
    int col,row;
    for(col=col1;col<=col2;col++){
    g(col,row1);p("|");
    }
    for(row=row1;row<=row2;row++){
    g(col2,row);p("|");
    }
    for(col=col2;col>=col1;col--){
    g(col,row2);p("|");
    }
    for(row=row2;row>=row1;row--){
    g(col1,row);p("|");
    }
}
main(){
    int choice;
    clrscr();
    box(15,60,7,20);
    g(35,10);p("ABC BANK");
    g(25,12);p("[1] Balance Inquiry");
    g(25,13);p("[2] Withdraw");
    g(25,14);p("[3] Deposit");
    g(25,15);p("[4] Exit");
    g(25,17);p("Enter choice:");
    g(45,17);s("%d",&choice);
    if (choice==1){
    clrscr();
    box(10,60,1,25);
    getch();
    }
}