#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <semaphore.h>
#include <unistd.h>
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

    sem_t *sem_empty = sem_open(SEM_EMPTY, 0);
    sem_t *sem_full  = sem_open(SEM_FULL,  0);
    sem_t *sem_mutex = sem_open(SEM_MUTEX, 0);

    shm_fd = shm_open(SHM_NAME, O_RDWR, 0666);
    shm_ptr = mmap(0, sizeof(shared_data), PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);

    for (int i = 0; i < 10; i++) {
        sem_wait(sem_full);
        sem_wait(sem_mutex);

        int item = shm_ptr->buffer[shm_ptr->out];
        printf("Consumed: %d at %d\n", item, shm_ptr->out);
        shm_ptr->out = (shm_ptr->out + 1) % BUFFER_SIZE;

        sem_post(sem_mutex);
        sem_post(sem_empty);

        sleep(2);
    }

    munmap(shm_ptr, sizeof(shared_data));
    close(shm_fd);

    sem_close(sem_empty);
    sem_close(sem_full);
    sem_close(sem_mutex);

    sem_unlink(SEM_EMPTY);
    sem_unlink(SEM_FULL);
    sem_unlink(SEM_MUTEX);
    shm_unlink(SHM_NAME);

    return 0;
}
