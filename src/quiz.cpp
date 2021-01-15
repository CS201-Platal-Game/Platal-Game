#include "quiz.h"
#include "game.h"

Quiz::Quiz(const std::vector<Question>& questions) { 
    questions_ = questions; 
    current_question = questions_.begin();
    FontManager::Instance()->Load("quiz_font", "./fonts/chary___.ttf", 50);

}

void Quiz::SetPass(int pass_condition) {
    pass_condition_ =
        (pass_condition > (int)questions_.size() ? questions_.size()
                                                 : pass_condition);
}

bool Quiz::Pass() { return correct_answers_ >= pass_condition_; }

void Quiz::HandleInput(SDL_Event event) {
    switch (event.key.keysym.sym) {
        case SDLK_KP_ENTER:
            current_question->CheckCorrect();
            MoveOn();
            break;

        case SDLK_UP:
            current_question->PickOption(event);
            break;

        case SDLK_DOWN:
            current_question->PickOption(event);
            break;
    }
}
void Quiz::ExecuteQuiz(){
    current_question->RenderQuestion();
}

void Quiz::DisplayScore(){
    SDL_Rect score_rect = {350, 300, 290, 50}; // tochange (size)
    SDL_SetRenderDrawBlendMode(Game::renderer_, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(Game::renderer_, 0, 0, 0, 200); // color
    SDL_RenderFillRect(Game::renderer_, &score_rect);
    if (correct_answers_ >= pass_condition_){
        int w = FontManager::Instance()->RenderWidth("quiz_font", "You passed!");

        FontManager::Instance()->Draw("quiz_font", "You passed!",
                                      350 + (290 - w)/2, 300,
                                      {16, 200, 16}, Game::renderer_);
    }
    else{
        int w = FontManager::Instance()->RenderWidth("quiz_font", "You passed!");

        FontManager::Instance()->Draw("quiz_font", "You FAILED!",
                                      350 + (290 - w)/2, 300,
                                      {200, 16, 16}, Game::renderer_);
    }
}

void Quiz::MoveOn(){
    if (current_question== questions_.end()-1){
        Game::game_state_ = kWorld; // End the game, change its state to not 
    }
    else{
        current_question++;
        ExecuteQuiz();
        DisplayScore();
    }
}