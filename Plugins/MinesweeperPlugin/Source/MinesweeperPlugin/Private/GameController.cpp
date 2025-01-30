#include "GameController.h"

const TCHAR FGameController::CELL_SYMBOL_EMPTY {'X'};
const TCHAR FGameController::CELL_SYMBOL_MINE {'O'};

void FGameController::httpResult(bool result, const FString &message)
{
    if (!result)
        return;

    // Split message into strings
    TArray<FString> lines = getLinesFromMessage(message);
    if (lines.IsEmpty())
        return;
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
