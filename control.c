#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <errno.h>

union semun {
  int val; // for SETVAL
  struct semid_ds *buf; // for IPC_STAT and IPC_SET
  unsigned short *array; // SETALL
  struct seminfo *__buf;
};

int main(int argc, char *argv[]){
  char input[4];

  fgets(input,3,stdin);
  input[4] = '\0';
  int key = ftok("control.c", 'R');
  int shmid, semid;
  char *data;
  union semun su;

  //printf("%s, %d\n", input, strcmp(input, "-c"));
  if(!strcmp(input, "-c")){ // make the shared memory, semaphore and file
    // Creates shared memory
    //printf("WOO\n");
    shmid = shmget(key, 200, IPC_CREAT | IPC_EXCL | 0644);
    data = shmat(shmid, (void *)0, 0);
  
    // Creates semaphore
    su.val = 1;
    semid = semget(key, 1, IPC_CREAT | IPC_EXCL | 0644);
    semctl(semid, 0, SETVAL, su);
    
    // Creates new file with O_TRUNC
    int file_out = open("story.txt", O_CREAT | O_TRUNC, 0666);
    //printf("WOO\n");
    
  } else if(!strcmp(input, "-r")){ // Remove the shared memory, the semaphore and the story.
    // Deletes shared memory
    shmdt(data);
    shmctl(shmid, IPC_RMID, NULL);
    
    // Waiting for semaphore

    /* struct sembuf *oper; */
    /* oper->sem_num = 0; */
    /* oper->sem_op = -1; */
    /* oper->sem_flg = SEM_UNDO; */
    
    /* while(su.val){ */

    /* } */
    /* semop(semid, oper, 1); */
    semid = semget(key, 1, 0);
    // Deletes semaphore
    semctl(semid, 0, IPC_RMID);
    //Prints out story and then deletes it
    struct stat file;
    stat("story.txt", &file);
    int size = file.st_size;
    //printf("%d\n", size);
    char store[size];
    int read_file = open("story.txt", O_RDONLY);
    read(read_file, store, size);
    printf("Story: %s\n", store);

    remove("story.txt");
  } else if(!strcmp(input, "-v")){ // Output the contents of the story file.
    //printf("%d\n", strcmp(input, "-v"));
    struct stat file;
    stat("story.txt", &file);
    int size = file.st_size;
    //printf("%d\n", size);
    char store[size];
    int read_file = open("story.txt", O_RDONLY);
    read(read_file, store, size);
    printf("%s\n", store);
  }
  
  return 0;
}
