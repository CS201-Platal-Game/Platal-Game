#pragma once
#include <string>
#include "quiz_questions.h"

class Quiz{
    Quiz(); // basic constructor
    // constructor for 5 questions
    // not sure if we should leave it like this or create a constructor that works for n questions

    Quiz(Question *questions, int); //TODO: make this a vector (n qs)
    void displayScore(); // give total score at the end
    bool pass(); // condition for completing challenge, eg if at least 3/5 questions correct

private:
    int correctAnswers_; // stores number of correct answers
    int passCondition_; // minimum level of correct answers needed to pass
    Question *questionArray_; // array of questions

};
