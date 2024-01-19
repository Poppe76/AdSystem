#ifndef _CLIENTS_H_
#define _CLIENTS_H_

struct Ad 
{
  char m_message[40];
  int m_rule;
};

struct Client 
{
  char m_name[30];
  int m_clientId[1];
  int m_paid;  
  int m_adTimeShare; 
  Ad ads[3];
};

struct Clients
{
  Client clients[4] = {
    {"Hederlige Harrys Cars", 0, 5000, 0, {  // client names serves no purpose and may take up unnecissary memory, but makes it easier to read.
      {"Kop bil hos Harry", 1},  // regular v
      {"En god bilaffar (for Harry!)", 1}, // regular v
      {"Hederlige Harrys Bilar", 2} // blinking v
    }},
    {"Farmor Ankas Pajer AB", 1, 3000, 0, {
      {"Kop paj hos Farmor Anka", 2}, // blinking v
      {"Skynda innan Marten atit alla p", 1}  // regular  v  // writing pajer instead of p causes a bug. 35 chars instead of 32...
    }},
    {"Svarte Petters Svartbyggen", 2, 1500, 0, {
      {"Lat Petter Bygga at dig", 3}, // even min  v
      {"Bygga svart? Ring Petter", 4} // uneven min  v
    }},
    {"Langbens detektivbyra", 3, 4000, 0, {
      {"Mysterier? Ring Langben", 5}, // even hour v
      {"Langben fixar biffen", 6} // uneven hour
    }},   // ASCII ?
  };
};

#endif // _CLIENTS_H_
