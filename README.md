Minesweeper test task.
Contains classes: SMainWindow, FAIController, FGameController. Main plugin's class creates these objects and links them to each other.

SMainWindow
Creates plugin's UI. Receives input from user (AI request, game commands), sends it to other classes, receives and shows feedback.

FAIConnector
Implements connection to Google Gemini Rest API. Receives AI request, performs HTTP request, parses JSON result and sends it to other classes.

FGameController
Implements game loop. Receives game field from FAIController, creates and controls it in SMainWindow. New game may be started in any time by requesting new game field via FAIController.
