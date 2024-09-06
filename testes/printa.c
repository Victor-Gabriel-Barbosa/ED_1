#include <stdio.h>

void limpa_buffer() {
  char c;
  while ((c = getchar())!= '\n' && c!= EOF);
}
int main() {
  char emoji[20];
  printf("Digite um emoji: ");
  scanf("%s", emoji);
  limpa_buffer();

  printf("Emoji digitado: %s\n", emoji);
  return 0;
}