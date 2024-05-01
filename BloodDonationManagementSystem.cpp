#define _CRT_SECURE_NO_WARNINGS	// to let local time usable
#include <iostream> //standard input-output stream
#include <string> //library enable string input
#include <conio.h> 
#include <ctime> //library for enable time 
#include <stdlib.h>
#include <algorithm>
#include <windows.h>
#include <string.h>
#include <iomanip> //input-output 
#include <mysql.h> //libmysql
#include <fstream>
#pragma comment(lib, "libmysql")

using namespace std;

//global variable for database connection
int qstate;
MYSQL* conn;
MYSQL_ROW row;
MYSQL_FIELD fields;
MYSQL_RES* res;

//global variable for login as admin, staff or donor
string Admin_ID, Staff_ID, Donor_ID, Staff_Name, Donor_Name;

//class for database connection
class db_response
{
public:
    static void ConnectionFunction()
    {
        //check whether if database connected
        conn = mysql_init(0);
        if (conn)
        {
            cout << "Database Connected!" << endl;
            system("cls");
        }
        else
        {
            cout << "Failed To Connect!" << mysql_errno(conn) << endl;
        }

        //check whether if database connected
        conn = mysql_real_connect(conn, "localhost", "root", "", "db_workshop1_sem2", 3306, NULL, 0);
        if (conn)
        {
            cout << "Database db_workshop1_sem2 Connected To MySql!" << endl;
            //_getch();
        }
        else
        {
            cout << "Failed To Connect!" << mysql_errno(conn) << endl;
        }
    }
};

//color design 
enum Color {
    Black,
    Blue,
    Green,
    Cyan,
    Red,
    Magenta,
    Yellow,
    White,
    Gray,
    Light_Blue,
    Light_Green,
    Light_Aqua,
    Light_Red,
    Light_Purple,
    Light_Yellow,
    Bright_White,
};

//text design
enum Text
{
    Underline,
    Reset_Underline,
};

//background color
string background(Color color) {
    switch (color) {
    case Black:
        return "\u001b[40m";
    case Blue:
        return "\u001b[44m";
    case Green:
        return "\u001b[42m";
    case Cyan:
        return "\u001b[46m";
    case Red:
        return "\u001b[41m";
    case Magenta:
        return "\u001b[45m";
    case Yellow:
        return "\u001b[43m";
    case White:
        return "\u001b[47m";
    case Gray:
        return "\u001b[40;1m";
    case Light_Blue:
        return "\u001b[44;1m";
    case Light_Green:
        return "\u001b[42;1m";
    case Light_Aqua:
        return "\u001b[46;1m";
    case Light_Red:
        return "\u001b[41;1m";
    case Light_Purple:
        return "\u001b[45;1m";
    case Light_Yellow:
        return "\u001b[43;1m";
    case Bright_White:
        return "\u001b[47;1m";
    default:
        throw std::invalid_argument("invalid value");
    }
}

//text color
string foreground(Color color) {
    switch (color) {
    case Black:
        return "\u001b[30m";
    case Blue:
        return "\u001b[34m";
    case Green:
        return "\u001b[32m";
    case Cyan:
        return "\u001b[36m";
    case Red:
        return "\u001b[31m";
    case Magenta:
        return "\u001b[35m";
    case Yellow:
        return "\u001b[33m";
    case White:
        return "\u001b[37m";
    case Gray:
        return "\u001b[30;1m";
    case Light_Blue:
        return "\u001b[34;1m";
    case Light_Green:
        return "\u001b[32;1m";
    case Light_Aqua:
        return "\u001b[36;1m";
    case Light_Red:
        return "\u001b[31;1m";
    case Light_Purple:
        return "\u001b[35;1m";
    case Light_Yellow:
        return "\u001b[33;1m";
    case Bright_White:
        return "\u001b[37;1m";
    default:
        throw std::invalid_argument("invalid value");
    }
}

string resetANSI() {
    return "\u001b[0m";
}

string underline(Text reply)
{
    switch (reply)
    {
    case Underline:
        return "\033[4m";
    case Reset_Underline:
        return "\033[0m";
    }

}

/********************\
* FUNCTION PROTOTYPE *
\*********************/
int main();
void Loading();
void MainLogin(); //Login Function
void Registration(); //Registration Function
void ForgetPassword(); //If forget password

void AdminLogin();
void AdminMainMenu(string);//admin main menu after successful login
void AdminControlMain();

//Admin Control Function
void AdminAdd();
void AdminDelete();
void AdminUpdate();
void AdminSearch();
void AdminDisplay();

void AdminReportMain();

void StaffLogin();
void StaffMainMenu(string, string); //staff main menu after successful login
void StaffControlMain();
void StaffAccount(string);

void StaffControlAdd();
void AddHospitalMenu();
void AddDonorMenu();
void AddBloodMenu();
void AddDonationMenu();

void StaffControlDelete();
void DeleteHospital();
void DeleteDonor();
void DeleteBlood();
void DeleteDonation();

void StaffControlUpdate();
void UpdateHospital();
void UpdateDonor();
void UpdateDonation();
void UpdateBlood();

void StaffControlSearch();
void SearchHospital();
void SearchDonor();
void SearchDonation();
void SearchBlood();

void RecentDonation();

void StaffReport();

void DonorLogin();
void DonorMainMenu(string, string); //donor main menu after successful login
void DonorDonation(string);
void DonorAccount(string);

//External function
void ShowTime();
int calculateAge(int, int, int);
int convertToInt(string str);

/**************************\
* FUNCTION IMPLEMENTATION *
\**************************/

//main function
int main()
{
    Loading();
    system("cls"); //clear the screen

    //adjusting windows console size
    HWND console = GetConsoleWindow();
    RECT r;
    GetWindowRect(console, &r);

    MoveWindow(console, r.left, r.top, 1500, 650, TRUE); //width=1500, height=650
    db_response::ConnectionFunction();
    char optionMain;
    cout << "\n";
    ShowTime();
    cout << background(White) << foreground(Black) << endl;
    cout << "---------------------------------------------" << endl;
    cout << " Welcome to Blood Donation Management System " << endl;
    cout << "---------------------------------------------";
    cout << background(Black) << foreground(White) << resetANSI() << endl;

    cout << " [1] Login " << endl;
    cout << " [2] Register " << endl;
    cout << " [3] Exit " << endl;
    cout << endl;

    cout << "Enter your option: ";
    cin >> optionMain;

    //validation of option
    while (optionMain != '1' && optionMain != '2' && optionMain != '3')
    {
        cout << "Invalid Choice" << endl;
        cout << "Please re-enter your option: " << endl;
        cin >> optionMain;
    }

    //Choice of homemenu
    if (optionMain == '1')
    {
        MainLogin();
    }
    else if (optionMain == '2')
    {
        Registration();
    }
    else if (optionMain == '3')
    {
        exit(3);
    }
    else
    {
        cout << "Invalid!";
        system("pause");
        main();
    }
}

//login main menu
void MainLogin()
{
    system("cls");
    cout << background(Magenta) << foreground(White);
    char choiceLogin;
    cout << "-------" << endl;
    cout << " LOGIN " << endl;
    cout << "-------" << endl;
    cout << background(Black) << foreground(White) << resetANSI() << endl;
    cout << foreground(Light_Red);
    cout << "[1] Login As Admin " << endl;
    cout << foreground(Cyan);
    cout << "[2] Login As Staff " << endl;
    cout << foreground(Light_Green);
    cout << "[3] Login As Donor " << endl;
    cout << foreground(Yellow);
    cout << "[4] Forget Password" << endl;
    cout << background(Black) << foreground(White) << resetANSI();
    cout << "[5] Back to Main Menu" << endl;
    cout << endl;

    while (1) {
        cout << "Enter your choice (Number 1 - 5 only): ";
        cin >> choiceLogin;

        if (choiceLogin == '1') {
            AdminLogin();
        }
        else if (choiceLogin == '2') {
            StaffLogin();
        }
        else if (choiceLogin == '3') {
            DonorLogin();
        }
        else if (choiceLogin == '4') {
            system("cls");
            ForgetPassword();
        }
        else if (choiceLogin == '5') {
            system("cls");
            main();
        }
        else {
            cout << "Invalid Choice! Only numeric number! Please enter again! ";
            cout << "\n";
            system("pause");
            MainLogin();
        }
    }
}

//recover password if user 
void ForgetPassword()
{
    system("cls");
    cout << background(Yellow) << foreground(Black);
    cout << "-------------------" << endl;
    cout << " PASSWORD RECOVERY " << endl;
    cout << "-------------------" << endl;
    cout << background(Black) << foreground(White) << resetANSI();

    char recover;

    cout << "\nAre you a ?" << endl;
    cout << "[1] Admin/Staff" << endl;
    cout << "[2] Donor" << endl;
    cout << "[M] Main Menu" << endl;

    cout << "\nYour choice: ";
    cin >> recover;

    if (recover == '1')
    {
        string Staff_Password;
        system("cls");
        cout << "-------------" << endl;
        cout << " ADMIN/STAFF " << endl;
        cout << "-------------" << endl;
        cout << "\nPlease insert your staff ID: ";
        cin >> Staff_ID;

        string search_query = "SELECT Staff_ID FROM staff WHERE Staff_ID = '" + Staff_ID + "' AND Active_Status = 'Active'";
        const char* q = search_query.c_str();
        qstate = mysql_query(conn, q);
        if (!qstate)
        {
            res = mysql_store_result(conn);
            while (row = mysql_fetch_row(res))
            {
                Staff_ID = row[0];
            }
            cout << "Staff found!" << endl;
            cout << "Set your new password: ";
            char ch;
            while ((ch = _getch()) != 13)
            {
                Staff_Password += ch;
                cout << "*";
            }

            string update_query = "UPDATE staff SET Staff_Password = sha1('" + Staff_Password + "') WHERE Staff_ID = '" + Staff_ID + "'";
            const char* q = update_query.c_str();
            qstate = mysql_query(conn, q);
            cout << "\n Successfully Updated!" << endl;
            system("pause");
            MainLogin();
        }
        else
        {
            cout << "Sorry, no such ID exist! Please try again!" << mysql_errno(conn) << endl;
            system("pause");
            MainLogin();
        }

    }
    else if (recover == '2')
    {
        string Donor_Password;
        system("cls");
        cout << "-------" << endl;
        cout << " DONOR " << endl;
        cout << "-------" << endl;
        cout << "\nPlease insert your donor ID: ";
        cin >> Donor_ID;

        string search_query = "SELECT Donor_ID FROM donor WHERE Donor_ID = '" + Donor_ID + "' AND Active_Status = 'Active'";
        const char* q = search_query.c_str();
        qstate = mysql_query(conn, q);
        if (!qstate)
        {
            res = mysql_store_result(conn);
            while (row = mysql_fetch_row(res))
            {
                Donor_ID = row[0];
            }
            cout << "Donor found!" << endl;
            cout << "Set your new password: ";
            char ch;
            while ((ch = _getch()) != 13)
            {
                Donor_Password += ch;
                cout << "*";
            }

            string update_query = "UPDATE donor SET Donor_Password = sha1('" + Donor_Password + "') WHERE Donor_ID = '" + Donor_ID + "'";
            const char* q = update_query.c_str();
            qstate = mysql_query(conn, q);
            cout << "\n Successfully Updated!" << endl;
            system("pause");
            MainLogin();
        }
        else
        {
            cout << "Sorry, no such ID exist! Please try again!" << mysql_errno(conn) << endl;
            system("pause");
            MainLogin();
        }

    }
    else if (recover == 'M' || recover == 'm')
    {
        MainLogin();
    }
    else
    {
        cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
        system("pause");
        MainLogin();
    }
}

//admin login page
void AdminLogin()
{
    string Staff_Password;

    system("cls");
    cout << background(Red) << foreground(White);
    cout << "----------------" << endl;
    cout << " LOGIN AS ADMIN " << endl;
    cout << "----------------" << endl;
    cout << background(Black) << foreground(White) << resetANSI();
    cout << endl;

    cout << "Enter Admin ID: ";
    cin >> Admin_ID;
    cout << "Enter Password: ";
    char ch;
    while ((ch = _getch()) != 13)
    {
        Staff_Password += ch;
        cout << "*";
    }

    string checkUser_query = "Select Admin_ID, Staff_Name from staff Where Admin_ID = Staff_ID AND Admin_ID = '" + Admin_ID + "' AND Staff_Password = sha1('" + Staff_Password + "') AND Active_Status = 'Active'";
    const char* cu = checkUser_query.c_str();
    qstate = mysql_query(conn, cu);
    if (!qstate)
    {
        res = mysql_store_result(conn);
        if (res->row_count == 1)
        {
            while (row = mysql_fetch_row(res))
            {
                Admin_ID = row[0];
                Staff_Name = row[1];
            }

            system("cls");
            AdminMainMenu(Staff_Name);
        }
        else
        {
            char c;
            cout << "\nInvalid username or password. Want to try again? (Y/N): ";
            cin >> c;
            if (c == 'y' || c == 'Y')
                AdminLogin();
            else
                MainLogin();
        }
    }
    else
        cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
}

//admin menu after successful login
void AdminMainMenu(string name)
{
    char AdminMain;
    system("cls");
    cout << foreground(White) << background(Red);
    cout << "-----------------" << endl;
    cout << " ADMIN MAIN MENU " << endl;
    cout << "-----------------" << endl;
    cout << background(Black) << foreground(White);
    cout << "Welcome, admin " << background(Black) << foreground(Red) << name << background(Black) << foreground(White) << "!" << endl;
    cout << background(Black) << foreground(White) << resetANSI();
    cout << endl;

    cout << "[1] Administration Control" << endl;
    cout << "[2] Staff Records" << endl;
    cout << "[3] Report Generation" << endl;
    cout << "[4] Back to main menu" << endl;

    cout << "\nPlease enter your choice: ";
    cin >> AdminMain;

    if (AdminMain == '1')
    {
        AdminControlMain();
    }
    else if (AdminMain == '2')
    {
        AdminDisplay();
    }
    else if (AdminMain == '3')
    {
        AdminReportMain();
    }
    else if (AdminMain == '4')
    {
        main();
    }
    else {
        cout << "Invalid!" << endl;
        AdminMainMenu(name);
    }
}

//Admin Control Main Page
void AdminControlMain()
{
    char adminControl;
    system("CLS");
    cout << background(Red) << foreground(Black);
    cout << "--------------------" << endl;
    cout << " ADMIN CONTROL MENU " << endl;
    cout << "--------------------" << endl;
    cout << background(Black) << foreground(White) << resetANSI();
    cout << "Welcome, admin! What would you like to do with Staff?" << endl;
    cout << endl;

    cout << "[A] Add Staff Record" << endl;
    cout << "[B] Delete Staff Record" << endl;
    cout << "[C] Update Staff Record" << endl;
    cout << "[D] Search Staff Record" << endl;
    cout << "[M] Main Menu" << endl;

    cout << "" << endl;
    cout << "Enter your choice (A, B, C, D, M): ";
    cin >> adminControl;

    if (adminControl == 'A' || adminControl == 'a') {
        system("cls");
        AdminAdd();
    }
    else if (adminControl == 'B' || adminControl == 'b') {
        system("cls");
        AdminDelete();
    }
    else if (adminControl == 'C' || adminControl == 'c') {
        system("cls");
        AdminUpdate();
    }
    else if (adminControl == 'D' || adminControl == 'd') {
        system("cls");
        AdminSearch();
    }
    else if (adminControl == 'M' || adminControl == 'm') {
        system("cls");
        AdminMainMenu(Staff_Name);
    }

    else {
        cout << "Error!";
        cout << "Press any key to back to main control for admin...";
        system("pause");
        AdminControlMain();
    }
}

//Admin Control Function
void AdminAdd()
{
    system("cls");
    string Staff_ID, Staff_Name, Staff_Gender, Staff_Address, Staff_Telno, Staff_Position, Staff_Password, Admin_ID, Hospital_ID;
    int Staff_Age;
    char continueAdd;
    cout << background(Red) << foreground(Black);
    cout << "-------------------" << endl;
    cout << " ADMIN ADD - STAFF " << endl;
    cout << "-------------------" << endl;
    cout << background(Black) << foreground(White) << resetANSI();
    cout << "Enter new records: " << endl;
    cout << "Staff ID (Non-negative numbers only): ";

    int IDNum;
    cin >> IDNum;

    string StID;
    if (IDNum >= 0 && IDNum < 10)
    {
        StID.append("ST000");
        StID.append(to_string(IDNum));
    }
    else if (IDNum >= 10 && IDNum < 100)
    {

        StID.append("ST00");
        StID.append(to_string(IDNum));
    }
    else if (IDNum >= 100 && IDNum < 1000)
    {
        StID.append("ST0");
        StID.append(to_string(IDNum));
    }
    else if (IDNum >= 1000 && IDNum < 10000)
    {
        StID.append("ST");
        StID.append(to_string(IDNum));
    }
    else
    {
        cout << "Invalid Input! Non-negative Integer (0-9) is used! Please try again!";
        system("pause");
        system("cls");
        AdminControlMain();
    }

    Staff_ID = StID;

    cout << "Name: ";
    cin.ignore(1, '\n');
    getline(cin, Staff_Name);
    cout << "Gender [M/F]: ";
    getline(cin, Staff_Gender);
    cout << "Age: ";
    cin >> Staff_Age;
    cout << "Address: ";
    cin.ignore(1, '\n');
    getline(cin, Staff_Address);
    cout << "Telephone Number: ";
    getline(cin, Staff_Telno);
    cout << "Position: ";
    getline(cin, Staff_Position);
    cout << "Staff Password: ";
    getline(cin, Staff_Password);
    cout << "Admin ID: ";
    getline(cin, Admin_ID);
    cout << "Hospital ID: ";
    getline(cin, Hospital_ID);

    string Active_Status = "Active";

    string insertStaff_query = "INSERT INTO staff (Staff_ID, Staff_Name, Staff_Gender, Staff_Age, Staff_Address, Staff_Telno, Staff_Position, Staff_Password, Admin_ID, Active_Status) values ('" + Staff_ID + "', '" + Staff_Name + "', '" + Staff_Gender + "', '" + to_string(Staff_Age) + "', '" + Staff_Address + "', '" + Staff_Telno + "', '" + Staff_Position + "', sha1('" + Staff_Password + "'), '" + Admin_ID + "', '" + Active_Status + "')";
    const char* q = insertStaff_query.c_str();
    qstate = mysql_query(conn, q);

    if (!qstate)
    {
        string insertStaff_query = "INSERT INTO staff_record (Staff_ID, Hospital_ID) values ('" + Staff_ID + "' , '" + Hospital_ID + "')";
        const char* q = insertStaff_query.c_str();
        qstate = mysql_query(conn, q);

        if (!qstate)
        {
            cout << endl << "Done." << endl;
        }
        else
        {
            cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
        }
        cout << endl << "A staff is successful added in database." << endl;
    }
    else
    {
        cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
    }

    do
    {
        cout << "Do you want add another record? (Y/N): ";
        cin >> continueAdd;
        if (continueAdd == 'y' || continueAdd == 'Y')
        {
            AdminAdd();
        }
        else if (continueAdd == 'n' || continueAdd == 'N')
        {
            AdminControlMain();
        }
    } while (continueAdd == 'y' || continueAdd == 'Y' || continueAdd == 'n' || continueAdd == 'N');
}

void AdminDelete()
{
    char confirmDel, DeleteAdmin;
    string Staff_ID;
    system("cls");
    cout << background(Red) << foreground(White);
    cout << "----------------------" << endl;
    cout << " ADMIN DELETE - STAFF " << endl;
    cout << "----------------------" << endl;
    cout << background(Black) << foreground(White) << resetANSI() << endl;
    cout << "\nEnter staff ID to search (Format:ST****): ";
    cin >> Staff_ID;

    cout << "\nHere's the record found: \n" << endl;
    string searchDel_query = "SELECT r.Staff_ID, s.Staff_Name, s.Staff_Gender, s.Staff_Age, s.Staff_Address, s.Staff_Telno, s.Staff_Position, h.Hospital_ID FROM staff s, staff_record r, hospital h WHERE r.Staff_ID = s.Staff_ID AND r.Hospital_ID = h.Hospital_ID AND s.Staff_ID = '" + Staff_ID + "' AND Active_Status = 'Active'";
    const char* q = searchDel_query.c_str();
    qstate = mysql_query(conn, q);
    if (!qstate)
    {
        res = mysql_store_result(conn);
        while (row = mysql_fetch_row(res))
        {
            cout << "Staff ID: " << row[0] << endl;
            cout << "Name: " << row[1] << endl;
            cout << "Gender: " << row[2] << endl;
            cout << "Age: " << row[3] << endl;
            cout << "Address: " << row[4] << endl;
            cout << "Phone: " << row[5] << endl;
            cout << "Position: " << row[6] << endl;
            cout << "Hospital: " << row[7] << endl;
        }
    }
    else
    {
        cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
        AdminDelete();
    }
    cout << "Are you confirm to delete this record? [Y/N]: ";
    cin >> confirmDel;

    if (confirmDel == 'Y' || confirmDel == 'y')
    {
        //Real time delete environment doesn't allow user to delete data in the database mysql
        // so soft delete is completed by updating status
        // real delete statement in sql
        // string delete_query = "DELETE FROM staff where staff_id = '" + Staff_ID + "'";
        string update_query = "UPDATE staff SET Active_Status = 'Inactive' WHERE Staff_ID = '" + Staff_ID + "'";
        const char* q = update_query.c_str();
        qstate = mysql_query(conn, q);
        cout << "Successfully delete a staff! " << endl;
        cout << endl << "Do you want to continue deleting? [Y/N]: ";
        cin >> DeleteAdmin;
        if (DeleteAdmin == 'y' || DeleteAdmin == 'Y')
            AdminDelete();
        else if (DeleteAdmin == 'n' || DeleteAdmin == 'N')
            AdminControlMain();
    }
    else
    {
        cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
        AdminControlMain();
    }
}

void AdminUpdate()
{
    string Staff_ID;
    char confirmUpd, continueUpd, UpdChoice, UpdateAdmin;
    system("cls");
    cout << background(Red) << foreground(White);
    cout << "----------------------" << endl;
    cout << " ADMIN UPDATE - STAFF " << endl;
    cout << "----------------------" << endl;
    cout << background(Black) << foreground(White) << endl;
    cout << "\nEnter staff ID to search: ";
    cin >> Staff_ID;

    cout << "\nHere's the record found: \n" << endl;
    string searchUpd_query = "SELECT r.Staff_ID, s.Staff_Name, s.Staff_Gender, s.Staff_Age, s.Staff_Address, s.Staff_Telno, s.Staff_Position, h.Hospital_ID FROM staff s, staff_record r, hospital h WHERE r.Staff_ID = s.Staff_ID AND r.Hospital_ID = h.Hospital_ID AND s.Staff_ID = '" + Staff_ID + "' AND Active_Status = 'Active'";
    const char* q = searchUpd_query.c_str();
    qstate = mysql_query(conn, q);
    if (!qstate)
    {
        res = mysql_store_result(conn);
        while (row = mysql_fetch_row(res))
        {
            cout << "Staff ID: " << row[0] << endl;
            cout << "Name: " << row[1] << endl;
            cout << "Gender: " << row[2] << endl;
            cout << "Age: " << row[3] << endl;
            cout << "Address: " << row[4] << endl;
            cout << "Phone: " << row[5] << endl;
            cout << "Position: " << row[6] << endl;
            cout << "Hospital ID: " << row[7] << endl;
        }

        cout << "Are you confirm to update staff information? [Y/N]: ";
        cin >> confirmUpd;

        if (confirmUpd == 'Y' || confirmUpd == 'y')
        {
            cout << "----------------------------" << endl;
            cout << "  Updation of Information " << endl;
            cout << "----------------------------" << endl;
            cout << "\nEnter information that you want to update: " << endl;
            cout << "[1] Name " << endl;
            cout << "[2] Gender " << endl;
            cout << "[3] Age " << endl;
            cout << "[4] Address " << endl;
            cout << "[5] Phone " << endl;
            cout << "[6] Position " << endl;
            cout << "[7] Password " << endl;
            cout << "[8] Hospital ID " << endl;

            cout << "\nYour choice >> ";
            cin >> UpdChoice;

            if (UpdChoice == '1') {
                string Staff_Name;
                cout << "Name: ";
                cin.ignore(1, '\n');
                getline(cin, Staff_Name);

                string update_query = "UPDATE staff SET Staff_Name = '" + Staff_Name + "' WHERE Staff_ID = '" + Staff_ID + "' AND Active_Status = 'Active'";
                const char* q = update_query.c_str();
                qstate = mysql_query(conn, q);
                cout << "\n Successfully Updated!" << endl;
                cout << "Do you want to continue update record? [Y/N]: ";
                cin >> continueUpd;

                if (continueUpd == 'Y' || continueUpd == 'y')
                    AdminUpdate();
                else
                    AdminControlMain();
            }

            else if (UpdChoice == '2') {
                string Staff_Gender;
                cout << "Gender [M/F]: ";
                cin >> Staff_Gender;

                string update_query = "UPDATE staff SET Staff_Gender = '" + Staff_Gender + "' WHERE Staff_ID = '" + Staff_ID + "'  AND Active_Status = 'Active'";
                const char* q = update_query.c_str();
                qstate = mysql_query(conn, q);
                cout << "\n Successfully Updated!" << endl;
                cout << "Do you want to continue update record? [Y/N]: ";
                cin >> continueUpd;

                if (continueUpd == 'Y' || continueUpd == 'y')
                    AdminUpdate();
                else
                    AdminControlMain();
            }

            else if (UpdChoice == '3') {
                int Staff_Age;
                cout << "Age: ";
                cin >> Staff_Age;

                string update_query = "UPDATE staff SET Staff_Age = '" + to_string(Staff_Age) + "' WHERE Staff_ID = '" + Staff_ID + "'  AND Active_Status = 'Active'";
                const char* q = update_query.c_str();
                qstate = mysql_query(conn, q);
                cout << "\n Successfully Updated!" << endl;
                cout << "Do you want to continue update record? [Y/N]: ";
                cin >> continueUpd;

                if (continueUpd == 'Y' || continueUpd == 'y')
                    AdminUpdate();
                else
                    AdminControlMain();

            }

            else if (UpdChoice == '4') {
                string Staff_Address;
                cout << "Address: ";
                cin >> Staff_Address;

                string update_query = "UPDATE staff SET Staff_Address = '" + Staff_Address + "' WHERE Staff_ID = '" + Staff_ID + "' AND Active_Status = 'Active'";
                const char* q = update_query.c_str();
                qstate = mysql_query(conn, q);
                cout << "\n Successfully Updated!" << endl;
                cout << "Do you want to continue update record? [Y/N]: ";
                cin >> continueUpd;

                if (continueUpd == 'Y' || continueUpd == 'y')
                    AdminUpdate();
                else
                    AdminControlMain();
            }

            else if (UpdChoice == '5') {
                string Staff_Telno;
                cout << "Phone: ";
                cin >> Staff_Telno;

                string update_query = "UPDATE staff SET Staff_Telno = '" + Staff_Telno + "' WHERE Staff_ID = '" + Staff_ID + "' AND Active_Status = 'Active'";
                const char* q = update_query.c_str();
                qstate = mysql_query(conn, q);
                cout << "\n Successfully Updated!" << endl;
                cout << "Do you want to continue update record? [Y/N]: ";
                cin >> continueUpd;

                if (continueUpd == 'Y' || continueUpd == 'y')
                    AdminUpdate();
                else
                    AdminControlMain();
            }

            else if (UpdChoice == '6') {
                string Staff_Position;
                cout << "Position: ";
                cin >> Staff_Position;

                string update_query = "UPDATE staff SET Staff_Position = '" + Staff_Position + "' WHERE Staff_ID = '" + Staff_ID + "' AND Active_Status = 'Active'";
                const char* q = update_query.c_str();
                qstate = mysql_query(conn, q);
                cout << "\n Successfully Updated!" << endl;
                cout << "Do you want to continue update record? [Y/N]: ";
                cin >> continueUpd;

                if (continueUpd == 'Y' || continueUpd == 'y')
                    AdminUpdate();
                else
                    AdminControlMain();
            }

            else if (UpdChoice == '7') {
                string Staff_Password;
                cout << "Password: ";
                char ch;
                while ((ch = _getch()) != 13)
                {
                    Staff_Password += ch;
                    cout << "*";
                }

                string update_query = "UPDATE staff SET Staff_Password = sha1('" + Staff_Password + "') WHERE Staff_ID = '" + Staff_ID + "' AND Active_Status = 'Active'";
                const char* q = update_query.c_str();
                qstate = mysql_query(conn, q);
                cout << "\n Successfully Updated!" << endl;
                cout << "Do you want to continue update record? [Y/N]: ";
                cin >> continueUpd;

                if (continueUpd == 'Y' || continueUpd == 'y')
                    AdminUpdate();
                else
                    AdminControlMain();
            }

            else if (UpdChoice == '8') {

                string Hospital_ID;

                cout << "Hospital ID: ";
                int IDNum4;
                cin >> IDNum4;

                string HsID;
                if (IDNum4 >= 0 && IDNum4 < 10)
                {
                    HsID.append("HS000");
                    HsID.append(to_string(IDNum4));
                }
                else if (IDNum4 >= 10 && IDNum4 < 100)
                {

                    HsID.append("HS00");
                    HsID.append(to_string(IDNum4));
                }
                else if (IDNum4 >= 100 && IDNum4 < 1000)
                {
                    HsID.append("DN0");
                    HsID.append(to_string(IDNum4));
                }
                else if (IDNum4 >= 1000 && IDNum4 < 10000)
                {
                    HsID.append("DN");
                    HsID.append(to_string(IDNum4));
                }
                else
                {
                    cout << "Invalid Input! Non-negative Integer (0-9) is used! Please try again!";
                    system("pause");
                    system("cls");
                    AdminControlMain();
                }
                Hospital_ID = HsID;

                string update_query = "UPDATE staff_record SET Hospital_ID = '" + Hospital_ID + "' WHERE Staff_ID = '" + Staff_ID + "'  AND Active_Status = 'Active'";
                const char* q = update_query.c_str();
                qstate = mysql_query(conn, q);
                cout << "\n Successfully Updated!" << endl;
                cout << "Do you want to continue update record? [Y/N]: ";
                cin >> continueUpd;

                if (continueUpd == 'Y' || continueUpd == 'y')
                    AdminUpdate();
                else
                    AdminControlMain();
            }

            else {
                cout << "Error in updation! " << endl;
                system("pause");
                AdminUpdate();
            }

        }

        else
        {
            AdminControlMain();
        }

    }
    else
    {
        cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
        system("pause");
        AdminControlMain();
    }
}

void AdminSearch()
{
    string Staff_ID, Staff_Name, Staff_Gender, Staff_Address, Staff_Telno, Staff_Position, Staff_Password, Admin_ID;
    int Staff_Age;
    system("cls");
    cout << background(Red) << foreground(White);
    cout << "----------------------" << endl;
    cout << " ADMIN SEARCH - STAFF " << endl;
    cout << "----------------------" << endl;
    cout << background(Black) << foreground(White) << endl;
    cout << "\nChoose the attribute that you want to search: " << endl;
    cout << "[1] Staff ID" << endl;
    cout << "[2] Name " << endl;
    cout << "[3] Gender " << endl;
    cout << "[4] Age " << endl;
    cout << "[5] Address " << endl;
    cout << "[6] Phone " << endl;
    cout << "[7] Position " << endl;
    cout << "[8] Hospital ID " << endl;
    cout << "[9] Back to main menu " << endl;
    cout << "\nYour choice >> ";

    int searchChoice;
    char SearchAdmin;
    cin >> searchChoice;

    if (searchChoice == 1)
    {
        cout << "\nEnter Staff ID to search: ";
        cin >> Staff_ID;

        cout << "\nHere's the record found: \n" << endl;
        string search_query = "SELECT r.Staff_ID, s.Staff_Name, s.Staff_Gender, s.Staff_Age, s.Staff_Address, s.Staff_Telno, s.Staff_Position, h.Hospital_ID FROM staff s, staff_record r, hospital h WHERE r.Staff_ID = s.Staff_ID AND r.Hospital_ID = h.Hospital_ID AND s.Staff_ID = '" + Staff_ID + "' AND Active_Status = 'Active'";
        const char* q = search_query.c_str();
        qstate = mysql_query(conn, q);
        if (!qstate)
        {
            res = mysql_store_result(conn);
            while (row = mysql_fetch_row(res))
            {
                cout << "Staff ID: " << row[0] << endl;
                cout << "Name: " << row[1] << endl;
                cout << "Gender: " << row[2] << endl;
                cout << "Age: " << row[3] << endl;
                cout << "Address: " << row[4] << endl;
                cout << "Phone: " << row[5] << endl;
                cout << "Position: " << row[6] << endl;
                cout << "Hospital ID: " << row[7] << endl;
                cout << endl;
            }
            cout << endl << "Do you want to continue searching?[Y/N]: ";
            cin >> SearchAdmin;
            if (SearchAdmin == 'y' || SearchAdmin == 'Y')
                AdminSearch();
            else if (SearchAdmin == 'n' || SearchAdmin == 'N')
                AdminControlMain();
        }
        else
        {
            cout << "There's no any result about staff found! " << endl;
            cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
            system("pause");
            system("cls");
            AdminControlMain();
        }
    }

    else if (searchChoice == 2)
    {
        cout << "\nEnter Staff Name to search: ";
        cin.ignore(1, '\n');
        getline(cin, Staff_Name);

        cout << "\nHere's the record found: \n" << endl;
        string search_query2 = "SELECT r.Staff_ID, s.Staff_Name, s.Staff_Gender, s.Staff_Age, s.Staff_Address, s.Staff_Telno, s.Staff_Position, h.Hospital_ID FROM staff s, staff_record r, hospital h WHERE r.Staff_ID = s.Staff_ID AND r.Hospital_ID = h.Hospital_ID AND s.Staff_Name LIKE '%" + Staff_Name + "%' AND Active_Status = 'Active'";
        const char* q = search_query2.c_str();
        qstate = mysql_query(conn, q);
        if (!qstate)
        {
            res = mysql_store_result(conn);
            while (row = mysql_fetch_row(res))
            {
                cout << "Staff ID: " << row[0] << endl;
                cout << "Name: " << row[1] << endl;
                cout << "Gender: " << row[2] << endl;
                cout << "Age: " << row[3] << endl;
                cout << "Address: " << row[4] << endl;
                cout << "Phone: " << row[5] << endl;
                cout << "Position: " << row[6] << endl;
                cout << "Hospital ID: " << row[7] << endl;
                cout << endl;
            }
            cout << endl << "Do you want to continue searching?[Y/N]: ";
            cin >> SearchAdmin;
            if (SearchAdmin == 'y' || SearchAdmin == 'Y')
                AdminSearch();
            else if (SearchAdmin == 'n' || SearchAdmin == 'N')
                AdminControlMain();
        }
        else
        {
            cout << "There's no any result about staff found! " << endl;
            cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
            system("pause");
            system("cls");
            AdminControlMain();
        }

    }

    else if (searchChoice == 3)
    {
        cout << "\nEnter Staff Gender to search [M/F]: ";
        cin >> Staff_Gender;

        cout << "\nHere's the record found: \n" << endl;
        string search_query3 = "SELECT r.Staff_ID, s.Staff_Name, s.Staff_Gender, s.Staff_Age, s.Staff_Address, s.Staff_Telno, s.Staff_Position, h.Hospital_ID FROM staff s, staff_record r, hospital h WHERE r.Staff_ID = s.Staff_ID AND r.Hospital_ID = h.Hospital_ID AND s.Staff_Gender = '" + Staff_Gender + "' AND Active_Status = 'Active'";
        const char* q = search_query3.c_str();
        qstate = mysql_query(conn, q);
        if (!qstate)
        {
            res = mysql_store_result(conn);
            while (row = mysql_fetch_row(res))
            {
                cout << "Staff ID: " << row[0] << endl;
                cout << "Name: " << row[1] << endl;
                cout << "Gender: " << row[2] << endl;
                cout << "Age: " << row[3] << endl;
                cout << "Address: " << row[4] << endl;
                cout << "Phone: " << row[5] << endl;
                cout << "Position: " << row[6] << endl;
                cout << "Hospital ID: " << row[7] << endl;
                cout << endl;
            }
            cout << endl << "Do you want to continue searching?[Y/N]: ";
            cin >> SearchAdmin;
            if (SearchAdmin == 'y' || SearchAdmin == 'Y')
                AdminSearch();
            else if (SearchAdmin == 'n' || SearchAdmin == 'N')
                AdminControlMain();
        }
        else
        {
            cout << "There's no any result about staff found! " << endl;
            cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
            system("pause");
            system("cls");
            AdminControlMain();
        }

    }

    else if (searchChoice == 4)
    {
        cout << "\nEnter Staff Age to search: ";
        cin >> Staff_Age;

        cout << "\nHere's the record found: \n" << endl;
        string search_query4 = "SELECT r.Staff_ID, s.Staff_Name, s.Staff_Gender, s.Staff_Age, s.Staff_Address, s.Staff_Telno, s.Staff_Position, h.Hospital_ID FROM staff s, staff_record r, hospital h WHERE r.Staff_ID = s.Staff_ID AND r.Hospital_ID = h.Hospital_ID AND s.Staff_Age = '" + to_string(Staff_Age) + "' AND Active_Status = 'Active'";
        const char* q = search_query4.c_str();
        qstate = mysql_query(conn, q);
        if (!qstate)
        {
            res = mysql_store_result(conn);
            while (row = mysql_fetch_row(res))
            {
                cout << "Staff ID: " << row[0] << endl;
                cout << "Name: " << row[1] << endl;
                cout << "Gender: " << row[2] << endl;
                cout << "Age: " << row[3] << endl;
                cout << "Address: " << row[4] << endl;
                cout << "Phone: " << row[5] << endl;
                cout << "Position: " << row[6] << endl;
                cout << "Hospital ID: " << row[7] << endl;
                cout << endl;
            }
            cout << endl << "Do you want to continue searching?[Y/N]: ";
            cin >> SearchAdmin;
            if (SearchAdmin == 'y' || SearchAdmin == 'Y')
                AdminSearch();
            else if (SearchAdmin == 'n' || SearchAdmin == 'N')
                AdminControlMain();
        }
        else
        {
            cout << "There's no any result about staff found! " << endl;
            cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
            system("pause");
            system("cls");
            AdminControlMain();
        }

    }

    else if (searchChoice == 5)
    {
        cout << "\nEnter Address to search: ";
        cin.ignore(1, '\n');
        getline(cin, Staff_Address);

        cout << "\nHere's the record found: \n" << endl;
        string search_query2 = "SELECT r.Staff_ID, s.Staff_Name, s.Staff_Gender, s.Staff_Age, s.Staff_Address, s.Staff_Telno, s.Staff_Position, h.Hospital_ID FROM staff s, staff_record r, hospital h WHERE r.Staff_ID = s.Staff_ID AND r.Hospital_ID = h.Hospital_ID AND s.Staff_Address LIKE '%" + Staff_Address + "%' AND Active_Status = 'Active'";
        const char* q = search_query2.c_str();
        qstate = mysql_query(conn, q);
        if (!qstate)
        {
            res = mysql_store_result(conn);
            while (row = mysql_fetch_row(res))
            {
                cout << "Staff ID: " << row[0] << endl;
                cout << "Name: " << row[1] << endl;
                cout << "Gender: " << row[2] << endl;
                cout << "Age: " << row[3] << endl;
                cout << "Address: " << row[4] << endl;
                cout << "Phone: " << row[5] << endl;
                cout << "Position: " << row[6] << endl;
                cout << "Hospital ID: " << row[7] << endl;
                cout << endl;
            }
            cout << endl << "Do you want to continue searching?[Y/N]: ";
            cin >> SearchAdmin;
            if (SearchAdmin == 'y' || SearchAdmin == 'Y')
                AdminSearch();
            else if (SearchAdmin == 'n' || SearchAdmin == 'N')
                AdminControlMain();
        }
        else
        {
            cout << "There's no any result about staff found! " << endl;
            cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
            system("pause");
            system("cls");
            AdminControlMain();
        }

    }

    else if (searchChoice == 6)
    {
        cout << "\nEnter Phone Number to search: ";
        cin >> Staff_Telno;

        cout << "\nHere's the record found: \n" << endl;
        string search_query6 = "SELECT r.Staff_ID, s.Staff_Name, s.Staff_Gender, s.Staff_Age, s.Staff_Address, s.Staff_Telno, s.Staff_Position, h.Hospital_ID FROM staff s, staff_record r, hospital h WHERE r.Staff_ID = s.Staff_ID AND r.Hospital_ID = h.Hospital_ID AND s.Staff_Telno LIKE '%" + Staff_Telno + "%' AND Active_Status = 'Active'";
        const char* q = search_query6.c_str();
        qstate = mysql_query(conn, q);
        if (!qstate)
        {
            res = mysql_store_result(conn);
            while (row = mysql_fetch_row(res))
            {
                cout << "Staff ID: " << row[0] << endl;
                cout << "Name: " << row[1] << endl;
                cout << "Gender: " << row[2] << endl;
                cout << "Age: " << row[3] << endl;
                cout << "Address: " << row[4] << endl;
                cout << "Phone: " << row[5] << endl;
                cout << "Position: " << row[6] << endl;
                cout << "Hospital ID: " << row[7] << endl;
                cout << endl;
            }
            cout << endl << "Do you want to continue searching?[Y/N]: ";
            cin >> SearchAdmin;
            if (SearchAdmin == 'y' || SearchAdmin == 'Y')
                AdminSearch();
            else if (SearchAdmin == 'n' || SearchAdmin == 'N')
                AdminControlMain();
        }
        else
        {
            cout << "There's no any result about staff found! " << endl;
            cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
            system("pause");
            system("cls");
            AdminControlMain();
        }

    }

    else if (searchChoice == 7)
    {
        cout << "\nEnter Position to search: ";
        cin >> Staff_Position;

        cout << "\nHere's the record found: \n" << endl;
        string search_query7 = "SELECT r.Staff_ID, s.Staff_Name, s.Staff_Gender, s.Staff_Age, s.Staff_Address, s.Staff_Telno, s.Staff_Position, h.Hospital_ID FROM staff s, staff_record r, hospital h WHERE r.Staff_ID = s.Staff_ID AND r.Hospital_ID = h.Hospital_ID AND s.Staff_Position LIKE '%" + Staff_Position + "%' AND Active_Status = 'Active'";
        const char* q = search_query7.c_str();
        qstate = mysql_query(conn, q);
        if (!qstate)
        {
            res = mysql_store_result(conn);
            while (row = mysql_fetch_row(res))
            {
                cout << "Staff ID: " << row[0] << endl;
                cout << "Name: " << row[1] << endl;
                cout << "Gender: " << row[2] << endl;
                cout << "Age: " << row[3] << endl;
                cout << "Address: " << row[4] << endl;
                cout << "Phone: " << row[5] << endl;
                cout << "Position: " << row[6] << endl;
                cout << "Hospital ID: " << row[7] << endl;
                cout << endl;
            }
            cout << endl << "Do you want to continue searching?[Y/N]: ";
            cin >> SearchAdmin;
            if (SearchAdmin == 'y' || SearchAdmin == 'Y')
                AdminSearch();
            else if (SearchAdmin == 'n' || SearchAdmin == 'N')
                AdminControlMain();
        }
        else
        {
            cout << "There's no any result about staff found! " << endl;
            cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
            system("pause");
            system("cls");
            AdminControlMain();

        }

    }

    else if (searchChoice == 8)
    {
        string Hospital_ID;
        cout << "\nEnter Staff ID to search (ST****): ";
        cin >> Staff_ID;
        cout << "\nEnter Hospital ID to search (HS****): ";
        cin >> Hospital_ID;

        cout << "\nHere's the record found: \n" << endl;
        string search_query5 = "SELECT r.Staff_ID, s.Staff_Name, s.Staff_Gender, s.Staff_Age, s.Staff_Address, s.Staff_Telno, s.Staff_Position, h.Hospital_ID FROM staff s, staff_record r, hospital h WHERE s.Staff_ID = r.Staff_ID AND r.Hospital_ID = h.Hospital_ID AND h.Hospital_ID = '" + Hospital_ID + "' AND s.Staff_ID = '" + Staff_ID + "' AND Active_Status = 'Active'";
        const char* q = search_query5.c_str();
        qstate = mysql_query(conn, q);
        if (!qstate)
        {
            res = mysql_store_result(conn);
            while (row = mysql_fetch_row(res))
            {
                cout << "Staff ID: " << row[0] << endl;
                cout << "Name: " << row[1] << endl;
                cout << "Gender: " << row[2] << endl;
                cout << "Age: " << row[3] << endl;
                cout << "Address: " << row[4] << endl;
                cout << "Phone: " << row[5] << endl;
                cout << "Position: " << row[6] << endl;
                cout << "Hospital ID: " << row[7] << endl;
                cout << endl;

            }
            cout << endl << "Do you want to continue searching?[Y/N]: ";
            cin >> SearchAdmin;
            if (SearchAdmin == 'y' || SearchAdmin == 'Y')
                AdminSearch();
            else if (SearchAdmin == 'n' || SearchAdmin == 'N')
                AdminControlMain();
        }
        else
        {
            cout << "There's no any result about staff found! " << endl;
            cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
            system("pause");
            system("cls");
            AdminControlMain();
        }

    }

    else
    {
        cout << "Error! Invalid input for searching!" << endl;
        system("pause");
        system("cls");
        AdminControlMain();
    }
}

//display list of staffs for admin
void AdminDisplay()
{
    system("cls");
    cout << background(Red) << foreground(White);
    cout << "--------------" << endl;
    cout << " STAFF RECORD " << endl;
    cout << "--------------" << endl;
    cout << background(Black) << foreground(White) << endl;
    cout << "Here is the record of staff: \n" << endl;
    cout << background(Yellow) << foreground(Black);
    string viewStaffList_query = "SELECT Staff_ID, Staff_Name, Staff_Gender, Staff_Age, Staff_Address, Staff_Telno, Staff_Position FROM staff WHERE Active_Status = 'Active'";
    const char* vtr = viewStaffList_query.c_str();
    qstate = mysql_query(conn, vtr);
    if (!qstate)
    {
        res = mysql_store_result(conn);
        if (res->row_count >= 1)
        {
            cout << background(Yellow) << foreground(Black) << "------------------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
            printf("| %-10s | %-40s | %-8s | %-5s | %-55s | %-18s | %-10s |\n", "Staff ID", "Name", "Gender", "Age", "Address", "Telephone Number", "Position");
            cout << background(Yellow) << foreground(Black) << "------------------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
            while (row = mysql_fetch_row(res))
            {
                cout << background(White) << foreground(Black) << underline(Underline);
                printf("| %-10s | %-40s | %-8s | %-5s | %-55s | %-18s | %-10s |\n", row[0], row[1], row[2], row[3], row[4], row[5], row[6]);
            }
            cout << background(Black) << foreground(White) << underline(Reset_Underline) << resetANSI();
            cout << "------------------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
            system("pause");
            system("cls");
            AdminMainMenu(Staff_Name);
        }
        else
        {
            cout << "Error!" << endl;
            system("pause");
            AdminMainMenu(Staff_Name);
        }
    }
    else
    {
        cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
        system("pause");
        AdminMainMenu(Staff_Name);
    }
    system("pause");
    AdminMainMenu(Staff_Name);
}

//report generation for admin
void AdminReportMain()
{
    system("cls");
    ShowTime();
    string numberStaff;
    int adminReport;
    cout << background(Red) << foreground(White);
    cout << "-----------------------------" << endl;
    cout << " REPORT GENERATION FOR ADMIN " << endl;
    cout << "-----------------------------" << endl;
    cout << background(Black) << foreground(White) << resetANSI() << endl;
    string countAct_query = "Select COUNT(Staff_ID) FROM staff WHERE Active_Status = 'Active'";
    const char* staf = countAct_query.c_str();
    qstate = mysql_query(conn, staf);
    if (!qstate)
    {
        res = mysql_store_result(conn);
        if (res->row_count == 1)
        {
            while (row = mysql_fetch_row(res))
            {
                numberStaff = row[0];
            }
        }
        else
        {
            cout << "Error" << endl;
            system("pause");
            AdminMainMenu(Staff_Name);
        }
    }
    else
    {
        cout << "error!" << endl;
        system("pause");
        AdminMainMenu(Staff_Name);
    }
    cout << "The default number of active staffs in the system: " << foreground(Light_Red) << numberStaff << resetANSI() << endl;

    cout << "\nWhich attribute do you want to generate as report? " << endl;
    cout << "[1] Gender" << endl;
    cout << "[2] Position" << endl;
    cout << "[3] Age" << endl;
    cout << "[4] Back to Main Menu" << endl;
    cout << "Your choice: ";
    cin >> adminReport;

    if (adminReport == 1) {
        string StaffGenderNum1, StaffGenderNum2;

        //calculate number of staff based on gender
        //select from a common single column but display it as different column
        //in this case, select from staff gender column, but display as 2 column
        //1. Number of staff that is male
        //2. Number of staff that is female
        //if there's any record then 1 (true)
        //else it's 0 (false) and return 0

        string countGender_query = "Select SUM(case when Staff_Gender = 'M' then 1 else 0 end), SUM(case when Staff_Gender = 'F' then 1 else 0 end) FROM staff WHERE Active_Status = 'Active'";
        const char* cu1 = countGender_query.c_str();
        qstate = mysql_query(conn, cu1);
        if (!qstate)
        {
            res = mysql_store_result(conn);
            if (res->row_count == 1)
            {
                while (row = mysql_fetch_row(res))
                {
                    StaffGenderNum1 = row[0];
                    StaffGenderNum2 = row[1];
                }
            }
            else
            {
                cout << "Error" << endl;
                system("pause");
                AdminMainMenu(Staff_Name);
            }
        }
        else
        {
            cout << "error!" << endl;
        }

        system("cls");
        ShowTime();

        cout << "\nThe number of active staff based on gender: " << endl;
        cout << "Male = " << foreground(Light_Red) << StaffGenderNum1 << foreground(White) << endl;

        cout << "Female = " << foreground(Light_Red) << StaffGenderNum2 << endl << foreground(White) << endl;


        //convert the string data collected to integer data type
        int gender1 = convertToInt(StaffGenderNum1);
        int gender2 = convertToInt(StaffGenderNum2);

        cout << "The following graph showing the number of staff based on gender: " << endl;

        //array for int calculated number of staff based on gender
        int arrayGender[2] = { gender1, gender2 };

        //array used to print out the gender type
        string arrayGenderType[2] = { "Male", "Female" };

        //Display the graph
        cout << "\n" << endl;
        cout << background(Light_Red);
        cout << "****************************************************" << endl;
        cout << "|         Graph (GENDER VS NUMBER OF STAFF)        |" << endl;
        cout << "****************************************************" << endl;
        cout << background(Black);
        cout << endl;
        cout << setw(6) << "Gender" << right << " Number of Staff" << endl;
        cout << setw(8) << right << "/ \\" << endl;

        for (int i = 0; i < 2; i++)
        {
            cout << setw(6) << left << arrayGenderType[i] << left << "|";

            for (int j = 0; j < arrayGender[i]; j++)
            {
                cout << "*";
            }
            if (arrayGender[i] != 0) //showing the number of each gender in the graph
            {
                cout << " " << foreground(Yellow) << arrayGender[i] << foreground(White) << endl;
            }
            else
            {
                cout << endl;
            }
        }

        cout << setw(7) << right;
        int* maxNum;
        maxNum = max_element(arrayGender, arrayGender + 1);
        for (int i = 0; i < *maxNum + 5; i++)
        {
            cout << "-";
        }
        cout << ">" << endl;
        cout << "\n" << endl;
        goto confirmRpt1;

    confirmRpt1:
        char continueRpt;
        cout << "Do you want to continue viewing report? [Y/N]: ";
        cin >> continueRpt;

        if (continueRpt == 'y' || continueRpt == 'Y')
        {
            AdminReportMain();
        }
        else if (continueRpt == 'n' || continueRpt == 'N')
        {
            AdminReportMain();
        }
        else
        {
            cout << "Invalid choice!" << endl;
            goto confirmRpt1;
        }
    }

    else if (adminReport == 2) {
        string StaffPosition1, StaffPosition2, StaffPosition3;

        //calculate number of staff based on position
        //select a common single column but display it as different column
        //in this case, select from staff position column, but display as 3 columns
        //1. Number of staff that is doctor
        //2. Number of staff that is nurse
        //3. Number of staff that is staff
        //if there's any record then 1 (true)
        //else it's 0 (false) and return 0

        string countPos_query = "Select SUM(case when Staff_Position = 'Doctor' then 1 else 0 end), SUM(case when Staff_Position = 'Nurse' then 1 else 0 end), SUM(case when Staff_Position = 'Staff' then 1 else 0 end) FROM staff WHERE Active_Status = 'Active'";
        const char* cu1 = countPos_query.c_str();
        qstate = mysql_query(conn, cu1);
        if (!qstate)
        {
            res = mysql_store_result(conn);
            if (res->row_count == 1)
            {
                while (row = mysql_fetch_row(res))
                {
                    StaffPosition1 = row[0];
                    StaffPosition2 = row[1];
                    StaffPosition3 = row[2];
                }
            }
            else
            {
                cout << "Error" << endl;
            }
        }
        else
        {
            cout << "error!" << endl;
        }

        system("cls");
        ShowTime();

        cout << "\nThe number of active staff based on gender: " << endl;
        cout << "Doctor = " << foreground(Light_Red) << StaffPosition1 << foreground(White) << endl;
        cout << "Nurse = " << foreground(Light_Red) << StaffPosition2 << foreground(White) << endl;
        cout << "Staff = " << foreground(Light_Red) << StaffPosition3 << foreground(White) << endl << endl;


        //convert the string data collected to integer data type
        int pos1 = convertToInt(StaffPosition1);
        int pos2 = convertToInt(StaffPosition2);
        int pos3 = convertToInt(StaffPosition3);

        cout << "The following graph showing the number of staff based on gender: " << endl;

        //array for int calculated number of staff based on gender
        int arrayPosition[3] = { pos1, pos2, pos3 };

        //array used to print out the gender type
        string arrayPostType[3] = { "Doctor", "Nurse", "Staff" };

        //Display the graph
        cout << "\n" << endl;
        cout << background(Light_Red);
        cout << "******************************************************" << endl;
        cout << "|         Graph (POSITION VS NUMBER OF STAFF)        |" << endl;
        cout << "******************************************************" << endl;
        cout << background(Black);
        cout << endl;
        cout << setw(8) << "Position" << right << " Number of Staff" << endl;
        cout << setw(10) << right << "/ \\" << endl;

        for (int i = 0; i < 3; i++)
        {
            cout << setw(8) << left << arrayPostType[i] << left << "|";

            for (int j = 0; j < arrayPosition[i]; j++)
            {
                cout << "*";
            }
            if (arrayPosition[i] != 0) //showing the number of each gender in the graph
            {
                cout << " " << foreground(Yellow) << arrayPosition[i] << foreground(White) << endl;
            }
            else
            {
                cout << endl;
            }
        }

        cout << setw(8) << right;
        int* maxNum;
        maxNum = max_element(arrayPosition, arrayPosition + 1);
        for (int i = 0; i < *maxNum + 5; i++)
        {
            cout << "-";
        }
        cout << ">" << endl;
        cout << "\n" << endl;
        goto confirmRpt2;

    confirmRpt2:
        char continueRpt;
        cout << "Do you want to continue viewing report? [Y/N]: ";
        cin >> continueRpt;

        if (continueRpt == 'y' || continueRpt == 'Y')
        {
            AdminReportMain();
        }
        else if (continueRpt == 'n' || continueRpt == 'N')
        {
            AdminReportMain();
        }
        else
        {
            cout << "Invalid choice!" << endl;
            goto confirmRpt2;
        }
    }

    else if (adminReport == 3) {
        string StaffAge1, StaffAge2, StaffAge3, StaffAge4;

        //calculate 20-29
        string countAge1_query = "Select COUNT(Staff_ID) FROM staff WHERE Staff_Age >=20 AND Staff_Age < 30 AND Active_Status = 'Active'";
        const char* cu1 = countAge1_query.c_str();
        qstate = mysql_query(conn, cu1);
        if (!qstate)
        {
            res = mysql_store_result(conn);
            if (res->row_count == 1)
            {
                while (row = mysql_fetch_row(res))
                {
                    StaffAge1 = row[0];
                }
            }
            else
            {
                cout << "Error" << endl;
                system("pause");
                AdminMainMenu(Staff_Name);
            }
        }
        else
        {
            cout << "error!" << endl;
        }

        //calculate 30-39
        string countAge2_query = "Select COUNT(Staff_ID) FROM staff WHERE Staff_Age >=30 AND Staff_Age < 40 AND Active_Status = 'Active'";
        const char* cu2 = countAge2_query.c_str();
        qstate = mysql_query(conn, cu2);
        if (!qstate)
        {
            res = mysql_store_result(conn);
            if (res->row_count == 1)
            {
                while (row = mysql_fetch_row(res))
                {
                    StaffAge2 = row[0];
                }
            }
            else
            {
                cout << "Error" << endl;
                system("pause");
                AdminMainMenu(Staff_Name);
            }
        }
        else
        {
            cout << "error!" << endl;
            system("pause");
            AdminMainMenu(Staff_Name);
        }

        //calculate 40-49
        string countAge3_query = "Select COUNT(Staff_ID) FROM staff WHERE Staff_Age >=40 AND Staff_Age < 50 AND Active_Status = 'Active'";
        const char* cu3 = countAge3_query.c_str();
        qstate = mysql_query(conn, cu3);
        if (!qstate)
        {
            res = mysql_store_result(conn);
            if (res->row_count == 1)
            {
                while (row = mysql_fetch_row(res))
                {
                    StaffAge3 = row[0];
                }
            }
            else
            {
                cout << "Error" << endl;
                system("pause");
                AdminMainMenu(Staff_Name);
            }
        }
        else
        {
            cout << "error!" << endl;
            system("pause");
            AdminMainMenu(Staff_Name);
        }

        //calculate 50-59
        string countAge4_query = "Select COUNT(Staff_ID) FROM staff WHERE Staff_Age >=50 AND Staff_Age < 60 AND Active_Status = 'Active'";
        const char* cu4 = countAge4_query.c_str();
        qstate = mysql_query(conn, cu4);
        if (!qstate)
        {
            res = mysql_store_result(conn);
            if (res->row_count == 1)
            {
                while (row = mysql_fetch_row(res))
                {
                    StaffAge4 = row[0];
                }
            }
            else
            {
                cout << "Error" << endl;
                system("pause");
                AdminMainMenu(Staff_Name);
            }
        }
        else
        {
            cout << "error!" << endl;
            system("pause");
            AdminMainMenu(Staff_Name);
        }


        system("cls");
        ShowTime();

        cout << "\nThe number of active staff based on age: " << endl;
        cout << "20-29 = " << foreground(Light_Red) << StaffAge1 << foreground(White) << endl;
        cout << "30-39 = " << foreground(Light_Red) << StaffAge2 << foreground(White) << endl;
        foreground(White);
        cout << "40-49 = " << foreground(Light_Red) << StaffAge3 << foreground(White) << endl;
        foreground(White);
        cout << "50-59 = " << foreground(Light_Red) << StaffAge4 << foreground(White) << endl << endl;
        foreground(White);

        //convert the string data collected to integer data type
        int age1 = convertToInt(StaffAge1);
        int age2 = convertToInt(StaffAge2);
        int age3 = convertToInt(StaffAge3);
        int age4 = convertToInt(StaffAge4);

        cout << "The following graph showing the number of staff based on gender: " << endl;

        //array for int calculated number of staff based on gender
        int arrayAge[4] = { age1, age2, age3, age4 };

        //array used to print out the gender type
        string arrayAgeType[4] = { "20-29", "30-39", "40-49", "50-59" };

        //Display the graph
        cout << "\n" << endl;
        cout << background(Light_Red) << foreground(White);
        cout << "*************************************************" << endl;
        cout << "|         Graph (AGE VS NUMBER OF STAFF)        |" << endl;
        cout << "*************************************************" << endl;
        cout << background(Black) << resetANSI();
        cout << endl;
        cout << setw(5) << "Age" << right << " Number of Staff" << endl;
        cout << setw(7) << right << "/ \\" << endl;

        for (int i = 0; i < 4; i++)
        {
            cout << setw(5) << left << arrayAgeType[i] << left << "|";

            for (int j = 0; j < arrayAge[i]; j++)
            {
                cout << "*";
            }
            if (arrayAge[i] != 0) //showing the number of each gender in the graph
            {
                cout << " " << foreground(Yellow) << arrayAge[i] << foreground(White) << endl;
            }
            else
            {
                cout << endl;
            }
        }

        cout << setw(7) << right;
        int* maxNum;
        maxNum = max_element(arrayAge, arrayAge + 1);
        for (int i = 0; i < *maxNum + 4; i++)
        {
            cout << "-";
        }
        cout << ">" << endl;
        cout << "\n" << endl;
        goto confirmRpt3;

    confirmRpt3:
        char continueRpt;
        cout << "Do you want to continue viewing report? [Y/N]: ";
        cin >> continueRpt;

        if (continueRpt == 'y' || continueRpt == 'Y')
        {
            AdminReportMain();
        }
        else if (continueRpt == 'n' || continueRpt == 'N')
        {
            AdminReportMain();
        }
        else
        {
            cout << "Invalid choice!" << endl;
            goto confirmRpt3;
        }
    }

    else if (adminReport == 4)
    {
        system("cls");
        AdminMainMenu(Staff_Name);
    }

    else
    {
        cout << "Error in report generation!" << endl;
        system("cls");
        AdminReportMain();
    }
}


//staff login page
void StaffLogin()
{
    string Staff_Password;
    system("cls");
    cout << background(Cyan) << foreground(Black);
    cout << "----------------" << endl;
    cout << " LOGIN AS STAFF " << endl;
    cout << "----------------" << endl;
    cout << background(Black) << foreground(White) << resetANSI();
    cout << endl;

    cout << "Enter Staff ID: ";
    cin >> Staff_ID;
    cout << "Enter Password: ";
    char ch;
    while ((ch = _getch()) != 13)
    {
        Staff_Password += ch;
        cout << "*";
    }

    string checkUser_query = "SELECT Staff_ID, Staff_Name FROM staff WHERE Staff_ID = '" + Staff_ID + "' AND Staff_Password = sha1('" + Staff_Password + "') AND Active_Status = 'Active' ";
    const char* cu = checkUser_query.c_str();
    qstate = mysql_query(conn, cu);
    if (!qstate)
    {
        res = mysql_store_result(conn);
        if (res->row_count == 1)
        {
            while (row = mysql_fetch_row(res))
            {
                Staff_ID = row[0];
                Staff_Name = row[1];
            }
            system("cls");
            StaffMainMenu(Staff_ID, Staff_Name);
        }
        else
        {
            char c;
            cout << "\nInvalid username or password. Want to try again? (Y/N): ";
            cin >> c;
            if (c == 'y' || c == 'Y')
                StaffLogin();
            else
                MainLogin();
        }
    }
    else
        cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
}

//staff menu page after successful login
void StaffMainMenu(string id, string name)
{
    char StaffMainChoice;
    cout << foreground(Cyan) << background(Black);
    cout << "-----------------" << endl;
    cout << " STAFF MAIN MENU " << endl;
    cout << "-----------------" << endl;
    cout << background(Black) << foreground(White) << resetANSI();

    cout << "Welcome, staff " << background(Black) << foreground(Cyan) << name << background(Black) << foreground(White) << "!" << endl;
    cout << resetANSI() << endl;

    cout << "[1] Control Menu" << endl;
    cout << "[2] Recent Donation Records" << endl;
    cout << "[3] Report Generation" << endl; //haven't done for this function
    cout << "[4] Account Information" << endl;
    cout << "[5] Back to main menu" << endl;
    cout << "\nYour choice (1 - 5): ";
    cin >> StaffMainChoice;

    switch (StaffMainChoice)
    {
    case '1':
        StaffControlMain();
        break;

    case '2':
        RecentDonation();
        break;

    case '3':
        system("cls");
        StaffReport();
        break;

    case '4':
        system("cls");
        StaffAccount(id);
        break;

    case '5':
        system("CLS");
        main();

    default:
        cout << "Error! Invalid choice! " << endl;
        system("pause");
        StaffMainMenu(id, name);
    }
}

void StaffControlMain()
{
    char StaffControl;
    system("cls");
    cout << background(Cyan) << foreground(Black);
    cout << "--------------------" << endl;
    cout << " STAFF CONTROL MENU " << endl;
    cout << "--------------------" << endl;
    cout << background(Black) << foreground(White) << resetANSI();
    cout << "Welcome, staff! What would you like to do?" << endl;
    cout << endl;

    cout << "[A] Add Record" << endl;
    cout << "[B] Delete Record" << endl;
    cout << "[C] Update Record" << endl;
    cout << "[D] Search Record" << endl;
    cout << "[M] Main Menu" << endl;

    cout << "\nPlease enter your choice (A, B, C, D, M): ";
    cin >> StaffControl;

    switch (StaffControl)
    {
    case 'A':
    case 'a':
        StaffControlAdd();
        break;

    case 'B':
    case 'b':
        system("cls");
        StaffControlDelete();
        break;

    case 'C':
    case 'c':
        system("cls");
        StaffControlUpdate();
        break;

    case 'D':
    case 'd':
        system("cls");
        StaffControlSearch();
        break;

    case 'M':
    case 'm':
        system("cls");
        StaffMainMenu(Staff_ID, Staff_Name);
        break;


    default:
        cout << "Invalid choice!" << endl;
        StaffControlMain();
    }
}

//staff own account information
void StaffAccount(string id)
{
    system("cls");
    ShowTime();
    cout << foreground(Black) << background(Cyan) << endl;
    cout << "===================================" << endl;
    cout << "       ACCOUNT INFORMATION         " << endl;
    cout << "===================================" << endl;
    cout << background(Black) << foreground(White) << resetANSI();
    string search_query = "SELECT Staff_ID, Staff_Name, Staff_Gender, Staff_Age, Staff_Address, Staff_Telno, Staff_Position FROM staff WHERE Staff_ID = '" + id + "' AND Active_Status = 'Active'";
    const char* q = search_query.c_str();
    qstate = mysql_query(conn, q);
    if (!qstate)
    {
        res = mysql_store_result(conn);
        while (row = mysql_fetch_row(res))
        {
            cout << "Staff ID: " << row[0] << endl;
            cout << "Name: " << row[1] << endl;
            cout << "Gender: " << row[2] << endl;
            cout << "Age: " << row[3] << endl;
            cout << "Address: " << row[4] << endl;
            cout << "Phone: " << row[5] << endl;
            cout << "Position: " << row[6] << endl;
        }
        system("pause");
        system("cls");
        StaffMainMenu(id, Staff_Name);
    }
    else
    {
        cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
        system("pause");
        system("cls");
        StaffMainMenu(id, Staff_Name);
    }
}


//add module for staff
void StaffControlAdd()
{
    char StaffAdd;
    system("cls");
    cout << background(Cyan) << foreground(Black);
    cout << "-----------------" << endl;
    cout << " ADD RECORD MENU " << endl;
    cout << "-----------------" << endl;
    cout << background(Black) << foreground(White) << resetANSI();
    cout << "[D] Add Record of Donors" << endl;
    cout << "[H] Add Record of Hospital" << endl;
    cout << "[B] Add Record of Blood Stock" << endl;
    cout << "[S] Add Record of Donation" << endl;
    cout << "[M] Main Menu" << endl;

    cout << "\nPlease enter your choice (D, H, B, S, M): ";
    cin >> StaffAdd;

    switch (StaffAdd) {
    case 'H':
    case 'h':
        AddHospitalMenu();
        break;

    case 'D':
    case 'd':
        AddDonorMenu();
        break;

    case 'B':
    case 'b':
        AddBloodMenu();
        break;

    case 'S':
    case 's':
        AddDonationMenu();
        break;

    case 'M':
    case 'm':
        StaffControlMain();
        break;

    default:
        cout << "Invalid choice!" << endl;
        system("pause");
        StaffControlAdd();
        break;
    }
}

void AddDonationMenu()
{
    system("cls");
    string Donation_ID, Donation_Date, Record_ID, Hospital_ID, Donor_ID;
    int Donation_Volume;
    char AddDonation;
    cout << foreground(Cyan);
    cout << "------------------------" << endl;
    cout << " ADD RECORDS - DONATION " << endl;
    cout << "------------------------" << endl;
    cout << background(Black) << foreground(White) << resetANSI();
    cout << "Enter new records: " << endl;
    cout << "Donation ID(nonnegative integer digit only): ";
    int IDNum;
    cin >> IDNum;

    string DtID;
    if (IDNum >= 0 && IDNum < 10)
    {
        DtID.append("DT000");
        DtID.append(to_string(IDNum));
    }
    else if (IDNum >= 10 && IDNum < 100)
    {

        DtID.append("DT00");
        DtID.append(to_string(IDNum));
    }
    else if (IDNum >= 100 && IDNum < 1000)
    {
        DtID.append("DT0");
        DtID.append(to_string(IDNum));
    }
    else if (IDNum >= 1000 && IDNum < 10000)
    {
        DtID.append("DT");
        DtID.append(to_string(IDNum));
    }
    else
    {
        cout << "Invalid Input! Non-negative Integer (0-9) is used! Please try again!";
        system("pause");
        system("cls");
        StaffControlAdd();
    }

    Donation_ID = DtID;

    cout << "Donation Date: ";
    cin.ignore(1, '\n');
    getline(cin, Donation_Date);
    cout << "Donation Volume: ";
    cin >> Donation_Volume;
    cout << "Record_ID(nonnegative integer digit only): ";
    int IDNum2;
    cin >> IDNum2;

    string RcID;
    if (IDNum2 >= 0 && IDNum2 < 10)
    {
        RcID.append("RC000");
        RcID.append(to_string(IDNum2));
    }
    else if (IDNum2 >= 10 && IDNum2 < 100)
    {

        RcID.append("RC00");
        RcID.append(to_string(IDNum2));
    }
    else if (IDNum2 >= 100 && IDNum2 < 1000)
    {
        RcID.append("RC0");
        RcID.append(to_string(IDNum2));
    }
    else if (IDNum2 >= 1000 && IDNum2 < 10000)
    {
        RcID.append("RC");
        RcID.append(to_string(IDNum2));
    }
    else
    {
        cout << "Invalid Input! Non-negative Integer (0-9) is used! Please try again!";
        system("pause");
        system("cls");
        StaffControlAdd();
    }
    Record_ID = RcID;

    cout << "Donor_ID(nonnegative integer digit only):" << endl;
    int IDNum3;
    cin >> IDNum3;

    string DnID;
    if (IDNum3 >= 0 && IDNum3 < 10)
    {
        DnID.append("DN000");
        DnID.append(to_string(IDNum3));
    }
    else if (IDNum3 >= 10 && IDNum3 < 100)
    {

        DnID.append("DN00");
        DnID.append(to_string(IDNum2));
    }
    else if (IDNum3 >= 100 && IDNum3 < 1000)
    {
        DnID.append("DN0");
        DnID.append(to_string(IDNum2));
    }
    else if (IDNum3 >= 1000 && IDNum3 < 10000)
    {
        DnID.append("DN");
        DnID.append(to_string(IDNum2));
    }
    else
    {
        cout << "Invalid Input! Please try again!";
        system("pause");
        system("cls");
        StaffControlMain();
    }
    Donor_ID = DnID;

    cout << "Hospital_ID (nonnegative integer digit only): ";
    int IDNum4;
    cin >> IDNum4;

    string HsID;
    if (IDNum4 >= 0 && IDNum4 < 10)
    {
        HsID.append("HS000");
        HsID.append(to_string(IDNum4));
    }
    else if (IDNum4 >= 10 && IDNum4 < 100)
    {

        HsID.append("HS00");
        HsID.append(to_string(IDNum4));
    }
    else if (IDNum4 >= 100 && IDNum4 < 1000)
    {
        HsID.append("DN0");
        HsID.append(to_string(IDNum4));
    }
    else if (IDNum4 >= 1000 && IDNum4 < 10000)
    {
        HsID.append("DN");
        HsID.append(to_string(IDNum4));
    }
    else
    {
        cout << "Invalid Input! Non-negative Integer (0-9) is used! Please try again!";
        system("pause");
        system("cls");
        StaffControlAdd();
    }
    Hospital_ID = HsID;

    string Status = "Completed";

    string insert_query = "INSERT INTO donor_record (Record_ID, Hospital_ID, Donor_ID) values('" + Record_ID + "', '" + Hospital_ID + "', '" + Donor_ID + "')";
    const char* q = insert_query.c_str();
    qstate = mysql_query(conn, q);
    if (!qstate)
    {
        string insert_query = "INSERT INTO blood_donation (Donation_ID, Donation_Date, Donation_Volume, Record_ID, Status) values('" + Donation_ID + "', '" + Donation_Date + "',  '" + to_string(Donation_Volume) + "'  , '" + Record_ID + "', '" + Status + "')";
        const char* q = insert_query.c_str();
        qstate = mysql_query(conn, q);
        if (!qstate)
        {
            cout << endl << "A donation is successful added in database." << endl;
        }
        else
        {
            cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
        }
        cout << endl << "A donation is successful added in database." << endl;
    }
    else
    {
        cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
    }

    do
    {
        cout << "Do you want to continue adding records? [Y/N]: ";
        cin >> AddDonation;
        if (AddDonation == 'y' || AddDonation == 'Y')
        {
            AddHospitalMenu();
        }
        else if (AddDonation == 'n' || AddDonation == 'N')
        {
            StaffControlAdd();
        }
    } while (AddDonation == 'y' || AddDonation == 'Y' || AddDonation == 'n' || AddDonation == 'N');
}

void AddHospitalMenu()
{
    string Hospital_ID, Hospital_Name, Hospital_Street, Hospital_State, Hospital_City;
    char AddHospital;
    system("cls");
    cout << foreground(Cyan);
    cout << "------------------------" << endl;
    cout << " ADD RECORDS - HOSPITAL " << endl;
    cout << "------------------------" << endl;
    cout << background(Black) << foreground(White) << resetANSI();
    cout << "Enter new records: " << endl;
    cout << "Hospital ID(nonnegative integer digit only): ";
    int IDNum4;
    cin >> IDNum4;

    string HsID;
    if (IDNum4 >= 0 && IDNum4 < 10)
    {
        HsID.append("HS000");
        HsID.append(to_string(IDNum4));
    }
    else if (IDNum4 >= 10 && IDNum4 < 100)
    {

        HsID.append("HS00");
        HsID.append(to_string(IDNum4));
    }
    else if (IDNum4 >= 100 && IDNum4 < 1000)
    {
        HsID.append("DN0");
        HsID.append(to_string(IDNum4));
    }
    else if (IDNum4 >= 1000 && IDNum4 < 10000)
    {
        HsID.append("DN");
        HsID.append(to_string(IDNum4));
    }
    else
    {
        cout << "Invalid Input! Non-negative Integer (0-9) is used! Please try again!";
        system("pause");
        system("cls");
        StaffControlAdd();
    }
    Hospital_ID = HsID;

    cout << "Name: ";
    cin.ignore(1, '\n');
    getline(cin, Hospital_Name);
    cout << "Street: ";
    getline(cin, Hospital_Street);
    cout << "City: ";
    getline(cin, Hospital_City);
    cout << "State: ";
    getline(cin, Hospital_State);

    string Availability = "Available";

    string insert_query = "INSERT INTO hospital (Hospital_ID, Hospital_Name, Hospital_Street, Hospital_State, Hospital_City, Availability) values('" + Hospital_ID + "', '" + Hospital_Name + "', '" + Hospital_Street + "', '" + Hospital_State + "', '" + Hospital_City + "', '" + Availability + "' )";

    const char* q = insert_query.c_str();
    qstate = mysql_query(conn, q);
    if (!qstate)
    {
        cout << endl << "Hospital is successful added in database." << endl;
    }
    else
    {
        cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
    }

    do
    {
        cout << "Do you want to continue adding records? [Y/N]: ";
        cin >> AddHospital;
        if (AddHospital == 'y' || AddHospital == 'Y')
        {
            AddHospitalMenu();
        }
        else if (AddHospital == 'n' || AddHospital == 'N')
        {
            StaffControlAdd();
        }
    } while (AddHospital == 'y' || AddHospital == 'Y' || AddHospital == 'n' || AddHospital == 'N');
}

void AddDonorMenu()
{
    system("cls");
    string Donor_ID, Donor_Name, Donor_Gender, Donor_DOB, Donor_Address, Donor_BloodType, Donor_TelNo, Donor_Password;
    int Donor_Age;
    double Donor_Height, Donor_Weight;

    int d_year, d_month, d_day;
    string year, month, day, DOB;

    char AddDonor;
    cout << foreground(Cyan);
    cout << "---------------------" << endl;
    cout << " ADD RECORDS - DONOR " << endl;
    cout << "---------------------" << endl;
    cout << background(Black) << foreground(White) << resetANSI();
    cout << "Enter new records: " << endl;
    cout << "Donor ID(nonnegative integer digit only): ";
    int IDNum3;
    cin >> IDNum3;

    string DnID;
    if (IDNum3 >= 0 && IDNum3 < 10)
    {
        DnID.append("DN000");
        DnID.append(to_string(IDNum3));
    }
    else if (IDNum3 >= 10 && IDNum3 < 100)
    {

        DnID.append("DN00");
        DnID.append(to_string(IDNum3));
    }
    else if (IDNum3 >= 100 && IDNum3 < 1000)
    {
        DnID.append("DN0");
        DnID.append(to_string(IDNum3));
    }
    else if (IDNum3 >= 1000 && IDNum3 < 10000)
    {
        DnID.append("DN");
        DnID.append(to_string(IDNum3));
    }
    else
    {
        cout << "Invalid Input! Non-negative Integer (0-9) is used! Please try again!";
        system("pause");
        system("cls");
        StaffControlAdd();
    }
    Donor_ID = DnID;
    cout << "Name: ";
    cin.ignore(1, '\n');
    getline(cin, Donor_Name);
    cout << "Gender: ";
    cin >> Donor_Gender;
    cout << "Date of Birth (YYYY MM DD): ";
    cin >> d_year >> d_month >> d_day;

    //DOB details: convert int to string
    year = to_string(d_year);
    month = to_string(d_month);
    day = to_string(d_day);

    //DOB details: make multiple string into single string
    DOB.append(year);
    DOB.append("-");
    DOB.append(month);
    DOB.append("-");
    DOB.append(day);

    //store the copied single string into Donor_DOB to insert into database later
    Donor_DOB = DOB;

    //calculate the age
    Donor_Age = calculateAge(d_year, d_month, d_day);

    cout << "Address: ";
    cin.ignore(1, '\n');
    getline(cin, Donor_Address);
    cout << "Blood Type: ";
    cin >> Donor_BloodType;
    cout << "Height: ";
    cin >> Donor_Height;
    cout << "Weight: ";
    cin >> Donor_Weight;
    cout << "Telephone Number: ";
    cin >> Donor_TelNo;
    cout << "Password: ";
    char ch;
    while ((ch = _getch()) != 13) // 13 is the ASCII number for Enter
    {
        Donor_Password += ch;
        cout << "*";
    }
    string Active_Status = "Active";
    string insert_query = "INSERT INTO donor (Donor_ID, Donor_Name, Donor_Gender, Donor_Age, Donor_DOB, Donor_Address, Donor_BloodType, Donor_Height, Donor_Weight, Donor_TelNo, Donor_Password, Active_Status) VALUES ('" + Donor_ID + "', '" + Donor_Name + "', '" + Donor_Gender + "', '" + to_string(Donor_Age) + "' , '" + Donor_DOB + "', '" + Donor_Address + "', '" + Donor_BloodType + "',  '" + to_string(Donor_Height) + "' ,  '" + to_string(Donor_Weight) + "', '" + Donor_TelNo + "',  sha1('" + Donor_Password + "'), '" + Active_Status + "')";
    const char* q = insert_query.c_str();
    qstate = mysql_query(conn, q);
    if (!qstate)
    {
        cout << endl << "Donor is successful added in database." << endl;
    }
    else
    {
        cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
    }

    do
    {
        cout << "Do you want to continue adding records? [Y/N]: ";
        cin >> AddDonor;
        if (AddDonor == 'y' || AddDonor == 'Y')
        {
            AddDonorMenu();
        }
        else if (AddDonor == 'n' || AddDonor == 'N')
        {
            StaffControlAdd();
        }
    } while (AddDonor == 'y' || AddDonor == 'Y' || AddDonor == 'n' || AddDonor == 'N');
}

void AddBloodMenu()
{
    system("cls");
    string Stock_ID, Stock_Category, Staff_ID, Donation_ID;
    int Stock_Volume, Stock_Quantity, Total_Stock_Volume;

    char AddBlood;
    cout << foreground(Cyan);
    cout << "---------------------------" << endl;
    cout << " ADD RECORDS - BLOOD STOCK " << endl;
    cout << "---------------------------" << endl;
    cout << background(Black) << foreground(White) << resetANSI();
    cout << "Enter new records: " << endl;
    cout << "Blood Stock ID (nonnegative integer digit only): ";
    int IDNum5;
    cin >> IDNum5;

    string BlID;
    if (IDNum5 >= 0 && IDNum5 < 10)
    {
        BlID.append("BL000");
        BlID.append(to_string(IDNum5));
    }
    else if (IDNum5 >= 10 && IDNum5 < 100)
    {

        BlID.append("BL00");
        BlID.append(to_string(IDNum5));
    }
    else if (IDNum5 >= 100 && IDNum5 < 1000)
    {
        BlID.append("BL0");
        BlID.append(to_string(IDNum5));
    }
    else if (IDNum5 >= 1000 && IDNum5 < 10000)
    {
        BlID.append("BL");
        BlID.append(to_string(IDNum5));
    }
    else
    {
        cout << "Invalid Input! Non-negative Integer (0-9) is used! Please try again!";
        system("pause");
        system("cls");
        StaffControlAdd();
    }
    Stock_ID = BlID;
    cin.ignore(1, '\n');
    cout << "Blood Stock Category: ";
    getline(cin, Stock_Category);
    cout << "Blood Stock Volume: ";
    cin >> Stock_Volume;
    cout << "Blood Stock Quantity: ";
    cin >> Stock_Quantity;
    cout << "Staff_ID: ";
    int IDNum;
    cin >> IDNum;

    string StID;
    if (IDNum >= 0 && IDNum < 10)
    {
        StID.append("ST000");
        StID.append(to_string(IDNum));
    }
    else if (IDNum >= 10 && IDNum < 100)
    {

        StID.append("ST00");
        StID.append(to_string(IDNum));
    }
    else if (IDNum >= 100 && IDNum < 1000)
    {
        StID.append("ST0");
        StID.append(to_string(IDNum));
    }
    else if (IDNum >= 1000 && IDNum < 10000)
    {
        StID.append("ST");
        StID.append(to_string(IDNum));
    }
    else
    {
        cout << "Invalid Input! Non-negative Integer (0-9) is used! Please try again!";
        system("pause");
        system("cls");
        StaffControlAdd();
    }

    Staff_ID = StID;

    cout << "Donation_ID: ";
    int IDNum6;
    cin >> IDNum6;

    string DtID;
    if (IDNum6 >= 0 && IDNum6 < 10)
    {
        DtID.append("DT000");
        DtID.append(to_string(IDNum6));
    }
    else if (IDNum6 >= 10 && IDNum6 < 100)
    {

        DtID.append("DT00");
        DtID.append(to_string(IDNum6));
    }
    else if (IDNum6 >= 100 && IDNum6 < 1000)
    {
        DtID.append("DT0");
        DtID.append(to_string(IDNum6));
    }
    else if (IDNum6 >= 1000 && IDNum6 < 10000)
    {
        DtID.append("DT");
        DtID.append(to_string(IDNum6));
    }
    else
    {
        cout << "Invalid Input! Non-negative Integer (0-9) is used! Please try again!";
        system("pause");
        system("cls");
        StaffControlAdd();
    }

    Donation_ID = DtID;

    Total_Stock_Volume = Stock_Volume * Stock_Quantity;
    string Availability = "Available";

    string insert_query = "INSERT INTO blood_stock (Stock_ID, Stock_Category, Stock_Volume, Stock_Quantity, Total_Stock_Volume, Staff_ID, Donation_ID, Status) VALUES('" + Stock_ID + "', '" + Stock_Category + "', '" + to_string(Stock_Volume) + "', '" + to_string(Stock_Quantity) + "','" + to_string(Total_Stock_Volume) + "' ,'" + Staff_ID + "', '" + Donation_ID + "', '" + Availability + "')";
    const char* q = insert_query.c_str();
    qstate = mysql_query(conn, q);
    if (!qstate)
    {
        cout << endl << "A blood stock is successful added in database." << endl;
    }
    else
    {
        cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
    }

    do
    {
        cout << "Do you want to continue adding records? [Y/N]: ";
        cin >> AddBlood;
        if (AddBlood == 'y' || AddBlood == 'Y')
        {
            AddBloodMenu();
        }
        else if (AddBlood == 'n' || AddBlood == 'N')
        {
            StaffControlAdd();
        }
    } while (AddBlood == 'y' || AddBlood == 'Y' || AddBlood == 'n' || AddBlood == 'N');
}


//delete module for staff
void StaffControlDelete()
{
    char StaffDelete;
    system("cls");
    cout << background(Cyan) << foreground(Black);
    cout << "--------------------" << endl;
    cout << " DELETE RECORD MENU " << endl;
    cout << "--------------------" << endl;
    cout << background(Black) << foreground(White) << resetANSI();
    cout << "[D] Delete Record of Donors" << endl;
    cout << "[H] Delete Record of Hospital" << endl;
    cout << "[B] Delete Record of Blood Stock" << endl;
    cout << "[S] Delete Record of Donation" << endl;
    cout << "[M] Main Menu" << endl;

    cout << "\nPlease enter your choice (D, H, B, S, M): ";
    cin >> StaffDelete;

    switch (StaffDelete) {
    case 'H':
    case 'h':
        DeleteHospital();
        break;

    case 'D':
    case 'd':
        DeleteDonor();
        break;

    case 'B':
    case 'b':
        DeleteBlood();
        break;

    case 'S':
    case 's':
        DeleteDonation();
        break;

    case 'M':
    case 'm':
        StaffControlMain();
        break;

    default:
        cout << "Invalid choice!" << endl;
        system("pause");
        StaffControlDelete();
        break;
    }
}

void DeleteHospital()
{
    string Hospital_ID;
    char confirmDel, continueDel;
    system("cls");
    cout << foreground(Cyan);
    cout << "--------------------------" << endl;
    cout << " DELETE RECORD - HOSPITAL " << endl;
    cout << "--------------------------" << endl;
    cout << background(Black) << foreground(White) << resetANSI();
    cout << "\nEnter Hospital ID to search: ";
    cin >> Hospital_ID;

    cout << "\nHere's the record found: \n" << endl;
    string searchDel_query = "SELECT Hospital_ID, Hospital_Name, Hospital_Street, Hospital_State, Hospital_City FROM hospital WHERE Hospital_ID = '" + Hospital_ID + "' AND Availability = 'Available' ";
    const char* q = searchDel_query.c_str();
    qstate = mysql_query(conn, q);
    if (!qstate)
    {
        res = mysql_store_result(conn);
        while (row = mysql_fetch_row(res))
        {
            cout << "Hospital ID: " << row[0] << endl;
            cout << "Name: " << row[1] << endl;
            cout << "Street: " << row[2] << endl;
            cout << "City: " << row[3] << endl;
            cout << "State: " << row[4] << endl;
        }
    }
    else
    {
        cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
        system("pause");
        DeleteHospital();
    }

    cout << "Are you confirm to delete this record [Y/N]: ";
    cin >> confirmDel;

    if (confirmDel == 'Y' || confirmDel == 'y')
    {
        //real time delete environment doesn't allow
        //string delete_query = "DELETE FROM hospital WHERE Hospital_ID = '" + Hospital_ID + "'";

        string update_query = "UPDATE hospital SET Availability = 'Inavailable' WHERE Hospital_ID = '" + Hospital_ID + "' ";
        const char* q = update_query.c_str();
        qstate = mysql_query(conn, q);
        cout << "Successfully delete a hospital! " << endl;
        cout << "Do you want to continue deleting record?[Y/N]: ";
        cin >> continueDel;
        if (continueDel == 'y' || continueDel == 'Y')
            DeleteHospital();
        else if (continueDel == 'n' || continueDel == 'N')
            StaffControlDelete();
    }
    else
    {
        cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
        system("pause");
        StaffControlDelete();
    }
}

void DeleteDonor()
{
    string Donor_ID;
    char confirmDel, continueDel;
    system("cls");
    cout << foreground(Cyan);
    cout << "-----------------------" << endl;
    cout << " DELETE RECORD - DONOR " << endl;
    cout << "-----------------------" << endl;
    cout << background(Black) << foreground(White) << resetANSI();
    cout << "\nEnter Donor ID to search: ";
    cin >> Donor_ID;

    cout << "\nHere's the record found: \n" << endl;
    string searchDel_query = "SELECT Donor_ID, Donor_Name, Donor_Gender, Donor_Age, Donor_DOB, Donor_Address, Donor_BloodType, Donor_Height, Donor_Weight, Donor_TelNo FROM donor WHERE Donor_ID = '" + Donor_ID + "' AND Active_Status = 'Active'";
    const char* q = searchDel_query.c_str();
    qstate = mysql_query(conn, q);
    if (!qstate)
    {
        res = mysql_store_result(conn);
        while (row = mysql_fetch_row(res))
        {
            cout << "Donor ID: " << row[0] << endl;
            cout << "Name: " << row[1] << endl;
            cout << "Gender: " << row[2] << endl;
            cout << "Age: " << row[3] << endl;
            cout << "Date of Birth: " << row[4] << endl;
            cout << "Address: " << row[5] << endl;
            cout << "Blood Type: " << row[6] << endl;
            cout << "Height: " << row[7] << endl;
            cout << "Weight: " << row[8] << endl;
            cout << "Telephone number: " << row[9] << endl;
        }
    }
    else
    {
        cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
        system("pause");
        DeleteDonor();
    }

    cout << "Are you confirm to delete this record [Y/N]: ";
    cin >> confirmDel;

    if (confirmDel == 'Y' || confirmDel == 'y')
    {
        //string delete_query = "DELETE FROM donor where Donor_ID = '" + Donor_ID + "'";
        string update_query = "UPDATE donor SET Active_Status = 'Inactive' WHERE Donor_ID = '" + Donor_ID + "' ";
        const char* q = update_query.c_str();
        qstate = mysql_query(conn, q);
        cout << "Successfully delete a donor! " << endl;
        cout << "Do you want to continue deleting record?[Y/N]: ";
        cin >> continueDel;
        if (continueDel == 'y' || continueDel == 'Y')
            DeleteDonor();
        else if (continueDel == 'n' || continueDel == 'N')
            StaffControlDelete();
    }
    else
    {
        cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
        system("pause");
        StaffControlDelete();
    }
}

void DeleteBlood()
{
    string Stock_ID;
    char confirmDel, continueDel;
    system("cls");
    cout << foreground(Cyan);
    cout << "-----------------------------" << endl;
    cout << " DELETE RECORD - BLOOD STOCK " << endl;
    cout << "-----------------------------" << endl;
    cout << background(Black) << foreground(White) << resetANSI();
    cout << "\nEnter Blood Stock ID to search: ";
    cin >> Stock_ID;

    cout << "\nHere's the record found: \n" << endl;
    string search_query = "SELECT Stock_ID, Stock_Category, Stock_Volume, Stock_Quantity, Total_Stock_Volume, Staff_ID, Donation_ID FROM blood_stock WHERE Stock_ID = '" + Stock_ID + "' AND Status = 'Available'";
    const char* q = search_query.c_str();
    qstate = mysql_query(conn, q);
    if (!qstate)
    {
        res = mysql_store_result(conn);
        while (row = mysql_fetch_row(res))
        {
            cout << "Stock ID: " << row[0] << endl;
            cout << "Category: " << row[1] << endl;
            cout << "Volume: " << row[2] << endl;
            cout << "Quantity: " << row[3] << endl;
            cout << "Total Volume: " << row[4] << endl;
            cout << "Staff ID: " << row[5] << endl;
            cout << "Donation ID: " << row[6] << endl;
        }
    }
    else
    {
        cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
        system("pause");
        DeleteBlood();
    }

    cout << "Are you confirm to delete this record [Y/N]: ";
    cin >> confirmDel;

    if (confirmDel == 'Y' || confirmDel == 'y')
    {
        //string delete_query = "DELETE FROM blood_stock where Stock_ID = '" + Stock_ID + "'";
        //const char* q = delete_query.c_str();

        string update_query = "UPDATE blood_stock SET Status = 'Inavailable' WHERE Stock_ID = '" + Stock_ID + "' ";
        const char* q = update_query.c_str();
        qstate = mysql_query(conn, q);
        cout << "Successfully delete a blood stock! " << endl;
        cout << "Do you want to continue deleting record?[Y/N]: ";
        cin >> continueDel;
        if (continueDel == 'y' || continueDel == 'Y')
            DeleteBlood();
        else if (continueDel == 'n' || continueDel == 'N')
            StaffControlDelete();
    }
    else
    {
        cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
        system("pause");
        StaffControlDelete();
    }
}

void DeleteDonation()
{
    system("cls");
    string Donation_ID;
    char confirmDel, continueDel;
    cout << foreground(Cyan);
    cout << "--------------------------" << endl;
    cout << " DELETE RECORD - DONATION " << endl;
    cout << "--------------------------" << endl;
    cout << background(Black) << foreground(White) << resetANSI();
    cout << "\nEnter Donation ID to search: ";
    cin >> Donation_ID;

    cout << "\nHere's the record found: \n" << endl;
    string search_query = "SELECT t.Donation_ID, t.Donation_Date, t.Donation_Volume, r.Record_ID, h.Hospital_ID, d.Donor_ID FROM blood_donation t, donor_record r, hospital h, donor d WHERE t.Donation_ID = '" + Donation_ID + "' AND t.Record_ID = r.Record_ID AND r.Hospital_ID = h.Hospital_ID AND r.Donor_ID = d.Donor_ID AND t.Status = 'Completed' ";
    const char* q = search_query.c_str();
    qstate = mysql_query(conn, q);
    if (!qstate)
    {
        res = mysql_store_result(conn);
        while (row = mysql_fetch_row(res))
        {
            cout << "Donation ID: " << row[0] << endl;
            cout << "Date: " << row[1] << endl;
            cout << "Volume: " << row[2] << endl;
            cout << "Record ID: " << row[3] << endl;
            cout << "Hospital ID: " << row[4] << endl;
            cout << "Donor ID: " << row[5] << endl;
        }
    }
    else
    {
        cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
        system("pause");
        DeleteDonation();
    }

    cout << "Are you confirm to delete this record [Y/N]: ";
    cin >> confirmDel;

    if (confirmDel == 'Y' || confirmDel == 'y')
    {
        //string delete_query = "DELETE FROM blood_donation where Donation_ID = '" + Donation_ID + "'";
        //const char* q = delete_query.c_str();

        string update_query = "UPDATE blood_donation SET Status = 'Unavailable' WHERE Donation_ID = '" + Donation_ID + "' ";
        const char* q = update_query.c_str();
        qstate = mysql_query(conn, q);
        cout << "Successfully delete a blood donation record! " << endl;
        cout << "Do you want to continue deleting record?[Y/N]: ";
        cin >> continueDel;
        if (continueDel == 'y' || continueDel == 'Y')
            DeleteDonation();
        else if (continueDel == 'n' || continueDel == 'N')
            StaffControlDelete();
    }
    else
    {
        cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
        system("pause");
        StaffControlDelete();
    }
}


//update module for staff
void StaffControlUpdate()
{
    char StaffUpdate;
    system("cls");
    do
    {
        cout << background(Blue) << foreground(White);
        cout << "--------------------" << endl;
        cout << " UPDATE RECORD MENU " << endl;
        cout << "--------------------" << endl;
        cout << background(Black) << foreground(White) << resetANSI();
        cout << "[D] Update Record of Donors" << endl;
        cout << "[H] Update Record of Hospital" << endl;
        cout << "[B] Update Record of Blood Stock" << endl;
        cout << "[S] Update Record of Donation" << endl;
        cout << "[M] Main Menu" << endl;

        cout << "\nPlease enter your choice (D, H, B, S, M): ";
        cin >> StaffUpdate;

        switch (StaffUpdate) {
        case 'H':
        case 'h':
            UpdateHospital();
            break;

        case 'D':
        case 'd':
            UpdateDonor();
            break;

        case 'B':
        case 'b':
            UpdateBlood();
            break;

        case 'S':
        case 's':
            UpdateDonation();
            break;

        case 'M':
        case 'm':
            StaffControlMain();
            break;

        default:
            cout << "Invalid choice!" << endl;
            system("pause");
            break;
        }
    } while (StaffUpdate != 'D' || StaffUpdate != 'D' || StaffUpdate != 'b' || StaffUpdate != 'B' || StaffUpdate != 's' || StaffUpdate != 'S' || StaffUpdate != 'h' || StaffUpdate != 'H' || StaffUpdate != 'M' || StaffUpdate != 'm');
    StaffControlUpdate();
}

void UpdateHospital()
{
    string Hospital_ID, Hospital_Name, Hospital_Street, Hospital_City, Hospital_State;
    char UpdChoice, confirmUpd, continueUpd;
    system("cls");
    cout << foreground(Cyan);
    cout << "--------------------------" << endl;
    cout << " UPDATE RECORD - HOSPITAL " << endl;
    cout << "--------------------------" << endl;
    cout << background(Black) << foreground(White) << resetANSI();
    cout << "\nEnter Hospital ID to search (Format: HS****): ";
    cin >> Hospital_ID;

    cout << "\nHere's the record found: \n" << endl;
    string searchUpd_query = "SELECT Hospital_ID, Hospital_Name, Hospital_Street, Hospital_State, Hospital_City FROM hospital WHERE Hospital_ID = '" + Hospital_ID + "' AND Availability = 'Available' ";
    const char* q = searchUpd_query.c_str();
    qstate = mysql_query(conn, q);
    if (!qstate)
    {
        res = mysql_store_result(conn);
        while (row = mysql_fetch_row(res))
        {
            cout << "Hospital ID: " << row[0] << endl;
            cout << "Name: " << row[1] << endl;
            cout << "Street: " << row[2] << endl;
            cout << "City: " << row[3] << endl;
            cout << "State: " << row[4] << endl;
        }

        cout << "Are you confirm to update information? [Y/N]: ";
        cin >> confirmUpd;

        if (confirmUpd == 'Y' || confirmUpd == 'y')
        {
            cout << "----------------------------" << endl;
            cout << "  Updation of Information " << endl;
            cout << "----------------------------" << endl;
            cout << "\nEnter information that you want to update: " << endl;
            cout << "[1] Name " << endl;
            cout << "[2] Street " << endl;
            cout << "[3] City " << endl;
            cout << "[4] State " << endl;
            cout << "\nYour choice >> ";
            cin >> UpdChoice;

            if (UpdChoice == '1') {
                cout << "Name: ";
                cin.ignore(1, '\n');
                getline(cin, Hospital_Name);

                string update_query = "UPDATE hospital SET Hospital_Name = '" + Hospital_Name + "' WHERE Hospital_ID = '" + Hospital_ID + "' AND Availability = 'Available'";
                const char* q = update_query.c_str();
                qstate = mysql_query(conn, q);
                cout << "\n Successfully Updated!" << endl;
                cout << "Do you want to continue update record? [Y/N]: ";
                cin >> continueUpd;

                if (continueUpd == 'Y' || continueUpd == 'y')
                    UpdateHospital();
                else
                    StaffControlUpdate();
            }

            else if (UpdChoice == '2') {
                cout << "Street: ";
                cin.ignore(1, '\n');
                getline(cin, Hospital_Street);

                string update_query = "UPDATE hospital SET Hospital_Street = '" + Hospital_Street + "' WHERE Hospital_ID = '" + Hospital_ID + "' AND Availability = 'Available'";
                const char* q = update_query.c_str();
                qstate = mysql_query(conn, q);
                cout << "\n Successfully Updated!" << endl;
                cout << "Do you want to continue update record? [Y/N]: ";
                cin >> continueUpd;

                if (continueUpd == 'Y' || continueUpd == 'y')
                    UpdateHospital();
                else
                    StaffControlUpdate();
            }

            else if (UpdChoice == '3') {
                cout << "City: ";
                cin.ignore(1, '\n');
                getline(cin, Hospital_City);

                string update_query = "UPDATE hospital SET Hospital_City = '" + Hospital_City + "' WHERE Hospital_ID = '" + Hospital_ID + "' AND Availability = 'Available'";
                const char* q = update_query.c_str();
                qstate = mysql_query(conn, q);
                cout << "\n Successfully Updated!" << endl;
                cout << "Do you want to continue update record? [Y/N]: ";
                cin >> continueUpd;

                if (continueUpd == 'Y' || continueUpd == 'y')
                    UpdateHospital();
                else
                    StaffControlUpdate();
            }

            else if (UpdChoice == '4') {
                cout << "State: ";
                cin.ignore(1, '\n');
                getline(cin, Hospital_State);

                string update_query = "UPDATE hospital SET Hospital_State = '" + Hospital_State + "'WHERE Hospital_ID = '" + Hospital_ID + "' AND Availability = 'Available'";
                const char* q = update_query.c_str();
                qstate = mysql_query(conn, q);
                cout << "Do you want to continue update record? [Y/N]: ";
                cin >> continueUpd;

                if (continueUpd == 'Y' || continueUpd == 'y')
                    UpdateHospital();
                else
                    StaffControlUpdate();
            }

            else {
                cout << "Error in updation! " << endl;
                system("pause");
                UpdateHospital();
            }
        }
        else
        {
            StaffControlUpdate();
        }
    }
    else
    {
        cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
        system("pause");
        UpdateHospital();
    }
}

void UpdateDonor()
{
    string Donor_ID, Donor_Name, Donor_Gender, Donor_DOB, Donor_Address, Donor_BloodType, Donor_TelNo, Donor_Password;
    int Donor_Age;
    double Donor_Height, Donor_Weight;

    char UpdChoice, confirmUpd, continueUpd;
    system("cls");
    cout << foreground(Cyan);
    cout << "-----------------------" << endl;
    cout << " UPDATE RECORD - DONOR " << endl;
    cout << "-----------------------" << endl;
    cout << background(Black) << foreground(White) << resetANSI();
    cout << "\nEnter Donor ID to search (Format: DN****): ";
    cin >> Donor_ID;

    cout << "\nHere's the record found: \n" << endl;
    string searchUpd_query = "SELECT Donor_ID, Donor_Name, Donor_Gender, Donor_Age, Donor_DOB, Donor_Address, Donor_BloodType, Donor_Height, Donor_Weight, Donor_TelNo FROM donor WHERE Donor_ID = '" + Donor_ID + "' AND Active_Status = 'Active'";
    const char* q = searchUpd_query.c_str();
    qstate = mysql_query(conn, q);
    if (!qstate)
    {
        res = mysql_store_result(conn);
        while (row = mysql_fetch_row(res))
        {
            cout << "Donor ID: " << row[0] << endl;
            cout << "Name: " << row[1] << endl;
            cout << "Gender: " << row[2] << endl;
            cout << "Age: " << row[3] << endl;
            cout << "Date of Birth: " << row[4] << endl;
            cout << "Address: " << row[5] << endl;
            cout << "Blood Type: " << row[6] << endl;
            cout << "Height: " << row[7] << endl;
            cout << "Weight: " << row[8] << endl;
            cout << "Phone: " << row[9] << endl;
        }

        cout << "Are you confirm to update information? [Y/N]: ";
        cin >> confirmUpd;

        if (confirmUpd == 'Y' || confirmUpd == 'y')
        {
            cout << "----------------------------" << endl;
            cout << "  Updation of Information " << endl;
            cout << "----------------------------" << endl;
            cout << "\nEnter information that you want to update: " << endl;
            cout << "[1] Name " << endl;
            cout << "[2] Gender " << endl;
            cout << "[3] Date of Birth: " << endl;
            cout << "[4] Address " << endl;
            cout << "[5] Blood Type " << endl;
            cout << "[6] Height " << endl;
            cout << "[7] Weight " << endl;
            cout << "[8] Phone " << endl;
            cout << "[9] Password " << endl;
            cout << "\nYour choice >> ";
            cin >> UpdChoice;

            if (UpdChoice == '1') {
                cout << "Name: ";
                cin.ignore(1, '\n');
                getline(cin, Donor_Name);

                string update_query = "UPDATE donor SET Donor_Name = '" + Donor_Name + "' WHERE  Donor_ID = '" + Donor_ID + "'AND Active_Status = 'Active'";
                const char* q = update_query.c_str();
                qstate = mysql_query(conn, q);
                cout << "\n Successfully Updated!" << endl;
                cout << "Do you want to continue update record? [Y/N]: ";
                cin >> continueUpd;

                if (continueUpd == 'Y' || continueUpd == 'y')
                    UpdateDonor();
                else
                    StaffControlUpdate();
            }

            else if (UpdChoice == '2') {
                cout << "Gender: ";
                cin.ignore(1, '\n');
                getline(cin, Donor_Gender);

                string update_query = "UPDATE donor SET Donor_Gender = '" + Donor_Gender + "' WHERE  Donor_ID = '" + Donor_ID + "'AND Active_Status = 'Active'";
                const char* q = update_query.c_str();
                qstate = mysql_query(conn, q);
                cout << "\n Successfully Updated!" << endl;
                cout << "Do you want to continue update record? [Y/N]: ";
                cin >> continueUpd;

                if (continueUpd == 'Y' || continueUpd == 'y')
                    UpdateDonor();
                else
                    StaffControlUpdate();
            }

            else if (UpdChoice == '3') {

                int d_year, d_month, d_day;
                string year, month, day, DOB;

                cout << "Date of Birth [YYYY MM DD]: ";
                cin >> d_year >> d_month >> d_day;

                //DOB details: convert int to string
                year = to_string(d_year);
                month = to_string(d_month);
                day = to_string(d_day);

                //DOB details: make multiple string into single string
                DOB.append(year);
                DOB.append("-");
                DOB.append(month);
                DOB.append("-");
                DOB.append(day);

                //store the copied single string into Donor_DOB to insert into database later
                Donor_DOB = DOB;

                //calculate the age
                Donor_Age = calculateAge(d_year, d_month, d_day);

                string update_query = "UPDATE donor SET Donor_DOB = '" + Donor_DOB + "', Donor_Age = '" + to_string(Donor_Age) + "' WHERE Donor_ID = '" + Donor_ID + "'AND Active_Status = 'Active'";
                const char* q = update_query.c_str();
                qstate = mysql_query(conn, q);
                cout << "\n Successfully Updated!" << endl;
                cout << "Do you want to continue update record? [Y/N]: ";
                cin >> continueUpd;

                if (continueUpd == 'Y' || continueUpd == 'y')
                    UpdateDonor();
                else
                    StaffControlUpdate();
            }

            else if (UpdChoice == '4') {
                cout << "Address: ";
                cin >> Donor_Address;

                string update_query = "UPDATE donor SET Donor_Address = '" + Donor_Address + "' WHERE Donor_ID = '" + Donor_ID + "'AND Active_Status = 'Active'";
                const char* q = update_query.c_str();
                qstate = mysql_query(conn, q);
                cout << "\n Successfully Updated!" << endl;
                cout << "Do you want to continue update record? [Y/N]: ";
                cin >> continueUpd;

                if (continueUpd == 'Y' || continueUpd == 'y')
                    UpdateDonor();
                else
                    StaffControlUpdate();
            }

            else if (UpdChoice == '5') {
                cout << "Blood Type: ";
                cin >> Donor_BloodType;

                string update_query = "UPDATE donor SET Donor_BloodType = '" + Donor_BloodType + "' WHERE Donor_ID = '" + Donor_ID + "'AND Active_Status = 'Active'";
                const char* q = update_query.c_str();
                qstate = mysql_query(conn, q);
                cout << "\n Successfully Updated!" << endl;
                cout << "Do you want to continue update record? [Y/N]: ";
                cin >> continueUpd;

                if (continueUpd == 'Y' || continueUpd == 'y')
                    UpdateDonor();
                else
                    StaffControlUpdate();
            }

            else if (UpdChoice == '6') {
                cout << "Height: ";
                cin >> Donor_Height;

                string update_query = "UPDATE donor SET Donor_Height = '" + to_string(Donor_Height) + "' WHERE Donor_ID = '" + Donor_ID + "'AND Active_Status = 'Active'";
                const char* q = update_query.c_str();
                qstate = mysql_query(conn, q);
                cout << "\n Successfully Updated!" << endl;
                cout << "Do you want to continue update record? [Y/N]: ";
                cin >> continueUpd;

                if (continueUpd == 'Y' || continueUpd == 'y')
                    UpdateDonor();
                else
                    StaffControlUpdate();
            }

            else if (UpdChoice == '7') {
                cout << "Weight: ";
                cin >> Donor_Weight;

                string update_query = "UPDATE donor SET Donor_Weight = '" + to_string(Donor_Weight) + "' WHERE Donor_ID = '" + Donor_ID + "' AND Active_Status = 'Active'";
                const char* q = update_query.c_str();
                qstate = mysql_query(conn, q);
                cout << "\n Successfully Updated!" << endl;
                cout << "Do you want to continue update record? [Y/N]: ";
                cin >> continueUpd;

                if (continueUpd == 'Y' || continueUpd == 'y')
                    UpdateDonor();
                else
                    StaffControlUpdate();
            }

            else if (UpdChoice == '8') {
                cout << "Phone: ";
                cin >> Donor_TelNo;

                string update_query = "UPDATE donor SET Donor_TelNo = '" + Donor_TelNo + "' WHERE Donor_ID = '" + Donor_ID + "'AND Active_Status = 'Active'";
                const char* q = update_query.c_str();
                qstate = mysql_query(conn, q);
                cout << "\n Successfully Updated!" << endl;
                cout << "Do you want to continue update record? [Y/N]: ";
                cin >> continueUpd;

                if (continueUpd == 'Y' || continueUpd == 'y')
                    UpdateDonor();
                else
                    StaffControlUpdate();
            }

            else if (UpdChoice == '9') {
                cout << "Password: ";
                char ch;
                while ((ch = _getch()) != 13)
                {
                    Donor_Password += ch;
                    cout << "*";
                }

                string update_query = "UPDATE donor SET Donor_Password = sha1('" + Donor_Password + "') WHERE Donor_ID = '" + Donor_ID + "'";
                const char* q = update_query.c_str();
                qstate = mysql_query(conn, q);
                cout << "\n Successfully Updated!" << endl;
                cout << "Do you want to continue update record? [Y/N]: ";
                cin >> continueUpd;

                if (continueUpd == 'Y' || continueUpd == 'y')
                    UpdateDonor();
                else
                    StaffControlUpdate();
            }

            else {
                cout << "Error in updation! " << endl;
                system("pause");
                UpdateDonor();
            }
        }

        else
        {
            StaffControlUpdate();
        }
    }
    else
    {
        cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
        system("pause");
        UpdateDonor();
    }
}

void UpdateDonation()
{
    string Donation_ID, Donation_Date, Record_ID, Hospital_ID;
    int Donation_Volume;
    char UpdChoice, confirmUpd, continueUpd;
    system("cls");
    cout << foreground(Cyan);
    cout << "--------------------------" << endl;
    cout << " UPDATE RECORD - DONATION " << endl;
    cout << "--------------------------" << endl;
    cout << background(Black) << foreground(White) << resetANSI();
    cout << "\nEnter Donation ID to search (Format: DT****): ";
    cin >> Donation_ID;

    cout << "\nHere's the record found: \n" << endl;
    string searchUpd_query = "SELECT r.Record_ID, t.Donation_ID, d.Donor_ID, t.Donation_Date, t.Donation_Volume, h.Hospital_ID FROM blood_donation t, donor_record r, hospital h, donor d WHERE t.Donation_ID = '" + Donation_ID + "' AND r.Record_ID = t.Record_ID AND d.Donor_ID = r.Donor_ID AND h.Hospital_ID = r.Hospital_ID AND Status = 'Completed'";
    const char* q = searchUpd_query.c_str();
    qstate = mysql_query(conn, q);
    if (!qstate)
    {
        res = mysql_store_result(conn);
        while (row = mysql_fetch_row(res))
        {
            cout << "Record ID: " << row[0] << endl;
            cout << "Donation ID: " << row[1] << endl;
            cout << "Donor ID: " << row[2] << endl;
            cout << "Donation Date: " << row[3] << endl;
            cout << "Donation Volume: " << row[4] << endl;
            cout << "Hospital ID: " << row[5] << endl;

        }

        cout << "Are you confirm to update information? [Y/N]: ";
        cin >> confirmUpd;

        if (confirmUpd == 'Y' || confirmUpd == 'y')
        {
            cout << "----------------------------" << endl;
            cout << "  Updation of Information " << endl;
            cout << "----------------------------" << endl;
            cout << "\nEnter information that you want to update: " << endl;
            cout << "[1] Record ID " << endl;
            cout << "[2] Donor ID " << endl;
            cout << "[3] Donation Date " << endl;
            cout << "[4] Donation Volume " << endl;
            cout << "[5] Hospital ID" << endl;

            cout << "\nYour choice >> ";
            cin >> UpdChoice;

            if (UpdChoice == '1') {
                cout << "Record ID: ";
                int IDNum2;
                cin >> IDNum2;

                string RcID;
                if (IDNum2 >= 0 && IDNum2 < 10)
                {
                    RcID.append("RC000");
                    RcID.append(to_string(IDNum2));
                }
                else if (IDNum2 >= 10 && IDNum2 < 100)
                {

                    RcID.append("RC00");
                    RcID.append(to_string(IDNum2));
                }
                else if (IDNum2 >= 100 && IDNum2 < 1000)
                {
                    RcID.append("RC0");
                    RcID.append(to_string(IDNum2));
                }
                else if (IDNum2 >= 1000 && IDNum2 < 10000)
                {
                    RcID.append("RC");
                    RcID.append(to_string(IDNum2));
                }
                else
                {
                    cout << "Invalid Input! Only Numeric Integer! Please try again!";
                    system("pause");
                    system("cls");
                    StaffControlUpdate();
                }
                Record_ID = RcID;

                string update_query = "UPDATE blood_donation SET Record_ID = '" + Record_ID + "' WHERE Donation_ID = '" + Donation_ID + "' AND Status = 'Completed'";
                const char* q = update_query.c_str();
                qstate = mysql_query(conn, q);

                cout << "\n Successfully Updated!" << endl;
                cout << "Do you want to continue update record? [Y/N]: ";
                cin >> continueUpd;

                if (continueUpd == 'Y' || continueUpd == 'y')
                    UpdateDonation();
                else
                    StaffControlUpdate();
            }

            else if (UpdChoice == '2') {
                cout << "Record ID: ";
                cin >> Record_ID;

                cout << "Donor ID: ";
                int IDNum3;
                cin >> IDNum3;

                string DnID;
                if (IDNum3 >= 0 && IDNum3 < 10)
                {
                    DnID.append("DN000");
                    DnID.append(to_string(IDNum3));
                }
                else if (IDNum3 >= 10 && IDNum3 < 100)
                {

                    DnID.append("DN00");
                    DnID.append(to_string(IDNum3));
                }
                else if (IDNum3 >= 100 && IDNum3 < 1000)
                {
                    DnID.append("DN0");
                    DnID.append(to_string(IDNum3));
                }
                else if (IDNum3 >= 1000 && IDNum3 < 10000)
                {
                    DnID.append("DN");
                    DnID.append(to_string(IDNum3));
                }
                else
                {
                    cout << "Invalid Input! Only Numeric Integer! Please try again!";
                    system("pause");
                    system("cls");
                    StaffControlUpdate();
                }
                Donor_ID = DnID;

                string update_query = "UPDATE donor_record SET Donor_ID = '" + Donor_ID + "' WHERE Record_ID = '" + Record_ID + "' AND Status = 'Completed'";
                const char* q = update_query.c_str();
                qstate = mysql_query(conn, q);
                cout << "\n Successfully Updated!" << endl;
                cout << "Do you want to continue update record? [Y/N]: ";
                cin >> continueUpd;

                if (continueUpd == 'Y' || continueUpd == 'y')
                    UpdateDonation();
                else
                    StaffControlUpdate();
            }

            else if (UpdChoice == '3') {
                cout << "Donation Date: ";
                cin.ignore(1, '\n');
                getline(cin, Donation_Date);

                string update_query = "UPDATE blood_donation SET Donation_Date = '" + Donation_Date + "' WHERE Donation_ID = '" + Donation_ID + "' AND Status = 'Completed'";
                const char* q = update_query.c_str();
                qstate = mysql_query(conn, q);
                cout << "\n Successfully Updated!" << endl;
                system("pause");
                cout << "Do you want to continue update record? [Y/N]: ";
                cin >> continueUpd;

                if (continueUpd == 'Y' || continueUpd == 'y')
                    UpdateDonation();
                else
                    StaffControlUpdate();
            }

            else if (UpdChoice == '4') {

                cout << "Donation Volume: ";
                cin >> Donation_Volume;

                string update_query = "UPDATE blood_donation SET Donation_Volume = '" + to_string(Donation_Volume) + "' WHERE Donation_ID = '" + Donation_ID + "' AND Status = 'Completed'";
                const char* q = update_query.c_str();
                qstate = mysql_query(conn, q);
                cout << "\n Successfully Updated!" << endl;
                cout << "Do you want to continue update record? [Y/N]: ";
                cin >> continueUpd;

                if (continueUpd == 'Y' || continueUpd == 'y')
                    UpdateDonation();
                else
                    StaffControlUpdate();
            }

            else if (UpdChoice == '5') {
                cout << "Record ID: ";
                cin >> Record_ID;

                cout << "Hospital ID: ";
                int IDNum4;
                cin >> IDNum4;

                string HsID;
                if (IDNum4 >= 0 && IDNum4 < 10)
                {
                    HsID.append("HS000");
                    HsID.append(to_string(IDNum4));
                }
                else if (IDNum4 >= 10 && IDNum4 < 100)
                {

                    HsID.append("HS00");
                    HsID.append(to_string(IDNum4));
                }
                else if (IDNum4 >= 100 && IDNum4 < 1000)
                {
                    HsID.append("DN0");
                    HsID.append(to_string(IDNum4));
                }
                else if (IDNum4 >= 1000 && IDNum4 < 10000)
                {
                    HsID.append("DN");
                    HsID.append(to_string(IDNum4));
                }
                else
                {
                    cout << "Invalid Input! Only Numeric Integer! Please try again!";
                    system("pause");
                    system("cls");
                    StaffControlUpdate();
                }
                Hospital_ID = HsID;

                string update_query = "UPDATE donor_record SET Hospital_ID = '" + Hospital_ID + "' WHERE Record_ID = '" + Record_ID + "'";
                const char* q = update_query.c_str();
                qstate = mysql_query(conn, q);
                cout << "\n Successfully Updated!" << endl;
                cout << "Do you want to continue update record? [Y/N]: ";
                cin >> continueUpd;

                if (continueUpd == 'Y' || continueUpd == 'y')
                    UpdateDonation();
                else
                    StaffControlUpdate();
            }

            else {
                cout << "Error in updation! " << endl;
                system("pause");
                UpdateDonation();
            }
        }
        else
        {
            StaffControlUpdate();
        }

    }
    else
    {
        cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
        system("pause");
        UpdateDonation();
    }
}

void UpdateBlood()
{
    string Stock_ID, Stock_Category, Staff_ID, Donation_ID;
    int Stock_Volume, Stock_Quantity, Total_Stock_Volume;

    system("cls");
    char UpdChoice, confirmUpd, continueUpd;
    cout << foreground(Cyan);
    cout << "-----------------------------" << endl;
    cout << " UPDATE RECORD - BLOOD STOCK " << endl;
    cout << "-----------------------------" << endl;
    cout << background(Black) << foreground(White) << resetANSI();
    cout << "\nEnter Blood Stock ID to search (Format: BL****): ";
    cin >> Stock_ID;

    cout << "\nHere's the record found: \n" << endl;
    string searchUpd_query = "SELECT Stock_ID, Stock_Category, Stock_Volume, Stock_Quantity, Stock_Volume, Total_Stock_Volume, Staff_ID, Donation_ID FROM blood_stock WHERE Stock_ID = '" + Stock_ID + "' AND Status = 'Available'";
    const char* q = searchUpd_query.c_str();
    qstate = mysql_query(conn, q);
    if (!qstate)
    {
        res = mysql_store_result(conn);
        while (row = mysql_fetch_row(res))
        {
            cout << "Stock ID: " << row[0] << endl;
            cout << "Category: " << row[1] << endl;
            cout << "Volume: " << row[2] << endl;
            cout << "Quantity: " << row[3] << endl;
            cout << "Total Volume: " << row[5] << endl;
            cout << "Staff ID: " << row[6] << endl;
            cout << "Donation ID: " << row[7] << endl;
        }

        cout << "\nAre you confirm to update the record? [Y/N]: ";
        cin >> confirmUpd;

        if (confirmUpd == 'Y' || confirmUpd == 'y')
        {
            cout << "----------------------------" << endl;
            cout << "  Updation of Information " << endl;
            cout << "----------------------------" << endl;
            cout << "\nEnter information that you want to update: " << endl;
            cout << "[1] Category " << endl;
            cout << "[2] Volume " << endl;
            cout << "[3] Quantity " << endl;
            cout << "[4] Staff ID " << endl;
            cout << "[5] Donation ID " << endl;

            cout << "\nYour choice >> ";
            cin >> UpdChoice;

            if (UpdChoice == '1') {
                cout << "Category: ";
                cin.ignore(1, '\n');
                getline(cin, Stock_Category);

                string update_query = "UPDATE blood_stock SET Stock_Category = '" + Stock_Category + "' WHERE  Stock_ID = '" + Stock_ID + "'";
                const char* q = update_query.c_str();
                qstate = mysql_query(conn, q);
                cout << "\n Successfully Updated!" << endl;
                system("pause");
                UpdateBlood();
            }

            else if (UpdChoice == '2') {

                cout << "Volume: ";
                cin >> Stock_Volume;

                string Quantity;
                string checkUser_query = "SELECT Stock_Quantity FROM blood_stock WHERE Stock_ID = '" + Stock_ID + "'";
                const char* cu = checkUser_query.c_str();
                qstate = mysql_query(conn, cu);
                if (!qstate)
                {
                    res = mysql_store_result(conn);
                    if (res->row_count == 1)
                    {
                        while (row = mysql_fetch_row(res))
                        {
                            Quantity = row[0];
                        }
                    }
                    else
                    {
                        cout << "Error in counting!" << endl;
                        system("pause");
                        system("cls");
                        StaffControlUpdate();
                    }
                    int Stock_Quantity = convertToInt(Quantity);
                    int Total_Stock_Volume = Stock_Volume * Stock_Quantity;
                    string update_query = "UPDATE blood_stock SET Stock_Volume = '" + to_string(Stock_Volume) + "', Total_Stock_Volume= '" + to_string(Total_Stock_Volume) + "' WHERE  Stock_ID = '" + Stock_ID + "'";
                    const char* q = update_query.c_str();
                    qstate = mysql_query(conn, q);
                    cout << "\n Successfully Updated!" << endl;
                    system("pause");
                    UpdateBlood();
                }
                else
                {
                    cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
                    system("pause");
                }
            }

            else if (UpdChoice == '3') {
                cout << "Quantity: ";
                cin >> Stock_Quantity;

                string Volume;
                string checkUser_query = "SELECT Stock_Volume FROM blood_stock WHERE Stock_ID = '" + Stock_ID + "'";
                const char* cu = checkUser_query.c_str();
                qstate = mysql_query(conn, cu);
                if (!qstate)
                {
                    res = mysql_store_result(conn);
                    if (res->row_count == 1)
                    {
                        while (row = mysql_fetch_row(res))
                        {
                            Volume = row[0];
                        }
                    }
                    else
                    {
                        cout << "Error in counting!" << endl;
                        system("pause");
                        system("cls");
                        StaffControlUpdate();
                    }
                    int Stock_Volume = convertToInt(Volume);
                    int Total_Stock_Volume = Stock_Volume * Stock_Quantity;
                    string update_query = "UPDATE blood_stock SET Stock_Quantity = '" + to_string(Stock_Quantity) + "', Total_Stock_Volume = '" + to_string(Total_Stock_Volume) + "' WHERE  Stock_ID = '" + Stock_ID + "'";
                    const char* q = update_query.c_str();
                    qstate = mysql_query(conn, q);
                    cout << "\n Successfully Updated!" << endl;
                    system("pause");
                    UpdateBlood();
                }
                else
                {
                    cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
                    system("pause");
                }
            }


            else if (UpdChoice == '4') {
                cout << "Staff_ID: ";
                int IDNum;
                cin >> IDNum;

                string StID;
                if (IDNum >= 0 && IDNum < 10)
                {
                    StID.append("SD000");
                    StID.append(to_string(IDNum));
                }
                else if (IDNum >= 10 && IDNum < 100)
                {

                    StID.append("SD00");
                    StID.append(to_string(IDNum));
                }
                else if (IDNum >= 100 && IDNum < 1000)
                {
                    StID.append("SD0");
                    StID.append(to_string(IDNum));
                }
                else if (IDNum >= 1000 && IDNum < 10000)
                {
                    StID.append("SD");
                    StID.append(to_string(IDNum));
                }
                else
                {
                    cout << "Invalid Input! Please try again!";
                    system("pause");
                    system("cls");
                    AdminControlMain();
                }

                Staff_ID = StID;

                string update_query = "UPDATE blood_stock SET Staff_ID = '" + Staff_ID + "' WHERE  Stock_ID = '" + Stock_ID + "'";
                const char* q = update_query.c_str();
                qstate = mysql_query(conn, q);
                cout << "\n Successfully Updated!" << endl;
                cout << "Do you want to continue update record? [Y/N]: ";
                cin >> continueUpd;

                if (continueUpd == 'Y' || continueUpd == 'y')
                    UpdateBlood();
                else
                    StaffControlUpdate();
            }

            else if (UpdChoice == '5') {
                cout << "Donation_ID: ";
                int IDNum;
                cin >> IDNum;

                string DtID;
                if (IDNum >= 0 && IDNum < 10)
                {
                    DtID.append("DT000");
                    DtID.append(to_string(IDNum));
                }
                else if (IDNum >= 10 && IDNum < 100)
                {

                    DtID.append("DT00");
                    DtID.append(to_string(IDNum));
                }
                else if (IDNum >= 100 && IDNum < 1000)
                {
                    DtID.append("DT0");
                    DtID.append(to_string(IDNum));
                }
                else if (IDNum >= 1000 && IDNum < 10000)
                {
                    DtID.append("DT");
                    DtID.append(to_string(IDNum));
                }
                else
                {
                    cout << "Invalid Input! Please try again!";
                    system("pause");
                    system("cls");
                    StaffControlMain();
                }

                Donation_ID = DtID;

                string update_query = "UPDATE blood_stock SET Donation_ID = '" + Donation_ID + "' WHERE  Stock_ID = '" + Stock_ID + "'";
                const char* q = update_query.c_str();
                qstate = mysql_query(conn, q);
                cout << "\n Successfully Updated!" << endl;
                cout << "Do you want to continue update record? [Y/N]: ";
                cin >> continueUpd;

                if (continueUpd == 'Y' || continueUpd == 'y')
                    UpdateBlood();
                else
                    StaffControlUpdate();
            }

            else
            {
                cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
                system("pause");
                UpdateBlood();
            }
        }
        else
        {
            StaffControlUpdate();
        }
    }
    else
    {
        cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
        system("pause");
        UpdateBlood();
    }
}


//searching module for staff
void StaffControlSearch()
{
    char StaffSearch;
    system("cls");
    cout << background(Cyan) << foreground(Black);
    cout << "--------------------" << endl;
    cout << " SEARCH RECORD MENU " << endl;
    cout << "--------------------" << endl;
    cout << background(Black) << foreground(White) << resetANSI();
    cout << "[D] Search Record of Donors" << endl;
    cout << "[H] Search Record of Hospital" << endl;
    cout << "[B] Search Record of Blood Stock" << endl;
    cout << "[S] Search Record of Donation" << endl;
    cout << "[M] Main Menu" << endl;

    cout << "\nPlease enter your choice (D, H, B, S, M): ";
    cin >> StaffSearch;

    switch (StaffSearch) {
    case 'H':
    case 'h':
        SearchHospital();
        break;

    case 'D':
    case 'd':
        SearchDonor();
        break;

    case 'B':
    case 'b':
        SearchBlood();
        break;

    case 'S':
    case 's':
        SearchDonation();
        break;

    case 'M':
    case 'm':
        StaffControlMain();
        break;

    default:
        cout << "Invalid choice!" << endl;
        system("pause");
        StaffControlSearch();
        break;
    }
}

void SearchHospital()
{
    string Hospital_ID, Hospital_Name, Hospital_Street, Hospital_City, Hospital_State;
    char SearchHosp;
    int searchHospChoice;
    system("cls");
    cout << foreground(Cyan);
    cout << "--------------------------" << endl;
    cout << " SEARCH RECORD - HOSPITAL " << endl;
    cout << "--------------------------" << endl;
    cout << background(Black) << foreground(White) << resetANSI();
    cout << "Please select the attribute you want to search: " << endl;
    cout << "[1] Hospital ID " << endl;
    cout << "[2] Name " << endl;
    cout << "[3] Street " << endl;
    cout << "[4] City " << endl;
    cout << "[5] State " << endl;
    cout << "[6] Back to Main Menu " << endl;
    cout << "\nYour Choice >> ";

    cin >> searchHospChoice;

    if (searchHospChoice == 1)
    {
        cout << "\nEnter Hospital ID to search (Format: HS****): ";
        cin >> Hospital_ID;
        cout << "\nHere's the record found: \n" << endl;
        string search_query = "SELECT Hospital_ID, Hospital_Name, Hospital_Street, Hospital_State, Hospital_City FROM hospital WHERE Hospital_ID = '" + Hospital_ID + "' AND Availability = 'Available' ";
        const char* q = search_query.c_str();
        qstate = mysql_query(conn, q);
        if (!qstate)
        {
            res = mysql_store_result(conn);
            while (row = mysql_fetch_row(res))
            {
                cout << "Hospital ID: " << row[0] << endl;
                cout << "Name: " << row[1] << endl;
                cout << "Street: " << row[2] << endl;
                cout << "City: " << row[3] << endl;
                cout << "State: " << row[4] << endl;
            }
            cout << endl << "Do you want to search other hospital?[Y/N]: ";
            cin >> SearchHosp;
            if (SearchHosp == 'y' || SearchHosp == 'Y')
                SearchHospital();
            else if (SearchHosp == 'n' || SearchHosp == 'N')
                StaffControlMain();
        }
        else
        {
            cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
            system("pause");
            StaffControlSearch();
        }
    }

    else if (searchHospChoice == 2)
    {
        cout << "\nEnter Hospital Name to search: ";
        cin.ignore(1, '\n');
        getline(cin, Hospital_Name);
        cout << "\nHere's the record found: \n" << endl;
        string search_query = "SELECT Hospital_ID, Hospital_Name, Hospital_Street, Hospital_State, Hospital_City FROM hospital WHERE Hospital_Name LIKE '%" + Hospital_Name + "%' AND Availability = 'Available' ";
        const char* q = search_query.c_str();
        qstate = mysql_query(conn, q);
        if (!qstate)
        {
            res = mysql_store_result(conn);
            while (row = mysql_fetch_row(res))
            {
                cout << "Hospital ID: " << row[0] << endl;
                cout << "Name: " << row[1] << endl;
                cout << "Street: " << row[2] << endl;
                cout << "City: " << row[3] << endl;
                cout << "State: " << row[4] << endl;
                cout << endl;

            }
            cout << endl << "Do you want to search other hospital?[Y/N]: ";
            cin >> SearchHosp;
            if (SearchHosp == 'y' || SearchHosp == 'Y')
                SearchHospital();
            else if (SearchHosp == 'n' || SearchHosp == 'N')
                StaffControlSearch();
        }
        else
        {
            cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
            system("pause");
            StaffControlSearch();
        }
    }

    else if (searchHospChoice == 3)
    {
        cout << "\nEnter Hospital Street to search: ";
        cin.ignore(1, '\n');
        getline(cin, Hospital_Street);
        cout << "\nHere's the record found: \n" << endl;
        string search_query = "SELECT Hospital_ID, Hospital_Name, Hospital_Street, Hospital_State, Hospital_City FROM hospital WHERE Hospital_Street LIKE '%" + Hospital_Street + "%' AND Availability = 'Available' ";
        const char* q = search_query.c_str();
        qstate = mysql_query(conn, q);
        if (!qstate)
        {
            res = mysql_store_result(conn);
            while (row = mysql_fetch_row(res))
            {
                cout << "Hospital ID: " << row[0] << endl;
                cout << "Name: " << row[1] << endl;
                cout << "Street: " << row[2] << endl;
                cout << "City: " << row[3] << endl;
                cout << "State: " << row[4] << endl;
                cout << endl;
            }
            cout << endl << "Do you want to search other hospital?[Y/N]: ";
            cin >> SearchHosp;
            if (SearchHosp == 'y' || SearchHosp == 'Y')
                SearchHospital();
            else if (SearchHosp == 'n' || SearchHosp == 'N')
                StaffControlSearch();
        }
        else
        {
            cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
            system("pause");
            StaffControlSearch();
        }
    }

    else if (searchHospChoice == 4)
    {
        cout << "\nEnter Hospital  to search: ";
        cin.ignore(1, '\n');
        getline(cin, Hospital_State);
        cout << "\nHere's the record found: \n" << endl;
        string search_query = "SELECT Hospital_ID, Hospital_Name, Hospital_Street, Hospital_State, Hospital_City FROM hospital WHERE Hospital_State LIKE '%" + Hospital_State + "%' AND Availability = 'Available' ";
        const char* q = search_query.c_str();
        qstate = mysql_query(conn, q);
        if (!qstate)
        {
            res = mysql_store_result(conn);
            while (row = mysql_fetch_row(res))
            {
                cout << "Hospital ID: " << row[0] << endl;
                cout << "Name: " << row[1] << endl;
                cout << "Street: " << row[2] << endl;
                cout << "City: " << row[3] << endl;
                cout << "State: " << row[4] << endl;
                cout << endl;
            }
            cout << endl << "Do you want to search other hospital?[Y/N]: ";
            cin >> SearchHosp;
            if (SearchHosp == 'y' || SearchHosp == 'Y')
                SearchHospital();
            else if (SearchHosp == 'n' || SearchHosp == 'N')
                StaffControlSearch();
        }
        else
        {
            cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
            system("pause");
            StaffControlSearch();
        }
    }

    else if (searchHospChoice == 5)
    {
        cout << "\nEnter Hospital City to search: ";
        cin >> Hospital_City;
        cout << "\nHere's the record found: \n" << endl;
        string search_query = "SELECT Hospital_ID, Hospital_Name, Hospital_Street, Hospital_State, Hospital_City FROM hospital WHERE Hospital_City LIKE '%" + Hospital_City + "%' AND Availability = 'Available' ";
        const char* q = search_query.c_str();
        qstate = mysql_query(conn, q);
        if (!qstate)
        {
            res = mysql_store_result(conn);
            while (row = mysql_fetch_row(res))
            {
                cout << "Hospital ID: " << row[0] << endl;
                cout << "Name: " << row[1] << endl;
                cout << "Street: " << row[2] << endl;
                cout << "City: " << row[3] << endl;
                cout << "State: " << row[4] << endl;
                cout << endl;
            }
            cout << endl << "Do you want to search other hospital?[Y/N]: ";
            cin >> SearchHosp;
            if (SearchHosp == 'y' || SearchHosp == 'Y')
                SearchHospital();
            else if (SearchHosp == 'n' || SearchHosp == 'N')
                StaffControlSearch();
        }
        else
        {
            cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
            system("pause");
            StaffControlSearch();
        }
    }

    else if (searchHospChoice == 6)
    {
        StaffControlSearch();
    }

    else
    {
        cout << "Error! Invalid input for searching!" << endl;
        system("pause");
        StaffControlSearch();
    }
}

void SearchDonor()
{
    string Donor_ID, Donor_Name, Donor_Gender, Donor_DOB, Donor_Address, Donor_BloodType, Donor_TelNo, Donor_Password;
    int Donor_Age;
    double Donor_Height, Donor_Weight;

    int searchDonor;
    char SearchDon;
    system("cls");
    cout << foreground(Cyan);
    cout << "-----------------------" << endl;
    cout << " SEARCH RECORD - DONOR " << endl;
    cout << "-----------------------" << endl;
    cout << "\n";
    cout << background(Black) << foreground(White) << resetANSI();
    cout << "Please select the attribute you want to search: " << endl;
    cout << "[1] Donor ID " << endl;
    cout << "[2] Name " << endl;
    cout << "[3] Gender " << endl;
    cout << "[4] Age " << endl;
    cout << "[5] Date of Birth " << endl;
    cout << "[6] Address " << endl;
    cout << "[7] Blood Type " << endl;
    cout << "[8] Height " << endl;
    cout << "[9] Weight " << endl;
    cout << "[10] Phone " << endl;
    cout << "[11] Back to Main Menu " << endl;

    cout << "\nYour Choice >> ";
    cin >> searchDonor;

    if (searchDonor == 1)
    {
        cout << "Enter Donor ID to search (Format: DN****): ";
        cin >> Donor_ID;

        cout << "\nHere's the record found: \n" << endl;
        string search_query = "SELECT Donor_ID, Donor_Name, Donor_Gender, Donor_Age, Donor_DOB, Donor_Address, Donor_BloodType, Donor_Height, Donor_Weight, Donor_TelNo FROM donor WHERE Donor_ID = '" + Donor_ID + "' AND Active_Status = 'Active'";
        const char* q = search_query.c_str();
        qstate = mysql_query(conn, q);
        if (!qstate)
        {
            res = mysql_store_result(conn);
            while (row = mysql_fetch_row(res))
            {
                cout << "Donor ID: " << row[0] << endl;
                cout << "Name: " << row[1] << endl;
                cout << "Gender: " << row[2] << endl;
                cout << "Age: " << row[3] << endl;
                cout << "Date of Birth: " << row[4] << endl;
                cout << "Address: " << row[5] << endl;
                cout << "Blood Type: " << row[6] << endl;
                cout << "Height: " << row[7] << endl;
                cout << "Weight: " << row[8] << endl;
                cout << "Phone: " << row[9] << endl;
                cout << endl;
            }
            cout << endl << "Do you want to search other donor?[Y/N]: ";
            cin >> SearchDon;
            if (SearchDon == 'y' || SearchDon == 'Y')
                SearchDonor();
            else if (SearchDon == 'n' || SearchDon == 'N')
                StaffControlMain();
        }
        else
        {
            cout << "There's no any result about staff found! " << endl;
            cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
            system("pause");
            StaffControlSearch();
        }
    }

    else if (searchDonor == 2)
    {
        cout << "Enter Donor Name to search: ";
        cin.ignore(1, '\n');
        getline(cin, Donor_Name);

        cout << "\nHere's the record found: \n" << endl;
        string search_query = "SELECT Donor_ID, Donor_Name, Donor_Gender, Donor_Age, Donor_DOB, Donor_Address, Donor_BloodType, Donor_Height, Donor_Weight, Donor_TelNo FROM donor WHERE Donor_Name LIKE '%" + Donor_Name + "%' AND Active_Status = 'Active'";
        const char* q = search_query.c_str();
        qstate = mysql_query(conn, q);
        if (!qstate)
        {
            res = mysql_store_result(conn);
            while (row = mysql_fetch_row(res))
            {
                cout << "Donor ID: " << row[0] << endl;
                cout << "Name: " << row[1] << endl;
                cout << "Gender: " << row[2] << endl;
                cout << "Age: " << row[3] << endl;
                cout << "Date of Birth: " << row[4] << endl;
                cout << "Address: " << row[5] << endl;
                cout << "Blood Type: " << row[6] << endl;
                cout << "Height: " << row[7] << endl;
                cout << "Weight: " << row[8] << endl;
                cout << "Phone: " << row[9] << endl;
                cout << endl;
            }
            cout << endl << "Do you want to search other donor?[Y/N]: ";
            cin >> SearchDon;
            if (SearchDon == 'y' || SearchDon == 'Y')
                SearchDonor();
            else if (SearchDon == 'n' || SearchDon == 'N')
                StaffControlMain();
        }
        else
        {
            cout << "There's no any result about staff found! " << endl;
            cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
            system("pause");
            StaffControlSearch();
        }
    }

    else if (searchDonor == 3)
    {
        cout << "Enter Donor Gender to search [M/F]: ";
        cin >> Donor_Gender;

        cout << "\nHere's the record found: \n" << endl;
        string search_query = "SELECT Donor_ID, Donor_Name, Donor_Gender, Donor_Age, Donor_DOB, Donor_Address, Donor_BloodType, Donor_Height, Donor_Weight, Donor_TelNo FROM donor WHERE Donor_Gender = '" + Donor_Gender + "' AND Active_Status = 'Active'";
        const char* q = search_query.c_str();
        qstate = mysql_query(conn, q);
        if (!qstate)
        {
            res = mysql_store_result(conn);
            while (row = mysql_fetch_row(res))
            {
                cout << "Donor ID: " << row[0] << endl;
                cout << "Name: " << row[1] << endl;
                cout << "Gender: " << row[2] << endl;
                cout << "Age: " << row[3] << endl;
                cout << "Date of Birth: " << row[4] << endl;
                cout << "Address: " << row[5] << endl;
                cout << "Blood Type: " << row[6] << endl;
                cout << "Height: " << row[7] << endl;
                cout << "Weight: " << row[8] << endl;
                cout << "Phone: " << row[9] << endl;
                cout << endl;
            }
            cout << endl << "Do you want to search other donor?[Y/N]: ";
            cin >> SearchDon;
            if (SearchDon == 'y' || SearchDon == 'Y')
                SearchDonor();
            else if (SearchDon == 'n' || SearchDon == 'N')
                StaffControlMain();
        }
        else
        {
            cout << "There's no any result about staff found! " << endl;
            cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
            system("pause");
            StaffControlSearch();
        }
    }

    else if (searchDonor == 4)
    {
        cout << "Enter Donor Age to search: ";
        cin >> Donor_Age;

        cout << "\nHere's the record found: \n" << endl;
        string search_query = "SELECT Donor_ID, Donor_Name, Donor_Gender, Donor_Age, Donor_DOB, Donor_Address, Donor_BloodType, Donor_Height, Donor_Weight, Donor_TelNo FROM donor WHERE Donor_Age = '" + to_string(Donor_Age) + "' AND Active_Status = 'Active'";
        const char* q = search_query.c_str();
        qstate = mysql_query(conn, q);
        if (!qstate)
        {
            res = mysql_store_result(conn);
            while (row = mysql_fetch_row(res))
            {
                cout << "Donor ID: " << row[0] << endl;
                cout << "Name: " << row[1] << endl;
                cout << "Gender: " << row[2] << endl;
                cout << "Age: " << row[3] << endl;
                cout << "Date of Birth: " << row[4] << endl;
                cout << "Address: " << row[5] << endl;
                cout << "Blood Type: " << row[6] << endl;
                cout << "Height: " << row[7] << endl;
                cout << "Weight: " << row[8] << endl;
                cout << "Phone: " << row[9] << endl;
                cout << endl;
            }
            cout << endl << "Do you want to search other donor?[Y/N]: ";
            cin >> SearchDon;
            if (SearchDon == 'y' || SearchDon == 'Y')
                SearchDonor();
            else if (SearchDon == 'n' || SearchDon == 'N')
                StaffControlMain();
        }
        else
        {
            cout << "There's no any result about staff found! " << endl;
            cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
            system("pause");
            StaffControlSearch();
        }
    }

    else if (searchDonor == 5)
    {
        cout << "Enter Date of Birth to search: ";
        cin >> Donor_DOB;

        cout << "\nHere's the record found: \n" << endl;
        string search_query = "SELECT Donor_ID, Donor_Name, Donor_Gender, Donor_Age, Donor_DOB, Donor_Address, Donor_BloodType, Donor_Height, Donor_Weight, Donor_TelNo FROM donor WHERE Donor_DOB LIKE '%" + Donor_DOB + "%' AND Active_Status = 'Active'";
        const char* q = search_query.c_str();
        qstate = mysql_query(conn, q);
        if (!qstate)
        {
            res = mysql_store_result(conn);
            while (row = mysql_fetch_row(res))
            {
                cout << "Donor ID: " << row[0] << endl;
                cout << "Name: " << row[1] << endl;
                cout << "Gender: " << row[2] << endl;
                cout << "Age: " << row[3] << endl;
                cout << "Date of Birth: " << row[4] << endl;
                cout << "Address: " << row[5] << endl;
                cout << "Blood Type: " << row[6] << endl;
                cout << "Height: " << row[7] << endl;
                cout << "Weight: " << row[8] << endl;
                cout << "Phone: " << row[9] << endl;
                cout << endl;
            }
            cout << endl << "Do you want to search other donor?[Y/N]: ";
            cin >> SearchDon;
            if (SearchDon == 'y' || SearchDon == 'Y')
                SearchDonor();
            else if (SearchDon == 'n' || SearchDon == 'N')
                StaffControlMain();
        }
        else
        {
            cout << "There's no any result about staff found! " << endl;
            cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
            system("pause");
            StaffControlSearch();
        }
    }

    else if (searchDonor == 6)
    {
        cout << "Enter Address to search: ";
        cin.ignore(1, '\n');
        getline(cin, Donor_Address);

        cout << "\nHere's the record found: \n" << endl;
        string search_query = "SELECT Donor_ID, Donor_Name, Donor_Gender, Donor_Age, Donor_DOB, Donor_Address, Donor_BloodType, Donor_Height, Donor_Weight, Donor_TelNo FROM donor WHERE Donor_Address LIKE '%" + Donor_Address + "%' AND Active_Status = 'Active'";
        const char* q = search_query.c_str();
        qstate = mysql_query(conn, q);
        if (!qstate)
        {
            res = mysql_store_result(conn);
            while (row = mysql_fetch_row(res))
            {
                cout << "Donor ID: " << row[0] << endl;
                cout << "Name: " << row[1] << endl;
                cout << "Gender: " << row[2] << endl;
                cout << "Age: " << row[3] << endl;
                cout << "Date of Birth: " << row[4] << endl;
                cout << "Address: " << row[5] << endl;
                cout << "Blood Type: " << row[6] << endl;
                cout << "Height: " << row[7] << endl;
                cout << "Weight: " << row[8] << endl;
                cout << "Phone: " << row[9] << endl;
                cout << endl;
            }
            cout << endl << "Do you want to search other donor?[Y/N]: ";
            cin >> SearchDon;
            if (SearchDon == 'y' || SearchDon == 'Y')
                SearchDonor();
            else if (SearchDon == 'n' || SearchDon == 'N')
                StaffControlMain();
        }
        else
        {
            cout << "There's no any result about staff found! " << endl;
            cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
            system("pause");
            StaffControlSearch();
        }
    }

    else if (searchDonor == 7)
    {
        cout << "Enter Blood Type to search [A, O, B, AB]: ";
        cin >> Donor_BloodType;

        cout << "\nHere's the record found: \n" << endl;
        string search_query = "SELECT Donor_ID, Donor_Name, Donor_Gender, Donor_Age, Donor_DOB, Donor_Address, Donor_BloodType, Donor_Height, Donor_Weight, Donor_TelNo FROM donor WHERE Donor_BloodType = '" + Donor_BloodType + "' AND Active_Status = 'Active'";
        const char* q = search_query.c_str();
        qstate = mysql_query(conn, q);
        if (!qstate)
        {
            res = mysql_store_result(conn);
            while (row = mysql_fetch_row(res))
            {
                cout << "Donor ID: " << row[0] << endl;
                cout << "Name: " << row[1] << endl;
                cout << "Gender: " << row[2] << endl;
                cout << "Age: " << row[3] << endl;
                cout << "Date of Birth: " << row[4] << endl;
                cout << "Address: " << row[5] << endl;
                cout << "Blood Type: " << row[6] << endl;
                cout << "Height: " << row[7] << endl;
                cout << "Weight: " << row[8] << endl;
                cout << "Phone: " << row[9] << endl;
                cout << endl;
            }
            cout << endl << "Do you want to search other donor?[Y/N]: ";
            cin >> SearchDon;
            if (SearchDon == 'y' || SearchDon == 'Y')
                SearchDonor();
            else if (SearchDon == 'n' || SearchDon == 'N')
                StaffControlMain();
        }
        else
        {
            cout << "There's no any result about staff found! " << endl;
            cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
            system("pause");
            StaffControlSearch();
        }
    }

    else if (searchDonor == 8)
    {
        cout << "Enter Height to search: ";
        cin >> Donor_Height;

        cout << "\nHere's the record found: \n" << endl;
        string search_query = "SELECT Donor_ID, Donor_Name, Donor_Gender, Donor_Age, Donor_DOB, Donor_Address, Donor_BloodType, Donor_Height, Donor_Weight, Donor_TelNo FROM donor WHERE Donor_Height = '" + to_string(Donor_Height) + "' AND Active_Status = 'Active'";
        const char* q = search_query.c_str();
        qstate = mysql_query(conn, q);
        if (!qstate)
        {
            res = mysql_store_result(conn);
            while (row = mysql_fetch_row(res))
            {
                cout << "Donor ID: " << row[0] << endl;
                cout << "Name: " << row[1] << endl;
                cout << "Gender: " << row[2] << endl;
                cout << "Age: " << row[3] << endl;
                cout << "Date of Birth: " << row[4] << endl;
                cout << "Address: " << row[5] << endl;
                cout << "Blood Type: " << row[6] << endl;
                cout << "Height: " << row[7] << endl;
                cout << "Weight: " << row[8] << endl;
                cout << "Phone: " << row[9] << endl;
                cout << endl;
            }
            cout << endl << "Do you want to search other donor?[Y/N]: ";
            cin >> SearchDon;
            if (SearchDon == 'y' || SearchDon == 'Y')
                SearchDonor();
            else if (SearchDon == 'n' || SearchDon == 'N')
                StaffControlMain();
        }
        else
        {
            cout << "There's no any result about staff found! " << endl;
            cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
            system("pause");
            StaffControlSearch();
        }
    }

    else if (searchDonor == 9)
    {
        cout << "Enter Weight to search: ";
        cin >> Donor_Weight;

        cout << "\nHere's the record found: \n" << endl;
        string search_query = "SELECT Donor_ID, Donor_Name, Donor_Gender, Donor_Age, Donor_DOB, Donor_Address, Donor_BloodType, Donor_Height, Donor_Weight, Donor_TelNo FROM donor WHERE Donor_Weight = '" + to_string(Donor_Weight) + "' AND Active_Status = 'Active'";
        const char* q = search_query.c_str();
        qstate = mysql_query(conn, q);
        if (!qstate)
        {
            res = mysql_store_result(conn);
            while (row = mysql_fetch_row(res))
            {
                cout << "Donor ID: " << row[0] << endl;
                cout << "Name: " << row[1] << endl;
                cout << "Gender: " << row[2] << endl;
                cout << "Age: " << row[3] << endl;
                cout << "Date of Birth: " << row[4] << endl;
                cout << "Address: " << row[5] << endl;
                cout << "Blood Type: " << row[6] << endl;
                cout << "Height: " << row[7] << endl;
                cout << "Weight: " << row[8] << endl;
                cout << "Phone: " << row[9] << endl;
                cout << endl;
            }
            cout << endl << "Do you want to search other donor?[Y/N]: ";
            cin >> SearchDon;
            if (SearchDon == 'y' || SearchDon == 'Y')
                SearchDonor();
            else if (SearchDon == 'n' || SearchDon == 'N')
                StaffControlMain();
        }
        else
        {
            cout << "There's no any result about staff found! " << endl;
            cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
            system("pause");
            StaffControlSearch();
        }
    }

    else if (searchDonor == 10)
    {
        cout << "Enter Phone Number to search: ";
        cin >> Donor_TelNo;

        cout << "\nHere's the record found: \n" << endl;
        string search_query = "SELECT Donor_ID, Donor_Name, Donor_Gender, Donor_Age, Donor_DOB, Donor_Address, Donor_BloodType, Donor_Height, Donor_Weight, Donor_TelNo FROM donor WHERE Donor_TelNo LIKE '%" + Donor_TelNo + "%' AND Active_Status = 'Active'";
        const char* q = search_query.c_str();
        qstate = mysql_query(conn, q);
        if (!qstate)
        {
            res = mysql_store_result(conn);
            while (row = mysql_fetch_row(res))
            {
                cout << "Donor ID: " << row[0] << endl;
                cout << "Name: " << row[1] << endl;
                cout << "Gender: " << row[2] << endl;
                cout << "Age: " << row[3] << endl;
                cout << "Date of Birth: " << row[4] << endl;
                cout << "Address: " << row[5] << endl;
                cout << "Blood Type: " << row[6] << endl;
                cout << "Height: " << row[7] << endl;
                cout << "Weight: " << row[8] << endl;
                cout << "Phone: " << row[9] << endl;
                cout << endl;
            }
            cout << endl << "Do you want to search other donor?[Y/N]: ";
            cin >> SearchDon;
            if (SearchDon == 'y' || SearchDon == 'Y')
                SearchDonor();
            else if (SearchDon == 'n' || SearchDon == 'N')
                StaffControlMain();
        }
        else
        {
            cout << "There's no any result about staff found! " << endl;
            cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
            system("pause");
            StaffControlSearch();
        }
    }

    else if (searchDonor == 11)
    {
        StaffControlSearch();
    }

    else
    {
        cout << "Error! Invalid input for searching!" << endl;
        system("pause");
        StaffControlSearch();
    }
}

void SearchDonation()
{
    system("cls");
    string Donation_ID, Donation_Date, Record_ID, Hospital_ID, Donor_ID;
    int Donation_Volume;
    int searchDonation;
    char SearchDonate;
    cout << foreground(Cyan) << resetANSI();
    cout << "--------------------------" << endl;
    cout << " SEARCH RECORD - DONATION " << endl;
    cout << "--------------------------" << endl;
    cout << "Please select the attribute you want to search: " << endl;
    cout << "[1] Record ID: " << endl;
    cout << "[2] Donation ID " << endl;
    cout << "[3] Donor ID " << endl;
    cout << "[4] Donation Date " << endl;
    cout << "[5] Donation Volume " << endl;
    cout << "[6] Hospital ID " << endl;
    cout << "[7] Back to Main Menu" << endl;

    cout << "\nYour Choice >> ";
    cin >> searchDonation;

    if (searchDonation == 1)
    {
        cout << "\nEnter Record ID to search (Format: RC****): ";
        cin >> Record_ID;

        cout << "\nHere's the record found: \n" << endl;
        string search_query = "SELECT r.Record_ID, t.Donation_ID, d.Donor_ID, t.Donation_Date, t.Donation_Volume, h.Hospital_ID FROM blood_donation t, donor_record r, hospital h, donor d WHERE t.Record_ID = '" + Record_ID + "' AND r.Record_ID = t.Record_ID AND d.Donor_ID = r.Donor_ID AND h.Hospital_ID = r.Hospital_ID AND Status = 'Completed'";
        const char* q = search_query.c_str();
        qstate = mysql_query(conn, q);
        if (!qstate)
        {
            res = mysql_store_result(conn);
            while (row = mysql_fetch_row(res))
            {
                cout << "Record ID: " << row[0] << endl;
                cout << "Donation ID: " << row[1] << endl;
                cout << "Donor ID: " << row[2] << endl;
                cout << "Donation Date: " << row[3] << endl;
                cout << "Donation Volume: " << row[4] << endl;
                cout << "Hospital ID: " << row[5] << endl;
                cout << endl;
            }
            cout << endl << "Do you want to search other blood donation record?[Y/N]: ";

            cin >> SearchDonate;
            if (SearchDonate == 'y' || SearchDonate == 'Y')
                SearchDonation();
            else if (SearchDonate == 'n' || SearchDonate == 'N')
                StaffControlSearch();
        }
        else
        {
            cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
            system("pause");
            StaffControlSearch();
        }
    }

    else if (searchDonation == 2)
    {
        cout << "\nEnter Donation ID to search (Format: DT****): ";
        cin >> Donation_ID;

        cout << "\nHere's the record found: \n" << endl;
        string search_query = "SELECT r.Record_ID, t.Donation_ID, d.Donor_ID, t.Donation_Date, t.Donation_Volume, h.Hospital_ID FROM blood_donation t, donor_record r, hospital h, donor d WHERE t.Donation_ID = '" + Donation_ID + "' AND r.Record_ID = t.Record_ID AND d.Donor_ID = r.Donor_ID AND h.Hospital_ID = r.Hospital_ID AND Status = 'Completed'";
        const char* q = search_query.c_str();
        qstate = mysql_query(conn, q);
        if (!qstate)
        {
            res = mysql_store_result(conn);
            while (row = mysql_fetch_row(res))
            {
                cout << "Record ID: " << row[0] << endl;
                cout << "Donation ID: " << row[1] << endl;
                cout << "Donor ID: " << row[2] << endl;
                cout << "Donation Date: " << row[3] << endl;
                cout << "Donation Volume: " << row[4] << endl;
                cout << "Hospital ID: " << row[5] << endl;
                cout << endl;
            }
            cout << endl << "Do you want to search other blood donation record?[Y/N]: ";

            cin >> SearchDonate;
            if (SearchDonate == 'y' || SearchDonate == 'Y')
                SearchDonation();
            else if (SearchDonate == 'n' || SearchDonate == 'N')
                StaffControlSearch();
        }
        else
        {
            cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
            system("pause");
            StaffControlSearch();
        }
    }

    else if (searchDonation == 3)
    {
        cout << "\nEnter Donor ID to search (Format: DN****): ";
        cin >> Donor_ID;

        cout << "\nHere's the record found: \n" << endl;
        string search_query = "SELECT r.Record_ID, t.Donation_ID, d.Donor_ID, t.Donation_Date, t.Donation_Volume, h.Hospital_ID FROM blood_donation t, donor_record r, hospital h, donor d WHERE r.Donor_ID = '" + Donor_ID + "' AND r.Record_ID = t.Record_ID AND d.Donor_ID = r.Donor_ID AND h.Hospital_ID = r.Hospital_ID AND Status = 'Completed'";
        const char* q = search_query.c_str();
        qstate = mysql_query(conn, q);
        if (!qstate)
        {
            res = mysql_store_result(conn);
            while (row = mysql_fetch_row(res))
            {
                cout << "Record ID: " << row[0] << endl;
                cout << "Donation ID: " << row[1] << endl;
                cout << "Donor ID: " << row[2] << endl;
                cout << "Donation Date: " << row[3] << endl;
                cout << "Donation Volume: " << row[4] << endl;
                cout << "Hospital ID: " << row[5] << endl;
                cout << endl;
            }
            cout << endl << "Do you want to search other blood donation record?[Y/N]: ";

            cin >> SearchDonate;
            if (SearchDonate == 'y' || SearchDonate == 'Y')
                SearchDonation();
            else if (SearchDonate == 'n' || SearchDonate == 'N')
                StaffControlSearch();
        }
        else
        {
            cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
            system("pause");
            StaffControlSearch();
        }
    }

    else if (searchDonation == 4)
    {
        cout << "\nEnter Donation Date to search: ";
        cin >> Donation_Date;

        cout << "\nHere's the record found: \n" << endl;
        string search_query = "SELECT r.Record_ID, t.Donation_ID, d.Donor_ID, t.Donation_Date, t.Donation_Volume, h.Hospital_ID FROM blood_donation t, donor_record r, hospital h, donor d WHERE t.Donation_Date LIKE '%" + Donation_Date + "%' AND r.Record_ID = t.Record_ID AND d.Donor_ID = r.Donor_ID AND h.Hospital_ID = r.Hospital_ID AND Status = 'Completed'";
        const char* q = search_query.c_str();
        qstate = mysql_query(conn, q);
        if (!qstate)
        {
            res = mysql_store_result(conn);
            while (row = mysql_fetch_row(res))
            {
                cout << "Record ID: " << row[0] << endl;
                cout << "Donation ID: " << row[1] << endl;
                cout << "Donor ID: " << row[2] << endl;
                cout << "Donation Date: " << row[3] << endl;
                cout << "Donation Volume: " << row[4] << endl;
                cout << "Hospital ID: " << row[5] << endl;
                cout << endl;
            }
            cout << endl << "Do you want to search other blood donation record?[Y/N]: ";

            cin >> SearchDonate;
            if (SearchDonate == 'y' || SearchDonate == 'Y')
                SearchDonation();
            else if (SearchDonate == 'n' || SearchDonate == 'N')
                StaffControlSearch();
        }
        else
        {
            cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
            system("pause");
            StaffControlSearch();
        }
    }

    else if (searchDonation == 5)
    {
        cout << "\nEnter Donation Volume to search: ";
        cin >> Donation_Volume;

        cout << "\nHere's the record found: \n" << endl;
        string search_query = "SELECT r.Record_ID, t.Donation_ID, d.Donor_ID, t.Donation_Date, t.Donation_Volume, h.Hospital_ID FROM blood_donation t, donor_record r, hospital h, donor d WHERE t.Donation_Volume = '" + to_string(Donation_Volume) + "' AND r.Record_ID = t.Record_ID AND d.Donor_ID = r.Donor_ID AND h.Hospital_ID = r.Hospital_ID AND Status = 'Completed'";
        const char* q = search_query.c_str();
        qstate = mysql_query(conn, q);
        if (!qstate)
        {
            res = mysql_store_result(conn);
            while (row = mysql_fetch_row(res))
            {
                cout << "Record ID: " << row[0] << endl;
                cout << "Donation ID: " << row[1] << endl;
                cout << "Donor ID: " << row[2] << endl;
                cout << "Donation Date: " << row[3] << endl;
                cout << "Donation Volume: " << row[4] << endl;
                cout << "Hospital ID: " << row[5] << endl;
                cout << endl;
            }
            cout << endl << "Do you want to search other blood donation record?[Y/N]: ";

            cin >> SearchDonate;
            if (SearchDonate == 'y' || SearchDonate == 'Y')
                SearchDonation();
            else if (SearchDonate == 'n' || SearchDonate == 'N')
                StaffControlSearch();
        }
        else
        {
            cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
            system("pause");
            StaffControlSearch();
        }
    }

    else if (searchDonation == 6)
    {
        cout << "\nEnter Hospital ID to search (Format: HS****): ";
        cin >> Hospital_ID;

        cout << "\nHere's the record found: \n" << endl;
        string search_query = "SELECT r.Record_ID, t.Donation_ID, d.Donor_ID, t.Donation_Date, t.Donation_Volume, h.Hospital_ID FROM blood_donation t, donor_record r, hospital h, donor d WHERE r.Hospital_ID = '" + Hospital_ID + "' AND r.Record_ID = t.Record_ID AND d.Donor_ID = r.Donor_ID AND h.Hospital_ID = r.Hospital_ID AND Status = 'Completed'";
        const char* q = search_query.c_str();
        qstate = mysql_query(conn, q);
        if (!qstate)
        {
            res = mysql_store_result(conn);
            while (row = mysql_fetch_row(res))
            {
                cout << "Record ID: " << row[0] << endl;
                cout << "Donation ID: " << row[1] << endl;
                cout << "Donor ID: " << row[2] << endl;
                cout << "Donation Date: " << row[3] << endl;
                cout << "Donation Volume: " << row[4] << endl;
                cout << "Hospital ID: " << row[5] << endl;
                cout << endl;
            }
            cout << endl << "Do you want to search other blood donation record?[Y/N]: ";

            cin >> SearchDonate;
            if (SearchDonate == 'y' || SearchDonate == 'Y')
                SearchDonation();
            else if (SearchDonate == 'n' || SearchDonate == 'N')
                StaffControlSearch();
        }
        else
        {
            cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
            system("pause");
            StaffControlSearch();
        }
    }

    else if (searchDonation == 7)
    {
        StaffControlSearch();
    }

    else
    {
        cout << "Error! Invalid input for searching!" << endl;
        system("pause");
        StaffControlSearch();
    }
}

void SearchBlood()
{
    string Stock_ID, Stock_Category, Staff_ID, Donation_ID;
    int Stock_Volume, Stock_Quantity, Total_Stock_Volume;
    char SearchStock;
    int searchBlood;
    system("cls");
    cout << foreground(Black) << background(Cyan);
    cout << "-----------------------------" << endl;
    cout << " SEARCH RECORD - BLOOD STOCK " << endl;
    cout << "-----------------------------" << endl;
    cout << background(Black) << foreground(White) << resetANSI();
    cout << "Please select the attribute you want to search: " << endl;

    cout << "[1] Stock ID " << endl;
    cout << "[2] Category " << endl;
    cout << "[3] Volume " << endl;
    cout << "[4] Quantity " << endl;
    cout << "[5] Total Volume " << endl;
    cout << "[6] Staff ID " << endl;
    cout << "[7] Donation ID " << endl;
    cout << "[8] Back to Main Menu" << endl;

    cout << "\nYour choice >> ";
    cin >> searchBlood;

    if (searchBlood == 1)
    {
        cout << "\nEnter Blood Stock ID to search (Format: BL****): ";
        cin >> Stock_ID;

        cout << "\nHere's the record found: \n" << endl;
        string search_query = "SELECT Stock_ID, Stock_Category, Stock_Volume, Stock_Quantity, Stock_Volume, Total_Stock_Volume, Staff_ID, Donation_ID FROM blood_stock WHERE Stock_ID = '" + Stock_ID + "' AND Status = 'Available'";
        const char* q = search_query.c_str();
        qstate = mysql_query(conn, q);
        if (!qstate)
        {
            res = mysql_store_result(conn);
            while (row = mysql_fetch_row(res))
            {
                cout << "Stock ID: " << row[0] << endl;
                cout << "Category: " << row[1] << endl;
                cout << "Volume: " << row[2] << endl;
                cout << "Quantity: " << row[3] << endl;
                cout << "Total Volume: " << row[4] << endl;
                cout << "Staff ID: " << row[5] << endl;
                cout << "Donation ID: " << row[6] << endl;
                cout << endl;
            }
            cout << endl << "Do you want to search other blood stock?(y/n): ";
            cin >> SearchStock;

            if (SearchStock == 'y' || SearchStock == 'Y')
                SearchBlood();

            else if (SearchStock == 'n' || SearchStock == 'N')
                StaffControlSearch();
        }
        else
        {
            cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
            system("pause");
            StaffControlSearch();
        }
    }

    else if (searchBlood == 2)
    {
        cout << "\nEnter Blood Category to search (O, AB, A, B): ";
        cin >> Stock_Category;

        cout << "\nHere's the record found: \n" << endl;
        string search_query = "SELECT Stock_ID, Stock_Category, Stock_Volume, Stock_Quantity, Stock_Volume, Total_Stock_Volume, Staff_ID, Donation_ID FROM blood_stock WHERE Stock_Category = '" + Stock_Category + "' AND Status = 'Available'";
        const char* q = search_query.c_str();
        qstate = mysql_query(conn, q);
        if (!qstate)
        {
            res = mysql_store_result(conn);
            while (row = mysql_fetch_row(res))
            {
                cout << "Stock ID: " << row[0] << endl;
                cout << "Category: " << row[1] << endl;
                cout << "Volume: " << row[2] << endl;
                cout << "Quantity: " << row[3] << endl;
                cout << "Total Volume: " << row[4] << endl;
                cout << "Staff ID: " << row[5] << endl;
                cout << "Donation ID: " << row[6] << endl;
                cout << endl;
            }
            cout << endl << "Do you want to search other blood stock?(y/n): ";
            cin >> SearchStock;

            if (SearchStock == 'y' || SearchStock == 'Y')
                SearchBlood();

            else if (SearchStock == 'n' || SearchStock == 'N')
                StaffControlSearch();
        }
        else
        {
            cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
            system("pause");
            StaffControlSearch();
        }
    }

    else if (searchBlood == 3)
    {
        cout << "\nEnter Blood Stock Volume to search: ";
        cin >> Stock_Volume;

        cout << "\nHere's the record found: \n" << endl;
        string search_query = "SELECT Stock_ID, Stock_Category, Stock_Volume, Stock_Quantity, Stock_Volume, Total_Stock_Volume, Staff_ID, Donation_ID FROM blood_stock WHERE Stock_Volume = '" + to_string(Stock_Volume) + "' AND Status = 'Available'";
        const char* q = search_query.c_str();
        qstate = mysql_query(conn, q);
        if (!qstate)
        {
            res = mysql_store_result(conn);
            while (row = mysql_fetch_row(res))
            {
                cout << "Stock ID: " << row[0] << endl;
                cout << "Category: " << row[1] << endl;
                cout << "Volume: " << row[2] << endl;
                cout << "Quantity: " << row[3] << endl;
                cout << "Total Volume: " << row[4] << endl;
                cout << "Staff ID: " << row[5] << endl;
                cout << "Donation ID: " << row[6] << endl;
                cout << endl;
            }
            cout << endl << "Do you want to search other blood stock?(y/n): ";
            cin >> SearchStock;

            if (SearchStock == 'y' || SearchStock == 'Y')
                SearchBlood();

            else if (SearchStock == 'n' || SearchStock == 'N')
                StaffControlSearch();
        }
        else
        {
            cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
            system("pause");
            StaffControlSearch();
        }
    }

    else if (searchBlood == 4)
    {
        cout << "\nEnter Blood Stock Quantity to search: ";
        cin >> Stock_Quantity;

        cout << "\nHere's the record found: \n" << endl;
        string search_query = "SELECT Stock_ID, Stock_Category, Stock_Volume, Stock_Quantity, Stock_Volume, Total_Stock_Volume, Staff_ID, Donation_ID FROM blood_stock WHERE Stock_Quantity = '" + to_string(Stock_Quantity) + "' AND Status = 'Available'";
        const char* q = search_query.c_str();
        qstate = mysql_query(conn, q);
        if (!qstate)
        {
            res = mysql_store_result(conn);
            while (row = mysql_fetch_row(res))
            {
                cout << "Stock ID: " << row[0] << endl;
                cout << "Category: " << row[1] << endl;
                cout << "Volume: " << row[2] << endl;
                cout << "Quantity: " << row[3] << endl;
                cout << "Total Volume: " << row[4] << endl;
                cout << "Staff ID: " << row[5] << endl;
                cout << "Donation ID: " << row[6] << endl;
                cout << endl;
            }
            cout << endl << "Do you want to search other blood stock?(y/n): ";
            cin >> SearchStock;

            if (SearchStock == 'y' || SearchStock == 'Y')
                SearchBlood();

            else if (SearchStock == 'n' || SearchStock == 'N')
                StaffControlSearch();
        }
        else
        {
            cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
            system("pause");
            StaffControlSearch();
        }
    }

    else if (searchBlood == 5)
    {
        cout << "\nEnter Total Stock Volume to search (Format: BL****): ";
        cin >> Total_Stock_Volume;

        cout << "\nHere's the record found: \n" << endl;
        string search_query = "SELECT Stock_ID, Stock_Category, Stock_Volume, Stock_Quantity, Stock_Volume, Total_Stock_Volume, Staff_ID, Donation_ID FROM blood_stock WHERE Total_Stock_Volume = '" + to_string(Total_Stock_Volume) + "' AND Status = 'Available'";
        const char* q = search_query.c_str();
        qstate = mysql_query(conn, q);
        if (!qstate)
        {
            res = mysql_store_result(conn);
            while (row = mysql_fetch_row(res))
            {
                cout << "Stock ID: " << row[0] << endl;
                cout << "Category: " << row[1] << endl;
                cout << "Volume: " << row[2] << endl;
                cout << "Quantity: " << row[3] << endl;
                cout << "Total Volume: " << row[4] << endl;
                cout << "Staff ID: " << row[5] << endl;
                cout << "Donation ID: " << row[6] << endl;
                cout << endl;
            }
            cout << endl << "Do you want to search other blood stock?(y/n): ";
            cin >> SearchStock;

            if (SearchStock == 'y' || SearchStock == 'Y')
                SearchBlood();

            else if (SearchStock == 'n' || SearchStock == 'N')
                StaffControlSearch();
        }
        else
        {
            cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
            system("pause");
            StaffControlSearch();
        }
    }

    else if (searchBlood == 6)
    {
        cout << "\nEnter Staff ID to search (Format: ST****): ";
        cin >> Staff_ID;

        cout << "\nHere's the record found: \n" << endl;
        string search_query = "SELECT Stock_ID, Stock_Category, Stock_Volume, Stock_Quantity, Stock_Volume, Total_Stock_Volume, Staff_ID, Donation_ID FROM blood_stock JOIN staff USING (Staff_ID) WHERE Staff_ID = '" + Staff_ID + "' AND Status = 'Available'";
        const char* q = search_query.c_str();
        qstate = mysql_query(conn, q);
        if (!qstate)
        {
            res = mysql_store_result(conn);
            while (row = mysql_fetch_row(res))
            {
                cout << "Stock ID: " << row[0] << endl;
                cout << "Category: " << row[1] << endl;
                cout << "Volume: " << row[2] << endl;
                cout << "Quantity: " << row[3] << endl;
                cout << "Total Volume: " << row[4] << endl;
                cout << "Staff ID: " << row[5] << endl;
                cout << "Donation ID: " << row[6] << endl;
                cout << endl;
            }
            cout << endl << "Do you want to search other blood stock?(y/n): ";
            cin >> SearchStock;

            if (SearchStock == 'y' || SearchStock == 'Y')
                SearchBlood();

            else if (SearchStock == 'n' || SearchStock == 'N')
                StaffControlSearch();
        }
        else
        {
            cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
            system("pause");
            StaffControlSearch();
        }
    }

    else if (searchBlood == 7)
    {
        cout << "\nEnter Donation ID to search (Format: DT****): ";
        cin >> Donation_ID;

        cout << "\nHere's the record found: \n" << endl;
        string search_query = "SELECT Stock_ID, Stock_Category, Stock_Volume, Stock_Quantity, Stock_Volume, Total_Stock_Volume, Staff_ID, Donation_ID FROM blood_stock JOIN blood_donation USING (Donation_ID) WHERE Donation_ID = '" + Donation_ID + "' AND Status = 'Available'";
        const char* q = search_query.c_str();
        qstate = mysql_query(conn, q);
        if (!qstate)
        {
            res = mysql_store_result(conn);
            while (row = mysql_fetch_row(res))
            {
                cout << "Stock ID: " << row[0] << endl;
                cout << "Category: " << row[1] << endl;
                cout << "Volume: " << row[2] << endl;
                cout << "Quantity: " << row[3] << endl;
                cout << "Total Volume: " << row[4] << endl;
                cout << "Staff ID: " << row[5] << endl;
                cout << "Donation ID: " << row[6] << endl;
                cout << endl;
            }
            cout << endl << "Do you want to search other blood stock?(y/n): ";
            cin >> SearchStock;

            if (SearchStock == 'y' || SearchStock == 'Y')
                SearchBlood();

            else if (SearchStock == 'n' || SearchStock == 'N')
                StaffControlSearch();
        }
        else
        {
            cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
            system("pause");
            StaffControlSearch();
        }
    }

    else if (searchBlood == 8)
    {
        StaffControlSearch();
    }

    else
    {
        cout << "Error! Invalid input for searching!" << endl;
        system("pause");
        StaffControlSearch();
    }
}


//staff view the recent donation records of all donors
void RecentDonation()
{
    system("cls");
    cout << background(Cyan) << foreground(Black);
    cout << "-------------------------" << endl;
    cout << "  BLOOD DONATION RECORD  " << endl;
    cout << "-------------------------" << endl;
    cout << background(Black) << foreground(White) << resetANSI();
    cout << "\nHere is the blood donation record: " << endl;

    //equijoin method to display record
    string viewDonorRecordList = "SELECT s.Record_ID, t.Donation_Date, d.Donor_ID, d.Donor_Name, t.Donation_Volume, d.Donor_BloodType, h.Hospital_Name FROM donor d, blood_donation t, donor_record s , hospital h WHERE d.Donor_ID = s.Donor_ID AND t.Record_ID = s.Record_ID AND h.Hospital_ID = s.Hospital_ID ORDER BY s.Record_ID";
    const char* vtr = viewDonorRecordList.c_str();
    qstate = mysql_query(conn, vtr);
    if (!qstate)
    {
        cout << background(Cyan) << foreground(Black) << "-------------------------------------------------------------------------------------------------------------------------------------" << endl;
        printf("| %-10s | %-15s | %-8s | %-30s | %-16s | %-12s | %-20s |\n", "Record ID", "Donation Date", "Donor ID", "Donor Name", "Donation Volume", "Blood Type", "Hospital");
        cout << background(Cyan) << foreground(Black) << "-------------------------------------------------------------------------------------------------------------------------------------" << endl;

        res = mysql_store_result(conn);
        while (row = mysql_fetch_row(res))
        {
            cout << background(White) << foreground(Black);
            printf("| %-10s | %-15s | %-8s | %-30s | %-16s | %-12s | %-20s |\n", row[0], row[1], row[2], row[3], row[4], row[5], row[6]);
        }
        cout << "-------------------------------------------------------------------------------------------------------------------------------------" << endl;
        cout << background(Black) << foreground(White) << resetANSI();
        cout << "\n";
        system("pause");
        system("cls");
        StaffMainMenu(Staff_ID, Staff_Name);
    }
    else
    {
        cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
        system("pause");
        system("cls");
        StaffMainMenu(Staff_ID, Staff_Name);
    }
}

//report generated for staff
void StaffReport()
{
    system("cls");

    string donorNum;
    cout << foreground(Black) << background(Cyan);
    cout << "=============================================" << endl;
    cout << "            BLOOD DONATION REPORT            " << endl;
    cout << "=============================================" << endl;
    cout << background(Black) << foreground(White) << resetANSI();
    string countActDon_query = "Select COUNT(Donor_ID) FROM donor WHERE Active_Status = 'Active'";
    const char* staf = countActDon_query.c_str();
    qstate = mysql_query(conn, staf);
    if (!qstate)
    {
        res = mysql_store_result(conn);
        if (res->row_count == 1)
        {
            while (row = mysql_fetch_row(res))
            {
                donorNum = row[0];
            }
        }
        else
        {
            cout << "Error" << endl;
            system("pause");
            system("cls");
            StaffMainMenu(Staff_ID, Staff_Name);
        }
    }
    else
    {
        cout << "error!" << endl;
        system("pause");
        system("cls");
        StaffMainMenu(Staff_ID, Staff_Name);
    }

    cout << "\nCurrently, there are " << foreground(Cyan) << donorNum << foreground(White) << " active donors registered in the system." << endl;



    int startYear, startMonth, startDay, endYear, endMonth, endDay;

    cout << foreground(Light_Red) << background(Black);
    cout << "------------------------" << endl;
    cout << " REPORT SELECTION QUERY " << endl;
    cout << "------------------------" << endl;
    cout << foreground(White) << background(Black);
    cout << "Please select the period for blood donation record:" << endl;
    cout << "If want to choose same year, just type same value for both starting and ending year;" << endl;
    cout << "If want to choose same month, just type same value for both starting and ending month;" << endl;
    cout << "If want to choose same day, just type same value for both starting and ending day;" << endl;
    cout << "\n";

    cout << "Select starting year (YYYY): ";
    cin >> startYear;

    cout << "Select starting month (MM): ";
    cin >> startMonth;

    cout << "Select starting day (DD): ";
    cin >> startDay;

    cout << "\n";

    cout << "Select ending year (YYYY): ";
    cin >> endYear;

    cout << "Select ending month (MMMM): ";
    cin >> endMonth;

    cout << "Select ending day (DD): ";
    cin >> endDay;

    cout << background(Black) << foreground(Light_Blue);
    char a = 177, b = 219;

    cout << "\n\t\t" << "Loading...\n";
    printf("\t\t");

    // Print initial loading bar
    for (int i = 0; i < 30; i++)
        printf("%c", a);

    // Set the cursor again starting
    // point of loading bar
    printf("\r");
    printf("\t\t");

    // Print loading bar progress
    for (int i = 0; i < 30; i++) {
        printf("%c", b);

        // Sleep for 1 second
        Sleep(120);
    }
    cout << endl;
    cout << resetANSI();

    if (endYear < startYear || startMonth > 12 || startMonth < 1 || endMonth > 12 || endMonth < 1)
    {
        cout << "Invalid input! Please try again! " << endl;
        system("pause");
        system("cls");
        StaffReport();

    }
    else
    {
        string Number;
        string Period1, Period2, StartDate, EndDate;

        Period1.append(to_string(startYear));
        Period1.append("-");
        Period1.append(to_string(startMonth));
        Period1.append("-");
        Period1.append(to_string(startDay));

        Period2.append(to_string(endYear));
        Period2.append("-");
        Period2.append(to_string(endMonth));
        Period2.append("-");
        Period2.append(to_string(endDay));

        StartDate = Period1;
        EndDate = Period2;


        string viewDonorRecordList = "SELECT s.Record_ID, d.Donor_Name, t.Donation_Date, t.Donation_Volume, h.Hospital_Name FROM donor d, blood_donation t, donor_record s , hospital h WHERE d.Donor_ID = s.Donor_ID AND t.Record_ID = s.Record_ID AND d.Donor_ID = s.Donor_ID AND h.Hospital_ID = s.Hospital_ID AND (t.Donation_Date BETWEEN '" + StartDate + "' AND '" + EndDate + "') AND t.Status = 'Completed'";
        const char* vtr = viewDonorRecordList.c_str();
        qstate = mysql_query(conn, vtr);
        if (!qstate)
        {
            res = mysql_store_result(conn);
            cout << "\nHere's the record found: " << endl;
            cout << background(Yellow) << foreground(Black) << "------------------------------------------------------------------------------------------------------------------------" << resetANSI() << endl;
            cout << background(Yellow) << foreground(Black);
            printf("| %-10s | %-50s| %-15s | %-10s | %-20s |\n", "Record", "Donor Name", "Donation Date", "Volume", "Hospital");
            cout << background(Yellow) << foreground(Black) << "------------------------------------------------------------------------------------------------------------------------" << resetANSI() << endl;

            while (row = mysql_fetch_row(res))
            {
                cout << background(White) << foreground(Black) << underline(Underline);
                printf("| %-10s | %-50s| %-15s | %-10s | %-20s |\n", row[0], row[1], row[2], row[3], row[4]);
            }
            cout << background(Black) << foreground(White) << resetANSI();
            cout << "-----------------------------------------------------------------------------------------------------------------------" << endl;
            string countGender_query = "Select SUM(case when Donation_Date BETWEEN '" + StartDate + "' AND '" + EndDate + "' then 1 else 0 end) FROM blood_donation WHERE Status = 'Completed'";
            const char* cu1 = countGender_query.c_str();
            qstate = mysql_query(conn, cu1);
            if (!qstate)
            {
                res = mysql_store_result(conn);
                if (res->row_count == 1)
                {
                    while (row = mysql_fetch_row(res))
                    {
                        Number = row[0];
                    }
                }
                else
                {
                    cout << "Execution failed! Please try again!";
                    system("pause");
                    system("cls");
                    StaffMainMenu(Staff_ID, Staff_Name);
                }
            }
            else
            {
                cout << "Execution failed! Please try again!";
                system("pause");
                system("cls");
                StaffMainMenu(Staff_ID, Staff_Name);
            }
        }
        else
        {
            cout << "Execution failed! Please try again! ";
            system("pause");
            system("cls");
            StaffMainMenu(Staff_ID, Staff_Name);
        }
        cout << background(Black) << foreground(White);
        cout << "\nThere are total " << foreground(Light_Blue) << Number << foreground(White) << " blood donations are made during " << foreground(Light_Blue) << StartDate << foreground(White) << " and " << foreground(Light_Blue) << EndDate << " ." << resetANSI() << endl;

        cout << background(Black) << foreground(White);
        system("pause");
        system("cls");
        StaffMainMenu(Staff_ID, Staff_Name);
    }

}


//donor login page
void DonorLogin()
{
    system("cls");
    string Donor_Password;
    cout << background(Light_Green) << foreground(White);
    cout << "----------------" << endl;
    cout << " LOGIN AS DONOR " << endl;
    cout << "----------------" << endl;
    cout << background(Black) << foreground(White) << resetANSI();
    cout << endl;

    cout << "Enter Donor ID: ";
    cin >> Donor_ID;
    cout << "Enter Password: ";
    char ch;
    while ((ch = _getch()) != 13)
    {
        Donor_Password += ch;
        cout << "*";
    }

    string checkUser_query = "SELECT Donor_ID, Donor_Name FROM donor WHERE Donor_ID = '" + Donor_ID + "' AND Donor_Password = sha1('" + Donor_Password + "') AND Active_Status = 'Active'";
    const char* cu = checkUser_query.c_str();
    qstate = mysql_query(conn, cu);
    if (!qstate)
    {
        res = mysql_store_result(conn);
        if (res->row_count == 1)
        {
            while (row = mysql_fetch_row(res))
            {
                Donor_ID = row[0];
                Donor_Name = row[1];
            }

            system("cls");
            DonorMainMenu(Donor_ID, Donor_Name);
        }
        else
        {
            char c;
            cout << "\nInvalid username or password. Want to try again? (Y/N): ";
            cin >> c;
            if (c == 'y' || c == 'Y')
                DonorLogin();
            else
                MainLogin();
        }
    }
    else
        cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
}

//donor main menu after successful login
void DonorMainMenu(string id, string name)
{
    char DonorMainChoice;
    system("cls");
    cout << foreground(Black) << background(Green);
    cout << "-----------------" << endl;
    cout << " DONOR MAIN MENU " << endl;
    cout << "-----------------" << endl;
    cout << background(Black) << foreground(White) << resetANSI();
    cout << "Welcome, donor " << background(Black) << foreground(Green) << name << background(Black) << foreground(White) << "!" << endl;
    cout << endl;

    cout << "[1] Self Recent Donation" << endl;
    cout << "[2] Account Information" << endl;
    cout << "[3] Back to main menu" << endl;

    cout << "Please enter your choice (1 - 3): ";
    cin >> DonorMainChoice;

    switch (DonorMainChoice)
    {
    case '1':
        system("cls");
        DonorDonation(id);

    case '2':
        system("cls");
        DonorAccount(id);
        break;

    case '3':
        system("CLS");
        main();

    default:
        cout << "Error! Invalid input! " << endl;
        system("pause");
        system("cls");
        DonorMainMenu(id, name);

    }
}

//donors can view their own donation
void DonorDonation(string id)
{
    system("cls");
    cout << foreground(Black) << background(Green);
    cout << "--------------------------" << endl;
    cout << "  RECENT DONATION RECORD  " << endl;
    cout << "--------------------------" << endl;
    cout << foreground(White) << background(Black) << resetANSI();
    cout << "\n" << endl;
    cout << "This is your donation record: \n" << endl;
    string search_query = "SELECT Donor_ID, Donor_Name FROM donor WHERE Donor_ID = '" + id + "'";
    const char* q = search_query.c_str();
    qstate = mysql_query(conn, q);
    if (!qstate)
    {
        res = mysql_store_result(conn);
        while (row = mysql_fetch_row(res))
        {
            cout << "Donor ID: " << row[0] << endl;
            cout << "Name: " << row[1] << endl;
        }
    }
    else
    {
        cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
        system("pause");
        DonorMainMenu(id, Donor_Name);
    }
    cout << "\n";

    //equijoin method to display record
    string viewDonorRecordList = "SELECT s.Record_ID, d.Donor_Name, t.Donation_Date, t.Donation_Volume, h.Hospital_Name FROM donor d, blood_donation t, donor_record s , hospital h WHERE d.Donor_ID = s.Donor_ID AND t.Record_ID = s.Record_ID AND d.Donor_ID = '" + id + "' AND h.Hospital_ID = s.Hospital_ID ";
    const char* vtr = viewDonorRecordList.c_str();
    qstate = mysql_query(conn, vtr);
    if (!qstate)
    {
        res = mysql_store_result(conn);

        cout << foreground(Black) << background(Yellow) << "-------------------------------------------------------------------------------------------------" << endl;
        printf("| %-10s | %-30s | %-15s | %-6s | %-20s |\n", "Record ID", "Name", "Date", "Volume", "Hospital");
        cout << foreground(Black) << background(Yellow) << "-------------------------------------------------------------------------------------------------";
        while (row = mysql_fetch_row(res))
        {
            cout << foreground(Black) << background(White) << underline(Underline) << endl;
            printf("| %-10s | %-30s | %-15s | %-6s | %-20s |\n", row[0], row[1], row[2], row[3], row[4]);
        }

        cout << foreground(White) << background(Black) << underline(Reset_Underline) << resetANSI();
        cout << "-------------------------------------------------------------------------------------------------" << endl;
        cout << "\n";
        system("pause");
        system("cls");
        DonorMainMenu(id, Donor_Name);
    }
    else
    {
        cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
        system("pause");
        system("cls");
        DonorMainMenu(id, Donor_Name);
    }
}

//donor own account information
void DonorAccount(string id)
{
    system("cls");
    ShowTime();
    cout << foreground(Black) << background(Green) << endl;
    cout << "===================================" << endl;
    cout << "       ACCOUNT INFORMATION         " << endl;
    cout << "===================================" << endl;
    cout << foreground(White) << background(Black) << resetANSI();
    string search_query = "SELECT Donor_ID, Donor_Name, Donor_Gender, Donor_Age, Donor_DOB, Donor_Address, Donor_BloodType, Donor_Height, Donor_Weight, Donor_TelNo FROM donor WHERE Donor_ID = '" + id + "' AND Active_Status = 'Active'";
    const char* q = search_query.c_str();
    qstate = mysql_query(conn, q);
    if (!qstate)
    {
        res = mysql_store_result(conn);
        while (row = mysql_fetch_row(res))
        {
            cout << "Donor ID: " << row[0] << endl;
            cout << "Name: " << row[1] << endl;
            cout << "Gender: " << row[2] << endl;
            cout << "Age: " << row[3] << endl;
            cout << "Date of Birth: " << row[4] << endl;
            cout << "Address: " << row[5] << endl;
            cout << "Blood Type: " << row[6] << endl;
            cout << "Height: " << row[7] << endl;
            cout << "Weight: " << row[8] << endl;
            cout << "Phone: " << row[9] << endl;
        }
        system("pause");
        system("cls");
        DonorMainMenu(id, Donor_Name);
    }
    else
    {
        cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
        system("pause");
        system("cls");
        DonorMainMenu(id, Donor_Name);
    }

}


void Registration()
{
    int userRole;
    string Staff_ID, Staff_Name, Staff_Gender, Staff_Address, Staff_Telno, Staff_Position, Staff_Password, Admin_ID, Hospital_ID;
    int Staff_Age;
    system("cls");
    cout << background(White) << foreground(Black);
    cout << "----------------------" << endl;
    cout << " ACCOUNT REGISTRATION " << endl;
    cout << "----------------------" << endl;
    cout << background(Black) << foreground(White) << resetANSI();
    cout << "Please choose which role do you want to register?" << endl;
    cout << "[1] As Admin / Staff" << endl;
    cout << "[2] As Donor" << endl;
    cout << "[3] Main Menu" << endl;
    cout << "\nYour choice (1 - 3): ";
    cin >> userRole;

    if (userRole == 1) {

        system("cls");
        cout << foreground(Black) << background(Yellow);
        cout << "------------------------------" << endl;
        cout << " NEW ADMIN/STAFF REGISTRATION " << endl;
        cout << "------------------------------" << endl;
        cout << background(Black) << foreground(White) << resetANSI();
        cout << "Please fill in the following information: " << endl;
        cout << "Name: ";
        cin.ignore(1, '\n');
        getline(cin, Staff_Name);
        cout << "Gender: ";
        getline(cin, Staff_Gender);
        cout << "Age: ";
        cin >> Staff_Age;
        cout << "Address: ";
        cin.ignore(1, '\n');
        getline(cin, Staff_Address);
        cout << "Telephone Number: ";
        getline(cin, Staff_Telno);
        cout << "Position: ";
        getline(cin, Staff_Position);
        cout << "Admin ID: ";
        getline(cin, Admin_ID);
        cout << "Hospital ID: ";
        getline(cin, Hospital_ID);

        cout << "------------------------------------------------------" << endl;
        cout << "Now please set your Staff ID and Password: " << endl;
        cout << "\n";
        cout << "Staff ID (Non-negative integer only! No characters!): ";
        int IDNum;
        cin >> IDNum;

        string StID;
        if (IDNum >= 0 && IDNum < 10)
        {
            StID.append("ST000");
            StID.append(to_string(IDNum));
        }
        else if (IDNum >= 10 && IDNum < 100)
        {

            StID.append("ST00");
            StID.append(to_string(IDNum));
        }
        else if (IDNum >= 100 && IDNum < 1000)
        {
            StID.append("ST0");
            StID.append(to_string(IDNum));
        }
        else if (IDNum >= 1000 && IDNum < 10000)
        {
            StID.append("ST");
            StID.append(to_string(IDNum));
        }
        else
        {
            cout << "Invalid Input! Non-negative Integer (0-9) is used! Please try again!";
            system("pause");
            system("cls");
            AdminControlMain();
        }

        Staff_ID = StID;

        cout << "Password: ";
        char ch1;
        while ((ch1 = _getch()) != 13) // 13 is the ASCII number for Enter
        {
            Staff_Password += ch1;
            cout << "*";
        }

        string conStaffPw;
        cout << "\nRe-enter Password: ";
        char ch2;
        while ((ch2 = _getch()) != 13) // 13 is the ASCII number for Enter
        {
            conStaffPw += ch2;
            cout << "*";
        }

        cout << "\n";
        string Active_Status = "Active";
        if (conStaffPw == Staff_Password) {

            string checkStaff_query = "SELECT * FROM staff WHERE Staff_ID = '" + Staff_ID + "' AND Active_Status = 'Active'";
            const char* cu = checkStaff_query.c_str();
            qstate = mysql_query(conn, cu);

            if (!qstate)
            {
                res = mysql_store_result(conn);
                if (res->row_count == 1)
                {
                    cout << "Username is already exist. Press Enter to Try Again...";
                    _getch();
                    Registration();
                }
                else
                {

                    string insertStaffAdmin_query = "INSERT INTO staff (Staff_ID, Staff_Name, Staff_Gender, Staff_Age, Staff_Address, Staff_Telno, Staff_Position, Staff_Password, Admin_ID, Active_Status) values ('" + Staff_ID + "', '" + Staff_Name + "', '" + Staff_Gender + "', '" + to_string(Staff_Age) + "', '" + Staff_Address + "', '" + Staff_Telno + "', '" + Staff_Position + "', sha1('" + Staff_Password + "'), '" + Admin_ID + "', '" + Active_Status + "')";

                    const char* q = insertStaffAdmin_query.c_str();
                    qstate = mysql_query(conn, q);

                    if (!qstate)
                    {
                        string insertStaff_query = "INSERT INTO staff_record (Staff_ID, Hospital_ID) values ('" + Staff_ID + "' , '" + Hospital_ID + "')";
                        const char* q = insertStaff_query.c_str();
                        qstate = mysql_query(conn, q);

                        if (!qstate)
                        {
                            cout << endl << "Done." << endl;
                            cout << endl << "A admin or staff is successful added in database." << endl;
                            cout << endl << "You have been registered. Press Enter to Continue...";
                        }
                        else
                        {
                            cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
                        }

                        system("pause");
                        main();
                    }
                    else
                    {
                        cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
                        system("pause");
                        main();
                    }
                }
            }
            else
            {
                cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
                main();
            }
        }
    }
    else if (userRole == 2)
    {
        string Donor_ID, Donor_Name, Donor_Gender, Donor_DOB, Donor_Address, Donor_BloodType, Donor_TelNo, Donor_Password;
        int Donor_Age;
        double Donor_Height, Donor_Weight;
        system("cls");
        cout << foreground(Black) << background(Yellow);
        cout << "------------------------" << endl;
        cout << " NEW DONOR REGISTRATION " << endl;
        cout << "------------------------" << endl;
        cout << background(Black) << foreground(White) << resetANSI();
        cout << "Please fill in the following information: " << endl;
        cout << "Name: ";
        cin.ignore(1, '\n');
        getline(cin, Donor_Name);
        cout << "Gender: ";
        getline(cin, Donor_Gender);

        int d_year, d_month, d_day;
        string year, month, day, DOB;

        cout << "Date of Birth (YYYY MM DD): ";
        cin >> d_year >> d_month >> d_day;

        //DOB details: convert int to string
        year = to_string(d_year);
        month = to_string(d_month);
        day = to_string(d_day);

        //DOB details: make multiple string into single string
        DOB.append(year);
        DOB.append("-");
        DOB.append(month);
        DOB.append("-");
        DOB.append(day);

        //store the copied single string into Donor_DOB to insert into database later
        Donor_DOB = DOB;

        //calculate the age
        Donor_Age = calculateAge(d_year, d_month, d_day);
        cout << "Address: ";
        cin.ignore(1, '\n');
        getline(cin, Donor_Address);
        cout << "Blood Type: ";
        getline(cin, Donor_BloodType);
        cout << "Height: ";
        cin >> Donor_Height;
        cout << "Weight: ";
        cin >> Donor_Weight;
        cout << "Telephone Number: ";
        cin >> Donor_TelNo;

        cout << "------------------------------------------------------" << endl;
        cout << "Now please set your Donor ID and password: " << endl;
        cout << "Donor ID (Non-negative integer only! No characters!):: ";
        int IDNum3;
        cin >> IDNum3;

        string DnID;
        if (IDNum3 >= 0 && IDNum3 < 10)
        {
            DnID.append("DN000");
            DnID.append(to_string(IDNum3));
        }
        else if (IDNum3 >= 10 && IDNum3 < 100)
        {

            DnID.append("DN00");
            DnID.append(to_string(IDNum3));
        }
        else if (IDNum3 >= 100 && IDNum3 < 1000)
        {
            DnID.append("DN0");
            DnID.append(to_string(IDNum3));
        }
        else if (IDNum3 >= 1000 && IDNum3 < 10000)
        {
            DnID.append("DN");
            DnID.append(to_string(IDNum3));
        }
        else
        {
            cout << "Invalid Input! Non-negative Integer (0-9) is used! Please try again!";
            system("pause");
            system("cls");
            StaffControlAdd();
        }
        Donor_ID = DnID;

        cout << "Password: ";
        char ch1;
        while ((ch1 = _getch()) != 13) // 13 is the ASCII number for Enter
        {
            Donor_Password += ch1;
            cout << "*";
        }

        cout << "\n";

        string conDonorPw;
        cout << "Re-enter Password: ";
        char ch2;
        while ((ch2 = _getch()) != 13) // 13 is the ASCII number for Enter
        {
            conDonorPw += ch2;
            cout << "*";
        }

        cout << "\n";

        if (conDonorPw == Donor_Password) {
            string checkDonor_query = "SELECT * FROM donor WHERE Donor_ID = '" + Donor_ID + "'";
            const char* cu = checkDonor_query.c_str();
            qstate = mysql_query(conn, cu);

            if (!qstate)
            {
                res = mysql_store_result(conn);
                if (res->row_count == 1)
                {
                    cout << "Username is already exist. Press Enter to Try Again...";
                    _getch();
                    Registration();
                }
                else
                {
                    string Status = "Active";
                    string insertDonor_query = "INSERT INTO donor(Donor_ID, Donor_Name, Donor_Gender, Donor_Age, Donor_DOB, Donor_Address, Donor_BloodType, Donor_Height, Donor_Weight, Donor_TelNo, Donor_Password, Active_Status) VALUES ('" + Donor_ID + "', '" + Donor_Name + "', '" + Donor_Gender + "', '" + to_string(Donor_Age) + "' , '" + Donor_DOB + "', '" + Donor_Address + "', '" + Donor_BloodType + "', '" + to_string(Donor_Height) + "',  '" + to_string(Donor_Weight) + "',  '" + Donor_TelNo + "', sha1('" + Donor_Password + "'), '" + Status + "')";

                    const char* q = insertDonor_query.c_str();
                    qstate = mysql_query(conn, q);

                    if (!qstate)
                    {
                        cout << endl << "You have been registered. Press Enter to Continue...";
                        _getch();
                        main();
                    }
                    else
                    {
                        cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
                        system("pause");
                        main();
                    }
                }
            }
            else
            {
                cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
                main();
            }
        }

    }
    else if (userRole == 3)
    {
        main();
    }
    else
    {
        cout << "Invalid Choice! Please try again! " << endl;
        system("pause");
        Registration();
    }

}

//display current time
void ShowTime()
{
    int year, month, day, hour, minute, second;
    string date, curTime;
    string morOrNight;

    //current time and date
    time_t now = time(0);
    tm* ltm = localtime(&now);

    year = 1900 + ltm->tm_year;
    month = 1 + ltm->tm_mon;
    day = ltm->tm_mday;

    hour = ltm->tm_hour;
    minute = ltm->tm_min;
    second = ltm->tm_sec;

    //determine whether it is pm(post meridiem) or am(ante meridiem)
    if (hour < 12)
    {
        morOrNight = "am";
    }
    else if (hour == 12)
    {
        morOrNight = "pm";
    }
    else if (hour > 12)
    {
        morOrNight = "pm";
        hour -= 12;
    }
    else if (hour == 24)
    {
        morOrNight = "am";
        hour = 0;
    }

    date = to_string(day) + "/" + to_string(month) + "/" + to_string(year);

    //process for display current time
    if (minute < 10)
    {
        if (second < 10)
        {
            curTime = to_string(hour) + ":0" + to_string(minute) + ":0" + to_string(second) + " " + morOrNight;
        }
        else
        {
            curTime = to_string(hour) + ":0" + to_string(minute) + ":" + to_string(second) + " " + morOrNight;
        }
    }
    else
    {
        if (second < 10)
        {
            curTime = to_string(hour) + ":" + to_string(minute) + ":0" + to_string(second) + " " + morOrNight;
        }
        else
        {
            curTime = to_string(hour) + ":" + to_string(minute) + ":" + to_string(second) + " " + morOrNight;
        }
    }

    //display Date and Time
    cout << "Date: " << date << setw(20);
    cout << "Time: " << curTime << endl;
}

//calculate age
int calculateAge(int year, int month, int day)
{
    //getting current date
    int currYear, currMonth, currDay;
    int age = 0;

    time_t now = time(0);
    tm* ltm = localtime(&now);

    currYear = 1900 + ltm->tm_year;
    currMonth = 1 + ltm->tm_mon;
    currDay = ltm->tm_mday;

    //getting the age by comparing current date and user input date
    if (currMonth < month)
        age = currYear - year;

    if (currDay < day)
        age = currYear - year - 1;
    else
        age = currYear - year;

    return age;
}

//convert string to integer
int convertToInt(string str)
{
    int num = 0, size = str.size();

    for (int i = 0, j = size; i < size; i++)
    {
        num += (str[--j] - '0') * pow(10, i); //converted integer
    }

    return num;
}

void Loading()
{
    system("cls");
    // Initialize char for printing
    // loading bar
    cout << background(Black) << foreground(Light_Blue);
    char a = 177, b = 219;

    printf("\n\n\n\n");
    cout << "\n\n\n\n\t\t\t\t\t" << "Loading...\n\n";
    printf("\t\t\t\t\t");

    // Print initial loading bar
    for (int i = 0; i < 30; i++)
        printf("%c", a);

    // Set the cursor again starting
    // point of loading bar
    printf("\r");
    printf("\t\t\t\t\t");

    // Print loading bar progress
    for (int i = 0; i < 30; i++) {
        printf("%c", b);

        // Sleep for 1 second
        Sleep(60);
    }

    cout << resetANSI();
}