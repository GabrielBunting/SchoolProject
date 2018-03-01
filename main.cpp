#include <iostream>
#include<iostream>
#include<fstream>
#include<iomanip>
#include <stdlib.h>

using namespace std;
void PrintMessage(string message, bool printTop = true, bool printBottom = true){
	if (printTop)
	{

		cout << "+---------------------------------+" << endl;
		cout << "|";
	}
	else
	{
		cout << "|";
	}
	bool front = true;
	for (int i = message.length(); i < 33; i++)
	{
		if (front)
		{
			message = " " + message;
		}
		else
		{
			message = message + " ";

		}
		front = !front;
	}
	cout << message.c_str();
	if (printBottom)
	{
		cout << "|" << endl;
		cout << "+---------------------------------+" << endl;
	}
	else
	{
		cout << "|" << endl;
	}
}


class student{
    char name[50];
    int age;

public:
    unsigned int id;
    static unsigned int id_counter;
    int reID();
    void createData();
    void showData();
    void showTable();
};

unsigned int student::id_counter = 1;

int student :: reID(){
    return id;
}

void student::createData(){
    cout << "Write Your name: ";
    cin.ignore(); cin.getline(name, 50);
    cout << "Write Your age: ";
    cin >> age;
}
void student::showData(){
    cout << "ID: " << id;
    cout << "\nName: " << name;
    cout << "\nAge: " << age;

}

void student::showTable(){
    cout << setw(15) << name << setw(4) << age << endl;
}

void createStudent();
void displayAll();
void displaybyID(int n);
void modbyID(int n);
void delbyID(int n);
void tableResult();





int main()
{
    char ch;
	int num;
	do{
        system("cls");
        PrintMessage("Edit Menu");
        PrintMessage("1. Create Student Record      ",false,false);
        PrintMessage("2. Display All Students Record",false,false);
        PrintMessage("3. Search Student Record      ",false,false);
        PrintMessage("4. Modify Student Record      ", false, false);
        PrintMessage("5. Delete Student Record      ", false, false);
        PrintMessage("6. Back to Main Menu          ", false, false);
        PrintMessage("Enter Your Choice (1-6)");
        cin >> ch;
        system("cls");
        switch (ch)
        {
        case '1':	createStudent(); break;
        case '2':	displayAll(); break;
        case '3':
		cout << "\n\n\tPlease Enter The roll number "; cin >> num;
		displaybyID(num); break;
		case '4':
		cout << "\n\n\tPlease Enter The roll number "; cin >> num;
		modbyID(num); break;
		case '5':
		cout << "\n\n\tPlease Enter The roll number "; cin >> num;
		delbyID(num); break;

        case '6':  break;
        default:	cout << "\a";
        }
	} while (ch != '6');
    return 0;
}

void createStudent(){
    student st;
    ofstream outFile;
    outFile.open("Student.dat", ios::binary | ios::app);
    st.createData();
    st.id = st.id_counter;
    st.id_counter++;
    outFile.write(reinterpret_cast<char*>(&st), sizeof(student));
    outFile.close();
    cout << "Student has been Created";
    cin.ignore(); cin.get();

}

void displayAll(){
    student st;
    ifstream inFile;
    inFile.open("Student.dat",ios::binary);
        if(!inFile){
            cout << "File couldnt be found! press any key..";
            cin.ignore(); cin.get();return;
        }
        cout << "\n\Show All Student\n";
        while (inFile.read(reinterpret_cast<char*>(&st), sizeof(student))){
            st.showData();
            cout << "\n\n=============================\n";
        }
        inFile.close(); cin.ignore(); cin.get();
}

void displaybyID(int n){
    student st;
    ifstream inFile;
    inFile.open("Student.dat", ios::binary);
    if (!inFile)
    {
        cout << "File couldnt be found! press any key..";
        return;
    }
    bool flag = false;
    while (inFile.read(reinterpret_cast<char *> (&st), sizeof(student)))
	{
		if (st.reID() == n)
		{
			st.showData();
			flag = true;
		}
	}
	inFile.close();
	if (flag == false)
		cout << "\n\nrecord not exist";
	cin.ignore();
	cin.get();
}

void modbyID(int n){
    bool found = false;
    student st;
    fstream File;
    File.open("Student.dat", ios::binary | ios::in | ios ::out);
    if (!File)
    {
        cout << "File could not be open !! Press any Key...";
		cin.ignore();
		cin.get();
		return;
    }
    while (!File.eof()&&found ==false)
    {
        File.read(reinterpret_cast<char*>(&st), sizeof(student));
        if(st.reID()==n)
        {
            st.showData();
            cout << "\n\nPlease Enter The New Details of student" << endl;
            st.createData();
			int pos = (-1)*static_cast<int>(sizeof(st));
			File.seekp(pos, ios::cur);
			File.write(reinterpret_cast<char *> (&st), sizeof(student));
			cout << "\n\n\t Record Updated";
			found = true;
        }
    }
    File.close();
	if (found == false)
		cout << "\n\n Record Not Found ";
	cin.ignore();
	cin.get();
}

void delbyID(int n){
    student st;
	ifstream inFile;
	inFile.open("Student.dat", ios::binary);
	if (!inFile)
	{
		cout << "File could not be open !! Press any Key...";
		cin.ignore();
		cin.get();
		return;
	}
	ofstream outFile;
	outFile.open("Temp.dat", ios::out);
	inFile.seekg(0, ios::beg);
	while (inFile.read(reinterpret_cast<char *> (&st), sizeof(student)))
	{
		if (st.reID() != n)
		{
			outFile.write(reinterpret_cast<char *> (&st), sizeof(student));
		}
	}
	outFile.close();
	inFile.close();
	remove("student.dat");
	rename("Temp.dat", "student.dat");
	cout << "\n\n\tRecord Deleted ..";
	cin.ignore();
	cin.get();
}


void tableResult(){
    student st;
	ifstream inFile;
	inFile.open("student.dat", ios::binary);
	if (!inFile)
	{
		cout << "File could not be open !! Press any Key...";
		cin.ignore();
		cin.get();
		return;
	}
	cout << "\n\n\t\tALL STUDENTS RESULT \n\n";
	cout << "==========================================================\n";
	cout << setw(15) << "Name" << setw(4) << "Age" << endl;
	cout << "==========================================================\n";
	while (inFile.read(reinterpret_cast<char *> (&st), sizeof(student)))
	{
		st.showTable();
	}
	cin.ignore();
	cin.get();
	inFile.close();
}


