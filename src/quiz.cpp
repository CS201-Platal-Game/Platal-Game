#include "quiz.h"

// TODO: finish implementation
Quiz::Quiz(const std::vector<Question>& questions) { questions_ = questions; }

void Quiz::SetPass(int pass_condition) {
    pass_condition_ =
        (pass_condition > (int)questions_.size() ? questions_.size()
                                                 : pass_condition);
}

bool Quiz::Pass() { return correct_answers_ >= pass_condition_; }
