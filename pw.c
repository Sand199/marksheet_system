
//@author: Sand1

#include <stdio.h>
#include <stdlib.h>
#define MAX_NAME_LEN 30

struct stu 
{
	char name[MAX_NAME_LEN];
	int roll;
	int math;
	int sci;
	int eng;
	int nep;
	int soc;
};

void add();
void bulk();
void list();
void search();
int scan_marks(const char*, int*);
int scan_student(struct stu*);
int fscan_student(FILE*, struct stu*);
void fprint_student();
void change(int, char);
void marksheet(struct stu);
int dump();

int main(void)
{
	int inp;
	
	do {
	printf("\n****************************************\n\n");
	printf("1. Add a Record\n");
	printf("2. Add Bulk Records\n");
	printf("3. List Students\n");
	printf("4. Search Students\n");
	printf("5. Quit\n");
	printf("\nWhat is your choice? : ");
	
	inp = getchar();
	if (inp != '\n' && getchar() != '\n')
	{	inp = 0;
		while (getchar() != '\n');
	}
	
	printf("\n****************************************\n");

	if (inp == 49)
		add();
	else if (inp == 50)
		bulk();
	else if (inp == 51)
		list();
	else if (inp == 52)
		search();
	else if (inp == 53)
	{
		printf("\nBye Bye!!\n");
		printf("\n****************************************\n");
	}
	else
		printf("\nInvalid Input\n");
	}
	
	while (inp != 53);
}
int scan_student(struct stu* s1){
	
	printf("\nEnter Name : ");
       	if (scanf("%[a-z A-z]",s1->name) == 0) {
		if (dump() != EOF) {
		printf("\n****************************************\n");
		printf("\nError : Input can't be Scanned\n");
		}
		return EOF;
	}
	if (dump() == EOF) 
		return EOF;
	printf("Enter Roll : ");
	if (scanf("%d",&s1->roll) == 0) {
		if (dump() != EOF) {
		printf("\n****************************************\n");
		printf("\nError : Input can't be Scanned\n");
		}
		return EOF;
	}
	if (dump() == EOF)
		return EOF;
	if (scan_marks("Mathematics",&s1->math) == EOF)
		return EOF;
	if (scan_marks("Science",&s1->sci) == EOF)
		return EOF;
	if (scan_marks("English",&s1->eng) == EOF)
		return EOF;
	if (scan_marks("Nepali",&s1->nep) == EOF)
		return EOF;
	if (scan_marks("Social",&s1->soc) == EOF)
		return EOF;
	return 0;
}
int fscan_student(FILE* file, struct stu* s1) {
	return fscanf(file,"%d,%[^,],%d,%d,%d,%d,%d\n",&s1->roll,s1->name,&s1->math,&s1->sci,&s1->eng,&s1->nep,&s1->soc); 
}

void fprint_student(FILE *file, struct stu* p) {
	fprintf(file,"%d,%s,%d,%d,%d,%d,%d\n",p->roll,p->name,p->math,p->sci,p->eng,p->nep,p->soc);
}


int scan_marks(const char* subject,int* marks){
	printf("Enter Marks in %s : ",subject);
	if (scanf("%2d",marks) == 0) {
		if (dump() != EOF) {
		printf("\n****************************************\n");
		printf("\nError : Input can't be Scanned\n");
		}
		return EOF;
	}
	if (dump() == EOF)
	 	return EOF;
	return 0;
}

void add()
{
	struct stu s1;
	FILE *fp;

	fp = fopen("record.csv","a");
	if (fp == NULL) {
		perror("\nError opening record.csv for writing");
		return;
	}
	
	if (scan_student(&s1) == EOF) {
		fclose(fp);
		return;
	}
 
	fprint_student(fp,&s1);
	
	fclose(fp);

	printf("\n****************************************\n\n");
	printf("Added\n");
}

void bulk()
{
	int i, n;
	struct stu *p;
	FILE *fp;
	
	fp = fopen("record.csv","a");
	if (fp == NULL) {
		perror("\nError opening record.csv");
		return;
	}
	
	printf("\nHow many students? : ");
	if (scanf("%d", &n) == 0) {
		if (dump() != EOF) {
		printf("\n****************************************\n");
		printf("\nError : Input can't be Scanned\n");
		}
		fclose(fp);
		return;
	}
	
	if (dump() == EOF) {
		fclose(fp);
		return;
	}
	
	p = malloc(sizeof(struct stu));
	
	for (i=1; i<=n; ++i)
	{	
		printf("\n****************************************\n");
		printf("\nEnter information for student %d :\n",i);
		if (scan_student(p) == EOF) {
			fclose(fp);
			free(p);
			return;
		}
		fprint_student(fp,p);
	}
	
	fclose(fp);
	free(p);

	printf("\n****************************************\n\n");
	printf("Added\n");
}

void list()
{
	struct stu s1;
	FILE *fp;

	fp = fopen("record.csv","r");
	if (fp == NULL) {
		perror("\nError opening record.csv");
		return;
	}
	printf("\nRoll\tName\n");
	while (fscan_student(fp, &s1) != EOF)
		printf("%2d\t%s\n",s1.roll,s1.name);	
	
	fclose(fp);
}

void search()
{
	int roll, inp, flag;
	struct stu s1,s2;
	FILE *fp;

	fp = fopen("record.csv","r");	
	if (fp == NULL) {
		perror("\nError opening record.csv");
		return;
	}
	flag = 0;
	
	printf("\nEnter Roll No : ");
	if (scanf("%d",&roll) == 0) {
		if (dump() != EOF) {
		printf("\n****************************************\n");
		printf("\nError : Input can't be Scanned\n");
		}
	return;
	}
	if (dump() == EOF)
		return;
	printf("\n****************************************\n");
	
	while (fscan_student(fp,&s1) != EOF)
		if ( roll == s1.roll) {
			printf("\nRecord Found :\n");
			printf("Student Name : %s\n", s1.name);
			
			s2 = s1;
			flag = 1;
		}

	if (flag == 0) {
		printf("\nRecord Not Found\n");
		return;
	}

	fclose(fp);
	
	printf("\n****************************************\n\n");
	printf("1. Edit Record\n");
	printf("2. Delete Record\n");
	printf("3. View Marksheet\n");
	printf("4. Quit\n");
	printf("\nWhat is your choice? : ");

	inp = getchar();
	if (inp != '\n' && getchar() != '\n')
	{	
		inp = 0;
		while (getchar() != '\n');
	}
	
	if (inp == 49)
		change(roll,'e');
	else if (inp == 50)
		change(roll,'d');
	else if (inp == 51)
		marksheet(s2);
	
	else if (inp != 52) {
		printf("\n****************************************\n");
		printf("\nInvalid Input\n");
	}
}

void change(int roll,char c)
{
	int quit = 0;
	FILE *f1 = fopen("record.csv", "r");
	FILE *f2 = fopen("temp","w");
	struct stu s1;

	if (f1 == NULL) {
		perror("\nError opening record.csv");
		return;
	}
	if (f2 == NULL) {
		perror("\nError creating temporary file");
		fclose(f1);
		return;
	}
	
	
	printf("\n****************************************\n\n");
	while(fscan_student(f1, &s1) != EOF)
		if (s1.roll != roll)
			fprint_student(f2,&s1);	
	if (c == 'd')
		printf("Record Deleted\n");
	if (c == 'e') {
		s1.roll = roll;
		printf("\nEnter Name : ");
       		if (scanf("%[a-z A-z]",s1.name) == 0) {
			if (dump() != EOF) {
				printf("\n****************************************\n\n");
				printf("\nError : Input can't be scanned\n");
			}
			quit = 1;
		}
		if (!(quit ||dump() 
			|| scan_marks("Mathematics",&s1.math) 
			|| scan_marks("Science",&s1.sci)
			|| scan_marks("English",&s1.eng)
			|| scan_marks("Nepali",&s1.nep)
			|| scan_marks("Social",&s1.soc) )) {
			fprint_student(f2,&s1);
	              	printf("\n****************************************    \n\n");
                	printf("Record Updated\n");
			quit = 2;

		}
	}	
	fclose(f1);
	fclose(f2);
	
	if(quit == 2 || c == 'd') {
		remove("record.csv");
		rename("temp","record.csv");
	}
	else
		remove("temp");
}

void marksheet(struct stu s)
{
	int fail = 0;
	if (s.math<40 || s.sci<40 || s.eng < 40 || s.eng<40 || s.nep <40 || s.soc<40)
		fail = 1;

	int total = s.math+s.sci+s.eng+s.nep+s.soc;
	float per = total/5.0;

	printf("\n****************************************\n\n");
	printf("\t\tMARKSHEET\n");
	printf("+--------------------------------------+\n");
	printf("| Name : %-30s|\n", s.name);
	printf("| Roll : %-30d|\n", s.roll);	
	printf("+----+-----------------------+---------+\n");
	printf("| SN |   Subjects            |  Marks  |\n");
	printf("+----+-----------------------+---------+\n");
	printf("|  1 |   Mathematics         |    %2d   |\n",s.math);
	printf("|  2 |   Science             |    %2d   |\n",s.sci);
	printf("|  3 |   English             |    %2d   |\n",s.eng);
	printf("|  4 |   Nepali              |    %2d   |\n",s.nep);
	printf("|  5 |   Social              |    %2d   |\n",s.soc);
	printf("+----+-----------------------+---------+\n");
	printf("|        Total               |   %3d   |\n",total);
	printf("+----------------------------+---------+\n");
	if (!fail)
		printf("|        Percentage          |  %2.2f%% |\n", per);
	else
		printf("|        Percentage          | Failed! |\n");
	printf("+----------------------------+---------+\n");
	if (fail)
		printf("|        Division            | Failed! |\n");
	else if (per >= 80)
		printf("|        Division            |  Distn  |\n");
	else if (per >= 60)
		printf("|        Division            | 1st Div |\n");
	else if (per >= 50)
		printf("|        Division            | 2nd Div |\n");
	else
		printf("|        Division            | 3rd Div |\n");
	printf("+----------------------------+---------+\n\n");
}

int dump()
{
	int c,flag = 0;
	while((c = getchar()) != '\n' && c != EOF)
		flag = 1;
	if (flag == 1) {
		printf("\n****************************************\n\n");
		printf("Error : Invalid Input\n");
	 	return EOF;
	}
	return 0;
}
