#include "dialogue.h"
#include <iostream>
#include <fstream>
#include <string>

DialogueNode::DialogueNode() {}
DialogueNode::~DialogueNode() {}

DialogueNode::DialogueNode(const std::string &line) {
    line_ = line;
}

void DialogueNode::AddResponse(const std::string &response, DialogueNode* const next) {
    responses_.emplace_back(response, next);
}

void DialogueNode::PrintLine() {
    std::cout << line_ << std::endl;
}

void DialogueNode::PrintResponses() {
    for (int i = 0; i < responses_.size(); i += 1) {
        std::cout << std::get<0>(responses_[i]) << std::endl;
    };
}

// Goes to the next DialogueNode.
void DialogueNode::Next(int response_id) {
    //TODO
}

Dialogue::Dialogue(const char filename[]) {
    this->Import(filename);
}

Dialogue::~Dialogue() {
    for (int i = 0; i < nodes_.size(); i += 1) {
        delete nodes_[i];
    }
}

// Add a DialogueNode with no responses.
void Dialogue::AddNode(const std::string &line) {
    auto *node = new DialogueNode(line);
    nodes_.emplace_back(node);
}

// Calls DialogueNode::AddResponse.
// The IDs are the input order.
void Dialogue::AddEdge(int node_id, int response_id, int next_node_id) {
    nodes_[node_id]->AddResponse(response_lines_[response_id], nodes_[next_node_id]);
}

// Generates the dialogue from a text file (sample file in Notion/Structure).
// Returns false on failure (e.g. file does not exist).
bool Dialogue::Import(const char *filename) {
    //TODO where do we put dialogue files? -> create a folder
    std::ifstream dialogue(filename);
    std::string line_reader;
    if(!dialogue) {
        std::cout << "Couldn't open file" << std::endl;
    }
    getline(dialogue,line_reader);
    int sample_n = std::stoi(line_reader);
    for (int i = 0; i < sample_n; i += 1) {
        getline(dialogue,line_reader);
        this->AddNode(line_reader);
    };
    getline(dialogue,line_reader);
    int response_n = std::stoi(line_reader);
    for (int i = 0; i < response_n; i += 1) {
        getline(dialogue,line_reader);
        response_lines_.push_back(line_reader);
    };
    getline(dialogue,line_reader);
    int edge_n = std::stoi(line_reader);
    int from, with, to;
    while (dialogue >> from >> with >> to) {
        this->AddEdge(from, with, to);
    };
    head_ = nodes_[0];
    current = 0;
}

// Prints the current line and possible responses, then call Next().
void Dialogue::Advance() {
    nodes_[current]->PrintLine();
    nodes_[current]->PrintResponses();
}


// Resets the conversation, e.g. the protag talks to the NPC again.
void Dialogue::Reset() {
    //TODO - implement
}

// Verifies if the graph is cycle-free. Returns true on success.
bool Dialogue::CheckCycle() {
    //TODO - implement
}
