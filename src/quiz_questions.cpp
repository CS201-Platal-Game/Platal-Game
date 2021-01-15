#include "quiz.h"

Question::Question(const std::string& question_text,
                   const std::string& answer) {
    question_text_ = question_text;
    answer_ = answer;
    FontManager::Instance()->Load("questionFont", "./fonts/novem___.ttf", 15;
    FontManager::Instance()->Load("answerFont", "./fonts/novem___.ttf", 12;
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
    SDL_Rect quizBackground = {100, 900, 800, 800}; // x, y (of top left), width, height
	SDL_SetRenderDrawBlendMode(Game::renderer_, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(Game::renderer_, 209, 207, 198, 100); // light grey
    SDL_RenderFillRect(Game::renderer_, &quizBackground); // fill 
    
    // display the question at the top
    FontManager::Instance()->Draw("questionFont", question_text_, 150, 750,
                                  {56, 56, 56}, Game::renderer_); // color: dark grey




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
