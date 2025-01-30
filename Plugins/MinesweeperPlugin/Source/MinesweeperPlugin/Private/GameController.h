#pragma once

#include "CoreMinimal.h"

/**
 * Game controller component. Receives AI-generated game field, builds and controls game loop.
 */
class FGameController
{
public:
    // Methods
    // HTTP request result
    void httpResult(bool result, const FString &message);

protected:
    // Constants
    // Empty cell symbol
    static const TCHAR CELL_SYMBOL_EMPTY;
    // Mine cell symbol
    static const TCHAR CELL_SYMBOL_MINE;

    // Methods
    // Split received HTTP message into strings and validate it. Return array of lines, empty if message was incorrect.
    TArray<FString> getLinesFromMessage(const FString &message);
};
