#pragma once
#include <string>


class Question{
    // constructor
    Question(std::string, std::string, std::string, std::string, std::string, std::string);
    // render options + question
    void renderQuestion();
    // check if correct
    bool checkCorrect();
    // allow user to choose an otpion
    void pickOption();

private:
    std::string questionText_; // question to ask
    std::string option1_, option2_, option3_, option4_; // options available
    std::string answer_; // correct answer to question
    std::string chosen_; // answer chosen by user
};


