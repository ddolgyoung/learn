#include <stdio.h>
#include <stdlib.h>
#include "cards.h"
#include "deck.h"
#include "future.h"
#include "input.h"

int main(int argc, char ** argv){
  if(argc != 2){
    perror("invalid argc\n");
    return EXIT_FAILURE;
  }
  //    future_cards_t * fc = make_future();
  future_cards_t * fc = malloc(sizeof(*fc));
  fc->n_decks = 0;
  fc->decks = NULL;
  FILE * f = fopen(argv[1], "r");
  size_t n_input;
  deck_t ** input = read_input(f, &n_input, fc);
  deck_t * r_deck = build_remaining_deck(input, n_input);
  printf("deck\n");
  print_hand(r_deck);
  printf("\n");
  future_cards_from_deck(r_deck, fc);
  for(int i = 0; i < fc->n_decks; i++){
    for(int j = 0; j < fc->decks[i].n_cards; j++){
      printf("fc->decks[%d].n_cards[%zu]: ",i, fc->decks[i].n_cards);
      print_card(*fc->decks[i].cards[j]);
      printf("\n");
    }
  }
  for(int n = 0; n < n_input; n++){
    print_hand(input[n]);
    printf("\n");
  }
  fclose(f);
  for(int y = 0; y < fc->n_decks; y++){
    for(int x = 0; x < fc->decks[y].n_cards; x++){
      if(fc->decks[y].n_cards != 0)
      free(fc->decks[y].cards);
    }
  }
  free(fc->decks);
  free(fc);
  for(int n = 0; n < n_input ; n++){
    free_deck(input[n]);
  }
  free(input);  
  free_deck(r_deck);
  return EXIT_SUCCESS;
}      
