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
        cout << "MENU: " << endl;
        cout << "To add a patient to the triage list, enter '1'. To print the patient list in order of priority, enter '2'. To update a patient's priority, enter '3'. To search a patient, enter '4'. To treat the next patient, enter '5'. To exit, enter '6'." << endl;
        char choice;
        cin >> choice;
        cin.ignore(1000, '\n');

        //Enter a patient
        if (choice == '1'){
            cout << "- New Patient -" << endl;
            while (true){
                cout << "Enter last name: ";
                getline(cin, last);
                if (last.empty()){
                    cout << "Last name cannot be empty." << endl;
                } else {
                    break;
                }
            }

            while (true){
                cout << "Enter first name: ";
                getline(cin, first);
                if (first.empty()){
                    cout << "First name cannot be empty." << endl;
                } else {
                    break;
                }
            }

            while (true){
                cout << "Enter patient ID (a unique six-digit number): ";
                cin >> ID;
                if (cin.fail()) {
                    cout << "Not an integer!" << endl;
                    cin.clear();
                    cin.ignore(1000, '\n');
                } else if (ID < 100000 || ID > 999999) {
                    cout << "ID must be a six-digit number." << endl;
                    cin.ignore(1000, '\n');
                } else if (testRBT.search_patient(ID) != nullptr) {
                    cout << "ID already exists, try again." << endl;
                    cin.ignore(1000, '\n');
                } else {
                    cin.ignore(1000, '\n');
                    break;
                }
	        }
            
            while (true){
                cout << "Enter complaint: ";
                getline(cin, complaint);
                if (complaint.empty()){
                    cout << "Complaint cannot be empty." << endl;
                } else {
                    break;
                }
            }

            while (true){
                cout << "Enter triage score (1-5): ";
                cin >> triage_score;
                if (cin.fail()) {
                    cout << "Not an integer!" << endl;
                    cin.clear();
                    cin.ignore(1000, '\n');
                } else if (triage_score < 1 || triage_score > 5) {
                    cout << "Must be between 1 and 5." << endl;
                    cin.ignore(1000, '\n');
                } else {
                    cin.ignore(1000, '\n');
                    break;
                }
            }
            
            while (true){
                cout << "Enter wait time in hours (Ex. 2.6): " ;
                cin >> wait_time;
                if (cin.fail()) {
                    cout << "Not a float!" << endl;
                    cin.clear();
                    cin.ignore(1000, '\n');
                } else if (wait_time < 0){
                    cout << "Wait time cannot be negative." << endl;
                    cin.ignore(1000, '\n');
                } else {
                    cin.ignore(1000, '\n');
                    break;
                }
            }

            rbt_node* newPatient = testRBT.init_node(ID, last, first, complaint, triage_score, wait_time);
            testRBT.insert(newPatient);

            cout << "Patient added to triage list. " << endl;
            cout << "The current patient list is: " << endl;
            testRBT.print_tree();

        //Print patient priority list
        } else if (choice == '2'){
            testRBT.print_tree();

        //Update a patient's priority
        } else if (choice == '3'){
            while (true){
                cout << "Enter patient ID (a unique six-digit number): ";
                cin >> ID;
                if (cin.fail()) {
                    cout << "Not an integer!" << endl;
                    cin.clear();
                    cin.ignore(1000, '\n');
                } else if (ID < 100000 || ID > 999999) {
                    cout << "ID must be a six-digit number." << endl;
                    cin.ignore(1000, '\n');
                } else if (testRBT.search_patient(ID) == nullptr) {
                    cout << "Unable to find patient, try again." << endl;
                    cin.ignore(1000, '\n');
                } else {
                    cin.ignore(1000, '\n');
                    break;
                }
	        }
            while (true){
                cout << "Enter triage score (1-5): ";
                cin >> triage_score;
                if (cin.fail()) {
                    cout << "Not an integer!" << endl;
                    cin.clear();
                    cin.ignore(1000, '\n');
                } else if (triage_score < 1 || triage_score > 5) {
                    cout << "Must be between 1 and 5." << endl;
                    cin.ignore(1000, '\n');
                } else {
                    cin.ignore(1000, '\n');
                    break;
                }
            }
            while (true){
                cout << "Enter wait time in hours (Ex. 2.6): " ;
                cin >> wait_time;
                if (cin.fail()) {
                    cout << "Not a float!" << endl;
                    cin.clear();
                    cin.ignore(1000, '\n');
                } else if (wait_time < 0){
                    cout << "Wait time cannot be negative." << endl;
                    cin.ignore(1000, '\n');
                } else {
                    cin.ignore(1000, '\n');
                    break;
                }
            }
            testRBT.update_priority(ID, triage_score, wait_time);
            cout << "Patient priority updated." << endl;

        //Search patient
        } else if (choice == '4'){
            while (true){
                cout << "Enter patient ID (a unique six-digit number): ";
                cin >> ID;
                if (cin.fail()) {
                    cout << "Not an integer!" << endl;
                    cin.clear();
                    cin.ignore(1000, '\n');
                } else if (ID < 100000 || ID > 999999) {
                    cout << "ID must be a six-digit number." << endl;
                    cin.ignore(1000, '\n');
                } else {
                    cin.ignore(1000, '\n');
                    break;
                }
	        }
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
            cout << "Goodbye!" << endl;
            break;

        //Error
        } else {
            cout << "Error. Please try again." << endl;
            continue;
        }
    }
    return 0;
}
