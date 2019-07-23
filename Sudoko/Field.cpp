#include "Field.h"
#include <iostream>
#include "Point.h"

Field::Field(char* pArr)
{
	for (int i = 0; i < 9 * 9; i++, pArr++)
	{
		fieldArray[i] = *pArr;
		AssignCell(i, fieldArray[i]);
	}
}

void Field::Print() const
{
	std::cout<<"  -------------------------" << std::endl;
	for (int Y = 0; Y < 9; Y++)
	{
			std::cout << " |";
		for (int X = 0; X < 3; X++)
		{
			for (int i = 0; i < 3; i++)
			{
				std::cout << " "<<fieldArray[(3 * X + i) + Y * 9] << "";
			}
			std::cout << " | ";	
		}
		std::cout << std::endl;
		if ( (Y+1)%3 == 0)
		{
			std::cout <<  "  -------------------------" << std::endl;
		}
	} 
}

void Field::AssignCell(int i, char ch)
{
	fieldArray[i] = ch;
	
	rowSubfields[i/9].subfieldArray[i%9] = ch;
	colSubfields[i%9].subfieldArray[i/9] = ch;

	Point fieldCell(i % 9, i / 9);
	Point block(fieldCell.x / 3, fieldCell.y / 3);
	Point blockCell(fieldCell.x - block.x * 3, fieldCell.y - block.y * 3);
	blockSubfields[block.x + block.y * 3].subfieldArray[blockCell.x + blockCell.y * 3] = ch;
}

int Field::GetAvailableChars(int i, char* pArr)
{
	int row = i / 9;
	int col = i % 9;
	int block = col/3 + int(row/3)*3;
	int count = 0;
	char* pIt = pArr;

	for (char ch = '1'; ch <= '9'; ch++)
	{
		if ( !colSubfields[col].Contains(ch) && !rowSubfields[row].Contains(ch) && !blockSubfields[block].Contains(ch) )
		{
			*pIt = ch;
			pIt++;
			count++;
		}
	}
	return count;
}

bool Field::SolutionExists()
{
	for (int i = 0; i < 9 * 9; i++)
	{
		if (fieldArray[i] == '.')
		{
			char AvailableChars[9] = { 0 };
			int n = GetAvailableChars(i, AvailableChars);
			for (int k=0; k<n; k++)
			{
				AssignCell(i, AvailableChars[k]);
				if (SolutionExists())
				{
					return true;
				}
			}
			AssignCell(i,'.');
			return false;
		}
	}
}

void Field::Test()
{
	char testArray[9];// = { '1','2','3','4','5','6','7','8','9' };
	//AssignCell(40, '1');
	Print();
	colSubfields[6].Print();
	rowSubfields[1].Print();
	blockSubfields[2].Print();
	
	int n=GetAvailableChars(15, testArray);
	true;
	
}

void Field::SubField::Print()
{
	char* p1 = subfieldArray; char* p2 = p1 + 9;
	for (; p1 < p2; p1++)
	{
		std::cout << *p1 << ",";
	}
	std::cout << std::endl;
}
