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
    if (*chosen_ == answer_) {
        return true;
    }
    return false;
}

void Question::RenderQuestion() { // TODO: implement this
    // since we are using keyboard controls this needs to be done such that
    // when an option is selected it changes color
}

void Question::PickOption(SDL_Event event) {
    switch (event.key.keysym.sym) {
        case SDLK_UP:
            if (chosen_ != options_.begin()) {
                chosen_ = std::prev(chosen_, 1);
            }
            break;
        case SDLK_DOWN:
            if (chosen_ != options_.end()-1) {
                chosen_ = std::next(chosen_, 1);
            }
        default:
            break;
    }
}
