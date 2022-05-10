/*
зад 63: Съставете програма за работа с ориентиран граф, представен чрез списъци на съседство, която да предлага меню с основните операции със структурата граф.
    Да се напише функция, която брои и визуализира изолирани върхове в дадения граф и се добави към менюто.
*/

#include <iostream>
using namespace std;

struct link
{
    int key;
    link* next;
};
const int n = 15;
link* gr[n];//масив от списъци съхраняващи адреси (масив от указатели)

void init(link* gr[n]);
int searchNode(link* gr[n], char c);
int searchArc(link* gr[5], char c1, char c2);
void addNode(link* gr[n], char c);
void addArc(link* gr[n], char c1, char c2);
void deleteNode(link* gr[n], char c);
void deleteArc(link* gr[n], char c1, char c2);
void listNode(link* gr[n]);

void init(link* gr[n])//инициализация на граф
{
    for (int i = 0; i < n; i++)
    {
        gr[n] = NULL;
    }
}

int searchNode(link* gr[n], char c)//търсене на връх
{
    bool flag = false;
    for (int i = 0; i < n; i++)
    {
        if (gr[i])
        {
            if (gr[i]->key == c)
                flag = true;
        }
    }

    return flag;
}

int searchArc(link* gr[5], char c1, char c2)//търсене на дъга в граф
{
    bool flag = false;
    if (searchNode(gr, c1) && searchNode(gr, c2))
    {
        int i = 0;
        while (gr[i]->key != c1)
            i++;

        link* p = gr[i];

        while (p->key != c2 && p->next != NULL)
            p = p->next;

        if (p->key == c2)
        {
            flag = true;
        }

    }

    return flag;
}


void addNode(link* gr[n], char c)//включване на връх в граф
{
    if (searchNode(gr, c))
    {
        cout << " The node exists! " << endl;
    }
    else
    {
        int j = 0;

        while (gr[j] && (j < n))
        {
            j++;
        }

        if (gr[j] == NULL)
        {
            gr[j] = new link;
            gr[j]->key = c;
            gr[j]->next = NULL;
        }
        else
            cout << " Overflow!!! " << endl;
    }
}

void addArc(link* gr[n], char c1, char c2)//включване на дъга на граф
{
    int i = 0;
    link* p;

    if (searchArc(gr, c1, c2))
    {
        cout << " Existing arc!" << endl;
    }
    else
    {
        if (!(searchNode(gr, c1)))
        {
            addNode(gr, c1);
        }

        if (!(searchNode(gr, c2)))
        {
            addNode(gr, c2);
        }

        while (gr[i]->key != c1)
            i++;

        p = new link;
        p->key = c2;
        p->next = gr[i]->next;
        gr[i]->next = p;
    }
}

void deleteNode(link* gr[n], char c)//премахване на връх от граф
{
    if (searchNode(gr, c))
    {
        int i = 0;

        while (gr[i]->key != c)
            i++;

        link* p, * q = NULL;

        while (gr[i] != NULL)
        {
            p = gr[i];
            gr[i] = p->next;
            delete p;
        }

        for (int i = 0; i < n; i++)
        {
            if (gr[n])
            {
                p = gr[i];

                while ((p->key != c) && (p->next != NULL))
                {
                    q = p;
                    p = p->next;
                }

                if (p->key == c)
                {
                    q->next = p->next;
                    delete p;
                }
            }
        }
    }
    else
    {
        cout << " The node is not in the graph! " << endl;
    }
}

void deleteArc(link* gr[n], char c1, char c2)//изстриване на дъга от граф
{
    if (searchArc(gr, c1, c2))
    {
        int i = 0;

        while (gr[i]->key != c1)
            i++;

        link* p = gr[i], * q = NULL;

        while (p->key != c2)
        {
            q = p;
            p = p->next;
        }
        q->next = p->next;
        delete p;
    }
    else
    {
        cout << " The arc is not in the graph! " << endl;
    }
}

void listNode(link* gr[n])//print graph
{
    cout << endl;
    for (int i = 0; i < n; i++)
    {
        if (gr[i])
        {
            cout << gr[i]->key;
        }
    }
}


void main()
{
    char c, k;
    int choice;

    do
    {
        cout << "    Menu    " << endl;
        cout << " 1. Init " << endl;
        cout << " 2. Add node " << endl;
        cout << " 3. Add arc  " << endl;
        cout << " 4. Delete node " << endl;
        cout << " 5. Delete arc " << endl;
        cout << " 6. Search node " << endl;
        cout << " 7. Search arc " << endl;
        cout << " 8. Print Graph " << endl;
        cout << " 9. Find Isolated nodes " << endl;
        cout << " 10. End " << endl;
        cout << endl;
        cout << "Enter (1 - 10): ";
        cout << endl;

        cin >> choice;
        switch (choice)
        {
        case (1): init(gr); break;

        case (2):
            cout << " Enter node (char): ";
            cin >> c;

            addNode(gr, c); break;

        case (3):
            cout << " Enter the first node (char): ";
            cin >> c;
            cout << " Enter the second node (char): ";
            cin >> k;

            addArc(gr, c, k); break;

        case (4):
            cout << " The node you want to delete is (char): ";
            cin >> c;

            deleteNode(gr, c); break;

        case (5):
            cout << " Enter the first node (char): ";
            cin >> c;
            cout << " Enter the second node (char): ";
            cin >> k;

            deleteArc(gr, c, k); break;

        case (6):
            cout << " Enter node (char): ";
            cin >> k;

            if (searchNode(gr, k))
            {
                cout << " Search result: Existing!" << endl;
            }
            else
            {
                cout << " Search result: Not existing." << endl;
            }

            break;

        case(7):
            cout << " Enter the first node (char): ";
            cin >> c;
            cout << " Enter the second node (char): ";
            cin >> k;

            if (searchArc(gr, c, k))
            {
                cout << " Search result: Existing! " << endl;
            }
            else
            {
                cout << " Search result: Not existing." << endl;
            }

            break;

        case (8): listNode(gr); break;

        case(9):
            bool flag = false;
            int counter = 0;
            char search = gr[1]->key;

            for (int i = 0; i < n; i++)
            {
                if (gr[i])
                {
                    if (gr[i]->key != search)
                    {
                        flag = searchArc(gr, gr[i]->key, search);

                        if (flag == true)
                        {
                            break;
                        }
                        else
                        {
                            counter++;
                        }

                    }


                }
            }

            cout << " The isolated nodes are: " << counter << endl;
        }

    } while (choice != 10);

    cout << endl;
}
