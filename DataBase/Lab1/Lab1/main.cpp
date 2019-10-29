#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>

namespace Const 
{
	constexpr int DefaultCharLen = 30;
}

void clearCin()
{
	std::cout << "Incorrect input" << std::endl;
	std::cin.clear();
	while (std::cin.get() != '\n')
	{
		std::cin.ignore();
	}
}

struct Subject
{
	uint32_t id;
	char name[Const::DefaultCharLen];
	uint32_t hours;
	uint32_t credits;
	void print() const
	{
		std::cout << "id = " << id << ", name = " << name << ", hours = " << hours << ", credits = " << credits << std::endl;
	}
	void input(uint32_t UID)
	{
		std::cout << "Enter Subject Field [name][hours][credits]" << std::endl;
		id = UID;
		std::string name;
		while (!(std::cin >> name) || name.length() > Const::DefaultCharLen)
		{
			clearCin();
		}
		name += '\0';
		std::copy(name.data(), name.data() + name.length(), this->name);
		while (!(std::cin >> hours))
		{
			clearCin();
		}
		while (!(std::cin >> credits))
		{
			clearCin();
		}
	}
};

struct Group
{
	uint32_t id;
	char name[Const::DefaultCharLen];
	uint32_t amountStudents;
	void print() const
	{
		std::cout << "id = " << id << ", name = " << name << ", amountStudents = " << amountStudents << std::endl;
	}
	void input(uint32_t UID)
	{
		std::cout << "Enter Group Field [name][amountStudents]" << std::endl;
		id = UID;
		std::string name;
		while (!(std::cin >> name)||name.length()>Const::DefaultCharLen)
		{
			clearCin();
		}
		name += '\0';
		std::copy(name.data(), name.data()+name.length(),this->name);
		while (!(std::cin >> amountStudents))
		{
			clearCin();
		}
	}
};

struct Lesson
{
	uint32_t number;
	char type[Const::DefaultCharLen];
	uint32_t subjectID;
	uint32_t groupID;
	void print() const
	{
		std::cout << "subjectID = " << subjectID << ", groupID = " << groupID << ", type = " << type << ", number = " << number << std::endl;
	}
	void input(uint32_t groupID, uint32_t subjectID)
	{
		std::cout << "Enter Lesson Field [number][type]" << std::endl;
		while (!(std::cin >> number))
		{
			clearCin();
		}
		std::string type;
		while (!(std::cin >> type) || type.length() > Const::DefaultCharLen)
		{
			clearCin();
		}
		type += '\0';
		std::copy(type.data(), type.data() + type.length(), this->type);
		this->subjectID = subjectID;
		this->groupID = groupID;
	}

};

class DataBase
{
public:
	void init(const std::string& studentsFileName, const std::string& groupsFileName, const std::string& lessonsFileName);
	void printAllSubjects();
	void printAllGroups();
	void printAllLessons();
	bool get_m();
	bool get_s();
	void insert_m();
	void insert_s();
	void update_m();
	void update_s();
	void delete_m();
	void delete_s();
private:
	uint32_t subjectsCount = 0;
	uint32_t groupsCount = 0;
	uint32_t lessonsCount = 0;
	uint32_t subjectsUID = 0;
	uint32_t groupsUID = 0;
	std::fstream subjectsFile;
	std::fstream groupsFile;
	std::fstream lessonsFile;
};

void DataBase::init(const std::string& studentsFileName, const std::string& groupsFileName, const std::string& lessonsFileName)
{
	subjectsFile.open(studentsFileName);
	subjectsFile.setf(std::ios::binary);
	groupsFile.open(groupsFileName);
	groupsFile.setf(std::ios::binary);
	lessonsFile.open(lessonsFileName);
	lessonsFile.setf(std::ios::binary);
	
	Subject tempSubject;
	Group tempGroup;
	Lesson tempLesson;
	
	while (subjectsFile)
	{
		subjectsFile.read(reinterpret_cast<char*>(&tempSubject), sizeof Subject);
		if (subjectsFile)
		{
			subjectsCount++;
			if (tempSubject.id >= subjectsUID)
			{
				subjectsUID = tempSubject.id + 1;
			}
		}
	}
	while (groupsFile)
	{
		groupsFile.read(reinterpret_cast<char*>(&tempGroup), sizeof Group);
		if (groupsFile)
		{
			groupsCount++;
			if (tempGroup.id >= groupsUID)
			{
				groupsUID = tempSubject.id + 1;
			}
		}
	}
	while (lessonsFile)
	{
		lessonsFile.read(reinterpret_cast<char*>(&tempLesson), sizeof Lesson);
		if (lessonsFile)
		{
			lessonsCount++;
		}
	}

	subjectsFile.clear();
	groupsFile.clear();
	lessonsFile.clear();

}

void DataBase::printAllSubjects()
{
	if (subjectsCount == 0)
	{
		std::cout << "Subjects is empty" << std::endl;
	}
	Subject tempSubject;
	subjectsFile.seekg(0);
	while (subjectsFile)
	{
		subjectsFile.read(reinterpret_cast<char*>(&tempSubject), sizeof Subject);
		if (subjectsFile)
		{
			tempSubject.print();
		}
	}
	subjectsFile.clear();
}

void DataBase::printAllGroups()
{
	if (groupsCount == 0)
	{
		std::cout << "Groups is empty" << std::endl;
	}
	Group tempGroup;
	groupsFile.seekg(0);
	while (groupsFile)
	{
		groupsFile.read(reinterpret_cast<char*>(&tempGroup), sizeof Group);
		if (groupsFile)
		{
			tempGroup.print();
		}
	}
	groupsFile.clear();
}

void DataBase::printAllLessons()
{
	if (lessonsCount == 0)
	{
		std::cout << "Lessons is empty" << std::endl;
	}
	Lesson tempLesson;
	lessonsFile.seekg(0);
	while (lessonsFile)
	{
		lessonsFile.read(reinterpret_cast<char*>(&tempLesson), sizeof Lesson);
		if (lessonsFile)
		{
			tempLesson.print();
		}
	}
	lessonsFile.clear();
}

bool DataBase::get_m()
{
	while (true)
	{
		std::cout << "Choose table :" << std::endl << "[1] - Subjects" << std::endl << "[2] - Groups" << std::endl << "[3] - All Subjects" << std::endl << "[4] - All Groups" << std::endl << "[5] - Exit" << std::endl;
		int num = 0;
		std::cin >> num;
		switch (num)
		{
			case 1:
			{
				std::cout << "Enter table ID" << std::endl;
				uint32_t tableID = 0;
				while (!(std::cin >> tableID))
				{
					clearCin();
				}
				Subject currentRecord;
				subjectsFile.seekg(0);
				while (subjectsFile)
				{
					subjectsFile.read(reinterpret_cast<char*>(&currentRecord), sizeof Subject);
					if (currentRecord.id == tableID)
					{
						currentRecord.print();
						return true;
					}
				}
				std::cout << "Subject with this ID wasn't find" << std::endl;
				subjectsFile.clear();
				return false;
			}
			case 2:
			{
				std::cout << "Enter table ID" << std::endl;
				uint32_t tableID = 0;
				while (!(std::cin >> tableID))
				{
					clearCin();
				}
				Group currentRecord;
				groupsFile.seekg(0);
				while (groupsFile)
				{
					groupsFile.read(reinterpret_cast<char*>(&currentRecord), sizeof Group);
					if (currentRecord.id == tableID)
					{
						currentRecord.print();
						return true;
					}
				}
				std::cout << "Group with this ID wasn't find" << std::endl;
				groupsFile.clear();
				return false;
			}
			case 3:
			{
				printAllSubjects();
				break;
			}
			case 4:
			{
				printAllGroups();
				break;
			}
			case 5:
			{
				return false;
			}
			default:
			{
				clearCin();
			}
		}
	}
}

bool DataBase::get_s()
{
	if (subjectsCount == 0)
	{
		std::cout << "Enable to print Lessons, because Subjects is empty" << std::endl;
		return false;
	}
	if (groupsCount == 0)
	{
		std::cout << "Enable to print Lessons, because Groups is empty" << std::endl;
		return false;
	}

	std::cout << "Subjects :" << std::endl;
	printAllSubjects();
	std::cout << "Choose one Subject id" << std::endl;
	uint32_t subjectID = 0;
	while (!(std::cin >> subjectID))
	{
		clearCin();
	}

	std::cout << "Groups :" << std::endl;
	printAllGroups();
	std::cout << "Choose one Group id" << std::endl;
	uint32_t groupID = 0;
	while (!(std::cin >> groupID))
	{
		clearCin();
	}

	Lesson currentRecord;
	lessonsFile.seekg(0);
	bool bWasFind = false;
	while (lessonsFile)
	{
		lessonsFile.read(reinterpret_cast<char*>(&currentRecord), sizeof Lesson);
		if (lessonsFile)
		{
			if (currentRecord.groupID == groupID && currentRecord.subjectID == subjectID)
			{
				currentRecord.print();
				bWasFind = true;
			}
		}
	}
	lessonsFile.clear();
	if (!bWasFind)
	{
		std::cout << "Lesson by that params doesn't exist" << std::endl;
	}
	return bWasFind;
}

void DataBase::insert_m()
{
	bool bRepeat = true;
	while (bRepeat)
	{
		std::cout << "Choose table :" << std::endl << "[1] - Subjects" << std::endl << "[2] - Groups" << std::endl << "[3] - Exit" << std::endl;
		int num = 0;
		std::cin >> num;
		switch (num)
		{
			case 1:
			{
				Subject currentRecord;
				currentRecord.input(subjectsUID++);
				subjectsFile.seekp(subjectsCount * (sizeof Subject));
				subjectsFile.write(reinterpret_cast<char*>(&currentRecord), sizeof Subject);
				subjectsFile.flush();
				subjectsCount++;
				bRepeat = false;
				break;
			}
			case 2:
			{
				Group currentRecord;
				currentRecord.input(groupsUID++);
				groupsFile.seekp(groupsCount * (sizeof Group));
				groupsFile.write(reinterpret_cast<char*>(&currentRecord), sizeof Group);
				groupsFile.flush();
				groupsCount++;
				bRepeat = false;
				break;
			}
			case 3:
			{
				return;
			}
			default:
			{
				clearCin();
			}
		}
	}
}

void DataBase::insert_s()
{
	if (subjectsCount == 0)
	{
		std::cout << "Enable to insert Lessons, because Subjects is empty" << std::endl;
		return;
	}
	if (groupsCount == 0)
	{
		std::cout << "Enable to insert Lessons, because Groups is empty" << std::endl;
		return;
	}

	std::cout << "Subjects :" << std::endl;
	printAllSubjects();
	std::cout << "Choose one Subject id" << std::endl;
	uint32_t subjectID = 0;
	while (!(std::cin >> subjectID))
	{
		clearCin();
	}

	bool bWasFind = false;

	Subject currentSubject;
	subjectsFile.seekg(0);
	while (subjectsFile)
	{
		subjectsFile.read(reinterpret_cast<char*>(&currentSubject), sizeof Subject);
		if (currentSubject.id == subjectID)
		{
			bWasFind = true;
			break;
		}
	}
	subjectsFile.clear();
	if (!bWasFind)
	{
		std::cout << "Subject with this ID wasn't find" << std::endl;
		return;
	}

	std::cout << "Groups :" << std::endl;
	printAllGroups();
	std::cout << "Choose one Group id" << std::endl;
	uint32_t groupID = 0;
	while (!(std::cin >> groupID))
	{
		clearCin();
	}

	bWasFind = false;
	Group currentGroup;
	groupsFile.seekg(0);
	while (groupsFile)
	{
		groupsFile.read(reinterpret_cast<char*>(&currentGroup), sizeof Group);
		if (currentGroup.id == groupID)
		{
			bWasFind = true;
			break;
		}
	}
	groupsFile.clear();
	if (!bWasFind)
	{
		std::cout << "Group with this ID wasn't find" << std::endl;
		return;
	}


	Lesson currentRecord;
	currentRecord.input(groupID,subjectID);
	lessonsFile.seekp(lessonsCount * (sizeof Lesson));
	lessonsFile.write(reinterpret_cast<char*>(&currentRecord), sizeof Lesson);
	lessonsFile.flush();
	lessonsCount++;
}

void DataBase::update_m()
{
	while (true)
	{
		std::cout << "Choose table :" << std::endl << "[1] - Subjects" << std::endl << "[2] - Groups" << std::endl << "[3] - All Subjects" << std::endl << "[4] - All Groups" << std::endl << "[5] - Exit" << std::endl;
		int num = 0;
		std::cin >> num;
		switch (num)
		{
		case 1:
		{
			std::cout << "Enter table ID" << std::endl;
			uint32_t tableID = 0;
			while (!(std::cin >> tableID))
			{
				clearCin();
			}
			Subject currentRecord;
			subjectsFile.seekg(0);
			uint32_t position = 0;
			while (subjectsFile)
			{
				subjectsFile.read(reinterpret_cast<char*>(&currentRecord), sizeof Subject);
				if (currentRecord.id == tableID)
				{
					std::cout << "Input update params" << std::endl;
					currentRecord.input(currentRecord.id);
					subjectsFile.seekp(position);
					subjectsFile.write(reinterpret_cast<char*>(&currentRecord), sizeof Subject);
					return;
				}
				position += sizeof Subject;
			}
			std::cout << "Subject with this ID wasn't find" << std::endl;
			subjectsFile.clear();
			return;
		}
		case 2:
		{
			std::cout << "Enter table ID" << std::endl;
			uint32_t tableID = 0;
			while (!(std::cin >> tableID))
			{
				clearCin();
			}
			Group currentRecord;
			uint32_t position = 0;
			groupsFile.seekg(0);
			while (groupsFile)
			{
				groupsFile.read(reinterpret_cast<char*>(&currentRecord), sizeof Group);
				if (currentRecord.id == tableID)
				{
					std::cout << "Input update params" << std::endl;
					currentRecord.input(currentRecord.id);
					groupsFile.seekp(position);
					groupsFile.write(reinterpret_cast<char*>(&currentRecord), sizeof Group);
					return;
				}
				position += sizeof Group;
			}
			std::cout << "Group with this ID wasn't find" << std::endl;
			groupsFile.clear();
			return;
		}
		case 3:
		{
			printAllSubjects();
			break;
		}
		case 4:
		{
			printAllGroups();
			break;
		}
		case 5:
		{
			return;
		}
		default:
		{
			clearCin();
		}
		}
	}
}

void DataBase::update_s()
{
	if (subjectsCount == 0)
	{
		std::cout << "Enable to update Lessons, because Subjects is empty" << std::endl;
		return;
	}
	if (groupsCount == 0)
	{
		std::cout << "Enable to update Lessons, because Groups is empty" << std::endl;
		return;
	}

	std::cout << "Subjects :" << std::endl;
	printAllSubjects();
	std::cout << "Choose one Subject id" << std::endl;
	uint32_t subjectID = 0;
	while (!(std::cin >> subjectID))
	{
		clearCin();
	}

	std::cout << "Groups :" << std::endl;
	printAllGroups();
	std::cout << "Choose one Group id" << std::endl;
	uint32_t groupID = 0;
	while (!(std::cin >> groupID))
	{
		clearCin();
	}

	Lesson currentRecord;
	std::vector<std::pair<uint32_t, Lesson>> lessons;
	lessonsFile.seekg(0);
	uint32_t position = 0;
	bool bWasFind = false;
	while (lessonsFile)
	{
		lessonsFile.read(reinterpret_cast<char*>(&currentRecord), sizeof Lesson);
		if (lessonsFile)
		{
			if (currentRecord.groupID == groupID && currentRecord.subjectID == subjectID)
			{
				lessons.emplace_back(position, currentRecord);
				bWasFind = true;
			}
		}
		position += sizeof Lesson;
	}
	lessonsFile.clear();
	if (!bWasFind)
	{
		std::cout << "Lesson by that params doesn't exist" << std::endl;
		return;
	}
	std::cout << "Choose one available lesson (i)" << std::endl;
	uint32_t i = 0;
	for (;i<lessons.size();i++)
	{
		std::cout << " [i] =" << i << " ";
		lessons[i].second.print();
	}
	i = 0;
	while (!(std::cin >> i)||i >= lessons.size())
	{
		clearCin();
	}


	std::cout << "Input new params for this Lesson" << std::endl;
	currentRecord.input(groupID, subjectID);
	lessonsFile.seekp(lessons[i].first);
	lessonsFile.write(reinterpret_cast<char*>(&currentRecord), sizeof Lesson);
	lessonsFile.flush();
}

void DataBase::delete_m()
{
	while (true)
	{
		std::cout << "Choose table :" << std::endl << "[1] - Subjects" << std::endl << "[2] - Groups" << std::endl << "[3] - All Subjects" << std::endl << "[4] - All Groups" << std::endl << "[5] - Exit" << std::endl;
		int num = 0;
		std::cin >> num;
		switch (num)
		{
		case 1:
		{
			std::cout << "Enter table ID" << std::endl;
			uint32_t tableID = 0;
			while (!(std::cin >> tableID))
			{
				clearCin();
			}
			Subject currentRecord;
			subjectsFile.seekg(0);
			std::fstream tempFile;
			tempFile.open("temp.bin");
			tempFile.setf(std::ios::binary);
			tempFile.seekp(0);
			bool bWasFind = false;
			while (subjectsFile)
			{
				subjectsFile.read(reinterpret_cast<char*>(&currentRecord), sizeof Subject);
				if (subjectsFile)
				{
					if (currentRecord.id != tableID)
					{
						tempFile.write(reinterpret_cast<char*>(&currentRecord), sizeof Subject);
					}
					else
					{
						bWasFind = true;
					}
				}
			}
			subjectsFile.clear();
			if (bWasFind)
			{
				// TODO
				subjectsCount--;
				subjectsFile.swap(tempFile);
			}
			else
			{
				std::cout << "Subject with this ID wasn't find" << std::endl;
			}
			return;
		}
		case 2:
		{
			std::cout << "Enter table ID" << std::endl;
			uint32_t tableID = 0;
			while (!(std::cin >> tableID))
			{
				clearCin();
			}
			Group currentRecord;
			groupsFile.seekg(0);
			std::fstream tempFile;
			tempFile.open("temp.bin");
			tempFile.setf(std::ios::binary);
			tempFile.seekp(0);
			bool bWasFind = false;
			while (groupsFile)
			{
				groupsFile.read(reinterpret_cast<char*>(&currentRecord), sizeof Group);
				if (groupsFile)
				{
					if (currentRecord.id != tableID)
					{
						tempFile.write(reinterpret_cast<char*>(&currentRecord), sizeof Group);
					}
					else
					{
						bWasFind = true;
					}
				}
			}
			groupsFile.clear();
			if (bWasFind)
			{
				// TODO
				groupsCount--;
				groupsFile.swap(tempFile);
			}
			else
			{
				std::cout << "Group with this ID wasn't find" << std::endl;
			}
			return;
		}
		case 3:
		{
			printAllSubjects();
			break;
		}
		case 4:
		{
			printAllGroups();
			break;
		}
		case 5:
		{
			return;
		}
		default:
		{
			clearCin();
		}
		}
	}
}

void DataBase::delete_s()
{
	if (subjectsCount == 0)
	{
		std::cout << "Enable to update Lessons, because Subjects is empty" << std::endl;
		return;
	}
	if (groupsCount == 0)
	{
		std::cout << "Enable to update Lessons, because Groups is empty" << std::endl;
		return;
	}

	std::cout << "Subjects :" << std::endl;
	printAllSubjects();
	std::cout << "Choose one Subject id" << std::endl;
	uint32_t subjectID = 0;
	while (!(std::cin >> subjectID))
	{
		clearCin();
	}

	std::cout << "Groups :" << std::endl;
	printAllGroups();
	std::cout << "Choose one Group id" << std::endl;
	uint32_t groupID = 0;
	while (!(std::cin >> groupID))
	{
		clearCin();
	}

	Lesson currentRecord;
	std::vector<std::pair<uint32_t, Lesson>> lessons;
	lessonsFile.seekg(0);
	uint32_t position = 0;
	bool bWasFind = false;
	while (lessonsFile)
	{
		lessonsFile.read(reinterpret_cast<char*>(&currentRecord), sizeof Lesson);
		if (lessonsFile)
		{
			if (currentRecord.groupID == groupID && currentRecord.subjectID == subjectID)
			{
				lessons.emplace_back(position, currentRecord);
				bWasFind = true;
			}
		}
		position += sizeof Lesson;
	}
	lessonsFile.clear();
	if (!bWasFind)
	{
		std::cout << "Lesson by that params doesn't exist" << std::endl;
		return;
	}
	std::cout << "Choose one available lesson (i)" << std::endl;
	uint32_t i = 0;
	for (; i < lessons.size(); i++)
	{
		std::cout << " [i] =" << i << " ";
		lessons[i].second.print();
	}
	i = 0;
	while (!(std::cin >> i) || i >= lessons.size())
	{
		clearCin();
	}
	std::fstream tempFile;
	tempFile.open("temp.bin");
	tempFile.setf(std::ios::binary);
	tempFile.seekp(0);

	lessonsFile.seekg(0);
	position = 0;
	bWasFind = false;
	while (lessonsFile)
	{
		lessonsFile.read(reinterpret_cast<char*>(&currentRecord), sizeof Lesson);
		if (position != lessons[i].first)
		{
			tempFile.write(reinterpret_cast<char*>(&currentRecord), sizeof Lesson);
		}
		else
		{
			bWasFind = true;
		}
	}
	lessonsFile.clear();
	if (!bWasFind)
	{
		std::cout << "Input new params for this Lesson" << std::endl;
	}
	else
	{
		// TODO
		lessonsFile.swap(tempFile);
		lessonsCount--;
	}
}

int main()
{
	DataBase dataBase;
	dataBase.init("subjects.bin", "groups.bin", "lessons.bin");

	while (true)
	{
		int input = 0;
		std::cout << "Choose option:\n[1] - get_m\n[2] - insert_m\n[3] - update_m\n[4] - delete_m\n[5] - get_s\n[6] - insert_s\n[7] - update_s\n[8] - delete_s" << std::endl << "[9] - PrintAllSubjects\n[10] - PrintAllGroups\n[11] - PrintAllLessons\n[12] - Exit" << std::endl;
		std::cin >> input;
		switch (input)
		{
			case 1:
			{
				system("cls");
				dataBase.get_m();
				break;
			}
			case 2:
			{
				system("cls");
				dataBase.insert_m();
				break;
			}
			case 3:
			{
				system("cls");
				dataBase.update_m();
				break;
			}
			case 4:
			{
				system("cls");
				dataBase.delete_m();
				break;
			}
			case 5:
			{
				system("cls");
				dataBase.get_s();
				break;
			}
			case 6:
			{
				system("cls");
				dataBase.insert_s();
				break;
			}
			case 7:
			{
				system("cls");
				dataBase.update_s();
				break;
			}
			case 8:
			{
				system("cls");
				dataBase.delete_s();
				break;
			}
			case 9:
			{
				system("cls");
				dataBase.printAllSubjects();
				break;
			}
			case 10:
			{
				system("cls");
				dataBase.printAllGroups();
				break;
			}
			case 11:
			{
				system("cls");
				dataBase.printAllLessons();
				break;
			}
			case 12:
			{
				system("cls");
				return 0;
			}
			default:
			{
				clearCin();
			}
		}
	}
}