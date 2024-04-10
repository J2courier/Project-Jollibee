#include <stdio.h>
#include <windows.h>
#define p printf
#define s scanf
#define g gotoxy

//! array variable 1D
int sold [4] = {0, 0 , 0, 0}; 
int sales [4] = {0, 0, 0, 0};
int price [4] = {0, 25, 30, 15};
int stocks [4] = {0, 100, 100, 100};
int quantity [4] = {0, 0, 0, 0};
int sub_sales [4] = {0, 0, 0, 0};
int present_stocks [4] = {0, 100, 100, 100};
int present_quantity [4] = {0, 0, 0, 0};
int stock_beginning [4] = {0, 100, 100, 100};
char description [5][10] = {"","Hamburger", "French", "Coke", "Exit"}; 

//! none array global variables
int num;
char ans;
int may_order = 0;
int col, row;
int order_no = 1;
int choice;
int subtotal = 0; 
int total_bill = 0; 
int stock_after = 0; 
int grand_total = 0;
int stock_before = 0;
float payment, change;

void gotoxy (int x, int y){
    COORD coord;
    coord.X = x - 1;
    coord.Y = y - 1;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

int box (int col1, int col2, int row1, int row2){ //!function para sa box
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

void display_jollibee (){ //! function para e display ang menu sang jolllibee
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
    g(2, 7);p("[4]"); //! ang choice nga 4 e display ta seperately kay ga conflict mag display
    g(5, 7);p("%s", description[4]);
}

void display_total_inventory(){//! function para ma display ang inventory
    g(19, 15);p("SB");//! stock beginning
    g(24, 15);p("SE");//! stock end
    g(29, 15);p("SOLD");
    g(36, 15);p("SALES");
    g(3, 21);p("Grand Total: ");
    g(16, 21);p("%d", grand_total);
    for (int i = 1; i < 4; i ++){//! loop para ma display ang value sang aton nga items, ila SB, SE, sold, and sales
        g(19, 16 + i);p("100");
        g(24, 16 + i);p("%d", stocks[i]);
        g(29, 16 + i);p("%d", present_quantity[i]);
        g(36, 16 + i);p("%d", sales[i]);
        g(3, 16 + i);p("%s", description[i]);      
    }
}
void erase_list (){//! function para i erase ang list sang gin order
    g(17, 8);p("  ");
    g(40, 1 + num);p("      ");//! the rest para sa list nga gin order
    g(45, 1 + num);p("                     ");
    g(45, 2 + num);p("                     ");
    g(40, 3 + num);p("                     ");
    g(68, 1 + num);p("     ");
    g(72, 1 + num);p("     ");
    g(60, 1 + num);p("                     ");
    g(60, 2 + num);p("                      ");
}
void erase (){//! function para i erase ang cancel order kag ang payment 
    g(17, 8);p("               "); //! para sa choice
    g(60, 3 + num);p("                     ");//! para sa payment
    g(55, 4 + num);p("                     ");//! para sa cancel order
    g(60, 5 + num);p("                     ");//! para sa value sang cancel order
    
}

void enter_order (){//! 70% of process is stored in this function
    goto_sang_cancel_order: 
    display_jollibee (); //! call out and function
    order: //! unecessary but incase
    g(2, 8);p("Enter Choice: "); //! prompt to enter a choice
    for (num = 1; num > 0; num++){ //! loop for entering choice endless, ma end lang if mag enter choice '4' which is exit
        g(17, 8);s("%d", &choice);
        g(2, 9);p("                  ");
        if (choice > 0 && choice < 4){
            quantity: 
            may_order = 1; //! para ma determine sa choice 4 kung may order or wala 1 means may order, 0 means wala order
            g(20, 8);p("Qty: ");
            g(25, 8);s("%d", &quantity[choice]);
            if (quantity [choice] <= stocks[choice]){ //! condition/ sentinel kung sufficient ang stocks sa quantity nya nga gin order
                if (quantity[choice] > 0) { //! greater than 0 means may quantiy sya nga gin butang
                    g(2, 9);p("              "); //! erase the invalid input display
                    stocks[choice] = stocks[choice] - quantity[choice]; //! bawasan ang stocks
                    subtotal = price[choice] * quantity[choice];  //! e total iya balayran
                    sub_sales[choice] = price[choice] * quantity [choice];//! para ma total ang sales sa kada items
                    sales[choice] = sales[choice] + sub_sales[choice]; //! para  madisplay ang sales
                    total_bill = total_bill + subtotal; //!final nga balayran
                    present_quantity [choice] = present_quantity[choice] + quantity[choice]; //! para ma monitor ang quantiy sa kada item
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
                }  else {
                    g(2, 9);p("INVALID INPUT");
                    g(25, 8);p("  ");
                    goto quantity;
                }
            } else { //! CONDITION PARA SA INVALID QUANTITY which is less than 0
                num = num - 1;
                g(2, 9);p("INVALID QUANTITY");
                g(17, 8);p("                "); 
            }
        }     
        else if (choice == 4){ //! ma proceed sa payment or kung mag exit without order ma ask another customer
            if (may_order == 1){//! nag set ta flag sa enter choice 1,2,3 if mag enter sa either sa tatlo ma set ang flag sa 1 means may order sya if 0 means wala sya order
                pay:
                grand_total = grand_total + total_bill; //! para ma display ang grand total
                g(60, 2 + num);p("Total is: %d", total_bill);
                g(60, 3 + num);p("Payment : ");
                g(70, 3 + num);s("%f", &payment);
                if (payment == total_bill){ //! success
                    break; //! ma break out sa sya for loop sang enter_order() function
                }
                else if (payment > total_bill){ //? change
                    change = payment - total_bill;
                    g(60, 4 + num);p("Change  : %5.2f", change);
                    break; //! ma break out sa sya for loop sang enter_order() function
                }
                else if (payment < total_bill){ //! cancel order
                    g(60, 4 + num);p("cancel order? ");  //! display cancel order
                    g(75, 4 + num);s("%s", &ans); //! get the input using scanf 
                    if (ans == 'y' || ans == 'Y'){ //! check the input if Y or others, Y means yes
                        for (num = 1; num < 4; num ++){ //! loop the the stocks element in order to return the previous value
                            total_bill = 0; //! set total bill to 0 para sa next order 0 na ang value
                            stocks[num] = stocks[num] + quantity[num];//! e add ang quantity sang stocks, para ma balik
                            grand_total = grand_total - total_bill; //! e subtract para hindi mag add
                            g(60, 5 + num);p("                     ");
                            erase_list(); //! ini nga function consist ni sya sang mga pang tamper sa display
                        }
                        goto goto_sang_cancel_order;
                    } else if (ans == 'n' || 'N'){ //! condition if ans is no in cancel order, no means ma pay sya liwat
                        g(70, 4 + num);p("   ");
                        g(60, 5 + num);p("                 ");
                        erase(); //! erase_function is consist of erasing the part of cancel order and the value of payment
                        goto pay;
                    } else {
                        g(70, 4 + num);p("INVALID INPUT"); //! invalid input sang cancel order
                    }
                } else {
                    g(65, 5 + num);p("INVALID INPUT");//! invalid input sang payment
                }
            } else { //! else sang flag means if flag = 0 man gihapon wala sa order kag ma another customer nalng
                break; //! ma break sya sa enter_order function directly ma ask another customer
            }
        } else {
            g(2, 9);p("INVALID INPUT"); //! invalid input sa pag enter sang choice
            num = num - 1; //! enter choice that is invalid is counted in loop, para ma prevent ang value sang loop kung error e decrement naton
            g(17, 8);p("              "); //! tamper sa display nga choice
        }   
    }
}

int main (){
    system("cls");
    while (1) { //! while (true) endless, will stop in certain condition inside the process by using 'break;'
        box(1, 37, 1, 10);
        enter_order(); //? sa enter order naga increment ang num para ma adjust depend sa kadamoun sang order ang another customer
        another_customer:
        g(50, 5 + num);p("Another Customer? "); //? ang increment sang num halin sa function nga enter_order();
        g(67, 5 + num);s("%s", &ans);
        if (ans == 'n' || ans == 'N') {
            box (1, 75, 15, 22 );//! we need new variable for incrementing and move the box
            display_total_inventory();
            g(55, 6 + num);p("Exit? ");
            g(70, 6 + num);s("%s", &ans);
            if (ans == 'Y' || ans == 'y') { 
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
    system("cls"); //! after break sa exit diri na sa ma direct
}
