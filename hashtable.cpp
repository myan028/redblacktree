#include <iostream>
#include <vector>
#include <cstring>
#include <iomanip>
#include <cmath>
#include <map>
#include <fstream>


using namespace std;

/*
Code by Michael Yan 5/28/20
Part 2 to StudentList, this is a program that allows the user to randomly generate students in a
database and store them via hash table.
*/

struct Student{ //struct including student info
  char* firstName;
  char* lastName;
  int id;
  float gpa;
};


struct Node{ //linkedlist for chaining
	Student* student;
	Node* next;
	int index;
};



int tableSize = 10;

Node** HashTable = new Node*[tableSize];

vector<int> usedIDs;
vector<map<char*, char*>> usedNames;
int nameSize = 20;


void initTable(Node** table, int size){
	for(int i = 0; i < size; i++){
		table[i] = NULL;
	}
}



bool checkTable(bool forced){
	if(forced){
		return true;
	}
	if(usedNames.size() >= tableSize/2){
		return true;
	}
	else{
		return false;
	}
}



void rehash(bool forced){ //rehash table, increase size
	while(checkTable(forced)){ //reindex nodes
		forced = false;
		
		cout << "\nRehashing..." << endl;
		
		Node** tempTable = new Node*[(int)pow(tableSize, 2)]; 
		initTable(tempTable, (int)pow(tableSize, 2)); //temptable
		
		for(int i = 0; i < tableSize; i++){
			if(HashTable[i] != NULL){
				Node* tempNode = HashTable[i];
				int pos = 0;
				for(int i = 0; i < nameSize; i++){
					if(tempNode->student->firstName[i] != '\0'){
						pos+=(int)tempNode->student->firstName[i];
					}
				}
				
				pos = pos % (int)pow(tableSize, 2);
				tempNode->index = pos;
				tempTable[pos] = tempNode;
				
			}
		}
		
		HashTable = tempTable;
		tableSize = (int)pow(tableSize, 2);
		
		
		for(int i = 0; i < tableSize; i++){ //check for chain index , 
			if(HashTable[i] != NULL){
				if(HashTable[i]->next != NULL){
					Node* current = HashTable[i];
					while(current->next != NULL){
						Node* parent = current;
						current = current->next;
						int pos = 0;
						for(int i = 0; i < nameSize; i++){
							if(current->student->firstName[i] != '\0'){
								pos += (int) current->student->firstName[i];
							}
						}
						pos = pos % tableSize;

						if(pos != parent->index){
							Node* temp = current;
							temp->index = pos;
							current = parent;
							parent = NULL;
							current->next = temp->next;
							if(HashTable[pos] == NULL){
								HashTable[pos] = temp;
							}
							
							else{
								Node* occupier = HashTable[pos];
								while(occupier->next != NULL)
								occupier = occupier->next;

								occupier->next = temp;
							}
						}
						else{
							current->index = pos;
						}
					}
				}
			}
		}
		
		cout << "New table size: " << tableSize << endl << endl;
		
	}
}


int generateID(){ //generate a random ID that hasa does not exist yet
	int randomID;
	while(true){
		randomID = rand() % 10000;
		bool exists = false;
		vector<int>::iterator i;
		for(i = usedIDs.begin(); i != usedIDs.end(); i++){
			if(randomID == *i){
				exists = true;
			}
		}
		
		if(!exists){
			break;
		}
	}
	usedIDs.push_back(randomID);
	return randomID;
}


bool checkCombos(char* first, char* last, bool shouldDelete){ //check first and last combinations if name has been used
	vector<map<char*, char*>>::iterator v;
	map<char*, char*>::const_iterator j;
	for(v = usedNames.begin(); v != usedNames.end(); v++){
		for(j = v->begin(); j != v->end(); ++j){
			if(strcmp(first, j->first) == 0){
				if(strcmp(last, j->second) == 0){
					if(shouldDelete){
						usedNames.erase(v);
					}
					return false;
				}
			}
		}
	}
	return true;
}



Student* ADD(char* first1, char* last1, float gpa1){ //add function
	Student* newStudent = new Student(); //store the new student in heap
	Node* newNode = new Node();

	/*cout << "\nEnter the student's first name: ";
	cin >> newStudent->firstName;
	cin.clear(); //clear for next input (many)
	cin.ignore(999, '\n');
	cout << "Enter the student's last name: ";
	cin >> newStudent->lastName;
	cin.clear();
	cin.ignore(999, '\n');
	cout << "Enter their student id: ";
	cin >> newStudent->id;
	cin.clear();
	cin.ignore(999, '\n');
	cout << "Enter their gpa: ";
	cin >> newStudent->gpa;
	cin.clear();
	cin.ignore(999, '\n');
	return newStudent; //return student pointer*/

	newStudent->id = generateID();  
	newStudent->firstName = first1;
	newStudent->lastName = last1;
	newStudent->gpa = gpa1;

	int pos = 0;

	for(int i = 0; i < nameSize; i++){
		if(newStudent->firstName[i] != '\0'){
			pos += (int)newStudent->firstName[i];
		}
	}

	pos = pos % tableSize;
	newNode->student = newStudent;
	newNode->index = pos;

	if(HashTable[pos] ==  NULL){
		HashTable[pos] = newNode;
	}
	else{
		Node* current = HashTable[pos];
		while(current->next != NULL)
		current = current->next;

		current->next = newNode;
	}

	map<char*, char*> temp;
	temp.insert(pair<char*, char*> (first1, last1));
	usedNames.push_back(temp);
	temp.clear();

	rehash(false);
  
}



void parseInput(vector<char*> &names, char* input){ //parse the txt fileinput
	char* name = new char[nameSize];
	int i = 0;
	int counter = 0;
	while(input[i] != '\0'){
		if(input[i] == ' '){ //names separated by a single space
			if(counter < nameSize){
				name[counter] = '\0';
				names.push_back(name);
			}
			name = new char[nameSize];
			counter = 0;
		}
		else{
			name[counter] = input[i];
			counter++;
		}
		i++;
	}
	names.push_back(name); //add name
}




void randomGen(char first[], char last[], int amount){ //algorithm taking file input
	vector<char*> firstNames;
	vector<char*> lastNames;
	char* input = new char[10000];
	ifstream file;

	//open inputted txt files for first and last name
	file.open(first);
	if(file){
		int i = 0;
		while(!file.eof()){
			input[i] = file.get();
			i++;
		}
		input[i - 1] = '\0';
	}
	else{
		cout << "There is an error opening: " << first << endl;
		return;
	}
	parseInput(firstNames, input);
	file.close();

	file.open(last);
	if(file){
		int i = 0;
		while(!file.eof()){
			input[i] = file.get();
			i++;
		}
		input[i - 1] = '\0';
	}
	else{
		cout << "There is an error opening: " << last << endl;
		return;
	}
	
	parseInput(lastNames, input);
	file.close();
	vector<map<char*,char*>> combos;
	vector<char*>::iterator n;
	vector<char*>::iterator n2;
	int z;
	
	for(n = firstNames.begin(); n != firstNames.end(); n++){ //add to vector
		for(n2 = lastNames.begin(); n2 != lastNames.end(); n2++){
			map<char*, char*> temp;
			if(checkCombos(*n, *n2, false)){
				temp.insert(pair<char*, char*> (*n, *n2));
				combos.push_back(temp);
			}
			temp.clear();
			z++;
		}
	}

	if(amount > combos.size()){
		cout << "Maximum amount of random students is: " << combos.size() << endl; //max size reached
		return;
	}

	for(int i = 0; i < amount; i++){ //selecting unused combination
		char* firstName = new char[nameSize];
		char* lastName = new char[nameSize];
		float gpa = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/5));
		do{ //while unused combination
			vector<map<char*, char*>>::const_iterator v;
			map<char*, char*>::const_iterator m;
			int random = rand() % combos.size();
			int counter = 0;
			for(v = combos.begin(); v != combos.end(); ++v){
				if(counter == random){
					for(m = v->begin(); m != v->end(); ++m){
						firstName = m->first;
						lastName = m->second;
						break;
					}
					break;
				}
				counter++;
			}
		} 
		while(!checkCombos(firstName, lastName, false)); 
		
		ADD(firstName, lastName, gpa); //run add to add node to database
	}
 
}





void PRINT(vector<Student*> students){ //print function
	/*vector<Student*>::iterator cycle; // creates iterator through student pointer vector
	for(cycle = students.begin(); cycle != students.end(); ++cycle){ //iterates through the vector
		cout << "\nStudent name: " << (*cycle)->firstName << " " << (*cycle)->lastName << endl;
		cout << "Student ID: " << (*cycle)->id << endl;
		cout << "Student GPA: " << fixed << setprecision(2) << (*cycle)->gpa << endl; //round to 2 decimal places
		cout << endl;
  }*/
  
	Node* current;
	bool found = false;
	int counter = 0;
	for(int i = 0; i < tableSize; i++){ //increment print
		if(HashTable[i] != NULL){
			found = true;
			if(HashTable[i]->student != NULL){
				counter++;
				
				cout << endl << "Name: "  << HashTable[i]->student->firstName << " " << HashTable[i]->student->lastName << endl;
				
				cout << "ID: " << setw(6) << setfill('0') << HashTable[i]->student->id << endl;
				cout << "GPA: ";
				printf("%.2f\n", HashTable[i]->student->gpa); //
				cout << "Index: " << HashTable[i]->index << " (Chain: 0)" << endl;
			}
			current = HashTable[i];
			int num = 0;
			while(current->next != NULL){
				current = current->next;
				num++;
				if(current->student != NULL){
					counter++;
					
					cout << endl << "Name: " << current->student->firstName << " " << current->student->lastName << endl;
					
					cout << "ID: " << setw(6) << setfill('0') << HashTable[i]->student->id << endl;
					cout << "GPA: ";
					printf("%.2f\n", current->student->gpa);
					cout << "Index: " << current->index << " (Chain: " << num << ")" << endl;
				}
			}
		}
	}
	if(!found){ //if nothing in database
		cout << "There are no students to print." << endl;
	}

	else{
		cout << endl << counter << " students in database.\n" << endl;
	}

	//cout << usedNames.size();
  
}



void DELETE(int index){ //delete function
    /*int idInput;
	cout << "\nWhich student would you like to delete? Enter their student id: ";
	cin >> idInput;
	cin.clear();
	cin.ignore(999, '\n');
	vector<Student*>::iterator cycle; // creates iterator through vector of students
	for(cycle = students->begin(); cycle != students->end(); ++cycle){
	  //cout << (*cycle)->id << "it works! somethings just being weird" << endl;
	  if((*cycle)->id == idInput){ //make sure input matches existing id
	    cout << "\nDeleted student " << (*cycle)->id << "." << endl;
		students->erase(cycle);//erase that index from student vector
	    delete *cycle;//clear iterator memory in the heap
	    return;
	  }
	  else{
		cout << "Couldn't find a student with the ID " << idInput << " in the directory." << endl; 
	  }
	}*/
	
	if(HashTable[index]->next == NULL){ //found student
		char yesno = '\0';
		cout << "\nAre you sure you would like to delete this student? Type 'y' or 'n': ";
		cin >> yesno;
		cin.clear();
		cin.ignore(1000000, '\n');

		if(yesno == 'y'){
			checkCombos(HashTable[index]->student->firstName, HashTable[index]->student->lastName, true);
			delete HashTable[index];
			HashTable[index] = NULL;
			
			cout << "\nStudent has been deleted.\n" << endl;
			return;
		}
		
		else if(yesno == 'n'){
			cout << "\nStudent was not deleted.\n" << endl;
			return;
		}
		
		else{
			cout << "\nInvalid Input." << endl;
			return;
		}
	}

	else{ //if index has multiple students sharing
		int chainNo = 0;
		char yesno = '\0';
		
		cout << "\nEnter the student's chain number: ";
		cin >> chainNo;
		cin.clear();
		cin.ignore(1000000, '\n');

		Node* current = HashTable[index];
		Node* parent;
		int counter;
		
		
		while(counter != chainNo){
			if(current->next != NULL){
				parent = current;
				current = current->next;
			}
			else{
				cout << "\nStudent not found. " << endl; //no student found
				return;
			}
			counter++; //increase count each time
			cout << endl << counter << endl;
		}

		cout << endl << "Name: " << current->student->firstName << " " << current->student->lastName << endl;		
		cout << "ID: " << setw(6) << setfill('0') << current->student->id << endl;
		cout << "GPA: ";
		printf("%.2f\n", current->student->gpa);

		cout << "\nAre you sure you would like to delete this student? Type 'y' or 'n': ";
		cin >> yesno;
		cin.clear();
		cin.ignore(1000000, '\n');
		
		if(yesno == 'y'){ 
			if(current->next == NULL){
				checkCombos(current->student->firstName, current->student->lastName, true);
				parent->next = NULL;
				current = NULL;
				delete current;
				cout << "Student has been deleted.\n" << endl;
			}
			else{ //case
				Node* temp = current->next;
				if(current == HashTable[index]){
					HashTable[index] = temp;
				}
				if(parent != NULL)
				parent->next = temp;

				checkCombos(current->student->firstName, current->student->lastName, true);
				
				current = NULL;
				delete current;
				
				cout << "\nStudent has been deleted.\n" << endl;
				return;
			}
		}
		else if(yesno == 'n'){ //dont want to delete
			cout << "\nStudent was not deleted.\n" << endl;
			return;
		}
		else{ //neither y or n
			cout << "\nPlease type 'y' or 'n'.\n" << endl;
			return;
		}
	}
	
}



int main(){
	srand(time(0));
	initTable(HashTable, tableSize);
	
	bool running = true;
	char input[10]; //input for command
	vector<Student*> students;
	int idInput;// input for delete
	
	while(running = true){
		cout << "Enter a command. \nType 'add', 'print', 'delete', or 'exit': ";
		cin.get(input, 10);
		cin.clear();
		cin.ignore(999, '\n');
		
		if(strcmp(input, "add") == 0){
			cout << "Would you like to input manually or via file? Type 'manual' or 'file': "
			char input2[10];
			cin.get(input2, 10);
			cin.clear();
			cin.ignore(999, '\n');
			
			if(strcmp(input2, 'manual') == 0){
				
			}
			
			else if(strcmp(input2, "file") == 0){
				char file1[50];
				char file2[50];
				int number;
				
				cout << "\nEnter the filename containing first names: "; //prompt for input
				cin.get(file1, 50);
				cin.clear();
				cin.ignore(99999, '\n');
				
				cout << "Enter the filename containing last names: ";
				cin.get(file2, 50);
				cin.clear();
				cin.ignore(99999, '\n');
				
				cout << "How many students would you like to generate? ";
				cin >> number;
				cin.clear();
				cin.ignore(99999, '\n');
				
				randomGen(file1, file2, number); //call random generator algorithm to create student w input
			}
			
			
			cout << endl;
		}
		
		else if(strcmp(input, "print") == 0){
			PRINT(students); //call print function
		}
		
		else if(strcmp(input, "delete") == 0){
			char* name = new char[nameSize];
			int index;
			cout << "Enter the student's index: ";
			cin >> index;
			cin.clear();
			cin.ignore(1000000, '\n');

			bool found = false;
			if(HashTable[index] != NULL){ //print students with matching index for deletion
				cout << endl << "Name: " << HashTable[index]->student->firstName << " " << HashTable[index]->student->lastName << endl;
				cout << "ID: " << setw(6) << setfill('0') << HashTable[index]->student->id << endl;
				cout << "GPA: ";
				printf("%.2f\n", HashTable[index]->student->gpa);
				if(HashTable[index]->next != NULL){
					cout << "Chain: " << "0" << endl; //0 case
				}
				
				Node* current = HashTable[index];
				int num = 0;
				while(current->next != NULL){
					current = current->next;
					num++;
					if(current->student != NULL){
						cout << endl << "Name: " << current->student->firstName << " " << current->student->lastName << endl;
						cout << "ID: " << setw(6) << setfill('0') << current->student->id << endl;
						cout << "GPA: ";
						printf("%.2f\n", current->student->gpa);
						cout << "Chain: " << num << endl;
					}
				}
				found = true;
			}
			if(!found){
				cout << "Student not found." << endl;
			}
			
			else{
				DELETE(index); //call delete
			}
		
		}
		
		else if(strcmp(input, "exit") == 0){
			break; //get out of here
		}
		
		else{
			cout << "\nInvalid command." << endl;
		}
	}
	//return 0; same thing
	running = false;
}