#include <iostream>
#include <string>

/*
*   Samantha Sutter
*   Calorie Tracker App
*   Assignment 9
*   ITDEV-185
*/

// Abstract base class representing a person
class Person {
public:
    double weightPounds;
    double heightFeet;
    double age;
    double caloriesBurned;
    double caloriesConsumed;

    // Constructor for the Person class
    Person(double weight, double height, double age)
        : weightPounds(weight), heightFeet(height), age(age), caloriesBurned(0), caloriesConsumed(0) {}

    // Virtual function to calculate Total Daily Energy Expenditure
    virtual double calculateTDEE() const = 0;

    // Virtual function to get the gender of the person
    virtual std::string getGender() const = 0;

    // Virtual function to update calories consumed and burned
    virtual void updateCalories(double caloriesConsumed, double caloriesBurned) = 0;

    // Virtual function to get the remaining calories
    virtual double getRemainingCalories() const = 0;
};

// Concrete class representing a man
class Man : public Person {
public:
    // Constructor for the Man class
    Man(double weight, double height, double age)
        : Person(weight, height, age) {}

    // Calculate TDEE for a man
    double calculateTDEE() const override {
        double weightKg = weightPounds * 0.453592;
        double heightCm = heightFeet * 30.48;
        return 10 * weightKg + 6.25 * heightCm - 5 * age + 5 + caloriesBurned;
    }

    // Get the gender of a man
    std::string getGender() const override {
        return "Man";
    }

    // Update calories consumed and burned for a man
    void updateCalories(double caloriesConsumed, double caloriesBurned) override {
        this->caloriesConsumed += caloriesConsumed;
        this->caloriesBurned += caloriesBurned;
    }

    // Get the remaining calories for a man
    double getRemainingCalories() const override {
        return calculateTDEE() - caloriesConsumed + caloriesBurned;
    }
};

// Concrete class representing a woman
class Woman : public Person {
public:
    // Constructor for the Woman class
    Woman(double weight, double height, double age)
        : Person(weight, height, age) {}

    // Calculate TDEE for a woman
    double calculateTDEE() const override {
        double weightKg = weightPounds * 0.453592;
        double heightCm = heightFeet * 30.48;
        return 10 * weightKg + 6.25 * heightCm - 5 * age - 161 + caloriesBurned;
    }

    // Get the gender of a woman
    std::string getGender() const override {
        return "Woman";
    }

    // Update calories consumed and burned for a woman
    void updateCalories(double caloriesConsumed, double caloriesBurned) override {
        this->caloriesConsumed += caloriesConsumed;
        this->caloriesBurned += caloriesBurned;
    }

    // Get the remaining calories for a woman
    double getRemainingCalories() const override {
        return calculateTDEE() - caloriesConsumed + caloriesBurned;
    }
};

int main() {
    double weightPounds, heightFeet, age;
    double baseCalories;
    int choice;
    double remainingCalories = 0;

    // Introduction message
    std::cout << "Welcome to the Calorie Counter App!\nYou will be asked to enter your gender assigned at birth, height, and weight to determine your baseline goal.\n" << std::endl;

    std::string gender;  // Variable to store gender

    // Loop to allow user to re-enter gender if mistyped
    while (true) {
        // User input for gender
        std::cout << "Enter your gender (man or woman): ";
        std::cin >> gender;

        if (gender == "man" || gender == "woman") {
            break;  // Exit the loop if a valid gender is entered
        }
        else {
            std::cout << "Invalid gender input. Please enter 'man' or 'woman'." << std::endl;
        }
    }

    // User input for weight in pounds, height in feet, and age
    std::cout << "Enter your weight (in pounds): ";
    std::cin >> weightPounds;
    std::cout << "Enter your height (in feet): ";
    std::cin >> heightFeet;
    std::cout << "Enter your age: ";
    std::cin >> age;

    // Create a person object based on gender
    Person* person = nullptr;
    if (gender == "man") {
        person = new Man(weightPounds, heightFeet, age);
    }
    else {
        person = new Woman(weightPounds, heightFeet, age);
    }

    // Calculate and display the base calories needed
    baseCalories = person->calculateTDEE();
    std::cout << "Your baseline goal for maintenance: " << baseCalories << " calories per day" << std::endl;

    while (true) {
        // Display the menu
        std::cout << "\nMenu:\n";
        std::cout << "1. Log food intake\n";
        std::cout << "2. Add exercise\n";
        std::cout << "3. Exit application\n";
        std::cout << "Choose an option: ";
        std::cin >> choice;

        switch (choice) {
        case 1:
            double caloriesConsumedToday;
            std::cout << "\nEnter calories consumed today: ";
            std::cin >> caloriesConsumedToday;
            person->updateCalories(caloriesConsumedToday, 0);
            remainingCalories = person->getRemainingCalories();
            std::cout << "Remaining calories for the day: " << remainingCalories << " calories" << std::endl;
            break;
        case 2:
            double caloriesBurnedToday;
            std::cout << "\nEnter calories burned through exercise today: ";
            std::cin >> caloriesBurnedToday;
            person->updateCalories(0, caloriesBurnedToday);
            remainingCalories = person->getRemainingCalories();
            std::cout << "Remaining calories for the day: " << remainingCalories << " calories" << std::endl;
            break;
        case 3:
            // Display the remaining calories for the day
            remainingCalories = person->getRemainingCalories();
            std::cout << "\nRemaining calories for the day: " << remainingCalories << " calories" << std::endl;
            if (remainingCalories > 0) {
                std::cout << "! You have more calories to eat to meet your baseline.\nConsider meeting your daily calorie goal for better health." << std::endl;
            }
            return 0;
        default:
            std::cout << "Invalid option. Please choose a valid option (1, 2, or 3)." << std::endl;
        }
    }

    return 0;
}

