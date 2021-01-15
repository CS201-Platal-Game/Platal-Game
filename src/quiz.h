#pragma once
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include <string>
#include <vector>
#include "utils/font_manager.h"

class Question {
  public:
    // constructor
    // TODO: create list of constant questions.
    Question(const std::string& question_text, const std::string& answer);
    Question(const std::vector<std::string>& options);
    void AddOption(const std::string& option);

    void SetOptions(const std::vector<std::string>& options);

    void RenderQuestion();

    bool CheckCorrect();

    void PickOption(SDL_Event event); // TODO: think about how to implement this

    std::string GetQuestionText();

  private:
    std::string question_text_;        // question to ask
    std::vector<std::string> options_; // options available
    std::string answer_; // correct answer to question [make indexes/pters]
    std::vector<std::string>::iterator chosen_; // answer chosen by user
};

class Quiz {
  public:
    Quiz(const std::vector<Question>& questions);

    void SetPass(int pass_condition); // optional, should be at 3

    void ExecuteQuiz(); // TODO e.g. runs RenderQuestions for each question.

    void DisplayScore(); //  Says whether you passed or failed
    //compares correct answers with the passed condition


    void HandleInput(SDL_Event event);
    void MoveOn();
    // Return the verdict of the Quiz.
    bool Pass();

  private:
    int correct_answers_ = 0; // stores number of correct answers
    int pass_condition_ = 3;  // minimum level of correct answers needed to pass
    std::vector<Question> questions_;
    std::vector<Question>::iterator current_question;
};
