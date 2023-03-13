#include <fstream>
#include <string>
#include <math.h>

using namespace std;

struct node {
	node() {
		p = 0;
		l = 0;
		q = 0;
		code = "";
	}
	double q;
	double p;
	int l;
	string code;
};

class Shen
{
public:
	Shen()
	{
		mas = nullptr;
		i = 0;
	}

	void read()
	{
		ifstream fin;
		node* buf;
		fin.open("input.txt");
		while (fin)
		{
			buf = mas;
			mas = new node[i + 1];
			for (int j = 0; j < i; j++)
			{
				mas[j].p = buf[j].p;
			}
			fin >> mas[i].p;
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
		node buf;
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
		double number;
		for (int j = 0; j < i; j++)
		{
			for (int g = 0; g < j; g++)
			{
				mas[j].q += mas[g].p; // получаем q ебаное
			}
			mas[j].l = (int)ceil(-log2(mas[j].p)); // размер считаем
		}
		for (int j = 0; j < i; j++)
		{
			number = mas[j].q - (int)mas[j].q; // дробную часть выделяем
			for (int g = 0; g < mas[j].l; g++)
			{
				number = number - (int)number;
				number *= 2;
				if ((int)number == 0)
				{
					mas[j].code += "0";
				}
				else if ((int)number == 1)
				{
					mas[j].code += "1";
				}
			}
		}
	}



private:
	node* mas;
	int i;
};

int main(void)
{
	Shen test;
	test.read();
	test.sort();
	test.coding();
	test.write();	

	return 0;
}