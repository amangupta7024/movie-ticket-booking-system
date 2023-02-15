#include"MTH.h"
#include<string.h>
#include<math.h>
#include"conio2.h"
#include<stdio.h>
#include<error.h>
#include<dir.h>
void print_char(char ch, int reps, int row, int text_color)
{
    textcolor(text_color);
    gotoxy(1, row);
    for(int i = 1; i <= reps; i++)
        printf("%c", ch);
}
void print_title(char * title, int column, int row, int text_color)
{
    textcolor(text_color);
    gotoxy(column, row);
    printf("%s", title);
}
void print_title_in_middle(char * title, int row, int text_color)
{
    textcolor(text_color);
    int column = (80 - strlen(title)) / 2;
    gotoxy(column, row);
    printf("%s", title);
}
void print_basic_screen()
{
    clrscr();
    print_char('-', 80, 1, LIGHTCYAN);
    print_title_in_middle("Movie Ticket Booking App", 2, MAGENTA);
    print_char('-', 80, 3, LIGHTCYAN);
    print_title("Enter \"0\" to cancel input", 56, 4, LIGHTGREEN);
    print_char('-', 80, 6, YELLOW);
    print_char('-', 80, 22, YELLOW);
}
void add_questions()
{
    FILE *fp=fopen("E:\\Movie Ticket Booking\\Questions.bin","rb");
    if(fp==NULL)
    {
        fp=fopen("E:\\Movie Ticket Booking\\Questions.bin","wb");
        if(fp==NULL)
        {
            print_char(' ',79,25,BLACK);
            print_title("Error in creating the file Questions.bin\n",1,25,RED);
            perror("Reason:");
            getch();
            exit(1);
        }
        char questions[][100] = {"Which adventurous sport does your father enjoy?", "Who is your favorite sports columnist?", "Which company would you like to work for in the future?", "What is the registration number of your first vehicle?", "What is the name of your best friend?", "Who is your favorite author?", "What is your favorite food?", "What is your favorite hobby?", "What is your favorite sport?", "Where did you meet your spouse?"};
        question ques[10];
        for(int i=0;i<=9;i++)
        {
            sprintf(ques[i].question_id,"Ques-%d",i+1);
            strcpy(ques[i].question,questions[i]);
        }
        fwrite(ques,sizeof(ques),1,fp);
        printf("\nQuestions.bin file created and saved!");
    }
    else
        printf("\nQuestions.bin already present");
    fclose(fp);
}
void set_master_admin_rec()
{
    FILE *fp=fopen("E:\\Movie Ticket Booking\\Users.bin","rb");
    if(fp==NULL)
    {
        fp=fopen("E:\\Movie Ticket Booking\\Users.bin","wb");
        if(fp==NULL)
        {
            print_char(' ',79,25,BLACK);
            print_title("Error in creating the file Users.bin\n",1,25,RED);
            perror("Reason:");
            getch();
            exit(1);
        }
        user usr={"master_admin","Aman Gupta","Bittu_2002","master_admin","","","7024859152"};
        fwrite(&usr,sizeof(usr),1,fp);
        printf("\nUsers.bin created and saved");
    }
    else
        printf("\nUsers.bin already exists");
    fclose(fp);
}
void get_string(char *str,int size)
{
    fflush(stdin);
    textcolor(RED);
    fgets(str,size,stdin);
    char *p;
    p=strchr(str,'\n');
    if(p!=NULL)
        *p='\0';
}
int is_valid_integer(char *str)
{
    while(*str)
    {
       if(isdigit(*str)==0)
           return 0;
       str++;
    }
    return 1;
}
char * get_mobile_number(int row,int col)
{
    static char mobile_number[20];
    int valid=0;
    do
    {
        print_title("Enter your mobile number: +91-",25,row,BROWN);
        get_string(mobile_number,20);
        if(strcmp(mobile_number,"0")==0)
        {
            return NULL;
        }
        if(is_valid_integer(mobile_number)==0 || strlen(mobile_number)!=10)
        {
            print_char(' ',80,25,BLACK);
            print_title_in_middle("Error! Mobile Number Is Incorrect. Please Try Again",25,RED);
            getch();
            print_char(' ',80,25,BLACK);
            print_char(' ',80,row,BLACK);
        }
        else
            valid=1;
    }while(valid==0);

    return mobile_number;
}
int check_mobile_number_in_records(char *mob_no)
{
  FILE *fp=fopen("E:\\Movie Ticket Booking\\Users.bin","rb");
  if(fp==NULL)
  {
      print_char(' ',79,25,BLACK);
      print_title("Error in opening the file Users.bin\n",1,25,RED);
      perror("Reason:");
      getch();
      return -1;
  }
  user u;
  while(fread(&u,sizeof(u),1,fp)==1)
  {
      if(strcmp(u.mobile_number,mob_no)==0)
      {
        fclose(fp);
        return 1;
      }
  }
  fclose(fp);
  return 0;

}
void get_password(char *pwd,int size)
{
    int i=0;
    char ch;
    fflush(stdin);
    textcolor(LIGHTRED);
    while(1)
    {
        ch=getch();
        if(ch==13)
            break;
        if(ch=='\b')
        {
            if(i==0)
                continue;
            i--;
            printf("\b \b");
            continue;
        }
        if(i==size-1)
            continue;
        printf("%c",ch);
        delay(100);
        printf("\b*");
        pwd[i]=ch;
        i++;
    }
    printf("\n");
    pwd[i]='\0';

}
user * get_credentials(char *usertype)
{
    print_basic_screen();
    if(strcmp(usertype,"master_admin")==0)
    print_title_in_middle("enter default username & password to setup your profile",10,LIGHTCYAN);
    static user u;
    strcpy(u.usertype,usertype);
    int valid=0;
    do
    {
        print_title("Enter user Id: ",30,12,BROWN);
        get_string(u.userid,100);
        if(strcmp(u.userid,"0")==0)
        {
            return NULL;
        }
        if(strlen(u.userid)==0)
        {
            print_char(' ',79,25,BLACK);
            print_title_in_middle("Error! user id can not be blank",25,RED);
            getch();
        }
        else{
            valid =1;
        }

    }while(valid==0);
    valid=0;
    do
    {
        print_title("Enter password: ",30,14,BROWN);
        get_password(u.password,100);
        if(strcmp(u.password,"0")==0)
        {
            return NULL;
        }
        if(strlen(u.password)==0)
        {
            print_char(' ',79,25,BLACK);
            print_title_in_middle("Error! user password can not be blank",25,RED);
            getch();
        }
        else{
            valid=1;
        }
    }while(valid==0);
    return &u;
}
int check_user_details(user *u)
{
    FILE *fp=fopen("E:\\Movie Ticket Booking\\users.bin","rb");
    if(fp==NULL)
    {
        print_char(' ',79,25,BLACK);
        print_title("Error in opening the file Users.bin",1,25,RED);
        perror("Reason:");
        getch();
        return -1;
    }
    user usr;
    int found=0;
    char temp[200];
    while(fread(&usr,sizeof(usr),1,fp)==1)
    {
        if(strcmp(u->usertype,"master_admin")==0)
        {
            //display the details of master admin
            print_title_in_middle("Contact with admin if you have any trouble during logging",20,YELLOW);
            strcpy(temp,"Admin Name:");
            strcat(temp,usr.username);
            print_title_in_middle(temp,23,YELLOW);
            strcpy(temp,"Admin Contact Details:");
            strcat(temp,usr.mobile_number);
            print_title_in_middle(temp,24,YELLOW);
        }
        if(strcmp(usr.userid,u->userid)==0 && strcmp(usr.password,u->password)==0 && strcmp(usr.usertype,u->usertype)==0)
        {
            found=1;
            *u=usr;
            break;
        }
    }
    fclose(fp);
    return found;

}
user * login(char *usertype)
{
    user *usr;
    char temp[100];
    int i;
    for(i=1;i<=3;i++)
    {
        usr=get_credentials(usertype);
        if(usr==NULL)
        {
            print_char(' ',80,25,BLACK);
            print_title_in_middle("Login Cancelled",25,BLUE);
            getch();
            break;
        }
        else
        {
            if(check_user_details(usr)==1)
            {
                print_char(' ',80,25,BLACK);
                print_title_in_middle("Login Accepted",25,GREEN);
                getch();
                return usr;
            }
            else
            {
                if(i!=3)
                {
                    sprintf(temp,"%d attempts left",3-i);
                    print_title(temp,67,8,DARKGRAY);
                    print_char(' ',79,25,BLACK);
                    print_title_in_middle("Invalid Userid/Password",25,RED);
                }
                else
                {
                  print_char(' ',80,25,BLACK);
                  print_title_in_middle("Login Denied",25,RED);
                  getch();
                }
            }
        }
    }
    return NULL;
}
void input_password(user *u,int column,int row)
{
    char pwd1[100],pwd2[100];
    int valid=0;
    do
    {
        do
        {
            print_title("Enter password:",column,row,BROWN);
            get_string(pwd1,100);
            if(strcmp(pwd1,"0")==0){
                strcpy(u->password,"0");
                return;
            }
            if(strlen(pwd1)>=1){
                valid=1;
            }
            else{
                  print_char(' ',80,25,BLACK);
                  print_title_in_middle("Password cannot be blank",25,RED);
                  getch();
                  print_char(' ',80,row,BLACK);
                }

        }while(valid==0);
        valid=0;
        do
        {
            print_title("Re-Type password:",column,row+2,BROWN);
            get_password(pwd2,100);
            if(strcmp(pwd2,"0")==0){
                strcpy(u->password,"0");
                return;
            }
            if(strlen(pwd2)>=1){
                valid=1;
            }
            else{
                  print_char(' ',80,25,BLACK);
                  print_title_in_middle("Password cannot be blank",25,RED);
                  getch();
                  print_char(' ',80,row+2,BLACK);
                }
        }while(valid==0);
        valid=0;
        if(strcmp(pwd1,pwd2)!=0){
                  print_char(' ',80,25,BLACK);
                  print_title_in_middle("Passwords do not match. Try Again",25,RED);
                  getch();
                  print_char(' ',80,row,BLACK);
                  print_char(' ',80,row+2,BLACK);
        }
        else{
            valid=1;
        }
    }while(valid==0);
    strcpy(u->password,pwd1);
    return;
}
void get_integer(int *p)
{
    char temp[100];
    get_string(temp,100);
    if(strcmp(temp,"0")==0){
        *p=0;
        return;
    }
    if(strlen(temp)==0 || is_valid_integer(temp)==0){
            *p=-1;
             return;
    }
    *p=atoi(temp);
}
char* get_question_id()
{
  FILE *fp=fopen("E:\\Movie Ticket Booking\\Questions.bin","rb");
  if(fp==NULL)
  {
      print_char(' ',79,25,BLACK);
      print_title("Error in opening the file Questions.bin\n",1,25,RED);
      perror("Reason:");
      getch();
      return NULL;
  }
    print_basic_screen();
    print_title("Question ID",5,8,YELLOW);
    print_title("Question",40,8,YELLOW);
    int row_no=10;
    int column_que_id=6;
    question que;
    while(fread(&que,sizeof(que),1,fp)==1){
        print_title(que.question_id,column_que_id,row_no,YELLOW);
        print_title(que.question,column_que_id+18,row_no,YELLOW);
        row_no++;
    }
    int valid=0;
    int id;
    static char question_id[100];
    do{
        print_title("Enter Question ID: Ques-",25,23,BROWN);
        get_integer(&id);
        if(id==0){
            fclose(fp);
            return NULL;
        }
        if(id==-1){
            print_char(' ',80,25,BLACK);
            print_title_in_middle("Invalid Number",25,RED);
            getch();
            print_char(' ',80,23,BLACK);
        }
        else{
            sprintf(question_id,"Ques-%d",id);
            rewind(fp);
            while(fread(&que,sizeof(que),1,fp)==1){
                    if(strcmp(question_id,que.question_id)==0){
                        valid=1;
                        break;
                    }
            }
            if(valid==0){
                print_char(' ',80,25,BLACK);
                print_title_in_middle("Question Id Is Incorect. Try Again",25,RED);
                getch();
                        print_char(' ',80,23,BLACK);
            }
        }

    }while(valid==0);
    fclose(fp);
    return question_id;
}
user* get_user_details(char *usertype)
{
    print_basic_screen();
    char msg[100]={"Registration Of "};
    strcat(msg,usertype);
    print_title_in_middle(msg,5,LIGHTGRAY);
    int row=8,column=25;
    print_title_in_middle("Enter Details Carefully",row,DARKGRAY);
    print_title("Enter Username:",column,row+2,BROWN);
    static user u;
    get_string(u.username,100);
    if(strcmp(u.username,"0")==0){
        return NULL;
    }
    input_password(&u,column,row+4);
    if(strcmp(u.password,"0")==0){
        return NULL;
    }
    int valid=0;
    char *p;
    do{
        p=get_mobile_number(row+8,column);
        if(p==NULL){
            return NULL;
        }
        if(check_mobile_number_in_records(p)==1){
                print_char(' ',80,25,BLACK);
                print_title_in_middle("Mobile Number Already Registered. Try Again",25,RED);
                getch();
                print_char(' ',80,row+8,BLACK);
        }else{
            valid=1;
        }

    }while(valid==0);
    strcpy(u.mobile_number,p);
    p=get_question_id();
    if(p==NULL){
        return NULL;
    }
    strcpy(u.question_id,p);
    valid=0;
    do{
        print_title("Enter Hint Answer:",25,24,BROWN);
        get_string(u.hint_answer,100);
        if(strcmp(u.hint_answer,"0")==0)
            return NULL;
        if(strlen(u.hint_answer)>=1)
            valid=1;
        else
        {
            print_char(' ',80,25,BLACK);
            print_title_in_middle("Answer Cannot Be Blank. Try Again",25,RED);
            getch();
            print_char(' ',80,24,BLACK);
        }

    }while(valid==0);
    return &u;
}
void create_user(char*usertype)
{
FILE *fp=fopen("E:\\Movie Ticket Booking\\Users.bin","ab+");
    if(fp==NULL)
    {
        print_char(' ',79,25,BLACK);
        print_title("Error in opening the file Users.bin\n",1,25,RED);
        perror("Reason:");
        getch();
        exit(1);
    }
    user usr;
    user *up;
    char temp[100];
    char *p;
    if(strcmp(usertype,"admin")==0){
        fseek(fp,-(long long signed int)sizeof(usr),SEEK_END);
        fread(&usr,sizeof(usr),1,fp);
        //if(strcmp(usr.usertype,"master_admin")!=0)
        //return ;
        up=login("master_admin");
        if(up!=NULL){
            up=get_user_details("admin");
            if(up==NULL){
                printf("up is NULL");
                getch();
                print_char(' ',80,25,BLACK);
                print_title_in_middle("Cancelling The Admin Profile SetUp",25,RED);
                fclose(fp);
                getch();
                exit(0);
            }
            strcpy(up->userid,"admin");
            strcpy(up->usertype,"admin");
            //set fp to end
            fseek(fp,0,SEEK_END);
            fwrite(&up,sizeof(user),1,fp);
            print_basic_screen();
            print_title_in_middle("admin register successfully",10,YELLOW);
            strcpy(temp,"User Name: ");
            strcat(temp,up->username);
            print_title_in_middle(temp,13,YELLOW);
            strcpy(temp,"User Id: ");
            strcat(temp,up->userid);
            print_title_in_middle(temp,15,YELLOW);
            strcpy(temp,"Mobile Number: ");
            strcat(temp,up->mobile_number);
            print_title_in_middle(temp,17,YELLOW);
            getch();
        }
        else
        {
          print_char(' ',80,25,BLACK);
          print_title_in_middle("Cancelling The Admin Profile SetUp",25,RED);
          fclose(fp);
          getch();
          exit(0);
        }
    }
    else if(strcmp(usertype,"user")==0)
    {
        fseek(fp,-(long long signed int)sizeof(usr),SEEK_END);
        fread(&usr,sizeof(usr),1,fp);
        if(strcmp(usr.usertype,"admin")==0)
        {
            sprintf(temp,"USER-%d",1);
        }
        else{
            p=strchr(usr.userid,'-');
            int last_digit=atoi(p+1);
            last_digit++;
            sprintf(temp,"USER-%d",last_digit);
        }
        up=get_user_details("user");
        if(up==NULL){
                print_char(' ',80,25,BLACK);
                print_title_in_middle("Cancelling The user Profile SetUp",25,RED);
                fclose(fp);
                getch();
                exit(0);
            }
        strcpy(up->userid,temp);
        strcpy(up->usertype,"user");
        fseek(fp,0,SEEK_END);
        fwrite(up,sizeof(user),1,fp);
        print_basic_screen();
        print_title_in_middle("user register successfully",10,YELLOW);
        strcpy(temp,"User Name: ");
        strcat(temp,up->username);
        print_title_in_middle(temp,13,YELLOW);
        strcpy(temp,"User Id: ");
        strcat(temp,up->userid);
        print_title_in_middle(temp,15,YELLOW);
        strcpy(temp,"Mobile Number: ");
        strcat(temp,up->mobile_number);
        print_title_in_middle(temp,17,YELLOW);
        getch();

    }
    fclose(fp);
}
int enter_login_choice()
{
    int choice;
    int row=10;
    int column=32;
    print_basic_screen();
    print_title_in_middle("select an option",9,YELLOW);
    print_title("1. admin",column,row++,YELLOW);
    print_title("2. user(login)",column,row++,YELLOW);
    print_title("3. user(sign-up)",column,row++,YELLOW);
    int valid=0;
    do{
        print_title_in_middle("enter your choice: ",row+1,YELLOW);
        get_integer(&choice);
        if(choice==-1)
        {
            print_char(' ',80,25,BLACK);
            print_title_in_middle("only digit allow! plz try again",25,RED);
            getch();
            print_char(' ',80,row+1,BLACK);
        }
        else{
            valid=1;
        }
    }while(valid==0);
    return choice;
}
int enter_choice(user *ur)
{
    print_basic_screen();
    char temp[100];
    strcpy(temp,ur->usertype);
    strcat(temp,": ");
    strcpy(temp,ur->username);
    print_title(temp,1,5,YELLOW);
    print_title_in_middle("select an option",8,YELLOW);
    int row=9,column=28;
    if(strcmp(ur->usertype,"admin")==0)
    {
        row=9,column=28;
        print_title("1.add theater",column,++row,YELLOW);
        print_title("2.show theater",column,++row,YELLOW);
        print_title("3.delete theater",column,++row,YELLOW);
        print_title("4.add moive",column,++row,YELLOW);
        print_title("5.show moive",column,++row,YELLOW);
        print_title("6.delete moive",column,++row,YELLOW);
        print_title("7.change contact detail",column,++row,YELLOW);
        print_title("8.change security question",column,++row,YELLOW);
        print_title("9.change password",column,++row,YELLOW);
        print_title("10.view my profile",column,++row,YELLOW);
    }
    else{
        row=10,column=28;
        print_title("1.show movie",column,++row,YELLOW);
        print_title("2.book ticket",column,++row,YELLOW);
        print_title("3.view booking",column,++row,YELLOW);
        print_title("4.cancel booking",column,++row,YELLOW);
        print_title("5.change contact detail",column,++row,YELLOW);
        print_title("6.change security question",column,++row,YELLOW);
        print_title("7.change password",column,++row,YELLOW);
        print_title("8.view my profile",column,++row,YELLOW);
        print_title("9.delete my account",column,++row,YELLOW);
    }
    int choice,valid=0;
    do{
        print_title_in_middle("Enter Your Choice: ",row+2,YELLOW);
        get_integer(&choice);
        if(choice==-1)
        {
            print_char(' ',80,25,BLACK);
            print_title_in_middle("Only Digits Allowed! Try Again",25,RED);
            getch();
            print_char(' ',80,row+2,BLACK);
        }
        else{
            valid=1;
        }
    }while(valid==0);
    return choice;
}
void add_theater()
{
    print_basic_screen();
    FILE *fp=fopen("E:\\Movie Ticket Booking\\Theater.bin","ab+");
    if(fp==NULL)
    {
        print_char(' ',79,25,BLACK);
        print_title("Error in opening the theater.bin\n",1,25,RED);
        perror("Reason:");
        getch();
        return ;
    }
    theater th;
    fseek(fp,0,SEEK_END);
    if(ftell(fp)==0)
    {
        strcpy(th.theater_id,"Theater-1");
    }
    else{
       fseek(fp,-(long long signed int)sizeof(th),SEEK_END);
        fread(&th,sizeof(th),1,fp);
        char *p=strchr(th.theater_id,'-');
        int last_id=atoi(p+1);
        last_id++;
        sprintf(th.theater_id,"Theater-%d",last_id);
    }
    th.is_booked=0;
    int valid=0;
    do{
        print_title("enter theater name: ",25,12,YELLOW);
        get_string(th.theater_name,100);
        if(strcmp(th.theater_name,"0")==0)
        {
            print_char(' ',79,25,BLACK);
            print_title("cancelling add theater",1,25,RED);
            fclose(fp);
            getch();
            return ;
        }
        if(strlen(th.theater_name)==0)
        {
            print_char(' ',79,25,BLACK);
            print_title("theater name can not be blank",1,25,RED);
            getch();
            print_char(' ',80,12,BLACK);
            return ;
        }
        else
            valid=1;
    }while(valid==0);
    fseek(fp,0,SEEK_END);
    fwrite(&th,sizeof(th),1,fp);
    fclose(fp);
    char temp[100];
    strcpy(temp,"theater added successfully! theater Id is ");
    strcat(temp,th.theater_id);
    print_title_in_middle(temp,15,YELLOW);
    getch();
}
void show_theater()
{
    print_basic_screen();
    FILE *fp=fopen("E:\\Movie Ticket Booking\\Theater.bin","rb");
    if(fp==NULL)
    {
        print_char(' ',79,25,BLACK);
        print_title("Error in opening the theater.bin\n",1,25,RED);
        perror("Reason:");
        getch();
        return ;
    }
    fseek(fp,0,SEEK_END);
    if(ftell(fp)==0)
    {
        print_char(' ',79,25,BLACK);
        print_title("no theater present in file",1,25,RED);
        fclose(fp);
        getch();
        return ;
    }
    rewind(fp);
    int row=8;
    print_title("theater Id",5,row,YELLOW);
    print_title("theater name ",25,row,YELLOW);
    print_title("theater booking status",50,row,YELLOW);
    theater th;
    char temp[100];
    row+=2;
    while(fread(&th,sizeof(th),1,fp)==1)
    {
       print_title(th.theater_id,5,row,YELLOW);
       print_title(th.theater_name,25,row,YELLOW);
       if(th.is_booked==0)
            strcpy(temp,"available for booking");
       else
            strcpy(temp,"already booked");
        print_title(temp,50,row,YELLOW);
        row++;
    }
    fclose(fp);
    getch();
}
char * get_theater_id(int status)
{
    print_basic_screen();
    FILE *fp=fopen("E:\\Movie Ticket Booking\\Theater.bin","rb");
    if(fp==NULL)
    {
        print_char(' ',79,25,BLACK);
        print_title("Error in opening the theater.bin\n",1,25,RED);
        perror("Reason:");
        getch();
        return NULL;
    }
    fseek(fp,0,SEEK_END);
    if(ftell(fp)==0)
    {
        print_char(' ',79,25,BLACK);
        print_title("no theater present in file",1,25,RED);
        fclose(fp);
        getch();
        return NULL;
    }
    rewind(fp);
    static char th_id[100];
    int row=8;
    print_title("theater Id",5,row,YELLOW);
    print_title("theater name ",25,row,YELLOW);
    print_title("theater booking status",50,row,YELLOW);
    theater th;
    while(fread(&th,sizeof(th),1,fp)==1)
    {
        if(th.is_booked==0)
        {
             print_title(th.theater_id,5,row,YELLOW);
             print_title(th.theater_name,25,row,YELLOW);
             print_title("avilable for booking",45,row,YELLOW);
        }
        else{
            if(status==1)
                continue;
            else{
                print_title(th.theater_id,5,row,YELLOW);
                print_title(th.theater_name,25,row,YELLOW);
                print_title("already booked.",45,row,YELLOW);
            }
            row++;
        }
    }
    int valid=0;
    int id;
    do
    {
        print_title("Enter Theater ID: THEATER-",25,23,YELLOW);
        get_integer(&id);
        if(id==0)
        {
            fclose(fp);
            return NULL;
        }
        if(id==-1)
        {
            print_char(' ',80,25,BLACK);
            print_title_in_middle("Only Digits Allowed. Try Again",25,RED);
            getch();
            print_char(' ',80,23,BLACK);
        }
        else
        {
            sprintf(th_id,"THEATER-%d",id);
            rewind(fp);
             while(fread(&th,sizeof(th),1,fp)==1)
             {
                 if(status==0)
                 {
                     if(strcmp(th.theater_id,th_id)==0)
                     {
                         valid=1;
                         break;
                     }
                 }
                 else
                 {
                     if(strcmp(th.theater_id,th_id)==0 && th.is_booked==0)
                     {
                         valid=1;
                         break;
                     }
                 }
             }
             if(valid==0)
             {
                print_char(' ',80,25,BLACK);
                print_title_in_middle("Invalid ID. Try Again",25,RED);
                getch();
                print_char(' ',80,23,BLACK);
             }

        }

    }while(valid==0);
    fclose(fp);
    return th_id;
}
int delete_booking_by_movie_id(char* movie_id)
{
    print_basic_screen();
    FILE *fp1=fopen("E:\\Movie Ticket Booking\\Bookings.bin","rb");
    if(fp1==NULL)
    {
        print_char(' ',79,25,BLACK);
        print_title("Error in opening the file Bookings.bin\n",1,25,RED);
        perror("Reason:");
        getch();
        return 0;
    }
    FILE *fp2=fopen("c:\\Movie Ticket Booking\\TempBookings.bin","wb");
    if(fp2==NULL)
    {
        print_char(' ',79,25,BLACK);
        print_title("Error in opening the file TempBookings.bin\n",1,25,RED);
        perror("Reason:");
        getch();
        return 0;
    }
    ticket tk;
    while(fread(&tk,sizeof(tk),1,fp1)==1)
    {
        if(strcmp(tk.movie_id,movie_id)!=0)
        {
            fwrite(&tk,sizeof(tk),1,fp2);
        }

    }
    fclose(fp1);
    fclose(fp2);
    int x,y;
    x=remove("E:\\Movie Ticket Booking\\Bookings.bin");
    if(x==0)
    {
        y=rename("E:\\Movie Ticket Booking\\TempBookings.bin","E:\\Movie Ticket Booking\\Bookings.bin");
        if(y==0)
            return 1;
    }
    return 0;
}
int delete_movie_by_theater_id(char *th_id)
{
    FILE *fp1=fopen("E:\\Movie Ticket Booking\\Movies.bin","rb");
    if(fp1==NULL)
    {
        print_char(' ',79,25,BLACK);
        print_title("Error in opening the file Movies.bin\n",1,25,RED);
        perror("Reason:");
        getch();
        return 0;
    }
    FILE *fp2=fopen("E:\\Movie Ticket Booking\\TempMovies.bin","wb");
    if(fp2==NULL)
    {
        print_char(' ',79,25,BLACK);
        print_title("Error in opening the file TempMovies.bin\n",1,25,RED);
        perror("Reason:");
        getch();
        fclose(fp1);
        return 0;
    }
    movie mov;
    while(fread(&mov,sizeof(mov),1,fp1)==1)
    {
        if(strcmp(mov.theater_id,th_id)!=0)
        {
            fwrite(&mov,sizeof(mov),1,fp2);
        }
        else
        {
            int resp=delete_booking_by_movie_id(mov.movie_id);
            if(resp==0)
            {
                fclose(fp1);
                fclose(fp2);
                remove("E:\\Movie Ticket Booking\\TempMovies.bin");
                return 0;
            }
        }

    }
    fclose(fp1);
    fclose(fp2);
    int x,y;
    x=remove("E:\\Movie Ticket Booking\\Movies.bin");
    if(x==0)
    {
        y=rename("E:\\Movie Ticket Booking\\TempMovies.bin","E:\\Movie Ticket Booking\\Movies.bin");
        if(y==0)
            return 1;
    }
    return 0;
}
















