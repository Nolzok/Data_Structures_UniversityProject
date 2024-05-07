#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <sstream>
#include <vector>
#include <cstring>
using namespace std;

vector <string> Date;
vector <string> Requested;
vector <double> Cumulative;
string choice;




void printVector(vector<string> arr1)
    {
        for (int i = 0; i < arr1.size(); i++) {
            cout << arr1[i] << " ";
           
            cout << endl;
        }
        
    }



  
 void heapify(vector<double>& arr, vector<string>& arr1, double n, double i)
 {
    
     double largest = i;  // Initialize largest as root
     double l = 2 * i + 1;  // left child
     double r = 2 * i + 2;  // right child
    

     
     if (l < n && arr[l] > arr[largest]) {
         
         largest = l;
       
     }
    
        
  

    
     if (r < n && arr[r] > arr[largest]) {
         largest = r;
       
     }
   
        
     

    
     if (largest != i ) {
         
         swap(arr[i], arr[largest]);
         swap(arr1[i], arr1[largest]);
         
         heapify(arr,arr1, n, largest);
     }
   
 }


 void heapSort(vector<double>& arr, vector<string>& arr1)
 {
     double n = 111438.00;
     cout << n << endl;
     double i = n / 2.000 - 1.000;
     for (i; i >= 0; i--)
         heapify(arr,arr1, n, i);

    
     for (double i = n - 1; i >= 0; i--) {
         swap(arr1[0], arr1[i]);
         swap(arr[0], arr[i]);
        

       
         heapify(arr,arr1, i, 0);
     }
 }

 void HeapSort(vector<double>& arr, vector<string>& arr1) {
     heapSort(arr,arr1);
     printVector(arr1);

 }

 int partition(vector<string>& date, vector<double>& cumulative, int low, int high) {
    double pivot = cumulative[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (cumulative[j] < pivot) {
            i++;
            swap(cumulative[i], cumulative[j]);
            swap(date[i], date[j]);
        }
    }
    swap(cumulative[i + 1], cumulative[high]);
    swap(date[i + 1], date[high]);
    return i + 1;
}

void quickSort(vector<string>& date, vector<double>& cumulative, int low, int high) {
    if (low < high) {
        int pi = partition(date, cumulative, low, high);
        quickSort(date, cumulative, low, pi - 1);
        quickSort(date, cumulative, pi + 1, high);
    }
}


 void Quicksort(vector<double> cumulative, vector<string>& date) {
     quickSort(date, cumulative,0,cumulative.size()-1);
     printVector(date);
 }


 void Choice(string s) {
    

      int num;
       if (s == "HS")
         num = 1;
       else if (s == "QS")
         num = 2;
       else
         num = 3;

       switch (num)
       {



       case 1:

           cout << "running..." << endl;
           HeapSort(Cumulative, Requested);
           

           break;


       case 2:

           cout << "running..." << endl;
           Quicksort(Cumulative, Requested);

           break;



       default:
         
           
               cout << "\033[1;31m               ***Wrong input***\033[0m" << endl;
               cout << "\033[1;4;33m\n\t Choose the preferable sorting method:\n\033[0m""\033[1;31m !!!\033[0m"" \033[1;4;33mWrite\033[0m" "\033[1;4;31m HS \033[0m" "\033[1;4;33mfor Heap Sort or" "\033[1;4;31m QS \033[0m""\033[1;4;33m for Quick Sort\033[0m""\033[1;31m !!!\033[0m" << endl;
               cin >> s;
               Choice(s);
           
           break;
       }
     

     
 }

int main()
{


    string line;
    ifstream file("data.txt");
    if (!file.is_open())
    {
        cout << "Could not open the file." << endl;
    }

    char delimeter = ',';




    cout << "\033[1;32m Please wait...\033[0m" << endl;

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

            Cumulative.push_back(stod(Test[Test.size() - 1])); 

            
            Requested.push_back("\033[1;32m Date: \033[0m"+  Test[2] + " " + "\033[1;32m Cumulative: \033[0m" + (Test[Test.size() - 1]));
            


            

        }



    }
    file.close();

   
    cout << "\033[1;4;33m\n\t Choose the preferable sorting method:\n\033[0m""\033[1;31m !!!\033[0m"" \033[1;4;33mWrite\033[0m" "\033[1;4;31m HS \033[0m" "\033[1;4;33mfor Heap Sort or" "\033[1;4;31m QS \033[0m""\033[1;4;33m for Quick Sort\033[0m""\033[1;31m !!!\033[0m" << endl;
    cin >> choice;
    Choice(choice);


}








  












