#include <stdio.h>
#include <stdlib.h>

struct _retire_info {
  int months;
  double contribution;
  double rate_of_return;
};

typedef struct _retire_info retire_info;

double calculator(double balance, retire_info statusInfo) {
  balance = balance + (balance * statusInfo.rate_of_return);
  balance = balance + statusInfo.contribution;

  return balance;
}

void retirement(int startAge,
		double initial,
		retire_info working,
		retire_info retired) {

  int ageInMonth = startAge;
  double calculatedBalance = initial;
  while ( ageInMonth < (startAge + working.months + retired.months) ) {
    int year  = ageInMonth / 12;
    int month = ageInMonth % 12;
    printf("Age %3d month %2d you have $%.2lf\n", year, month, calculatedBalance);

    ageInMonth++;
    if ( (ageInMonth - startAge) <= working.months ) {
      calculatedBalance = calculator(calculatedBalance, working);
    } else {
      calculatedBalance = calculator(calculatedBalance, retired);
    }
  }
}

int main(void) {
  retire_info working;
  working.months = 489;
  working.contribution = 1000;
  working.rate_of_return = 0.045 / 12;

  retire_info retired;
  retired.months = 384;
  retired.contribution = -4000;
  retired.rate_of_return = 0.01 / 12;

  int startAge = 327;
  double initial = 21345;
  retirement(startAge, initial, working, retired);

  return EXIT_SUCCESS;
}
