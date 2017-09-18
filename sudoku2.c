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
/*
int sudo[] = {
		0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,
		
	};*//*
	int sudo[] = {
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
};*/

	int sudo[] = {
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
/*
	int sudo[] = {
	0, 0, 0, 0, 0, 0, 0, 0,0, 0, 0, 0,0,0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,0, 0, 0, 0,0,0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,0, 0, 0, 0,0,0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,0, 0, 0, 0,0,0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,0, 0, 0, 0,0,0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,0, 0, 0, 0,0,0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,0, 0, 0, 0,0,0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,0, 0, 0, 0,0,0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,0, 0, 0, 0,0,0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,0, 0, 0, 0,0,0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,0, 0, 0, 0,0,0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,0, 0, 0, 0,0,0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,0, 0, 0, 0,0,0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,0, 0, 0, 0,0,0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,0, 0, 0, 0,0,0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,0, 0, 0, 0,0,0, 0, 0,
};*/

/*
int sudo[] = {
 0, 1 ,3 ,4, 5, 6, 7, 8,  9, 10, 11, 12,  13, 14, 15, 16, 
 5 ,6 ,7 ,8,1 ,2 ,3 ,4  ,13 ,14 ,15 ,16 , 9 ,10, 11, 12 ,
 9 ,10 ,11 ,12 , 13, 14 ,15, 16,  1 ,2 ,3 ,4 , 5, 6, 7, 8 ,
 13, 14, 15, 16,  9, 10 ,11 ,12  ,5, 6, 7 ,8  ,1 ,2 ,3 ,4 ,
 1 ,2, 4, 3 , 6 ,5, 8, 7 , 10, 9 ,12 ,11 ,14 ,13 ,16 ,15, 
 6 ,5, 8, 7 , 2 ,1, 4, 3  ,14 ,13 ,16 ,15 ,10, 9 ,12, 11 ,
 10, 9 ,12 ,11 , 14, 13, 16, 15, 2, 1, 4, 3,  6, 5, 8, 7, 
 14, 13, 16, 15,  10, 9 ,12 ,11, 6, 5, 8, 7,  2 ,1, 4 ,3, 
 3 ,4 ,1, 2 , 7 ,8, 5 ,6,  11, 12 ,9 ,10, 15, 16, 13, 14, 
 7 ,8 ,5, 6 , 3 ,4, 1 ,2 , 15, 16, 13, 14, 11, 12, 9, 10 ,
 11, 12, 9 ,10 , 15 ,16 ,13, 14 , 3 ,4 ,1 ,2 ,7 ,8 ,5 ,6, 
 15, 16, 13, 14,  11 ,12 ,9 ,10  ,7 ,8 ,5 ,6 ,3 ,4,1, 2, 
 4 ,3 ,2, 1 , 8 ,7 ,6, 5,  12, 11 ,10, 9 , 16, 15, 14 ,13, 
 8 ,7 ,6, 5 , 4 ,3 ,2 ,13 , 16 ,15 ,14 ,1  ,12 ,11 ,10, 9 ,
 12, 15, 10, 9  ,16 ,11 ,14 ,1 , 4 ,7 ,6 ,13 , 8, 3 ,2 ,5 ,
 16, 11, 14, 13 , 12 ,15 ,10 ,9  ,8 ,3 ,2 ,5 , 4, 7, 6, 1 
};*/



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
				printf("|\n- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n");
			} else {
				if(i%size_sq == 0){
					printf("|\n");
				}
			}
			if(i%size == 0){
				printf("| ");
			}
			printf("%02i ",array[i]);
		}
	printf("|\n- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n");
}

void deep_copy(int size, int array[]){
	for(int i=0;i<size;i++){
		array[i] = sudo[i];
	}
}

void* sudoku_solver(void* args){
	
	fflush(stdout);
	unsigned int start_value = ((struct myData*)args)->start_value;
	unsigned int start_ind = ((struct myData*)args)->start_ind;
	unsigned int size = ((struct myData*)args)->size;
	unsigned int size_sq = size*size;
	unsigned int size_cb = size*size_sq;
	unsigned int size_qd = size*size_cb;
	int sudo_r[size_qd];
	unsigned int solutions = 0;
	deep_copy(size_qd, sudo_r);


	unsigned low = 256;
	bool meas = false;
	bool huh = true;
	unsigned int test[size_qd];

	printf("Created thread %u\n", start_value);
	if(valid_in_row(sudo_r,start_value,start_ind,size_sq) & valid_in_col(sudo_r,start_value,start_ind,size_sq) & valid_in_sq(sudo_r,start_value,start_ind,size)){
		sudo_r[start_ind] = start_value;
		unsigned int ind = start_ind+1;
		bool found = true;
		unsigned int contador = 0;
		
		while(ind < size_qd && ind>start_ind){
			contador++;
			if (sudo[ind]==0) {
				found=false;
				for(int n = sudo_r[ind]+1; n<size_sq+1; n++){
					if(valid_in_row(sudo_r,n,ind,size_sq) & valid_in_col(sudo_r,n,ind,size_sq) & valid_in_sq(sudo_r,n,ind,size)){
						found=true;
						sudo_r[ind]=n;
						break;
					}
				}
			}
			if(found){
				if(ind == size_qd - 1){
					printf("Found One! - at %u\n",contador);
					fflush(stdout);
					print_sudoku(sudo_r, size);
					fflush(stdout);
					solutions++;
					if(sudo[ind]==0){
						sudo_r[ind] = 0;
					}
					found=false;
					ind--;
				} else {
					ind++;
				}
			} else {
				if(sudo[ind]==0){
					sudo_r[ind] = 0;
				}
				sudo_r[ind]=sudo[ind];
				ind--;
			}/*
			if(sudo_r[55]==8 && 
				sudo_r[56]==2 && sudo_r[57]==12 && sudo_r[58]==9 && sudo_r[59]==13 && 
				sudo_r[60]==15 && sudo_r[61]==1 && sudo_r[62]==14 && sudo_r[63]==11 && 
				sudo_r[64]==14 && sudo_r[65]==5 && sudo_r[66]==7 && sudo_r[67]==2 && 
				sudo_r[68]==12 && sudo_r[69]==11 && sudo_r[70]==8 && sudo_r[71]==1 && 
				sudo_r[72]==9 && sudo_r[73]==4 && sudo_r[74]==6 && sudo_r[75]==15 && 
				sudo_r[76]==3 && sudo_r[77]==16 && sudo_r[78]==10 && sudo_r[79]==13 && 
				sudo_r[80]==4 && sudo_r[81]==6 && sudo_r[82]==13 && sudo_r[83]==1 && 
				sudo_r[84]==10 && sudo_r[85]==9 && sudo_r[86]==5 && sudo_r[87]==7 && 
				sudo_r[88]==11 && sudo_r[89]==16 && sudo_r[90]==2 && sudo_r[91]==3 && 
				sudo_r[92]==12 && sudo_r[93]==14 && sudo_r[94]==15 
				){
				*/
		}
	}
	printf("Done with %u\n",start_value);
	fflush(stdout);
	pthread_exit((void*)solutions);
}



int main(){
	unsigned int _size=4;
	pthread_t threads[_size*_size];
	struct myData data[_size*_size];
	printf("Creating threads\n");
	fflush(stdout);
	for(int i=0; i<_size*_size; i++){
		data[i].start_value = i+1;
		data[i].start_ind = 0;
		data[i].size = _size;
		pthread_create(&threads[i],NULL,sudoku_solver,(void*)&(data[i]));
	}
	printf("Created threads\n");
	fflush(stdout);
	void* return_var;
	unsigned int sum_solutions=0;
	for(int i=0; i<_size*_size; i++){
		pthread_join(threads[i],&return_var);
		fflush(stdout);
		sum_solutions += (unsigned int)return_var;
	}
	printf("%u\n", sum_solutions);
	fflush(stdout);
}










