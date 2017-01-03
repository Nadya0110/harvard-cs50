#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
  if (argc == 2)
    printf("%s\n", crypt(argv[1], "50"));
  else if (argc == 3)
    printf("%s\n", crypt(argv[1], argv[2]));
  else return 1;
}
