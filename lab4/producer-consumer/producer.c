#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <semaphore.h>
#include <unistd.h>
#include <time.h>
#include <string.h>

#define SHM_NAME "/shm_buffer"
#define SEM_EMPTY "/sem_empty"
#define SEM_FULL "/sem_full"
#define SEM_MUTEX "/sem_mutex"

#define BUFFER_SIZE 5

typedef struct {
    int buffer[BUFFER_SIZE];
    int in;
    int out;
} shared_data;

int main() {
    int shm_fd;
    shared_data *shm_ptr;

    sem_t *sem_empty = sem_open(SEM_EMPTY, O_CREAT, 0666, BUFFER_SIZE);
    sem_t *sem_full  = sem_open(SEM_FULL,  O_CREAT, 0666, 0);
    sem_t *sem_mutex = sem_open(SEM_MUTEX, O_CREAT, 0666, 1);

    shm_fd = shm_open(SHM_NAME, O_CREAT | O_RDWR, 0666);
    ftruncate(shm_fd, sizeof(shared_data));
    shm_ptr = mmap(0, sizeof(shared_data), PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);

    shm_ptr->in = 0;
    shm_ptr->out = 0;

    srand(time(NULL));

    while(1){
	    //for (int i = 0; i < 10; i++) {
        int item = rand() % 100;

        sem_wait(sem_empty);
        sem_wait(sem_mutex);

        shm_ptr->buffer[shm_ptr->in] = item;
        printf("Produced: %d at %d\n", item, shm_ptr->in);
        shm_ptr->in = (shm_ptr->in + 1) % BUFFER_SIZE;

        sem_post(sem_mutex);
        sem_post(sem_full);

        usleep(100000);
    }

    munmap(shm_ptr, sizeof(shared_data));
    close(shm_fd);

    sem_close(sem_empty);
    sem_close(sem_full);
    sem_close(sem_mutex);

    return 0;
}
