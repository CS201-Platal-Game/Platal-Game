#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

vector<vector<double>> csv2map(string filename){

    ifstream file;
    file.open(filename);

    vector<vector<double>> aout;
    string line = "0";
    int a, b;

    getline(file, line, ','); //we store the two first value of the csv file : they are the dimensions of the map
    a = stoi(line);
    getline(file, line, ',');
    b = stoi(line);
    getline(file, line, '\n');
    for (int i =0; i < b; i++){
        vector<double> tmp;
        for (int j = 0; j < a-1; j++){
            string line = "0";
            getline(file, line, ',');
            double n = stof(line);
            tmp.push_back(n);
        }
        getline(file, line, '\n'); //by default, the last element of each line doesn't have a comma
        double n = stof(line);
        tmp.push_back(n);
        aout.push_back(tmp);
    }
    return aout;
}
