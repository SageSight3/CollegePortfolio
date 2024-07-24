#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
#include "Tree.h"
#include "DRT.h"
#include "PG5.h"
#include "Database.h"
using namespace std;

Database* Studs;

int main(int argc, char** argv) {
    Studs = new Tree();
    while (ProcessCommand());
    delete Studs;
    return 0;
}

bool ProcessCommand() {

    string cmd;
    while (true) {
        getline(in, cmd);
        cout << "Command was " << cmd << endl;
        if (cmd == "EXIT") return false;
        if (cmd == "PRINT") Print();
        else if (cmd == "RPRINT") RPrint();
        else if (cmd.substr(0, 3) == "ADD") AddCommand(cmd);
        else if (cmd.substr(0, 6) == "REMOVE") RemoveCommand(cmd);
        else if (cmd.substr(0, 6) == "LOOKUP") LookupCommand(cmd);
        else if (cmd.substr(0, 4) == "EDIT") EditCommand(cmd); //problem?
        else cout << "Invalid Command!" << endl;
        if (!((Tree*)Studs)->Valid()) {
            cout << "Invalid node here" << endl;
            delete Studs;
            exit(1);
        }
        return true;
    }
}

void Print() {

    cout << "Printing list forwards:" << endl;
    DRT* T = Studs->search("");
    string k = T->getnext();
    while (k != "") {
        delete T;
        T = Studs->search(k);
        cout << "Name:  " << k << "\tGPA:  " << T->getdata() << endl;
        k = T->getnext();
    }
    delete T;
    cout << endl;
}

void RPrint() {

    cout << "Printing list backwards:" << endl;
    DRT* T = Studs->search("");
    string k = T->getprev();
    while (k != "") {
        delete T;
        T = Studs->search(k);
        cout << "Name:  " << k << "\tGPA:  " << T->getdata() << endl;
        k = T->getprev();
    }
    delete T;
    cout << endl;
}

void AddCommand(string cmd) {
    int q1, q2;
    for (q1 = 0; cmd[q1] != '\"'; q1++);
    for (q2 = q1 + 1; cmd[q2] != '\"'; q2++);
    string k = cmd.substr(q1 + 1, q2 - q1 - 1);
    string gpa = cmd.substr(q2 + 2, cmd.length() - q2 - 2);
    Studs->modify(k, gpa);
}

void RemoveCommand(string cmd) {

    int q1, q2;
    for (q1 = 0; cmd[q1] != '\"'; q1++);
    for (q2 = q1 + 1; cmd[q2] != '\"'; q2++);
    string k = cmd.substr(q1 + 1, q2 - q1 - 1);
    DRT* T = Studs->search(k);
    if (T->getdata() == "") {
        cout << "\"" << k << "\" does not exist in the database!" << endl;
    }
    else {
        delete T;
        T = Studs->modify(k, "");
        cout << "\"" << k << "\" has been removed from the database!"
            << endl;
    }
    delete T;
}

void LookupCommand(string cmd) {
    int q1, q2;
    for (q1 = 0; cmd[q1] != '\"'; q1++);
    for (q2 = q1 + 1; cmd[q2] != '\"'; q2++);
    string k = cmd.substr(q1 + 1, q2 - q1 - 1);
    DRT* sol = Studs->search(k);
    string prevPrin = sol->getprev();
    string nextPrin = sol->getnext();
    if (prevPrin == "") {
        prevPrin = "beginning of the list";
    }

    if (nextPrin == "") {
        nextPrin = "end of the list";
    }


    if (sol->getdata() == "") {
        cout << "No student between " << prevPrin  << " and " << nextPrin << endl;
        return;
    }
    cout << k << " " << sol->getdata() << endl;
}

void EditCommand(string cmd) {
    int q1, q2;
    for (q1 = 0; cmd[q1] != '\"'; q1++);
    for (q2 = q1 + 1; cmd[q2] != '\"'; q2++);
    string k = cmd.substr(q1 + 1, q2 - q1 - 1);
    string gpa = cmd.substr(q2 + 2, cmd.length() - q2 - 2);
    string oldGPA = Studs->search(k)->getdata();
    if (oldGPA == "") {
        cout << "That student doesn't exist" << endl;
        return;
    }
    Studs->modify(k, "");
    Studs->modify(k, gpa);

    cout << k << "\tOld GPA: " << oldGPA << "\tNew GPA: " << gpa << endl;
}