#include "GameController.h"
#include "SMainWindow.h"

const TCHAR FGameController::CELL_SYMBOL_EMPTY {'X'};
const TCHAR FGameController::CELL_SYMBOL_MINE {'O'};

void FGameController::httpResult(bool result, const FString &message)
{
    if (!result || !m_uiComponent)
        return;

    // Split message into strings
    TArray<FString> lines = getLinesFromMessage(message);
    if (lines.IsEmpty() || lines[0].IsEmpty())
        return;

    // Create new game grid
    m_gameGrid.setSize(lines[0].Len(), lines.Num(), HIDDEN);
    for (int32 iRow = 0; iRow < lines.Num(); iRow++)
        for (int32 iColumn = 0; iColumn < lines[0].Len(); iColumn++)
            if (lines[iRow][iColumn] == CELL_SYMBOL_MINE)
                m_gameGrid.setElem(iColumn, iRow, MINE);
    // Reset UI component
    m_uiComponent->resetField(lines[0].Len(), lines.Num());
}


void FGameController::setUIComponent(TSharedPtr<SMainWindow> uiComponent)
{
    m_uiComponent = uiComponent;
    m_uiComponent->m_onClicked.BindRaw(this, &FGameController::uiElementClicked);
}


void FGameController::uiElementClicked(int32 x, int32 y)
{
    TPair<int32, int32> gridSize = m_gameGrid.getSize();
    // Skip out-of-grid and already open elements
    if ((x >= gridSize.Key) ||
        (y >= gridSize.Value) ||
        ((m_gameGrid.getElem(x, y) != HIDDEN) && (m_gameGrid.getElem(x, y) != MINE)))
        return;

    // Found mine
    if (m_gameGrid.getElem(x, y) == MINE)
    {
        m_uiComponent->openElement(x, y, FText::FromString("#"), true);
        m_gameGrid.setElem(x, y, MINE_OPEN);
    }
    else
    {
        // Count mines on neighbor cells
        int32 minesCounter = 0;
        for (int32 xCheck = x - 1; xCheck <= x + 1; xCheck++)
            for (int32 yCheck = y - 1; yCheck <= y + 1; yCheck++)
            {
                if ((xCheck >= 0) && (xCheck < gridSize.Key) &&
                    (yCheck >= 0) && (yCheck < gridSize.Value) &&
                    (m_gameGrid.getElem(xCheck, yCheck) == MINE))
                    minesCounter++;
            }
        m_uiComponent->openElement(x, y, FText::AsNumber(minesCounter), false);
        m_gameGrid.setElem(x, y, OPEN);
    }
}


TArray<FString> FGameController::getLinesFromMessage(const FString &message)
{
    TArray<FString> result;

    // Split message into lines
    message.ParseIntoArrayLines(result);

    // Check lines
    for (const FString &line : result)
    {
        // Check length
        if (line.Len() != result[0].Len())
        {
            result.Empty();
            return result;
        }

        // Check characters
        for (TCHAR symbol : line)
            if ((symbol != CELL_SYMBOL_EMPTY) && (symbol != CELL_SYMBOL_MINE))
            {
                result.Empty();
                return result;
            }
    }

    return result;
}
