#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>
#include "stack.h"
#include "semaphore.h"

#define MIN(a,b) ((a) < (b) ? a : b)
#define MAX_size 8

sem_t semaphoreSentinela;
sem_t semaphoreConsumidor;
sem_t semaphoreP;
sem_t semaphoreCont;
pthread_barrier_t barrier;
Stack s;

unsigned int size = 4;
unsigned int size_sq;
unsigned int size_cb;
unsigned int size_qd;

unsigned int max_threads;
unsigned int solutions = 0;
/*
unsigned char sudo[] = {
		0,3,0,0,6,0,0,0,5,
		0,0,0,0,5,0,0,0,0,
		0,0,6,1,0,7,9,0,0,
		0,0,5,6,3,9,4,0,0,
		0,0,0,0,0,0,0,0,0,
		9,0,2,0,4,0,0,3,7,
		0,5,0,8,0,3,0,7,0,
		0,0,7,0,0,0,0,0,0,
		4,0,0,0,0,0,0,0,6
};*/

unsigned char sudo[] = {
	 0, 0, 0,15, 9, 0,16, 0, 0, 6, 0, 0,13, 7, 0, 0,
	 0,13, 6, 0, 0,15, 0, 0, 7, 0, 0, 4, 8, 0, 0, 0,
	 2, 0, 0, 0, 0, 0, 0,13,15, 0,10, 0, 0, 3, 9, 0,
	 7, 0, 5, 0, 6, 3, 0, 0, 0,12, 0, 0, 0, 0,14,11,
	 0, 5, 0, 0, 0,11, 8, 0, 0, 0, 0,15, 3, 0, 0, 0,
	 0, 6, 0, 1,10, 0, 5, 0,11, 0, 2, 0,12,14, 0, 0,
	 0, 0,16, 0, 0, 0, 0, 3,12, 0, 0, 8, 0, 6, 7, 0,
	 3, 0, 0,10, 0, 6, 0, 0, 0,13, 1, 0, 0, 0, 0, 8,
	12, 0, 0, 0, 0, 5, 2, 0, 0, 0, 8, 0, 0,15, 1, 0,
	 0, 0, 1, 9, 4, 0, 0, 0, 0,15, 0, 0, 7, 0, 0, 0,
	 0, 8, 2, 0, 3, 0, 0,16, 0,14, 7, 0, 0, 0, 0, 5,
	 0, 7, 0, 0, 0, 0,15, 6, 1, 0, 0,10, 0,12, 8, 0,
	 8, 0, 0,13,16, 0, 0,11, 0, 0,15, 0, 0, 0, 4, 7,
	 0, 9, 0, 0, 0, 0, 7, 0, 0,11, 0,16, 4, 0, 0, 0,
	 0,11, 3, 0,15,12, 0, 0, 8, 0, 0, 0, 0,10, 0, 0,
	 1, 0, 4, 0, 0, 0, 3, 0, 0, 2, 0, 6,16, 0, 0,15
};

bool valid_in_row(unsigned char* array, unsigned char x, int index){
	for(int i = 0; i < size_sq; i++){
		if(array[(index/size_sq)*size_sq + i] == x)
			return false;
	}
	return true;
}

bool valid_in_col(unsigned char* array, unsigned char x, int index){
	for(int i = 0; i < size_sq; i++){
		if(array[index%size_sq + i*size_sq] == x)
			return false;
	}
	return true;
}

bool valid_in_sq(unsigned char* array, unsigned char x, int index){
	for(int i = 0; i < size_sq; i++){
		if(array[((index/size_cb)*size_cb) + ((index%size_sq)/size)*size + i%size + (i/size)*size_sq] == x)
			return false;
	}
	return true;
}

void* sudoku_solver(void* args){

	unsigned char* sudo_r;
	int sem_check;
	bool found;
	bool next;

	while(1){
		
		sem_getvalue(&semaphoreSentinela, &sem_check);
		if(s.size == 0 && sem_check == max_threads){
			sem_wait(&semaphoreP);
			printf("Found %u solutions!\n", solutions);
			fflush(stdout);
			exit(0);
		}
		sem_wait(&semaphoreConsumidor);
		sem_post(&semaphoreSentinela);

		Data *stack = stackpop(&s);
		unsigned int start_ind = stack->start_ind;

		unsigned int start_line = (start_ind/size_sq);//*s.multiplier;
		unsigned int criterio = (start_ind/size_sq)+size_sq*size_qd*s.size/2000000000;
		//printf("Size %u  -- Lines %u\n",s.size, size_sq*size_qd*s.size/2000000000);
		//fflush(stdout);
		unsigned int ind = start_ind;
		sudo_r = malloc(sizeof(unsigned char) * size_qd);
		memcpy(sudo_r, stack->state, sizeof(unsigned char)*size_qd);

		found = true;
		next = true;
		while(ind/size_sq >= start_line && ind/size_sq <= criterio){
			if(stack->state[ind] == 0){
				found = false;
				for(unsigned char n = sudo_r[ind]+1; n < size_sq+1; n++){
					if(valid_in_row(sudo_r, n, ind) & 
						valid_in_col(sudo_r, n, ind) & 
						valid_in_sq(sudo_r, n, ind)){
							found = true;
							sudo_r[ind] = n;
							break;
					}
				}
				next = found;
			}
			if(found){
				if(ind == size_qd-1){
						sem_wait(&semaphoreCont);
						solutions++;
						printf("%u\n", solutions);
						fflush(stdout);
						sem_post(&semaphoreCont);
						next=false;
				} else {
					if((ind+1)/size_sq > criterio){
						unsigned char* temp_sudoku = malloc(sizeof(unsigned char) * size_qd);
						memcpy(temp_sudoku, sudo_r, sizeof(unsigned char) * size_qd);
						Data* temp = malloc(sizeof(Data));
						temp->state = temp_sudoku;
						temp->start_ind = ind+1;
						stackpush(&s, temp);
						sem_post(&semaphoreConsumidor);
						next=false;
					}
				}
			}
			if (next) {
				ind++;
			} else {
				if(stack->state[ind]==0){
					sudo_r[ind] = 0;
				}
				ind--;
			}
		}
		free(stack->state);
		free(sudo_r);
		sem_wait(&semaphoreSentinela);
	}
}

int main(int argc, char *argv[]){

	max_threads = atoi(argv[1]);
/*	assert(scanf("%d", &size) == 1);
	assert (size <= MAX_size);*/

	size_sq = size * size;
	size_cb = size * size_sq;
	size_qd = size * size_cb;
	
/*	int sudo[size_qd];
	for (int i = 0; i < size_qd; i++) {
	    if (scanf("%d", &sudo[i]) != 1) {
	    	printf("error reading file (%d)\n", i);
	    	exit(1);
	    }
	}*/

	stackinit(&s);
	sem_init(&semaphoreConsumidor, 0, 1);
	sem_init(&semaphoreSentinela, 0, max_threads);
	sem_init(&semaphoreCont, 0, 1);
	sem_init(&semaphoreP, 0, 1);
	pthread_barrier_init(&barrier, NULL, 10);
	
	printf("Initialized structures\n");
	fflush(stdout);
	
	Data initial_data;
	unsigned char* ini_array = malloc(sizeof(unsigned char)*(size_qd));
	memcpy(ini_array, sudo, sizeof(unsigned char)*(size_qd));
	initial_data.state = ini_array;
	initial_data.start_ind = 0;	
	stackpush(&s, &initial_data);

	printf("Created first stack entry\n");
	fflush(stdout);
	
	pthread_t threads[max_threads];
	for(int i=0; i<max_threads; i++){
		pthread_create(&threads[i], NULL, sudoku_solver, NULL);
	}
	
	printf("Created threads\n");
	fflush(stdout);
	printf("%i threads created\n", max_threads);
	fflush(stdout);
	printf("---- %u -----\n", s.multiplier);
	
	pthread_barrier_wait(&barrier);
	free(ini_array);
	
	printf("Found %u solutions.\n", solutions);
	fflush(stdout);

	fflush(stdout);

	sem_destroy(&semaphoreConsumidor);
	sem_destroy(&semaphoreSentinela);
	sem_destroy(&semaphoreCont);
	sem_destroy(&semaphoreP);
}