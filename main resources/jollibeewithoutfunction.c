#include <stdio.h>
#include <windows.h>
#define p printf
#define s scanf
#define g gotoxy

int col_1, col_2, row_1, row_3, col, row;
int price[4] = {0, 25, 30, 15}, stocks[4] = {0, 100, 100, 100}, previous_quantity[4] = {0, 0, 0, 0};
int sold[4] = {0, 0 , 0, 0}, sales[4] = {0, 0, 0, 0};
int grand_total = 0, order_no = 1, choice, total = 0, num; 
int quantity, stock_before = 0, stock_after = 0; 
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

int main (){
    system("cls");
    box(1, 37, 1, 10);
    do{
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
        g(2, 8);p("Enter Choice: ");
        for (num = 1; num > 0; num++){
            g(15, 8);s("%d", &choice);
            if (choice > 0 || choice < 4){
                g(25, 8);s("%d", &quantity);
                stocks[choice] = stocks[choice] - quantity;//ibanan ang stock
                total = price[choice] * quantity; //e total iya balayran
                g(40, 2 + num);p("%d", num);
                g(45, 2 + num);p("%s", description[choice]);
                g(60, 2 + num);p("P %d", price[choice]);
                g(68, 2 + num);p("%d", quantity);
                g(72, 2 + num);p("%d", total); 
                g(15, 8);p("                    ");
            } else if (choice == 4){
                break;
            }      
        }

        g(2, 25);p("Another Order? ");
        g(25, 25);s("%s", &ans);
        system("cls");
    } while (ans == 'y' || ans == 'Y');
    system("cls");
}