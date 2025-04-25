# Typing Speed Tracker - OOP Course Project

## **Project Overview**

This project is developed as part of the Object-Oriented Programming (OOP) course. It is a typing speed tracker that allows users to practice their typing speed and accuracy by typing random paragraphs. The application tracks the typing progress, calculates words per minute (WPM), characters per minute (CPM), and accuracy, and includes a timer feature. The project demonstrates the use of OOP principles such as **Encapsulation**, **Inheritance**, **Polymorphism**, **Abstraction**, and **Encapsulation**.

## **Contributors**
- **Minhal Raza** (Student ID: 24K-0554)
- **Ali Rooman** (Student ID: 24K-0792)
- **Madni Moazzam** (Student ID: 24K-0868)

## **Features**
- **Typing Speed Tracking**: Tracks the user’s typing progress, calculates Words Per Minute (WPM) and Characters Per Minute (CPM).
- **Accuracy Calculation**: Measures typing accuracy based on correct and incorrect keystrokes.
- **Timer**: Includes a 30-second countdown timer for timed typing sessions.
- **Difficulty Modes**: Includes three difficulty levels:
  - **Easy Mode**: Basic typing texts for beginners.
  - **Medium Mode**: Intermediate typing texts focused on technical topics.
  - **Hard Mode**: Advanced typing texts focused on complex technical topics like machine learning, cybersecurity, and programming.
- **Dynamic Paragraph Selection**: Selects a random paragraph from a pool of 10 predefined paragraphs.
- **User Feedback**: Provides real-time feedback on performance, including WPM, CPM, accuracy, and mistakes made.
- **Restart Functionality**: Allows users to restart the typing session by pressing the "R" key.
- **Resizing Support**: The application supports dynamic resizing of the window, adjusting the layout accordingly.
- **Polymorphic Typing Modes**: Uses polymorphism to allow the different typing modes (Easy, Medium, Hard) to implement specific behavior.

## **Technologies Used**
- **C++**: The core programming language used for implementing the logic and functionality.
- **raylib**: A simple and easy-to-use library for creating games and graphical applications.

## **Installation Instructions**
To run the project, you will need to have **raylib** installed on your system. Follow these steps to set up the project:

### **For Windows (via MinGW)**
1. **Install MinGW**: If you don’t already have MinGW installed, you can download it from [here](http://www.mingw.org/).
2. **Install raylib**:
   - Clone the raylib repository: 
     ```bash
     git clone https://github.com/raysan5/raylib.git
     ```
   - Build raylib using the following commands:
     ```bash
     cd raylib
     make
     sudo make install
     ```
3. **Compile the Project**:
   - Open a terminal or command prompt and navigate to the project folder.
   - Run the following command to compile the project:
     ```bash
     g++ -o TypingSpeedTracker main.cpp -lraylib -lopengl32 -lm -lpthread -ldl -lX11
     ```
4. **Run the Application**:
   - After compiling, run the program using the following command:
     ```bash
     ./TypingSpeedTracker
     ```