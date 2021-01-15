#include "dialogue.h"
#include "game.h"
#include "utils/font_manager.h"
#include "utils/texture_manager.h"
#include <fstream>
#include <iostream>
#include <string>

DialogueNode::DialogueNode() {}
DialogueNode::~DialogueNode() {}

DialogueNode::DialogueNode(const std::string& line) {
    line_ = line;
}

void DialogueNode::AddResponse(const std::string& response,
                               DialogueNode* const next) {
    responses_.emplace_back(response, next);
}

void DialogueNode::PrintLine() {
    std::cout << line_ << std::endl;
}

void DialogueNode::PrintResponses() {
    int number_of_responses = responses_.size();
    for (int i = 0; i < number_of_responses; i += 1) {
        std::cout << std::get<0>(responses_[i]) << std::endl;
    };
}

std::string DialogueNode::getLine() {
    return line_;
}

std::vector<std::pair<std::string, DialogueNode*>>
DialogueNode::getResponses() {
    return responses_;
}

// Goes to the next DialogueNode.
void DialogueNode::Next(int response_id) {
    // TODO we dont need it anymore (I hope)
}

bool DialogueNode::GetVisited() {
    return visited_;
}

bool DialogueNode::GetStack() {
    return in_stack_;
}

void DialogueNode::SetVisited(bool visited) {
    visited_ = visited;
}

void DialogueNode::SetStack(bool stack) {
    in_stack_ = stack;
}

Dialogue::Dialogue(const char filename[]) {
    this->Import(filename);
    selected_response = 0;
}

Dialogue::~Dialogue() {
    int number_of_nodes = nodes_.size();
    for (int i = 0; i < number_of_nodes; i += 1) {
        delete nodes_[i];
    }
}

// Add a DialogueNode with no responses.
void Dialogue::AddNode(const std::string& line) {
    auto* node = new DialogueNode(line);
    nodes_.emplace_back(node);
}

// Calls DialogueNode::AddResponse.
// The IDs are the input order.
void Dialogue::AddEdge(int node_id, int response_id, int next_node_id) {
    nodes_[node_id]->AddResponse(response_lines_[response_id],
                                 nodes_[next_node_id]);
}

// Generates the dialogue from a text file (sample file in Notion/Structure).
// Returns false on failure (e.g. file does not exist).
bool Dialogue::Import(const char* filename) {
    // TODO where do we put dialogue files? -> create a folder
    std::ifstream dialogue(filename);
    std::string line_reader;
    if (!dialogue) {
        std::cout << "Couldn't open file" << std::endl;
        return false;
    }
    getline(dialogue, line_reader);
    int sample_n = std::stoi(line_reader);
    for (int i = 0; i < sample_n; i += 1) {
        getline(dialogue, line_reader);
        this->AddNode(line_reader);
    };
    getline(dialogue, line_reader);
    int response_n = std::stoi(line_reader);
    for (int i = 0; i < response_n; i += 1) {
        getline(dialogue, line_reader);
        response_lines_.push_back(line_reader);
    };
    getline(dialogue, line_reader);
    // int edge_n = std::stoi(line_reader);
    int from, with, to;
    while (dialogue >> from >> with >> to) {
        this->AddEdge(from, with, to);
    };
    head_ = nodes_[0];
    current = head_;
    return true;
}

// Prints the current line and possible responses, then call Next().
void Dialogue::Advance() {
    // TODO we probably don't need this either
    current->PrintLine();
    current->PrintResponses();
}

void Dialogue::Render() {
    SDL_Rect dialog_rect = {0, 460, 896, 240};
    SDL_SetRenderDrawBlendMode(Game::renderer_, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(Game::renderer_, 0, 0, 0, 196);
    SDL_RenderFillRect(Game::renderer_, &dialog_rect);

    FontManager::Instance()->Draw("retganon", current->getLine(), 20, 480,
                                  {200, 50, 50}, Game::renderer_);
    int number_of_responses = current->getResponses().size();

    if (number_of_responses == 0) {
        FontManager::Instance()->Draw("retganon", "Press Z or [Enter] to continue", 20,
                                      530, {100, 100, 100}, Game::renderer_);
    }

    for (int i = 0; i < number_of_responses; i += 1) {
        std::string respo = "-" + std::get<0>(current->getResponses()[i]);
        int spacepos = 18;
        int j = 7;
        if (respo.length() > 18) {
            spacepos = respo.find(" ", 18 - j);
            while (spacepos > 18) {
                j += 1;
                spacepos = respo.find(" ", 18 - j);
            }
        }
        if (i == selected_response) {
            FontManager::Instance()->Draw("retganon", respo.substr(0,spacepos),
                                          10 + i * (896 / 3), 570,
                                          {175, 175, 255}, Game::renderer_);
            if (respo.length() > 18) {
                FontManager::Instance()->Draw("retganon", " " + respo.substr(spacepos + 1),
                                              10 + i * (896 / 3), 600,
                                              {175, 175, 255}, Game::renderer_);
            }

        } else {
            FontManager::Instance()->Draw("retganon", respo.substr(0,spacepos),
                                          10 + i * (896 / 3), 570,
                                          {255, 255, 255}, Game::renderer_);
            if (respo.length() > 18) {
                FontManager::Instance()->Draw("retganon", " " + respo.substr(spacepos + 1),
                                              10 + i * (896 / 3), 600,
                                              {255, 255, 255}, Game::renderer_);
            }
        };
    };
}

void Dialogue::HandleInput(SDL_Event event) {
    switch (event.key.keysym.sym) {
    case SDLK_z:
        if (current->getResponses().size() == 0) {
            Game::game_state_ = kWorld;
            this->Reset();
            selected_response = 0;
        } else {
            current = std::get<1>(current->getResponses()[selected_response]);
            selected_response = 0;
            this->Advance();
        }
        break;
    case SDLK_RETURN:
        if (current->getResponses().size() == 0) {
            Game::game_state_ = kWorld;
            this->Reset();
            selected_response = 0;
        } else {
            current = std::get<1>(current->getResponses()[selected_response]);
            selected_response = 0;
            this->Advance();
        }
        break;
    case SDLK_LEFT:
        if (selected_response > 0) {
            selected_response += -1;
        }
        break;
    case SDLK_RIGHT: {
        int number_of_responses = current->getResponses().size();

        if (selected_response < number_of_responses - 1) {
            selected_response += 1;
        }
        break;
    }
    default:
        break;
    }
}

// Resets the conversation, e.g. the protag talks to the NPC again.
void Dialogue::Reset() {
    current = head_;
    // Given the current implementation of the dialogue this should be sufficient
}

// Verifies if the graph is cycle-free. Returns true on success.
bool Dialogue::CheckCycle() {
    for (std::vector<DialogueNode*>::iterator i = nodes_.begin(); i != nodes_.end(); i++) {
        (*i)->SetVisited(false);
        (*i)->SetStack(false);
    }
    for (std::vector<DialogueNode*>::iterator i = nodes_.begin(); i != nodes_.end(); i++) {
        if ((*i)->CheckCycleUtil()) {
            return true;
        }
    }
    return false; 
}

bool DialogueNode::CheckCycleUtil() {
    if (!GetVisited()) {
        SetVisited(true);
        SetStack(true);
        std::vector<std::pair<std::string, DialogueNode*>>::iterator i;
        for( i = responses_.begin(); i != responses_.end(); i++) {
            DialogueNode* temp_node = i->second;
            if (!temp_node->GetVisited() && temp_node->CheckCycleUtil()) {
                return true;
            }
            else if (temp_node->GetStack()) { 
                return true;
            }
        }
    }
    SetStack(false);
    return false;
}