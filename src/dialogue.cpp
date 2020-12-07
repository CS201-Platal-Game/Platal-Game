#include "dialogue.h"
#include <iostream>
#include <fstream>

DialogueNode::DialogueNode() {

}

DialogueNode::DialogueNode(const std::string &line) {
    line_ = line;
}

DialogueNode::~DialogueNode() {

}

void DialogueNode::AddResponse(const std::string &response, DialogueNode* const next) {
    responses_.emplace_back(response, next);
}

void DialogueNode::PrintLine() {
    std::cout << line_;
};

void DialogueNode::PrintResponses() {
    for (int i; i <= responses_.size(); i += 1) {
        std::cout << std::get<1>(responses_[i]);
    };
}

// Goes to the next DialogueNode.
void DialogueNode::Next(int response_id) {

}

Dialogue::Dialogue() {

}

Dialogue::~Dialogue() {

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
    std::ifstream dialogue;
    dialogue.open(filename, std::ios::in);
    std::string linereader;
    getline(dialogue,linereader);
    int sample_n = std::stoi(linereader);
    for (int i; i <= sample_n; i += 1) {
        getline(dialogue,linereader);
        this->AddNode(linereader);
    };
    getline(dialogue,linereader);
    int response_n = std::stoi(linereader);
    for (int i; i <= response_n; i += 1) {
        getline(dialogue,linereader);
        response_lines_.push_back(linereader);
    };
    getline(dialogue,linereader);
    int edge_n = std::stoi(linereader);
    for (int i; i <= edge_n; i += 1);
        getline(dialogue, linereader);
        //TODO assumed the numbers have 1 digits correct it
        int from= std::stoi(linereader.substr(0,1));
        int with= std::stoi(linereader.substr(2,1));
        int to= std::stoi(linereader.substr(4,1));
        this->AddEdge(from,with,to);
}

// Prints the current line and possible responses, then call Next().
void Dialogue::Advance() {

}

// Resets the conversation, e.g. the protag talks to the NPC again.
void Dialogue::Reset() {

}

// Verifies if the graph is cycle-free. Returns true on success.
bool Dialogue::CheckCycle() {

}