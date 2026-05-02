#include <iostream>
#include <fstream>
#include <cctype>
#include <string>

using namespace std;

string keywords[] = {"int","float","string","char","bool","if","else","while","for","return","print"};
string ops[] = {"==","!=","<=",">=","&&","||"};

bool checkkeyword(string word) {
    for (int i=0;i<11;i++)
        if(word==keywords[i]) {
            return true;
        }
    return false;
}

bool checkoperator(char ch) {
    string ops1 = "+-*/=%<>!&|";
    for(int i=0;i<ops1.size();i++)
        if(ch==ops1[i]) {
            return true;
        }
    return false;
}

bool isTwoCharOperator(char first,char second) {
    string twoChar = string(1,first)+second;
    for(int i=0;i<6;i++)
        if(twoChar==ops[i]) {
            return true;
        }
    return false;
}

void scanner(string filename) {
    ifstream file(filename);
    if(!file) 
    {   cout<<"some error opening the file open file\n"; 
        return;}
    ofstream symboltable("symbol_table.txt");

    char ch;
    while(file.get(ch)) {
        if(isspace(ch)) 
            continue;
        string token;

        if(ch=='!') {
            token = ch;
            while(isalpha(file.peek()) || isdigit(file.peek())) {
                file.get(ch);
                token += ch;
            }
            symboltable<<token<<"\tIdentifier"<<endl;
        }
        else if(isalpha(ch)) {
            token = ch;
            while(isalpha(file.peek())) {
                file.get(ch);
                token += ch;
            }
            if(checkkeyword(token))
                symboltable<<token<<"\tkeyword"<<endl;
            else
                symboltable<<token<<"\tidentifier"<<endl;
        }
        else if(isdigit(ch)) {
            token = ch;
            while(isdigit(file.peek())) {
                file.get(ch);
                token += ch;
            }
            symboltable<<token<<"\tnnumber"<<endl;
        }
        else if(checkoperator(ch)) {
            char next = file.peek();
            if(isTwoCharOperator(ch,next)) {
                token = string(1,ch)+next;
                file.get();
            } 
            else token = ch;
            symboltable<<token<<"\tOperator"<<endl;
        }
        else if(ch=='('||ch==')'||ch=='{'||ch=='}'||ch=='['||ch==']') {
            token = ch;
            symboltable<<token<<"\tparenthesis"<<endl;
        }
        else if(ch=='$') {
            token = ch;
            symboltable<<token<<"\tendStatement"<<endl;
        }
        else {
            token= ch;
            symboltable<<token<<"\notknown"<<endl;
        }
    }
    file.close();
    symboltable.close();
}

int main() {
    scanner("source.txt");
}