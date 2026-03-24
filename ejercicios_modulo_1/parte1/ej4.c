#include <math.h>
#include <stdio.h>

int bin_to_dec(char* binum)
{
  int dec = 0;
  for (int i = 0; binum[i] != '\0'; i++) {
    dec = dec*2;
    if (binum[i] == '1') {
      dec += 1;
    }
  }
  return dec;
}


int main(int argc, char *argv[])
{
  char* bin = "101";
  printf("%d\n", bin_to_dec(bin)); 
  return 0;
}
