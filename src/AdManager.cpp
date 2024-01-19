#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "AdManager.h"

AdManager::AdManager()
{
}

/*
  CALCULATE AD SHARE NORMALIZER
  Calculate smallest possible value of 5000, 3000, 1500, 4000, or any other number

  for each client.m_paid
    while (m_paid--)  // or something similarly useful
      x = m_paid
      if (m_paid % x == 0)  
        set array of true or false indexes for modulus numbers that give 0.
  compare all client arrays and find highest possible modulus number. 
    this is the number that all m_paid can be divided with to get lowest possible number 
    corresponding proportionally to m_paid

  In this case it's 500 which gives AD_SHARE_NORMALIZER of 0.002 
  Ie 5000 => 10, 3000 => 6, 1500 => 3, 4000 => 8.
  Use this to setup amount of ad slots. 10 + 6 + 3 + 8 = 27.
*/


void AdManager::setup()
{  
  calculateTimeShare();
}

void AdManager::upDateTime()
{
  appTime.second++;
  if (appTime.second == 60)
  {
    appTime.second = 0;
    appTime.minute++;
  }
  if (appTime.minute == 60)
  {
    appTime.minute = 0;
    appTime.hour++;
  }
  if (appTime.hour == 24)
  {
    appTime.hour = 0;
  }
}

void AdManager::setRandomMsg()
{
  // fake randomness
    // no random seed and no keeping track of how the adslots (playlistClientIds) have been used in the past.
  while (m_randomAdIndex == m_previousAdIndex || m_selectedClientId == m_previousClientId)
  {
    m_randomAdIndex = rand() % m_totalAdShares;   
    m_selectedClientId = m_playlistClientIds[m_randomAdIndex];  
  }
  m_previousAdIndex = m_randomAdIndex;
  m_previousClientId = m_selectedClientId;

  // ------test for non random ads------
  // m_selectedClientId = adsRunCounter;
  // adsRunCounter++;
  // if(adsRunCounter == 4)
  // {
  //   adsRunCounter = 0;
  // }
  // ------------------------------------

  getAdRule();
  strcpy(m_currentAdMessage, m_clientCollection.clients[m_selectedClientId].ads[m_randomMsgIndex].m_message);
}

void AdManager::getAdRule()
{
  m_blinkingAdActive = false;
  int numAds = 0; 
  for(const Ad &adNum : m_clientCollection.clients[m_selectedClientId].ads)
  {
    if(adNum.m_rule != 0)  // this has no need to be here (legacy code), but without it AD[1][1] ("Skynda innan Marten atit alla p") will not show.....
    {
      numAds++;
    }    
  }

  bool hasBlinkingAds = false;
  int selectedAdIndex = 0; // set to fallback 0, if below fails

  // 1-6, regular, blinking, even min, uneven min, even hour, uneven hour 
  for (int i = 0; i < numAds; i++)
  {
    const Ad &ad = m_clientCollection.clients[m_selectedClientId].ads[i];

    if(ad.m_rule == 2)
    {
      hasBlinkingAds = true;  
      break;
    }
    else if(ad.m_rule == 3 && appTime.minute % 2 == 0)
    {
      selectedAdIndex = i;
      break;
    }
    else if(ad.m_rule == 4 && appTime.minute % 2 != 0)
    {
      selectedAdIndex = i;
      break;
    }
    else if(ad.m_rule == 5 && appTime.hour % 2 == 0)
    {
      selectedAdIndex = i;
      break;
    }
    else if(ad.m_rule == 6 && appTime.hour % 2 != 0)
    {
      selectedAdIndex = i;
      break;
    }
  }

  if (hasBlinkingAds)
  {
    selectedAdIndex = rand() % numAds;
    m_blinkingAdActive = (m_clientCollection.clients[m_selectedClientId].ads[selectedAdIndex].m_rule == 2) ? true : false;
  }  
  m_randomMsgIndex = selectedAdIndex;  // remove selectedAdIndex
}

void AdManager::calculateTimeShare()
{
  for(Client &client : m_clientCollection.clients)
  {
    m_totalAdShares += client.m_paid;
  }
  m_totalAdShares = static_cast<int>(m_totalAdShares * AD_SHARE_NORMALIZER);

  for(Client &client : m_clientCollection.clients)
  {
    client.m_adTimeShare = static_cast<int>(client.m_paid * AD_SHARE_NORMALIZER);
  }

  int shareCounter = 0;
  for(Client &client : m_clientCollection.clients)
  {
    for (int i = 0; i < client.m_adTimeShare; i++)
    {
      m_playlistClientIds[shareCounter] = *client.m_clientId;
      shareCounter++;
    }
  }
}