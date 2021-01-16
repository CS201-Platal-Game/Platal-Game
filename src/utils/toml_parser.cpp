#include <assert.h>
#include <fstream>
#include <iostream>
#include <map>
#include <string>

typedef std::map<std::string, std::map<std::string, std::string>> MapTOML;

const std::string whitespaces = " \t\f\v\n\r";

void StringStrip(std::string& str) {
    str.erase(0, str.find_first_not_of(whitespaces));
    str.erase(str.find_last_not_of(whitespaces) + 1);
}

// Returns true on success and false on failure.
bool ParseMapTOML(const std::string& filename, MapTOML& map_toml) {
    std::ifstream file;
    file.open(filename.c_str());
    if (file.fail()) {
        std::cerr << "File not found" << std::endl;
        return false;
    }
    std::string current_line, header = "";
    while (getline(file, current_line)) {
        StringStrip(current_line);
        size_t equal_sign_pos = current_line.find(" = ");
        if (equal_sign_pos != std::string::npos) {
            std::string left = current_line.substr(0, equal_sign_pos);
            std::string right = current_line.substr(equal_sign_pos + 3);
            StringStrip(left);
            StringStrip(right);
            // std::cerr << left << '#' << std::endl;
            // std::cerr << right << '#' << std::endl;
            map_toml[header][left] = right;
        } else if (current_line[0] == '[' && current_line.back() == ']') {
            header = current_line.substr(1, current_line.size() - 2);
            StringStrip(header);
            // std::cerr << header << '#' << std::endl;
        }
    }
    file.close();
    return true;
}

// for immediate testing
int main() {
    std::string filename = "../tomls/tree.toml";
    MapTOML map_toml;
    assert(ParseMapTOML(filename, map_toml));
    return 0;
}
