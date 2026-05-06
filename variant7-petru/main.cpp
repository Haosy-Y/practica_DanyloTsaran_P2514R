#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

struct Group {
	string gr_num;
	string spec;
	int disciplines = 0;
};
struct Student {
	string name;
	string surname;
	string gr_num;
	vector<int> notes{};
	int absence{};
};
struct GroupInfo {
	string gr_num;
	int studentCount{};
	float avgNotes{};
	int absencesCount{};
};

void ReadGroups(vector<Group>& groups);
void ReadStudents(vector<Student>& students, vector<Group>& groups);
void DisplayGroups(vector<Group>& groups);
void DisplayStudents(vector<Student>& students);
void WriteGroups(vector<Group>& groups);
void WriteStudents(vector<Student>& students);
void DeleteExtraStudents(vector<Student>& students, vector<Group>& groups);
void AddGroup(vector<Group>& groups);
void AddStudent(vector<Student>& students, vector<Group>& groups);
void DeleteGroup(vector<Group>& groups, vector<Student>& students);
void DeleteStudent(vector<Student>& students);
void ModifyGroup(vector<Group>& groups);
void ModifyStudent(vector<Student>& students, vector<Group>& groups);
void DisplayStudentInfo(Student student);
void FindMaxAbsencesStudent(vector<Student>& students);
float CountStudentAverage(Student student);
void DisplayStudentsAverageFromGroup(vector<Student>& students, string groupNum);
vector<Student> FindStudentFromGroup(vector<Student>& students, vector<Group>& groups, string groupName);
void UpdateGeneralInfo(vector<Group>& groups, vector<Student>& students, vector<GroupInfo>& groupInfos);
void WriteGeneralInfo(vector<GroupInfo>& groupInfos);

bool cycle = true;
string menu {
	"========================================\n"
	"        STUDENT MANAGEMENT SYSTEM       \n"
	"========================================\n\n"
	"Please select an option:\n\n"
	"[1] Display information\n"
	"[2] Add new element\n"
	"[3] Delete element\n"
	"[4] Modify Element\n"
	"[5] Update Count.txt\n"
	"[0] Exit\n\n"
	"----------------------------------------\n"
	"Enter your choice: " };

void ShowMenu(vector<Student>& students, vector<Group>& groups, vector<GroupInfo>& groupInfos) {
	cout << menu;
	char choice; cin >> choice;
	switch (choice) {
		case '0':
		{
			cycle = false;
			break;
		}
		case '1':
		{
			cout << "\nWhat do you want to display?"
					"\n[1] All Groups\n"
					"[2] All Students\n"
					"[3] Students From a group\n"
					"[4] Student with maximum absences\n"
					"[5] Students average from a group"
					"\n\nEnter your choice : ";

			char displayChoice; cin >> displayChoice;
			switch (displayChoice)
			{
				case '1':
				{
					DisplayGroups(groups);
					break;
				}
				case '2':
				{
					DisplayStudents(students);
					break;
				}
				case '3':
				{
					cout << "Enter group number: "; 
					string groupNum; cin >> groupNum;
					vector<Student> studentsFromGroup = FindStudentFromGroup(students, groups, groupNum);
					DisplayStudents(studentsFromGroup);
					break;
				}
				case '4': {
					FindMaxAbsencesStudent(students);
					break;
				}
				case '5': {
					string groupNum;
					cout << "Enter group number: "; cin >> groupNum;
					DisplayStudentsAverageFromGroup(students, groupNum);
					break;
				}
			}
			break;
		}
		case '2':
		{
			cout << "What do you want to add? \n[1] Group\t[2] Student\nEnter your choice: ";
			char addChoice; cin >> addChoice;
			switch (addChoice)
			{
				case '1':
				{
					AddGroup(groups);
					break;
				}
				case '2':
				{
					AddStudent(students, groups);
					break;
				}
			}
			break;
		}
		case '3':
		{
			cout << "What do you want to delete? \n[1] Group\t[2] Student\nEnter your choice: ";
			char deleteChoice; cin >> deleteChoice;
			switch (deleteChoice)
			{
				case '1':
				{
					DeleteGroup(groups, students);
					break;
				}
				case '2':
				{
					DeleteStudent(students);
					break;
				}
			}
			break;
		}
		case '4':
		{
			cout << "What do you want to modify? \n[1] Group\t[2] Student\nEnter your choice: ";
			char modifyChoice; cin >> modifyChoice;
			switch (modifyChoice)
			{
				case '1':
				{
					ModifyGroup(groups);
					break;
				}
				case '2':
				{
					ModifyStudent(students, groups);
					break;
				}
			}
			break;
		}
		case '5': {
			UpdateGeneralInfo(groups, students, groupInfos);
			WriteGeneralInfo(groupInfos);
			cout << "\n Count.txt updated\n";
			break;
		}
	}
}
		
void DisplayGroups(vector<Group>& groups) {
	cout << "\nGROUPS LIST:\n\n";
	for (int i = 0; i < groups.size(); i++)
	{
		cout << groups[i].gr_num << "\t" << groups[i].spec << "\t" << groups[i].disciplines << '\n';
	}
}
void DisplayStudents(vector<Student>& students) {
	if (students.empty())
		return;
	cout << "\nSTUDENTS LIST:\n\n";
	for (int i = 0; i < students.size(); i++)
	{
		DisplayStudentInfo(students[i]);
	}
}
void DisplayStudentInfo(Student student) {
	cout << student.name << ' ' << student.surname << '\t' << student.gr_num << '\t';
	for (int j = 0; j < student.notes.size(); j++)
	{
		cout << student.notes[j] << ' ';
	}
	cout << '\t' << student.absence << endl;
}
void DisplayStudentsAverageFromGroup(vector<Student>& students, string groupNum) {
	cout << "\nSTUDENTS AVERAGE FROM GROUP " << groupNum << ":\n\n";
	bool isFound = false;
	for (int i = 0; i < students.size(); i++)
	{
		if (students[i].gr_num == groupNum)
		{
			isFound = true;
			cout << students[i].name << ' ' << students[i].surname << "\tAverage: " << CountStudentAverage(students[i]) << endl;
		}
	}
	if (!isFound)
		cout << "No students found from group " << groupNum << endl;
}
void FindMaxAbsencesStudent(vector<Student>& students) {
	if (students.size() == 0) {
		cout << "No students available!" << endl;
		return;
	}
	Student maxAbsenceStudent = students[0];
	for (int i = 1; i < students.size(); i++)
	{
		if (students[i].absence > maxAbsenceStudent.absence)
			maxAbsenceStudent = students[i];
	}
	cout << "Student with maximum absences: ";
	DisplayStudentInfo(maxAbsenceStudent);
}


vector<Student> FindStudentFromGroup(vector<Student>& students, vector<Group>& groups, string groupName) {
	vector<Student> studentsFromGroup;
	for (int j = 0; j < students.size(); j++)
		if (students[j].gr_num == groupName)
			studentsFromGroup.push_back(students[j]);
	
	if (studentsFromGroup.size() == 0)
		cout << "No students found from group " << groupName << endl;
	
	return studentsFromGroup;
}


float CountStudentAverage(Student student) {
	float average = 0;
	for (int j = 0; j < student.notes.size(); j++)
	{
		average += student.notes[j];
	}
	if(student.notes.size() != 0) average /= (float)student.notes.size();
	return average;
}

void AddGroup(vector<Group>& groups) {
	Group newGroup;
	cout << "Enter group number: "; cin >> newGroup.gr_num;
	bool groupfound = false;
	for (int i = 0; i < groups.size(); i++)
	{
		if (newGroup.gr_num == groups[i].gr_num) {
			cout << "Group with this number already exists: " << groups[i].gr_num << '\t' << groups[i].spec << '\t' << groups[i].disciplines << endl;
			groupfound = true;
		}
	}
	if (groupfound)
		return;
	cout << "Enter specialization: "; cin >> newGroup.spec;
	cout << "Enter number of disciplines: "; cin >> newGroup.disciplines;
	cout << newGroup.gr_num << "\t" << newGroup.spec << "\t" << newGroup.disciplines << " -- added";
	groups.push_back(newGroup);
	WriteGroups(groups);
}
void AddStudent(vector<Student>& students, vector<Group>& groups) {
	Student newStudent;
	cout << "Enter student name: "; cin >> newStudent.name;
	cout << "Enter student surname: "; cin >> newStudent.surname;
	cout << "Enter group number: "; cin >> newStudent.gr_num;
	bool groupFound = false;
	for (int i = 0; i < groups.size(); i++)
	{
		if (newStudent.gr_num == groups[i].gr_num)
		{
			groupFound = true;
			newStudent.notes.resize(groups[i].disciplines);
			for (int j = 0; j < groups[i].disciplines; j++)
			{
				cout << "Enter note for discipline " << j + 1 << ": ";
				cin >> newStudent.notes[j];
			}
			cout << "Enter number of absences: "; cin >> newStudent.absence;
			break;
		}
	}
	if (!groupFound) {
		cout << "Invalid student group: " << newStudent.gr_num << endl;
		return;
	}
	cout << newStudent.name << ' ' << newStudent.surname << '\t' << newStudent.gr_num << '\t';
	for (int j = 0; j < newStudent.notes.size(); j++)
		cout << newStudent.notes[j] << ' ';
	cout << '\t' << newStudent.absence << " -- added";
	students.push_back(newStudent);
	WriteStudents(students);
}
void DeleteGroup(vector<Group>& groups, vector<Student>& students) {
	string groupNum;
	cout << "Enter group number to delete: "; cin >> groupNum;
	bool groupFound = false;
	for (int i = 0; i < groups.size(); i++)
	{
		if (groups[i].gr_num == groupNum)
		{
			groupFound = true;
			groups.erase(groups.begin() + i);
			WriteGroups(groups);
			break;
		}
	}
	if (!groupFound) {
		cout << "Group not found: " << groupNum << endl;
		return;
	}
	cout << "Group " << groupNum << " deleted. Deleting students from this group..." << endl;
	DeleteExtraStudents(students, groups);
}
void DeleteStudent(vector<Student>& students) {
	string studentName, studentSurname;
	cout << "Enter student name to delete: "; cin >> studentName;
	cout << "Enter student surname to delete: "; cin >> studentSurname;
	bool studentFound = false;
	for (int i = 0; i < students.size(); i++)
	{
		if (students[i].name == studentName && students[i].surname == studentSurname)
		{
			studentFound = true;
			students.erase(students.begin() + i);
			WriteStudents(students);
			break;
		}
	}
	if (!studentFound) {
		cout << "Student not found: " << studentName << ' ' << studentSurname << endl;
		return;
	}
	cout << "Student " << studentName << ' ' << studentSurname << " deleted." << endl;
}
void ModifyGroup(vector<Group>& groups) {
	string groupNum;
	cout << "Enter group number to modify: "; cin >> groupNum;

	bool groupFound = false;

	for (int i = 0; i < groups.size(); i++)
	{
		if (groups[i].gr_num == groupNum)
		{
			groupFound = true;

			bool cycl = true;
			while (cycl) {
				cout << "Choose what to modify: \n[1] Specialization\t[2] Number of disciplines\t[0] Save and exit\nEnter your choice: ";
				char modifyChoice; cin >> modifyChoice;
				switch (modifyChoice) {
					case '1':
				{
					cout << "Enter new specialization: "; cin >> groups[i].spec;
					break;
				}
					case '2':
				{
					cout << "Enter new number of disciplines: "; cin >> groups[i].disciplines;
					break;
				}
					case '0':
					{
						cout << groups[i].gr_num << "\t" << groups[i].spec << "\t" << groups[i].disciplines << " -- saved";
						cycl = false;
						break;
					}
				}
			}
			WriteGroups(groups);
			break;
		}
	}
	if (!groupFound) {
		cout << "Group not found: " << groupNum << endl;
		return;
	}
	cout << "Group " << groupNum << " modified. It is recommended to check students from this group for correct number of notes." << endl;
}
void ModifyStudent(vector<Student>& students, vector<Group>& groups) {
	string studentName, studentSurname;
	cout << "Enter student name to modify: "; cin >> studentName;
	cout << "Enter student surname to modify: "; cin >> studentSurname;
	bool studentFound = false;

	for (int i = 0; i < students.size(); i++)
	{
		if (students[i].name == studentName && students[i].surname == studentSurname)
		{
			studentFound = true;
			bool cycl = true;
			while (cycl) {
				cout << "Choose what to modify: \n[1] Group number\t[2] Notes\t[3] Absences\t[0] Save and exit\nEnter your choice: ";
				char modifyChoice; cin >> modifyChoice;
				switch (modifyChoice)
				{
				case '1':
				{
					cout << "Enter new group number: "; cin >> students[i].gr_num;
					bool groupFound = false;
					for (int j = 0; j < groups.size(); j++)
					{
						if (students[i].gr_num == groups[j].gr_num)
						{
							groupFound = true;
							students[i].notes.resize(groups[j].disciplines);
							cout << "It is recommended to change the student's notes";
							break;
						}
					}
					if (!groupFound) {
						cout << "Invalid group: " << students[i].gr_num << endl;
						break;
					}
					break;
				}
				case '2':
				{
					cout << "Which modification do you want to make? \n[1] Change all notes\t[2] Change note for specific discipline\nEnter your choice: ";
					char noteModifyChoice; cin >> noteModifyChoice;
					switch (noteModifyChoice)
					{
					case '1':
					{
						for (int j = 0; j < students[i].notes.size(); j++)
						{
							cout << "Enter new note for discipline " << j + 1 << ": ";
							cin >> students[i].notes[j];
						}
						break;
					}
					case '2':
					{
						cout << "Which discipline's notes do you want to change? Enter discipline number (1 - " << students[i].notes.size() << ") : ";
						int discNum; cin >> discNum; discNum--;
						if (discNum < 0 || discNum >= students[i].notes.size())
							cout << "Invalid discipline number!" << endl;
						else
						{
							cout << "Enter new note for discipline " << discNum + 1 << ": ";
							cin >> students[i].notes[discNum];
						}
						break;
					}
					}
					break;
				}
				case '3':
				{
					cout << "Enter new number of absences: "; cin >> students[i].absence;
					break;
				}
				case '0':
				{
					cout << students[i].name << ' ' << students[i].surname << '\t' << students[i].gr_num << '\t';
					for (int j = 0; j < students[i].notes.size(); j++)
						cout << students[i].notes[j] << ' ';

					cout << '\t' << students[i].absence << "\t--\tsaved";
					cycl = false;
					break;
				}
				}
			}
			WriteStudents(students);
			break;
		}
	}
	if (!studentFound)
		cout << "Student not found: " << studentName << ' ' << studentSurname << endl;
}


void ReadGroups(vector<Group>& groups) {
	groups.clear();

	ifstream gr("Group.txt");
	if (!gr.is_open()) {
		cout << "Error opening file!" << endl;
		return;
	}
	Group g;
	while (gr >> g.gr_num >> g.spec >> g.disciplines) 
		groups.push_back(g);

	gr.close();
}
void ReadStudents(vector<Student>& students, vector<Group>& groups) {
	students.clear();

	ifstream st("Student.txt");
	if (!st.is_open()) {
		cout << "Error opening file!" << endl;
		return;
	}
	Student s;
	bool isValid = true;
	while (st >> s.name >> s.surname >> s.gr_num) {
		bool groupFound = false;
		for (int i = 0; i < groups.size(); i++)
		{
			if (s.gr_num == groups[i].gr_num)
			{
				groupFound = true;

				s.notes.resize(groups[i].disciplines);

				for (int j = 0; j < groups[i].disciplines; j++)
					st >> s.notes[j];

				st >> s.absence;
				break;
			}
		}
		if (!groupFound) {
			cout << "Invalid student found in file\n";
			isValid = false;
			continue;
		}

		students.push_back(s);
	}
	if (!isValid) {
		cout << "[Any] Ignore\t[1] Delete\n";
		char choice; cin >> choice;
		if (choice == '1')
			DeleteExtraStudents(students, groups);
		else
			cout << "This student will be ignored. Please check the file for errors." << endl;

	}
	st.close();
}
void WriteGroups(vector<Group>& groups) {
	ofstream gr("Group.txt");
	if (!gr.is_open()) {
		cout << "Error opening file!" << endl;
		return;
	}
	for (int i = 0; i < groups.size(); i++)
	{
		gr << groups[i].gr_num << ' ' << groups[i].spec << ' ' << groups[i].disciplines << '\n';
	}
	gr.close();
}
void WriteStudents(vector<Student>& students) {
	ofstream st("Student.txt");
	if (!st.is_open()) {
		cout << "Error opening file!" << endl;
		return;
	}
	for (int i = 0; i < students.size(); i++)
	{
		st << students[i].name << ' ' << students[i].surname << ' ' << students[i].gr_num << ' ';
		for (int j = 0; j < students[i].notes.size(); j++)
		{
			st << students[i].notes[j] << ' ';
		}
		st << '\t' << students[i].absence << '\n';
	}
	st.close();
}

void UpdateGeneralInfo(vector<Group>& groups, vector<Student>& students, vector<GroupInfo>& groupInfos) {
	groupInfos.clear();
	GroupInfo gi;
	for (int i = 0; i < groups.size(); i++)
	{
		gi.gr_num = groups[i].gr_num;
		gi.studentCount = 0;
		gi.avgNotes = 0;
		gi.absencesCount = 0;
		for (int j = 0; j < students.size(); j++)
		{
			if (students[j].gr_num == groups[i].gr_num)
			{
				gi.studentCount++;
				gi.avgNotes += CountStudentAverage(students[j]);
				gi.absencesCount += students[j].absence;
			}
		}
		if (gi.studentCount > 0)
			gi.avgNotes /= gi.studentCount;
		
		groupInfos.push_back(gi);
	}
}
void WriteGeneralInfo(vector<GroupInfo>& groupInfos) {
	ofstream co("Count.txt");
	if (!co.is_open()) {
		cout << "Error opening file!" << endl;
		return;
	}
	for (int i = 0; i < groupInfos.size(); i++)
	{
		co << groupInfos[i].gr_num << '\t' << groupInfos[i].studentCount << '\t' << groupInfos[i].avgNotes << '\t' << groupInfos[i].absencesCount << '\n';
	}
	co.close();
}



void DeleteExtraStudents(vector<Student>& students, vector<Group>& groups) {
	for (int i = 0; i < students.size(); i++)
	{
		bool isFound = false;
		for (int j = 0; j < groups.size(); j++)
		{
			if(students[i].gr_num == groups[j].gr_num)
			{
				isFound = true;
				break;
			}
		}
		if (!isFound) {
			cout << "Deleting student " << students[i].name << ' ' << students[i].surname << " " << students[i].gr_num << endl;
			students.erase(students.begin() + i);
			i--;
		}
	}
	WriteStudents(students);
}


int main()
{
	vector<Group> groups;
	vector<Student> students;
	vector<GroupInfo> groupInfos;

	ReadGroups(groups);
	ReadStudents(students, groups);

	while (cycle) {
		ShowMenu(students, groups, groupInfos);
		menu = "\n[1] Display information\t"
			"[2] Add new element\t"
			"[3] Delete element\t"
			"[4] Modify Element\n"
			"[5] Update Count.txt\t"
			"[0] Exit\n\n"
			"Enter your choice: ";
	}
}
