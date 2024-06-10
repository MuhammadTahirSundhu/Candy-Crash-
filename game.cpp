#ifndef CENTIPEDE_CPP_
#define CENTIPEDE_CPP_
#include "util.h"
#include <iostream>
#include <string>
#include <cmath>
#include <time.h>
#include <ostream>
#include <fstream>

using namespace std;

///////////////////////
int elapsedTimeSeconds = 0;
bool hintsEnabled = false;   // Tracks whether hints are currently shown
bool hintsPenalized = false; // Tracks whether the penalty for hints has been applied

int hintGrid[row][col];

enum GameState
{
    MENU,
    PLAYING,
    INSTRUCTIONS,
    HIGHSCORES,
    EXIT
};

GameState currentState = MENU;

void DrawMenu()
{
    DrawString(425, 600, "MENU", colors[DARK_RED]);
    const char *menuItems[] = {"Play", "High Scores", "Instructions", "Exit"};
    int numItems = sizeof(menuItems) / sizeof(menuItems[0]);
    int menuY = 410;      // Starting Y position of the first menu item
    int menuX = 410;      // X position where menu items start
    int menuHeight = 50;  // Height of each menu item
    int menuSpacing = 10; // Space between menu items
    for (int i = 0; i < numItems; i++)
    {
        int itemY = menuY - i * (menuHeight + menuSpacing);
        DrawString(menuX, itemY, menuItems[i], colors[MISTY_ROSE]);
    }
}

void DrawInstructions()
{
    const char *instructions[] = {
        "1-Use arrow keys or mouse to move the gems.",
        "2-Match 3 or more gems horizontally or vertically to score.",
        "3-Press 'p' to pause and 'r' to resume the game.",
        "4-Press 'h' for hints.",
    };
    int numLines = sizeof(instructions) / sizeof(instructions[0]);
    int instrY = 400;
    DrawString(350, 500, "INSTRUCTIONS", colors[DARK_RED]);
    for (int i = 0; i < numLines; i++)
    {
        DrawString(200, instrY - i * 50, instructions[i], colors[MISTY_ROSE]);
    }
    DrawString(560, 20, "Press Backspace to go back", colors[DARK_RED]);
}

void DrawHighscores()
{
    DrawString(350, 600, "HIGHSCORES", colors[DARK_RED]);
    DrawString(560, 20, "Press Backspace to go back", colors[DARK_RED]);
}

void ToggleHints(int Level1[][21], int row, int col)
{
    hintsEnabled = !hintsEnabled; // Toggle hint visibility

    if (hintsEnabled && !hintsPenalized)
    {
        // Apply penalty only once per hint toggle
        score -= 10;         // Penalize the score for using a hint
        eachLevelScore -= 5; // Decrease progress
        if (eachLevelScore < 20)
            eachLevelScore = 20;
        if (score < 0)
            score = 0;
        hintsPenalized = true;
    }
    else if (!hintsEnabled)
    {
        hintsPenalized = false; // Reset penalty application for the next toggle
    }
}

void buildGrid()
{
    for (int i = 0; i < row; i += 1)
        for (int j = 0; j < col; j += 1)
        {
            if (i % 2 != 0)
                Level1[i][j] = 0;
            else
            {
                if (j % 2 == 0)
                    Level1[i][j] = rand() % 6 + 1;
                else
                    Level1[i][j] = 0;
            }
        }
    for (int i = 0; i < row; i += 1)
    {
        for (int j = 0; j < col; j += 1)
        {
            cout << Level1[i][j];
        }
        cout << endl;
    }
}

int ConvertWindowCoordToOpenGL(int y, int windowHeight)
{
    return windowHeight - y;
}

bool IsWithinGrid(int x, int y)
{
    return (x >= boundaryLeftX && x <= boundaryRightX && y >= boundaryBottomY && y <= boundaryTopY);
}

void ApplyGravity()
{
    for (int j = 0; j < col; j++)
    {                          // Iterate through each column
        int lastEmptyRow = -2; // Track the last empty row from the top
        for (int i = 0; i < row; i += 2)
        { // Start from the top of the column
            if (Level1[i][j] == 9)
            {
                // Found an empty space
                if (lastEmptyRow == -2)
                {
                    lastEmptyRow = i; // Mark this row if it's the first empty row found
                }
            }
            else if (lastEmptyRow != -2)
            {
                // There is a gem below an empty space
                Level1[lastEmptyRow][j] = Level1[i][j]; // Move the gem up to the last empty row
                Level1[i][j] = 9;                       // Set the current position to empty
                lastEmptyRow += 2;                      // Update the last empty row to be one row below
            }
        }
    }
}

void SwapGems(int r1, int c1, int r2, int c2)
{
    int temp = Level1[r1][c1];
    Level1[r1][c1] = Level1[r2][c2];
    Level1[r2][c2] = temp;
}

bool IsValidMove(int r1, int c1, int r2, int c2)
{
    if (abs(r1 - r2) + abs(c1 - c2) != 2) // Ensure that the gems are adjacent
    {
        cout << "Gems are not adjacent\n";
        return false;
    }
    if (Level1[abs(r1)][abs(c1)] == 0 || Level1[abs(r2)][abs(c2)] == 0)
    {
        cout << "This is Gap\n";
        return false;
    }

    SwapGems(r1, c1, r2, c2); // Swap to check for validity
    cout << "1\n";
    bool valid = false;

    // Functions to count similar gems horizontally and vertically
    auto countGems = [&](int r, int c) -> pair<int, int>
    {
        int horizontal = 1, vertical = 1;
        int gemType = Level1[r][c];

        for (int i = c - 2; i >= 0 && Level1[r][i] == gemType; i -= 2)
            horizontal++;
        for (int i = c + 2; i < col && Level1[r][i] == gemType; i += 2)
            horizontal++;

        for (int i = r - 2; i >= 0 && Level1[i][c] == gemType; i -= 2)
            vertical++;
        for (int i = r + 2; i < row && Level1[i][c] == gemType; i += 2)
            vertical++;

        if (horizontal >= 2)
        {
            for (int i = c - 2; i >= 0 && Level1[r][i] == gemType; i -= 2)
                Level1[r][i] = 9;
            for (int i = c + 2; i < col && Level1[r][i] == gemType; i += 2)
                Level1[r][i] = 9;
        }
        if (vertical >= 2)
        {
            for (int i = r - 2; i >= 0 && Level1[i][c] == gemType; i -= 2)
                Level1[i][c] = 9;
            for (int i = r + 2; i < row && Level1[i][c] == gemType; i += 2)
                Level1[i][c] = 9;
        }

        return {horizontal, vertical};
    };

    // Check if there are at least three gems in a row or column around the swapped locations
    auto [h1, v1] = countGems(r1, c1);
    auto [h2, v2] = countGems(r2, c2);

    if (h1 >= 2)
    {
        Level1[r1][c1] = 9;
        valid = true;
        cout << "Horizontal->Match\n";
        score += (scorePoint + 50 * (levelNo - 1));
        eachLevelScore += 10;
    }
    if (h2 >= 2)
    {
        Level1[r2][c2] = 9;
        valid = true;
        cout << "Horizontal->Match\n";
        score += (scorePoint + 50 * (levelNo - 1));
        eachLevelScore += 10;
    }
    if (v1 >= 2)
    {
        Level1[r1][c1] = 9;
        cout << "Vertical->Match\n";
        score += (scorePoint + 50 * (levelNo - 1));
        eachLevelScore += 10;
        valid = true;
    }
    if (v2 >= 2)
    {
        Level1[r2][c2] = 9;
        cout << "Vertical->Match\n";
        score += (scorePoint + 50 * (levelNo - 1));
        eachLevelScore += 10;
        valid = true;
    }
    cout << "3 ->" << valid << endl;
    SwapGems(r1, c1, r2, c2); // Swap back if invalid

    return valid;
}
bool canFormMatch()
{
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            hintGrid[i][j] = 0;
        }
        cout << endl;
    }
    for (int i = 0; i < row; i += 2)
    {
        for (int j = 0; j < col; j += 2)
        {
            // Check horizontally
            if (Level1[i][j] == Level1[i][j + 2])
            {
                hintGrid[i][j] = Level1[i][j];
                hintGrid[i][j + 2] = Level1[i][j];
            }

            // Check vertically
            if (Level1[i][j] == Level1[i + 2][j])
            {
                hintGrid[i][j] = Level1[i][j];
                hintGrid[i + 2][j] = Level1[i][j];
            }
        }
    }

    // Output the hint grid for debugging
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            cout << hintGrid[i][j];
        }
        cout << endl;
    }
}

void LoadGrid()
{
    int xOffset = 100; // Horizontal offset from the window edge to the start of the grid
    int yOffset = 50;  // Vertical offset from the window edge to the start of the grid

    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            int posX = xOffset + j * (cellSize);
            int posY = yOffset + i * (cellSize);
            int centerAdjust = cellSize / 2;

            if (hintsEnabled)
            {
                canFormMatch();
                // Draw only potential matches when hints are enabled
                switch (hintGrid[i][j])
                {
                case 1:
                    DrawCircle(posX + centerAdjust, posY + centerAdjust, cellSize / 2, colors[RED]);
                    break;
                case 2:
                    DrawTriangle(posX, posY, posX + cellSize, posY, posX + (cellSize / 2), posY + cellSize, colors[MISTY_ROSE]);
                    break;
                case 3:
                    DrawSquare(posX, posY, cellSize, colors[GREEN]);
                    break;
                case 4:
                    DrawCircle(posX + centerAdjust, posY + centerAdjust, cellSize / 2, colors[DARK_GOLDEN_ROD]);
                    break;
                case 5:
                    DrawSquare(posX, posY, cellSize, colors[DARK_MAGENTA]);
                    break;
                case 6:
                    DrawTriangle(posX, posY, posX + cellSize, posY, posX + (cellSize / 2), posY + cellSize, colors[DARK_ORANGE]);
                    break;
                }
            }
            else if (!hintsEnabled)
            {
                // Draw all shapes when hints are not enabled
                switch (Level1[i][j])
                {
                case 1:
                    DrawCircle(posX + centerAdjust, posY + centerAdjust, cellSize / 2, colors[RED]);
                    break;
                case 2:
                    DrawTriangle(posX, posY, posX + cellSize, posY, posX + (cellSize / 2), posY + cellSize, colors[MISTY_ROSE]);
                    break;
                case 3:
                    DrawSquare(posX, posY, cellSize, colors[GREEN]);
                    break;
                case 4:
                    DrawCircle(posX + centerAdjust, posY + centerAdjust, cellSize / 2, colors[DARK_GOLDEN_ROD]);
                    break;
                case 5:
                    DrawSquare(posX, posY, cellSize, colors[DARK_MAGENTA]);
                    break;
                case 6:
                    DrawTriangle(posX, posY, posX + cellSize, posY, posX + (cellSize / 2), posY + cellSize, colors[DARK_ORANGE]);
                    break;
                default:
                    DrawSquare(posX, posY, cellSize, colors[BLACK]); // For gems that are not of type 1-6
                }
            }
        }
    }
}
void SetCanvasSize(int width, int height)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, width, 0, height, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}
void GameDisplay()
{
    glClearColor(0, 0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT);
    switch (currentState)
    {
    case MENU:
        DrawMenu();
        break;

    case HIGHSCORES:
        DrawHighscores();
        break;

    case EXIT:
        exit(0);
        break;

    case INSTRUCTIONS:
        DrawInstructions();

        break;
    case PLAYING:
        if (!gamePause)
        {
            if (eachLevelScore >= 200)
            {
                eachLevelScore = 20;
                gridflag = true;
            }
            if (gridflag)
            {
                gridflag = false;
                buildGrid();
                levelNo++;
                cout << "New Grid\n";
            }
            cout << eachLevelScore << endl;
            glClearColor(0, 0, 0, 0);
            glClear(GL_COLOR_BUFFER_BIT);
            DrawString(50, 800, "Score : ", colors[MISTY_ROSE]);
            DrawString(120, 800, to_string(score), colors[MISTY_ROSE]);
            DrawString(700, 800, "Level no : ", colors[MISTY_ROSE]);
            DrawString(800, 800, to_string(levelNo), colors[MISTY_ROSE]);
            LoadGrid();

            time_t currentTime = time(0);
            int minutes = elapsedTimeSeconds / 60;
            int seconds = elapsedTimeSeconds % 60;
            string timeString = "Time: " + to_string(minutes) + "m " + to_string(seconds) + "s";
            DrawString(380, 700, timeString, colors[WHITE]);

            DrawLine(boundaryLeftX, boundaryBottomY, boundaryRightX, boundaryBottomY, boundaryLineWidth, colors[RED]);
            DrawLine(boundaryRightX, boundaryBottomY, boundaryRightX, boundaryTopY, boundaryLineWidth, colors[RED]);
            DrawLine(boundaryRightX, boundaryTopY, boundaryLeftX, boundaryTopY, boundaryLineWidth, colors[RED]);
            DrawLine(boundaryLeftX, boundaryTopY, boundaryLeftX, boundaryBottomY, boundaryLineWidth, colors[RED]);

            DrawRoundRect(boundaryLeftX + 150, boundaryTopY + 50, boundaryRightX - boundaryLeftX - 300, 40, colors[LIGHT_CYAN], 20);
            float progressBarLength = (float)eachLevelScore / 200.0 * (boundaryRightX - boundaryLeftX - 300);
            DrawRoundRect(boundaryLeftX + 150, boundaryTopY + 50, progressBarLength, 40, colors[DARK_GOLDEN_ROD], 20);
        }
        else
            DrawString(425, 420, "PAUSED : ", colors[DARK_RED]);

        break;
    }

    glutSwapBuffers();
}

void NonPrintableKeys(int key, int x, int y)
{
    glutPostRedisplay();
}

void PrintableKeys(unsigned char key, int x, int y)
{
    if (key == 27)
    { // ESC key
        exit(1);
    }
    if (key == 'p' && currentState == PLAYING)
    {
        cout << "Game Paused\n";
        gamePause = true;
    }
    if (key == 'r' && currentState == PLAYING)
    {
        cout << "Game Paused\n";
        gamePause = false;
    }
    if (key == 8)
        currentState = MENU;
    if (key == 'h' && currentState == PLAYING)
    {
        ToggleHints(Level1, row, col);
        cout << "hint" << endl;
        glutPostRedisplay(); // Redraw to show or hide hints
    }
    if(key == 's')
    {
    cout<<"Ready for save command\n";
    
    }

    glutPostRedisplay();
}

void Timer(int m)
{
    elapsedTimeSeconds++;
    glutPostRedisplay();
    glutTimerFunc(1000.0, Timer, 0);
}

void MousePressedAndMoved(int x, int y)
{
    if (isDragging)
    {
        // Optional: update visual feedback of dragging
    }
    glutPostRedisplay();
}

void MouseClicked(int button, int state, int x, int y)
{
    cout << x << "    , " << y << endl;
    if (currentState == MENU && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        int menuY = 410;      // Starting position of the first menu item
        int menuHeight = 50;  // Height of each menu item
        int menuWidth = 200;  // Width of each menu item
        int menuX = 410;      // X position where menu items start
        int menuSpacing = 10; // Space between menu items

        // Check if the click is within the menu bounds
        if (x >= menuX && x <= menuX + menuWidth)
        {
            for (int i = 0; i < 4; i++)
            { // Assuming there are 4 menu items
                int itemY = menuY + i * (menuHeight + menuSpacing);
                // Check if the click is within the bounds of the current menu item
                if (y >= itemY && y <= itemY + menuHeight)
                {
                    switch (i)
                    {
                    case 0:
                        currentState = PLAYING; // Adjusted index for "Play" menu item
                        break;
                    case 1:
                        currentState = HIGHSCORES;
                        break;
                    case 2:
                        currentState = INSTRUCTIONS;
                        break;
                    case 3:
                        currentState = EXIT;
                        break;
                    }
                    break; // Exit the loop once the correct item is found
                }
            }
        }
    }
    else if (currentState == PLAYING && !gamePause && !hintsEnabled)
    {
        if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
        {
            int gridX = (x - 100) / cellSize;
            int gridY = (ConvertWindowCoordToOpenGL(y, 840) - 50) / cellSize;
            selectedRow = gridY;
            selectedCol = gridX;
            isDragging = true;
        }
        else if (button == GLUT_LEFT_BUTTON && state == GLUT_UP && isDragging)
        {
            int gridX = (x - 100) / cellSize;
            int gridY = (ConvertWindowCoordToOpenGL(y, 840) - 50) / cellSize;
            if (selectedRow != -1 && selectedCol != -1 && (gridX != selectedCol || gridY != selectedRow))
            {
                if (IsValidMove(selectedRow, selectedCol, gridY, gridX))
                {
                    SwapGems(selectedRow, selectedCol, gridY, gridX);
                    ApplyGravity();
                }
            }
            selectedRow = -1;
            selectedCol = -1;
            isDragging = false;
        }
    }
    glutPostRedisplay();
}

int main(int argc, char *argv[])
{
    srand(time(0));
    int width = 900, height = 840;
    string PlayerName = "";
    cout << "Enter your name: ";
    cin >> PlayerName;
    InitRandomizer();
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(50, 50);
    glutInitWindowSize(width, height);
    glutCreateWindow("OOP Project");
    glutTimerFunc(1000, Timer, 0); // Start the timer to update time every second
    SetCanvasSize(width, height);

    glutDisplayFunc(GameDisplay);
    glutSpecialFunc(NonPrintableKeys);
    glutKeyboardFunc(PrintableKeys);
    glutMouseFunc(MouseClicked);
    glutMotionFunc(MousePressedAndMoved);
    glutMainLoop();
    return 1;
}

#endif // CENTIPEDE_CPP_