#include <unistd.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <stdio.h>

int main () {
    char memn[] = "shared-memory"; //shared memory name
    char *addr;
    int shm;
    int mem_size = 100;

    if ((shm = shm_open(memn, O_RDWR, 0666)) == -1) {
        printf("Opening error\n");
        perror("shm_open");
        return 1;
    } else {
        printf("Object is open: name = %s, id = 0x%x\n", memn, shm);
    }
 
    addr = mmap(0, mem_size, PROT_WRITE|PROT_READ, MAP_SHARED, shm, 0);
    if (addr == (char*)-1) {
        printf("Error getting pointer to shared memory\n");
        return 1;
    }

    //output
    printf(addr);

    //close object
    close(shm);
 
 
    //delete shared-memory
    if (shm_unlink(memn) == -1) {
        perror("shm_unlink");
    }
    return 0;
}
