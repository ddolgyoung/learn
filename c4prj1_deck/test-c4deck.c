#include <stdio.h>
#include "cards.h"
#include "deck.h"
#include "eval.h"

int main() {
  deck_t * deck = malloc(sizeof(*deck));
  deck->n_cards = 5;
  deck->cards = malloc(deck->n_cards * sizeof(*deck->cards));
  int j = 20;
  card_t a = card_from_num(j);
  for(int i = 0; i < deck->n_cards; i++){
    deck->cards[i] = malloc(sizeof(*deck->cards[i]));
    deck->cards[i]->value = a.value;
    deck->cards[i]->suit = a.suit;
    j++;
    a = card_from_num(j);
  }
  a = card_from_num(50);
  //  print_card(a);
  //printf("\n");
  //add_card_to(deck,a);
  /*  deck_t * deck2 = malloc(sizeof(*deck2));
  deck2->n_cards = 5;
  deck2->cards = malloc(deck2->n_cards * sizeof(*deck2->cards));
  int l = 30;
  card_t x = card_from_num(l);
  for(int y = 0; y < deck2->n_cards; y++){
    deck2->cards[y] = malloc(sizeof(*deck2->cards[y]));
    deck2->cards[y]->value = a.value;
    deck2->cards[y]->suit = a.suit;
    l++;
    x = card_from_num(l);
  }
  x = card_from_num(40);
  print_card(x);
  printf("\n");*/
  //  make_deck_exclude(deck);
  //  card_t * b = add_empty_card(deck);
  //card_t c = *b;
  //print_card(c);
  // make_deck_exclude(deck);
  deck_t ** hands = malloc(sizeof(deck_t));
  //  hands[0] = deck;
  //hands[1] = deck2;
  *hands = deck;
  build_remaining_deck(hands,1);
  //print_hand(deck);
  //printf("\n");
  //free(hands[0]);
  //free(hands[1]);
  free(hands);
  //  print_hand(deck2);
  //printf("\n");
  free_deck(deck);
  //free_deck(deck2);
  //free(b);
}
