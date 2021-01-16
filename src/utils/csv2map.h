#pragma once
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

struct MapBundle {
    int width, height;
    string music;
    vector<vector<int>> map_array;
};

MapBundle csv2map(const std::string& filename){

    ifstream file;
    file.open(filename);

    vector<vector<int>> aout;
    string line = "0";
    int a, b;
    string c;
    getline(file, line, ','); //we store the two first value of the csv file : they are the dimensions of the map
    a = stoi(line);
    getline(file, line, ',');
    b = stoi(line);
    getline(file, line, '\n');
    c = line;
    for (int i =0; i < b; i++){
        vector<int> tmp;
        for (int j = 0; j < a-1; j++){
            string line = "0";
            getline(file, line, ',');
            int n = stoi(line);
            tmp.push_back(n);
        }
        getline(file, line, '\n'); //by default, the last element of each line doesn't have a comma
        int n = stoi(line);
        tmp.push_back(n);
        aout.push_back(tmp);
    }
    return {a, b, c, aout};
}
