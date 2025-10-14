#include <stdio.h>
#include <windows.h>
#include <string.h>
#include <conio.h>

// ======== ADD THE RESERVATION MODULE CODE HERE ========
// ==================== RESERVATION MODULE ====================

// Reservation structure and global variables
typedef struct {
    int reservation_id;
    char customer_name[50];
    char phone[15];
    int party_size;
    char date[11];  // YYYY-MM-DD
    char time[6];   // HH:MM
    int duration;   // in hours
    int table_number;
    int is_confirmed;
} Reservation;

Reservation reservations[100];
int reservation_count = 0;
int next_reservation_id = 1;

// Function prototypes
void reservation_system();
void make_reservation();
void view_reservations();
void cancel_reservation();
void search_reservation();
int is_table_available(int table_num, char* date, char* time, int duration);
void display_reservation_menu();
void save_reservations_to_file();
void load_reservations_from_file();

// Reservation System Main Function
void reservation_system() {
    load_reservations_from_file();
    int choice;
   
    do {
        system("cls");
        system("color 0E");  // Yellow background
        printf("\n\n\n\t\t\t=== CAFE NIRVANA RESERVATION SYSTEM ===\n");
        printf("\t\t\t=====================================\n\n");
       
        display_reservation_menu();
       
        printf("\n\n\t\t\tEnter your choice (1-5): ");
        scanf("%d", &choice);
       
        switch(choice) {
            case 1:
                make_reservation();
                break;
            case 2:
                view_reservations();
                break;
            case 3:
                search_reservation();
                break;
            case 4:
                cancel_reservation();
                break;
            case 5:
                save_reservations_to_file();
                printf("\n\t\t\tReturning to main menu...\n");
                Sleep(2000);
                break;
            default:
                printf("\n\t\t\tInvalid choice! Please try again.\n");
                Sleep(1500);
        }
    } while(choice != 5);
}

// Display Reservation Menu
void display_reservation_menu() {
    printf("\n\t\t\t1. Make New Reservation\n");
    printf("\t\t\t2. View All Reservations\n");
    printf("\t\t\t3. Search Reservation\n");
    printf("\t\t\t4. Cancel Reservation\n");
    printf("\t\t\t5. Back to Main Menu\n");
   
    printf("\n\n\t\t\tCurrent Reservations: %d\n", reservation_count);
    printf("\t\t\tNext Available ID: %d\n", next_reservation_id);
}

// Make New Reservation
void make_reservation() {
    system("cls");
    system("color 0A");  // Green background
    printf("\n\n\n\t\t\t=== MAKE NEW RESERVATION ===\n");
    printf("\t\t\t============================\n\n");
   
    if(reservation_count >= 100) {
        printf("\t\t\tSorry! Reservation system is full.\n");
        Sleep(2000);
        return;
    }
   
    Reservation new_res;
    new_res.reservation_id = next_reservation_id++;
   
    printf("\n\t\t\tEnter Customer Name: ");
    scanf(" %[^\n]", new_res.customer_name);
   
    printf("\t\t\tEnter Phone Number: ");
    scanf("%s", new_res.phone);
   
    printf("\t\t\tEnter Party Size: ");
    scanf("%d", &new_res.party_size);
   
    printf("\t\t\tEnter Date (YYYY-MM-DD): ");
    scanf("%s", new_res.date);
   
    printf("\t\t\tEnter Time (HH:MM): ");
    scanf("%s", new_res.time);
   
    printf("\t\t\tEnter Duration (hours): ");
    scanf("%d", &new_res.duration);
   
    printf("\t\t\tEnter Preferred Table Number (1-20): ");
    scanf("%d", &new_res.table_number);
   
    // Validate table availability
    if(!is_table_available(new_res.table_number, new_res.date, new_res.time, new_res.duration)) {
        printf("\n\t\t\tTable %d is not available at that time!\n", new_res.table_number);
        printf("\t\t\tPlease choose a different table or time.\n");
        Sleep(3000);
        return;
    }
   
    new_res.is_confirmed = 1;
    reservations[reservation_count++] = new_res;
   
    printf("\n\n\t\t\t✓ Reservation Successful!\n");
    printf("\t\t\tReservation ID: %d\n", new_res.reservation_id);
    printf("\t\t\tCustomer: %s\n", new_res.customer_name);
    printf("\t\t\tTable: %d\n", new_res.table_number);
    printf("\t\t\tDate: %s at %s\n", new_res.date, new_res.time);
   
    printf("\n\t\t\tPress any key to continue...");
    getch();
}

// Check Table Availability
int is_table_available(int table_num, char* date, char* time, int duration) {
    if(table_num < 1 || table_num > 20) return 0;
   
    for(int i = 0; i < reservation_count; i++) {
        if(reservations[i].table_number == table_num &&
           strcmp(reservations[i].date, date) == 0 &&
           reservations[i].is_confirmed) {
            // Simple time conflict check (in real system, use proper time comparison)
            return 0;
        }
    }
    return 1;
}

// View All Reservations
void view_reservations() {
    system("cls");
    system("color 0B");  // Light blue background
    printf("\n\n\n\t\t\t=== ALL RESERVATIONS ===\n");
    printf("\t\t\t=======================\n\n");
   
    if(reservation_count == 0) {
        printf("\t\t\tNo reservations found.\n");
    } else {
        printf("%-4s %-20s %-12s %-4s %-12s %-8s %-3s %s\n",
               "ID", "Name", "Phone", "Size", "Date", "Time", "Tbl", "Dur");
        printf("--------------------------------------------------------------------------------\n");
       
        for(int i = 0; i < reservation_count; i++) {
            if(reservations[i].is_confirmed) {
                printf("%-4d %-20s %-12s %-4d %-12s %-8s %-3d %dh\n",
                       reservations[i].reservation_id,
                       reservations[i].customer_name,
                       reservations[i].phone,
                       reservations[i].party_size,
                       reservations[i].date,
                       reservations[i].time,
                       reservations[i].table_number,
                       reservations[i].duration);
            }
        }
    }
   
    printf("\n\n\t\t\tPress any key to continue...");
    getch();
}

// Search Reservation
void search_reservation() {
    system("cls");
    system("color 0D");  // Purple background
    printf("\n\n\n\t\t\t=== SEARCH RESERVATION ===\n");
    printf("\t\t\t=========================\n\n");
   
    int choice;
    printf("\t\t\tSearch by:\n");
    printf("\t\t\t1. Reservation ID\n");
    printf("\t\t\t2. Customer Name\n");
    printf("\t\t\t3. Phone Number\n");
    printf("\t\t\tEnter choice: ");
    scanf("%d", &choice);
   
    switch(choice) {
        case 1: {
            int search_id;
            printf("\t\t\tEnter Reservation ID: ");
            scanf("%d", &search_id);
           
            int found = 0;
            for(int i = 0; i < reservation_count; i++) {
                if(reservations[i].reservation_id == search_id && reservations[i].is_confirmed) {
                    printf("\n\t\t\tReservation Found:\n");
                    printf("\t\t\tID: %d\n", reservations[i].reservation_id);
                    printf("\t\t\tName: %s\n", reservations[i].customer_name);
                    printf("\t\t\tPhone: %s\n", reservations[i].phone);
                    printf("\t\t\tParty Size: %d\n", reservations[i].party_size);
                    printf("\t\t\tDate: %s\n", reservations[i].date);
                    printf("\t\t\tTime: %s\n", reservations[i].time);
                    printf("\t\t\tTable: %d\n", reservations[i].table_number);
                    printf("\t\t\tDuration: %d hours\n", reservations[i].duration);
                    found = 1;
                    break;
                }
            }
            if(!found) {
                printf("\t\t\tReservation not found!\n");
            }
            break;
        }
        case 2: {
            char search_name[50];
            printf("\t\t\tEnter Customer Name: ");
            scanf(" %[^\n]", search_name);
           
            int found = 0;
            for(int i = 0; i < reservation_count; i++) {
                if(strstr(reservations[i].customer_name, search_name) != NULL && reservations[i].is_confirmed) {
                    printf("\n\t\t\tReservation Found:\n");
                    printf("\t\t\tID: %d, Name: %s, Date: %s, Time: %s, Table: %d\n",
                           reservations[i].reservation_id, reservations[i].customer_name,
                           reservations[i].date, reservations[i].time, reservations[i].table_number);
                    found = 1;
                }
            }
            if(!found) {
                printf("\t\t\tNo reservations found for that name!\n");
            }
            break;
        }
        case 3: {
            char search_phone[15];
            printf("\t\t\tEnter Phone Number: ");
            scanf("%s", search_phone);
           
            int found = 0;
            for(int i = 0; i < reservation_count; i++) {
                if(strcmp(reservations[i].phone, search_phone) == 0 && reservations[i].is_confirmed) {
                    printf("\n\t\t\tReservation Found:\n");
                    printf("\t\t\tID: %d, Name: %s, Date: %s, Time: %s, Table: %d\n",
                           reservations[i].reservation_id, reservations[i].customer_name,
                           reservations[i].date, reservations[i].time, reservations[i].table_number);
                    found = 1;
                }
            }
            if(!found) {
                printf("\t\t\tNo reservations found for that phone number!\n");
            }
            break;
        }
        default:
            printf("\t\t\tInvalid choice!\n");
    }
   
    printf("\n\t\t\tPress any key to continue...");
    getch();
}

// Cancel Reservation
void cancel_reservation() {
    system("cls");
    system("color 0C");  // Red background
    printf("\n\n\n\t\t\t=== CANCEL RESERVATION ===\n");
    printf("\t\t\t==========================\n\n");
   
    int cancel_id;
    printf("\t\t\tEnter Reservation ID to cancel: ");
    scanf("%d", &cancel_id);
   
    int found = 0;
    for(int i = 0; i < reservation_count; i++) {
        if(reservations[i].reservation_id == cancel_id && reservations[i].is_confirmed) {
            printf("\n\t\t\tReservation Details:\n");
            printf("\t\t\tName: %s\n", reservations[i].customer_name);
            printf("\t\t\tDate: %s, Time: %s\n", reservations[i].date, reservations[i].time);
            printf("\t\t\tTable: %d\n", reservations[i].table_number);
           
            char confirm;
            printf("\n\t\t\tAre you sure you want to cancel? (y/n): ");
            scanf(" %c", &confirm);
           
            if(confirm == 'y' || confirm == 'Y') {
                reservations[i].is_confirmed = 0;
                printf("\t\t\t✓ Reservation cancelled successfully!\n");
            } else {
                printf("\t\t\tCancellation aborted.\n");
            }
            found = 1;
            break;
        }
    }
   
    if(!found) {
        printf("\t\t\tReservation not found or already cancelled!\n");
    }
   
    printf("\n\t\t\tPress any key to continue...");
    getch();
}

// Save reservations to file
void save_reservations_to_file() {
    FILE *file = fopen("reservations.dat", "wb");
    if(file) {
        fwrite(&reservation_count, sizeof(int), 1, file);
        fwrite(&next_reservation_id, sizeof(int), 1, file);
        fwrite(reservations, sizeof(Reservation), reservation_count, file);
        fclose(file);
    }
}

// Load reservations from file
void load_reservations_from_file() {
    FILE *file = fopen("reservations.dat", "rb");
    if(file) {
        fread(&reservation_count, sizeof(int), 1, file);
        fread(&next_reservation_id, sizeof(int), 1, file);
        fread(reservations, sizeof(Reservation), reservation_count, file);
        fclose(file);
    }
}
// ======================================================

int token = 0,tokens[50],payment_counter=0;




int main_page()
{
    int i;
    system("cls");
    system("color 0B");

    printf("\n\n\n\n\n\t\t       @@_@_\n\t\t         `'*'  Welcome to Cafe Nirvana \n\t\t\t\t\t\t\t`'*'`-@@_@\n\n");
    printf("\n\n\n\n\t\t\t    Quality food.Serves good. (^_^)\n\n                       ");
    for (i=0;i<36;i++)
     {
        printf("~");
     }
    printf("\n");
    printf("        tasty          $                                  $\n");
    printf("                       $    Select any of them -          $\n");
    printf("        and            $                                  $\n");
    printf("                       $    1. New Order.                 $\n");
    printf("       hygenic         $                                  $\n");
    printf("                       $    2. Bill Payment.              $\n");
    printf("      foods at         $                                  $\n");
    printf("                       $    3. Reservation System         $\n");  // CHANGED
    printf("      low cost..       $                                  $\n");
    printf("                       $    4. Exit.                      $\n");  // CHANGED
    printf("     GRAB NOW !!       ");


    for (i=0;i<36;i++)
     {
        printf("~");
     }
    printf("\n\n\n\n                         Enter Your Choice: ");
    int n;
    scanf("%d",&n);
    return n;
}


int menu_order()
{

    int arID[10],decision,arqty[10],Bill[10],counter=0;
    work:
    system("cls");
    system("color 4F");
    printf("\n\t\t\t\tFOOD MENU\n\t\t\t\t---------\n");
    printf("\n\tBUNS :\n\n");
    printf("\t1. Beef Burger ...................... 120/=\t  \n");
    printf("\t2. Hot Dog ..........................  40/=\n");
    printf("\t3. Donuts ...........................  70/=\t \n");
    printf("\t4. French Fries (FnF Pack) ..........  90/=\t \n");
    printf("\t\t\t\t\t\t\t \n\n\tCHICKEN :\n\n");
    printf("\t5. Chicken Breast ...................  90/=\n");
    printf("\t6. Chicken Wings ....................  65/=\n");
    printf("\n\tDESSERTS :\n\t\t\t\t\t\t\t \n");
    printf("\t7. Ice Cream ........................  65/=\t  \n");
    printf("\t8. Sweets ........................... 230/=\t \n");
    printf("\n\tDRINKS :\n\n");
    printf("\t9.  Coca-Cola ........................ 25/=\n");
    printf("\t10. Mirinda   ........................ 25/=\n");
    printf("\n\n\tOrder your dish: (Enter 0 to finish order)\n");
    for(;;)
    {
        counter++;
        printf("\t Enter Food ID: ");
        scanf("%d",&arID[counter-1]);
        if(arID[counter-1]==0)
        {
            break;
        }
        printf("\t Enter Quantity: ");
        scanf("%d",&arqty[counter-1]);

    }
    system("cls");
   printf("\n\n\n\n\n\n\n\n\n\n\t\tThanks for your order. We are getting ready the dishes.\n\t\tUntil then, have some selfies with friends. Enjoy!\n\n\n\n\n\t\t\t  <Enter 1 to check your bill>\n\t\t\tEnter your choice: ");

    scanf("%d",&decision);
    printf("\n\n\n\n\n\n\n\n");

    counter--;

    if(decision==1)
    {
        Bill_show(arID,arqty,counter);
    }

    else if(decision==2)
    {
       goto work;
    }

    else if(decision==3)
    {
        main();
    }

}


void Bill_show(int arID[],int arqty[],int counter)
{

    int n;
    system("cls");
    system("color B0");

    int i,sum=0;
    int costs[10]={120,40,70,90,90,65,65,230,25,25};
    char items[10][16]={"Beef Burger","Hot Dog","Donuts","French Fries","Chicken Breast","Chicken Wings","Ice Cream","Sweets","Coca-Cola","Mirinda"};
    printf("\n\nYour Bill:\n\n\n\t\tItem(s)\t\t     Quantity\t\t    Cost\n\n\n\n");

    for(i=0;i<counter;i++)
    {
        printf("\t%2d. %-16s ________\t%-5d piece(s) ____ %7d\n",i+1,items[arID[i]-1],arqty[i],arqty[i]*costs[arID[i]-1]);
        sum=sum+(costs[arID[i]-1]*arqty[i]);
    }

    printf("\n\n\n\n\t\t\t\t\t\t\t  Total = %d\n\n\n\n",sum);
    token ++;
    tokens[token]=sum;
    printf("\tYour token number is %d. Use this token while paying the bill.\n\n\n\n\n\t\t\t<enter (1) to give another order>\n\n\t\t\t<enter (2) to go to the main menu>\n\n\t\n\t\t\tEnter your choice: ",token);
    scanf("%d",&n);
    printf("\n\n\n");
    if(n==1)
    {
        menu_order();
    }
    else if(n==2)
    {
        main();

    }

}


void Bill_Payment()
{

    int k,i,cash,changer,n;
    redo:
    payment_counter++;
    system("cls");
    system("color 3F");
    printf("\n\n\n\t\t\tEnter your token number: ");
    scanf("%d",&k);
    printf("\t\t\tYour Total Bill is = %d",tokens[k]);
    work:
            printf("\n\t\t\tPay your bill: ");
            scanf("%d",&cash);
    changer = cash-tokens[k];
    if(changer == 0)
    {
        printf("\n\t\tThanks for your payment. Have a great day!\n");
    }
    else if (changer<0)
    {
        system("cls");
        printf("\n\t\t\tAmount is not sufficient. :(\n\t\tPlease pay the fair price of your bill\n");
        goto work;
    }
    else
    {
        printf("\n\n\n\t\tHere is your change : (%d - %d) = %d Tk.\n\t\t  ",cash,tokens[k],changer);

            for(i=0;i<19;i++)
            {
                printf("_");
            }
            if(changer>=1000 )
                {printf("\n\t\t1000 Tk. note(s) = %d\n",changer/1000);
                changer=changer%1000;}
            if(changer>=500 && changer<1000)
            {printf("\n\t\t 500 Tk. note(s) = %d\n",changer/500);
            changer=changer%500;}
            if(changer>=100 && changer<500)
            {printf("\n\t\t 100 Tk. note(s) = %d\n",changer/100);
            changer= changer%100;}
            if(changer>=50 && changer<100)
            {printf("\n\t\t  50 Tk. note(s) = %d\n",changer/50);
            changer=changer%50;}
             if(changer>=10 && changer<50)
            {printf("\n\t\t  10 Tk. note(s) = %d\n",changer/10);
            changer=changer%10;}
            if(changer>=5 && changer<10)
            {printf("\n\t\t   5 Tk. note(s) = %d\n",changer/5);
            changer=changer%5;}
            if(changer>=2 && changer<5)
            {printf("\n\t\t   2 Tk. note(s) = %d\n",changer/2);
            changer=changer%2;}
            if(changer>=1 && changer<2)
            {printf("\n\t\t   1 Tk. note(s) = %d\n",changer/1);
            changer=changer%1;}

            printf("\t\t  ");
            for(i=0;i<19;i++)
            {
                printf("_");
            }

        printf("\n\n\n\n\n\t\t\tThanks for your payment.\n\t\t\t    Have a great day!\n",changer);



    }
    printf("\n\n\t\t\t<Enter (1) to pay another bill.>\n\t\t\t<Enter (2) to go back main menu>\n\n\n\t\t\tEnter your choice: \t");
        scanf("%d",&n);
        if(n==2)
        {
            main();
        }
        else if(n==1)
        {
           goto redo;
        }

}


int main()
 {

    int k,j,n,d;
    k = main_page();

    if(k==1)
    {
        menu_order();
    }

    else if(k==2)
    {
        Bill_Payment();
    }

    else if(k==3)  // ADD THIS NEW CASE
    {
        reservation_system();
        main();  // Return to main menu after reservation system
    }

    else
    {
        system("cls");
        system("color 30");
        printf("\n\n\n\n\n\t\t       @@_@_\n\t\t         `'*'`  Cafe Nirvana\n\t\t\t\t\t`'*'`-@@_@\n\n");
        printf("\n\n\n\t\t\tThis session order recieved : %d\n\n",token);
        printf("\t\t\tThis session bill paid      : %d\n\n",payment_counter);
        if(payment_counter<token)
        {printf("\t\t\t\tYet to pay          : %d\n\n\n\n\n\n",token-payment_counter);}
        else
        {
            printf("\n\n\n\n\n\n");
        }
        return 0;
    }

 }