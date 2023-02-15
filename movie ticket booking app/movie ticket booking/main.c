#include <stdio.h>
#include <stdlib.h>
#include"conio2.h"
#include<string.h>
#include<error.h>
#include<dir.h>
#include"MTH.h"

int main()
{
    int result;
    result=mkdir("E:\\Movie Ticket Booking");
    if(result!=0 && errno!=17)
    {
        printf("Sorry! Application cannot run");
        printf("\nError Code:%d,",errno);
        perror("Reason:");
        return 1;
    }
    add_questions();
    set_master_admin_rec();
    create_user("admin");
    int choice;
    user *ur;
    while(1)
    {
        choice=enter_login_choice();
        if(choice==0)
            break;
        switch(choice)
        {
        case 1:
            ur=login("admin");
            if(ur==NULL)
                break;
                while(1){
                    choice=enter_choice(ur);
                    printf("Got %d",choice);
                    getch();
                    if(choice==0)
                    break;
                switch(choice){
                case 1:
                    add_theater();
                    break;
                case 2:
                    show_theater();
                    break;
                case 3:
                      //delete_theater();
                      break;
                case 4:
                    //add_movie();
                    break;
                case 5:
                    //show_movie();
                    break;
                case 6:
                    //delete_movie();
                    break;
                case 7:
                    //change_contact_details();
                    break;
                case 8:
                    //change_security_question();
                    break;
                case 9:
                    //change_password();
                    break;
                case 10:
                    // view_profile();
                    break;
                default:
                    print_char(' ',80,25,BLACK);
                    print_title_in_middle("Invalid Choice! Try Again",25,RED);
                    getch();

                }
                }

        case 2:
            //user as login
            break;
        case 3:
            //user as create account
            break;
        default:
            print_char(' ',80,25,BLACK);
            print_title_in_middle("only digit allow! plz try again",25,RED);
            getch();

        }

    }
    return 0;

}
