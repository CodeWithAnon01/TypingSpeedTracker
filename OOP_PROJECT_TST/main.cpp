#include "raylib.h"
#include <string>
#include <ctime>
#include <cstdlib>
#include <cstring>

// Base class for different text modes
class TextMode {
protected:
    const char* text;
    int textLength;
    int currentPosition;
    int mistakes;
    float startTime;
    bool isTyping;
    bool isTimeUp;
    bool isStarted;
    const char* paragraphs[10];
    int currentParagraph;
    bool wordWrap;

public:
    TextMode() : currentPosition(0), mistakes(0), startTime(0), isTyping(false), 
                isTimeUp(false), isStarted(false), currentParagraph(0), wordWrap(true) {
    }
    virtual ~TextMode() {}

    virtual const char* getText() { return text; }
    virtual int getLength() { return textLength; }
    virtual int getCurrentPosition() { return currentPosition; }
    virtual int getMistakes() { return mistakes; }
    virtual float getStartTime() { return startTime; }
    virtual bool getIsTyping() { return isTyping; }
    virtual bool getIsTimeUp() { return isTimeUp; }
    virtual bool getIsStarted() { return isStarted; }
    virtual bool getWordWrap() { return wordWrap; }
    virtual void toggleWordWrap() { wordWrap = !wordWrap; }

    virtual void startTyping() {
        if (!isTyping && isStarted) {
            isTyping = true;
            startTime = GetTime();
            isTimeUp = false;
        }
    }

    virtual void checkInput(int key) {
        if (!isTyping || isTimeUp || !isStarted) return;

        if (key == text[currentPosition]) {
            currentPosition++;
        } else {
            mistakes++;
        }
    }

    virtual bool isComplete() {
        return currentPosition >= textLength || isTimeUp;
    }

    virtual float getWPM() {
        if (!isTyping || !isStarted) return 0;
        float timeInMinutes = (GetTime() - startTime) / 60.0f;
        return (currentPosition / 5.0f) / timeInMinutes;
    }

    virtual float getCPM() {
        if (!isTyping || !isStarted) return 0;
        float timeInMinutes = (GetTime() - startTime) / 60.0f;
        return currentPosition / timeInMinutes;
    }

    virtual float getAccuracy() {
        if (currentPosition + mistakes == 0) return 100;
        return ((float)currentPosition / (currentPosition + mistakes)) * 100;
    }

    virtual void selectRandomParagraph() {
        currentParagraph = rand() % 10;
        text = paragraphs[currentParagraph];
        textLength = strlen(text);
        currentPosition = 0;
        mistakes = 0;
        isTyping = false;
        isTimeUp = false;
        isStarted = false;
    }

    virtual void updateTimer() {
        if (isTyping && !isTimeUp && isStarted) {
            float elapsedTime = GetTime() - startTime;
            if (elapsedTime >= 30.0f) {
                isTimeUp = true;
            }
        }
    }

    virtual float getRemainingTime() {
        if (!isTyping || !isStarted) return 30.0f;
        float elapsedTime = GetTime() - startTime;
        return (30.0f - elapsedTime) > 0 ? (30.0f - elapsedTime) : 0;
    }

    virtual void startGame() {
        isStarted = true;
        startTyping();
    }
};

// Easy mode class
class EasyMode : public TextMode {
public:
    EasyMode() {
        paragraphs[0] = "The quick brown fox jumps over the lazy dog. This is a simple test for typing speed.";
        paragraphs[1] = "Learning to type quickly and accurately is an important skill in today's digital world.";
        paragraphs[2] = "The sun rises in the east and sets in the west. This is a basic fact about our planet.";
        paragraphs[3] = "Practice makes perfect. The more you type, the better you will become at it.";
        paragraphs[4] = "A good typing speed can help you work more efficiently and save time.";
        paragraphs[5] = "The keyboard is your tool. Learn to use it well and you will be more productive.";
        paragraphs[6] = "Typing is a skill that everyone should learn. It is useful in many jobs.";
        paragraphs[7] = "The computer is a powerful tool. Learning to type helps you use it better.";
        paragraphs[8] = "Speed and accuracy are both important when typing. Practice both skills.";
        paragraphs[9] = "The internet has changed how we work. Good typing skills are essential.";
        selectRandomParagraph();
    }
};

// Medium mode class
class MediumMode : public TextMode {
public:
    MediumMode() {
        paragraphs[0] = "Programming is the process of creating a set of instructions that tell a computer how to perform a task. Programming can be done using a variety of computer programming languages.";
        paragraphs[1] = "Computer science is the study of computers and computational systems. It involves both theoretical and practical aspects of computing.";
        paragraphs[2] = "Algorithms are step-by-step procedures for solving problems. They are fundamental to computer programming and data processing.";
        paragraphs[3] = "Data structures are ways of organizing and storing data in a computer. They help in efficient data access and modification.";
        paragraphs[4] = "Software development is the process of creating computer programs. It involves writing code, testing, and debugging.";
        paragraphs[5] = "The internet is a global network of computers. It allows people to share information and communicate across the world.";
        paragraphs[6] = "Artificial intelligence is the simulation of human intelligence by machines. It includes learning, reasoning, and self-correction.";
        paragraphs[7] = "Cybersecurity is the practice of protecting systems and networks from digital attacks. It is crucial in today's connected world.";
        paragraphs[8] = "Cloud computing allows users to access computing resources over the internet. It provides flexibility and scalability.";
        paragraphs[9] = "Mobile applications have become essential in our daily lives. They help us communicate, work, and entertain ourselves.";
        selectRandomParagraph();
    }
};

// Hard mode class
class HardMode : public TextMode {
public:
    HardMode() {
        paragraphs[0] = "Object-oriented programming (OOP) is a programming paradigm based on the concept of objects, which can contain data and code: data in the form of fields, and code in the form of procedures. A feature of objects is that an object's own procedures can access and often modify the data fields of itself.";
        paragraphs[1] = "Machine learning is a subset of artificial intelligence that focuses on building systems that can learn from and make decisions based on data. It involves the development of algorithms that can identify patterns and make predictions without being explicitly programmed.";
        paragraphs[2] = "Quantum computing is a type of computing that uses quantum-mechanical phenomena, such as superposition and entanglement, to perform operations on data. It has the potential to solve certain problems much faster than classical computers.";
        paragraphs[3] = "Blockchain technology is a decentralized, distributed ledger that records the provenance of a digital asset. It is most notable for its role in cryptocurrency systems, such as Bitcoin, for maintaining a secure and decentralized record of transactions.";
        paragraphs[4] = "Neural networks are computing systems inspired by the biological neural networks that constitute animal brains. They are used in machine learning to recognize patterns and make decisions based on input data.";
        paragraphs[5] = "The Internet of Things (IoT) refers to the network of physical objects that are embedded with sensors, software, and other technologies for the purpose of connecting and exchanging data with other devices and systems over the internet.";
        paragraphs[6] = "Virtual reality (VR) is a simulated experience that can be similar to or completely different from the real world. It uses computer technology to create a simulated environment that can be explored and interacted with by a person.";
        paragraphs[7] = "Augmented reality (AR) is an interactive experience of a real-world environment where the objects that reside in the real world are enhanced by computer-generated perceptual information.";
        paragraphs[8] = "Big data refers to extremely large data sets that may be analyzed computationally to reveal patterns, trends, and associations, especially relating to human behavior and interactions.";
        paragraphs[9] = "Cybersecurity frameworks provide a structured approach to managing cybersecurity risk. They help organizations identify, protect, detect, respond to, and recover from cyber threats.";
        selectRandomParagraph();
    }
};

// Typing tracker class
class TypingTracker {
private:
    TextMode* currentMode;
    int selectedMode;
    int screenWidth;
    int screenHeight;
    float scaleFactor;
    int fontSize;
    int lineHeight;
    int margin;

public:
    TypingTracker() : selectedMode(0), screenWidth(800), screenHeight(600), 
                     scaleFactor(1.0f), fontSize(20), lineHeight(30), margin(20) {
        srand(time(NULL));
        currentMode = new EasyMode();
    }

    ~TypingTracker() {
        delete currentMode;
    }

    void updateScreenSize(int width, int height) {
        screenWidth = width;
        screenHeight = height;
        scaleFactor = (float)screenWidth / 800.0f;
    }

    void switchMode(int mode) {
        delete currentMode;
        selectedMode = mode;
        switch (mode) {
            case 0: currentMode = new EasyMode(); break;
            case 1: currentMode = new MediumMode(); break;
            case 2: currentMode = new HardMode(); break;
        }
    }

    void drawWrappedText(const char* text, int pos, int x, int y, int maxWidth, int fontSize, Color color) {
        const char* currentText = text;
        int currentY = y;
        int lineSpacing = fontSize + 5;
        int currentX = x;
        int wordSpacing = MeasureText(" ", fontSize);

        while (*currentText) {
            // Find the next word
            const char* nextSpace = strchr(currentText, ' ');
            if (!nextSpace) nextSpace = currentText + strlen(currentText);

            // Calculate the width of the current line plus the next word
            int currentWidth = MeasureText(TextSubtext(currentText, 0, nextSpace - currentText), fontSize);

            // If adding the next word would exceed the max width, start a new line
            if (currentX + currentWidth > x + maxWidth) {
                currentY += lineSpacing;
                currentX = x;
            }

            // Draw the current word
            DrawText(TextSubtext(currentText, 0, nextSpace - currentText), currentX, currentY, fontSize, color);
            currentX += currentWidth + wordSpacing;

            // Move to the next word
            currentText = nextSpace;
            if (*currentText == ' ') currentText++;
        }
    }

    void draw() {
        // Calculate scaled positions
        int scaledMargin = (int)(margin * scaleFactor);
        int buttonWidth = (int)(200 * scaleFactor);
        int buttonHeight = (int)(50 * scaleFactor);
        int buttonSpacing = (int)(50 * scaleFactor);
        int startButtonWidth = (int)(100 * scaleFactor);
        int startButtonHeight = (int)(40 * scaleFactor);
        int scaledFontSize = (int)(fontSize * scaleFactor);
        int scaledLineHeight = (int)(lineHeight * scaleFactor);

        // Draw mode selection buttons
        int buttonY = scaledMargin;
        DrawRectangle(scaledMargin, buttonY, buttonWidth, buttonHeight, LIGHTGRAY);
        DrawRectangle(scaledMargin + buttonWidth + buttonSpacing, buttonY, buttonWidth, buttonHeight, LIGHTGRAY);
        DrawRectangle(scaledMargin + 2 * (buttonWidth + buttonSpacing), buttonY, buttonWidth, buttonHeight, LIGHTGRAY);

        DrawText("Easy", scaledMargin + 70, buttonY + 15, scaledFontSize, selectedMode == 0 ? RED : BLACK);
        DrawText("Medium", scaledMargin + buttonWidth + buttonSpacing + 70, buttonY + 15, scaledFontSize, selectedMode == 1 ? RED : BLACK);
        DrawText("Hard", scaledMargin + 2 * (buttonWidth + buttonSpacing) + 70, buttonY + 15, scaledFontSize, selectedMode == 2 ? RED : BLACK);

        // Draw start button and word wrap toggle
        int startButtonY = buttonY + buttonHeight + scaledMargin;
        DrawRectangle(scaledMargin, startButtonY, startButtonWidth, startButtonHeight, LIGHTGRAY);
        DrawText("Start", scaledMargin + 20, startButtonY + 10, scaledFontSize, BLACK);

        DrawRectangle(scaledMargin + startButtonWidth + scaledMargin, startButtonY, startButtonWidth, startButtonHeight, LIGHTGRAY);
        DrawText(currentMode->getWordWrap() ? "Wrap: ON" : "Wrap: OFF", 
                scaledMargin + startButtonWidth + scaledMargin + 10, startButtonY + 10, scaledFontSize, BLACK);

        // Draw timer
        char timerText[20];
        sprintf(timerText, "Time: %.1f", currentMode->getRemainingTime());
        DrawText(timerText, scaledMargin, startButtonY + startButtonHeight + scaledMargin, 
                scaledFontSize, currentMode->getRemainingTime() < 5.0f ? RED : BLACK);

        // Draw the text to type
        const char* text = currentMode->getText();
        int pos = currentMode->getCurrentPosition();
        int textY = startButtonY + startButtonHeight + 2 * scaledMargin + scaledLineHeight;
        int maxWidth = screenWidth - 2 * scaledMargin;

        if (currentMode->getWordWrap()) {
            // Draw typed text in green with word wrap
            drawWrappedText(TextSubtext(text, 0, pos), pos, scaledMargin, textY, maxWidth, scaledFontSize, GREEN);
            // Draw untyped text in black with word wrap
            drawWrappedText(TextSubtext(text, pos, strlen(text) - pos), 0, scaledMargin, textY, maxWidth, scaledFontSize, BLACK);
        } else {
            // Draw without word wrap
            DrawText(TextSubtext(text, 0, pos), scaledMargin, textY, scaledFontSize, GREEN);
            DrawText(TextSubtext(text, pos, strlen(text) - pos), 
                    scaledMargin + MeasureText(TextSubtext(text, 0, pos), scaledFontSize), 
                    textY, scaledFontSize, BLACK);
        }

        // Draw statistics
        if (currentMode->getIsTyping() && currentMode->getIsStarted()) {
            char wpmText[50];
            char cpmText[50];
            char accuracyText[50];
            char mistakesText[50];

            sprintf(wpmText, "WPM: %.1f", currentMode->getWPM());
            sprintf(cpmText, "CPM: %.1f", currentMode->getCPM());
            sprintf(accuracyText, "Accuracy: %.1f%%", currentMode->getAccuracy());
            sprintf(mistakesText, "Mistakes: %d", currentMode->getMistakes());

            int statsY = textY + 3 * scaledLineHeight;
            DrawText(wpmText, scaledMargin, statsY, scaledFontSize, BLACK);
            DrawText(cpmText, scaledMargin, statsY + scaledLineHeight, scaledFontSize, BLACK);
            DrawText(accuracyText, scaledMargin, statsY + 2 * scaledLineHeight, scaledFontSize, BLACK);
            DrawText(mistakesText, scaledMargin, statsY + 3 * scaledLineHeight, scaledFontSize, BLACK);
        }

        // Draw completion message
        if (currentMode->isComplete() && currentMode->getIsStarted()) {
            const char* message = currentMode->getIsTimeUp() ? 
                "Time's up! Press R to try again" : 
                "Completed! Press R to try again";
            DrawText(message, scaledMargin, textY + 6 * scaledLineHeight, scaledFontSize, RED);
        }
    }

    void handleInput() {
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            Vector2 mousePos = GetMousePosition();
            
            // Calculate scaled dimensions
            int scaledMargin = (int)(margin * scaleFactor);
            int buttonWidth = (int)(200 * scaleFactor);
            int buttonHeight = (int)(50 * scaleFactor);
            int buttonSpacing = (int)(50 * scaleFactor);
            int startButtonWidth = (int)(100 * scaleFactor);
            int startButtonHeight = (int)(40 * scaleFactor);
            int buttonY = scaledMargin;
            int startButtonY = buttonY + buttonHeight + scaledMargin;

            // Check mode selection buttons
            if (mousePos.x >= scaledMargin && mousePos.x <= scaledMargin + buttonWidth && 
                mousePos.y >= scaledMargin && mousePos.y <= scaledMargin + buttonHeight) {
                switchMode(0);
            } else if (mousePos.x >= scaledMargin + buttonWidth + buttonSpacing && 
                       mousePos.x <= scaledMargin + 2 * buttonWidth + buttonSpacing && 
                       mousePos.y >= scaledMargin && mousePos.y <= scaledMargin + buttonHeight) {
                switchMode(1);
            } else if (mousePos.x >= scaledMargin + 2 * (buttonWidth + buttonSpacing) && 
                       mousePos.x <= scaledMargin + 3 * buttonWidth + 2 * buttonSpacing && 
                       mousePos.y >= scaledMargin && mousePos.y <= scaledMargin + buttonHeight) {
                switchMode(2);
            }
            // Check start button
            else if (mousePos.x >= scaledMargin && mousePos.x <= scaledMargin + startButtonWidth && 
                     mousePos.y >= startButtonY && mousePos.y <= startButtonY + startButtonHeight) {
                currentMode->startGame();
            }
            // Check word wrap toggle
            else if (mousePos.x >= scaledMargin + startButtonWidth + scaledMargin && 
                     mousePos.x <= scaledMargin + 2 * startButtonWidth + scaledMargin && 
                     mousePos.y >= startButtonY && mousePos.y <= startButtonY + startButtonHeight) {
                currentMode->toggleWordWrap();
            }
        }

        // Restart on R key press
        if (IsKeyPressed(KEY_R)) {
            currentMode->selectRandomParagraph();
        }
    }

    void update() {
        currentMode->updateTimer();
        
        if (!currentMode->getIsTyping() && currentMode->getIsStarted()) {
            currentMode->startTyping();
        }

        int key = GetCharPressed();
        if (key != 0) {
            currentMode->checkInput(key);
        }
    }
};

int main() {
    const int initialWidth = 1000;
    const int initialHeight = 700;

    InitWindow(initialWidth, initialHeight, "Typing Speed Tracker");
    SetTargetFPS(60);
    SetWindowState(FLAG_WINDOW_RESIZABLE);

    TypingTracker tracker;

    while (!WindowShouldClose()) {
        if (IsWindowResized()) {
            tracker.updateScreenSize(GetScreenWidth(), GetScreenHeight());
        }

        tracker.handleInput();
        tracker.update();

        BeginDrawing();
        ClearBackground(RAYWHITE);
        tracker.draw();
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
