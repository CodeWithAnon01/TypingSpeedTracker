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
    float finalWPM;
    float finalCPM;
    float finalAccuracy;
    bool isCompleted;
    float completionTime;

public:
    TextMode() : currentPosition(0), mistakes(0), startTime(0), isTyping(false), 
                isTimeUp(false), isStarted(false), currentParagraph(0),
                finalWPM(0), finalCPM(0), finalAccuracy(0), isCompleted(false),
                completionTime(0) {
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
    virtual bool getIsCompleted() { return isCompleted; }
    virtual float getCompletionTime() { return completionTime; }

    virtual void startTyping() {
        if (!isTyping && isStarted) {
            isTyping = true;
            startTime = GetTime();
            isTimeUp = false;
            isCompleted = false;
            completionTime = 0;
        }
    }

    virtual void checkInput(int key) {
        if (!isTyping || isTimeUp || !isStarted || isCompleted) return;

        if (key == text[currentPosition]) {
            currentPosition++;
            if (currentPosition >= textLength) {
                isCompleted = true;
                completionTime = GetTime() - startTime;
                calculateFinalStats();
            }
        } else {
            mistakes++;
        }
    }

    virtual void calculateFinalStats() {
        float timeInMinutes = completionTime / 60.0f;
        finalWPM = (currentPosition / 5.0f) / timeInMinutes;
        finalCPM = currentPosition / timeInMinutes;
        finalAccuracy = ((float)currentPosition / (currentPosition + mistakes)) * 100;
    }

    virtual bool isComplete() {
        return isCompleted || isTimeUp;
    }

    virtual float getWPM() {
        if (!isTyping || !isStarted) return 0;
        if (isCompleted || isTimeUp) return finalWPM;
        float timeInMinutes = (GetTime() - startTime) / 60.0f;
        return (currentPosition / 5.0f) / timeInMinutes;
    }

    virtual float getCPM() {
        if (!isTyping || !isStarted) return 0;
        if (isCompleted || isTimeUp) return finalCPM;
        float timeInMinutes = (GetTime() - startTime) / 60.0f;
        return currentPosition / timeInMinutes;
    }

    virtual float getAccuracy() {
        if (currentPosition + mistakes == 0) return 100;
        if (isCompleted || isTimeUp) return finalAccuracy;
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
        isCompleted = false;
        finalWPM = 0;
        finalCPM = 0;
        finalAccuracy = 0;
        completionTime = 0;
    }

    virtual void updateTimer() {
        if (isTyping && !isTimeUp && isStarted && !isCompleted) {
            float elapsedTime = GetTime() - startTime;
            if (elapsedTime >= 30.0f) {
                isTimeUp = true;
                completionTime = 30.0f;
                calculateFinalStats();
            }
        }
    }

    virtual float getRemainingTime() {
        if (!isTyping || !isStarted || isCompleted) return 30.0f;
        if (isTimeUp) return 0;
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
        paragraphs[0] = "The quick brown fox jumps over the lazy dog. This is a simple test for typing speed. Learning to type quickly and accurately is an important skill. The sun rises in the east and sets in the west. Practice makes perfect in everything we do.";
        paragraphs[1] = "A good typing speed helps you work more efficiently. The keyboard is your tool for digital communication. Typing is a skill that everyone should learn. Computers are powerful tools in our daily lives. Speed and accuracy are both important when typing.";
        paragraphs[2] = "The internet has changed how we work and communicate. Good typing skills are essential for success. Computers are everywhere in our modern world. Being able to type well makes everything easier. Practice every day to improve your skills.";
        paragraphs[3] = "Typing is like playing a musical instrument. Start slow and focus on accuracy first. Use all your fingers when typing. Keep your eyes on the screen, not the keyboard. This will help you type faster with fewer mistakes.";
        paragraphs[4] = "The home row keys are the foundation of good typing. Your fingers should rest on ASDF and JKL. From there, you can reach all other keys. Practice typing without looking at the keyboard. This is called touch typing.";
        paragraphs[5] = "Regular practice is the key to improving your typing. Set aside time each day to practice. Use online typing tests to measure progress. Try to beat your previous scores. Remember that accuracy is more important than speed.";
        paragraphs[6] = "Good posture is important when typing for long periods. Sit up straight with your feet flat on the floor. Keep your wrists straight and fingers curved. Take breaks often to rest your hands. Comfort is important for good typing.";
        paragraphs[7] = "The QWERTY keyboard layout was designed long ago. It was made to prevent typewriter keys from jamming. Today, we still use this layout for computers. Some people use different layouts like Dvorak. But QWERTY is the most common.";
        paragraphs[8] = "Typing games can make practice fun and engaging. They help you learn while having fun. Many websites offer free typing games. Some track your progress over time. Playing these games can improve your skills.";
        paragraphs[9] = "In today's world, typing is a basic skill everyone needs. Many jobs require good typing skills. Schools teach typing to prepare students. The faster you can type, the more productive you can be. It's a skill that will help you throughout life.";
        selectRandomParagraph();
    }
};

// Medium mode class
class MediumMode : public TextMode {
public:
    MediumMode() {
        paragraphs[0] = "Programming creates computer instructions using various languages. Each language has unique syntax and rules. Understanding these rules is essential for coding. Practice helps develop programming skills. Good programmers write clean, efficient code.";
        paragraphs[1] = "Computer science studies computers and computational systems. It combines theory and practical applications. Computer scientists develop new technologies. The field evolves with new innovations. Understanding CS is vital for modern technology.";
        paragraphs[2] = "Algorithms are step-by-step problem-solving procedures. They are fundamental to programming. Good algorithms are efficient and correct. Understanding algorithms improves coding skills. Many problems use standard algorithms.";
        paragraphs[3] = "Data structures organize and store computer data. They enable efficient data access. Common structures include arrays and lists. Choosing the right structure is crucial. Understanding structures is key to programming.";
        paragraphs[4] = "Software development creates computer programs. It involves coding and testing. Good software is reliable and user-friendly. The process includes planning and maintenance. Teamwork is important in development.";
        paragraphs[5] = "The internet is a global network of computers. It enables information sharing worldwide. The web contains websites and pages. Understanding the internet is crucial. Security is vital for internet usage.";
        paragraphs[6] = "Artificial intelligence simulates human intelligence. It includes learning and reasoning. AI systems perform complex tasks. Machine learning is an AI subset. AI is important in modern technology.";
        paragraphs[7] = "Cybersecurity protects systems from digital attacks. It's crucial in our connected world. Good security prevents data breaches. Understanding security is important. Strong passwords are essential.";
        paragraphs[8] = "Cloud computing provides resources over the internet. It offers flexibility and scalability. Users access data from anywhere. Cloud services are popular. Understanding cloud computing is important.";
        paragraphs[9] = "Mobile apps are essential in daily life. They help communication and work. Developing apps requires platform knowledge. Good apps are user-friendly. The app market continues growing.";
        selectRandomParagraph();
    }
};

// Hard mode class
class HardMode : public TextMode {
public:
    HardMode() {
        paragraphs[0] = "OOP utilizes encapsulation, inheritance, and polymorphism. Classes define object types and behaviors. Inheritance creates hierarchical relationships. Polymorphism enables flexible object handling. Abstraction hides complex details.";
        paragraphs[1] = "Machine learning processes vast datasets, identifying patterns. Deep learning excels at image recognition. NLP analyzes linguistic structures. Reinforcement learning optimizes decisions. These technologies revolutionize automation.";
        paragraphs[2] = "Quantum computing uses superposition and entanglement. Qubits exist in multiple states. Quantum algorithms solve problems faster. Decoherence challenges quantum states. Error correction mitigates quantum noise.";
        paragraphs[3] = "Blockchain uses cryptographic hashing and signatures. Smart contracts execute automatically. Consensus mechanisms validate transactions. Distributed ledgers maintain records. Cryptocurrencies use blockchain securely.";
        paragraphs[4] = "Neural networks process through artificial neurons. Backpropagation adjusts connection weights. Activation functions add non-linearity. Convolutional layers extract features. Recurrent networks handle sequences.";
        paragraphs[5] = "IoT integrates sensors and protocols. Edge computing reduces latency. Security needs encryption. Standards ensure device communication. Predictive maintenance uses IoT data.";
        paragraphs[6] = "VR uses displays and motion tracking. Haptic feedback enhances interaction. Spatial audio simulates sound. Latency reduction prevents sickness. VR spans training and entertainment.";
        paragraphs[7] = "AR overlays digital information. Tracking systems enable interactions. Vision algorithms detect objects. Displays project virtual content. AR aids navigation and education.";
        paragraphs[8] = "Big data processes high-velocity datasets. MapReduce parallelizes processing. NoSQL handles unstructured data. Mining extracts insights. Privacy techniques protect information.";
        paragraphs[9] = "Cybersecurity uses defense-in-depth strategies. IDS monitors network traffic. Cryptography secures communication. Zero-trust verifies access. Response plans handle breaches.";
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
    int textAreaWidth;
    int textAreaHeight;
    int textY;
    int maxVisibleLines;
    int currentScroll;
    int visibleLines;

public:
    TypingTracker() : selectedMode(0), screenWidth(800), screenHeight(600), 
                     scaleFactor(1.0f), fontSize(20), lineHeight(30), margin(20),
                     textAreaWidth(0), textAreaHeight(0), textY(0), maxVisibleLines(0),
                     currentScroll(0), visibleLines(0) {
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
        
        // Calculate text area dimensions
        int scaledMargin = (int)(margin * scaleFactor);
        int buttonHeight = (int)(50 * scaleFactor);
        int startButtonHeight = (int)(40 * scaleFactor);
        int statsHeight = (int)(120 * scaleFactor);
        int scaledLineHeight = (int)(lineHeight * scaleFactor);
        
        // Calculate heights of different sections
        int topSectionHeight = scaledMargin + buttonHeight + scaledMargin + startButtonHeight + scaledMargin;
        int bottomSectionHeight = statsHeight + scaledMargin;
        int availableHeight = screenHeight - (topSectionHeight + bottomSectionHeight);
        
        // Calculate text area
        textAreaWidth = screenWidth - (2 * scaledMargin);
        textAreaHeight = availableHeight;
        
        // Calculate text starting position
        textY = topSectionHeight + (availableHeight / 4); // Position text in the middle of available space
        
        // Calculate maximum visible lines
        maxVisibleLines = textAreaHeight / scaledLineHeight;
        visibleLines = maxVisibleLines;
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

        // Draw start button
        int startButtonY = buttonY + buttonHeight + scaledMargin;
        DrawRectangle(scaledMargin, startButtonY, startButtonWidth, startButtonHeight, LIGHTGRAY);
        DrawText("Start", scaledMargin + 20, startButtonY + 10, scaledFontSize, BLACK);

        // Draw timer
        char timerText[20];
        sprintf(timerText, "Time: %.1f", currentMode->getRemainingTime());
        DrawText(timerText, scaledMargin, startButtonY + startButtonHeight + scaledMargin, 
                scaledFontSize, currentMode->getRemainingTime() < 5.0f ? RED : BLACK);

        // Draw the text to type with wrapping
        const char* text = currentMode->getText();
        int pos = currentMode->getCurrentPosition();
        int currentLine = 0;
        int currentX = scaledMargin;
        int currentY = textY;
        int wordStart = 0;
        int wordEnd = 0;
        bool inWord = false;

        // Draw text in a single pass
        for (int i = 0; i <= strlen(text); i++) {
            if (text[i] == ' ' || text[i] == '\0') {
                if (inWord) {
                    wordEnd = i;
                    const char* word = TextSubtext(text, wordStart, wordEnd - wordStart);
                    int wordWidth = MeasureText(word, scaledFontSize);
                    
                    if (currentX + wordWidth > screenWidth - scaledMargin) {
                        currentX = scaledMargin;
                        currentY += scaledLineHeight;
                        currentLine++;
                    }

                    // Determine color based on position
                    Color wordColor;
                    if (wordEnd <= pos) {
                        wordColor = GREEN;  // Already typed
                    } else if (wordStart <= pos && pos < wordEnd) {
                        wordColor = BLUE;   // Current word
                    } else {
                        wordColor = GRAY;   // Upcoming text
                    }
                    
                    DrawText(word, currentX, currentY, scaledFontSize, wordColor);
                    currentX += wordWidth + MeasureText(" ", scaledFontSize);
                    inWord = false;
                }
            } else if (!inWord) {
                wordStart = i;
                inWord = true;
            }
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

            int statsY = screenHeight - (int)(120 * scaleFactor);
            DrawText(wpmText, scaledMargin, statsY, scaledFontSize, BLACK);
            DrawText(cpmText, scaledMargin, statsY + scaledLineHeight, scaledFontSize, BLACK);
            DrawText(accuracyText, scaledMargin, statsY + 2 * scaledLineHeight, scaledFontSize, BLACK);
            DrawText(mistakesText, scaledMargin, statsY + 3 * scaledLineHeight, scaledFontSize, BLACK);
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
        }
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
