#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

bool valid_in_row(int* array, int x, int index){
	for(int i = 0; i<9; i++){
		if(array[(index/9)*9 + i] == x){
			return false;
		}
	}
	return true;
}

bool valid_in_col(int* array, int x, int index){
	for(int i = 0; i<9; i++){
		if(array[index%9 + i*9] == x){
			return false;
		}
	}
	return true;
}

bool valid_in_sq(int* array, int x, int index){
	for(int i = 0; i<9; i++){
		if(array[((index/27)*27) + ((index%9)/3)*3 + i%3 + (i/3)*9] == x){
			return false;
		}
	}
	return true;
}

void print_sudoku(int* array){
	for(int i=0; i<81; i++) {
			if(i%27 == 0){
				printf("|\n- - - - - - - - - - - - -\n");
			} else {
				if(i%9 == 0){
					printf("|\n");
				}
			}
			if(i%3 == 0){
				printf("| ");
			}
			printf("%i ",array[i]);
		}
	printf("|\n- - - - - - - - - - - - -\n");
}
int main(){
	int debug = 0;
	int sudo[] = {
		1,3,0,0,6,0,0,2,5,
		0,0,0,0,5,0,0,0,0,
		0,0,6,1,0,7,9,0,0,
		0,0,5,6,3,9,4,0,0,
		0,0,0,0,0,0,0,0,0,
		9,0,2,0,4,0,3,0,7,
		0,5,0,8,0,3,0,7,0,
		0,0,7,0,0,0,8,0,0,
		4,0,0,0,0,0,0,0,6
	};
	int sudo_r[] = {
		1,3,0,0,6,0,0,2,5,
		0,0,0,0,5,0,0,0,0,
		0,0,6,1,0,7,9,0,0,
		0,0,5,6,3,9,4,0,0,
		0,0,0,0,0,0,0,0,0,
		9,0,2,0,4,0,3,0,7,
		0,5,0,8,0,3,0,7,0,
		0,0,7,0,0,0,8,0,0,
		4,0,0,0,0,0,0,0,6
	};

	
	int sudo_test[] = {
		1,3,8,9,6,4,7,2,5,
		7,2,9,3,5,8,6,4,1,
		5,4,6,1,2,7,9,3,8,
		8,0,5,6,3,9,4,0,0,
		0,0,0,0,0,0,0,0,0,
		9,0,2,0,4,0,3,0,7,
		0,5,0,8,0,3,0,7,0,
		0,0,7,0,0,0,8,0,0,
		4,0,0,0,0,0,0,0,6
	};
	
	for(int i=0; i<81; i++) {
		if(i%27 == 0){
			printf("|\n- - - - - - - - - - - - -\n");
		} else {
			if(i%9 == 0){
				printf("|\n");
			}
		}
		if(i%3 == 0){
			printf("| ");
		}
		printf("%i ",sudo[i]);
	}
	printf("|\n- - - - - - - - - - - - -\n");
	
	if(debug){
		for(int i=0; i<81; i++) {
			if(i%27 == 0){
				printf("|\n-T-E-S-T-E- - - - - - - -\n");
			} else {
				if(i%9 == 0){
					printf("|\n");
				}
			}
			if(i%3 == 0){
				printf("| ");
			}
			printf("%i ",sudo_test[i]);
		}
		printf("|\n- - - - - - - - - - - - -\n");
		
		printf("Rows------------------\n");
		for(int i=1; i<10; i++){
			printf("%i : %i\n",i, valid_in_row(sudo_test, i, 28));
		}
		printf("\nColumns------------------\n");
		for(int i=1; i<10; i++){
			printf("%i : %i\n",i, valid_in_col(sudo_test, i, 28));
		}
		printf("\nSquares-----------------\n");
		for(int i=1; i<10; i++){
			printf("%i : %i\n",i, valid_in_sq(sudo_test, i, 28));
		}
	}
	

	unsigned int ind = 0;
	bool found = true;
	unsigned int contador = 0;
	/*for(int ind=0 ; ind < 81; ind++){
		for(int i=0; i<9; i++){
			printf("%i -",(((ind/27)*3 + (ind%9)/3)*3) + i%3 + ((i%9)/3)*9);
		}
		printf("\n ind %i\n",ind);
	}*/
	
	while(ind < 81){
		++contador;
		if(sudo[ind] == 0){
			found = false;
			for(int n = sudo_r[ind] + 1; n<10; n++){
				if(valid_in_row(sudo_r,n,ind) & valid_in_col(sudo_r,n,ind) & valid_in_sq(sudo_r,n,ind)){
					sudo_r[ind] = n;
					found = true;
					break;
				}
			}
		} else {
			sudo_r[ind] = sudo[ind];
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
	if(ind==81){
		print_sudoku(sudo_r);
		printf("%u Iterations\n", contador);
	} else {
		printf("%u Iterations\n", contador);
		printf("This puzzle has no solution\n");
	}
	
	
	//if(valid_in_row(sudo,n,i/9) & valid_in_col(sudo,n,i%9) & valid_in_sq(sudo,n,(i%9)/3 + (i/27)*3)){
	
	
	
	
	
	
	
	
}