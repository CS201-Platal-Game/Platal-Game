#include "quiz.h"

// TODO: finish implementation
Quiz::Quiz(const std::vector<Question>& questions) { 
    questions_ = questions; 
    FontManager::Instance()->Load("quizFont", "./fonts/novem___.ttf", 15;
    }

void Quiz::SetPass(int pass_condition) {
    pass_condition_ =
        (pass_condition > (int)questions_.size() ? questions_.size()
                                                 : pass_condition);
}

bool Quiz::Pass() { return correct_answers_ >= pass_condition_; }

void Quiz::HandleInput(SDL_Event event) {}

std::string passOrNot(bool pass){ // if we want to be fancy we can also display the score I guess
    if (pass){
        return "you passed the quiz!"
    }
    else{
        return "you failed :("
    }
}


void Quiz::DisplayScore(){ // render function for score

}

void Quiz::RenderQuestions(){ // render function for questions
    // window is supposed to be slightly smaller than viewport
    // window is 900 x 900
    SDL_Rect quizDisplay = {100, 900, 800, 800}; // x, y (of top left), width, height
	SDL_SetRenderDrawBlendMode(Game::renderer_, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(Game::renderer_, 209, 207, 198, 100); // light grey
    SDL_RenderFillRect(Game::renderer_, &quizDisplay); // fill 

}