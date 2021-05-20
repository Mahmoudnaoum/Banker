#include <iostream>
#include <vector>
#include <algorithm>
#include <conio.h>

using namespace std;

void safety_state_fun(vector< vector<int> >allocation, vector< vector<int> >max, vector<int> available);

void request_state_fun(vector< vector<int> >allocation, vector< vector<int> >max, vector<int> available);
int main()
{
    cout << "Enter The Allocation matrix" << endl;
    vector< vector<int> > allocation
    {
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    };
    int input;
    for (size_t i = 0; i < 5; i++)
    {
        for (size_t j = 0; j < 4; j++)
        {
            cin >> input;
            allocation[i][j] = input;
        }
    }
    cout << "Enter The Max matrix" << endl;

    vector< vector<int> > max
    {
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    };
    for (size_t i = 0; i < 5; i++)
    {
        for (size_t j = 0; j < 4; j++)
        {
            cin >> input;
            max[i][j] = input;
        }
    }

    cout << "Enter The Available matrix" << endl;
    vector<int> available{ 0, 0, 0, 0 };
    for (size_t i = 0; i < 4; i++)
    {
        cin >> input;
        available[i] = input;
    }

    char state;
    cout << "Please enter S for safe state or R for the request state" << endl;
    cin >> state;
    if (state == 'S')
    {
        safety_state_fun(allocation, max, available);
    }
    else if (state == 'R')
    {
        request_state_fun(allocation, max, available);
    }
    return 0;
}
void safety_state_fun(vector< vector<int> >allocation, vector< vector<int> >max, vector<int> available)
{
    vector< vector<int> > need
    {
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    };

    for (int i = 0; i < allocation.size(); i++)
    {
        for (int j = 0; j < allocation[i].size(); j++)
        {
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }
    // Print NEED MATRIX
    cout << "Need Matrix" << endl;
    for (int i = 0; i < allocation.size(); i++)
    {
        for (int j = 0; j < allocation[i].size(); j++)
        {
            cout << need[i][j] << " ";
        }
        cout << endl;
    }
    // -----------------

    vector<int> sequence;
    int i_ = 0;
    vector<int>::iterator it;
    bool lte;
    int process_no = allocation.size();
    int data_no = allocation[0].size();
    for (int i = 0; i < 5; i++)
    {
        while (sequence.size() < process_no)
        {
            lte = true;

            it = find(sequence.begin(), sequence.end(), i_);
            for (int i = 0; i < available.size(); i++)
            {
                if (need[i_][i] > available[i])
                {
                    lte = false;
                    break;
                }
            }
            if (lte && it == sequence.end())
            {
                sequence.push_back(i_);
                for (int i = 0; i < data_no; i++)
                {
                    available[i] = available[i] + allocation[i_][i];
                }
            }
            i_ = (i_ + 1) % process_no;
        }
    }
    // Print Safe State
    if (sequence.size() < process_no)
    {
        cout << "No";
    }
    else
    {
        cout << "Yes , Safe state <";
        for (int i = 0; i < sequence.size(); i++)
        {
            if (i != sequence.size() - 1)
            {
                cout << "P" << sequence[i] << ", ";
            }
            else
            {
                cout << "P" << sequence[i] << ">";
            }
        }
    }
    _getch();
}

void request_state_fun(vector< vector<int> >allocation, vector< vector<int> >max, vector<int> available)
{
    vector< vector<int> > need
    {
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    };

    for (int i = 0; i < allocation.size(); i++)
    {
        for (int j = 0; j < allocation[i].size(); j++)
        {
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }
    // Print NEED MATRIX
    cout << "Need Matrix" << endl;
    for (int i = 0; i < allocation.size(); i++)
    {
        for (int j = 0; j < allocation[i].size(); j++)
        {
            cout << need[i][j] << " ";
        }
        cout << endl;
    }
    // -----------------
    int immediate_no;
    bool im_granted = true;
    cout << "Enter the process no" << endl;
    cin >> immediate_no;
    cout << "Enter the instances" << endl;
    int inputtt;
    vector<int> request{ 0 , 0 , 0 , 0 };
    for (size_t i = 0; i < 4; i++)
    {
        cin >> inputtt;
        request[i] = inputtt;
    }

    for (int i = 0; i < request.size(); i++)
    {
        if (need[immediate_no][i] < request[i])
        {
            cout << "NO it cant be granted";
            im_granted = false;
            break;
        }
        if (request[i] > available[i])
        {
            cout << "Wait";
            im_granted = false;
            break;
        }
    }

    if (im_granted)
    {
        for (int i = 0; i < request.size(); i++)
        {
            available[i] = available[i] - request[i];
            need[immediate_no][i] = need[immediate_no][i] - request[i];
            allocation[immediate_no][i] = allocation[immediate_no][i] + request[i];
        }
    }
    vector<int> sequence;
    int i_ = 0;
    vector<int>::iterator it;
    bool lte;
    int process_no = allocation.size();
    int data_no = allocation[0].size();
    for (int i = 0; i < 5; i++)
    {
        while (sequence.size() < process_no)
        {
            lte = true;

            it = find(sequence.begin(), sequence.end(), i_);
            for (int i = 0; i < available.size(); i++)
            {
                if (need[i_][i] > available[i])
                {
                    lte = false;
                    break;
                }
            }
            if (lte && it == sequence.end())
            {
                sequence.push_back(i_);
                for (int i = 0; i < data_no; i++)
                {
                    available[i] = available[i] + allocation[i_][i];
                }
            }
            i_ = (i_ + 1) % process_no;
        }
    }

    // Print Safe State
    if (sequence.size() < process_no)
    {
        cout << "No request can't be granted with safe state";
    }
    else
    {
        cout << "Yes request can be granted with safe state, Safe state <";
        for (int i = 0; i < sequence.size(); i++)
        {
            if (sequence[i] != immediate_no)
            {
                if (i != sequence.size() - 1)
                {
                    cout << "P" << sequence[i] << ", ";
                }
                else
                {
                    cout << "P" << sequence[i] << ">";
                }
            }
            else
            {
                if (i != sequence.size() - 1)
                {
                    cout << "P" << sequence[i] << "req" << ", ";
                }
                else
                {
                    cout << "P" << sequence[i] << "req" << ">";
                }
            }
        }
    }
    _getch() ;
}