#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include <string.h>
#include<time.h>
#include <unistd.h>


char BOOK_AVL[] = "A";
char BOOK_ISS[] = "I";
char password[10];

void add_book();
void view_book();
void delete_book();
void delete_student();
void add_student();
void view_student();
void issue_book();
int update_book_status(char id[], char status[]);
struct book book_avl(char book_id[]);
struct student std_avl(char std_id[]);
int delete_issue_book(char b_id[]);
void list_issued_book();
void ret_book();
void sign_up();
void get_password(char* pass);

typedef struct book{
	char id[10];
	char name[50];
	char author[50];
    char publication[50];
	char price[5];
	char status[10];
}b;
typedef struct student{
	char id[10];
	char sname[50];
	char bookname[50];
	char sroll[10];
	char date[12];
}stu;

int main()
{

        if(login()!=0)
        {
            exit;
        }
        int ch=0;
        top:
		system("cls");
		printf("<================Library management system ==============>\n");
		printf("\t 1. Add Book\n");
		printf("\t 2. View Book\n");
		printf("\t 3. Delete Book\n");
		printf("\t 4. Add Student\n");
		printf("\t 5. View Students\n");
		printf("\t 6. Delete Student\n");
		printf("\t 7. Book Issue\n");
		printf("\t 8. Book Return\n");
		printf("\t 9. View Book Status\n");
		printf("\t 0. Exit\n\n");
		printf("Enter your choice:(0-9)");
		scanf("%d",&ch);

		switch (ch){
			case 1:
				add_book();
				break;
            case 2:
                view_book();
                break;
            case 3:
                delete_book();
                break;
            case 4:
                add_student();
                break;
            case 5:
                view_student();
                break;
            case 6:
                delete_student();
                break;
            case 7:
                issue_book();
                break;
            case 8:
                ret_book();
                break;
            case 9:
                list_issued_book();
                break;
            case 0:
			    exit(0);
			    break;
            default:
                printf("invalid choice...\n\n");
		}
		printf("press any key to continue...");
		getch();
	goto top;
	return 0;
}
//////////////////////////////////////////////////// Book part ////////////////////////////////
//////////////////////////////////////////////////   Add Book ////////////////////////////////////////
void add_book()
{
    FILE *fp;
    struct book b;
    fp = fopen("book.dat", "a");
    if(fp == NULL)  // check if the file created of not
    {
       printf("Error during file creation!!!");
       sleep(3);
       main(); // go to book option
    }
    top:
    system("cls");
    printf("\nEnter Book ID:");
    scanf("%s", b.id);
    printf("\nEnter Book Name:");
    scanf("%s", b.name);
    printf("\nEnter Author Name:");
    scanf("%s", b.author);
    printf("\nEnter Publication Name:");
    scanf("%s", b.publication);
    printf("\nEnter Price:");
    scanf("%s", b.price);
    if(fprintf(fp,"\n%s\t" "%s\t" "%s\t" "%s\t" "%s\t" "%s", b.id, b.name, b.author, b.publication, b.price, BOOK_AVL)>0)
    {
        printf("\nBook added successfully!!!");
    }
    printf("\nDo you want to add more books? (Y/N)");
    if(getch()=='y'||getch()=='Y')
    {
        goto top;
    }
    else if(getch()=='n'||getch()=='Y')
    {
        fclose(fp);
        main();
    }
    printf("Wrong option selected!!!");
    fclose(fp);
    sleep(3);
    main();

}
///////////////////////////// View Book /////////////////////////////////
void view_book()
{
    FILE *fp;
    b b1[100];
    int ch;
    //system("cls");

    fp = fopen("book.dat", "r");
    if (fp == NULL)
    {
        printf("file can't be opened \n");
        getch();
    }
    int i = 0;
    printf("\nBookID \t\tName \t\tAuthor \t\tPublication \t\tPrice\tAvailibility");
    printf("\n==================================================================================================\n");
    while(fscanf(fp,"%s%s%s%s%s%s", &b1[i].id, &b1[i].name, &b1[i].author, &b1[i].publication, &b1[i].price, &b1[i].status)!=EOF)
    {
        printf("%s\t\t" "%s\t\t" "%s\t\t" "%s\t\t" "\t%s\t" "%s\n", b1[i].id, b1[i].name, b1[i].author, b1[i].publication, b1[i].price, b1[i].status);
        i++;
    }
    printf("\nPress any key to go main menu...");
    getch();
    main();
}
////////////////////////////////////////////////////// Delete Book //////////////////////////////////////////////
void delete_book()
{

    FILE *fp, *ft;
    b b1[100];
    b b2[100];
    char deleteBookID[10], tbookID[10];
    int i=0, j=0;
    printf("\nEnter Book ID to delete book from system");
    scanf("%s", deleteBookID);
    fp = fopen("book.dat", "r+");
    if (fp == NULL)
    {
        printf("file can't be opened \n");
        getch();
    }
    top:
    while(fscanf(fp,"%s%s%s%s%s%s", &b2[i].id, &b2[i].name, &b2[i].author, &b2[i].publication, &b2[i].price, &b2[i].status)!=EOF)
    {
        if(strcmp(deleteBookID,b2[i].id)==0)
        {
            printf("\n\t\tRecord found!!!");
            printf("\nBookID \tName \tAuthor \tPublication \tPrice \t Status");
            printf("\n===========================================================");
            printf("\n%s\t" "%s\t" "%s\t" "%s\t" "%s\t" "%s", b2[i].id, b2[i].name, b2[i].author,b2[i].publication, b2[i].price, b2[i].status);
            printf("\nDo you want to delete it?(Y/N):");
            if(getch()=='y')
            {
                rewind(fp);  // set the file pointer beginning of the file.
                ft=fopen("temp.dat","wb"); // create temporary file to store data.
                fflush(stdin); //flush data from buffer
                printf("%s\n", ft);
                while(fscanf(fp,"%s%s%s%s%s%s", &b2[i].id, &b2[i].name, &b2[i].author, &b2[i].publication, &b2[i].price, &b2[i].status)!=EOF)
                {
                    if(strcmp(deleteBookID,b2[j].id)!=0)
                    {
                        fprintf(ft,"\n%s\t" "%s\t" "%s\t" "%s\t" "%s\t" "%s", b2[i].id, b2[i].name, b2[i].author,b2[i].publication, b2[i].price, b2[i].status);
                    }
                    j++;
                }
                _fcloseall(); ///close all file
                remove("book.dat");
                rename("temp.dat","book.dat");
                printf("\n\t\tThe record is successfully deleted!!!");
                sleep(3);
                main();
            }
            else
            {
                 fclose(fp);
                printf("\n Cancelled!!!");
                sleep(3);
                main();
            }
        }
        i++;
    }
    printf("\n Book not found!!!\n Do you want to search with another ID?(Y/N)");
    if(getch()=='y')
    {
        goto top;
    }
    else if(getch()=='n')
    {
        fclose(fp);
        main();
    }
    printf("Wrong option selected!!!");
    fclose(fp);
    sleep(3);
    main();
    getch();
    goto top;
}

///////////////////////////student part//////////////////
//////////////////////////add student///////////////////
void add_student()
{
    FILE *fp;
    struct student s;
    fp = fopen("student.dat","a");
    if (fp==NULL)
    {
        printf("Error during creation!!!");
        sleep(3);
        main();
    }
    top:
    system("cls");
    printf("\n Enter student id:");
    scanf("%s",s.id);
    printf("\n Enter student sname:");
    scanf("%s",s.sname);
    printf("\n Enter student sroll:");
    scanf("%s",s.sroll);
    if(fprintf(fp,"\n%s\t" "%s\t" "%s",s.id,s.sname,s.sroll)>0)
    {
        printf("\nStudent added successfully!!!");
    }
    printf("Do you add more students?(Y/N)");
    if(getch()=='y' || getch()=='Y')
    {
        goto top;
    }
    else if(getch()=='n'|| getch()=='N')
    {
        fclose(fp);
        main();
    }
    printf("wrong option selected!!!");
    fclose(fp);
    sleep(3);
    main();
}
///////////////////////////// View Students /////////////////////////////////
void view_student()
{
    FILE *fp;
    struct student st[100];
    int ch;
    system("cls");
    fp = fopen("student.dat", "r");
    if (fp == NULL)
    {
        printf("file can't be opened \n");
        getch();
    }
    int i = 0;
    printf("\nStudent ID \t\tStudent's Name \t\tRoll No.\n");
    printf("\n============================================================================\n");
    while(fscanf(fp,"%s%s%s", &st[i].id, &st[i].sname, &st[i].sroll) != EOF)
    {
        printf("%s\t\t" "%s\t\t" "\t%s\n",  &st[i].id, &st[i].sname, &st[i].sroll);
        i++;
    }
    printf("\nPress any key to go main menu...");
    getch();
    main();
}
////////////////////////////////////////////////////// Delete Student//////////////////////////////////////////////
void delete_student()
{

    FILE *fp, *ft;
    struct student s1[100];
    struct student s2[100];
    char deleteStudentID[10], tStudentID[10];
    int i=0, j=0;
    printf("\nEnter student ID to student from system");
    scanf("%s", deleteStudentID);
    fp = fopen("student.dat", "r+");

    if (fp == NULL)
    {
        printf("file can't be opened \n");
        getch();
    }
    top:
    while(fscanf(fp,"%s%s%s", &s1[i].id, &s1[i].sname, &s1[i].sroll)!=EOF)
    {
        if(strcmp(deleteStudentID,s1[i].id)==0)
        {
            printf("\n\t\tRecord found!!!");
            printf("\nStudentID \tStudent's Name \tStudent's roll");
            printf("\n================================================");
            printf("\n%s\t" "%s\t" "%s\t", s1[i].id, s1[i].sname, s1[i].sroll);
            printf("\nDo you want to delete it?(Y/N):");
            if(getch()=='y' || getch()=='Y')
            {
                rewind(fp);  // set the file pointer beginning of the file.
                ft=fopen("stemp.dat","wb"); // create temporary file to store data.
                fflush(stdin); //flush data from buffer
                while(fscanf(fp,"%s%s%s", &s2[i].id, &s2[i].sname, &s2[i].sroll)!=EOF)
                {
                    if(strcmp(deleteStudentID,s2[j].id)!=0)
                    {
                        fprintf(ft,"%s\t" "%s\t" "%s\n", s2[i].id, s2[i].sname, s2[i].sroll);
                    }
                    j++;
                }
                _fcloseall(); // close all file

                if(!remove("student.dat"))
                   {
                       printf("Deleted!!!");
                   }
                if(!rename("stemp.dat","student.dat"))
                   {
                       printf("\n Renamed!!!");
                   }
                printf("\n\t\tThe Student's record is successfully deleted!!!");
                sleep(4);
                main();
            }
            else
            {
                fclose(fp);
                printf("\n Cancelled!!!");
                sleep(3);
                main();
            }
        }
        i++;
    }
    printf("\n Book not found!!!\n Do you want to search with another ID?(Y/N)\n");
    if(getch()=='y'||getch()=='Y')
    {
        goto top;
    }
    else if(getch()=='n'|| getch()=='N')
    {
        fclose(fp);
        main();
    }
    printf("\nWrong option selected!!!");
    fclose(fp);
    sleep(3);
    main();
    goto top;
}
///////////////////////////////////////////////////////Library Part ///////////////////////////////////////////////////////
///////////////////////////////////////////////////////Check Book avalibility ////////////////////////////////////////////////////////
struct book book_avl(char book_id[])
{
    FILE *fp;
    b b1;
    fp = fopen("book.dat", "r");
    if (fp == NULL)
    {
        printf("file can't be opened \n");
        getch();
    }
    while(fscanf(fp,"%s%s%s%s%s%s", &b1.id, &b1.name, &b1.author, &b1.publication, &b1.price, &b1.status)!=EOF)
    {
        if(strcmp(book_id,b1.id)==0)
        {

                fclose(fp);
                return b1;

        }
    }
    fclose(fp);
    printf("\n Book Not found!!! Try again!!!");
    sleep(3);
    main();
}
///////////////////////////////////////////////Check Student  ///////////////////////////////////
struct student std_avl(char std_id[])
{
    FILE *fp;
    struct student s1;
    int i=0;
    fp = fopen("student.dat", "r");
    if (fp == NULL)
    {
        printf("file can't be opened \n");
        getch();
    }
    while(fscanf(fp,"%s%s%s", &s1.id, &s1.sname, &s1.sroll)!=EOF)
    {
        if(strcmp(std_id,s1.id)==0)
        {
                fclose(fp);
                return s1;
        }
        i++;
    }
    fclose(fp);
    printf("\n Student Not found!!! Try again!!!");
    sleep(3);
    main();

}
////////////////////////////////////////////////issue book ////////////////////////////////////////
void issue_book()
{
    system("cls");
    char s_id[10],  b_id[10];
    printf("\nEnter student's id to issue book:");
    scanf("%s", s_id);
    printf("\n Enter book id:");
    scanf("%s", b_id);
    struct student s = std_avl(s_id);
    struct book b = book_avl(b_id);
    if(strcmp(BOOK_AVL, b.status)==0)
    {
        printf("\n\t\t\tBook Details: \nBook Id: %s\t" "Book Name %s\t" "Publication: %s\t" "Status: %s",  b.id, b.name, b.publication, b.status);
    }
    else
    {
        printf("\nBook issued to another student \n Try after getting it back!!!");
        sleep(3);
        main();
    }
    printf("\n\t\t\t Student Details: \nStudent ID: %s\t" "Student's Name: %s\t" "Roll No: %s\n",  s.id, s.sname, s.sroll);
    printf("\n\nDo you want issue %s to %s?(Y/N)", b.name, s.sname);
    if(getch()=='y'||getch()=='Y')
    {
        FILE *fp;
        fp = fopen("issue.dat", "a");
        if (fp == NULL)
        {
            printf("file can't be opened \n");
            getch();
        }
        if(fprintf(fp,"\n%s\t" "%s\t" "%s\t" "%s\t" "%s",s.id,s.sname,s.sroll,b.id,b.name)>0)
        {
            int a = update_book_status(b.id, BOOK_ISS);
            if(a>0)
            {
                printf("\nBook issued successfully!!!");
                fclose(fp);
                sleep(3);
                main();
            }
            else
            {
                printf("\n Failed to issue book!!!\tPress any key to continue....");
                getch();
            }
        }
        else
        {
            printf("Error!!");
            getch();
            main();
        }

    }
    else if(getch()=='n'|| getch()=='N')
    {
        main();
    }
    printf("\nWrong option selected!!!");
    sleep(3);
    main();
}
///////////////////////////////////////////////////////update book status ///////////////////////////////////////
int update_book_status(char id[], char status[])
{
    FILE *fp, *ft;
    b b2[100];
    int i =0;
    fp = fopen("book.dat", "r+");
    if (fp == NULL)
    {
         printf("file can't be opened \n");
         getch();
    }
    ft=fopen("temp.dat","wb"); // create temporary file to store data.
    fflush(stdin); //flush data from buffer
    while(fscanf(fp,"%s%s%s%s%s%s", &b2[i].id, &b2[i].name, &b2[i].author, &b2[i].publication, &b2[i].price, &b2[i].status)!=EOF)
    {
        if(strcmp(b2[i].id, id)==0)
        {
            strcpy(b2[i].status, status);
        }
        fprintf(ft,"\n%s\t" "%s\t" "%s\t" "%s\t" "%s\t" "%s", b2[i].id, b2[i].name, b2[i].author,b2[i].publication, b2[i].price, b2[i].status);
        i++;
    }
    _fcloseall(); ///close all file
    int fa = remove("book.dat");
    int fb = rename("temp.dat","book.dat");
    if(fa==0 && fb==0)
    {
        return 1;

    }
    else
    {
        return 0;
    }
}
/////////////////////////////////////////////////return book/////////////////////////////////////////
void ret_book()
{
    FILE *fp;
    b books; // book structure
    stu st; // student structure
    system("cls");
    char s_id[10],  b_id[10];
    printf("\n Enter book id that you want to return:");
    scanf("%s", b_id);
    fp = fopen("issue.dat", "r+");
    if (fp == NULL)
    {
         printf("file can't be opened \n");
         getch();
    }
    while(fscanf(fp,"%s%s%s%s%s", &st.id, st.sname, &st.sroll, &books.id, books.name)!=EOF)
    {
       if(strcmp(books.id, b_id) == 0)
       {
           printf("\nStudent ID \tStudent's Name \tRoll No. \tBook ID \tBook Name\n");
           printf("\n------------------------------------------------------------------------------\n");
           printf("%s\t\t" "%s\t\t" "%s\t\t" "%s\t\t" "%s\n",  st.id, st.sname, st.sroll, books.id, books.name);
           fclose(fp);
           printf("\nAre you sure to return this book?(Y/N)");
           if(getch()=='y'|| getch()=='Y')
            {
                int a = update_book_status(books.id, BOOK_AVL); //make book available from book file
                int b = delete_issue_book(books.id); // delete record from issue
                if(a>0 && b>0)
                {
                    printf("\nBook returned successfully!!!");
                    sleep(3);
                    main();
                }
            }
            else
            {
                printf("\n\tCanceled!!!\nPress any key to continue....");
                getch();
            }
       }
    }
    printf("\nRecord not found!!!");
    fclose(fp);
    getch();
    main();
}
//////////////////////////////////////////////////////////view status /////////////////////////////////////////
void list_issued_book()
{
    FILE *fp;
    stu st[100];
    b bk[100];
    int ch;
    system("cls");
    fp = fopen("issue.dat", "r");
    if (fp == NULL)
    {
        printf("file can't be opened \n");
        getch();
    }
    int i = 0;
    printf("\nStudent ID \tStudent's Name \tRoll No. \tBook ID \tBook Name\n");
    printf("\n------------------------------------------------------------------------------\n");
    while(fscanf(fp,"%s%s%s%s%s", &st[i].id, &st[i].sname, &st[i].sroll, &bk[i].id, &bk[i].name) != EOF)
    {
        printf("%s\t\t" "%s\t\t" "%s\t\t" "%s\t\t" "%s\n",  st[i].id, st[i].sname, st[i].sroll, bk[i].id, bk[i].name);
        i++;
    }
    printf("\nPress any key to go main menu...");
    getch();
    main();
}
/////////////////////////////////////////////////////Remove book from issue file///////////////////////////
int delete_issue_book(char b_id[])
{
    FILE *fp, *ft;
    stu s;
    b bk;
    int i=0;
    fp = fopen("issue.dat", "r+");
    if (fp == NULL)
    {
        return 0;
    }
    rewind(fp);  // set the file pointer beginning of the file.
    ft=fopen("itemp.dat","wb"); // create temporary file to store data.
    fflush(stdin); //flush data from buffer
    while(fscanf(fp,"\n%s\t" "%s\t" "%s\t" "%s\t" "%s",&s.id,&s.sname,&s.sroll,&bk.id,&bk.name)>0)
    {
        if(strcmp(b_id,bk.id)!=0)
        {
            fprintf(ft,"%s\t" "%s\t" "%s\t" "%s\t" "%s\n", s.id,s.sname,s.sroll,bk.id,bk.name);
        }
    }
    _fcloseall(); // close all file
    remove("issue.dat");
    rename("itemp.dat","issue.dat");
    return 1;
}

////////////////////////////////////////////Add new password/////////////////////////////////////////////

void sign_up()
{
    getch();
    system("cls");
    char temp[10];
    FILE *f;
    f = fopen("password.dat","wb");
    printf("Enter password: ");
    get_password(password);
    printf("\nRe Enter Password: ");
    get_password(temp);
    while(strcmp(password,temp)!=0){
        printf("\nPassword did not matched! Enter again");
        printf("\nEnter password: ");
        get_password(password);
        printf("\nRe Enter Password: ");
        get_password(temp);
        system("cls");
    }
    fprintf(f,"%s",password);
    fclose(f);
}

//////////////////////////////////////////get password and mask with * ///////////////////////////
void get_password(char* pass)
{
    char temp_passP[25];
    int i=0;
     while(1)
    {
            temp_passP[i]=getch();
            if(temp_passP[i]==13){break;}
            else if(temp_passP[i]==8)
            {
                if(i!=0) {
                printf("\b \b");
                i--;
                } else {printf("\a");}
            }
            else
            {
                printf("*");
                *(pass+i) = temp_passP[i];
                i++;
            }
             *(pass+i)='\0';
     }
}
/////////////////////////////////////////////////////////Validate password////////////////////////////////////
void authentication()
{
    FILE *f;
    char temp[10];
    f = fopen("password.dat","rb");
    printf("\nEnter password: ");
    get_password(temp);
    while(fscanf(f,"%s",password)!=EOF)
    {
        while(strcmp(temp,password)!=0)
            {
                system("cls");
                printf("\nPassword did not match! ");
                printf("\nEnter Again: ");
                get_password(temp);
            }
        printf("\n\n\t\tLogin Success!!!");
        sleep(2);
        break;
    }
    fclose(f);
}
////////////////////////////////////////////////////////// LOgin ////////////////////////
int login()
{
    FILE *f;
    f = fopen("password.dat","rb");
    if(f == NULL){
        printf("\nYou are new to system. \nAdd new password to continue...");
        sign_up();
    }else{
        authentication();
    }
    return 0;
}




