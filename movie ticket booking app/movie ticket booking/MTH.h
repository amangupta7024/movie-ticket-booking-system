#ifndef MTH_H_INCLUDED
#define MTH_H_INCLUDED
#include<time.h>
typedef struct
{
    char userid[100];
    char username[100];
    char password[100];
    char usertype[100];
    char question_id[100];
    char hint_answer[100];
    char mobile_number[11];
} user;
typedef struct
{
    int seat_number;
    int seat_is_booked;
} seat;
typedef struct
{
    char theater_id[100];
    char movie_id[100];
    char movie_name[100];
    int first_block_price;
    int second_block_price;
    int third_block_price;
    struct tm show_date;
    seat seats[100];
}movie;
typedef struct
{
    char theater_id[100];
    char theater_name[100];
    int is_booked;
}theater;
typedef struct
{
    char ticket_id[100];
    char theater_id[100];
    char movie_id[100];
    struct tm show_date;
    int seat_number;
    char user_id[100];
}ticket;
typedef struct
{
    char question_id[100];
    char question[100];
}question;
//basic screen function
void print_char(char, int, int, int);
void print_title(char *, int, int, int);
void print_title_in_middle(char *, int, int);
void print_basic_screen();

//inputing functions
void input_password(user *, int, int);
int check_name(char *);
int is_valid_integer(char * str);
void get_string(char *, int);
void get_password(char *, int);
char * get_mobile_number(int, int);
void add_questions();
user * get_user_details();
void create_user(char *);
void get_integer(int *);

user * get_credentials(char *);
void set_master_admin_rec();
int check_user_details(user *);
void forget_credentials(user *);
char * get_question_id();
int check_mobile_number_in_records(char *);
user * login(char *);
int enter_login_choice();
int enter_choice(user*);
void add_theater();
void show_theater();
//deleting theater and movie
int delete_theater();
char * get_theater_id(int);
int delete_movie_by_theater_id(char *);
int delete_booking_by_movie_id(char *);







#endif // MTH_H_INCLUDED
