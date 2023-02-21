#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<cstdlib>

using namespace std;

char score2grade(int score)
{
    if (score >= 80)
        return 'A';
    if (score >= 70)
        return 'B';
    if (score >= 60)
        return 'C';
    if (score >= 50)
        return 'D';
    else
        return 'F';
}

string toUpperStr(string x)
{
    string y = x;
    for (unsigned int i = 0; i < x.size(); i++)
        y[i] = toupper(x[i]);
    return y;
}

void importDataFromFile(string f, vector<string> &n, vector<int> &s, vector<char> &g)
{
    ifstream read(f);
    string txt = "";
    char format[] = "%[^:]: %d %d %d";
    while (getline(read, txt))
    {
        char name[100];
        int sum = 0, s1 = 0, s2 = 0, s3 = 0;
        sscanf(txt.c_str(), format, name, &s1, &s2, &s3);
        sum = s1 + s2 + s3;
        n.push_back(name);
        s.push_back(sum);
    }
    for (unsigned int i = 0; i < n.size(); i++)
        g.push_back(score2grade(s[i]));
}

void getCommand(string &cmd, string &key)
{
    string line = "";
    cout << "Please input your command: ";
    getline(cin,line);
    int start = 0;
    int end = line.find_first_of(" ");
    cmd = line.substr(start,end);   
    key = line.substr(end+1,line.length());
}

void searchName(vector<string> &n, vector<int> &s, vector<char> &g, string key)
{
    bool found = false;
    cout << "---------------------------------\n";
    for (unsigned int i = 0; i < n.size(); i++)
    {
        if (toUpperStr(n[i]) == key)
        {
            cout << n[i] << "'s score = " << s[i];
            cout << "\n";
            cout << n[i] << "'s grade = " << g[i];
            cout << "\n";
            found = true;
        }
        else if (i == n.size() - 1 && !found)
            cout << "Cannot found.\n";
    }
    cout << "---------------------------------\n";
}
void searchGrade(vector<string> &n, vector<int> &s, vector<char> &g, string key)

{
    bool found = false;
    cout << "---------------------------------\n";
    for (unsigned int i = 0; i < n.size(); i++)
    {
        if (g[i] == key[0])
        {
            cout << n[i] << " (" << s[i] << ")\n";
            found = true;
        }
        else if (i == n.size() - 1 && !found)
            cout << "Cannot found.\n";
    }
    cout << "---------------------------------\n";
}


int main(){
    string filename = "name_score.txt";
    vector<string> names;
    vector<int> scores;
    vector<char> grades; 
    importDataFromFile(filename, names, scores, grades);
    
    do{
        string command, key;
        getCommand(command,key);
        command = toUpperStr(command);
        key = toUpperStr(key);
        if(command == "EXIT") break;
        else if(command == "GRADE") searchGrade(names, scores, grades, key);
        else if(command == "NAME") searchName(names, scores, grades, key);
        else{
            cout << "---------------------------------\n";
            cout << "Invalid command.\n";
            cout << "---------------------------------\n";
        }
    }while(true);
    
    return 0;
}