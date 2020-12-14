#include "quiz.h"

// TODO: finish implementation
Quiz::Quiz(Question *questions, int min_pass){
    questionArray_ = questions;

    correctAnswers_ = 0;  // default value at the start

    // not sure this part is necessary since it is a private attribute
    while (min_pass > 5){ // not sure if this works the way i want it to but
        // the idea is that if for some reason one inputs a min_pass that is greater than the number of questions
        // then you subtract until it is AT MOST equal to the number of questions
        min_pass--;
    }

    while (min_pass < 1){
        // same idea as above, except here it deals with the case where min_pass is too low
        min_pass++;
    }

    passCondition_ = min_pass;
}