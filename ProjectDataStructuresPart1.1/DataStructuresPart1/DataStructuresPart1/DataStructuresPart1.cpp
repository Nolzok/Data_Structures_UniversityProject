#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;


//εδώ συνάντησα ένα πρόβλημα,έκανα Counting Sort στο πεδίο 'Value' αλλά έπρεπε κάπως να γίνονται και οι εναλλαγές στο πεδίο 'Data' που είναι το ζητούμενο
//οπότε αποφάσισα να βάλω μέσα στις εναλλαγές του Value να αλλάζουν και τα στοιχεία του Date,όμως μετά αντιμετώπισα ενα πρόβλημα στο output 
//όπου έβγαζε λανθασμένες τιμές 
//αυτό που έκανα για να διορθώσω αυτό το λάθος ήταν να βάλω στο Date Vector και τις υπόλοιπες στήλες για να βρω πιο εύκολα τις τιμές και αφότου έβαλα 
//και τις στήλες 3-6 συνειδητοποίησα ότι ο κώδικας ήταν σωστός και ότι απλά υπήρχαν πολλές ίδιες ημερομηνίες οπότε για να τεστάρω να δω αν υπήρχαν λάθη 
//χρησιμοποιούσα σαν Date Vector τις 2 εώς 6 στήλες και για την υλοποίηση του ερωτήματος την στήλη 2 που ειναι το πεδίο Date που μας ζητάει το ερώτημα


void CS(vector<int>& Value, vector<string>& Date, int max) {

	//φτιάχνουμε ένα νέο Vector για τις τιμές του πεδίου Value
	vector<int> count(max + 1, 0);

	//αποθηκεύουμε πόσες φορές συναντάμε μία τιμή
	for (int value : Value) {
		count[value]++;
	}


	for (int i = 1; i <= max; i++) {
		count[i] += count[i - 1];
	}

	//φτιάχνουμε ένα Vector για τις τιμές του πεδίου Date
	vector<string> temp(Date.size());

	//φτιάχνουμε το Date Vector βάσει των τιμών του πεδίου Values
	for (int i = Date.size() - 1; i >= 0; i--) {
		temp[count[Value[i]] - 1] = Date[i];
		count[Value[i]]--;
	}

	//βάζουμε τις τιμές του νέου Date στο παλιό Vector του πεδίου Date
	for (int i = 0; i < Date.size(); i++) {
		Date[i] = temp[i];
	}
}

//πρώτα θέλουμε να φτιάξουμε μία συνάρτηση που κάνει Merge η οποία θα είναι αναγκαία για την επόμενη συνάρτηση που θα φτιάξουμε,την Merge Sort
//με την Merge ενώνουμε δύο vectors σε ένα και στην συγκεκριμένη περίπτωση το αριστερά και το δεξιά μέρος του vector που θέλουμε 
void Merge(vector<int>& Value, vector<string>& Date, int left, int mid, int right) {
	int n = mid - left + 1; //χωρίζουμε τα στοιχεία στο αριστερό κομμάτι 
	int m = right - mid; //χωρίζουμε τα στοιχεία στο δεξιά κομμάτι 

	vector<int> L(n); //φτιάχνουμε ένα int vector για τα αριστερά Values
	vector<int> R(m); //φτιάχνουμε ένα int vector για τα δεξιά Values
	vector<string> DateL(n); //φτιάχνουμε ένα string vector για τα αριστερά Dates
	vector<string> DateR(m); //φτιάχνουμε ένα string vector για τα δεξιά Dates

	for (int i = 0; i < n; i++) {
		L[i] = Value[left + i]; //το αριστερά μέρος του Value πάει στο integer vector L
		DateL[i] = Date[left + i]; //το αριστερά μέρος του Date παει στο string vector DateL
	}

	for (int j = 0; j < m; j++) {
		R[j] = Value[mid + j + 1]; //το δεξιά μέρος του Value πάει στο R
		DateR[j] = Date[mid + j + 1];//το δεξιά μέρος του Date πάει στο DateR
	}

	int i = 0, j = 0, k = left;
	while (i < n && j < m) //μέχρι να φτάσουν στο τέλος του vector τα L και Right διαλέγουμε το μεγαλύτερο απο κάθε στοιχείο i ή j και το τοποθετούμε
		//στο σωστό vector
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
	//όταν τελειώσουν τα στοιχεία ,βάζουμε τα υπόλοιπα στο Value[k] 
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
		int mid = left + (right - left) / 2; //βρίσκουμε το μεσαίο στοιχείο βάσει τιμής
		MS(Value, Date, left, mid); //καλούμε τον MergeSort για το αριστερό κομμάτι
		MS(Value, Date, mid + 1, right); //καλούμε τον MergeSort για το δεξιά κομμάτι
		Merge(Value, Date, left, mid, right); //καλούμε το Merge για να ενώσουμε τα 2 κομμάτια σε ένα 
	}
}



int main()
{


	string line;
	ifstream file("data.txt"); //ανοίγουμε το file με το όνομα data το οποίο ειναι text file δηλαδή .txt
	if (!file.is_open())    //τεστάρουμε να δούμε αν το file ανοίγει ή όχι
	{
		cout << "\033[1;31mCould not open the file.\033[0m" << endl;
	}

	char delimeter = ','; //θέτουμε ως χαρκτήρα το ',' ,η ιδέα είναι να το χρησιμοποιήσουμε αυτό για να χωρίσουμε το αρχείο σε στήλες,στο πρώτο ερώτημα βέβαια θα χρησιμοποίσουμε μόνο
	// τα πεδία 'Date' και 'Value'


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

	//Αντιμετώπισα ένα πρόβλημα με το πως θα χωρίσω το αρχείο σε στήλες καθώς η έκτη στήλη 'Commodity' έχει σε μερικές γραμμές πολλά ',' οπότε θα πρέπει να βρω άλλον χαρακτήρα 
	//για να την χωρίσω αλλά τελικά αποφάσισα να διαβάσω το αρχείο από την αρχή για να βάλω τα στοιχεία του 'Date' σε ένα vector και μετά να διαβάσω το αρχείο ανάποδα και
	//να βαλω τα στοιχεία του 'Value' σε ένα άλλο vector 

	cout << "\033[1;35mPlease wait.\033[0m"<<endl; //εδώ τέσταρα χρώματα στο cout για να είναι πιο κατανοητός ο αλγόριθμος

	getline(file, line); //σβήνουμε την πρώτη γραμμή για να αποθηκεύσουμε τα Value σε int vector διότι η πρώτη γραμμή έχει απλά τα ονόματα της κάθε στήλης

	//τα οποία δεν μπορούν να αποθηκευτούν σε int vector γιατί είναι strings

	while (getline(file, line)) //για κάθε γραμμή του αρχείου την διαβάζουμε
	{
		//cout << line << endl;  //χρησιμοποιούμε αυτή την εντολή για να δούμε αν τα περιεχόμενα είναι ίδια
		stringstream f(line); //με αυτή την εντολή βρίσκουμε ποσες λέξεις έχουμε σε κάθε line
		string data;
		vector <string> Test;

		while (getline(f, data, delimeter)) //διαβάζει κάθε γραμμή και χωρίζει τις στήλες μέσω του ','
		{
			Test.push_back(data); //βάζουμε κάθε στήλη σε ένα vector
		}
		if (Test.size() >= 10) //χρησιμοποιώ την if για σιγουριά ,το πρόγραμμα τρέχει κανονικά και χωρίς αυτήν
		{
			Value.push_back(stoi(Test[Test.size() - 2])); //βάζουμε την 2η στήλη από το τέλος που είναι η 'Value' 

			//Date.push_back(Test[2]); //βάζουμε την 3η στήλη απο την αρχή που ειναι η 'Date'



			Date.push_back(Test[2] + Test[3]+Test[4]+Test[5]+Test[6]); //βάζουμε τις στήλες απο 2 εώς 6 για να σιγουρέψουμε ότι ο αλγόριθμος τρέχει σωστά 


		}
		
		
		//getline(f, data, delimeter);
		//getline(f, data, delimeter);
		//getline(f, data, delimeter); //θέλουμε την τρίτη στήλη η οποία είναι το πεδίο Date και την ένατη που ειναι το πεδίο Value
		//Date.push_back((data));
		//getline(f, data, delimeter);
		//getline(f, data, delimeter);
		//getline(f, data, delimeter);
		///getline(f, data, delimeter);
		//getline(f, data, delimeter);
		//getline(f, data, delimeter);
		//Value.push_back((data));
	}
	file.close(); //κλείνουμε το αρχείο

	int max = *max_element(Value.begin(), Value.end());
	//int max = Value[0]; //βρίσκουμε την μέγιστη τιμή του πεδίου 'Value'
	//for (int i = 1; i < Value.size(); i++) 
	//{
		//if (Value[i] > max)
		//{
			//max = Value[i];
		//}
	//}

	//int max1 = Value.size(); //βρίσκουμε το μέγεθος της στήλης
	//int max2 = Date.size();
	//cout << max << endl;  //τεστάρουμε να δούμε ποια είναι η μέγιστη τιμή του πεδίου Value για να δούμε αν κάναμε λάθος 



	//for (int i = 0; i < Date.size(); i++) //Βλέπουμε αν τα στοιχεία που θέλουμε μπήκαν στο σωστό vector
	//{
	//	cout << Date[i] << "\t" << Value[i] << endl;
	//}


	string algorithm; //φτιάχνουμε ένα string για να διαλέγει ο χρήστης ποιον αλγόριθμο να χρησιμοποιεί



	while (true) //μία while έτσι ώστε ο χρήστης να έχει την επιλογή να διαλέξει ανάμεσα στους 2 αλγορίθμους και αν δεν γράψει έναν από τους δύο να του 
		//δίνεται η επιλογή να ξαναδιαλέξει
	{
		cout << "\033[1;35mChoose what Algorithm you want to use\033[0m" << endl << "Type \033[1;33mCS\033[0m for \033[1;33mCounting Sort\033[0m or Type \033[1;34mMS\033[0m for \033[1;34mMerge Sort\033[0m:" << endl;
		cin >> algorithm;
		if (algorithm == "CS") //αν διαλέξει τον CS=Counting Sort τότε θα καλέσουμε την συνάρτηση CS και θα γίνει ο αλγόριθμος αυτος
		{
			cout << "\033[1;35mPlease wait.\033[0m" << endl;
			CS(Value, Date, max); //καλείται η συνάρτηση Counting Sort
			cout << "The Sorted Collumn is:" << endl;
			for (int i = 0; i < Date.size(); i++)
			{
				cout << "\033[1;31mDate:\033[0m" << "\033[1;33m"<< Date[i]<<"\033[0m" << endl;
			}
			break; //φεύγει από την while 
		}
		else if (algorithm == "MS") //αν διαλέξει τον MS=MergeSort τότε θα καλέσουμε την συνάρτηση MS και θα γίνει ο αλγόριθμος αυτος
		{
			cout << "\033[1;35mPlease wait.\033[0m" << endl;
			MS(Value, Date, 0, Value.size() - 1);
			cout << "The Sorted Collumn is:" << endl;
			for (int i = 0; i < Date.size(); i++)
			{
				cout <<"\033[1;31mDate:\033[0m" << "\033[1;34m" << Date[i] << "\033[0m" << endl;
			}
			break; //φεύγει από την while 
		}

		else //αλλιώς βγάζει το πρόγραμμα ειδοποίηση ότι έκανε λάθος ο χρήστης και τον ξανά βάζει να διαλέξει
		{
			cout << "\033[1;31mInvalid choice ,please choose again.\033[0m"<<endl;
		}
	}
	return 0;
}
