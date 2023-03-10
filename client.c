#include <unistd.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

size_t BUF_SIZE = 32;

int main ()
{
    char memn[] = "shared-memory"; // object name
    char *addr;
    int shm;
    srand(time(0));
    int mem_size = 100;

    if ((shm = shm_open(memn, O_CREAT|O_RDWR, 0666)) == -1 )
    {
        perror("shm_open");
        return 1;
    }
    else
    {
        printf("Object is open: name = %s, id = 0x%x\n", memn, shm);
    }
    if (ftruncate(shm, mem_size) == -1)
    {
        perror("ftruncate");
        return 1;
    }
    else
    {
        printf("Memory size set and = %d\n", mem_size);
    }
    char buf[BUF_SIZE];

    addr = mmap(0, mem_size, PROT_WRITE|PROT_READ, MAP_SHARED, shm, 0);
    if (addr == (char*) -1)
    {
        perror("mmap");
        return 1;
    }
    for (size_t i = 0; i < BUF_SIZE; ++i)
    {
        buf[i] = '0' + rand() % 10;
    }
    memcpy(addr, buf, sizeof(buf));
    close(shm);
    return 0;
}
