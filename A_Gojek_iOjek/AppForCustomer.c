#include <stdio.h>
#include <windows.h>
#include <time.h>

// <!-- FUNGSI INI UNTUK MENAMPILKAN LOADING PADA SAAT PROGRAM PERTAMA KALI DI JALANKAN -->
void loading(){
	int i,j;
	for(i=0;i<20;i++){
		puts  ("==========================================================\n\n\n");
		logo();
		printf("\n\n");
		printf("                       Loading ...                        ");
		printf("\n                  ");
		for(j=0;j<20;j++){
			if(i>j)
			printf("*");
			else
			printf(" ");
		}
		printf("\n\n\n");
		puts  ("==========================================================\n\n");
		if(i<10) Sleep(500);
		else Sleep(250);
		system("cls");
	}
}
// <!-- END OF FUNCTION -->

// <!-- START MAKE LOGO -->
void logo(){
	printf("                        `##                               \n");
	printf("                        ';;+                              \n");
	printf("                        '';`                              \n");
	printf("                        +'.                               \n");
	printf("   ';   .@+'@@         .';` +@         @   @';:  :#   @   \n");
	printf("       .@    ##        +++: `.:        @   @     ,#  @`   \n");
	printf("   ':  @      @        :;;+;:::        @   @     ,+ @     \n");
	printf("   ':  @      @        ;:, +++.        @   @;'   ,+@      \n");
	printf("   ':  @      @   +,+#::::++++,        @   @     ,+'@     \n");
	printf("   ':  @     .@    #''++'::++#`'@`    `#   @     ,+ +@    \n");
	printf("   ';  '@    @    # ,. +++;:: @.#@    #,   @     ,#  #@   \n");
	printf("   +;   :@@@@    +`@::@:+++':+@. .+  ;@    @@@@  ,#   #   \n");
	printf("                 `@```#.+.,'.+ @; @  + `                  \n");
	printf("                  @ #`;. ,..``@` +:                       \n");
	printf("                  #,  @       ;@@+                        \n");
	printf("                   #@@                                    \n");
}
// <!-- END MAKE LOGO -->

// <!-- START OF READ PASSWORD -->
void readOfPassword(char *temp) {
    int key = 0, index = 0;
    do {
        key = getch();
        switch (key) {
            case 0:
            case 224:
                getch();break;
            case '\b':
                if (index > 0) {
                    index = index - 1;
                    temp[index] = 0;
                    printf("\b \b");
                }
                break;
            default:
                if (key > 31 && key < 127) {
                    temp[index] = key;
                    index = index + 1;
                    printf("*");
                }
        }
    } while (key != 13);
    temp[index] = '\0';
}
// <!-- END OF READ PASSWORD -->

// <!-- START OF IDENTIFIER STRUCT -->
struct perjalanan{
	int idper, km;
	char almtAwal[250], almtTujuan[250], cttnTambahan[250], tgl[11], hari[15];
	int iddriver,idpel,status,harga,statusbayar;
};

struct driver{ int idDriv;char namaDriv[150], nohpDriv[15], almtDriv[250], plat[15], motor[50],userDriv[50],passDriv[50];};
struct pelanggan{ int idPelanggan;char namaPelanggan[150], nohpPelanggan[15], almtPelanggan[250], userPelanggan[50],passPelanggan[50];};

struct payment{ int idpel,saldo; };

struct databank{ long long int rekening; int saldo; char nama[100]; };

// <!-- END OF IDENTIFIER STRUCT -->

// <!-- FUNCTION FOR RE-DECLARE DAY OF WEEK FROM INTEGER TO STRING -->
char week(char *d,int today){
	if(today==0) strcpy(d,"Minggu");
	else if(today==1) strcpy(d,"Senin");
	else if(today==2) strcpy(d,"Selasa");
	else if(today==3) strcpy(d,"Rabu");
	else if(today==4) strcpy(d,"Kamis");
	else if(today==5) strcpy(d,"Jumat");
	else if(today==6) strcpy(d,"Sabtu");
}
// <!-- END OF FUNCTION -->

// <!-- FUNCTION FOR SEARCH PERJALANAN IN FILE perjalanan.txt -->
int SearchPerjalanan(struct perjalanan *m, int n, int search){
    int mid,low,high;
    low=0;
    high=n-1;
    while(low<=high){
        mid=(low+high)/2;		//kyk searching binary//
        if(search == m[mid].idper) return mid;
        if(search < m[mid].idper) high = mid-1;
        else low=mid+1;
    }
    return -1;
}
// <!-- END OF FUNCTION -->

// <!-- FUNCTION FOR SEARCH DRIVER IN FILE driver.txt -->
// Search Driver where iddriver
int SearchDriver(struct driver *m, int n, int *search){
    int mid,low,high;
    low=0;
    high=n-1;
    while(low<=high){
        mid=(low+high)/2;
        if(*search == m[mid].idDriv) return mid;
        if(*search < m[mid].idDriv) high = mid-1;
        else low=mid+1;
    }
    return -1;
}

// Search Driver where nohp driver
int SearchDriver2(struct driver *m, int n, char *search){
    int i;
    for(i=0;i<n;i++){
        if(strcmp(search,m[i].nohpDriv) == 0) return i;
    }
    return -1;
}

// Search Driver where username driver
int SearchDriver3(struct driver *m, int n, char *search){
    int i;
    for(i=0;i<n;i++){
        if(strcmp(search,m[i].userDriv) == 0) return i;
    }
    return -1;
}
// <!-- END OF FUNCTION -->

// <!-- FUNCTION FOR SEARCH PELANGGAN IN FILE pelanggan.txt -->
// Search Pelanggan where nohp pelanggan
int SearchPelanggan1(struct pelanggan *m, int n, char *search){
    int i;
    for(i=0;i<n;i++){
        if(strcmp(search,m[i].nohpPelanggan) == 0 || search == m[i].nohpPelanggan) return i;
    }
    return -1;
}

// Search Pelanggan where username pelanggan
int SearchPelanggan2(struct pelanggan *m, int n, char *search){
    int i;
    for(i=0;i<n;i++){
        if(strcmp(search,m[i].userPelanggan) == 0) return i;
    }
    return -1;
}
// <!-- END OF FUNCTION -->

// <!-- START SEARCH REKENING WHERE REKENING PELANGGAN -->
int searchRek(struct databank *data, int n, long long int search){
	int i;
	for (i=0; i<n; i++){
		if (search ==  data[i].rekening) return i;
	}
	return -1;
}
// <!-- END OF FUNCTION -->

// <!--  START OF SORT DATE FOR DATA PERJALANAN
void sortDateOfPerjalanan(struct perjalanan *db, int jumlah , int logIdPel, int kondisi){
    int i,j;
	struct perjalanan temp;
    
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
			}
	        db[j+1] = temp;
	    }
    
    printf("%-9s %-17s %-17s %-7s %-12s\n","Jarak (km)","Titik Awal","Titik Akhir","Hari","Tanggal");
    printf("======================================================================\n");
	for(i=0;i<jumlah;i++){
		if(db[i].idpel == logIdPel) {
			printf("%-10d %-17s %-17s %-7s %-12s\n",db[i].km,db[i].almtAwal,db[i].almtTujuan,db[i].hari,db[i].tgl);
		}
	}   
}
// <!-- END OF FUNCTION -->

int main(){
	loading();
	
	FILE *file; // <!-- DECLARE FILE AS *file -->
	
	// <!-- START TANGGAL - UNTUK MENDAPATKAN TANGGAL SEKARANG -->
	time_t t = time(NULL);struct tm tm = *localtime(&t);char date[15],day[15];week(day,tm.tm_wday);
	file = fopen("datenow.txt", "w");
	fprintf(file, "%02d/%02d/%d",tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
	fclose(file);
	
	file = fopen("datenow.txt", "r");
		while(!feof(file)){ fscanf(file, "%[^\n]\n",date);}
	fclose(file);
	// <!-- END TANGGAL -->
	
	// <!-- START OF STRUCT -->
	struct perjalanan perjalanan[150];
	struct payment pay[150];
	struct databank data[100];
	// <!-- END OF STRUCT -->
	
	// <!-- START IDENTIFIER FOR ALL VARIABLE -->
	int i, jumlah_data, pilih;
	char lagi,logPass[50],logUser[50], logNohp[15],logNama[50], logAlamat[100];int logIdPel;long long int logRekening; // untuk tampung session login
	char user[100];char pass[100]; // untuk menampung sementara username dan password pada saat login
  	int benar=0,salah=1; // untuk mengidentifikasi login berhasil atau tidak
  	int jarak;char alamatAwal[250], alamatTujuan[250], catatanTambahan[250]; // untuk menampung sementara pesanan perjalanan
  	int statusPer=0,counterperjalanan=0,counterIdPer,counterDriver=0,statusDriver,bayarsekarang,metode,saldo; // variabel tambahan
  	int countPay=0,idofpay,pilihalamat,pilLogOrDaf,pilLogPelOrDriv,pilDafPelOrDriv,lanjutkan; // variable tambahan
  	int pilihSort,JumlahPerjalananAll=0, counterPay=0,JumlahSaldoAll,counterdatabank=0,tanyaojekpay; // variable tambahan
  	int saldoIn,tanyaSecure, IndexSaldo, StartInsert=0, IndexSaldoBank=0, bayargopay=0,hargadriver,hargaiojek; // variable tambahan
  	int tarifTrip, kurangJarak, tarifTripSementara1, tarifTripSementara2; // variable tambahan
  	// <!-- END IDENTIFIER FOR ALL VARIABLE -->
  	
  	// <!-- START IDENTIFIER VARIABLE FOR DRIVER -->
  	char no_hpDriv[15],namaDriv[50], alamatDriv[100], platDriv[15], motorDriv[50];
	int counterIdDriver,checkDriver1,checkDriver2,checknohpdriv=0;
  	// <!-- END OF IDENTIFIER VARIABLE FOR DRIVER -->
  	
  	// <!-- START IDENTIFIER VARIABLE FOR REGISTER PELANGGAN -->
  	char passwordPelanggan[50],usernamePelanggan[50], no_hpPelanggan[15],namaPelanggan[50], alamatPelanggan[100],rekeningPelanggan[30];
	int counterIdPelanggan,checkPelanggan1,checkPelanggan2,counterPelanggan=0,checknohppel=0;
  	// <!-- END OF IDENTIFIER VARIABLE FOR REGISTER PELANGGAN -->
  	
  	// <!-- START DATA DRIVER INSERT TO STRUCT -->
  	struct driver driver[150];
					
	FILE *fdriv = fopen("driver.txt","r");
		while(!feof(fdriv)){
			fscanf(fdriv,"%d#%[^#]#%[^#]#%[^#]#%[^#]#%[^#]#%[^#]#%[^\n]\n",&driver[counterDriver].idDriv,
																		driver[counterDriver].namaDriv,
																		driver[counterDriver].nohpDriv,
																		driver[counterDriver].almtDriv,
																		driver[counterDriver].plat,
																		driver[counterDriver].motor,
																		driver[counterDriver].userDriv,
																		driver[counterDriver].passDriv);
			counterDriver++;
		}
	fclose(fdriv);
	// <!-- END DATA DRIVER INSERT TO STRUCT -->
	
	// <!-- START DATA PELANGGAN INSERT TO STRUCT -->
	struct pelanggan pelanggan[150];
	
	FILE *fpel = fopen("pelanggan.txt","r");
		while(!feof(fpel)){
			fscanf(fpel,"%d#%[^#]#%[^#]#%[^#]#%[^#]#%[^\n]\n",&pelanggan[counterPelanggan].idPelanggan,
															pelanggan[counterPelanggan].namaPelanggan,
															pelanggan[counterPelanggan].nohpPelanggan,
															pelanggan[counterPelanggan].almtPelanggan,
															pelanggan[counterPelanggan].userPelanggan,
															pelanggan[counterPelanggan].passPelanggan);
			counterPelanggan++;
		}
	fclose(fpel);
  	// <!-- END DATA PELANGGAN INSERT TO STRUCT -->
  	
  	do{
		printf("=======================================\n");
		puts  ("             iOjek Inc");
		printf("=======================================\n\n");
		printf("       1. Login  // 2. Daftar\n\n\n");
		printf("Pilih: ");scanf("%d",&pilLogOrDaf);system("cls");
		if(pilLogOrDaf == 1){
			// <!-- START OF PELANGGAN -->
			  		if((file = fopen("pelanggan.txt", "r")) == NULL){ 
				   			printf("File Tidak Ditemukan\n");
						fclose(file);
					} else {
						do{
							printf("=======================================\n");
							puts  ("         PORTAL LOGIN");
							printf("=======================================\n\n");
					  		printf("  username : ");scanf("%s",user);fflush(stdin);
					  		printf("  password : ");readOfPassword(pass);fflush(stdin);
					  		
							file = fopen("pelanggan.txt", "r");
						   	while(!feof(file)){
								fscanf(file, "%d#%[^#]#%[^#]#%[^#]#%[^#]#%[^#]#%lld\n", &logIdPel,logNama, logNohp, logAlamat, logUser, logPass,&logRekening);
								if(strcmp(logUser,user) == 0 && strcmp(logPass,pass) == 0){ benar=2;salah=0;}
								if(benar == 2 && salah == 0){ printf("\n\n  Selamat datang %s\n\n\n",logNama);system("pause");salah=0;benar=2;break;}
					        }
					        fclose(file);
					        
							if(benar==0 && salah==1){
						  		puts("\n\n  Username atau password salah");system("pause");system("cls");
							}else if(benar==2 && salah==0){ system("cls");                                                                                                  
								do{
									counterperjalanan=0;
									FILE *fper = fopen("perjalanan.txt", "r");
										while(!feof(fper)){
											fscanf(fper, "%d#%d#%[^#]#%[^#]#%[^#]#%[^#]#%[^#]#%d#%d#%d#%d#%[^\n]\n",&perjalanan[counterperjalanan].idper,
																													&perjalanan[counterperjalanan].km,
																													perjalanan[counterperjalanan].almtAwal,
																													perjalanan[counterperjalanan].almtTujuan,
																													perjalanan[counterperjalanan].cttnTambahan,
																													perjalanan[counterperjalanan].tgl,
																													perjalanan[counterperjalanan].hari,
																													&perjalanan[counterperjalanan].iddriver,
																													&perjalanan[counterperjalanan].idpel,
																													&perjalanan[counterperjalanan].status,
																													&perjalanan[counterperjalanan].harga,
																													&perjalanan[counterperjalanan].statusbayar);
											counterperjalanan++;
									    }
									fclose(fper);
									
									counterPay=0;
									FILE *fpay = fopen("ojekpay.txt","r");
										while(!feof(fpay)){
											fscanf(fpay,"%d#%d\n",&pay[counterPay].idpel,&pay[counterPay].saldo);
											counterPay++;
										}
									fclose(fpay);
									
									printf("=======================================\n");
									printf("             iOjek Inc.\n");
									printf("=======================================\n");
									printf("1. Lakukan Perjalanan\n");
									printf("2. History Perjalanan\n");
									printf("3. Pengisian Saldo iOjekPay\n");
									printf("4. Lihat Profil ( %s )\n",logNama);
									printf("5. Keluar\n");
									
									printf("\n=======================================\n");
									printf("Pilih : ");scanf("%d",&pilih);fflush(stdin);
									
									if(pilih == 1){ 
										system("pause");
										system("cls");
										int jarak;
										printf("=======================================\n");
										printf("          Lakukan Perjalanan\n");
										printf("=======================================\n");
										printf("Masukkan Jarak Tempuh (km)\t\t : ");scanf("%d",&jarak);fflush(stdin);
										printf("Masukkan Titik Awal (alamat awal)\t : ");gets(alamatAwal);fflush(stdin);
										printf("\nTitik Akhir (alamat tujuan)\t\t : \n");
										printf("1. Alamat Utama\n2. Alamat Lain\nPilih: ");scanf("%d",&pilihalamat);fflush(stdin);
										if(pilihalamat == 1) strcpy(alamatTujuan,logAlamat);
										else if(pilihalamat == 2) {
										printf("Masukkan Titik Akhir (alamat tujuan) : ");gets(alamatTujuan);fflush(stdin);
										}
										printf("\nCatatan tambahan\t\t\t: ");gets(catatanTambahan);fflush(stdin);
										
							// <!-- START OF FARE -->
							// TARIF RUSH HOUR //
										if(((tm.tm_hour >= 6 && tm.tm_hour < 9) || (tm.tm_hour >= 16 && tm.tm_hour < 20)) && (tm.tm_wday >= 1 && tm.tm_wday <= 5)){ //tm_hour = rush hour, tm_wday = jam biasa //
											if(jarak >= 0 && jarak <= 12){
												tarifTrip = jarak * 2500;
											}else if(jarak > 12){
												kurangJarak = jarak - 12;
												tarifTripSementara1 = 12 * 2500;
												tarifTripSementara2 = kurangJarak * 3000;
												tarifTrip = tarifTripSementara1 + tarifTripSementara2;
											}
							
							// TARIF BIASA //
										}else{
											if(jarak >= 0 && jarak <= 12){
												tarifTrip = jarak * 1500;
											}else if(jarak > 12){
												kurangJarak = jarak - 12;
												tarifTripSementara1 = 12 * 1500;
												tarifTripSementara2 = kurangJarak * 2500;
												tarifTrip = tarifTripSementara1 + tarifTripSementara2;
											}
										}
							// <!-- END OF FARE -->
										
										printf("\nMetode pembayaran:\n");printf("1. Cash\n2. iOjek Pay\nPilih : ");scanf("%d",&metode);fflush(stdin);
							
							// <!-- UNTUK MENDEFINISIKAN ID DARI COUNTER PERJALANAN SELANJUTNYA -->
										file = fopen("counterperjalanan.txt", "r");
										   	fscanf(file, "%d",&counterIdPer);
										fclose(file); counterIdPer +=1;
							// <!-- AKHIR DARI STATEMENT -->
										
										if(metode==2){
											countPay=0;
											file = fopen("ojekpay.txt", "r");
											while(!feof(file)){
										   		fscanf(file, "%d#%d\n",&pay[countPay].idpel,&pay[countPay].saldo);
												if(logIdPel == pay[countPay].idpel){
													saldo=pay[countPay].saldo;idofpay=countPay;//break;
												}
												countPay++;
										   	}
									    	fclose(file);//countPay=0;
									    	
											printf("\n Saldo anda : %d\n",saldo);
									    	printf(" Harga Perjalanan : %d\n",tarifTrip);
									    	if(saldo < tarifTrip){
									    		printf("Saldo anda tidak mencukupi,\nisi sekarang dengan membuka menu [3. Pengisian Saldo iOjekPay]");
									    		
									    		printf("\n Tetap lakukan perjalanan dengan membayar cash [Y/N] ? ");lanjutkan=getchar();fflush(stdin);
									    		if(lanjutkan == 'y' || lanjutkan == 'Y') metode=1;
												else if(lanjutkan == 'n' || lanjutkan == 'N'){ system("cls"); metode=0;}
											}else {
												
												printf("\n Bayar sekarang [Y/N]? ");bayarsekarang=getchar();fflush(stdin);
												if(bayarsekarang == 'y' || bayarsekarang == 'Y'){
													pay[idofpay].saldo -= tarifTrip;
													
													file = fopen("ojekpay.txt", "w");
													for(i=0;i<countPay;i++){
												   		fprintf(file, "%d#%d\n",pay[i].idpel,pay[i].saldo);
												   	}
												   	fclose(file);
												   	bayargopay=1;
												   	
												   	hargadriver = tarifTrip - (tarifTrip * 0.2);
													hargaiojek  = tarifTrip * 0.2;
																									
												   	printf("\n  PEMBAYARAN MENGGUNAKAN iOJEKPAY BERHASIL\n");
												}else{
													system("cls");
												}
												
											}
											
										}
										
										if(metode == 2 || metode == 1){
											
											FILE *fput = fopen("perjalanan.txt","a");
												if(bayargopay == 1){
										        	fprintf(fput, "%d#%d#%s#%s#%s#%s#%s#%d#%d#%d#%d#%d\n",counterIdPer,jarak,alamatAwal,alamatTujuan,catatanTambahan,date,day,0,logIdPel,0,tarifTrip,1);
										    	}else{
										    		fprintf(fput, "%d#%d#%s#%s#%s#%s#%s#%d#%d#%d#%d#%d\n",counterIdPer,jarak,alamatAwal,alamatTujuan,catatanTambahan,date,day,0,logIdPel,0,tarifTrip,0);
												}
										    fclose(fput);
										    
										    file = fopen("counterperjalanan.txt", "w+");
											   	fprintf(file, "%d",counterIdPer);
										    fclose(file);
										    
										    printf("\nPesanan Berhasil, tunggu beberapa saat..\n");
											printf("Tekan enter untuk memeriksa status pesanan\n\n");system("pause");system("cls");
										    
										    int hitung=0;
											do{												
												printf("=======================================\n");
												printf("          Lakukan Perjalanan\n");
												printf("=======================================\n");
												
												printf("Masukkan Jarak Tempuh (km)\t\t: %d\n",jarak);
												printf("Masukkan Titik Awal (alamat awal)\t: %s\n",alamatAwal);
												printf("Masukkan Titik Akhir (alamat tujuan)\t: %s\n",alamatTujuan);
												printf("Catatan tambahan\t\t\t: %s\n",catatanTambahan);
												printf("Harga yang harus dibayar\t\t: %d\n",tarifTrip);
												
												counterperjalanan=0;
												FILE *fper = fopen("perjalanan.txt", "r");
												   while(!feof(fper)){
													fscanf(fper, "%d#%d#%[^#]#%[^#]#%[^#]#%[^#]#%[^#]#%d#%d#%d#%d#%[^\n]\n",&perjalanan[counterperjalanan].idper,
																														&perjalanan[counterperjalanan].km,
																														perjalanan[counterperjalanan].almtAwal,
																														perjalanan[counterperjalanan].almtTujuan,
																														perjalanan[counterperjalanan].cttnTambahan,
																														perjalanan[counterperjalanan].tgl,
																														perjalanan[counterperjalanan].hari,
																														&perjalanan[counterperjalanan].iddriver,
																														&perjalanan[counterperjalanan].idpel,
																														&perjalanan[counterperjalanan].status,
																														&perjalanan[counterperjalanan].harga,
																														&perjalanan[counterperjalanan].statusbayar);
													counterperjalanan++;
										        }
										        fclose(fper); 
										        
										        
										        printf("\n\n     STATUS REFRESH [%d]\n\n",hitung);
										        hitung++;
										        
										        statusPer = SearchPerjalanan(perjalanan,counterperjalanan,counterIdPer);
												
								// <!-- LANJUTAN DARI PROGRAM GOPAY, UNTUK MEMASUKKAN DATA PENDAPATAN -->
											if(bayargopay==1 && perjalanan[statusPer].status==1){
													FILE *fpendapataniOjek = fopen("pendapataniojek.txt", "a");
														fprintf(fpendapataniOjek, "%s#%d#%d#%d\n",date,hargaiojek,perjalanan[statusPer].iddriver,counterIdPer);
													fclose(fpendapataniOjek);
																	
													FILE *fpendapatan = fopen("pendapatan.txt", "a");
														fprintf(fpendapatan, "%d#%d#%s\n",perjalanan[statusPer].iddriver,hargadriver,date);
													fclose(fpendapatan);
													bayargopay=0;
											}
								
								// <!-- AKHIR DARI STATEMENT -->
								
												printf("\n\n [Status] : ");
												if(perjalanan[statusPer].status == 0) printf("Sedang menungu driver\n");
												else if(perjalanan[statusPer].status == 1) printf("Driver sudah dalam perjalanan ke titik awal\n");
												else if(perjalanan[statusPer].status == 2) printf("Driver sudah di lokasi penjemputan\n");
												else if(perjalanan[statusPer].status == 3) printf("Dalam perjalanan ke titik akhir\n");
												else if(perjalanan[statusPer].status == 4) printf("Perjalanan telah selesai\n");
												
												if(perjalanan[statusPer].status != 0 || perjalanan[statusPer].status != 4){
													puts("[Data Driver]:");
													statusDriver = SearchDriver(driver,counterDriver,&perjalanan[statusPer].iddriver);
													printf("Nama\t\t: %s\n",driver[statusDriver].namaDriv);
													printf("Plat No.\t: %s\n",driver[statusDriver].plat);
													printf("Motor\t\t: %s\n",driver[statusDriver].motor);
												}
												
												if(perjalanan[statusPer].status == 4){
													//printf("status bayar perjalanan : %d",perjalanan[statusPer].statusbayar);
													if(metode == 1 && perjalanan[statusPer].statusbayar == '0'){
														printf("===============================");  	
														printf("\n\n    Bayar sekarang : %d\n\n",tarifTrip);
													}else if(metode == 1 && perjalanan[statusPer].statusbayar == '1' || metode == 2 && perjalanan[statusPer].statusbayar == '1'){
														printf("\n\n    Terimakasih Telah Menggunakan iOjek Inc\n");
														system("pause");system("cls");break;
													}
												}
												counterperjalanan=0;
												printf("\n");system("pause");fflush(stdin);system("cls");
											}while(1);
										}
									}else if(pilih == 2){
										system("cls");
										do{
											printf("======================================================================\n");
											printf("                       History Perjalanan\n");
											printf("======================================================================\n");
											
											for(i=0;i<counterperjalanan;i++){
												if(perjalanan[i].iddriver == logIdPel) JumlahPerjalananAll++;
											}
											printf("   Perjalanan Anda Selama Bergabung di iOjek : %d\n",JumlahPerjalananAll);JumlahPerjalananAll=0;
												printf("======================================================================\n\n");
												printf("Sort berdasarkan tanggal\n  1. Asc // 2. Desc // 3. Kembali\nPilih : ");scanf("%d",&pilihSort);fflush(stdin);
												printf("======================================================================\n");
												if(pilihSort == 1){
													sortDateOfPerjalanan(perjalanan,counterperjalanan,logIdPel,0);
												}else if(pilihSort == 2){
													sortDateOfPerjalanan(perjalanan,counterperjalanan,logIdPel,1);
												}else if(pilihSort == 3){
													counterperjalanan=0;system("cls");break;
												}
											system("pause");system("cls");
										}while(1);
									}else if(pilih == 3){
										system("cls");
										do{
											printf("==========================================\n");
											printf("              iOjekPay\n");
											printf("==========================================\n");
											
											for(i=0;i<counterPay;i++){
												if(pay[i].idpel == logIdPel){ JumlahSaldoAll = pay[i].saldo;IndexSaldo = i; }
											}
											printf("\n  Saldo anda : %d\n\n", JumlahSaldoAll);
											printf("==========================================\n");
											printf("     1. Isi Saldo // 2. Kembali\n");
											printf("==========================================\n");
											printf("Pilih : ");tanyaojekpay = getchar();fflush(stdin);
											if(tanyaojekpay == '1'){
												
												counterdatabank=0;
												FILE *file = fopen("databank.txt", "r");
												while(!feof(file)){
													fscanf(file, "%lld#%[^#]#%d\n", &data[counterdatabank].rekening, data[counterdatabank].nama, &data[counterdatabank].saldo); // %lld = long long integer //
													counterdatabank++;
												}
												fclose(file);
												
												for(i=0;i<counterdatabank;i++){
													if(data[i].rekening == logRekening){ IndexSaldoBank = i; }
												}
												
												printf("\nMasukkan nominal saldo yang ingin di isi :\n");scanf("%d",&saldoIn);fflush(stdin);
												
												printf(" Anda yakin sudah memeriksanya [Y/N] ? ");tanyaSecure = getchar();fflush(stdin);
												if(tanyaSecure == 'y' || tanyaSecure == 'Y'){
													
													pay[IndexSaldo].saldo += saldoIn;
													data[IndexSaldoBank].saldo -= saldoIn;
													StartInsert=1;
													
													if(StartInsert == 1){
													
														FILE *fbank = fopen("databank.txt", "w");
															for(i=0;i<counterdatabank;i++){
																fprintf(fbank,"%lld#%s#%d\n",data[i].rekening, data[i].nama, data[i].saldo);
																}	
														fclose(fbank); 
														
														FILE *fpay = fopen("ojekpay.txt", "w");
															for(i=0;i<counterPay;i++){
																fprintf(fpay,"%d#%d\n",pay[i].idpel, pay[i].saldo);
															}	
														fclose(fpay); 
														StartInsert=0;
														system("cls");
													}
													
												}else system("cls");
												
											}else if(tanyaojekpay == '2') {
												system("pause");system("cls");break;
											}
										}while(1);
									}else if(pilih == 4){
										system("cls");
										printf("=======================================\n");
										printf("            Data Pelanggan\n");
										printf("=======================================\n");
									    printf("Nama pelanggan\t\t= %s\n", logNama); 
									    printf("Nomor Hp\t\t= %s\n", logNohp); 
										printf("Alamat pelanggan\t= %s\n", logAlamat); 
										printf("User name pelanggan\t= %s\n", logUser); 
										printf("Password pelanggan\t= %s\n\n", logPass);
										printf("Rekening pelanggan\t= %lld\n\n", logRekening);
										system("pause");system("cls");
									}else if(pilih == 5){
										counterDriver=0;counterperjalanan=0;statusPer=0;benar=0;salah=1;system("cls");
										break;
									}else{
										system("cls");
									}
								}while(1);
							if(pilih==5) break;
							} 
						
						}while(1);
					}
				    fflush(stdin);
// <!-- END OF PELANGGAN -->			  		

		}else if(pilLogOrDaf == 2){
			do{
				printf("=======================================\n");
				puts  ("           Daftar iOjek Inc");
				printf("=======================================\n\n");
				printf("      1. Pelanggan // 2. Kembali\n\n\n");
		  		printf("Pilih: ");scanf("%d",&pilDafPelOrDriv);fflush(stdin);system("cls");
		  		if(pilDafPelOrDriv == 1){
	
// <!-- START OF DAFTAR PELANGGAN -- >
		  			if((file = fopen("pelanggan.txt", "a+")) == NULL){
				   		printf("File Tidak Ditemukan\n");system("pause");break;fclose(file);
				    } else {
						do{
						printf("+-----------------------------------------------+\n");
						printf("|          WELCOME NEW PELANGGAN ! ! !          |\n");
						printf("+-----------------------------------------------+\n\n\n");
						printf("   Yang harus diperhatikan : \n    No hp yang sudah pernah di daftarkan, \n    tidak bisa di gunakan kembali\n");
						printf("| Nama = "); gets(namaPelanggan); fflush(stdin);
						printf("| Nomor Hp = "); gets(no_hpPelanggan); fflush(stdin);
						printf("| Alamat = "); gets(alamatPelanggan); fflush(stdin);
						printf("| Username = "); gets(usernamePelanggan); fflush(stdin);
						printf("| Password = "); readOfPassword(passwordPelanggan); fflush(stdin);printf("\n");
						printf("| Rekening Bank = "); gets(rekeningPelanggan); fflush(stdin);
						printf("+-----------------------------------------------+\n");
						
						checkPelanggan1 = SearchPelanggan1(pelanggan,counterPelanggan,no_hpPelanggan);
						checkPelanggan2 = SearchPelanggan2(pelanggan,counterPelanggan,usernamePelanggan);
						
						if(strlen(no_hpPelanggan) < 11 || strlen(no_hpPelanggan) > 12){ printf("No telepon minimal 11 digit dan maksimal 12 digit\n");checknohppel=1;}
						if(checkPelanggan1 != -1) printf("No telepon tidak bisa digunakan, telah terdaftar sebagai akun lain\n");
						if(checkPelanggan2 != -1) printf("Username tidak bisa digunakan, telah terdaftar sebagai akun lain\n");
						
						//system("pause");system("cls");
						
						if(checkPelanggan1 == -1 && checkPelanggan2 == -1 && checknohppel == 0){
							FILE *fcounterp = fopen("counterp.txt", "r");
								fscanf(fcounterp, "%d",&counterIdPelanggan);
							fclose(fcounterp); counterIdPelanggan +=1;
							
							FILE *fpel = fopen("pelanggan.txt", "a");
						   	fprintf(fpel, "%d#%s#%s#%s#%s#%s#%s\n", counterIdPelanggan,namaPelanggan, no_hpPelanggan, alamatPelanggan, usernamePelanggan, passwordPelanggan,rekeningPelanggan);    
						   	fclose(fpel); 
						   	
						   	FILE *rekIn = fopen("ojekpay.txt", "a");
								fprintf(rekIn, "%d#%d",&counterIdPelanggan,0);
							fclose(rekIn); 
					   	
					   		FILE *fcounterpIN = fopen("counterp.txt", "w+");
								fprintf(fcounterpIN, "%d",counterIdPelanggan);
							fclose(fcounterpIN);
							
							printf("data pelanggan berhasil di tambahankan.\n");system("pause");system("cls");break;
						}
						printf("\n");system("pause");system("cls");
						}while(1);
					}
					//fflush(stdin);system("cls");
// <!-- END OF DAFTAR PELANGGAN -- >

				}else if(pilDafPelOrDriv == 2){
					break;
				}else{
					system("cls");
				}
			}while(1);
		}else{
			system("cls");
		}
	}while(1);
	
	
	return 0;
}
