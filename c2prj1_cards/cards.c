#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "cards.h"

void assert_card_valid(card_t c) {
  assert(c.value >= 2 && c.value <= VALUE_ACE);
  assert(c.suit >=SPADES && c.suit <= CLUBS);
}

const char * ranking_to_string(hand_ranking_t r) {
  switch(r){
    case STRAIGHT_FLUSH: return "STRAIGHT_FLUSH";
    case FOUR_OF_A_KIND: return "FOUR_OF_A_KIND";
    case FULL_HOUSE: return "FULL_HOUSE";
    case FLUSH: return "FLUSH";
    case STRAIGHT: return "STRAIGHT";
    case THREE_OF_A_KIND: return "THREE_OF_A_KIND";
    case TWO_PAIR: return "TWO_PAIR";
    case PAIR: return "PAIR";
    default: return "NOTHING";
  }
}

char value_letter(card_t c) {
   switch(c.value){
     case 2: return '2';
     case 3: return '3';
     case 4: return '4';
     case 5: return '5';
     case 6: return '6';
     case 7: return '7';
     case 8: return '8';
     case 9: return '9';
     case 10: return '0';
     case VALUE_JACK: return 'J';
     case VALUE_KING: return 'K';
     case VALUE_QUEEN: return 'Q';
     case VALUE_ACE: return 'A';
     default: break;
  }
  return 0;
}

char suit_letter(card_t c) {
  switch(c.suit){
    case SPADES: return 's';
    case HEARTS: return 'h';
    case DIAMONDS: return 'd';
    case CLUBS: return 'c';
    default: break;
  }
  return 0;
}

void print_card(card_t c) {
  printf("%c%c", value_letter(c), suit_letter(c));
}

card_t card_from_letters(char value_let, char suit_let) {
  card_t temp;
  //card_from_letters function is different from value_letter and suit_letter functions. In card_from_letters function, just do reverse process of value_letter and suit_letter functions. There are a letter of value and a letter of suit as argument of card_from_letters function and you need to return a struct, say temp , then temp.value is a integer from 2 to 14 and temp.suit is also a number between SPADES and CLUBS. You just need to convert char of value and char of suit to the corresponding number.
  //if (value_let == '0') temp.value = 10; or if (value_let == 48) temp.value = 10;
   switch(value_let) {
     case '2': temp.value = 2; break;
     case '3': temp.value = 3; break;
     case '4': temp.value = 4; break;
     case '5': temp.value = 5; break;
     case '6': temp.value = 6; break;
     case '7': temp.value = 7; break;
     case '8': temp.value = 8; break;
     case '9': temp.value = 9; break;
     case '0': temp.value = 10; break;
     case 'J': temp.value = VALUE_JACK; break;
     case 'K': temp.value = VALUE_KING; break;
     case 'Q': temp.value = VALUE_QUEEN; break;
     case 'A': temp.value = VALUE_ACE; break;
     default: break;
  }
    
  switch(suit_let){
    case 's': temp.suit = SPADES; break;
    case 'h': temp.suit = HEARTS; break;
    case 'd': temp.suit = DIAMONDS; break;
    case 'c': temp.suit = CLUBS; break;
    default: break;
  }
  assert_card_valid(temp);

  //You want to make a card_t struct from the letters that represent that card. So for example, if the value is 'A' and the suit is 's' then the card is the Ace of Spades, so should have value VALUE_ACE (defined to be 14 in cards.h) and suit SPADES (from the enum in cards.h). Likewise, '0' and 'c' would make the 10 of clubs, so value=10, and suit=CLUBS

  return temp;
}

card_t card_from_num(unsigned c) {
  card_t temp;
  temp.value = c % 13 + 2;
  
  if (0 <= c && c <= 12){
    temp.suit = SPADES;
  }
  else if (13 <= c && c <= 25){
    temp.suit = HEARTS;
  }
  else if (26 <= c && c <= 38){
    temp.suit = DIAMONDS;
  }
  else if (39 <= c && c <= 51){
    temp.suit = CLUBS;
  }
  return temp;
}
