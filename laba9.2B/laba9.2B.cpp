//B
#include <iostream>
#include <iomanip>
#include <string>
#include <algorithm>
#include <Windows.h> 
using namespace std;

enum Spec { ME, MF, FI, In, KN };
string specStr[] = { "Математика та економіка", "Трудове навчання", "Фізика та інформатика", "Інформатика" ,"Комп'ютерні науки" };


struct Student
{
	string prizv;
	unsigned kurs;
	Spec spec;
	unsigned markPh;
	unsigned markMath;
	union {
		unsigned markProg;
	};
	union {
		unsigned markChM;
	};
	union {
		unsigned markPed;
	};
};

void Create(Student* p, const int N);
void Print(Student* p, const int N);
double LineSearch(Student* p, const int N);
void Sort(Student* p, const int N);
int* IndexSort(Student* p, const int N);
void PrintIndexSorted(Student* p, int* I, const int N);
int BinSearch(Student* p, const int N, const string prizv, const Spec spec, const unsigned markMath);

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	int N;
	cout << "Введіть кількість студентів: "; cin >> N;

	Student* p = new Student[N];
	double proc;
	int ispec;
	Spec spec;
	string prizv;
	unsigned markMath;
	unsigned imarkMath;
	int found;

	int menuItem;
	do {
		cout << endl << endl << endl;
		cout << "Виберіть дію:" << endl << endl;
		cout << " [1] - введення даних з клавіатури" << endl;
		cout << " [2] - вивід даних на екран" << endl;
		cout << " [3] - вивід прізвищ студентів, що отримали з фізика 5" << endl;
		cout << " і хто вчиться на відмінно" << endl;
		cout << " [4] - фізичне впорядкування даних" << endl << endl;
		cout << " [5] - індексне впорядкування" << endl;
		cout << " [6] - бінарний пошук працівника за посадою та прізвищем" << endl;
		cout << " [0] - вихід та завершення роботи програми" << endl << endl;
		cout << "Введіть значення: "; cin >> menuItem;
		cout << endl << endl << endl;
		switch (menuItem)
		{
		case 1:
			Create(p, N);
			break;
		case 2:
			Print(p, N);
			break;
		case 3:
			proc = LineSearch(p, N);
			cout << "Процент студентів, що вчаться на відмінно:" << endl;
			cout << proc << "%" << endl;
			break;
		case 4:
			Sort(p, N);
			break;

		case 5:
			PrintIndexSorted(p, IndexSort(p, N), N);

		case 6:
			cout << "Введіть ключі пошуку:" << endl;
			cout << "спеціальність(0 - Математика та економіка, 1 - Трудове навчання, 2 - Фізика та інформатика, 3 - інформатика, 4 - комп'ютерні науки): ";
			cin >> ispec;
			spec = (Spec)ispec;
			cout << "Оцінка з математики: ";
			cin >> imarkMath;
			markMath = imarkMath;
			cin.get();
			cin.sync();
			cout << " прізвище: "; getline(cin, prizv);
			cout << endl;
			if ((found = BinSearch(p, N, prizv, spec, markMath)) != -1)
				cout << "Знайдено студента в позиції " << found + 1 << endl;
			else
				cout << "Шуканого студента не знайдено" << endl;
			break;

			break;
		case 0:
			break;
		default:
			cout << "Ви ввели помилкове значення! "
				"Слід ввести число - номер вибраного пункту меню" << endl;

		}
	} while (menuItem != 0);

}

void Create(Student* p, const int N)
{
	int spec;
	for (int i = 0; i < N; i++)
	{
		cout << "Студент № " << i + 1 << ":" << endl;
		cin.get();
		cin.sync();

		cout << " прізвище: "; getline(cin, p[i].prizv);
		cout << " курс: "; cin >> p[i].kurs;
		cout << " спеціальність ( 0 - Математика та економіка, 1 - Трудове навчання, 2 - Фізика та інформатика, 3 - інформатика , 4 - комп'ютерні науки): ";
		cin >> spec;
		p[i].spec = (Spec)spec;


		switch (p[i].spec) {

		case 3:
			cout << " фізика : "; cin >> p[i].markPh;
			cout << " математика : "; cin >> p[i].markMath;
			cout << " чисельні методи : "; cin >> p[i].markChM;
			break;
		case 4:
			cout << " фізика : "; cin >> p[i].markPh;
			cout << " математика : "; cin >> p[i].markMath;
			cout << " програмування : "; cin >> p[i].markProg;
			break;

		default:
			cout << " фізика : "; cin >> p[i].markPh;
			cout << " математика : "; cin >> p[i].markMath;
			cout << " педагогіка : "; cin >> p[i].markPed;
			break;
		}
		cout << endl;
	}
}

void Print(Student* p, const int N)
{
	cout << "=============================================================================================================================="
		<< endl;
	cout << "| № |     Прізвище     | курс |       спеціальність     | фізика | математика | програмування | чисельні методи | педагогіка |"
		<< endl;
	cout << "------------------------------------------------------------------------------------------------------------------------------"
		<< endl;

	for (int i = 0; i < N; i++)
	{
		switch (p[i].spec) {

		case 3:
			cout << "| " << setw(1) << right << i + 1 << " ";
			cout << "| " << setw(17) << left << p[i].prizv
				<< "| " << setw(4) << right << p[i].kurs << " "
				<< "| " << setw(24) << left << specStr[p[i].spec] << "| " << setw(7) << right << p[i].markPh << "| " << setw(11) << right << p[i].markMath << "|" << setw(16) << "|" << setw(17) << right << p[i].markChM << "|" << setw(13) << "|" << endl;
			break;
		case 4:
			cout << "| " << setw(1) << right << i + 1 << " ";
			cout << "| " << setw(17) << left << p[i].prizv
				<< "| " << setw(4) << right << p[i].kurs << " "
				<< "| " << setw(24) << left << specStr[p[i].spec] << "| " << setw(7) << right << p[i].markPh << "| " << setw(11) << right << p[i].markMath << "|" << setw(15) << p[i].markProg << "|" << setw(18) << right << "|" << setw(13) << "|" << endl;
			break;

		default:
			cout << "| " << setw(1) << right << i + 1 << " ";
			cout << "| " << setw(17) << left << p[i].prizv
				<< "| " << setw(4) << right << p[i].kurs << " "
				<< "| " << setw(24) << left << specStr[p[i].spec] << "| " << setw(7) << right << p[i].markPh << "| " << setw(12) << right << "|" << setw(16) << "|" << setw(18) << right << "|" << setw(12) << p[i].markPed << "|" << endl;
			break;
		}


		cout << "------------------------------------------------------------------------------------------------------------------------------" << endl;

	}

	cout << endl;
}

double LineSearch(Student* p, const int N)
{
	cout << "Прізвища студентів, що отримали з фізика 5:" << endl;

	int k = 0, n = 0;
	for (int i = 0; i < N; i++)
	{
		if (true)
		{
			n++;
			if (p[i].markMath == 5 && p[i].markPh == 5 && p[i].markProg == 5 || p[i].markMath == 5 && p[i].markPh == 5 && p[i].markChM == 5 || p[i].markMath == 5 && p[i].markPh == 5 && p[i].markPed == 5)
			{
				k++;
			}
			if (p[i].markPh == 5) {
				cout << setw(3) << right
					<< " " << p[i].prizv << endl;
			}
		}
	}
	return 100.0 * k / n;
}

//1. Physical

void Sort(Student* p, const int N)
{
	Student tmp;
	for (int i0 = 0; i0 < N - 1; i0++) // метод "бульбашки"
		for (int i1 = 0; i1 < N - i0 - 1; i1++) {
			if ((p[i1].spec > p[i1 + 1].spec)
				||
				(p[i1].spec == p[i1 + 1].spec &&
					p[i1].markMath < p[i1 + 1].markMath)
				||
				(p[i1].spec == p[i1 + 1].spec &&
					p[i1].markMath == p[i1 + 1].markMath && p[i1].prizv > p[i1 + 1].prizv)
				)
			{
				tmp = p[i1];
				p[i1] = p[i1 + 1];
				p[i1 + 1] = tmp;
			}

		}
}

// 2.Index 

int* IndexSort(Student* p, const int N)
{
	int* I = new int[N]; // створили індексний масив
	for (int i = 0; i < N; i++)
		I[i] = i; // заповнили його початковими даними
	int i, j, value; // починаємо сортувати масив індексів
	for (i = 1; i < N; i++)
	{
		value = I[i];
		for (j = i - 1;
			j >= 0 && ((p[I[j]].spec > p[value].spec)
				||
				(p[I[j]].spec == p[value].spec &&
					p[I[j]].markMath < p[value].markMath)
				||
				(p[I[j]].prizv > p[value].prizv));
			j--)
		{
			I[j + 1] = I[j];
		}
		I[j + 1] = value;
	}
	return I;
}
void PrintIndexSorted(Student* p, int* I, const int N)
{
	cout << "============================================================================================="
		<< endl;
	cout << "| № |     Прізвище     | курс |       спеціальність     | фізика | математика | інформатика | "
		<< endl;
	cout << "---------------------------------------------------------------------------------------------"
		<< endl;

	for (int i = 0; i < N; i++)
	{

		switch (p[i].spec) {

		case 3:
			cout << "| " << setw(1) << right << i + 1 << " ";
			cout << "| " << setw(17) << left << p[i].prizv
				<< "| " << setw(4) << right << p[i].kurs << " "
				<< "| " << setw(24) << left << specStr[p[i].spec] << "| " << setw(7) << right << p[i].markPh << "| " << setw(11) << right << p[i].markMath << "|" << setw(16) << "|" << setw(17) << right << p[i].markChM << "|" << setw(13) << "|" << endl;
			break;
		case 4:
			cout << "| " << setw(1) << right << i + 1 << " ";
			cout << "| " << setw(17) << left << p[i].prizv
				<< "| " << setw(4) << right << p[i].kurs << " "
				<< "| " << setw(24) << left << specStr[p[i].spec] << "| " << setw(7) << right << p[i].markPh << "| " << setw(11) << right << p[i].markMath << "|" << setw(15) << p[i].markProg << "|" << setw(18) << right << "|" << setw(13) << "|" << endl;
			break;

		default:
			cout << "| " << setw(1) << right << i + 1 << " ";
			cout << "| " << setw(17) << left << p[i].prizv
				<< "| " << setw(4) << right << p[i].kurs << " "
				<< "| " << setw(24) << left << specStr[p[i].spec] << "| " << setw(7) << right << p[i].markPh << "| " << setw(12) << right << "|" << setw(16) << "|" << setw(18) << right << "|" << setw(12) << p[i].markPed << "|" << endl;
			break;
		}


	}
	cout << "---------------------------------------------------------------------------------------------" << endl;
}



//3. binSearch

int BinSearch(Student* p, const int N, const string prizv, const Spec spec, const unsigned markMath)
{ // повертає індекс знайденого елемента або -1, якщо шуканий елемент відсутній
	int L = 0, R = N - 1, m;
	do {
		m = (L + R) / 2;
		if (p[m].prizv == prizv && p[m].spec == spec && p[m].markMath == markMath)
			return m;
		if ((p[m].spec < spec)
			||
			(p[m].spec == spec &&
				p[m].prizv < prizv)
			||
			(p[m].spec == spec &&
				p[m].prizv == prizv && p[m].markMath < markMath))
		{
			L = m + 1;
		}
		else
		{
			R = m - 1;
		}
	} while (L <= R);
	return -1;
}
