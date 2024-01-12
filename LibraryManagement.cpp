// Library Management System LMS
// Author: Waleed Ahmad

#include<fstream>
#include<iostream>
#include<conio.h>
#include<cstdio>
#include<cstring>
#include<process.h>
#include<iomanip>

using namespace std;
//***************************************************************
//                   CLASS USED IN PROJECT
//****************************************************************


class library {
public:
    virtual void create() = 0;

    virtual void show() = 0;

    virtual void MODIFY() = 0;

};

class book : public library {
    char bno[6]{};
    char bookName[50]{};
    char authName[20]{};
public:
    void create() override {
        cout << "\nNEW BOOK ENTRY...\n";
        cout << "\nEnter The book no. ";
        cin >> bno;

        cout << "\n\nEnter The Name of The Book: ";
        cin >> bookName;

        cout << "\n\nEnter The Author's Name: ";
        cin >> authName;

        cout << "\n\n\nBook Created..";
    }


    void show() override {
        cout << "\nBook no. : " << bno;
        cout << "\nBook Name : ";
        puts(bookName);
        cout << "Author Name : ";
        puts(authName);
    }

    void MODIFY() override {
        cout << "\nBook no. : " << bno;
        cout << "\nModify Book Name : ";
        gets(bookName);
        cout << "\nModify Author's Name of Book : ";
        gets(authName);
    }

    char *returnBookNum() {
        return bno;
    }

    void report() { cout << bno << setw(30) << bookName << setw(30) << authName << endl; }

};
//class ends here


class student : public library {
    char studentNum[6]{};
    char name[20]{};
    char stBookNum[6]{};
    int token{};
public:
    void create() override {
        system("cls");
        cout << "\nNEW STUDENT ENTRY...\n";
        cout << "\nEnter The admission no. ";
        cin >> studentNum;
        cout << "\n\nEnter The Name of The Student: ";
        cin >> name;
        token = 0;
        cout << "\n\nStudent Record Created..";
    }

    void show() override {
        cout << "\nAdmission no. : " << studentNum;
        cout << "\nStudent Name : " << name;
        //puts(name);
        cout << "\nNo of Book issued : " << token;
        if (token == 1)
            cout << "\nBook No " << stBookNum;
    }

    void MODIFY() override {
        cout << "\nAdmission no. : " << studentNum;
        cout << "\nModify Student Name : ";
        cin >> name;
    }

    char *getStudentNum() {
        return studentNum;
    }

    char *getStBookNum() {
        return stBookNum;
    }

    int getToken() const {
        return token;
    }

    void addtoken() { token = 1; }

    void resetToken() { token = 0; }

    void setStBookNum(char t[]) {
        strcpy(stBookNum, t);
    }

    void report() { cout << "\t" << studentNum << setw(20) << name << setw(10) << token << endl; }

};
//class ends here


//***************************************************************
//    	global declaration for stream object, object
//****************************************************************

fstream fp, fp1;
book bk;
student st;
library *Book = &bk;
library *Student = &st;



//***************************************************************
//    	function to write in file
//****************************************************************

void writeBook() {
    char ch;
    fp.open("book.txt", ios::out | ios::app);
    do {
        system("cls");
        Book->create();
        fp.write((char *) &bk, sizeof(book));
        cout << "\n\nDo you want to add more record..(y/n?)";
        cin >> ch;
    } while (ch == 'y' || ch == 'Y');
    fp.close();
}

void writeStudent() {
    char ch;
    fp.open("student.txt", ios::out | ios::app);
    do {
        Student->create();
        fp.write((char *) &st, sizeof(student));
        cout << "\n\nDo you want to add more record..(y/n?)";
        cin >> ch;
    } while (ch == 'y' || ch == 'Y');
    fp.close();
}


//***************************************************************
//    	function to read specific record from file
//****************************************************************


void displaySpecificBook(char n[]) {
    cout << "\nBOOK DETAILS\n";
    int flag = 0;
    fp.open("book.txt", ios::in);
    while (fp.read((char *) &bk, sizeof(book))) {
        if (strcmpi(bk.returnBookNum(), n) == 0) {
            Book->show();
            flag = 1;
        }
    }

    fp.close();
    if (flag == 0)
        cout << "\n\nBook does not exist";
    getch();
}

//Display Specific Student Record
void displaySpecificStudent(char n[]) {
    cout << "\nSTUDENT DETAILS\n";
    int flag = 0;
    fp.open("student.txt", ios::in);
    while (fp.read((char *) &st, sizeof(student))) {
        if ((strcmpi(st.getStudentNum(), n) == 0)) {
            Student->show();
            flag = 1;
        }
    }

    fp.close();
    if (flag == 0)
        cout << "\n\nStudent does not exist";
    getch();
}


//***************************************************************
//    	function to modify record of file
//****************************************************************


void modifyBook() {
    char n[6];
    int found = 0;
    system("cls");
    cout << "\n\n\tMODIFY BOOK RECORD.... ";
    cout << "\n\n\tEnter The book no. of The book";
    cin >> n;
    fp.open("book.txt", ios::in | ios::out);
    while (fp.read((char *) &bk, sizeof(book)) && found == 0) {
        if (strcmpi(bk.returnBookNum(), n) == 0) {
            Book->show();
            cout << "\nEnter The New Details of book" << endl;
            bk.MODIFY();
            int pos = sizeof(bk);
            pos = -1 * pos;
            fp.seekp(pos, ios::cur);
            fp.write((char *) &bk, sizeof(book));
            cout << "\n\n\t Record Updated";
            found = 1;
        }
    }

    fp.close();
    if (found == 0)
        cout << "\n\n Record Not Found ";
    getch();
}


void modifyStudent() {
    char n[6];
    int found = 0;
    system("cls");
    cout << "\n\n\tMODIFY STUDENT RECORD... ";
    cout << "\n\n\tEnter The admission no. of The student";
    cin >> n;
    fp.open("student.txt", ios::in | ios::out);
    while (fp.read((char *) &st, sizeof(student)) && found == 0) {
        if (strcmpi(st.getStudentNum(), n) == 0) //if the new entered adm number and the new one are the same
        {
            Student->show();  //shows the old details
            cout << "\nEnter The New Details of student" << endl;
            Student->MODIFY();
            int pos = sizeof(st);
            pos = -1 * pos;
            fp.seekp(pos, ios::cur); //in output stream goes back upto size of name starting from current position
            fp.write((char *) &st, sizeof(student));
            cout << "\n\n\t Record Updated";
            found = 1;
        }
    }

    fp.close();
    if (found == 0)
        cout << "\n\n Record Not Found ";
    getch();
}

//***************************************************************
//    	function to delete record of file
//****************************************************************


void deleteStudent() {
    char n[6];
    int flag = 0;     //indicator of deletion being successful or not
    system("cls");
    cout << "\n\n\n\tDELETE STUDENT...";
    cout << "\n\nEnter The admission no. of the Student You Want To Delete : ";
    cin >> n;
    fp.open("student.txt", ios::in | ios::out);
    fstream fp2;
    fp2.open("Temp.txt", ios::out);  //temporary file is created
    fp.seekg(0, ios::beg);   //file pointer is moved to the beginning
    while (fp.read((char *) &st, sizeof(student))) {
        if (strcmpi(st.getStudentNum(), n) != 0) //copies old file to new one if adm number does not  match
            fp2.write((char *) &st, sizeof(student));
        else
            flag = 1; //if it matches flag is given the value 1 which is an indicator that the deletion was successful
    }

    fp2.close();
    fp.close();
    remove("student.txt");  //old file deleted
    rename("Temp.txt", "student.txt");   //new file renamed
    if (flag == 1)
        cout << "\n\n\tRecord Deleted ..";
    else
        cout << "\n\nRecord not found";
    getch();
}


void deleteBook() {
    char n[6];
    system("cls");
    cout << "\n\n\n\tDELETE BOOK ...";
    cout << "\n\nEnter The Book no. of the Book You Want To Delete : ";
    cin >> n;
    fp.open("book.txt", ios::in | ios::out);
    fstream fp2;
    fp2.open("Temp.txt", ios::out);
    fp.seekg(0, ios::beg);
    while (fp.read((char *) &bk, sizeof(book))) {
        if (strcmpi(bk.returnBookNum(), n) != 0) {
            fp2.write((char *) &bk, sizeof(book));
        }
    }

    fp2.close();
    fp.close();
    remove("book.txt");
    rename("Temp.txt", "book.txt");
    cout << "\n\n\tRecord Deleted ..";
    getch();
}



//***************************************************************
//    	function to display all students list
//****************************************************************

void displayAllStudent() {
    system("cls");
    fp.open("student.txt", ios::in);
    if (!fp) {
        cout << "ERROR!!! FILE NOT FOUND\n";
        getch();
        return;
    }

    cout << "\n\n\t\tSTUDENT LIST\n\n";
    cout << "==================================================================\n";
    cout << "\tAdmission No." << setw(10) << "Name" << setw(20) << "Book Issued\n";
    cout << "==================================================================\n";

    while (fp.read((char *) &st, sizeof(student))) {
        st.report();
    }

    fp.close();
    getch();
}


//***************************************************************
//    	function to display Books list
//****************************************************************

void displayAllBooks() {
    system("cls");
    fp.open("book.txt", ios::in);
    if (!fp) {
        cout << "ERROR!!! FILE COULD NOT BE OPEN ";
        getch();
        return;
    }

    cout << "\n\n\t\tBook LIST\n\n";
    cout << "=========================================================================\n";
    cout << "Book Number" << setw(20) << "Book Name" << setw(25) << "Author\n";
    cout << "=========================================================================\n";

    while (fp.read((char *) &bk, sizeof(book))) {
        bk.report();
    }
    fp.close();
    getch();
}



//***************************************************************
//    	function to issue book
//****************************************************************

void bookIssue() {
    char sn[6], bn[6];
    int found = 0, flag = 0;
    system("cls");
    cout << "\n\nBOOK ISSUE ...";
    cout << "\n\n\tEnter The student's admission no.";
    cin >> sn;
    fp.open("student.txt", ios::in | ios::out);
    fp1.open("book.txt", ios::in | ios::out);
    while (fp.read((char *) &st, sizeof(student)) && found == 0) {
        if (strcmpi(st.getStudentNum(), sn) == 0) {
            found = 1;
            if (st.getToken() == 0) {
                cout << "\n\n\tEnter the book no. ";
                cin >> bn;
                while (fp1.read((char *) &bk, sizeof(book)) && flag == 0) {
                    if (strcmpi(bk.returnBookNum(), bn) == 0) {
                        Book->show();
                        flag = 1;
                        st.addtoken();
                        st.setStBookNum(bk.returnBookNum());
                        int pos = sizeof(st);
                        pos = -1 * pos;
                        fp.seekp(pos, ios::cur);
                        fp.write((char *) &st, sizeof(student));
                        cout << "\n\n\t Book issued successfully\n\n";
                        cout << " Please Note: Write current date in backside of book";
                        cout << " and submit within 15 days fine Rs. 1 for each day after 15 days period";
                    }
                }
                if (flag == 0) cout << "Book no does not exist";
            } else cout << "You have not returned the last book ";

        }
    }
    if (found == 0)
        cout << "Student record not exist...";
    getch();
    fp.close();
    fp1.close();
}

//***************************************************************
//    	function to deposit book
//****************************************************************

void bookDeposit() {
    char sn[6];
    int found = 0, flag = 0, day, fine;
    system("cls");
    cout << "\n\nBOOK DEPOSIT ...";
    cout << "\n\n\tEnter The student�s admission no.";
    cin >> sn;
    fp.open("student.txt", ios::in | ios::out);
    fp1.open("book.txt", ios::in | ios::out);
    while (fp.read((char *) &st, sizeof(student)) && found == 0) {
        if (strcmpi(st.getStudentNum(), sn) == 0) {
            found = 1;
            if (st.getToken() == 1) {
                while (fp1.read((char *) &bk, sizeof(book)) && flag == 0) {
                    if (strcmpi(bk.returnBookNum(), st.getStBookNum()) == 0) {
                        Book->show();
                        flag = 1;
                        cout << "\n\nBook deposited in no. of days";
                        cin >> day;
                        if (day > 15) {
                            fine = (day - 15) * 1;
                            cout << "\n\nFine has to deposited Rs. " << fine;
                        }
                        st.resetToken();
                        int pos = sizeof(st);
                        pos = -1 * pos;
                        fp.seekp(pos, ios::cur);
                        fp.write((char *) &st, sizeof(student));
                        cout << "\n\n\t Book deposited successfully";
                    }
                }
                if (flag == 0)
                    cout << "Book no does not exist";
            } else
                cout << "No book is issued..please check!!";
        }
    }
    if (found == 0)
        cout << "Student record not exist...";
    getch();
    fp.close();
    fp1.close();
}

//***************************************************************
//    	INTRODUCTION FUNCTION
//****************************************************************

void intro() {
    system("cls");
    cout << "LIBRARY MANAGEMENT SYSTEM\n";
    cout << "Made by Waleed Ahmad\n";
    cout << "Press Enter to continue\n";
    getch();
}

//***************************************************************
//    	ADMINISTRATOR MENU FUNCTION
//****************************************************************

void adminMenu() {
    while(true)
    {


    system("cls");
    int ch2;
    cout << "\n\n\n\tADMINISTRATOR MENU";
    cout << "\n\n\t1.CREATE STUDENT RECORD";
    cout << "\n\n\t2.DISPLAY ALL STUDENTS RECORD";
    cout << "\n\n\t3.DISPLAY SPECIFIC STUDENT RECORD ";
    cout << "\n\n\t4.MODIFY STUDENT RECORD";
    cout << "\n\n\t5.DELETE STUDENT RECORD";
    cout << "\n\n\t6.CREATE BOOK ";
    cout << "\n\n\t7.DISPLAY ALL BOOKS ";
    cout << "\n\n\t8.DISPLAY SPECIFIC BOOK ";
    cout << "\n\n\t9.MODIFY BOOK ";
    cout << "\n\n\t10.DELETE BOOK ";
    cout << "\n\n\t11.BACK TO MAIN MENU";
    cout << "\n\n\tPlease Enter Your Choice (1-11) ";
    cin >> ch2;
    switch (ch2) {
        case 1:
            system("cls");
            writeStudent();
            break;
        case 2:
            displayAllStudent();
            break;
        case 3:
            char num[6];
            system("cls");
            cout << "\n\n\tPlease Enter The Admission No. ";
            cin >> num;
            displaySpecificStudent(num);
            break;
        case 4:
            modifyStudent();
            break;
        case 5:
            deleteStudent();
            break;
        case 6:
            system("cls");
            writeBook();
            break;
        case 7:
            displayAllBooks();
            break;
        case 8: {
            char n[6];
            system("cls");
            cout << "\n\n\tPlease Enter The book No. ";
            cin >> n;
            displaySpecificBook(n);
            break;
        }
        case 9:
            modifyBook();
            break;
        case 10:
            deleteBook();
            break;
        case 11:
            return;
        default:
            cout << "\a";
    }
    }

}

//***************************************************************
//    	THE MAIN FUNCTION OF PROGRAM
//****************************************************************


int main() {
    int ch;
    intro();
    do {
        system("cls");
        cout << "\n\n\n\tMAIN MENU";
        cout << "\n\n\t01. BOOK ISSUE";
        cout << "\n\n\t02. BOOK DEPOSIT";
        cout << "\n\n\t03. ADMINISTRATOR MENU";
        cout << "\n\n\t04. EXIT";
        cout << "\n\n\tPlease Select Your Option (1-4) _____ ";
        ch = getche();
        switch (ch) {
            case '1':
                system("cls");
                bookIssue();
                break;
            case '2':
                bookDeposit();
                break;
            case '3':
                adminMenu();
                break;
            case '4':
                break;
            default :
                cout << "\a";
        }
    } while (ch != '4');
}

//***************************************************************
//    			END OF PROJECT
//***************************************************************
