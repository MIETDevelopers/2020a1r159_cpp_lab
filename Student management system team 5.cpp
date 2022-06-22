/*                       STUDENT REPORT MANAGEMENT SYSTEM
                              MINI PROJECT OF C++
          NAME: RISHAB JAIN, SHRIFAL RAINA, RATINDER MIET, NITISH ARORA
          ROLL NUMBER: 2020A1R159, 2020A1R177, 2020A1R166, 2020A1R197
          BRANCH: COMPUTER SCIENCE AND ENGINEERING
          SEMESTER:4TH
*/
#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

//THE CLASS THAT STORES DATA
class student
{
     int rollno;
     char name[50];
     int RDBMS_MARKS, ENTREPRENEURSHIP_MARKS, COA_MARKS, CPP_MARKS;
     double average;
     char grade;

public:
     void getdata();
     void showdata() const;
     void calculate();
     int retrollno() const;
}; //CLASS ENDS HERE

void student::calculate()
{
     average = (RDBMS_MARKS + ENTREPRENEURSHIP_MARKS + COA_MARKS + CPP_MARKS)/4.0;
     if (average >= 90)
          grade = 'A';
     else if (average >= 75)
          grade = 'B';
     else if (average >= 50)
          grade = 'C';
     else
          grade = 'F';
}

void student::getdata()
{
     cout << "\nENTER STUDENT'S ROLL NUMBER : ";
     cin >> rollno;
     cout << "\nENTER STUDENT'S NAME : ";
     cin.ignore();
     cin.getline(name, 50);
     cout << "\nALL MARKS SHOULD BE OUT OF 100";
     cout << "\nENTER MARKS IN RDBMS : ";
     cin >> RDBMS_MARKS;
     cout << "\nENTER MARKS IN ENTREPRENEURSHIP : ";
     cin >> ENTREPRENEURSHIP_MARKS;
     cout << "\nENTER MARKS IN COA : ";
     cin >> COA_MARKS;
     cout << "\nENTER MARKS IN C++ : ";
     cin >> CPP_MARKS;
     calculate();
}
void student::showdata() const
{
     cout << "\nROLL NUMBER OF STUDENT : " << rollno;
     cout << "\nNAME OF STUDENT : " << name;
     cout << "\nRDMBS : " << RDBMS_MARKS;
     cout << "\nENTREPRENEURSHIP : " << ENTREPRENEURSHIP_MARKS;
     cout << "\nCOA : " << COA_MARKS;
     cout << "\nC++ : " << CPP_MARKS;
     cout << "\nAVERAGE MARKS : " << average;
     cout << "\nGRADE OF STUDENT IS : " << grade;
}
int student::retrollno() const
{
     return rollno;
}
// FUNCTION DECLARATION
void create_student();
void display_sp(int);     // DISPLAY PARTICULAR RECORD
void display_all();       // DISPLAY ALL RECORDS
void delete_student(int); // DELETE PARTICULAR RECORD
void change_student(int); // EDIT PARTICULAR RECORD
// MAIN PROGRAM
int main()
{
     char ch;
     cout.setf(ios::fixed|ios::showpoint);
     cout << setprecision(2);//PROGRAM OUTPUTS DECIMAL NUMBER TO TWO DECIMAL PLACES
     do
     {
          int num;
          system("cls");
          cout << "\n\n\n\tMENU";
          cout << "\n\n\t1. CREATE STUDENT RECORD";
          cout << "\n\n\t2. SEARCH STUDENT RECORD";
          cout << "\n\n\t3. DISPLAY ALL STUDENT RECORDS";
          cout << "\n\n\t4. DELETE STUDENT RECORD";
          cout << "\n\n\t5. MDIFY STUDENT RECORD";
          cout << "\n\n\t6. EXIT";
          cout << "\nENTER YOUR CHOICE ::  ";
          cin >> ch;
          system("cls");
          switch (ch)
          {
          case '1':
               create_student();
               break;
          case '2':
               cout << "\n\n\tENTER THE ROLL NUMBER : ";
               cin >> num;
               display_sp(num);
               break;
          case '3':
               display_all();
               break;
          case '4':
               cout << "\n\n\tENTER THE ROLL NUMBER : ";
               cin >> num;
               delete_student(num);
               break;
          case '5':
               cout << "\n\n\tENTER THE ROLL NUMBER : ";
               cin >> num;
               change_student(num);
               break;
          case '6':
               cout << "EXITING, THANK YOU!";
               exit(0);
          }
     } while (ch != '6');
     return 0;
}//END OF MAIN FUNCION
//WRITE STUDENT DETAILS TO FILE
void create_student()
{
     student stud;
     ofstream oFile;
     oFile.open("student.dat", ios::binary | ios::app);
     stud.getdata();
     oFile.write(reinterpret_cast<char *>(&stud), sizeof(student));
     oFile.close();
     cout << "\n\nSTUDENT RECORD HAS BEEN CREATED";
     cin.ignore();
     cin.get();
}
//READ FILE RECORDS
void display_all()
{
     student stud;
     ifstream inFile;
     inFile.open("student.dat", ios::binary);
     if (!inFile)
     {
          cout << "FILE COULD NOT BE OPENED !!\nPRESS ANY KEY TO EXIT";
          inFile.close();
          cin.ignore();
          cin.get();
          return;
     }
     cout << "\n\n\n\t\tDISPLAYING ALL RECORDS\n\n";
     while (inFile.read(reinterpret_cast<char*> (&stud), sizeof(student)))
     {
          stud.showdata();
          cout << "\n\n====================================\n";
     }
     inFile.close();
     cin.ignore();
     cin.get();
}
//READ SPECIFIC RECORD BASED ON ROLL NUMBER
void display_sp(int n)
{
     student stud;
     ifstream iFile;
     iFile.open("student.dat", ios::binary);
     if (!iFile)
     {
          cout << "FILE COULD NOT BE OPENED...!!\nPRESS ANY KEY TO EXIT";
          cin.ignore();
          cin.get();
          return;
     }
     bool flag = false;
     while (iFile.read(reinterpret_cast<char *>(&stud), sizeof(student)))
     {
          if (stud.retrollno() == n)
          {
               stud.showdata();
               flag = true;
          }
     }
     iFile.close();
     if (flag == false)
          cout << "\n\nRECORD DOESN'T EXISTS";
     cin.ignore();
     cin.get();
}
//MODIFY RECORDS FOR SPECIFIED ROLL NUMBER
void change_student(int n)
{
     bool found = false;
     student stud;
     fstream fl;
     fl.open("student.dat", ios::binary | ios::in | ios::out);
     if (!fl)
     {
          cout << "FILE COULD NOT BE OPENED...\nPRESS ANY KEY TO EXIT";
          cin.ignore();
          cin.get();
          return;
     }
     while (!fl.eof() && found == false)
     {
          fl.read(reinterpret_cast<char *>(&stud), sizeof(student));
          if (stud.retrollno() == n)
          {
               stud.showdata();
               cout << "\nENTER NEW STUDENT DETAILS : " << endl;
               stud.getdata();
               int pos = (-1) * static_cast<int>(sizeof(stud));
               fl.seekp(pos, ios::cur);
               fl.write(reinterpret_cast<char *>(&stud), sizeof(student));
               cout << "\n\n\t RECORD UPDATED";
               found = true;
          }
     }
     fl.close();
     if (found == false)
          cout << "\n\n RECORD NOT FOUND ";
     cin.ignore();
     cin.get();
}
//DELETE RECORD WITH PARTICULAR ROLL NUMBER
void delete_student(int n)
{
     student stud;
     ifstream iFile;
     iFile.open("student.dat", ios::binary);
     if (!iFile)
     {
          cout << "FILE COULD NOT BE OPENED...\nPRESS ANY KEY TO EXIT";
          cin.ignore();
          cin.get();
          iFile.close();
          return;
     }
     ofstream oFile;
     oFile.open("Temp.dat", ios::out);
     iFile.seekg(0, ios::beg);
     while (iFile.read(reinterpret_cast<char *>(&stud), sizeof(student)))
     {
          if (stud.retrollno() != n)
          {
               oFile.write(reinterpret_cast<char *>(&stud), sizeof(student));
          }
     }
     oFile.close();
     iFile.close();
     remove("student.dat");
     rename("Temp.dat", "student.dat");
     cout << "\n\n\t RECORD DELETED SUCCESSFULLY";
     cin.ignore();
     cin.get();
}
//END OF PROGRAM
