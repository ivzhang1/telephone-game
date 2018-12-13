#tdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <errno.h>
#define KEY 10100
#define SKEY 9898

union semun {
  int val; // for SETVAL
  struct semid_ds *buf; // for IPC_STAT and IPC_SET
  unsigned short *array; // SETALL
  struct seminfo *__buf;
};

int main(int argc, char *argv[]){
  char input[3];
  fgets(input,3,stdin);
  int shmid, semid;
  char *data;
  union semun su;

  //printf("\n");
  if(strcmp(input, "-c")){ // make the shared memory, semaphore and file
    // Creates shared memory
    shmid = shmget(SKEY, 200, IPC_CREAT | IPC_EXCL | 0644);
    data = shmat(shmid, (void *)0, 0);

    // Creates semaphore
    su.val = 1;
    semid = semget(KEY, 1, IPC_CREAT | IPC_EXCL | 0644);
    semctl(semid, 0, SETVAL, su);

    // Creates new file with O_TRUNC
    int file_out = open("story.txt", O_WRONLY | O_CREAT | O_TRUNC, 644);

  }

  if(strcmp(input, "-r")){ // Remove the shared memory, the semaphore and the story.
    // Deletes shared memory
    shmdt(data);
    shmctl(shmid, IPC_RMID, NULL);

    // Waiting for semaphore

    struct sembuf *oper;
    oper->sem_num = 0;
    oper->sem_op = -1;
    oper->sem_flg = SEM_UNDO;

    while(su.val){

    }
    semop(semid, oper, 1);
    semid = semget(KEY, 1, 0);
    // Deletes semaphore
    semctl(semid, 0, IPC_RMID);
    //Prints out story and then deletes it
    struct stat file;
    stat("story.txt", &file);
    int size = file.st_size;
    //printf("%d\n", size);
    char store[size];
    read(read_file, store, size);
    printf("Story: %s\n", store);

    remove("story.txt");
  }

  if(strcmp(input, "-v")){ // Output the contents of the story file.
    struct stat file;
    stat("story.txt", &file);
    int size = file.st_size;
    //printf("%d\n", size);
    char store[size];
    read(read_file, store, size);
    printf("%s\n", store);
  }

  return 0;
}#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <errno.h>
#define KEY 10100
#define SKEY 9898

union semun {
  int val; // for SETVAL
  struct semid_ds *buf; // for IPC_STAT and IPC_SET
  unsigned short *array; // SETALL
  struct seminfo *__buf;
};

int main(int argc, char *argv[]){
  char input[3];
  fgets(input,3,stdin);
  int shmid, semid;
  char *data;
  union semun su;

  //printf("\n");
  if(strcmp(input, "-c")){ // make the shared memory, semaphore and file
    // Creates shared memory
    shmid = shmget(SKEY, 200, IPC_CREAT | IPC_EXCL | 0644);
    data = shmat(shmid, (void *)0, 0);

    // Creates semaphore
    su.val = 1;
    semid = semget(KEY, 1, IPC_CREAT | IPC_EXCL | 0644);
    semctl(semid, 0, SETVAL, su);

    // Creates new file with O_TRUNC
    int file_out = open("story.txt", O_WRONLY | O_CREAT | O_TRUNC, 644);

  }

  if(strcmp(input, "-r")){ // Remove the shared memory, the semaphore and the story.
    // Deletes shared memory
    shmdt(data);
    shmctl(shmid, IPC_RMID, NULL);

    // Waiting for semaphore

    struct sembuf *oper;
    oper->sem_num = 0;
    oper->sem_op = -1;
    oper->sem_flg = SEM_UNDO;

    while(su.val){

    }
    semop(semid, oper, 1);
    semid = semget(KEY, 1, 0);
    // Deletes semaphore
    semctl(semid, 0, IPC_RMID);
    //Prints out story and then deletes it
    struct stat file;
    stat("story.txt", &file);
    int size = file.st_size;
    //printf("%d\n", size);
    char store[size];
    read(read_file, store, size);
    printf("Story: %s\n", store);

    remove("story.txt");
  }

  if(strcmp(input, "-v")){ // Output the contents of the story file.
    struct stat file;
    stat("story.txt", &file);
    int size = file.st_size;
    //printf("%d\n", size);
    char store[size];
    read(read_file, store, size);
    printf("%s\n", store);
  }

  return 0;
}#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <errno.h>
#define KEY 10100
#define SKEY 9898

union semun {
  int val; // for SETVAL
  struct semid_ds *buf; // for IPC_STAT and IPC_SET
  unsigned short *array; // SETALL
  struct seminfo *__buf;
};

int main(int argc, char *argv[]){
  char input[3];
  fgets(input,3,stdin);
  int shmid, semid;
  char *data;
  union semun su;

  //printf("\n");
  if(strcmp(input, "-c")){ // make the shared memory, semaphore and file
    // Creates shared memory
    shmid = shmget(SKEY, 200, IPC_CREAT | IPC_EXCL | 0644);
    data = shmat(shmid, (void *)0, 0);

    // Creates semaphore
    su.val = 1;
    semid = semget(KEY, 1, IPC_CREAT | IPC_EXCL | 0644);
    semctl(semid, 0, SETVAL, su);

    // Creates new file with O_TRUNC
    int file_out = open("story.txt", O_WRONLY | O_CREAT | O_TRUNC, 644);

  }

  if(strcmp(input, "-r")){ // Remove the shared memory, the semaphore and the story.
    // Deletes shared memory
    shmdt(data);
    shmctl(shmid, IPC_RMID, NULL);

    // Waiting for semaphore

    struct sembuf *oper;
    oper->sem_num = 0;
    oper->sem_op = -1;
    oper->sem_flg = SEM_UNDO;

    while(su.val){

    }
    semop(semid, oper, 1);
    semid = semget(KEY, 1, 0);
    // Deletes semaphore
    semctl(semid, 0, IPC_RMID);
    //Prints out story and then deletes it
    struct stat file;
    stat("story.txt", &file);
    int size = file.st_size;
    //printf("%d\n", size);
    char store[size];
    read(read_file, store, size);
    printf("Story: %s\n", store);

    remove("story.txt");
  }

  if(strcmp(input, "-v")){ // Output the contents of the story file.
    struct stat file;
    stat("story.txt", &file);
    int size = file.st_size;
    //printf("%d\n", size);
    char store[size];
    read(read_file, store, size);
    printf("%s\n", store);
  }

  return 0;
}
