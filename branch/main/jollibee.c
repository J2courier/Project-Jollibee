#include <stdio.h>
#include <windows.h>
#define p printf
#define s scanf
#define g gotoxy
#define peso '₱'

//! need to fix in instant exit if user enters choice 4 without order que
//! Need to fix quantity 0
//! Need to fix grand total
//! need to fix cancel order 'N'
//? what's new?
//? order update fixed
//? order no increment fixed

char ans;
float payment, change;
int col_1, col_2, row_1, row_3, col, row;
int price[4] = {0, 25, 30, 15}, stocks[4] = {0, 100, 100, 100}, stock_beginning[4] = {0, 100, 100, 100}, present_stocks[4] = {0, 100, 100, 100};
int quantity [4] = {0, 0, 0, 0}, present_quantity[4] = {0, 0, 0, 0}, sold[4] = {0, 0 , 0, 0}, sales[4] = {0, 0, 0, 0};
int grand_total = 0, order_no = 1, choice, subtotal = 0, num, total_bill = 0, stock_before = 0, stock_after = 0; 
char description [5][10] = {"","Hamburger", "French", "Coke", "Exit"}; //[5] is number sang index, [10] 10 characters or letters max

void gotoxy (int x, int y){
    COORD coord;
    coord.X = x - 1;
    coord.Y = y - 1;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

int box (int col1, int col2, int row1, int row2) {
    for(col=col1;col<=col2;col++){
        g(col,row1);p("-");
    }
    for(row=row1;row<=row2;row++){
        g(col2,row);p("|");
    }
    for(col=col2;col>=col1;col--){
        g(col,row2);p("-");
    }
    for(row=row2;row>=row1;row--){
        g(col1,row);p("|");
    }
}

void display_jollibee (){
    g(2, 2);p("ORDER NO. %d", order_no);
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

void display_total_inventory(){
    g(15, 12);p("SB");
    g(20, 12);p("SE");
    g(25, 12);p("SOLD");
    g(32, 12);p("SALES");
    g(50, 17);p("Grand Total: ");
    g(70, 16 + num);p("%d", grand_total);
    for (num = 1; num < 4; num ++){
        g(15, 13 + num);p("100");
        g(20, 13 + num);p("%d", stocks[num]);
        g(26, 13 + num);p("%d", present_quantity[num]);
        g(2, 13 + num);p("%s", description[num]);
        
    }
}

void erase (){
    g(17, 8);p("               ");
    g(40, 1 + num);p("      ");
    g(45, 1 + num);p("                     ");
    g(60, 1 + num);p("                     ");
    g(68, 1 + num);p("     ");
    g(72, 1 + num);p("     ");
    g(60, 2 + num);p("                      ");
    g(60, 3 + num);p("                      ");
    g(60, 4 + num);p("                     ");
    g(60, 5 + num);p("                     ");
}

void enter_order (){//? 70% of process is stored in this function
    cancel_order:
    display_jollibee ();
    order:
    g(2, 8);p("Enter Choice: ");
    for (num = 1; num > 0; num++){
        g(17, 8);s("%d", &choice);
        g(2, 9);p("              ");
        if (choice > 0 && choice < 4){
            g(20, 8);p("Qty: ");
            g(25, 8);s("%d", &quantity[choice]);
            stocks[choice] = stocks[choice] - quantity[choice]; //! bawasan ang stocks
            subtotal = price[choice] * quantity[choice];  //! e total iya balayran
            total_bill = total_bill + subtotal; //!final nga balayran
            grand_total = grand_total + total_bill;
            present_quantity [choice] = present_quantity[choice] + quantity[choice]; 
            g(40, 1);p("Item#");
            g(47, 1);p("Description");
            g(60, 1);p("Price", price[choice]);
            g(68, 1);p("Qty", quantity[choice]);
            g(72, 1);p("subtotal");
            g(40, 2 + num);p("%d", num);
            g(47, 2 + num);p("%s", description[choice]);
            g(60, 2 + num);p("P %d", price[choice]);
            g(69, 2 + num);p("%d", quantity[choice]);
            g(73, 2 + num);p("%d", subtotal);
            g(15, 8);p("                    "); //! erase ang input sa pag iterate
            g(32, 4);p("%d ", stocks[1]);
            g(32, 5);p("%d ", stocks[2]);
            g(32, 6);p("%d ", stocks[3]);
        }  
        else if (choice == 4){ //ma proceed sa payment
            pay:
            g(60, 2 + num);p("Total is: %d", total_bill);
            g(60, 3 + num);p("Payment: ");
            g(70, 3 + num);s("%f", &payment);
            if (payment == total_bill){ //? success
                g(60, 4 + num);p("Order success");
                break;
            }
            else if (payment > total_bill){ //? change
                change = payment - total_bill;
                g(60, 4 + num);p("Change: %5.2f", change);
                break;
            }
            else if (payment < total_bill){ //! cancel order
                g(60, 4 + num);p("Cancel Order?: ");
                g(75, 4 + num);s("%s", &ans);
                if (ans == 'y' || ans == 'Y'){
                    for (num = 1; num < 4; num ++){
                        total_bill = 0;
                        stocks[num] = stocks[num] + quantity[num];
                        grand_total = grand_total - total_bill;                        
                        erase();
                    }
                    goto cancel_order;
                } else if (ans == 'n' || 'N'){
                    g(70, 4 + num);p("   ");
                    g(60, 5 + num);p("                 ");
                    goto pay;
                } else {
                    g(70, 4 + num);p("INVALID INPUT");
                }
            } else {
                g(65, 5 + num);p("INVALID INPUT");
            }
        } else {
            g(2, 9);p("INVALID INPUT");
            num = num - 1;
            g(17, 8);p("              ");
        }   
    }
}

int main (){
    system("cls");
    while (1) {
        box(1, 37, 1, 10);
        //display_jollibee();
        enter_order(); //? sa enter order naga increment ang num para ma adjust depend sa kadamoun sang order ang another customer
        g(50, 5 + num);p("Another Customer? "); //? ang increment sang num halin sa function nga enter_order();
        g(67, 5 + num);s("%s", &ans);
        if (ans == 'n' || ans == 'N'){
            inventory:
            box (1, 75, 12, 18);
            display_total_inventory();
            g(55, 5 + num);p("Exit? ");
            g(70, 5 + num);s("%s", &ans);
            if (ans == 'Y' || ans == 'y'){
                system("cls");
            } else {
                goto inventory;
            }
        } else {
            total_bill = 0;
            order_no = order_no + 1;
            system("cls");
        }
    } 
}
