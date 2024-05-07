#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;


//��� ��������� ��� ��������,����� Counting Sort ��� ����� 'Value' ���� ������ ����� �� �������� ��� �� ��������� ��� ����� 'Data' ��� ����� �� ���������
//����� ��������� �� ���� ���� ���� ��������� ��� Value �� �������� ��� �� �������� ��� Date,���� ���� ������������ ��� �������� ��� output 
//���� ������ ����������� ����� 
//���� ��� ����� ��� �� �������� ���� �� ����� ���� �� ���� ��� Date Vector ��� ��� ��������� ������ ��� �� ��� ��� ������ ��� ����� ��� ������ ����� 
//��� ��� ������ 3-6 ��������������� ��� � ������� ���� ������ ��� ��� ���� ������� ������ ����� ����������� ����� ��� �� ������� �� �� �� ������� ���� 
//�������������� ��� Date Vector ��� 2 ��� 6 ������ ��� ��� ��� ��������� ��� ���������� ��� ����� 2 ��� ����� �� ����� Date ��� ��� ������ �� �������


void CS(vector<int>& Value, vector<string>& Date, int max) {

	//���������� ��� ��� Vector ��� ��� ����� ��� ������ Value
	vector<int> count(max + 1, 0);

	//������������ ����� ����� ��������� ��� ����
	for (int value : Value) {
		count[value]++;
	}


	for (int i = 1; i <= max; i++) {
		count[i] += count[i - 1];
	}

	//���������� ��� Vector ��� ��� ����� ��� ������ Date
	vector<string> temp(Date.size());

	//���������� �� Date Vector ����� ��� ����� ��� ������ Values
	for (int i = Date.size() - 1; i >= 0; i--) {
		temp[count[Value[i]] - 1] = Date[i];
		count[Value[i]]--;
	}

	//������� ��� ����� ��� ���� Date ��� ����� Vector ��� ������ Date
	for (int i = 0; i < Date.size(); i++) {
		Date[i] = temp[i];
	}
}

//����� ������� �� ��������� ��� ��������� ��� ����� Merge � ����� �� ����� �������� ��� ��� ������� ��������� ��� �� ���������,��� Merge Sort
//�� ��� Merge �������� ��� vectors �� ��� ��� ���� ������������ ��������� �� �������� ��� �� ����� ����� ��� vector ��� ������� 
void Merge(vector<int>& Value, vector<string>& Date, int left, int mid, int right) {
	int n = mid - left + 1; //��������� �� �������� ��� �������� ������� 
	int m = right - mid; //��������� �� �������� ��� ����� ������� 

	vector<int> L(n); //���������� ��� int vector ��� �� �������� Values
	vector<int> R(m); //���������� ��� int vector ��� �� ����� Values
	vector<string> DateL(n); //���������� ��� string vector ��� �� �������� Dates
	vector<string> DateR(m); //���������� ��� string vector ��� �� ����� Dates

	for (int i = 0; i < n; i++) {
		L[i] = Value[left + i]; //�� �������� ����� ��� Value ���� ��� integer vector L
		DateL[i] = Date[left + i]; //�� �������� ����� ��� Date ���� ��� string vector DateL
	}

	for (int j = 0; j < m; j++) {
		R[j] = Value[mid + j + 1]; //�� ����� ����� ��� Value ���� ��� R
		DateR[j] = Date[mid + j + 1];//�� ����� ����� ��� Date ���� ��� DateR
	}

	int i = 0, j = 0, k = left;
	while (i < n && j < m) //����� �� ������� ��� ����� ��� vector �� L ��� Right ���������� �� ���������� ��� ���� �������� i � j ��� �� �����������
		//��� ����� vector
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
	//���� ���������� �� �������� ,������� �� �������� ��� Value[k] 
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
		int mid = left + (right - left) / 2; //��������� �� ������ �������� ����� �����
		MS(Value, Date, left, mid); //������� ��� MergeSort ��� �� �������� �������
		MS(Value, Date, mid + 1, right); //������� ��� MergeSort ��� �� ����� �������
		Merge(Value, Date, left, mid, right); //������� �� Merge ��� �� �������� �� 2 �������� �� ��� 
	}
}



int main()
{


	string line;
	ifstream file("data.txt"); //��������� �� file �� �� ����� data �� ����� ����� text file ������ .txt
	if (!file.is_open())    //���������� �� ����� �� �� file ������� � ���
	{
		cout << "\033[1;31mCould not open the file.\033[0m" << endl;
	}

	char delimeter = ','; //������� �� �������� �� ',' ,� ���� ����� �� �� ���������������� ���� ��� �� ��������� �� ������ �� ������,��� ����� ������� ������ �� ��������������� ����
	// �� ����� 'Date' ��� 'Value'


	//vector <string> Direction;
	//vector <int> Year;
	vector <string> Date;
	//vector <string> Weekday;
	//vector <string> Country;
	//vector <string> Commodity;
	//vector <string> Transport_Mode;
	//vector <string> Measure;
	vector <int> Value;
	//vector <int> Cumulative;

	//������������ ��� �������� �� �� ��� �� ������ �� ������ �� ������ ����� � ���� ����� 'Commodity' ���� �� ������� ������� ����� ',' ����� �� ������ �� ��� ����� ��������� 
	//��� �� ��� ������ ���� ������ ��������� �� ������� �� ������ ��� ��� ���� ��� �� ���� �� �������� ��� 'Date' �� ��� vector ��� ���� �� ������� �� ������ ������� ���
	//�� ���� �� �������� ��� 'Value' �� ��� ���� vector 

	cout << "\033[1;35mPlease wait.\033[0m"<<endl; //��� ������� ������� ��� cout ��� �� ����� ��� ���������� � ����������

	getline(file, line); //�������� ��� ����� ������ ��� �� ������������� �� Value �� int vector ����� � ����� ������ ���� ���� �� ������� ��� ���� ������

	//�� ����� ��� ������� �� ������������ �� int vector ����� ����� strings

	while (getline(file, line)) //��� ���� ������ ��� ������� ��� ����������
	{
		//cout << line << endl;  //�������������� ���� ��� ������ ��� �� ����� �� �� ����������� ����� ����
		stringstream f(line); //�� ���� ��� ������ ��������� ����� ������ ������ �� ���� line
		string data;
		vector <string> Test;

		while (getline(f, data, delimeter)) //�������� ���� ������ ��� ������� ��� ������ ���� ��� ','
		{
			Test.push_back(data); //������� ���� ����� �� ��� vector
		}
		if (Test.size() >= 10) //����������� ��� if ��� �������� ,�� ��������� ������ �������� ��� ����� �����
		{
			Value.push_back(stoi(Test[Test.size() - 2])); //������� ��� 2� ����� ��� �� ����� ��� ����� � 'Value' 

			//Date.push_back(Test[2]); //������� ��� 3� ����� ��� ��� ���� ��� ����� � 'Date'



			Date.push_back(Test[2] + Test[3]+Test[4]+Test[5]+Test[6]); //������� ��� ������ ��� 2 ��� 6 ��� �� ������������ ��� � ���������� ������ ����� 


		}
		
		
		//getline(f, data, delimeter);
		//getline(f, data, delimeter);
		//getline(f, data, delimeter); //������� ��� ����� ����� � ����� ����� �� ����� Date ��� ��� ����� ��� ����� �� ����� Value
		//Date.push_back((data));
		//getline(f, data, delimeter);
		//getline(f, data, delimeter);
		//getline(f, data, delimeter);
		///getline(f, data, delimeter);
		//getline(f, data, delimeter);
		//getline(f, data, delimeter);
		//Value.push_back((data));
	}
	file.close(); //��������� �� ������

	int max = *max_element(Value.begin(), Value.end());
	//int max = Value[0]; //��������� ��� ������� ���� ��� ������ 'Value'
	//for (int i = 1; i < Value.size(); i++) 
	//{
		//if (Value[i] > max)
		//{
			//max = Value[i];
		//}
	//}

	//int max1 = Value.size(); //��������� �� ������� ��� ������
	//int max2 = Date.size();
	//cout << max << endl;  //���������� �� ����� ���� ����� � ������� ���� ��� ������ Value ��� �� ����� �� ������ ����� 



	//for (int i = 0; i < Date.size(); i++) //�������� �� �� �������� ��� ������� ������ ��� ����� vector
	//{
	//	cout << Date[i] << "\t" << Value[i] << endl;
	//}


	string algorithm; //���������� ��� string ��� �� �������� � ������� ����� ��������� �� ������������



	while (true) //��� while ���� ���� � ������� �� ���� ��� ������� �� �������� ������� ����� 2 ����������� ��� �� ��� ������ ���� ��� ���� ��� �� ��� 
		//������� � ������� �� ������������
	{
		cout << "\033[1;35mChoose what Algorithm you want to use\033[0m" << endl << "Type \033[1;33mCS\033[0m for \033[1;33mCounting Sort\033[0m or Type \033[1;34mMS\033[0m for \033[1;34mMerge Sort\033[0m:" << endl;
		cin >> algorithm;
		if (algorithm == "CS") //�� �������� ��� CS=Counting Sort ���� �� ��������� ��� ��������� CS ��� �� ����� � ���������� �����
		{
			cout << "\033[1;35mPlease wait.\033[0m" << endl;
			CS(Value, Date, max); //�������� � ��������� Counting Sort
			cout << "The Sorted Collumn is:" << endl;
			for (int i = 0; i < Date.size(); i++)
			{
				cout << "\033[1;31mDate:\033[0m" << "\033[1;33m"<< Date[i]<<"\033[0m" << endl;
			}
			break; //������ ��� ��� while 
		}
		else if (algorithm == "MS") //�� �������� ��� MS=MergeSort ���� �� ��������� ��� ��������� MS ��� �� ����� � ���������� �����
		{
			cout << "\033[1;35mPlease wait.\033[0m" << endl;
			MS(Value, Date, 0, Value.size() - 1);
			cout << "The Sorted Collumn is:" << endl;
			for (int i = 0; i < Date.size(); i++)
			{
				cout <<"\033[1;31mDate:\033[0m" << "\033[1;34m" << Date[i] << "\033[0m" << endl;
			}
			break; //������ ��� ��� while 
		}

		else //������ ������ �� ��������� ���������� ��� ����� ����� � ������� ��� ��� ���� ����� �� ��������
		{
			cout << "\033[1;31mInvalid choice ,please choose again.\033[0m"<<endl;
		}
	}
	return 0;
}
