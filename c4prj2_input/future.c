#include <stdio.h>
#include <stdlib.h>
#include "cards.h"
#include "deck.h"
#include "future.h"

void add_future_card(future_cards_t * fc, size_t index, card_t * ptr) {
  if(index >= fc->n_decks){
    for(int n = fc->n_decks; n < index+1; n++){
      fc->n_decks += 1;
      fc->decks = realloc(fc->decks, fc->n_decks * sizeof(*fc->decks));
      fc->decks[n].n_cards = 0;
      fc->decks[n].cards = NULL;
      if(fc->n_decks == index+1){
	fc->decks[n].n_cards = 1;
	fc->decks[n].cards = realloc(fc->decks[n].cards, fc->decks[n].n_cards * sizeof(*fc->decks[n].cards));
	fc->decks[n].cards[fc->decks[n].n_cards-1] = ptr;
      }
    }
  }
  else{
    for(int i = 0; i < fc->n_decks; i++){
      if(i == index){
	fc->decks[i].n_cards += 1;
	fc->decks[i].cards = realloc(fc->decks[i].cards, fc->decks[i].n_cards * sizeof(*fc->decks[i].cards));
	fc->decks[i].cards[fc->decks[i].n_cards-1] = ptr;
	break;
      }
    }
  }
}   
 
void future_cards_from_deck(deck_t * deck, future_cards_t * fc) {
  int count = 0;
  for(int n = 0; n < fc->n_decks; n++){
    if(fc->decks[n].n_cards != 0){
      for(int m = 0; m < fc->decks[n].n_cards; m++){
	fc->decks[n].cards[m]->value = deck->cards[count]->value;
	fc->decks[n].cards[m]->suit = deck->cards[count]->suit;
      }
      count++;
    }
  }
}
