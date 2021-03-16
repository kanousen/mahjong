
#include "QtGuiApplication1.h"
#include <vector>
#include <iostream>
#include <ctime>
#include <cstdio>
#include <cstdlib>
#include <string>

#define random(a,b) (rand()%(b-a)+a)

using namespace std;

int random_card();
void quicksort_card(int*, int, int);
int partition(int*, int, int);
void get_card(int*);
void card_itoa(string*, int*);
void get_icon(string*);

bool iswin(const vector<int>&);


QtGuiApplication1::QtGuiApplication1(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	int Cardnum[14] = { 0 };
	string Cardgroup[14] = { "" };
	QStringList arguments = QCoreApplication::arguments();
	int argc = arguments.count();
	string in_str = "";

	for (int i = 1; i < arguments.count() && i<= 2; i++)
	{
		in_str = arguments[i].toStdString();
	}

	if (in_str == "")
	{
		srand((int)time(NULL));
		get_card(Cardnum);
		quicksort_card(Cardnum, 0, 13);
		card_itoa(Cardgroup, Cardnum);
		QString noparam = QString::fromLocal8Bit("无参数输入");
		ui.input_text->setText(noparam);
	}
	else
	{

		QString qstr = arguments[1];
		ui.input_text->setText(qstr);

		string input_string = in_str;
		int card;
		string::size_type index = 0;
		for (int n = 0; n < 14; n++)
		{
			index = input_string.find(",");
			string cardstr = input_string.substr(0, index);
			card = atoi(cardstr.c_str());
			Cardnum[n] = (card-1)/4+1;
			input_string.erase(0, index + 1);
			index = 0;
		}
		quicksort_card(Cardnum, 0, 13);
		card_itoa(Cardgroup, Cardnum);
	}
	QPushButton* buttongroup[14];
	*buttongroup = ui.Button_card1;
	buttongroup[1] = ui.Button_card2;
	buttongroup[2] = ui.Button_card3;
	buttongroup[3] = ui.Button_card4;
	buttongroup[4] = ui.Button_card5;
	buttongroup[5] = ui.Button_card6;
	buttongroup[6] = ui.Button_card7;
	buttongroup[7] = ui.Button_card8;
	buttongroup[8] = ui.Button_card9;
	buttongroup[9] = ui.Button_card10;
	buttongroup[10] = ui.Button_card11;
	buttongroup[11] = ui.Button_card12;
	buttongroup[12] = ui.Button_card13;
	buttongroup[13] = ui.Button_card14;

	for (int i = 0; i <= 13; i++)
	{
		string card_str = Cardgroup[i];
		string str = ":/QtGuiApplication1/MajiangImages/" + card_str + ".png";
		QString qstr = QString::fromStdString(str);
		buttongroup[i]->setIcon(QIcon(qstr));
	}	
	//int num[14] = { 1,1,1,2,3,4,4,4,4,5,6,7,8,8 };
	//vector<int> cardvector(num, num + 14);
	vector<int> cardvector(Cardnum,Cardnum+14);

	if (iswin(cardvector))
		ui.label_iswin->setText("You win");
	else ui.label_iswin->setText("You lose");
	connect(ui.reshuffle, SIGNAL(clicked(bool)), this, SLOT(reshuffle()));
		

}



int random_card()
{

	int card_num;
	card_num = random(1, 136);
	return card_num;
}

void get_card(int* A)
{
	for (int i = 0; i <= 13; i++)
	{
		int temp = (random_card()-1)/4+1;
		A[i] = temp;
	}
}

void quicksort_card(int* Cards, int p, int r)
{
	if (p < r) {
		int q = partition(Cards, p, r);
		quicksort_card(Cards, p, q - 1);
		quicksort_card(Cards, q + 1, r);
	}
}

int partition(int* Cards, int m, int n)
{
	int p = m;
	int r = n;
	int x = Cards[r];
	int i = p - 1;
	int temp;
	for (int j = p; j <= r - 1; j++)
	{
		if (Cards[j] <= x) {
			i++;
			temp = Cards[j];
			Cards[j] = Cards[i];
			Cards[i] = temp;
		}
	}
	temp = Cards[i + 1];
	Cards[i + 1] = Cards[r];
	Cards[r] = temp;
	return i + 1;
}

void card_itoa(string* Cardstr, int* Cardnum)
{
	for (int i = 0; i <= 13; i++)
	{
		char str[5];
		sprintf(str, "%03d", Cardnum[i]);
		Cardstr[i] = str;
	}
}

void QtGuiApplication1::reshuffle()
{
	int Cardnum[14] = { 0 };
	string Cardgroup[14] = { "" };
	srand((int)time(NULL));
	get_card(Cardnum);
	quicksort_card(Cardnum, 0, 13);
	card_itoa(Cardgroup, Cardnum);
	QPushButton* buttongroup[14];
	*buttongroup = ui.Button_card1;
	buttongroup[1] = ui.Button_card2;
	buttongroup[2] = ui.Button_card3;
	buttongroup[3] = ui.Button_card4;
	buttongroup[4] = ui.Button_card5;
	buttongroup[5] = ui.Button_card6;
	buttongroup[6] = ui.Button_card7;
	buttongroup[7] = ui.Button_card8;
	buttongroup[8] = ui.Button_card9;
	buttongroup[9] = ui.Button_card10;
	buttongroup[10] = ui.Button_card11;
	buttongroup[11] = ui.Button_card12;
	buttongroup[12] = ui.Button_card13;
	buttongroup[13] = ui.Button_card14;
	for (int i = 0; i <= 13; i++)
	{
		string card_str = Cardgroup[i];
		string str = ":/QtGuiApplication1/MajiangImages/" + card_str + ".png";
		QString qstr = QString::fromStdString(str);
		buttongroup[i]->setIcon(QIcon(qstr));
	}
	vector<int> cardvector(Cardnum, Cardnum + 14);
	QString str_reshuffle = QString::fromLocal8Bit("重新洗牌");
	ui.input_text->setText(str_reshuffle);
	if (iswin(cardvector))
		ui.label_iswin->setText("You win");
	else ui.label_iswin->setText("You lose");
}

bool iswin(const vector<int> &invector)
{
	size_t location = -1;
	vector<int> a;
	while (true)
	{
		auto i = location + 1;
		if (i >= invector.size())
			return false;
		a = invector;

		if (location != -1)
		{
			if (a[i] == a[location])
				i++;
		}

		location = -1;
		for (; i < a.size() - 1; i++) 
		{
			if (a[i] == a[i + 1])
			{
				location = i + 1;
				a.erase(a.begin() + i, a.begin() + i + 2);
				break;
			}
		}
		if (location == -1)
			return false;

		while (a.size() >= 3)
		{
			if (a[0] == a[1] && a[0] == a[2])
			{
				a.erase(a.begin(), a.begin() + 3);
			}
			else 
			{
				vector<int>::iterator it1 = find(a.begin() + 1, a.end(), a[0] + 1);
				//if (it1 != a.end() && (a[0]%9 <= 7)) 改正
				if (it1 != a.end() && (a[0]%9 <= 7)&& a[0]<=27)
				{
					vector<int>::iterator it2 = find(it1 + 1, a.end(), a[0] + 2);
					if (it2 != a.end())
					{
						a.erase(it2);
						a.erase(it1);
						a.erase(a.begin());
					}
					else  break;
				}
				else break;
			}
		}

		if (a.empty())
			break;
	}
	return true;
}

