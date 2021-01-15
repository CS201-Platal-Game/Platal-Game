#include "quiz.h"
#include "game.h"

// TODO: finish implementation
Quiz::Quiz(const std::vector<Question>& questions) { questions_ = questions; }

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
            break;

        case SDLK_LEFT:
            current_question->PickOption(event);
            break;

        case SDLK_RIGHT:
            current_question->PickOption(event);
            break;
    }
}

void:: Quiz::MoveOn(){
    if (current_question== questions_.end()-1){
        (*myInstance) = kWorld; // End the game, change its state to not 
    }
    else{
        current_question++;
        ExecuteQuiz();
        DisplayScore();
    }
}