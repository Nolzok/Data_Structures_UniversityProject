#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string.h>
#include<math.h>

using namespace std;

void CS(vector<int>& Value, vector<string>& Date, int max) {

	vector<int> count(max + 1, 0);


	for (int value : Value) {
		count[value]++;
	}


	for (int i = 1; i <= max; i++) {
		count[i] += count[i - 1];
	}


	vector<string> temp(Date.size());


	for (int i = Date.size() - 1; i >= 0; i--) {
		temp[count[Value[i]] - 1] = Date[i];
		count[Value[i]]--;
	}


	for (int i = 0; i < Date.size(); i++) {
		Date[i] = temp[i];
	}
}

void Merge(vector<int>& Value, vector<string>& Date, int left, int mid, int right) {
	int n = mid - left + 1;
	int m = right - mid;

	vector<int> L(n);
	vector<int> R(m);
	vector<string> DateL(n);
	vector<string> DateR(m);

	for (int i = 0; i < n; i++) {
		L[i] = Value[left + i];
		DateL[i] = Date[left + i];
	}

	for (int j = 0; j < m; j++) {
		R[j] = Value[mid + j + 1];
		DateR[j] = Date[mid + j + 1];
	}

	int i = 0, j = 0, k = left;
	while (i < n && j < m)
	{

		if (L[i] <= R[j])
		{
			Value[k] = L[i];
			Date[k] = DateL[i];
			i++;
		}
		else
		{
			Value[k] = R[j];
			Date[k] = DateR[j];
			j++;
		}
		k++;
	}

	while (i < n)
	{
		Value[k] = L[i];
		Date[k] = DateL[i];
		i++;
		k++;
	}

	while (j < m)
	{
		Value[k] = R[j];
		Date[k] = DateR[j];
		j++;
		k++;
	}
}


void MS(vector<int>& Value, vector<string>& Date, int left, int right) {
	if (left < right) {
		int mid = left + (right - left) / 2;
		MS(Value, Date, left, mid);
		MS(Value, Date, mid + 1, right);
		Merge(Value, Date, left, mid, right);
	}
}


 int BIS(long int arr[], int lo , int hi,long int x)
{
    int i;
    int size = hi - lo + 1;
   long int next = ceil((size) * (x - lo/(hi-lo))) ;

    while(x!=arr[next]){
     i=0;    int size = hi - lo + 1 ; int o;
     int y = floor(sqrt(size));

    if(size <= 5){
        for (next = 0; o < size ; o++)
        if (arr[next] == x)
            return 1;
    }

    if(x>=arr[next]){
        while(x>arr[next+((i)*y)-1]){
            i=i+1;
            hi=next+((i)*y);
            lo=next+((i-1)*y);
        }
    }
   else if(x<arr[next]){
         while(x<arr[next-((i)*y)+1]){
            i=i+1;
            hi=next-((i-1)*y);
            lo=next-((i)*y);
         }
   }
             if(i%2 ==0){
                next=floor((lo+hi)/2);
             }
                else if(i%2 ==1){
                    next=floor(((x+arr[lo])/(arr[hi]-arr[lo]))*(hi-lo));
             }



    }

     if(x==arr[next])
        return 1;

    else return -1;

}




int main()
{


	string line;
	ifstream file("data.txt");
	if (!file.is_open())
	{
		cout << "\033[1;31mCould not open the file.\033[0m" << endl;
	}

	char delimeter = ',';


	vector <string> Date;

	vector <int> Value;



	cout << "\033[1;35mPlease wait.\033[0m"<<endl;

	getline(file, line);

	while (getline(file, line))
	{

		stringstream f(line);
		string data;
		vector <string> Test;

		while (getline(f, data, delimeter))
		{
			Test.push_back(data);
		}
		if (Test.size() >= 10)
		{
			Value.push_back(stoi(Test[Test.size() - 2]));


			Date.push_back(Test[2]);


		}


	}
	file.close();

	int max = *max_element(Value.begin(), Value.end());

	string algorithm;



	while (true)
	{
		cout << "\033[1;35mChoose what Algorithm you want to use\033[0m" << endl << "Type \033[1;33mCS\033[0m for \033[1;33mCounting Sort\033[0m or Type \033[1;34mMS\033[0m for \033[1;34mMerge Sort\033[0m:" << endl;
		cin >> algorithm;
		if (algorithm == "CS")
		{
			cout << "\033[1;35mPlease wait.\033[0m" << endl;
			CS(Value, Date, max);
			break;
		}
		else if (algorithm == "MS")
		{
			cout << "\033[1;35mPlease wait.\033[0m" << endl;
			MS(Value, Date, 0, Value.size() - 1);

			break;
		}

		else
		{
			cout << "\033[1;31mInvalid choice ,please choose again.\033[0m"<<endl;
		}

	}
int d = 0;
vector<string>:: iterator dat ;

string wd = "17/12/2015" ;

vector<long int> a ;

for(dat=Date.begin();dat<Date.end();dat++){
    if(wd==Date[d]){
        a.push_back(Value[d]);
    }
    d++;
}

vector< long int>::iterator val = a.begin();
d=0;

int n = a.size();

long int arr[n];


for(val=a.begin();val<a.end();val++){
    arr[d]=a[d];
    d++;
}



 long int wvalue = 1000;

 int index = BIS(arr,0,n-1,1000);



if (index < 0)
        cout << "Element not found  " ;
    else
        cout << "Element found ";

cout<< endl;

for(d=0;d<n;d++)
    cout<<arr[d]<<endl;

    cout<< index;



	return 0;
}
