#include "eval.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int card_ptr_comp(const void * vp1, const void * vp2) {
  const card_t * const * cp1 = vp1;
  const card_t * const * cp2 = vp2;
  if((*cp1)->value > (*cp2)->value){
    return -1;
  }
  else if((*cp1)->value == (*cp2)->value){
    if((*cp1)->suit == (*cp2)->suit){
      return 0;
    }
    else if((*cp1)->suit > (*cp2)->suit){
      return -1;
    }
    else{
      return 1;
    }
  }
  else{
    return 1;
  }
}

void sortStringArray(const void ** hand, size_t n_cards){
  qsort(hand, n_cards, sizeof(hand), card_ptr_comp);
}


suit_t flush_suit(deck_t * hand) {
  card_t **myCards = hand->cards;
  int s = 0;
  int d = 0;
  int h = 0;
  int c = 0;
  for(size_t i = 0; i < hand->n_cards; i++){
    if(myCards[i]->suit == SPADES){
      s += 1;
    }
    else if(myCards[i]->suit == DIAMONDS){
      d += 1 ;
    }
    else if(myCards[i]->suit == HEARTS){
      h += 1;
    }
    else{
      c += 1;
    }
  }
  if(s > 4){return SPADES;}
  else if(d > 4){return DIAMONDS;}
  else if(h > 4){return HEARTS;}
  else if(c > 4){return CLUBS;}
  else{return NUM_SUITS;}
}


unsigned get_largest_element(unsigned * arr, size_t n) {
  if(n <= 0){
    return -1;
  }
  int largestValue = arr[0];
  for(size_t i=1; i < n; i++){
    if(arr[i] > largestValue){
      largestValue = arr[i];
    }
  }
  return largestValue;
}


size_t get_match_index(unsigned * match_counts, size_t n, unsigned n_of_akind){
  for(size_t i=0; i < n; i++){
    if(match_counts[i] == n_of_akind){
      return i;
    }
  }
  return -1;
}


ssize_t find_secondary_pair(deck_t * hand, unsigned * match_counts, size_t match_idx) {
  card_t **pair = hand->cards;
  if(* match_counts > 0){
    for(size_t i=0; i < hand->n_cards-1; i++){
      if(pair[i]->value == pair[i+1]->value){
	if(pair[i]->value != pair[match_idx]->value){
	  return i;
	}
      }
    }
  }
  return -1;
}


int is_straight_at(deck_t * hand, size_t index, suit_t fs) {
  card_t **cards = hand->cards;
  size_t n_cards = hand->n_cards;
  size_t counts = 1;
  size_t counts_a = 1;
  unsigned nextv = cards[index]->value - 1;
  unsigned nextv_a = 5;
  if(fs == NUM_SUITS){
    for(size_t i = index; i < n_cards-1; i++){
      size_t diff = cards[i]->value - cards[i+1]->value;
      if(diff > 1 && cards[index]->value == VALUE_ACE && cards[n_cards-1]->value == 2){
	for(size_t m = 0; m < n_cards; m++){
	  if(cards[m]->value == nextv_a){
	    counts_a++;
	    nextv_a--;
	    if(counts_a == 5) return -1;
	  }
	}
      }
      else if(cards[i+1]->value == nextv){
	counts++;
	nextv--;
	if(counts == 5) return 1;
      }
    }
  }
  else{
    for(size_t i = index; i < n_cards-1; i++){
      size_t diff = cards[i]->value - cards[i+1]->value;
      if(diff > 1 && cards[index]->value == VALUE_ACE && cards[n_cards-1]->value == 2){
	for(size_t m = index; m < n_cards; m++){
	  if(cards[m]->value == nextv_a && cards[m]->suit == cards[index]->suit){
	    counts_a++;
	    nextv_a--;
	    if(counts_a == 5) return -1;
	  }
	}
      }
      else if(cards[i+1]->value == nextv && cards[i+1]->suit == cards[index]->suit){
	counts++;
	nextv--;
	if(counts == 5) return 1;
      }
    }
  }
  return 0;
}


hand_eval_t build_hand_from_match(deck_t * hand, unsigned n, hand_ranking_t what, size_t idx) {
  hand_eval_t ans;
  ans.ranking = what;
  if(n == 0){
    for(size_t m = 0; m < 5; m++){
      ans.cards[m] = hand->cards[m];
    }
    return ans;
  }
  for(size_t i = 0; i < n; i++){
    if(idx > 0){
      ans.cards[i] = hand->cards[idx+i];
    }
    else{
      ans.cards[i] = hand->cards[i];
    }
  }
  for(size_t j = 0; j < 5-n; j++){
    if(idx == 0){
      ans.cards[n+j] = hand->cards[n+j];
    }
    else{
      for(size_t k = 0; k < idx; k++){
	if(n+k >= 5)
	  break;
	ans.cards[n+k] = hand->cards[k];
      }
    }
    if(n+j+idx >= 5)
      break;
    ans.cards[n+j+idx] = hand->cards[n+j+idx];
  }
  return ans;
}


int compare_hands(deck_t * hand1, deck_t * hand2) {
  qsort(hand1->cards, hand1->n_cards, sizeof(hand1->cards[0]),card_ptr_comp);
  qsort(hand2->cards, hand2->n_cards, sizeof(hand2->cards[0]),card_ptr_comp);
  hand_eval_t rank1, rank2;
  rank1 = evaluate_hand(hand1);
  rank2 = evaluate_hand(hand2);
  if(rank1.ranking < rank2.ranking){
    return 1;
  }
  else if(rank1.ranking > rank2.ranking){
    return -1;
  }
  else{
    for(size_t i = 0; i < 5; i++){
      int c = rank1.cards[i]->value - rank2.cards[i]->value;
      if(c > 0){
	return 1;
      }
      else if(c < 0){
	return -1;
      }      
    }
  }
  return 0;  
}


//You will write this function in Course 4.
//For now, we leave a prototype (and provide our
//implementation in eval-c4.o) so that the
//other functions we have provided can make
//use of get_match_counts.
unsigned * get_match_counts(deck_t * hand){
  unsigned * a = malloc(hand->n_cards * sizeof(*a));
  int count = 1;
  for(int i = 0; i < hand->n_cards; i++){
    for(int j = 0; j < hand->n_cards; j++){
      if(i != j && hand->cards[i]->value == hand->cards[j]->value){
	count++;
      }
    }
    a[i] = count;
    count = 1;
  }
  return a;
}



// We provide the below functions.  You do NOT need to modify them
// In fact, you should not modify them!


//This function copies a straight starting at index "ind" from deck "from".
//This copies "count" cards (typically 5).
//into the card array "to"
//if "fs" is NUM_SUITS, then suits are ignored.
//if "fs" is any other value, a straight flush (of that suit) is copied.
void copy_straight(card_t ** to, deck_t *from, size_t ind, suit_t fs, size_t count) {
  assert(fs == NUM_SUITS || from->cards[ind]->suit == fs);
  unsigned nextv = from->cards[ind]->value;
  size_t to_ind = 0;
  while (count > 0) {
    assert(ind < from->n_cards);
    assert(nextv >= 2);
    assert(to_ind <5);
    if (from->cards[ind]->value == nextv &&
	(fs == NUM_SUITS || from->cards[ind]->suit == fs)){
      to[to_ind] = from->cards[ind];
      to_ind++;
      count--;
      nextv--;
    }
    ind++;
  }
}


//This looks for a straight (or straight flush if "fs" is not NUM_SUITS)
// in "hand".  It calls the student's is_straight_at for each possible
// index to do the work of detecting the straight.
// If one is found, copy_straight is used to copy the cards into
// "ans".

int find_straight(deck_t * hand, suit_t fs, hand_eval_t * ans) {
  if (hand->n_cards < 5){
    return 0;
  }
  for(size_t i = 0; i <= hand->n_cards -5; i++) {
    int x = is_straight_at(hand, i, fs);
    if (x != 0){
      if (x < 0) { //ace low straight
	assert(hand->cards[i]->value == VALUE_ACE &&
	       (fs == NUM_SUITS || hand->cards[i]->suit == fs));
	ans->cards[4] = hand->cards[i];
	size_t cpind = i+1;
	while(hand->cards[cpind]->value != 5 ||
	      !(fs==NUM_SUITS || hand->cards[cpind]->suit ==fs)){
	  cpind++;
	  assert(cpind < hand->n_cards);
	}
	copy_straight(ans->cards, hand, cpind, fs,4) ;
      }
      else {
        copy_straight(ans->cards, hand, i, fs,5);
      }
      return 1;
    }
  }
  return 0;
}


/*int find_straight(deck_t * hand, suit_t fs, hand_eval_t * ans) {
  if (hand->n_cards < 5){
    return 0;
  }
  for(size_t i = 0; i <= hand->n_cards -5; i++) {
    int x = is_straight_at(hand, i, fs);
    if (x >0){
      copy_straight(ans->cards, hand, i, fs,5);
      return 1;
    }
  }
  //we have to check ace low straights LAST since
  // Ac 6c 5c 4c 3c 2c will give the ace low otherwise
  for(size_t i = 0; i <= hand->n_cards -5; i++) {
    int x = is_straight_at(hand, i, fs);
    if (x < 0) { //ace low straight
       assert(hand->cards[i]->value == VALUE_ACE &&
           (fs == NUM_SUITS || hand->cards[i]->suit == fs));
      ans->cards[4] = hand->cards[i];
      size_t cpind = i+1;
      while(hand->cards[cpind]->value != 5 ||
	    !(fs==NUM_SUITS || hand->cards[cpind]->suit ==fs)){
	cpind++;
	assert(cpind < hand->n_cards);
      }
      copy_straight(ans->cards, hand, cpind, fs,4) ;
      return 1;
    }
  }
  return 0;
  }*/


//This function puts all the hand evaluation logic together.
//This function is longer than we generally like to make functions,
//and is thus not so great for readability :(
hand_eval_t evaluate_hand(deck_t * hand) {
  suit_t fs = flush_suit(hand);
  hand_eval_t ans;
  if (fs != NUM_SUITS) {
    if(find_straight(hand, fs, &ans)) {
      ans.ranking = STRAIGHT_FLUSH;
      return ans;
    }
  }
  unsigned * match_counts = get_match_counts(hand);
  unsigned n_of_a_kind = get_largest_element(match_counts, hand->n_cards);
  assert(n_of_a_kind <= 4);
  size_t match_idx = get_match_index(match_counts, hand->n_cards, n_of_a_kind);
  ssize_t other_pair_idx = find_secondary_pair(hand, match_counts, match_idx);
  free(match_counts);
  if (n_of_a_kind == 4) { //4 of a kind
    return build_hand_from_match(hand, 4, FOUR_OF_A_KIND, match_idx);
  }
  else if (n_of_a_kind == 3 && other_pair_idx >= 0) {     //full house
    ans = build_hand_from_match(hand, 3, FULL_HOUSE, match_idx);
    ans.cards[3] = hand->cards[other_pair_idx];
    ans.cards[4] = hand->cards[other_pair_idx+1];
    return ans;
  }
  else if(fs != NUM_SUITS) { //flush
    ans.ranking = FLUSH;
    size_t copy_idx = 0;
    for(size_t i = 0; i < hand->n_cards;i++) {
      if (hand->cards[i]->suit == fs){
	ans.cards[copy_idx] = hand->cards[i];
	copy_idx++;
	if (copy_idx >=5){
	  break;
	}
      }
    }
    return ans;
  }
  else if(find_straight(hand,NUM_SUITS, &ans)) {     //straight
    ans.ranking = STRAIGHT;
    return ans;
  }
  else if (n_of_a_kind == 3) { //3 of a kind
    return build_hand_from_match(hand, 3, THREE_OF_A_KIND, match_idx);
  }
  else if (other_pair_idx >=0) {     //two pair
    assert(n_of_a_kind ==2);
    ans = build_hand_from_match(hand, 2, TWO_PAIR, match_idx);
    ans.cards[2] = hand->cards[other_pair_idx];
    ans.cards[3] = hand->cards[other_pair_idx + 1];
    if (match_idx > 0) {
      ans.cards[4] = hand->cards[0];
    }
    else if (other_pair_idx > 2) {  //if match_idx is 0, first pair is in 01
      //if other_pair_idx > 2, then, e.g. A A K Q Q
      ans.cards[4] = hand->cards[2];
    }
    else {       //e.g., A A K K Q
      ans.cards[4] = hand->cards[4];
    }
    return ans;
  }
  else if (n_of_a_kind == 2) {
    return build_hand_from_match(hand, 2, PAIR, match_idx);
  }
  return build_hand_from_match(hand, 0, NOTHING, 0);
}
