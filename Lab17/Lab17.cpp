#include <iostream>
#include <vector>
#include <string>
#include <list>
#include <ctime>
#include <cmath>
#include <fstream>
using namespace std;
struct STR
{
    string NAME;
    int dat1;
    int dat2;
    int dat3;
    string No;
    int n;
};
int random(int a, int b)
{
    if (a > 0) return a + rand() % (b - a);
    else return a + rand() % (abs(a) + b);
}
void Fill(vector<STR>& human, int n1)
{
    human.clear();
    ifstream nameM1("NameM.txt");
    ifstream nameW1("NameW.txt");
    ifstream surnameM1("surnameM.txt");
    ifstream surnameW1("surnameW.txt");
    ifstream patronymicM1("patronymicM.txt");
    ifstream patronymicW1("patronymicW.txt");
    string nameM[42];
    string nameW[41];
    string surnameM[100];
    string surnameW[100];
    string patronymicM[65];
    string patronymicW[57];
    for (int i = 0; i < 42; i++)
    {
        string row;
        nameM1 >> row;
        nameM[i] = row;
    }
    for (int i = 0; i < 41; i++)
    {
        string row;
        nameW1 >> row;
        nameW[i] = row;
    }
    for (int i = 0; i < 100; i++)
    {
        string row;
        surnameM1 >> row;
        surnameM[i] = row;
    }
    for (int i = 0; i < 100; i++)
    {
        string row;
        surnameW1 >> row;
        surnameW[i] = row;
    }
    for (int i = 0; i < 65; i++)
    {
        string row;
        patronymicM1 >> row;
        patronymicM[i] = row;
    }
    for (int i = 0; i < 57; i++)
    {
        string row;
        patronymicW1 >> row;
        patronymicW[i] = row;
    }
    nameM1.close();
    nameW1.close();
    surnameM1.close();
    surnameW1.close();
    patronymicM1.close();
    patronymicW1.close();
    int r;
    for (int i = 0; i < n1; i++)
    {
        r = random(0, 20);
        if (r <= 10)
        {
            STR test;
            test.NAME = surnameM[random(0, 100)];
            test.NAME = test.NAME + ' ' + nameM[random(0, 42)];
            test.NAME = test.NAME + ' ' + patronymicM[random(0, 65)];
            test.dat1 = random(1, 31);
            test.dat2 = random(1, 12);
            test.dat3 = random(1950, 2005);
            test.No = '8';
            test.No += std::to_string(random(100, 999));
            test.No += std::to_string(random(1000000, 9999999));
            test.n = i + 1;
            human.push_back(test);
        }
        else
        {
            STR test;
            int n1, n2;
            test.NAME = surnameW[random(0, 100)];
            test.NAME = test.NAME + ' ' + nameW[random(0, 41)];
            test.NAME = test.NAME + ' ' + patronymicW[random(0, 57)];
            test.dat1 = random(1, 31);
            test.dat2 = random(1, 12);
            test.dat3 = random(1940, 2005);
            test.No = '8';
            test.No += std::to_string(random(100, 999));
            test.No += std::to_string(random(1000000, 9999999));
            test.n = i + 1;
            human.push_back(test);
        }
    }
}
void Print(vector<STR> human, int n1)
{
    for (int i = 0; i < n1; i++)
    {
        cout << human[i].n << ')' << '\t';
        cout << human[i].NAME << endl << '\t';
        cout << human[i].dat1 << '.' << human[i].dat2 << '.' << human[i].dat3 << endl << '\t';
        cout << human[i].No << endl << endl;
    }
}
class HashT
{
public:
    int key;
    vector<STR>list;
    void HashF(int dat1, int dat2, int dat3,int N)
    {
        int tmp = dat1 + dat2 + dat3; 
        double A = 0.618033;
        key = N * fmod(tmp * A, 1);
    }
    void Add(STR hum)
    {
        list.push_back(hum);
    }
};
void hashSort(vector<HashT>& list)
{
    for (int step = list.size() / 2; step > 0; step /= 2)
    {
        for (int i = step; i < list.size(); i++)
        {
            for (int j = i; j >= step; j -= step)
            {
                if (list[j].key < list[j - step].key)
                    swap(list[j], list[j - step]);
            }
        }
    }
}
void FillHash(vector<HashT>& list, vector<STR> human)
{
    for (int i = 0; i < human.size(); i++)
    {
        HashT tmp;
        tmp.HashF(human[i].dat1, human[i].dat2, human[i].dat3, human.size());
        tmp.Add(human[i]);
        list.push_back(tmp);
    }
    hashSort(list);
    int size = list.size();
    for (int i = 0; i < size - 1;)
    {
        if (list[i].key == list[i + 1].key)
        {
            list[i].list.push_back(list[i + 1].list[0]);
            list.erase(list.begin() + i + 1);
            size--;
        }
        else
            i++;
    }
}
void ShowHash(vector<HashT> list)
{
    for (int i = 0; i < list.size(); i++)
    {
        cout << "-----------------------------------------------------------------------\n";
        cout << "Хеш: " << i + 1 << list[i].key << endl;
        for (int j = 0; j < list[i].list.size(); j++)
        {
            cout << "*\t" << list[i].list[j].NAME << endl << '\t';
            cout << list[i].list[j].dat1 << '.' << list[i].list[j].dat2 << '.' << list[i].list[j].dat3 << endl << '\t';
            cout << list[i].list[j].No << endl << endl;
        }
    }
}
int main()
{
    system("chcp 1251>nul");
    srand(time(NULL));
    vector<STR> human;
    int n1 = 0;
    cout << "Введите количество элементов(не менее 5): ";
    while (n1 < 5)
    {
        cin >> n1;
        if (n1 < 5)
        {
            cout << "Введено некоректное значение. Введите значение заново";
        }
    }
    Fill(human, n1);
    cout << "\n\n-----------------------------------------------------------------------\n\n";
    Print(human, n1);
    cout << "-----------------------------------------------------------------------\n\n";
    vector<HashT>list;
    FillHash(list, human);
    cout << "\n\tХЕШ ТАБЛИЦА\t";
    cout << "\n\n-----------------------------------------------------------------------\n\n";
    ShowHash(list);
    cout << "-----------------------------------------------------------------------\n\n";
    return 0;
}

