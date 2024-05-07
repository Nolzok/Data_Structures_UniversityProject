#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>

using namespace std;

//PROEIDOPOIHSH!!!!! TO ARXEIO CSV EXEI ALLAKSEI STA SHMEIA (Fish, crustaceans, and molluscs),(Logs, wood, and wood articles),(Milk powder, butter, and cheese) OPOU AFAIRE8HKAN TA KOMATA ANAMESA

int CompareDates(string& Date1, string& Date2)
{
    stringstream ss1(Date1);
    stringstream ss2(Date2);
    string day1, month1, year1, day2, month2, year2;

    getline(ss1, day1, '/');
    getline(ss1, month1, '/');
    getline(ss1, year1, '/');

    getline(ss2, day2, '/');
    getline(ss2, month2, '/');
    getline(ss2, year2, '/');

    int d1 = std::stoi(day1);
    int m1 = std::stoi(month1);
    int y1 = std::stoi(year1);

    int d2 = std::stoi(day2);
    int m2 = std::stoi(month2);
    int y2 = std::stoi(year2);

    //  1 if date1 > date2
    // -1 if date1 < date2
    //  0 if date1 = date2 

    if (y1 > y2)
        return 1;
    else if (y1 < y2)
        return -1;

    if (m1 > m2)
        return 1;
    else if (m1 < m2)
        return -1;

    if (d1 > d2)
        return 1;
    else if (d1 < d2)
        return -1;

    return 0;
}
int InterpolationSearch(vector<string>& Dates, string target)
{
    int a;
    int pos;
    int min = 0;
    int max = Dates.size() - 1;

    while (min <= max && CompareDates(Dates[min], Dates[max]) != 0 && CompareDates(target, Dates[min]) >= 0 && CompareDates(target, Dates[max]) <= 0)
    {
        pos = min + ((CompareDates(target, Dates[min]) * (max - min)) / (CompareDates(Dates[max], Dates[min])));

        a = CompareDates(Dates[pos], target);

        if (a == 0)
        {
            return pos;
        }
        else if (a < 0)
        {
            min = pos + 1;
        }
        else
        {
            max = pos - 1;
        }
    }
}
int BinarySearch(vector<string>& Dates, string target)
{
    int a = 5;
    int mid;
    int max = Dates.size() - 1;
    int min = 0;
    int i = 0;

    while (min <= max)
    {
        mid = min + (max - min) / 2;
        a = CompareDates(Dates[mid], target);

        if (a == 0)
        {
            return mid;
        }
        else if (a == -1)
        {
            min = mid + 1;
        }
        else if (a == 1)
        {
            max = mid - 1;
        }
    }
}

int main()
{
    //For making the data from the CSV file usable

    vector <string> row;
    vector<vector<string>> data;

    //For creating a vector of dates able to be used for BIN search and INTERPOLATION search

    vector <string> dates;
    vector<int> date_indexes;
    vector <vector<int>> dates_indexes;
    vector<string>::iterator it;

    string word;
    string line;
    int i = 0;
    int j = 0;
    string target;

    ifstream myfile("text.txt"); //open file


    //2--Date 
    //8--Value
    //9--Cumulative

    if (myfile.is_open())
    {
        while (getline(myfile, line))
        {
            stringstream ss(line);
            while (getline(ss, word, ','))
            {
                row.push_back(word);
                i++;
                if (i == 10)
                {

                    data.push_back(row);
                    row.clear();
                    i = 0;
                    j++;
                }
            }

        }

        myfile.close();
    }
    else cout << "Unable to open file";

    

    for (i = 1; i < data.size(); i++)
    {
        it = find(dates.begin(), dates.end(), data[i][2]);
        if (it == dates.end())
        {
            dates.push_back(data[i][2]);
        }



    }

    for (i = 1; i < dates.size(); i++)
    {
        for (j = 1; j < data.size(); j++)
        {
            if (dates[i] == data[j][2])
            {
                date_indexes.push_back(j);
            }
        }
        dates_indexes.push_back(date_indexes);
        date_indexes.clear();
    }
start:
    //User choice
    cout << "\033[33mPlease write the date you want to see the values and cumulatives in this format(DD/MM/YYYY):\033[0m " << endl;
    cin >> target;
    while (true)
    {
        string algorithm;
        cout << "\033[1;35mChoose what Algorithm you want to use\033[0m" << endl << "Type \033[1;33mBS\033[0m for \033[1;33mBinary Search\033[0m or Type \033[1;34mIS\033[0m for \033[1;34mInterpolation Search\033[0m:" << endl;
        cin >> algorithm;
        if (algorithm == "BS")
        {
            cout << "\033[1;35mPlease wait.\033[0m" << endl;
            int location; // pou bre8hke h hmeromhnia
            int x; // to index gia na mhn to grafoume polles fores

            location = BinarySearch(dates, target);


            for (i = 0; i < dates_indexes[location].size(); i++)
            {
                x = dates_indexes[location][i];
                cout << "x: " << x << " value: " << data[x - 1][8] << "  Cumulative: " << data[x - 1][9] << endl;
            }

            break;
        }
        else if (algorithm == "IS")
        {
            cout << "\033[1;35mPlease wait.\033[0m" << endl;
            int location; // pou bre8hke h hmeromhnia
            int x; // to index gia na mhn to grafoume polles fores

            location = InterpolationSearch(dates, target);


            for (i = 0; i < dates_indexes[location].size(); i++)
            {
                x = dates_indexes[location][i];
                cout << "value: " << data[x][8] << "  Cumulative: " << data[x][9] << endl;
            }

            break;
        }

        else
        {
            cout << "\033[1;31mInvalid choice ,please choose again.\033[0m" << endl;
        }

    }
    char executeAgain;
    cout << endl;
    cout << "if you wish to see another date press 'y'" << endl;
    cin >> executeAgain;
    if (executeAgain == 'y')
    {
        goto start;
    }
    return 0;
}