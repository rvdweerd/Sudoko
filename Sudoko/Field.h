#pragma once

class Field
{
public:
	class SubField {
	public:
		bool Contains(char ch)
		{
			for (int i = 0; i < 9; i++)
			{
				if (subfieldArray[i] == ch)
				{
					return true;
				}
			}
			return false;
		}
		void Print();
		char subfieldArray[9];
	};

public:
	Field() = default;
	Field(char* pArr);
	void Print() const;
	void AssignCell(int i, char ch);
	int GetAvailableChars(int i, char* pArr);
	bool SolutionExists();
	void Test();

private:
	char fieldArray[9 * 9] = { 0 };
	SubField colSubfields[9] = { 0 };
	SubField rowSubfields[9] = { 0 };
	SubField blockSubfields[9]={ 0 };
};