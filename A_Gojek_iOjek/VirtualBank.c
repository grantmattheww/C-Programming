#include <stdio.h>
#include <windows.h>
#include <time.h>

struct databank{
	long long int rekening; int saldo;
	char nama[100];
};

int searchRek(struct databank *data, int n, long long int search){
	int i;
	for (i=0; i<n; i++){
		if (search ==  data[i].rekening) return i;
	}
	return -1;
}


int main(){
	char namaAnda[100];
	int saldomasuk, saldo=0, counter=0; 
	long long int rekening;
	int varCari, cari, i;
	
	time_t t = time(NULL);
	struct tm tm = *localtime(&t);
	
	int tanyasatu,tanyadua,isisaldo=0;
	
	struct databank data[100];
	
	do{
		counter=0;
		FILE *file = fopen("databank.txt", "r");
		while(!feof(file)){
			fscanf(file, "%lld#%[^#]#%d\n", &data[counter].rekening, data[counter].nama, &data[counter].saldo);
			counter++;
		}
		fclose(file);
		
		
		
		printf("================================================\n");
		printf("               VirtualBank\n");
		printf("================================================\n");
		printf("Sudah memiliki akun [Y/N] ? ");tanyasatu=getchar();fflush(stdin);
		if(tanyasatu == 'y' || tanyasatu == 'Y'){
			printf ("\n Rekening\t\t: ");
			scanf ("%lld", &rekening);fflush(stdin);
			varCari = searchRek(data, counter, rekening);
			printf(" Saldo Anda\t\t: %d\n",data[varCari].saldo);
			printf("\n Isi ulang sekarang [Y/N] ? ");tanyadua=getchar();fflush(stdin);
			if(tanyadua == 'y' || tanyadua == 'Y'){
				printf(" Saldo yang di isi\t: ");scanf("%d",&saldo);
				if (varCari!=-1){ data[varCari].saldo += saldo;printf ("\n Saldo berhasil ditambah\n");system("pause");}else{ printf ("\n Rekening Tidak Tersedia\n");system("pause"); }
				
				FILE *fput = fopen("databank.txt", "w+");
				for(i=0;i<counter;i++){
					fprintf(fput, "%lld#%s#%d\n",data[i].rekening, data[i].nama, data[i].saldo);	
				}
				fclose(fput);
			}
			system("cls");
		}else if(tanyasatu == 'n' || tanyasatu == 'N'){
			printf("\nCatatan : tolong ingat nomor rekening anda untuk keperluan transaksi.\n");
			printf(" Rekening Anda\t: ");
			printf("%02d%02d%d%d%d%d\n", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900, tm.tm_hour, tm.tm_min, tm.tm_sec);
			printf(" Nama Anda\t: ");scanf("%s",namaAnda);fflush(stdin);
			printf(" Isi saldo Anda\t: ");scanf("%d",&isisaldo);fflush(stdin);
			
			FILE *fput = fopen("databank.txt", "a");
			fprintf(fput, "%02d%02d%d%02d%02d%02d#%s#%d\n", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900, tm.tm_hour, tm.tm_min, tm.tm_sec, namaAnda, isisaldo);
			fclose(fput);
			system("cls");
		}else{ system("cls"); }
	}while(1);



return 0;
}
