#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>

#define MAX_n 8

int n;
int nsq;
int ncb;
int nqd;

bool valid_in_row(int* array, int x, int index){
	for(int i = 0; i<nsq; i++){
		if(array[(index/nsq)*nsq + i] == x){
			return false;
		}
	}
	return true;
}

bool valid_in_col(int* array, int x, int index){
	for(int i = 0; i<nsq; i++){
		if(array[index%nsq + i*nsq] == x){
			return false;
		}
	}
	return true;
}

bool valid_in_sq(int* array, int x, int index){
	for(int i = 0; i<nsq; i++){
		if(array[((index/ncb)*ncb) + ((index%nsq)/n)*n + i%n + (i/n)*nsq] == x){
			return false;
		}
	}
	return true;
}

void print_sudoku(int* array){
	for(int i=0; i<nqd; i++) {
			if(i%ncb == 0){
				printf("|\n- - - - - - - - - - - - -\n");
			} else {
				if(i%nsq == 0){
					printf("|\n");
				}
			}
			if(i%n == 0){
				printf("| ");
			}
			printf("%i ",array[i]);
		}
	printf("|\n- - - - - - - - - - - - -\n");
}
int main(){

	assert(scanf("%d", &n) == 1);
	assert (n <= MAX_n);

	nsq = n * n;
	ncb = n * nsq;
	nqd = n * ncb;
	int sudo[nqd];
	int sudo_r[nqd];

	for (int i = 0; i < nqd; i++) {
	    if (scanf("%d", &sudo[i]) != 1) {
	    	printf("error reading file (%d)\n", i);
	    	exit(1);
	    }
	}
	memcpy(sudo_r, sudo, sizeof(int)*nqd);


	unsigned int ind = 0;
	bool found = true;
	unsigned int contador = 0;

	while(ind < nqd){
		if(sudo[ind] == 0){
			found = false;
			for(int i = sudo_r[ind] + 1; i<nsq+1; i++){
				if(valid_in_row(sudo_r,i,ind) & valid_in_col(sudo_r,i,ind) & valid_in_sq(sudo_r,i,ind)){
					sudo_r[ind] = i;
					found = true;
					break;
				}
			}
		} else {
			sudo_r[ind] = sudo[ind];
		}
		if(ind==nqd-1){
			if(found){
				contador++;
				
			}
			found = false;			
		}
		if(found){
			ind++;
		} else {
			if(sudo[ind]==0){
				sudo_r[ind] = 0;
			}
			ind--;
		}
	}
	
	printf("Solutions: %u", contador);
}