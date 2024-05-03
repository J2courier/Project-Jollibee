    #include <stdio.h>
    #include <windows.h>
    #define p printf
    #define s scanf
    #define g gotoxy

    //! array variable 1D
    int total_sold [4] = {0, 0 , 0, 0}; 
    int subtotal[4] = {0, 0, 0, 0}; 
    int price [4] = {0, 25, 30, 15};
    int stocks [4] = {0, 100, 100, 100};
    int quantity [4] = {0, 0, 0, 0};
    int total_sales [4] = {0, 0, 0, 0};
    char description [5][10] = {"","Hamburger", "Fries", "Coke", "Exit"}; 

    //! none array global variablesxN
    int num;
    char ans;
    int may_order = 0;
    int col, row;
    int order_no = 1;   
    int choice;
    int total_bill = 0; 
    int grand_total = 0;
    float payment, change;

    void gotoxy(int x,int y){
        COORD coord;
        coord.X = x-1;
        coord.Y = y-1;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
    }


    int box (int col1, int col2, int row1, int row2){ 
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

    void main_menu(){ 
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
        g(19, 15);p("SB");
        g(24, 15);p("SE");
        g(29, 15);p("SOLD");
        g(36, 15);p("SALES");
        g(3, 21);p("Grand Total: ");
        g(16, 21);p("%d", grand_total);
        for (int i = 1; i < 4; i ++){
            g(19, 16 + i);p("100");
            g(24, 16 + i);p("%d", stocks[i]);
            g(29, 16 + i);p("%d", total_sold[i]);
            g(36, 16 + i);p("%d", total_sales[i]);
            g(3, 16 + i);p("%s", description[i]);      
        }
    }
    
    void enter_order (){ 
        goto_sang_cancel_order: 
        main_menu (); 
        order: 
        g(2, 9);p("                  "); 
        g(2, 8);p("Enter Choice: ");  
        for (num = 1; num > 0; num++){ 
            g(17, 8);s("%d", &choice);
            g(2, 9);p("                  ");
            if (choice > 0 && choice < 4){
                quantity: 
                may_order = 1; 
                g(20, 8);p("Qty: ");
                g(25, 8);s("%d", &quantity[choice]);
                if (quantity [choice] <= stocks[choice]){ 
                    if (quantity[choice] > 0) { 
                        g(2, 9);p("                  ");
                        stocks[choice] = stocks[choice] - quantity[choice]; 
                        subtotal[choice] = price[choice] * quantity[choice];  
                        total_sales[choice] = total_sales[choice] + subtotal[choice]; 
                        total_bill = total_bill + subtotal[choice]; 
                        total_sold [choice] = total_sold[choice] + quantity[choice]; 
                        g(40, 1);p("Item#");
                        g(47, 1);p("Description");
                        g(60, 1);p("Price", price[choice]); 
                        g(68, 1);p("Qty", quantity[choice]);
                        g(72, 1);p("subtotal");
                        g(40, 2 + num);p("%d", num);
                        g(47, 2 + num);p("%s", description[choice]);
                        g(60, 2 + num);p("P %d", price[choice]);
                        g(69, 2 + num);p("%d", quantity[choice]);
                        g(73, 2 + num);p("%d", subtotal[choice]);
                        g(17, 8);p("                    "); 
                        g(32, 4);p("%d ", stocks[1]);
                        g(32, 5);p("%d ", stocks[2]);
                        g(32, 6);p("%d ", stocks[3]);
                    }  else {
                        g(2, 9);p("INVALID INPUT");
                        g(25, 8);p("  ");
                        goto quantity;
                    }
                } else { 
                    num = num - 1; //minus increment pag nag error para mag remain ang order sa 1,2,3 pasunod ang number
                    g(2, 9);p("Insufficient qty, restock?");
                    g(29, 9);s("%s", &ans);
                    if (ans == 'Y' || ans == 'y'){
                        for (num = 1; num < 4; num ++){
                            stocks[num] = stocks[num] + 100;
                        }
                    }
                    g(17, 8);p("                 "); 
                }
            }     

            else if (choice == 4){ 
                if (may_order == 1){
                    pay:
                    grand_total = grand_total + total_bill; 
                    g(60, 2 + num);p("Total is: %d", total_bill);
                    g(60, 3 + num);p("Payment : ");
                    g(70, 3 + num);s("%f", &payment);
                    if (payment == total_bill){ 
                        g(60, 4 + num);p("                     ");
                        may_order = 0;
                        break; 
                    }
                    else if (payment > total_bill){ //? change and success
                        g(60, 4 + num);p("                     ");
                        change = payment - total_bill;
                        may_order = 0;
                        g(60, 4 + num);p("Change  : %5.2f", change);
                        break; 
                    }
                    else if (payment < total_bill){
                        g(70, 3 + num);p("     ");
                        g(60, 4 + num);p("INSUFFICIENT  AMOUNT");
                    goto pay;
                    } 

                } else {
                    order_no = order_no - 1; // DECREMENT SANG ORDER IF MAG ERROR
                    break; 
                }
            } else {
                g(2, 9);p("INVALID CHOICE"); 
                num = num - 1; 
                g(17, 8);p("              ");
            }   
        }
    }

    int main (){
        system("cls");
        while (1) { 
            box(1, 37, 1, 10);
            enter_order(); 
            box (1, 75, 15, 22 );
            display_total_inventory();
            another_customer:
            g(50, 5 + num);p("Another Customer? "); 
            g(67, 5 + num);s("%s", &ans); 
            if (ans == 'n' || ans == 'N') { //if no means ma exit sya tas confirmation naman sa no
                g(55, 6 + num);p("Exit? ");
                g(70, 6 + num);s("%s", &ans);
                if (ans == 'Y' || ans == 'y') { //if yes means ma terminate ang program, if no or else ma balik sya ma ask sya another customer
                    break; //! ma break nasa sa while loop
                } else {
                    g(55, 6 + num);p("                   ");
                    goto another_customer; 
                }
            } else {
                total_bill = 0;
                order_no = order_no + 1;
                system("cls");
            }
        } 
        system("cls"); 
    }
