#include <iostream>
#include<iostream>
#include<fstream>
#include<iomanip>

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
    void createData();
    void showData();
    void showTable();
};

void student::createData(){
    cout << "Write Your name: ";
    cin.ignore(); cin.getline(name, 50);
    cout << "Write Your age: ";
    cin >> age;
}
void student::showData(){
    cout << "Your name is: " << name;
    cout << "Your age is" << age;

}

void student::showTable(){
    cout << setw(15) << name << setw(4) << age << endl;
}

void createStudent();
void displayAll();
/*void displaybyID();
void modbyID();
void delbyID();*/
void tableResult();
void menu();




int main()
{
    return 0;
}

void createStudent(){
    student st;
    ofstream outFile;
    outFile.open("Student.dat", ios::binary | ios::app);
    st.createData();
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
        cout << "\n\Show All Student";
        while (inFile.read(reinterpret_cast<char*>(&st), sizeof(student))){
            st.showData();
            cout << "\n\n=============================\n";
        }
        inFile.close(); cin.ignore(); cin.get();
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

void menu(){
	char ch;
	int num;
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
	case '1':	Create_Student(); break;
	case '2':	Display_All(); break;

	case '6':	break;
	default:	cout << "\a"; menu();
	}
}


