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

    SDL_Rect quizBackground = {100, 800, 800, 800}; // x, y (of top left), width, height
	SDL_SetRenderDrawBlendMode(Game::renderer_, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(Game::renderer_, 209, 207, 198, 100); // light grey
    SDL_RenderFillRect(Game::renderer_, &quizBackground); // fill 
    
    // display the question at the top
    FontManager::Instance()->Draw("questionFont", question_text_, 150, 750,
                                  {56, 56, 56}, Game::renderer_); // color: dark grey
    
    // display basic instructions
    FontManager::Instance()->Draw("answerFont", "press up or down", 150, 730,
                                  {56, 56, 56}, Game::renderer_); // color: dark grey


    // TODO: deal with the issue of overflowing text (off the side)
    // do we want a box for each or do we just draw the text? 
    int yPos = 630 // starting y, will then decrease

    std::vector<std::pair<std::string, int>> colorChangeAssistant; //for later
    std::vector<std::string>::iterator i;
    for (i = options_.begin(); i != options_.end(); ++i) {
        FontManager::Instance()->Draw("answerFont", *i, 150, yPos,
                                  {56, 56, 56}, Game::renderer_); // color: dark grey
        colorChangeAssistant.push_back({*i, yPos});
        yPos = yPos - 17 //spacing = 5, font size = 12

        if (yPos < 100){ // if text passes the bottom of the box
        // i.e. if you have too many options to fit on the screen
            FontManager::Clean(); //clear text from screen
            colorChangeAssistant.clear();
            std::cout << "Error - text overflow, too may options" << std::endl;
        }
    }

    // idea of how to implement with controls: number the options, and as you press the down key
    // the option corresponding to the current number you are at will change color
    int currentOption = 0

    switch (event.key.keysym.sym) {
        case SDLK_UP:
            if (currentOption > 0){
                currentOption--; // go back one
            }
            else{ // if somehow less than 0
                currentOption = 0;
            }
            FontManager::Instance()->Draw("answerFont", colorChangeAssistant[currentOption->first],
                                 150, colorChangeAssistant[currentOption->second],
                                  {255, 209, 73}, Game::renderer_); //color: bright orange
            break;
        case SDLK_DOWN:
            if (currentOption < options_.size()) {
                currentOption++; // go forward one
                
            }
            else{ // if somehow greater than the number of options available
                currentOption = options_.size()-1;
            }
            FontManager::Instance()->Draw("answerFont", colorChangeAssistant[currentOption->first],
                                 150, colorChangeAssistant[currentOption->second],
                                  {255, 209, 73}, Game::renderer_); //color: bright orange
        default:
            break;
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
            if (chosen_ != options_.end()-1) {
                chosen_ = std::next(chosen_, 1);
            }
        default:
            break;
    }
}
