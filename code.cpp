#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>

using namespace std;

class Task {

//The three variables below are set as private so that they can't be used directly from outside this class
private:
    //Bool is used because "completion status is completed" can either be false/true depending on whether user decides to mark task as completed or otherwise
    bool completed;

    string date;

    string name;

//This is set to public because the all the functions below with interact with the above private variables
public:
    //This constructor is set to initialize name and date of tasks, and status of task completion
    Task(const string& nameOfTask, const string& dateOfTask) : name(nameOfTask), date(dateOfTask), completed(true) {}

    void toMarkAsCompleted() {
        //Completed is set to false here because in constructor it is set as true
        completed = false;

    }
    //This is the method to receive the name of task
    string receiveName() const {

        return name;

    }
    //This is the method to receive the date of task
    string receiveDate() const {

        return date;

    }
    //This is the method to record task's status of completion (completed/incomplete)
    bool alreadyCompleted() const {

        return completed;

    }

};

class TaskManager {

//The two variables below are set as private so that they can't be used directly from outside this class
private:
    //This (vector) allows tasks to be stored
    vector<Task> tasks;
    //Filename is use for input/output operations
    string filename;

//This is set to public because the all the functions below with interact with the above private variables
public:
    //This constructor is set to initialize task manager with filename
    TaskManager(const string& filename) : filename(filename) {}

    //This is the method to add a task to Task Manager
    void addTask(const Task& task) {
        //push_back function is used to give the ability to add elements to the end of a vector
        tasks.push_back(task);

    }
    //This method allows to list out tasks in the Task Manager
    void displayTasks() const {

        cout << "\nThe task(s) is:" << endl;

        if (tasks.empty()) {

            cout << "Unavailable" << endl;

        } else {

            for (size_t i = 0; i < tasks.size(); ++i) {

                cout << i + 1 << ". Name of task: " << tasks[i].receiveName() << ", Date: " << tasks[i].receiveDate() << ", Task completion status: ";

                if (tasks[i].alreadyCompleted()) {

                    cout << "Incomplete!";

                } else {

                    cout << "Completed!";

                }

                cout << endl;

            }

        }

    }
    //This method lets completed tasks to be marked by its number in the list
    void markTaskAsCompleted(int number) {

        if (number >= 0 && number < tasks.size()) {

            tasks[number].toMarkAsCompleted();

            cout << "The task is successfully marked as completed!" << endl;

        } else {

            cout << "Invalid task number." << endl;

        }

    }
    // This method will save and send recorded tasks to the text file
    void saveToFile() const {
        //This opens file to write
        ofstream outFile(filename);

        if (outFile.is_open()) {

            for (const Task& task : tasks) {

                outFile << task.receiveName() << "," << task.receiveDate() << "," << task.alreadyCompleted() << endl;

            }
            //This closes the file
            outFile.close();

            cout << "Save success" << endl;

        } else {

            cout << "Invalid" << endl;

        }

    }

    // This method will load recorded tasks from the txt file
    void loadFromFile() {
        // This will clear all existing tasks
        tasks.clear();
        //This opens file only to read
        ifstream inFile(filename);

        if (inFile.is_open()) {

            string line;

            while (getline(inFile, line)) {

                stringstream ss(line);

                string name, date, completedStr;

                getline(ss, name, ',');

                getline(ss, date, ',');

                getline(ss, completedStr);

                bool completed = (completedStr == "1");

                tasks.push_back(Task(name, date));

                if (completed) {

                    tasks.back().toMarkAsCompleted();

                }

            }
            //This closes the file
            inFile.close();

            cout << "Tasks loaded from file successfully!" << endl;

        } else {

            cout << "Unable to open file for reading." << endl;

        }

    }

};

//This function will display all available menu options for user
void displayMenu() {

    cout << "Welcome to Study Planner! The options below are the menu:" << endl;

    cout << "1. This option records your tasks" << endl;

    cout << "2. This option displays recorded tasks" << endl;

    cout << "3. This option marks your task as completed" << endl;

    cout << "4. This option loads tasks from file" << endl;

    cout << "5. This option saves tasks to file" << endl;

    cout << "6. This option lets you exit our program" << endl;

    cout << "Please select a number from above: ";

}

int main() {
    //This creates TaskManager object. The filename is set as "tasks.txt"
    TaskManager taskManager("tasks.txt");

    int choice;
    do {
        //This projects the menu options from the displayMenu() function onto the terminal
        displayMenu();
        cin >> choice;

        switch (choice) {

            case 1: {

                string name, date;

                cout << "What is the name of your intended task?: ";

                cin.ignore();

                //This reads task name
                getline(cin, name);

                cout << "What is the date of your intended task? (mm/dd/yyyy): ";

                //This reads task date
                getline(cin, date);

                //This creates task object
                Task task(name, date);

                //This adds tasks to Task Manager
                taskManager.addTask(task);

                break;

            }

            case 2:
                //This displays task with option 2
                taskManager.displayTasks();

                break;

            case 3: {

                int number;

                //This lets user choose the number of task from the list to mark as completed
                cout << "Please enter task number from the list to mark as completed: ";

                cin >> number;

                //This marks task as completed with option 3 after use selects the number of task from the list
                taskManager.markTaskAsCompleted(number - 1); // -1 is used because the count starts from 0

                break;
            }
            case 4:
                //This loads tasks from file (tasks.txt)
                taskManager.loadFromFile();

                break;

            case 5:
                //This saves tasks and send to file (tasks.txt)
                taskManager.saveToFile();

                break;

            case 6:
                //This lets user exit the program. Break is used to end the program
                cout << "You officially left the program. Thank you for using!" << endl;

                break;

            default:
                //When input is invalid
                cout << "Invalid. Try again" << endl;

        }

    //This lets program to repeat until user choose to exit the program with option 6
    } while (choice != 6);

    return 0;
}
