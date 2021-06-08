#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "deck.h"
#include "future.h"
#include "input.h"

deck_t * hand_from_string(const char * str, future_cards_t * fc){
  deck_t * d = malloc(sizeof(*d));
  d->n_cards = 0;
  d->cards = NULL;
  int n = 0;
  for(int i = 0; i < strlen(str); i++){
    if( (isspace(str[i])) || str[i] == '\n'){
      continue;
    }
    else{
      if(str[i] == '?'){
	size_t index = strtoul(str+i+1,NULL,0);
	add_future_card(fc, index, add_empty_card(d));
	n++;
      }
      else{
	d->n_cards += 1;
	d->cards = realloc(d->cards, d->n_cards * sizeof(*d->cards));
	d->cards[n] = malloc(sizeof(*d->cards[n]));
	*d->cards[n] = card_from_letters(str[i],str[i+1]);
	n++;
      }
    }
    i += 2;
  }
  if(d->n_cards < 5){
    fprintf(stderr, "Invalid n_cards\n");
  }
  return d;
}

deck_t ** read_input(FILE * f, size_t * n_hands, future_cards_t * fc) {
  deck_t ** hands = NULL;
  *n_hands = 0;
  char * curr = NULL;
  size_t sz;
  while (getline(&curr,&sz,f) >= 0) {
    *n_hands += 1;
    hands = realloc(hands, *n_hands * sizeof(*n_hands));
    hands[*n_hands-1] = hand_from_string(curr,fc);
    //    curr = NULL;
  }
  free(curr);
  return hands;
}
