#include <iostream>
#include <vector>
#include <random>
#include <cmath>

class NumberGuessingGame {
private:
    const int LEVEL1_MIN_RANGE = 1;
    const int LEVEL1_MAX_RANGE = 50;
    const int LEVEL2_MIN_RANGE = 1;
    const int LEVEL2_MAX_RANGE = 100;
    const int LEVEL3_MIN_RANGE = 1;
    const int LEVEL3_MAX_RANGE = 200;

    int totalGames = 0;
    int totalGuesses = 0;

public:
    void start() {
        bool playAgain = true;
        std::cout << "Welcome to the Number Guessing Game!" << std::endl;
        
        while (playAgain) {
            std::cout << "\nChoose difficulty level:" << std::endl;
            std::cout << "1. Level 1 [range : 1 to 50]" << std::endl;
            std::cout << "2. Level 2 [range : 1 to 100]" << std::endl;
            std::cout << "3. Level 3 [range : 1 to 200]" << std::endl;
            std::cout << "Enter your choice: ";
            int choice;
            std::cin >> choice;
            int minRange, maxRange;

            switch (choice) {
                case 1:
                    minRange = LEVEL1_MIN_RANGE;
                    maxRange = LEVEL1_MAX_RANGE;
                    break;
                case 2:
                    minRange = LEVEL2_MIN_RANGE;
                    maxRange = LEVEL2_MAX_RANGE;
                    break;
                case 3:
                    minRange = LEVEL3_MIN_RANGE;
                    maxRange = LEVEL3_MAX_RANGE;
                    break;
                default:
                    std::cout << "Invalid choice. Defaulting to Level 1." << std::endl;
                    minRange = LEVEL1_MIN_RANGE;
                    maxRange = LEVEL1_MAX_RANGE;
            }

            playGame(minRange, maxRange);
            totalGames++;

            std::cout << "\nDo you want to play again? (yes/no): ";
            std::string playAgainChoice;
            std::cin >> playAgainChoice;
            playAgain = (playAgainChoice == "yes" || playAgainChoice == "y");
        }

        std::cout << "\nTotal games played: " << totalGames << std::endl;
        std::cout << "Total guesses made: " << totalGuesses << std::endl;
        double averageGuesses = totalGuesses / static_cast<double>(totalGames);
        std::cout << "Average guesses per game: " << averageGuesses << std::endl;
        std::cout << "Thank you for playing! Goodbye!" << std::endl;
    }

    void playGame(int minRange, int maxRange) {
        bool isGuessCorrect = false;
        int guessAttempts = 0;
        int targetNumber = generateTargetNumber(minRange, maxRange);
        int lastGuess = 0; // Store the last guess
        bool hintGiven = false; // Track if hint has been given

        std::cout << "\nLet's start guessing! The number is between " << minRange << " and " << maxRange << "." << std::endl;

        while (!isGuessCorrect) {
            if (!hintGiven && guessAttempts >= 3) {
                std::cout << "\nHints:" << std::endl;
                provideHint(targetNumber, minRange, maxRange);
                hintGiven = true;
            }

            int userGuess = getUserGuess();
            totalGuesses++;
            guessAttempts++;

            if (userGuess > targetNumber) {
                if (userGuess - targetNumber > (maxRange - minRange) / 4)
                    std::cout << "Too high!" << std::endl;
                else
                    std::cout << "High!" << std::endl;
            } else if (userGuess < targetNumber) {
                if (targetNumber - userGuess > (maxRange - minRange) / 4)
                    std::cout << "Too low!" << std::endl;
                else
                    std::cout << "Low!" << std::endl;
            } else {
                std::cout << "\nCongratulations! You guessed it right!" << std::endl;
                isGuessCorrect = true;
            }
        }

        std::cout << "You found the number in " << guessAttempts << " guesses." << std::endl;
    }

    int generateTargetNumber(int minRange, int maxRange) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(minRange, maxRange);
        return dis(gen);
    }

    int getUserGuess() {
        std::cout << "\nTake a guess: ";
        int guess;
        std::cin >> guess;
        return guess;
    }

    void provideHint(int targetNumber, int minRange, int maxRange) {
        if (isEven(targetNumber))
            std::cout << "The number is even." << std::endl;
        else
            std::cout << "The number is odd." << std::endl;

        if (isPrime(targetNumber))
            std::cout << "The number is prime." << std::endl;
        else
            std::cout << "The number is not prime." << std::endl;

        std::cout << "The number is between " << minRange << " and " << maxRange << "." << std::endl;
    }

    bool isEven(int number) {
        return (number % 2 == 0);
    }

    bool isPrime(int number) {
        if (number <= 1)
            return false;
        if (number <= 3)
            return true;
        if (number % 2 == 0 || number % 3 == 0)
            return false;

        for (int i = 5; i * i <= number; i += 6) {
            if (number % i == 0 || number % (i + 2) == 0)
                return false;
        }

        return true;
    }
};

int main() {
    NumberGuessingGame game;
    game.start();
    return 0;
}