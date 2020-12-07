#pragma once

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

    // Goes to the next DialogueNode.
    void Next(int response_id);

  private:
    // Line of NPCs or objects.
    std::string line_;

    // Vector of responses and corresponding DialogueNode.
    // The dialogue ends when responses_ is empty.
    std::vector<std::pair<std::string, DialogueNode*>> responses_;
};

// Dialogues for NPCs or objects.
// Contains a directed graph, represented by an adjacency list.
class Dialogue {
  public:
    Dialogue();
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

  private:
    DialogueNode* head_;
    int current;
    // At the moment, each response is stored twice, one here and
    // one in DialogueNode. Feel free to optimize this.
    std::vector<std::string> response_lines_;
    std::vector<DialogueNode*> nodes_;
};
