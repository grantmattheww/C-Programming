#include <stdio.h>
#include <windows.h>
#include <time.h>

struct pendapatan{
	char tgl[11]; 
	int harga,iddriver,idperjalanan;
};

struct driver{ int idDriv;char namaDriv[150], nohpDriv[15], almtDriv[250], plat[15], motor[50],userDriv[50],passDriv[50];};
/*struct databank{
	long long int rekening; int saldo;
	char nama[100];
};

int searchRek(struct databank *data, int n, long long int search){
	int i;
	for (i=0; i<n; i++){
		if (search ==  data[i].rekening) return i;
	}
	return -1;
}*/

// <!--  START OF SORT DATE FOR DATA PENDAPATAN
void sortDateOfPendapatan(struct pendapatan *db, int jumlah , int kondisi){
    int i,j;
	struct pendapatan temp;
    
		for(i=1;i<jumlah;i++){
			temp = db[i];
			j = i-1;
			if(kondisi == 0){
				while(strcmp(db[j].tgl, temp.tgl) > 0 && j >= 0){
					db[j+1] = db[j];
					j = j-1;
				}	
			}else if(kondisi == 1){
				while(strcmp(db[j].tgl, temp.tgl) < 0 && j >= 0){
					db[j+1] = db[j];
					j = j-1;
				}
			}else if(kondisi == 2){
				while(db[j].tgl > temp.tgl && j >= 0){
					db[j+1] = db[j];
					j = j-1;
				}	
			}else if(kondisi == 3){
				while(db[j].tgl < temp.tgl && j >= 0){
					db[j+1] = db[j];
					j = j-1;
				}
			}else if(kondisi == 4){
				while(db[j].iddriver > temp.iddriver && j >= 0){
					db[j+1] = db[j];
					j = j-1;
				}	
			}else if(kondisi == 5){
				while(db[j].iddriver < temp.iddriver && j >= 0){
					db[j+1] = db[j];
					j = j-1;
				}
			}else if(kondisi == 6){
				while(db[j].idperjalanan > temp.idperjalanan && j >= 0){
					db[j+1] = db[j];
					j = j-1;
				}	
			}else if(kondisi == 7){
				while(db[j].idperjalanan < temp.idperjalanan && j >= 0){
					db[j+1] = db[j];
					j = j-1;
				}
			}
	        db[j+1] = temp;
	    }
    
    	
    	printf("  %-12s %-9s %-20s %-14s \n","Tanggal","Harga","Driver","No Perjalanan.");
		for(i=0;i<jumlah;i++){
			printf("  %-12s %-9d %-20d %-14d \n",db[i].tgl,db[i].harga,db[i].iddriver,db[i].idperjalanan);
		}
    
}
// <!-- END OF FUNCTION -->


int main(){
	char nama[100];
	int counter=0,counter1=0; 
	int  i,j,flag,pilih,cashIn=0;;
	
	time_t t = time(NULL);
	struct tm tm = *localtime(&t);
	
	struct pendapatan pendapatan[200];
	struct driver driver[100];
	
	do{
		flag=0;
		do{
			printf("======================================================================\n\n");
			printf("  Pendapatan iOjek                             [%02d/%02d/%d %02d:%02d:%02d]\n\n",tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900, tm.tm_hour, tm.tm_min, tm.tm_sec);
			printf("======================================================================\n\n");
			counter=0;cashIn=0;
			FILE *file = fopen("pendapataniojek.txt", "r");
			while(!feof(file)){
				fscanf(file, "%[^#]#%d#%d#%d\n", pendapatan[counter].tgl, &pendapatan[counter].harga, &pendapatan[counter].iddriver, &pendapatan[counter].idperjalanan);
				cashIn+=pendapatan[counter].harga;
				counter++;
			}
			fclose(file);
			
			counter1=0;
			FILE *fdriv = fopen("driver.txt", "r");
			while(!feof(fdriv)){
				fscanf(file, "%d#%[^#]#%[^#]#%[^#]#%[^#]#%[^#]#%[^#]#%[^\n]\n", &driver[counter1].idDriv,driver[counter1].namaDriv, driver[counter1].nohpDriv, driver[counter1].almtDriv, driver[counter1].plat,driver[counter1].motor,driver[counter1].userDriv, driver[counter1].passDriv);
				counter1++;
			}
			fclose(fdriv);
			printf("      == Data Driver ==\n\n");
			printf("    %-9s    %-20s  \n","ID Driver","Nama");
			for(j=0;j<counter1;j++){
				printf("    %-9d    %-20s\n",driver[j].idDriv,driver[j].namaDriv);
			}
				
			printf("\n\n======================================================================\n\n");
			printf("                      == Data Penghasilan ==\n\n");
			printf("\n  Total Penghasilan : %d\n\n",cashIn);
			sortDateOfPendapatan(pendapatan,counter,flag);
			printf("\n======================================================================\n\n");
			printf("  Sort berdasarkan tanggal           Sort berdasarkan harga\n   1. Asc // 2. Desc                  3. Asc // 4. Desc\n\n");
			printf("  Sort berdasarkan driver (id)       Sort berdasarkan perjalanan\n   5. Asc // 6. Desc                  7. Asc // 8. Desc\n\n");
			printf("======================================================================\n\n");
			printf("  Pilih : ");scanf("%d",&pilih);fflush(stdin);
			printf("\n");
			
			if(pilih == 1){
				flag=0;sortDateOfPendapatan(pendapatan,counter,flag);system("cls");
			}else if(pilih == 2){
				flag=1;sortDateOfPendapatan(pendapatan,counter,flag);system("cls");
			}else if(pilih == 3){
				flag=2;sortDateOfPendapatan(pendapatan,counter,flag);system("cls");
			}else if(pilih == 4){
				flag=3;sortDateOfPendapatan(pendapatan,counter,flag);system("cls");
			}else if(pilih == 5){
				flag=4;sortDateOfPendapatan(pendapatan,counter,flag);system("cls");
			}else if(pilih == 6){
				flag=5;sortDateOfPendapatan(pendapatan,counter,flag);system("cls");
			}else if(pilih == 7){
				flag=6;sortDateOfPendapatan(pendapatan,counter,flag);system("cls");
			}else if(pilih == 8){
				flag=7;sortDateOfPendapatan(pendapatan,counter,flag);system("cls");
			}else system("cls");
			
		}while(1);
		
	}while(1);

return 0;
}
