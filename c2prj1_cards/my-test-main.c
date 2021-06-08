#include <stdio.h>
#include "cards.h"

int main() {
  card_t a = card_from_num(13);
  card_t b = card_from_letters('2', 'h');
  assert_card_valid(a);
  assert_card_valid(b);

  print_card(a);
  print_card(b);
}
