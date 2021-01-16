#include "game.h"
#include "quiz.h"

Question::Question(const std::string& question_text,
                   const std::string& answer) {
    question_text_ = question_text;
    answer_ = answer;
    FontManager::Instance()->Load("questionFont", "./fonts/novem___.ttf", 15);
    FontManager::Instance()->Load("answerFont", "./fonts/novem___.ttf", 12);
}

Question::Question(const std::vector<std::string>& options) {
    options_ = options;
    chosen_ = options_.begin();
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

void Question::RenderQuestion() {
    SDL_Rect quizBackground = {100, 800, 800, 800};
    SDL_SetRenderDrawBlendMode(Game::renderer_, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(Game::renderer_, 209, 207, 198, 100); // light grey
    SDL_RenderFillRect(Game::renderer_, &quizBackground);        // fill

    // display the question at the top
    FontManager::Instance()->Draw("questionFont", question_text_, 150, 750,
                                  {56, 56, 56}, Game::renderer_); // color: dark grey

    // display basic instructions
    FontManager::Instance()->Draw("answerFont", "press up or down", 150, 730,
                                  {56, 56, 56}, Game::renderer_); // color: dark grey

    int yPos = 630;
    std::vector<std::pair<std::string, int>> colorChangeAssistant;
    std::vector<std::string>::iterator i;
    for (i = options_.begin(); i != options_.end(); ++i) {
        if (i == chosen_)
            FontManager::Instance()->Draw("answerFont", *i, 150, yPos,
                                          {255, 209, 73}, Game::renderer_);
        else
            FontManager::Instance()->Draw("answerFont", *i, 150, yPos,
                                          {255, 209, 73}, Game::renderer_);

        yPos = yPos - 17; //spacing = 5, font size = 12
    }
}

void Question::PickOption(SDL_Event event) {
    switch (event.key.keysym.sym) {
    case SDLK_UP:
        if (chosen_ != options_.begin()) {
            chosen_ = std::prev(chosen_, 1);
        }
        break;
    case SDLK_DOWN:
        if (chosen_ != options_.end() - 1) {
            chosen_ = std::next(chosen_, 1);
        }
    default:
        break;
    }
}
