#include "RBTree.h"
#include <memory>
#include <string>
#include <iostream>

using namespace std;

int main(){
    RBT testRBT;

    //PRELOAD SOME PATIENTS---------------
    testRBT.insert(testRBT.init_node(123456, "Smith", "Rob", "Fever", 4, 2.5));
    testRBT.insert(testRBT.init_node(124567, "Mallard", "Mark", "Cardiac Arrest", 1, 0.2));
    testRBT.insert(testRBT.init_node(145678, "Smith", "Mary", "Deep Vein Thrombosis", 2, 1.2));
    testRBT.insert(testRBT.init_node(128904, "Anthony", "Roberto", "Appendicitis", 2, 1.8));
    testRBT.insert(testRBT.init_node(134567, "Patel", "Krupa", "Hypertension", 3, 4.5));
    testRBT.insert(testRBT.init_node(156789, "Banderas", "Miguel", "Presyncope", 3, 2.4));
    testRBT.insert(testRBT.init_node(167823, "Banderas", "Maria", "Med Refill", 4, 4.8));

    cout << "You have entered the Patient Triage System. " << endl;
    cout << "Current patient triage priority list: " << endl;
    testRBT.print_tree();

    string first;
    string last;
    string complaint;
    int triage_score;
    float wait_time;
    int ID;

    while (true){
        cout << "- New Patient -" << endl;
        cout << "Enter last name: ";
        cin >> last;
        cout << "Enter first name: ";
        cin >> first;
        cout << "Enter patient ID (a unique six-digit number): ";
        cin >> ID;
        cin.ignore();
        cout << "Enter complaint: ";
        getline(cin, complaint);
        cout << "Enter triage score (1-5): ";
        cin >> triage_score;
        cout << "Enter wait time in hours (Ex. 2.6): " ;
        cin >> wait_time;

        rbt_node* newPatient = testRBT.init_node(ID, last, first, complaint, triage_score, wait_time);
        testRBT.insert(newPatient);

        cout << "Patient added to triage list. " << endl;
        cout << "The current patient list is: " << endl;
        testRBT.print_tree();

        cout << "MENU: " << endl;
        cout << "To add another patient to triage list, enter '1'. To print the patient list in order of priority, enter '2'. To update a patient's priority, enter '3'. To search a patient, enter '4'. To treat the next patient, enter '5'. To exit, enter '6'." << endl;
        char choice;
        cin >> choice;
        cin.ignore();

        //Enter another patient
        if (choice == '1'){
            continue;

        //Print patient priority list
        } else if (choice == '2'){
            testRBT.print_tree();

        //Update a patient's priority
        } else if (choice == '3'){
            cout << "Please enter the patient's ID: " << endl;
            cin >> ID;
            cout << "Please enter the paient's new triage score: " << endl;
            cin >> triage_score;
            cout << "Please enter the patient's new wait time: " << endl;
            cin >> wait_time;
            testRBT.update_priority(ID, triage_score, wait_time);
            cout << "Patient priority updated." << endl;

        //Search patient
        } else if (choice == '4'){
            cout << "Patient Search - Please enter the patient's ID: " << endl;
            cin >> ID;
            rbt_node* search = testRBT.search_patient(ID);
            if (search) {
                cout << search->lastName << ", " << search->firstName << endl;
            } else {
                cout << "Patient not found." << endl;
            }

        //Treat the next patient
        } else if (choice == '5'){
            rbt_node* nextPatient = testRBT.get_next_patient();
            if (nextPatient){
                cout << "Treating: " << nextPatient->lastName << ", " << nextPatient->firstName << endl;
                cout << "Patient treated and removed from triage list." << endl;
            } else {
                cout << "No patients in triage." << endl;
            }

        //Exit program
        } else if (choice == '6'){
            break;

        //Error
        } else {
            cout << "Error. Please try again later." << endl;
            continue;
        }
    }
    return 0;
}
