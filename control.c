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
	char *input = argv[1];
	//printf("%s,%s \n", input, argv[1]);
      	int key = ftok("control.c", 'R');
	int shmid, semid;
	char *data;
	union semun su;

	struct sembuf opp;
	opp.sem_flg = SEM_UNDO;
	opp.sem_num = 0;
	
	//printf("%s, %d\n", input, strcmp(input, "-c"));
	if(!strcmp(input, "-c")){ // make the shared memory, semaphore and file
		// Creates semaphore
		su.val = 1;
		semid = semget(key, 1, IPC_CREAT | IPC_EXCL | 0644);
		semctl(semid, 0, SETVAL, su);
		opp.sem_op = -1;
		semop(semid,&opp,1); //down

		// Creates shared memory
		shmid = shmget(key, 200, IPC_CREAT | IPC_EXCL | 0644);
		data = shmat(shmid, (void *)0, 0);
		*data = 0;
		// Creates new file with O_TRUNC
		int file_out = open("story.txt", O_CREAT | O_TRUNC, 0666);
		close(file_out);
		shmdt(data);
		opp.sem_op = 1;
		semop(semid,&opp,1); //up

		
	} else if(!strcmp(input, "-r")){ // Remove the shared memory, the semaphore and the story.
		semid = semget(key, 1, 0);
		opp.sem_op = -1;
		semop(semid,&opp,1); //down

		// Deletes shared memory
		shmid = shmget(key, 200, 0);
	    shmctl(shmid, IPC_RMID, NULL);

		//Prints out story and then deletes it
		struct stat file;
		stat("story.txt", &file);
		int size = file.st_size;
		//printf("%d\n", size);
		char store[size];
		int read_file = open("story.txt", O_RDONLY);
		read(read_file, store, size);
		close(read_file);
		printf("Story: %s\n", store);
		remove("story.txt");

		opp.sem_op = 1;
		semop(semid,&opp,1); //up
		
		// Deletes semaphore
		semctl(semid, 0, IPC_RMID);
		
	} else if(!strcmp(input, "-v")){ // Output the contents of the story file.
		//printf("%d\n", strcmp(input, "-v"));

		opp.sem_op = -1;
		semop(semid,&opp,1); //down
		
		struct stat file;
		stat("story.txt", &file);
		int size = file.st_size;
		//printf("%d\n", size);
		char store[size];
		int read_file = open("story.txt", O_RDONLY);
		read(read_file, store, size);
		printf("%s\n", store);
		close(read_file);
		
		opp.sem_op = 1;
		semop(semid,&opp,1); //up
	}
  
	return 0;
}
