#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <pthread.h>


struct myData{
	unsigned int start_value;
	unsigned int start_ind;
	unsigned int size;
};
/*
int sudo[] = {
		1,3,0,0,6,0,0,2,5,
		0,0,0,0,5,0,0,0,0,
		0,0,6,1,0,7,9,0,0,
		0,0,5,6,3,9,4,0,0,
		0,0,0,0,0,0,0,0,0,
		9,0,2,0,4,0,3,0,7,
		0,5,0,8,0,3,0,7,0,
		0,0,7,0,0,0,0,0,0,
		4,0,0,0,0,0,0,0,0
	};
	*/
	
int sudo[] = {
	0,0,0,15,9,0,16,0,0,6,0,0,13,7,0,0,
	0,13,6,0,0,15,0,0,7,0,0,4,8,0,0,0,
	2,0,0,0,0,0,0,13,15,0,10,0,0,3,9,0,
	7,0,5,6,3,0,0,0,12,0,0,0,0,14,11,
	0,5,0,0,0,11,8,0,0,0,0,15,3,0,0,0,
	0,6,0,1,10,0,5,0,11,0,2,0,12,14,0,0,
	0,0,16,0,0,0,0,3,12,0,0,8,0,6,7,0,
	3,0,0,10,0,6,0,0,0,13,1,0,0,0,0,8,
	12,0,0,0,0,5,2,0,0,0,8,0,0,15,1,0,
	0,0,1,9,4,0,0,0,0,15,0,0,7,0,0,0,
	0,8,2,0,3,0,0,16,0,14,7,0,0,0,0,5,
	0,7,0,0,0,0,15,6,1,0,0,10,0,12,8,0,
	8,0,0,13,16,0,0,11,0,0,15,0,0,0,4,7,
	0,9,0,0,0,0,7,0,0,11,0,16,14,0,0,0,
	0,11,3,0,15,12,0,0,8,0,0,0,0,10,0,0,
	1,0,4,0,0,0,3,0,0,2,0,6,16,0,0,15
};


bool valid_in_row(int* array, int x, int index, unsigned int size_sq){
	for(int i = 0; i<size_sq; i++){
		if(array[(index/size_sq)*size_sq + i] == x){
			return false;
		}
	}
	return true;
}

bool valid_in_col(int* array, int x, int index, unsigned int size_sq){
	for(int i = 0; i<size_sq; i++){
		if(array[index%size_sq + i*size_sq] == x){
			return false;
		}
	}
	return true;
}

bool valid_in_sq(int* array, int x, int index, unsigned int size){
	unsigned int size_sq = size*size;
	unsigned int size_cb = size*size_sq;
	for(int i = 0; i<size_sq; i++){
		if(array[((index/size_cb)*size_cb) + ((index%size_sq)/size)*size + i%size + (i/size)*size_sq] == x){
			return false;
		}
	}
	return true;
}

void print_sudoku(int* array, unsigned int size){
	unsigned int size_sq = size*size;
	unsigned int size_cb = size*size_sq;
	unsigned int size_qd = size*size_cb;
	for(int i=0; i<size_qd; i++) {
			if(i%size_cb == 0){
				printf("|\n- - - - - - - - - - - - -\n");
			} else {
				if(i%size_sq == 0){
					printf("|\n");
				}
			}
			if(i%size == 0){
				printf("| ");
			}
			printf("%i ",array[i]);
		}
	printf("|\n- - - - - - - - - - - - -\n");
}

void deep_copy(int size, int array[]){
	for(int i=0;i<size;i++){
		array[i] = sudo[i];
	}
}

void* sudoku_solver(void* args){
	int start_value = ((struct myData*)args)->start_value;
	int start_ind = ((struct myData*)args)->start_ind;
	unsigned int size = ((struct myData*)args)->size;
	unsigned int size_sq = size*size;
	unsigned int size_cb = size*size_sq;
	unsigned int size_qd = size*size_cb;
	int sudo_r[size_qd];
	deep_copy(size_qd, sudo_r);
	sudo_r[start_ind] = start_value;
	unsigned int ind = start_ind+1;
	bool found = true;
	unsigned int contador = 0;
	unsigned int solutions = 0;
	while(ind < size_qd && ind>start_ind){
		++contador;
		if(sudo[ind] == 0){
			found = false;
			for(int n = sudo_r[ind] + 1; n<size_sq+1; n++){
				if(valid_in_row(sudo_r,n,ind,size_sq) & valid_in_col(sudo_r,n,ind,size_sq) & valid_in_sq(sudo_r,n,ind,size)){
					sudo_r[ind] = n;
					found = true;
					break;
				}
			}
		} else {
			sudo_r[ind] = sudo[ind];
		}
		if(found){
			if(ind==size_qd-1){
				if(sudo[ind]==0){
					sudo_r[ind] = 0;
				}
				ind--;
				solutions++;
				print_sudoku(sudo_r,size);
			} else {
				ind++;
			}
		} else {
			if(sudo[ind]==0){
				sudo_r[ind] = 0;
			}
			ind--;
		}
	}
	printf("%u\n", ind);
	printf("%u", solutions);
	pthread_exit((void*)solutions);
}

int main(){
	unsigned int _size=4;
	pthread_t threads[_size];
	struct myData data[_size];
	for(int i=0; i<_size; i++){
		data[i].start_value = i+1;
		data[i].start_ind = 0;
		data[i].size = _size;
		pthread_create(&threads[i],NULL,sudoku_solver,(void*)&(data[0]));
	}
	
	unsigned int return_var;
	unsigned int sum_solutions=0;
	for(int i=0; i<_size; i++){
		pthread_join(threads[i],(void**)return_var);
		sum_solutions += *((int*)return_var);
	}
}


















