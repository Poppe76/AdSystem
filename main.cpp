#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "millis.h"
#include "stdint.h"
#include "lcd.h"
#include "analogPin.h"
#include "src/AdManager.h"


// https://wokwi.com/projects/365067824797777921

/*
---------TODO-------
- how do I set length of adm.playlistClientIds ? I don't technically know it until calculation in AdManager.cpp
*/

int main(void)
{
  AdManager adm;
  adm.setup();

  HD44780 lcd;
  lcd.GoTo(0, 0);  
  adm.setRandomMsg();
  // adm.appTime.hour = 1;  // for testing ad rule 6.
  char *message = adm.m_currentAdMessage;
  lcd.WriteText(message);
  millis_init();
  sei();
  millis_t millis = millis_get();

  while (1)
  {
    millis_t current = millis_get();

    if (adm.m_blinkingAdActive)
    {
      if (adm.appTime.second % 2 != 0)
      {
        message = adm.m_emptyBlinker;
        lcd.Clear();
      }
      else
      {
        message = adm.m_currentAdMessage;
        lcd.WriteText(message);
      }
    }
    else
    {
      message = adm.m_currentAdMessage;
      lcd.Clear();
      lcd.WriteText(message);
    }
    
    if (current - millis > AD_LENGTH)
    {
      adm.setRandomMsg();
      millis = current;
    }

    _delay_ms(1000); // 1 sec
    adm.upDateTime();
  }
  return 0;
}