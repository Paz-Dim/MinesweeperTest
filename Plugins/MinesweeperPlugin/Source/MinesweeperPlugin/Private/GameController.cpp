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
