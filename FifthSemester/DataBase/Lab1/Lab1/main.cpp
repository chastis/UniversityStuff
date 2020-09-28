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

struct Detail
{
	uint32_t id;
	uint32_t amount;
	uint32_t difficult;
	char name[Const::DefaultCharLen];
	void print() const
	{
		std::cout << "id = " << id << ", name = " << name << ", amount = " << amount << ", difficult = " << difficult << std::endl;
	}
	void input(uint32_t UID)
	{
		std::cout << "Enter Detail Field [name][amount][difficult]" << std::endl;
		id = UID;
		std::string name;
		while (!(std::cin >> name) || name.length() > Const::DefaultCharLen)
		{
			clearCin();
		}
		name += '\0';
		std::copy(name.data(), name.data() + name.length(), this->name);
		while (!(std::cin >> amount))
		{
			clearCin();
		}
		while (!(std::cin >> difficult))
		{
			clearCin();
		}
	}
};

struct Supplier
{
	uint32_t id;
	char name[Const::DefaultCharLen];
	uint32_t age;
	void print() const
	{
		std::cout << "id = " << id << ", name = " << name << ", age = " << age << std::endl;
	}
	void input(uint32_t UID)
	{
		std::cout << "Enter Supplier Field [name][age]" << std::endl;
		id = UID;
		std::string name;
		while (!(std::cin >> name)||name.length()>Const::DefaultCharLen)
		{
			clearCin();
		}
		name += '\0';
		std::copy(name.data(), name.data()+name.length(),this->name);
		while (!(std::cin >> age))
		{
			clearCin();
		}
	}
};

struct Supplement
{
	uint32_t number;
	char name[Const::DefaultCharLen];
	uint32_t detailID;
	uint32_t supplierID;
	void print() const
	{
		std::cout << "detailID = " << detailID << ", supplierID = " << supplierID << ", name = " << name << ", number = " << number << std::endl;
	}
	void input(uint32_t SupplementID, uint32_t DetailID)
	{
		std::cout << "Enter Supplement Field [number][name]" << std::endl;
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
		std::copy(type.data(), type.data() + type.length(), this->name);
		this->detailID = DetailID;
		this->supplierID = SupplementID;
	}

};

class DataBase
{
public:
	void init(const std::string& studentsFileName, const std::string& SupplementsFileName, const std::string& SuppliersFileName);
	void printAllDetails();
	void printAllSupplements();
	void printAllSuppliers();
	bool get_m();
	bool get_s();
	void insert_m();
	void insert_s();
	void update_m();
	void update_s();
	void delete_m();
	void delete_s();
private:
	uint32_t DetailsCount = 0;
	uint32_t SupplementsCount = 0;
	uint32_t SuppliersCount = 0;
	uint32_t DetailsUID = 0;
	uint32_t SupplementsUID = 0;
	std::fstream DetailsFile;
	std::fstream SupplementsFile;
	std::fstream SuppliersFile;
};

void DataBase::init(const std::string& studentsFileName, const std::string& SupplementsFileName, const std::string& SuppliersFileName)
{
	DetailsFile.open(studentsFileName);
	DetailsFile.setf(std::ios::binary);
	SupplementsFile.open(SupplementsFileName);
	SupplementsFile.setf(std::ios::binary);
	SuppliersFile.open(SuppliersFileName);
	SuppliersFile.setf(std::ios::binary);
	
	Detail tempDetail;
	Supplier tempSupplement;
	Supplement tempSupplier;
	
	while (DetailsFile)
	{
		DetailsFile.read(reinterpret_cast<char*>(&tempDetail), sizeof Detail);
		if (DetailsFile)
		{
			DetailsCount++;
			if (tempDetail.id >= DetailsUID)
			{
				DetailsUID = tempDetail.id + 1;
			}
		}
	}
	while (SupplementsFile)
	{
		SupplementsFile.read(reinterpret_cast<char*>(&tempSupplement), sizeof Supplier);
		if (SupplementsFile)
		{
			SupplementsCount++;
			if (tempSupplement.id >= SupplementsUID)
			{
				SupplementsUID = tempSupplement.id + 1;
			}
		}
	}
	while (SuppliersFile)
	{
		SuppliersFile.read(reinterpret_cast<char*>(&tempSupplier), sizeof Supplement);
		if (SuppliersFile)
		{
			SuppliersCount++;
		}
	}

	DetailsFile.clear();
	SupplementsFile.clear();
	SuppliersFile.clear();

}

void DataBase::printAllDetails()
{
	if (DetailsCount == 0)
	{
		std::cout << "Details is empty" << std::endl;
	}
	Detail tempDetail;
	DetailsFile.seekg(0);
	while (DetailsFile)
	{
		DetailsFile.read(reinterpret_cast<char*>(&tempDetail), sizeof Detail);
		if (DetailsFile)
		{
			tempDetail.print();
		}
	}
	DetailsFile.clear();
}

void DataBase::printAllSupplements()
{
	if (SupplementsCount == 0)
	{
		std::cout << "Supplements is empty" << std::endl;
	}
	Supplier tempSupplement;
	SupplementsFile.seekg(0);
	while (SupplementsFile)
	{
		SupplementsFile.read(reinterpret_cast<char*>(&tempSupplement), sizeof Supplier);
		if (SupplementsFile)
		{
			tempSupplement.print();
		}
	}
	SupplementsFile.clear();
}

void DataBase::printAllSuppliers()
{
	if (SuppliersCount == 0)
	{
		std::cout << "Suppliers is empty" << std::endl;
	}
	Supplement tempSupplier;
	SuppliersFile.seekg(0);
	while (SuppliersFile)
	{
		SuppliersFile.read(reinterpret_cast<char*>(&tempSupplier), sizeof Supplement);
		if (SuppliersFile)
		{
			tempSupplier.print();
		}
	}
	SuppliersFile.clear();
}

bool DataBase::get_m()
{
	while (true)
	{
		std::cout << "Choose table :" << std::endl << "[1] - Details" << std::endl << "[2] - Supplements" << std::endl << "[3] - All Details" << std::endl << "[4] - All Supplements" << std::endl << "[5] - Exit" << std::endl;
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
				Detail currentRecord;
				DetailsFile.seekg(0);
				while (DetailsFile)
				{
					DetailsFile.read(reinterpret_cast<char*>(&currentRecord), sizeof Detail);
					if (currentRecord.id == tableID)
					{
						currentRecord.print();
						return true;
					}
				}
				std::cout << "Detail with this ID wasn't find" << std::endl;
				DetailsFile.clear();
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
				Supplier currentRecord;
				SupplementsFile.seekg(0);
				while (SupplementsFile)
				{
					SupplementsFile.read(reinterpret_cast<char*>(&currentRecord), sizeof Supplier);
					if (currentRecord.id == tableID)
					{
						currentRecord.print();
						return true;
					}
				}
				std::cout << "Supplier with this ID wasn't find" << std::endl;
				SupplementsFile.clear();
				return false;
			}
			case 3:
			{
				printAllDetails();
				break;
			}
			case 4:
			{
				printAllSupplements();
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
	if (DetailsCount == 0)
	{
		std::cout << "Enable to print Suppliers, because Details is empty" << std::endl;
		return false;
	}
	if (SupplementsCount == 0)
	{
		std::cout << "Enable to print Suppliers, because Supplements is empty" << std::endl;
		return false;
	}

	std::cout << "Details :" << std::endl;
	printAllDetails();
	std::cout << "Choose one Detail id" << std::endl;
	uint32_t DetailID = 0;
	while (!(std::cin >> DetailID))
	{
		clearCin();
	}

	std::cout << "Supplements :" << std::endl;
	printAllSupplements();
	std::cout << "Choose one Supplier id" << std::endl;
	uint32_t SupplementID = 0;
	while (!(std::cin >> SupplementID))
	{
		clearCin();
	}

	Supplement currentRecord;
	SuppliersFile.seekg(0);
	bool bWasFind = false;
	while (SuppliersFile)
	{
		SuppliersFile.read(reinterpret_cast<char*>(&currentRecord), sizeof Supplement);
		if (SuppliersFile)
		{
			if (currentRecord.supplierID == SupplementID && currentRecord.detailID == DetailID)
			{
				currentRecord.print();
				bWasFind = true;
			}
		}
	}
	SuppliersFile.clear();
	if (!bWasFind)
	{
		std::cout << "Supplement by that params doesn't exist" << std::endl;
	}
	return bWasFind;
}

void DataBase::insert_m()
{
	bool bRepeat = true;
	while (bRepeat)
	{
		std::cout << "Choose table :" << std::endl << "[1] - Details" << std::endl << "[2] - Supplements" << std::endl << "[3] - Exit" << std::endl;
		int num = 0;
		std::cin >> num;
		switch (num)
		{
			case 1:
			{
				Detail currentRecord;
				currentRecord.input(DetailsUID++);
				DetailsFile.seekp(DetailsCount * (sizeof Detail));
				DetailsFile.write(reinterpret_cast<char*>(&currentRecord), sizeof Detail);
				DetailsFile.flush();
				DetailsCount++;
				bRepeat = false;
				break;
			}
			case 2:
			{
				Supplier currentRecord;
				currentRecord.input(SupplementsUID++);
				SupplementsFile.seekp(SupplementsCount * (sizeof Supplier));
				SupplementsFile.write(reinterpret_cast<char*>(&currentRecord), sizeof Supplier);
				SupplementsFile.flush();
				SupplementsCount++;
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
	if (DetailsCount == 0)
	{
		std::cout << "Enable to insert Suppliers, because Details is empty" << std::endl;
		return;
	}
	if (SupplementsCount == 0)
	{
		std::cout << "Enable to insert Suppliers, because Supplements is empty" << std::endl;
		return;
	}

	std::cout << "Details :" << std::endl;
	printAllDetails();
	std::cout << "Choose one Detail id" << std::endl;
	uint32_t DetailID = 0;
	while (!(std::cin >> DetailID))
	{
		clearCin();
	}

	bool bWasFind = false;

	Detail currentDetail;
	DetailsFile.seekg(0);
	while (DetailsFile)
	{
		DetailsFile.read(reinterpret_cast<char*>(&currentDetail), sizeof Detail);
		if (currentDetail.id == DetailID)
		{
			bWasFind = true;
			break;
		}
	}
	DetailsFile.clear();
	if (!bWasFind)
	{
		std::cout << "Detail with this ID wasn't find" << std::endl;
		return;
	}

	std::cout << "Supplements :" << std::endl;
	printAllSupplements();
	std::cout << "Choose one Supplier id" << std::endl;
	uint32_t SupplementID = 0;
	while (!(std::cin >> SupplementID))
	{
		clearCin();
	}

	bWasFind = false;
	Supplier currentSupplement;
	SupplementsFile.seekg(0);
	while (SupplementsFile)
	{
		SupplementsFile.read(reinterpret_cast<char*>(&currentSupplement), sizeof Supplier);
		if (currentSupplement.id == SupplementID)
		{
			bWasFind = true;
			break;
		}
	}
	SupplementsFile.clear();
	if (!bWasFind)
	{
		std::cout << "Supplier with this ID wasn't find" << std::endl;
		return;
	}


	Supplement currentRecord;
	currentRecord.input(SupplementID,DetailID);
	SuppliersFile.seekp(SuppliersCount * (sizeof Supplement));
	SuppliersFile.write(reinterpret_cast<char*>(&currentRecord), sizeof Supplement);
	SuppliersFile.flush();
	SuppliersCount++;
}

void DataBase::update_m()
{
	while (true)
	{
		std::cout << "Choose table :" << std::endl << "[1] - Details" << std::endl << "[2] - Supplements" << std::endl << "[3] - All Details" << std::endl << "[4] - All Supplements" << std::endl << "[5] - Exit" << std::endl;
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
			Detail currentRecord;
			DetailsFile.seekg(0);
			uint32_t position = 0;
			while (DetailsFile)
			{
				DetailsFile.read(reinterpret_cast<char*>(&currentRecord), sizeof Detail);
				if (currentRecord.id == tableID)
				{
					std::cout << "Input update params" << std::endl;
					currentRecord.input(currentRecord.id);
					DetailsFile.seekp(position);
					DetailsFile.write(reinterpret_cast<char*>(&currentRecord), sizeof Detail);
					return;
				}
				position += sizeof Detail;
			}
			std::cout << "Detail with this ID wasn't find" << std::endl;
			DetailsFile.clear();
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
			Supplier currentRecord;
			uint32_t position = 0;
			SupplementsFile.seekg(0);
			while (SupplementsFile)
			{
				SupplementsFile.read(reinterpret_cast<char*>(&currentRecord), sizeof Supplier);
				if (currentRecord.id == tableID)
				{
					std::cout << "Input update params" << std::endl;
					currentRecord.input(currentRecord.id);
					SupplementsFile.seekp(position);
					SupplementsFile.write(reinterpret_cast<char*>(&currentRecord), sizeof Supplier);
					return;
				}
				position += sizeof Supplier;
			}
			std::cout << "Supplier with this ID wasn't find" << std::endl;
			SupplementsFile.clear();
			return;
		}
		case 3:
		{
			printAllDetails();
			break;
		}
		case 4:
		{
			printAllSupplements();
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
	if (DetailsCount == 0)
	{
		std::cout << "Enable to update Suppliers, because Details is empty" << std::endl;
		return;
	}
	if (SupplementsCount == 0)
	{
		std::cout << "Enable to update Suppliers, because Supplements is empty" << std::endl;
		return;
	}

	std::cout << "Details :" << std::endl;
	printAllDetails();
	std::cout << "Choose one Detail id" << std::endl;
	uint32_t DetailID = 0;
	while (!(std::cin >> DetailID))
	{
		clearCin();
	}

	std::cout << "Supplements :" << std::endl;
	printAllSupplements();
	std::cout << "Choose one Supplier id" << std::endl;
	uint32_t SupplementID = 0;
	while (!(std::cin >> SupplementID))
	{
		clearCin();
	}

	Supplement currentRecord;
	std::vector<std::pair<uint32_t, Supplement>> Suppliers;
	SuppliersFile.seekg(0);
	uint32_t position = 0;
	bool bWasFind = false;
	while (SuppliersFile)
	{
		SuppliersFile.read(reinterpret_cast<char*>(&currentRecord), sizeof Supplement);
		if (SuppliersFile)
		{
			if (currentRecord.supplierID == SupplementID && currentRecord.detailID == DetailID)
			{
				Suppliers.emplace_back(position, currentRecord);
				bWasFind = true;
			}
		}
		position += sizeof Supplement;
	}
	SuppliersFile.clear();
	if (!bWasFind)
	{
		std::cout << "Supplement by that params doesn't exist" << std::endl;
		return;
	}
	std::cout << "Choose one available Supplier (i)" << std::endl;
	uint32_t i = 0;
	for (;i<Suppliers.size();i++)
	{
		std::cout << " [i] =" << i << " ";
		Suppliers[i].second.print();
	}
	i = 0;
	while (!(std::cin >> i)||i >= Suppliers.size())
	{
		clearCin();
	}


	std::cout << "Input new params for this Supplement" << std::endl;
	currentRecord.input(SupplementID, DetailID);
	SuppliersFile.seekp(Suppliers[i].first);
	SuppliersFile.write(reinterpret_cast<char*>(&currentRecord), sizeof Supplement);
	SuppliersFile.flush();
}

void DataBase::delete_m()
{
	while (true)
	{
		std::cout << "Choose table :" << std::endl << "[1] - Details" << std::endl << "[2] - Supplements" << std::endl << "[3] - All Details" << std::endl << "[4] - All Supplements" << std::endl << "[5] - Exit" << std::endl;
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
			Detail currentRecord;
			DetailsFile.seekg(0);
			std::ofstream tempFile;		
			tempFile.open("temp.bin", std::ios::binary | std::ios::trunc);
			tempFile.seekp(0);
			bool bWasFind = false;
			while (DetailsFile)
			{
				DetailsFile.read(reinterpret_cast<char*>(&currentRecord), sizeof Detail);
				if (DetailsFile)
				{
					if (currentRecord.id != tableID)
					{
						tempFile.write(reinterpret_cast<char*>(&currentRecord), sizeof Detail);
					}
					else
					{
						bWasFind = true;
					}
				}
			}
			DetailsFile.clear();
			if (bWasFind)
			{
				DetailsFile.close();
				tempFile.close();			
				std::rename("Details.bin", "trash.bin");
				std::rename("temp.bin", "Details.bin");
				std::rename("trash.bin","temp.bin");
				DetailsFile.open("Details.bin");
				DetailsFile.setf(std::ios::binary);
				DetailsCount--;

				tempFile.open("temp.bin", std::ios::binary | std::ios::trunc);
				tempFile.seekp(0);
				Supplement Supplier;
				SuppliersFile.seekg(0);
				uint32_t countSuppliers = 0;
				while (SuppliersFile)
				{
					SuppliersFile.read(reinterpret_cast<char*>(&Supplier), sizeof Supplement);
					if (SuppliersFile)
					{
						if (Supplier.detailID != tableID)
						{
							tempFile.write(reinterpret_cast<char*>(&Supplier), sizeof Supplement);
						}
						else
						{
							countSuppliers++;
						}
					}
				}
				SuppliersFile.clear();
				if (countSuppliers>0)
				{
					SuppliersFile.close();
					tempFile.close();					
					std::rename("Suppliers.bin", "trash.bin");
					std::rename("temp.bin", "Suppliers.bin");
					std::rename("trash.bin","temp.bin");
					SuppliersFile.open("Suppliers.bin");
					SuppliersFile.setf(std::ios::binary);
					SuppliersCount -= countSuppliers;
				}

			}
			else
			{
				std::cout << "Detail with this ID wasn't find" << std::endl;
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
			Supplier currentRecord;
			SupplementsFile.seekg(0);
			std::ofstream tempFile;
			tempFile.open("temp.bin", std::ios::binary | std::ios::trunc);
			tempFile.seekp(0);
			bool bWasFind = false;
			while (SupplementsFile)
			{
				SupplementsFile.read(reinterpret_cast<char*>(&currentRecord), sizeof Supplier);
				if (SupplementsFile)
				{
					if (currentRecord.id != tableID)
					{
						tempFile.write(reinterpret_cast<char*>(&currentRecord), sizeof Supplier);
					}
					else
					{
						bWasFind = true;
					}
				}
			}
			SupplementsFile.clear();
			if (bWasFind)
			{
				SupplementsFile.close();
				tempFile.close();
			
				std::rename("Supplements.bin", "trash.bin");
				std::rename("temp.bin", "Supplements.bin");
				std::rename("trash.bin","temp.bin");
				SupplementsFile.open("Supplements.bin");
				SupplementsFile.setf(std::ios::binary);
				SupplementsCount--;

				tempFile.open("temp.bin", std::ios::binary | std::ios::trunc);
				tempFile.seekp(0);
				Supplement Supplier;
				SuppliersFile.seekg(0);
				uint32_t countSuppliers = 0;
				while (SuppliersFile)
				{
					SuppliersFile.read(reinterpret_cast<char*>(&Supplier), sizeof Supplement);
					if (SuppliersFile)
					{

						if (Supplier.supplierID != tableID)
						{
							tempFile.write(reinterpret_cast<char*>(&Supplier), sizeof Supplement);
						}
						else
						{
							countSuppliers++;
						}
					}
				}
				SuppliersFile.clear();
				if (countSuppliers > 0)
				{
					SuppliersFile.close();
					tempFile.close();
					std::rename("Suppliers.bin", "trash.bin");
					std::rename("temp.bin", "Suppliers.bin");
					std::rename("trash.bin", "temp.bin");
					SuppliersFile.open("Suppliers.bin");
					SuppliersFile.setf(std::ios::binary);
					SuppliersCount -= countSuppliers;
				}
			}
			else
			{
				std::cout << "Supplier with this ID wasn't find" << std::endl;
			}
			return;
		}
		case 3:
		{
			printAllDetails();
			break;
		}
		case 4:
		{
			printAllSupplements();
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
	if (DetailsCount == 0)
	{
		std::cout << "Enable to update Suppliers, because Details is empty" << std::endl;
		return;
	}
	if (SupplementsCount == 0)
	{
		std::cout << "Enable to update Suppliers, because Supplements is empty" << std::endl;
		return;
	}

	std::cout << "Details :" << std::endl;
	printAllDetails();
	std::cout << "Choose one Detail id" << std::endl;
	uint32_t DetailID = 0;
	while (!(std::cin >> DetailID))
	{
		clearCin();
	}

	std::cout << "Supplements :" << std::endl;
	printAllSupplements();
	std::cout << "Choose one Supplier id" << std::endl;
	uint32_t SupplementID = 0;
	while (!(std::cin >> SupplementID))
	{
		clearCin();
	}

	Supplement currentRecord;
	std::vector<std::pair<uint32_t, Supplement>> Suppliers;
	SuppliersFile.seekg(0);
	uint32_t position = 0;
	bool bWasFind = false;
	while (SuppliersFile)
	{
		SuppliersFile.read(reinterpret_cast<char*>(&currentRecord), sizeof Supplement);
		if (SuppliersFile)
		{
			if (currentRecord.supplierID == SupplementID && currentRecord.detailID == DetailID)
			{
				Suppliers.emplace_back(position, currentRecord);
				bWasFind = true;
			}
		}
		position += sizeof Supplement;
	}
	SuppliersFile.clear();
	if (!bWasFind)
	{
		std::cout << "Supplement by that params doesn't exist" << std::endl;
		return;
	}
	std::cout << "Choose one available Supplier (i)" << std::endl;
	uint32_t i = 0;
	for (; i < Suppliers.size(); i++)
	{
		std::cout << " [i] =" << i << " ";
		Suppliers[i].second.print();
	}
	i = 0;
	while (!(std::cin >> i) || i >= Suppliers.size())
	{
		clearCin();
	}
	std::ofstream tempFile;
	tempFile.open("temp.bin", std::ios::binary | std::ios::trunc);
	tempFile.seekp(0);

	SuppliersFile.seekg(0);
	position = 0;
	bWasFind = false;
	while (SuppliersFile)
	{
		SuppliersFile.read(reinterpret_cast<char*>(&currentRecord), sizeof Supplement);
		if (position != Suppliers[i].first)
		{
			tempFile.write(reinterpret_cast<char*>(&currentRecord), sizeof Supplement);
		}
		else
		{
			bWasFind = true;
		}
	}
	SuppliersFile.clear();
	if (!bWasFind)
	{
		std::cout << "Input new params for this Supplement" << std::endl;
	}
	else
	{
		SuppliersFile.close();
		tempFile.close();	
		std::rename("Suppliers.bin", "trash.bin");
		std::rename("temp.bin", "Suppliers.bin");
		std::rename("trash.bin", "temp.bin");
		SuppliersFile.open("Suppliers.bin");
		SuppliersFile.setf(std::ios::binary);
		SuppliersCount--;
	}
}

int main()
{
	DataBase dataBase;
	dataBase.init("Details.bin", "Supplements.bin", "Suppliers.bin");

	while (true)
	{
		int input = 0;
		std::cout << "Choose option:\n[1] - get_m\n[2] - insert_m\n[3] - update_m\n[4] - delete_m\n[5] - get_s\n[6] - insert_s\n[7] - update_s\n[8] - delete_s" << std::endl << "[9] - PrintAllDetails\n[10] - PrintAllSupplements\n[11] - PrintAllSuppliers\n[12] - Exit" << std::endl;
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
				dataBase.printAllDetails();
				break;
			}
			case 10:
			{
				system("cls");
				dataBase.printAllSupplements();
				break;
			}
			case 11:
			{
				system("cls");
				dataBase.printAllSuppliers();
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