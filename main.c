#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[]){
	int key = ftok("control.c", 'R');
	int shmid, semid;
	char *data;
    
	// Creates shared memory
	shmid = shmget(key, 200, 0);
	data = shmat(shmid, (void *)0, 0);

	// Creates semaphore
	semid = semget(key, 1, 0);
    
	struct sembuf opp;
	opp.sem_flg = SEM_UNDO;
	opp.sem_num = 0;
	
	opp.sem_op = -1;
	semop(semid,&opp,1); //down
	
	struct stat file;
	stat("story.txt", &file);
	int size = file.st_size;
	char store[size];
	int read_file = open("story.txt", O_RDWR | O_APPEND);
	read(read_file, store, size);

	if(*data){
		char sad[*data];
		lseek(read_file, -1* *data, SEEK_END);
		read(read_file, sad, *data);
		printf("Previous line: %s\n", sad);
	}
	printf("Enter Next line:\n");
	
	char line[255];
	fgets(line,255,stdin);
	int i;
	for(i=0;line[i];i++);
	*data=i;

	//printf("data:%d\n",*data);
	
	write(read_file, line, *data);
	close(read_file);

	shmdt(data);
	
	opp.sem_op = 1;
	semop(semid,&opp,1); //up

	return 0;
}
