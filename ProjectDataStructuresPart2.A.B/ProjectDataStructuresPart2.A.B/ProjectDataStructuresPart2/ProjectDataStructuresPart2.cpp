#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string.h>
#include<math.h>
#include <queue>


using namespace std;

string c;
string choice;
int condition = 0;

struct Node
{

    int date;
    int value;
    Node* left;
    Node* right;
    int height;
};

Node* node = nullptr;
Node* externalNode = nullptr;
Node* newNode(int date, int value)
{
    Node* node = new Node();
    node->date = date;
    node->value = value;
    node->left = node->right = nullptr;
    node->height = 1;

    return(node);
}

int Kdate(string data) {

    string d;
    string  day = (data.substr(0, 2));
    string  month = (data.substr(3, 2));
    string year = (data.substr(6));


    d = year + month + day;

    int a = stoi(d);


    return a;
}
void minimum(Node* root) {
    string det = to_string(root->date);
    int Min = 0;
    if (root->value == Min) {
        cout << "The date with the minimum value is: " << "\033[1;32m Date: \033[0m" << det[6] << det[7] << "/" << det[4] << det[5] << "/" << det[0] << det[1] << det[2] << det[3] << endl;
    }

    minimum(root->left);
    minimum(root->right);


}

void maximum(Node* root) {
    string det = to_string(root->date);
    long int Max = 549000000;
    if (root->value == Max) {
        cout << "The date with the maximum value is: " << "\033[1;32m Date: \033[0m" << det[6] << det[7] << "/" << det[4] << det[5] << "/" << det[0] << det[1] << det[2] << det[3] << endl;
    }



    maximum(root->left);
    maximum(root->right);

}



int height(Node* N)
{
    if (N == nullptr)
        return 0;
    return N->height;
}

int max(int a, int b)
{
    return (a > b) ? a : b;
}

Node* rightRotate(Node* y)
{
    Node* x = y->left;
    Node* T2 = x->right;

    // Perform rotation
    x->right = y;
    y->left = T2;

    // Update heights
    y->height = max(height(y->left),
        height(y->right)) + 1;
    x->height = max(height(x->left),
        height(x->right)) + 1;

    // Return new root
    return x;
}

Node* leftRotate(Node* x)
{
    Node* y = x->right;
    Node* T2 = y->left;

    // Perform rotation
    y->left = x;
    x->right = T2;

    // Update heights
    x->height = max(height(x->left),
        height(x->right)) + 1;
    y->height = max(height(y->left),
        height(y->right)) + 1;

    // Return new root
    return y;
}

int getBalance(Node* N)
{
    if (N == nullptr)
        return 0;
    return height(N->left) - height(N->right);
}

Node* insertD(Node* node, int date, int value)
{
    /* 1. Perform the normal BST insertion */
    if (node == NULL)
        return(newNode(date, value));

    if (date < node->date)
        node->left = insertD(node->left, date, value);
    else if (date > node->date)
        node->right = insertD(node->right, date, value);
    else // Equal keys are not allowed in BST
        return node;

    /* 2. Update height of this ancestor node */
    node->height = 1 + max(height(node->left),
        height(node->right));


    int balance = getBalance(node);

    // If this node becomes unbalanced, then
    // there are 4 cases

    // Left Left Case
    if (balance > 1 && date < node->left->date)
        return rightRotate(node);

    // Right Right Case
    if (balance < -1 && date > node->right->date)
        return leftRotate(node);

    // Left Right Case
    if (balance > 1 && date > node->left->date)
    {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // Right Left Case
    if (balance < -1 && date < node->right->date)
    {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    /* return the (unchanged) node pointer */
    return node;
}

Node* insertV(Node* node, int date, int value)
{
    /* 1. Perform the normal BST insertion */
    if (node == NULL)
        return(newNode(date, value));

    if (value < node->value)
        node->left = insertV(node->left, date, value);
    else if (value > node->value)
        node->right = insertV(node->right, date, value);
    else // Equal keys are not allowed in BST
        return node;

    /* 2. Update height of this ancestor node */
    node->height = 1 + max(height(node->left),
        height(node->right));


    int balance = getBalance(node);

    // If this node becomes unbalanced, then
    // there are 4 cases

    // Left Left Case
    if (balance > 1 && value < node->left->value)
        return rightRotate(node);

    // Right Right Case
    if (balance < -1 && value > node->right->value)
        return leftRotate(node);

    // Left Right Case
    if (balance > 1 && value > node->left->value)
    {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // Right Left Case
    if (balance < -1 && value < node->right->value)
    {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    /* return the (unchanged) node pointer */
    return node;
}

Node* findMinNode(Node* node) {
    Node* current = node;
    while (current->left != nullptr)
        current = current->left;
    return current;
}

// Function to delete a node from the AVL tree
Node* deleteNode(Node* root, int date) {
    // Perform the normal BST delete
    if (root == nullptr)
        return root;

    if (date < root->date)
        root->left = deleteNode(root->left, date);
    else if (date > root->date)
        root->right = deleteNode(root->right, date);
    else {
        // Node to be deleted found
        // Case 1: Node with only one child or no child
        if ((root->left == nullptr) || (root->right == nullptr)) {
            Node* temp = root->left ? root->left : root->right;

            // No child case
            if (temp == nullptr) {
                temp = root;
                root = nullptr;
            }
            else // One child case
                *root = *temp; // Copy the contents of the non-empty child

            delete temp;
        }
        else {
            // Case 2: Node with two children
            Node* temp = findMinNode(root->right);

            // Copy the successor's data to this node
            root->date = temp->date;
            root->value = temp->value;

            // Delete the successor
            root->right = deleteNode(root->right, temp->date);
        }
    }

    // If the tree had only one node, return
    if (root == nullptr)
        return root;

    // Update the height of the current node
    root->height = 1 + max(height(root->left), height(root->right));

    // Check the balance factor and perform rotations if needed
    int balance = getBalance(root);

    // Left Left Case
    if (balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root);

    // Left Right Case
    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    // Right Right Case
    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);

    // Right Left Case
    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    // Return the unchanged node pointer
    return root;
}

// Function to search for a node in the AVL tree
Node* searchNode(Node* root, int date) {
    if (root == nullptr || root->date == date)
        return root;

    if (date < root->date)
        return searchNode(root->left, date);
    else
        return searchNode(root->right, date);

}

// Function to depict the AVL tree level by level
/*void depictTree(Node* root) {
    if (root == nullptr)
        return;

    queue <Node*> q;
    q.push(root);

    while (!q.empty()) {
        int count = q.size();

        while (count > 0) {
            Node* node = q.front();
            std::cout << "Date: " << node->date << ", Value: " << node->value << " | ";
            q.pop();

            if (node->left != nullptr)
                q.push(node->left);

            if (node->right != nullptr)
                q.push(node->right);

            count--;
        }

        cout <<endl;
    }
}*/

// Function to modify the value of a node in the AVL tree
Node* modifyNode(Node* root, int date, int newValue) {
    Node* node = searchNode(root, date);

    if (node != nullptr)
    {
        cout << "Node with date " << date << " found! Value: " << node->value << endl;
        node->value = newValue;
    }
    else if (node == nullptr)
    {
        cout << "Node with date " << date << " not found.\n";
        return 0;
    }
    return root;
}

// Function to print the AVL tree in inorder traversal
void printInorder(Node* root) {
    if (root == nullptr)
        return;
    string det = to_string(root->date);
    printInorder(root->left);

    cout << "\033[1;32m Date: \033[0m" << det[6] << det[7] << "/" << det[4] << det[5] << "/" << det[0] << det[1] << det[2] << det[3] << "\033[1;32m Value: \033[0m" << root->value << endl;
    printInorder(root->right);

}

void findNode(Node* root, int searchDate) {

    Node* searchedNode = searchNode(root, searchDate);
    if (searchedNode != nullptr)
        cout << "Node with date " << searchDate << " found! Value: " << searchedNode->value << endl;
    else
    {
        cout << "Node with date " << searchDate << " not found.\n";
        condition = 1;
    }
}

void Choice(string s) {


    int num;
    if (s == "Modification")
        num = 1;
    else if (s == "Depiction")
        num = 2;
    else if (s == "Deletion")
        num = 3;
    else if (s == "Search")
        num = 4;
    else if (s == "Exit")
        num = 5;
    else
        num = 6;
    switch (num)
    {



    case 1://Modification
        cout << "running..." << endl;
        int modifyDate;
        int newValue;
        cout << "Enter the date you want to modify:\n";
        cin >> modifyDate;
        searchNode(node, modifyDate);
        findNode(node, modifyDate);
        if (condition == 1) { goto next; }
        cout << "Enter the new value\n";
        cin >> newValue;
        node = modifyNode(node, modifyDate, newValue);
        cout << "AVL tree after modifing node with date " << modifyDate << ":\n";
        printInorder(node);
    next:
        cout << "\033[1;4;33m\n\t\t Choose the preferable action:\n\033[0m""\033[1;31m !!!\033[0m"" \033[1;4;33mWrite\033[0m"" ""\033[1;4;31m Modification\033[0m" "\033[1;4;33m to modify a node,\033[0m"" ""\033[1;4;31mDepiction \033[0m""\033[1;4;33m to depict a node,\033[0m"" ""\033[1;4;31mDeletion \033[0m""\033[1;4;33m to delete a node,\033[0m"" ""\n\033[1;4;31mSearch\033[0m""\033[1;4;33m to search for a node,\033[0m"" ""\033[1;4;31mExit\033[0m""\033[1;4;33m to exit the program,\033[0m""\033[1;31m !!!\033[0m" << endl;

        cin >> c;
        Choice(c);

        break;


    case 2://Depiction

        cout << "running..." << endl;
        cout << "AVL tree in inorder traversal:\n";
        printInorder(node);
        cout << "\033[1;4;33m\n\t\t Choose the preferable action:\n\033[0m""\033[1;31m !!!\033[0m"" \033[1;4;33mWrite\033[0m"" ""\033[1;4;31m Modification\033[0m" "\033[1;4;33m to modify a node,\033[0m"" ""\033[1;4;31mDepiction \033[0m""\033[1;4;33m to depict a node,\033[0m"" ""\033[1;4;31mDeletion \033[0m""\033[1;4;33m to delete a node,\033[0m"" ""\n\033[1;4;31mSearch\033[0m""\033[1;4;33m to search for a node,\033[0m"" ""\033[1;4;31mExit\033[0m""\033[1;4;33m to exit the program,\033[0m""\033[1;31m !!!\033[0m" << endl;

        cin >> c;
        Choice(c);

        break;


    case 3://Deletion

        cout << "running..." << endl;
        int deleteDate;
        cout << "Enter the date you want to delete:" << endl;
        cin >> deleteDate;
        node = deleteNode(node, deleteDate);
        cout << "AVL tree after deleting node with date " << deleteDate << ":\n";
        printInorder(node);
        cout << "\033[1;4;33m\n\t\t Choose the preferable action:\n\033[0m""\033[1;31m !!!\033[0m"" \033[1;4;33mWrite\033[0m"" ""\033[1;4;31m Modification\033[0m" "\033[1;4;33m to modify a node,\033[0m"" ""\033[1;4;31mDepiction \033[0m""\033[1;4;33m to depict a node,\033[0m"" ""\033[1;4;31mDeletion \033[0m""\033[1;4;33m to delete a node,\033[0m"" ""\n\033[1;4;31mSearch\033[0m""\033[1;4;33m to search for a node,\033[0m"" ""\033[1;4;31mExit\033[0m""\033[1;4;33m to exit the program,\033[0m""\033[1;31m !!!\033[0m" << endl;

        cin >> c;
        Choice(c);

        break;

    case 4://Search

        cout << "running..." << endl;
        int searchDate;
        cout << "Enter the date you want to search:(in this form: 20150101 for 01/01/2015)" << endl;
        cin >> searchDate;
        searchNode(node, searchDate);
        findNode(node, searchDate);
        cout << "\033[1;4;33m\n\t\t Choose the preferable action:\n\033[0m""\033[1;31m !!!\033[0m"" \033[1;4;33mWrite\033[0m"" ""\033[1;4;31m Modification\033[0m" "\033[1;4;33m to modify a node,\033[0m"" ""\033[1;4;31mDepiction \033[0m""\033[1;4;33m to depict a node,\033[0m"" ""\033[1;4;31mDeletion \033[0m""\033[1;4;33m to delete a node,\033[0m"" ""\n\033[1;4;31mSearch\033[0m""\033[1;4;33m to search for a node,\033[0m"" ""\033[1;4;31mExit\033[0m""\033[1;4;33m to exit the program,\033[0m""\033[1;31m !!!\033[0m" << endl;

        cin >> c;
        Choice(c);

        break;

    case 5://Exit

        break;


    default:
        cout << "\033[1;31m               ***Wrong input***\033[0m" << endl;
        cout << "\033[1;4;33m\n\t\t Choose the preferable action:\n\033[0m""\033[1;31m !!!\033[0m"" \033[1;4;33mWrite\033[0m"" ""\033[1;4;31m Modification\033[0m" "\033[1;4;33m to modify a node,\033[0m"" ""\033[1;4;31mDepiction \033[0m""\033[1;4;33m to depict a node,\033[0m"" ""\033[1;4;31mDeletion \033[0m""\033[1;4;33m to delete a node,\033[0m"" ""\n\033[1;4;31mSearch\033[0m""\033[1;4;33m to search for a node,\033[0m"" ""\033[1;4;31mExit\033[0m""\033[1;4;33m to exit the program,\033[0m""\033[1;31m !!!\033[0m" << endl;

        cin >> c;
        Choice(c);

        break;
    }



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
    cout << "\033[1;32m Please wait...\033[0m" << endl;

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
    int i = 0;

    vector<int> intdate;

    vector<string>::iterator r;

    for (r = Date.begin(); r < Date.end(); r++) {
        int a = Kdate(Date[i]);
        i++;
        intdate.push_back(a);
    }

    i = 0;
    cout << "\033[1;4;33m\n\t\t Choose the sorting method:\n\033[0m""\033[1;31m !!!\033[0m"" \033[1;4;33mWrite\033[0m"" ""\033[1;4;31m ByDate\033[0m" "\033[1;4;33m to sort by date,\033[0m"" ""\033[1;4;31mByValue\033[0m""\033[1;4;33m to sort by value!!!\033[0m" << endl;
next1:
    cin >> c;

    int num1;
    if (c == "ByValue")
        num1 = 1;
    else if (c == "ByDate")
        num1 = 2;
    else
        num1 = 3;

    switch (num1)
    {



    case 1://ByValue

        for (r = Date.begin(); r < Date.end(); r++) {

            node = insertV(node, intdate[i], Value[i]);
            i++;

        }

        break;


    case 2://ByDate

        for (r = Date.begin(); r < Date.end(); r++) {

            node = insertD(node, intdate[i], Value[i]);
            i++;

        }


        break;

    default:
        cout << "\033[1;31m               ***Wrong input***\033[0m" << endl;
        cout << "\033[1;4;33m\n\t\t Choose the sorting method:\n\033[0m""\033[1;31m !!!\033[0m"" \033[1;4;33mWrite\033[0m"" ""\033[1;4;31m ByDate\033[0m" "\033[1;4;33m to sort by date,\033[0m"" ""\033[1;4;31mByValue\033[0m""\033[1;4;33m to sort by value!!!\033[0m" << endl;

        goto next1;


        break;
    }





    cout << "\033[1;4;33m\n\t\t Choose the preferable action:\n\033[0m""\033[1;31m !!!\033[0m"" \033[1;4;33mWrite\033[0m"" ""\033[1;4;31m Modification\033[0m" "\033[1;4;33m to modify a node,\033[0m"" ""\033[1;4;31mDepiction \033[0m""\033[1;4;33m to depict a node,\033[0m"" ""\033[1;4;31mDeletion \033[0m""\033[1;4;33m to delete a node,\033[0m"" ""\n\033[1;4;31mSearch\033[0m""\033[1;4;33m to search for a node,\033[0m"" ""\033[1;4;31mExit\033[0m""\033[1;4;33m to exit the program,\033[0m""\033[1;31m !!!\033[0m" << endl;
    cin >> choice;
    Choice(choice);


   // maximum(node);

   // minimum(node);








    return 0;
}
