#pragma once

#include "CoreMinimal.h"

#include "MatrixArray.h"

class SMainWindow;

/**
 * Game controller component. Receives AI-generated game field, builds and controls game loop.
 */
class FGameController
{
public:
    // Methods
    // HTTP request result
    void httpResult(bool result, const FString &message);
    // Set UI component
    void setUIComponent(TSharedPtr<SMainWindow> uiComponent);
    // UI element clicked
    void uiElementClicked(int32 x, int32 y);

protected:
    // Types
    // Game field cell type
    enum EGameCell
    {
        // Default - cell is covered
        HIDDEN,
        // Empty open cell
        OPEN,
        // Cell with mine, covered
        MINE,
        // Found mine
        MINE_OPEN,
    };

    // Constants
    // Empty cell symbol
    static const TCHAR CELL_SYMBOL_EMPTY;
    // Mine cell symbol
    static const TCHAR CELL_SYMBOL_MINE;

    // Fields
    // UI component pointer
    TSharedPtr<SMainWindow> m_uiComponent;
    // Game field matrix
    FMatrixArray<EGameCell> m_gameGrid;
    // Game over flag
    bool m_gameOver {false};

    // Methods
    // Split received HTTP message into strings and validate it. Return array of lines, empty if message was incorrect.
    TArray<FString> getLinesFromMessage(const FString &message);
    // Count mines around cell
    int32 getNeighborMinesNumber(int32 x, int32 y);
    // Check cell for recursive processing. Return true if it is HIDDEN.
    bool checkCell(int32 x, int32 y);
    // Recursive empty cell process
    void processCell(int32 x, int32 y);
};
