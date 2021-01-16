#pragma once
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include <string>
#include <vector>
#include "utils/font_manager.h"

class Question {
  public:
    // constructor
    Question(const std::string& question_text, const std::string& answer);
    Question(const std::vector<std::string>& options);

    void AddOption(const std::string& option);
    void SetOptions(const std::vector<std::string>& options);
    void RenderQuestion();
    bool CheckCorrect();
    void PickOption(SDL_Event event);
    std::string GetQuestionText();

  private:
    std::string question_text_;
    std::vector<std::string> options_; 
    std::string answer_; // correct answers
    std::vector<std::string>::iterator chosen_; // user's answers
};

class Quiz {
  public:
    Quiz(const std::vector<Question>& questions);

    void SetPass(int pass_condition); 
    void ExecuteQuiz(); // runs RenderQuestions for each question.
    void DisplayScore(); //  quiz results (fail/pass depending on the pass condition)
    void HandleInput(SDL_Event event);
    void MoveOn();
    bool Pass();

  private:
    int correct_answers_ = 0; 
    int pass_condition_ = 3;  // minimum correct answers needed to pass
    std::vector<Question> questions_;
    std::vector<Question>::iterator current_question;
};
