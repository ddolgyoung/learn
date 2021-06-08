#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "deck.h"

void print_hand(deck_t * hand){
  card_t myHand;;
  for(size_t i=0; i < hand->n_cards; i++){
    myHand = *hand->cards[i];
    print_card(myHand);
    printf(" ");
  }
}
  
  
int deck_contains(deck_t * d, card_t c) {
  for(size_t i=0; i< d->n_cards; i++){
    if( (d->cards[i]->value)==c.value && (d->cards[i]->suit==c.suit) ){
      return 1;
    }
  }
  return 0;
}


void shuffle(deck_t * d){
  for(size_t i = 0; i< d->n_cards; i++){
    card_t * temp = d->cards[i];
    int r = random() % d->n_cards;
    d->cards[i] = d->cards[r];
    d->cards[r] = temp;
  }
}

void assert_full_deck(deck_t * d) {
  for(int i=0; i < 52; i++){
    assert(deck_contains(d,card_from_num(i))==1); 
  }
}

void add_card_to(deck_t * deck, card_t c){
  deck->n_cards += 1;
  deck->cards = realloc(deck->cards, (deck->n_cards) * sizeof(*deck->cards));
  deck->cards[deck->n_cards-1] = malloc(sizeof(*deck->cards[deck->n_cards-1]));
  deck->cards[deck->n_cards-1]->value = c.value;
  deck->cards[deck->n_cards-1]->suit = c.suit;
}

card_t * add_empty_card(deck_t * deck){
  card_t *empty = malloc(sizeof(*empty));
  empty->value = 0;
  empty->suit = NUM_SUITS;
  add_card_to(deck, *empty);
  free(empty);  
  return deck->cards[deck->n_cards-1];
}

deck_t * make_deck_exclude(deck_t * excluded_cards){
  deck_t * d = malloc(sizeof(*d));
  d->n_cards = 52-(excluded_cards->n_cards);
  d->cards = malloc((d->n_cards) * sizeof(*d->cards));
  size_t n = 0;
  for(int i = 0; i < d->n_cards; i++){
    card_t c = card_from_num(i+n);
    for(int j = 0; j < excluded_cards->n_cards; j++){
      if(excluded_cards->cards[j]->value == c.value && excluded_cards->cards[j]->suit == c.suit){
	n++;
	c = card_from_num(i+n);
	j = -1;
      }
    }
    d->cards[i] = malloc(sizeof(*d->cards[i]));
    d->cards[i]->value = c.value;
    d->cards[i]->suit = c.suit;
  }
  return d;
}

deck_t * build_remaining_deck(deck_t ** hands, size_t n_hands){
  deck_t * d1 = malloc(sizeof(*d1));
  d1->n_cards = 0;
  d1->cards = NULL;
  int i = 0;
  for(int h = 0; h < n_hands; h++){
    for(int l = 0; l < hands[h]->n_cards; l++){
      if( (hands[h]->cards[l]->value) >= 2 && (hands[h]->cards[l]->value) <= 14){
	add_card_to(d1,*hands[h]->cards[l]);
	i++;
      }
    }
  }
  deck_t *d2 = make_deck_exclude(d1);
  free_deck(d1);
  return d2;
}
  
  
void free_deck(deck_t * deck){
  for(int m = 0; m < deck->n_cards; m++){
    free(deck->cards[m]);
  }
  free(deck->cards);
  free(deck);
}
