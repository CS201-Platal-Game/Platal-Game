#include "quiz.h"

Question::Question(const std::string& question_text,
                   const std::string& answer) {
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
    if (chosen_ == answer_) {
        return true;
    }
    return false;
}

void Question::RenderQuestion() { // TODO: implement this
    // since we are using keyboard controls this needs to be done such that
    // when an option is selected it changes color
}

void Question::PickOption() { // TODO: implement this
    // the idea is that when a person clicks on an option, it sets answer equal
    // to the option clicked.
}
