#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
#include <windows.h>
#include <stdbool.h>

#define Student struct Stud

void add(FILE * fp);
void modify(FILE * fp);
void display(FILE * fp);
void IndiualView(FILE *fp);
void password();
FILE * del(FILE * fp);
void printChar(char ch,int n);
void title();

FILE* tp;

void gotoxy(int x,int y)
{
	COORD CRD;
    CRD.X = x;
    CRD.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),CRD);
}

struct pass
{
	char pass[25];
}pa;

struct Stud
{
    char name[100];
    char grade[50];
    short index;
    float semesterAverage[8];
    float generalAverage;
};

int main()
{
    int k=0,i,cnt;
    char pas[50];
    SetConsoleTitle("School Management App");
    FILE * fp;
    Student s;
    int option;
    char another;
    if((fp=fopen("db.txt","rb+"))==NULL)
    {
        if((fp=fopen("db.txt","wb+"))==NULL)
        {
            printf("Can't create or open Database.");
            return 0;
        }
    }
    system("color BD");
	gotoxy(42,8);
	printf("LOGIN(If 1st login press ENTER)");
	gotoxy(42,10);
	printf("____________________________________");
	gotoxy(42,11);
	printf("|\tEnter password :             |");
	gotoxy(42,12);
	printf("|__________________________________|");
    gotoxy(65,11);
	while( k<10)
	{
	    pas[k]=getch();
	    char s=pas[k];
	    if(s==13)
            break;
	    else printf("*");
	    k++;
	}
	pas[k]='\0';
	tp=fopen("Password.txt","r+");
    fgets(pa.pass,25,tp);
    if(strcmp(pas,pa.pass)==0)
	{
		system("cls");
        cnt=3;
		while(cnt)
        {
            gotoxy(10,3);
            printf("<<<< Loading Please Wait >>>>                                           ");
            Sleep(500);
            gotoxy(39,3);
            for(i=0; i<5; i++)
            {
                printf("\t(*_*)");
                Sleep(500);
            }
            cnt--;
        }
        printf("\n\n\n\n\n\t\t\t\t\t     *  *  *  *  *  *  *  *");
		printf("\n\n\t\t\t\t\t     *                    *");
		printf("\n\n\t\t\t\t\t     *       Welcome      *");
		printf("\n\n\t\t\t\t\t     *                    *");
		printf("\n\n\t\t\t\t\t     *  *  *  *  *  *  *  *");
		printf("\n\n\n\n\n\t\t\t\t\tPress any key to continue...... ");
		getch();
        title();
        printf("\n\n\t\t    Application for managing the situation");
        printf("\n\n\t\t           of a class of students\n\t\t    ");
        printChar('=',38);
        printf("\n\n\n\t\t    press any key to Enter...");
        getch();
        while(1)
        {
            title();
            printf("\n\t");
            printChar('*',64);
            printf("\n\n\t\t\t\t1. Add Student");
            printf("\n\n\t\t\t\t2. Modify Student");
            printf("\n\n\t\t\t\t3. Show All Student");
            printf("\n\n\t\t\t\t4. Individual View");
            printf("\n\n\t\t\t\t5. Remove Student");
            printf("\n\n\t\t\t\t6. Change Password");
            printf("\n\n\t\t\t\t7. Logout\n\t");
            printChar('*',64);
            printf("\n\n\t\t\t\tEnter Your Option :--> ");
            scanf("%d",&option);
            switch(option)
            {
                case 1:
                    add(fp);
                    break;
                case 2:
                    modify(fp);
                    break;
                case 3:
                    display(fp);
                    break;
                case 4:
                    IndividualView(fp);
                    break;
                case 5:
                    fp=del(fp);
                    break;
                case 6:
                    system("cls");
                    system("color 0A");
                    password();
                    break;
                case 7:
                    return 1;
                    break;
                default:
                    printf("\n\t\tNo Action Detected");
                    printf("\n\t\tPress Any Key\n\n\n");
                    getch();
                    system("pause");
            }
        }
    }
    else
    {
        gotoxy(48,13);
        printf("Wrong Password . You will be disconnected");
        getch();
    }
    return 1;
}

void password()
{
	char c;
	printf("\n\t\t\t\t\t\tEnter new password :");
	fflush(stdin);
	gets(pa.pass);
	printf("\n\t\t\t\t\t\tSave password (y/n) :");
	fflush(stdin);
	scanf("%c",&c);
	if(c=='y'||c=='Y')
	{
	    int k1=3,k2;
        while(k1)
        {
            gotoxy(5,5);
            printf("\n\n\t\t\t\t\t\t Saving     ");
            gotoxy(55,7);
            k2=5;
            Sleep(500);
            while(k2)
            {
                printf(".");
                Sleep(500);
                k2--;
            }
            k1--;
        }
		tp=fopen("Password.txt","w+");
	    fwrite(&pa,sizeof(pa),1,tp);
	    fclose(tp);
		printf("\n\n\n\t\t\t\t\t\t\tPassword Saved\n");
		printf("\t\t\t\t\t\tPress any key to continue >>>");
		getch();
	}
	else
	{
		printf("Password not saved :\n");
		printf("Press any key to continue >>>");
		getch();
	}
}

void printChar(char ch,int n)
{
    while(n--)
    {
        putchar(ch);
    }
}

void title()
{
    system("cls");
    system("COLOR 03");
    printf("\n\n\t");
    printChar('=',19);
    printf(" School Management App ");
    printChar('=',19);
    printf("\n");
}

void add(FILE* fp)
{
    title();
    char another='y';
    Student s;
    int i;
    fseek(fp,0,SEEK_END);
    while(another=='y'||another=='Y')
    {
        s.generalAverage=0;
        printf("\n\n\t\tEnter Full Name of Student: ");
        fflush(stdin);
        fgets(s.name,100,stdin);
        s.name[strlen(s.name)-1]='\0';
        printf("\n\n\t\tEnter student's Grade and class : ");
        fflush(stdin);
        fgets(s.grade,50,stdin);
        s.grade[strlen(s.grade)-1]='\0';
        printf("\n\n\t\tEnter index number: ");
        scanf("%d",&s.index);
        printf("\n\n\tEnter averages for 8 semesters\n");
        for(i=0; i<8; i++)
        {
            scanf("%f",&s.semesterAverage[i]);
            s.generalAverage+=s.semesterAverage[i];
        }
        s.generalAverage=s.generalAverage/8;
        fwrite(&s,sizeof(s),1,fp);
        printf("\n\n\t\tAdd another student?(Y/N)?");
        fflush(stdin);
        another=getchar();
    }
}

FILE * del(FILE * fp)
{
    title();
    Student s;
    int flag=0,tempIndex,siz=sizeof(s);
    FILE *ft;
    if((ft=fopen("temp.txt","w+"))==NULL)
    {
        printf("\n\n\t\t\t\\t!!! ERROR !!!\n\t\t");
        system("pause");
        return fp;
    }
    printf("\n\n\tEnter index number of Student to Delete the Record : ");
    scanf("%d",&tempIndex);
    rewind(fp);
    while((fread(&s,siz,1,fp))==1)
    {
        if(s.index==tempIndex)
        {
            flag=1;
            printf("\n\tRecord Deleted for");
            printf("\n\n\t\t%s\n\n\t\t%s\n\n\t\t%d\n\t",s.name,s.grade,s.index);
            continue;
        }
        fwrite(&s,siz,1,ft);
    }
    fclose(fp);
    fclose(ft);
    remove("db.txt");
    rename("temp.txt","db.txt");
    if((fp=fopen("db.txt","rb+"))==NULL)
    {
        printf("ERROR");
        return  NULL;
    }
    if(flag==0)
        printf("\n\n\t\tNO STUDENT FOUND WITH THE INFORMATION\n\t");
    printChar('-',65);
    printf("\n\t");
    system("pause");
    return fp;
}

void modify(FILE * fp)
{
    title();
    Student s;
    int i,flag=0,tempIndex,siz=sizeof(s);
    float cgpa;
    printf("\n\n\tEnter Index Number of Student to MODIFY the Record : ");
    scanf("%d",&tempIndex);
    rewind(fp);
    while((fread(&s,siz,1,fp))==1)
    {
        if(s.index==tempIndex)
        {
            flag=1;
            break;
        }
    }
    if(flag==1)
    {
        fseek(fp,-siz,SEEK_CUR);
        printf("\n\n\t\t\t\tRecord Found\n\t\t\t");
        printChar('=',38);
        printf("\n\n\t\t\tStudent Name: %s",s.name);
        printf("\n\n\t\t\tStudent Class: %s\n\t\t\t",s.grade);
        printChar('=',38);
        printf("\n\n\t\t\tEnter New Data for the student");
        printf("\n\n\t\tEnter Full Name of Student: ");
        fflush(stdin);
        fgets(s.name,100,stdin);
        s.name[strlen(s.name)-1]='\0';
        printf("\n\n\t\tEnter student's Grade and class : ");
        fflush(stdin);
        fgets(s.grade,50,stdin);
        s.grade[strlen(s.grade)-1]='\0';
        printf("\n\n\t\tEnter index number: ");
        scanf("%d",&s.index);
        s.generalAverage=0;
        printf("\n\n\tEnter averages for 8 semesters\n");
        for(i=0; i<8; i++)
        {
            scanf("%f",&s.semesterAverage[i]);
            s.generalAverage+=s.semesterAverage[i];
        }
        s.generalAverage=s.generalAverage/8;
        fwrite(&s,sizeof(s),1,fp);
    }
    else
        printf("\n\n\t!!!! ERROR !!!! RECORD NOT FOUND");
    printf("\n\n\t");
    system("pause");
}

void display(FILE * fp)
{
    title();
    Student s;
    int i,siz=sizeof(s);
    rewind(fp);
    while((fread(&s,siz,1,fp))==1)
    {
        printf("\n\t\tName : %s",s.name);
        printf("\n\n\t\tClass : %s",s.grade);
        printf("\n\n\t\tIndex : %d",s.index);
        printf("\n\n\tSemester Averages: ");
        for(i=0; i<8; i++)
            printf("| Sem %d : %.2f |",i+1, s.semesterAverage[i]);
        printf("\n\n\t\t General Average : %.2f\n\t", s.generalAverage);
        printChar('-',65);
    }
    printf("\n\n\n\t");
    printChar('*',65);
    printf("\n\n\t");
    system("pause");
}

void IndividualView(FILE *fp)
{
    title();
    int tempIndex,flag,siz,i;
    Student s;
    char another='y';
    siz=sizeof(s);
    while(another=='y'||another=='Y')
    {
        printf("\n\n\tEnter Index Number: ");
        scanf("%d",&tempIndex);
        rewind(fp);
        while((fread(&s,siz,1,fp))==1)
        {
            if(s.index==tempIndex)
            {
                flag=1;
                break;
            }
        }
        if(flag==1)
        {
            printf("\n\t\tName : %s",s.name);
            printf("\n\n\t\tGrade : %s",s.grade);
            printf("\n\n\t\tIndex : %d",s.index);
            printf("\n\n\Semester Averege: ");
            for(i=0; i<8; i++)
                printf("| %.2f |",s.semesterAverage[i]);
            printf("\n\n\t\tGeneral Average : %.2f\n\t",s.generalAverage);
            printChar('-',65);
        }
        else printf("\n\n\t\t!!!! ERROR RECORD NOT FOUND !!!!");
        printf("\n\n\t\tShow another student information? (Y/N)?");
        fflush(stdin);
        another=getchar();
    }
}
