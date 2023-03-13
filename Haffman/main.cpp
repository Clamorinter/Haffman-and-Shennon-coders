#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct ansamble {
	ansamble()
	{
		code = "";
		number = 0;
		parent1 = nullptr;
		parent2 = nullptr;
		ancestor = nullptr;
		key = -1;
	}
	int number;
	double p;
	string code;
	ansamble* parent1;
	ansamble* parent2;
	ansamble* ancestor;
	int key;
};

struct haff {
	haff* past;
	ansamble* now;
};

class Haffman
{
public:
	Haffman()
	{
		mas = nullptr;
		i = 0;
		last = nullptr;
	}
	void read()
	{
		ifstream fin;
		ansamble* buf;
		fin.open("input.txt");
		while (fin)
		{
			buf = mas; 
			mas = new ansamble[i+1];
			for (int j = 0; j < i; j++)
			{
				mas[j].p = buf[j].p;
				mas[j].number = buf[j].number;
			}
			fin >> mas[i].p;
			mas[i].number = i+1;
			i++;
			if (buf)
			{
				delete[] buf;
			}

		}
		i--;
		fin.close();
	}

	void write()
	{
		ofstream fout;
		fout.open("output.txt");
		for (int j = 0; j < i; j++)
		{
			fout << mas[j].code << endl;
		}
		fout.close();
	}

	void sort()
	{
		ansamble buf;
		bool flag;
		for (int j = 0; j < i; j++)
		{
			flag = true;
			for (int g = 0; g < i - 1; g++)
			{
				if (mas[g].p < mas[g + 1].p)
				{
					buf = mas[g];
					mas[g] = mas[g + 1];
					mas[g + 1] = buf;
					flag = false;
				}
			}
			if (flag)
			{
				break;
			}
		}
	}

	void coding()
	{
		haff* buf = new haff; // haff - это вот типо итераци€ одна
		buf = last;
		last = new haff;
		last->past = buf; // past - прошла€ итераци€
		last->now = mas; //now - то, кака€ итераци€ щас

		if (i == 1) 
		{
			haff* buf;
			while (last->past != nullptr) // пока все итерации не пролетим
			{
				for (int j = 0; j < i; j++)
				{
					if ((last->now[j].number != 0 || last->now[j].key != i) && last->now[j].ancestor != nullptr)
					{
						last->now[j].ancestor->code += last->now[j].code;
					} 
					else if (last->now[j].number == 0 && last->now[j].key == i)
					{
						
						last->now[j].parent1->code = last->now[j].parent1->code + last->now[j].code + "0";
						last->now[j].parent2->code = last->now[j].parent2->code + last->now[j].code + "1";
					} 
				}
				buf = last;
				last = last->past;
				delete buf;
				i++;
			}
			mas = last->now;

		}
		else
		{
			mas = new ansamble[i--]; //новый массив веро€тностей создаю
			mas[i - 1].p = last->now[i].p + last->now[i - 1].p;
			mas[i - 1].parent1 = &last->now[i]; // аккуратно указываю родител€ номер 1 и номер 2
			mas[i - 1].parent2 = &last->now[i - 1];
			mas[i - 1].key = i; // указываю итерацию
			for (int j = 0; j < i - 1; j++)
			{
				mas[j] = last->now[j]; 
				mas[j].ancestor = &last->now[j]; // указываю предка в предыдущей итерации
			}
			sort(); // сортирую по убыванию
			coding(); // р≈к”р—ия
		}
	}


private:
	ansamble* mas;
	int i;
	haff* last;
};

int main(void)
{
	Haffman test;
	test.read();
	test.sort();
	test.coding();
	test.write();
	return 0;
}