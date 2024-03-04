#include <bits/stdc++.h>
using namespace std;
#define ll long long int
#define endl '\n'

typedef struct Student
{
    string name;
    int roll;
    string dob;
    int marks;
    struct Student *next;
} Student;

Student *head = NULL;
Student *tail = NULL;

void printHead()
{
    cout << endl;
    cout << "====================================================================================================" << endl;
    cout << "|" << setw(24) << "Name |" << setw(25) << "Roll |" << setw(25) << "Total Marks |" << setw(25) << "DOB |" << endl;
    cout << "====================================================================================================" << endl;
}

void printRow(Student *temp)
{
    string name = temp->name + " |";
    string roll = to_string(temp->roll) + " |";
    string marks = to_string(temp->marks) + " |";
    string dob = temp->dob + " |";
    cout
        << "|" << setw(24) << name << setw(25) << roll << setw(25) << marks << setw(25) << dob << endl;
    cout << "----------------------------------------------------------------------------------------------------" << endl;
}

void printSheet()
{
    printHead();
    Student *temp = head;
    while (temp)
    {
        printRow(temp);
        temp = temp->next;
    }
}

void findByRoll()
{
    int roll;
    cout << "Enter roll to find: ";
    cin >> roll;
    Student *temp = head;
    while (temp)
    {
        if (temp->roll == roll)
        {
            printHead();
            printRow(temp);
            return;
        }
        temp = temp->next;
    }
    cout << endl
         << "No data found with this roll!" << endl;
}

void addRows()
{
    Student *t = new Student();
    cout << "Enter name: ";
    cin >> t->name;
    cout << "Enter roll: ";
    cin >> t->roll;
    cout << "Enter total marks: ";
    cin >> t->marks;
    cout << "Enter DOB (DD/MM/YYYY): ";
    cin >> t->dob;
    if (!head)
    {
        head = t;
        tail = t;
        return;
    }
    tail->next = t;
    tail = tail->next;
}
void FrontBackSplit(Student *source, Student **frontRef, Student **backRef)
{
    Student *fast;
    Student *slow;
    slow = source;
    fast = source->next;
    while (fast != NULL)
    {
        fast = fast->next;
        if (fast != NULL)
        {
            slow = slow->next;
            fast = fast->next;
        }
    }
    *frontRef = source;
    *backRef = slow->next;
    slow->next = NULL;
}

Student *SortedMerge(Student *a, Student *b, int option)
{
    Student *result = NULL;
    if (a == NULL)
        return (b);
    else if (b == NULL)
        return (a);
    if ((option == 4 && a->roll <= b->roll) || (option == 5 && a->marks <= b->marks))
    {
        result = a;
        result->next = SortedMerge(a->next, b, option);
    }
    else
    {
        result = b;
        result->next = SortedMerge(a, b->next, option);
    }
    return (result);
}

void MergeSort(int option)
{
    Student *temp = head;
    Student *a;
    Student *b;
    if ((temp == NULL) || (temp->next == NULL))
    {
        return;
    }
    FrontBackSplit(temp, &a, &b);
    MergeSort(option);
    MergeSort(option);
    head = SortedMerge(a, b, option);
}

void deleteByRoll()
{
    int roll;
    cout << "Enter roll to delete: ";
    cin >> roll;
    if (head->roll == roll)
    {
        Student *t = head;
        head = head->next;
        delete (t);
        printSheet();
        return;
    }
    Student *temp1, *temp2;
    temp1 = head;
    temp2 = head->next;
    while (temp2)
    {
        if (temp2->roll == roll)
        {
            temp1->next = temp2->next;
            delete (temp2);
            printSheet();
            return;
        }
        temp1 = temp1->next;
        temp2 = temp2->next;
    }
    cout << endl
         << "No rows found with the given roll!" << endl;
}

int main()
{
    while (true)
    {
        int choice;
        cout << endl
             << "Enter choice:" << endl
             << "1. Show sheet" << endl
             << "2. Add rows" << endl
             << "3. Search by roll" << endl
             << "4. Sort by roll" << endl
             << "5. Sort by mark" << endl
             << "6. Delete row by roll" << endl
             << "7. Clear screen" << endl
             << "8. Exit" << endl
             << "Your choice: ";
        cin >> choice;
        switch (choice)
        {
        case 1:
        {
            printSheet();
            break;
        }
        case 2:
        {
            addRows();
            break;
        }
        case 3:
        {
            findByRoll();
            break;
        }
        case 4:
        {
            MergeSort(4);
            printSheet();
            break;
        }
        case 5:
        {
            MergeSort(5);
            printSheet();
            break;
        }
        case 6:
        {
            deleteByRoll();
            break;
        }
        case 7:
        {
            system("CLS");
            break;
        }
        default:
        {
            return 0;
        }
        }
    }
    return 0;
}