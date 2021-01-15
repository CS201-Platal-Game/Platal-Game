#include "quiz.h"

// TODO: finish implementation
Question::Question(const std::string& question_text, const std::string& answer) {
    question_text_ = question_text;
    answer_ = answer;
}

void Question::AddOption(const std::string& option) {
    options_.push_back(option);
}

void Question::SetOptions(const std::vector<std::string>& options) {
    options_ = options;
}

bool Question::CheckCorrect() {
    return (*chosen_ == answer_);
}

Quiz::Quiz(const std::vector<Question>& questions) { questions_ = questions; }

void Quiz::SetPass(int pass_condition) {
    pass_condition_ =
        (pass_condition > (int)questions_.size() ? questions_.size()
                                                 : pass_condition);
}

bool Quiz::Pass() { return correct_answers_ >= pass_condition_; }

void Quiz::HandleInput(SDL_Event event) {}