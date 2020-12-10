#include "quiz_questions.h"

Question::Question(std::string question,
                   std::string op1,
                   std::string op2,
                   std::string op3,
                   std::string op4,
                   std::string ans){

    questionText_ = question;
    option1_ = op1;
    option2_ = op2;
    option3_ = op3;
    option4_ = op4;
    answer_ = ans;
    chosen_ = "default";

};

bool Question::checkCorrect() {
    if (chosen_ == answer_){
        return true;
    }
    return false;
};

void Question::renderQuestion() { // TODO: implement this

};

void Question::pickOption(){  //TODO: implement this
    // the idea is that when a person clicks on an option, it sets answer equal to the option clicked.
};