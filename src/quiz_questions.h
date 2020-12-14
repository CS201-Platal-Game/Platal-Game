#pragma once
#include <string>


class Question{
    // constructor
    //TODO: make this a vector
    Question(std::string, std::string, std::string, std::string, std::string, std::string);
    // render options + question
    void renderQuestion();
    // check if correct
    bool checkCorrect();
    // allow user to choose an otpion
    void pickOption(); //TODO: think about how to implement this

private:
    std::string questionText_; // question to ask
    std::string option1_, option2_, option3_, option4_; // options available: needs to be a vector
    std::string answer_; // correct answer to question [make indexes/pters]
    std::string chosen_; // answer chosen by user
};


