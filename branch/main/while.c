#include <stdio.h>
#include <windows.h>
#define p printf
#define s scanf
#define g gotoxy
#define peso '₱'
// ! bug found when entering invalids the number increments
// ? bug fixed  
int col_1, col_2, row_1, row_3, col, row;
int price[4] = {0, 25, 30, 15}, stocks[4] = {0, 100, 100, 100};
int present_quantity [4] = {0, 0, 0, 0}, previous_quantity[4] = {0, 0, 0, 0};
int sold[4] = {0, 0 , 0, 0}, sales[4] = {0, 0, 0, 0};
int grand_total = 0, order_no = 1, choice, total = 0, num, total_bill = 0; 
int  stock_before = 0, stock_after = 0, quantity = 0; 
char description [5][10] = {"","Hamburger", "French", "Coke", "Exit"};
char ans;
float payment, change; 

void gotoxy (int x, int y){
    COORD coord;
    coord.X = x - 1;
    coord.Y = y - 1;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

int box(int col1, int col2, int row1, int row2) {
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

void display_jollibee (){
    g(2, 3);p("ORDER NO. %d", order_no);
    g(2, 3);p("Products");
    g(20, 3);p("Price &");
    g(30, 3);p("Stocks");
    for (num = 1; num < 4; num ++){
        g(2, 3 + num);p("[%d]", num);
        g(5, 3 + num);p("%s", description[num]);
        g(22, 3 + num);p("%d", price[num]);
        g(32, 3 + num);p("%d", stocks[num]);
    }
    g(2, 7);p("[4]");
    g(5, 7);p("%s", description[4]);
}

void display_total(){
    //total/grand total
}

void enter_order (){
    num = 1;
    while (1){
        g(2, 9);p("              ");
        g(2, 8);p("Enter Choice: ");
        g(17, 8);s("%d", &choice);
        if (choice > 0 && choice < 4){
            enter_quantity_again:
            g(20, 8);p("Qty: ");
            g(25, 8);s("%d", &quantity);
            if (quantity <= stocks[choice]){
                stocks[choice] = stocks[choice] - quantity;//bawasan ang stock
                total = price[choice] * quantity; //e total iya balayran
                total_bill = total_bill + total;
                previous_quantity [choice] = quantity; //i set ta ang quantity subong sa previous quanitity nga iya gin pili, kay gamiton tana karon
                g(40, 2 + num);p("%d", num);
                g(45, 2 + num);p("%s", description[choice]);
                g(60, 2 + num);p("P %d", price[choice]);
                g(68, 2 + num);p("%d", quantity);
                g(72, 2 + num);p("%d", total); 
                g(15, 8);p("                    ");
                g(2, 9);p("                 ");
                num ++;
            } else {
                g(25, 8);p("       ");
                g(2, 9);p("INVALID INPUT");
                goto enter_quantity_again;
            }
        }
        if (choice == 4){
            break;
        } else {
            g(17, 8);p("              ");
            g(2, 9);p("INVALID INPUT");
        }   

    }
}
    
int main (){
    system("cls");
    do{
        box(1, 37, 1, 10);
        display_jollibee();
        enter_order();
        g(55, 7 + num);p("Another Order? ");
        g(70, 7 + num);s("%s", &ans);
        system("cls");
    } while (ans == 'y' || ans == 'Y');
    system("cls");
}