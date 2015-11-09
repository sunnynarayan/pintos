#include <syscall.h>

int int main(int argc, char const *argv[])
{
	bool flag;
	flag = create("file.txt", 1000);
	return 0;
}

