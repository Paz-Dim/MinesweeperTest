#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "HttpModule.h"
#include "Interfaces/IHttpRequest.h"
#include "Interfaces/IHttpResponse.h"

// Request result delegate
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnRequestResult, bool /*Result*/, const FString &/*Message*/);

/**
 * AI connector. Performs requests to Google Gemini.
 */
class FAIConnector
{

public:
    // Fields
    // Request result delegate
    FOnRequestResult m_onRequestResultUI;

    // Methods
    // Perform request
    void performRequest(const FString &request);

protected:
    // Constants
    // Google Gemini request format
    static const FString HTTP_REQUEST_FORMAT;
    // Google Gemeni API URL
    static const FString HTTP_REQUEST_URL;

    // Methods
    // HTTP request callback
    void httpRequestCallback(FHttpRequestPtr httpRequest, FHttpResponsePtr httpResponse, bool bSucceeded);
};
