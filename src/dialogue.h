#pragma once
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include <string>
#include <utility>
#include <vector>

class DialogueNode {
  public:
    DialogueNode();
    DialogueNode(const std::string& line);
    ~DialogueNode();

    void AddResponse(const std::string& response, DialogueNode* const next);

    // Prints to console.
    void PrintLine();
    void PrintResponses();

    std::string getLine();
    std::vector<std::pair<std::string, DialogueNode*>> getResponses();

    // Accesses the visited_ and in_stack_ attributes
    bool GetVisited();
    bool GetStack();

    // Sets the visited_ and in_stack_ attributes
    void SetVisited(bool visited);
    void SetStack(bool stack);

    // Auxiliary function for CheckCycle()
    bool CheckCycleUtil();

  private:
    // Line of NPCs or objects.
    std::string line_;

    // Vector of responses and corresponding DialogueNode.
    // The dialogue ends when responses_ is empty.
    std::vector<std::pair<std::string, DialogueNode*>> responses_;

    // Used for the CheckCycle() method of the Dialogue class
    bool visited_;
    bool in_stack_;
};

// Dialogues for NPCs or objects.
// Contains a directed graph, represented by an adjacency list.
class Dialogue {
  public:
    Dialogue();
    Dialogue(const char filename[]);
    ~Dialogue();

    // Add a DialogueNode with no responses.
    void AddNode(const std::string& line);

    // Calls DialogueNode::AddResponse.
    // The IDs are the input order.
    void AddEdge(int node_id, int response_id, int next_node_id);

    // Generates the dialogue from a text file (sample file in Notion/Structure).
    // Returns false on failure (e.g. file does not exist).
    bool Import(const char filename[]);

    // Prints the current line and possible responses, then call Next().
    void Advance();

    // Resets the conversation, e.g. the protag talks to the NPC again.
    void Reset();

    // Verifies if the graph is cycle-free. Returns true on success.
    bool CheckCycle();

    void Render();

    void HandleInput(SDL_Event key);

  private:
    DialogueNode* head_;
    DialogueNode* current;
    int selected_response;
    // At the moment, each response is stored twice, one here and
    // one in DialogueNode. Feel free to optimize this.
    std::vector<std::string> response_lines_;
    std::vector<DialogueNode*> nodes_;
};
