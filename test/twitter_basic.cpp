//
// Created by Rayer Tung on 31/05/2017.
//

#include "gtest/gtest.h"
#include "twitcurl.h"
#include <string>

TEST(Twitter_Basic, Login_Without_Cred) {
    twitCurl twitterObj;
    //TODO: Put these into yaml files
    twitterObj.setTwitterPassword("rayer");
    twitterObj.setTwitterUsername("wj/654e;");
    twitterObj.getOAuth().setConsumerKey( std::string( "JDLHdxA4LHzLPQzmdNFLH3YtZ" ) );
    twitterObj.getOAuth().setConsumerSecret( std::string( "hsuYvBtK5PbylGovTwIQMfCQqZDMqZjDnHPMC6dvcg15q1w1jH" ) );

    std::string myOAuthAccessTokenKey("");
    std::string myOAuthAccessTokenSecret("");
    std::ifstream oAuthTokenKeyIn;
    std::ifstream oAuthTokenSecretIn;
    char tmpBuf[1024];
    std::string tmpStr;

    oAuthTokenKeyIn.open( "twitterClient_token_key.txt" );
    oAuthTokenSecretIn.open( "twitterClient_token_secret.txt" );

    memset( tmpBuf, 0, 1024 );
    oAuthTokenKeyIn >> tmpBuf;
    myOAuthAccessTokenKey = tmpBuf;

    memset( tmpBuf, 0, 1024 );
    oAuthTokenSecretIn >> tmpBuf;
    myOAuthAccessTokenSecret = tmpBuf;

    oAuthTokenKeyIn.close();
    oAuthTokenSecretIn.close();

    if( myOAuthAccessTokenKey.size() && myOAuthAccessTokenSecret.size() )
    {
        /* If we already have these keys, then no need to go through auth again */
        printf( "\nUsing:\nKey: %s\nSecret: %s\n\n", myOAuthAccessTokenKey.c_str(), myOAuthAccessTokenSecret.c_str() );

        twitterObj.getOAuth().setOAuthTokenKey( myOAuthAccessTokenKey );
        twitterObj.getOAuth().setOAuthTokenSecret( myOAuthAccessTokenSecret );
    }    else
    {
        /* Step 2: Get request token key and secret */
        std::string authUrl;
        twitterObj.oAuthRequestToken( authUrl );

        /* Step 3: Get PIN  */
        memset( tmpBuf, 0, 1024 );
//        printf( "\nDo you want to visit twitter.com for PIN (0 for no; 1 for yes): " );
//        fgets( tmpBuf, sizeof( tmpBuf ), stdin );
//        tmpStr = tmpBuf;
//        if( std::string::npos != tmpStr.find( "1" ) )
//        {
//            /* Ask user to visit twitter.com auth page and get PIN */
//            memset( tmpBuf, 0, 1024 );
//            printf( "\nPlease visit this link in web browser and authorize this application:\n%s", authUrl.c_str() );
//            printf( "\nEnter the PIN provided by twitter: " );
//            fgets( tmpBuf, sizeof( tmpBuf ), stdin );
//            tmpStr = tmpBuf;
//            twitterObj.getOAuth().setOAuthPin( tmpStr );
//        }
//        else
//        {
//            /* Else, pass auth url to twitCurl and get it via twitCurl PIN handling */
//            twitterObj.oAuthHandlePIN( authUrl );
//        }

        twitterObj.oAuthHandlePIN( authUrl );

        /* Step 4: Exchange request token with access token */
        twitterObj.oAuthAccessToken();

        /* Step 5: Now, save this access token key and secret for future use without PIN */
        twitterObj.getOAuth().getOAuthTokenKey( myOAuthAccessTokenKey );
        twitterObj.getOAuth().getOAuthTokenSecret( myOAuthAccessTokenSecret );

        /* Step 6: Save these keys in a file or wherever */
        std::ofstream oAuthTokenKeyOut;
        std::ofstream oAuthTokenSecretOut;

        oAuthTokenKeyOut.open( "twitterClient_token_key.txt" );
        oAuthTokenSecretOut.open( "twitterClient_token_secret.txt" );

        oAuthTokenKeyOut.clear();
        oAuthTokenSecretOut.clear();

        oAuthTokenKeyOut << myOAuthAccessTokenKey.c_str();
        oAuthTokenSecretOut << myOAuthAccessTokenSecret.c_str();

        oAuthTokenKeyOut.close();
        oAuthTokenSecretOut.close();
        
    }
    /* OAuth flow ends */

}

TEST(Twitter_Basic, Login_With_Cred) {

}

TEST(Twitter_Basic, Logout) {

}