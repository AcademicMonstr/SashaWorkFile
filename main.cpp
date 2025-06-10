#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib> 
#include <algorithm>

struct Student
{
    std::string name;
    int group;
    double grade;
};


bool compareByName(const Student& a, const Student& b) {
    return a.name < b.name;
}


Student* copyStudentArray(const Student* original, int size) {
    if (original == nullptr || size <= 0) {
        return nullptr;
    }


    Student* copy = new Student[size];

    for (int i = 0; i < size; ++i) {
        copy[i].name = original[i].name;  
        copy[i].group = original[i].group;
        copy[i].grade = original[i].grade;
    }

    return copy;
}

void outputArrayInStream(std::ofstream& fout, Student*& students, int size){

     for (int i = 0; i < size; i++) {
        fout << students[i].name << ';'
            << students[i].group << ';'
            << students[i].grade << std::endl;
    }
}

void checkInputFile(std::ifstream& fin){

    if(!fin.good()){
        throw "Files isnt exist!";
    }
    if(!fin){
        throw "input file erreo!";
    }
    if(fin.peek() == EOF){
        throw "file is empty!";
    }

}

void checkOutputFile(std::ofstream& fout){

    if(!fout.good()){
        throw "Files isnt exist!";
    }
    if(!fout){
        throw "input file erreo!";
    }

    
}


int countLinesInFile(std::ifstream& file) {
    int count{};
    std::string line;
    while (getline(file, line)) {
        if (!line.empty()){
            count++;
        } 
    }
    file.clear();  
    file.seekg(0); 
    return count;
}

void checkSizeArray(int32_t size){

    if(size <= 0){
        throw std::invalid_argument("Uncorrect size!");
    }
}

void splitString(const std::string& str, char delimiter, std::string* tokens, size_t max_tokens) {
    

    size_t start = 0;
    size_t end = str.find(delimiter);
    size_t count = 0;

    while (end != std::string::npos && count < max_tokens - 1) {
        tokens[count++] = str.substr(start, end - start);
        start = end + 1;
        end = str.find(delimiter, start);
    }
    if (count < max_tokens) {
        tokens[count] = str.substr(start);
    }
}

void readAndWriteStudentsFromFile(std::ifstream& file, Student*& students, int& size){

    file.clear();
    file.seekg(0);

    int index = 0;
    std::string str;
    std::string tokens[3];

    checkSizeArray(size);
    students = new Student[size];
    
    while (getline(file, str) && index < size) {
       

        splitString(str, ';', tokens, 3);

        students[index].name = tokens[0];
        students[index].group = stoi(tokens[1]);
        students[index].grade = stod(tokens[2]);
        index++;
     
    }

    file.close();
}





int main(){
    try
    {
         
        std::ifstream file("students.txt");
        checkInputFile(file);

        int sizeArrayStudents = countLinesInFile(file);
        Student* students{};

        readAndWriteStudentsFromFile(file, students, sizeArrayStudents);

          for (int i = 0; i < sizeArrayStudents; i++) {
            std::cout << i+1 << ". " << students[i].name 
                 << ", группа " << students[i].group 
                 << ", оценка " << students[i].grade << std::endl;
        }
        std::ofstream fout("fout.txt");
        checkOutputFile(fout);
        Student* copy =copyStudentArray(students,sizeArrayStudents);
        std::sort(copy, copy + sizeArrayStudents, compareByName);
        outputArrayInStream(fout,copy,sizeArrayStudents);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
   


    return 0;
}
