#include <stdio.h>
#include <unistd.h>
int main() {
int p = getpid();
printf("DÉBUT %i", p);
unsigned n = 0x7fffffff;
while(n--);
printf("FIN %i", p);
return 0;
}
