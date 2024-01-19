#ifndef _ADMANAGER_H_
#define _ADMANAGER_H_

#include "Clients.h"

#define AD_SHARE_NORMALIZER 0.002   // as gotten from the theoretical calculation AD SHARE NORMALIZER in AdManager.cpp
#define AD_LENGTH 20000
#define BLINK_DELAY 1000

struct TimeHolder
{
  int hour = 0;
  int minute = 0;
  int second = 0;
}; 

class AdManager
{
  private:
    int m_previousAdIndex = -1;
    int m_previousClientId = 0;
    int m_randomAdIndex = -1;
    int m_selectedClientId = 0;
    int m_randomMsgIndex = 0;
    int m_totalAdShares = 0;
    int m_playlistClientIds[27];

    void getAdRule();

  public:
    Clients m_clientCollection;
    TimeHolder appTime;
    char m_currentAdMessage[32] = "hopplasasanjo";    
    bool m_blinkingAdActive = false;
    char *m_emptyBlinker = "";
    //int adsRunCounter = 0; // test for non-random ads

    void setup();
    void calculateTimeShare();
    void setRandomMsg();
    void upDateTime();

    AdManager();
};


#endif // _ADMANAGER_H_