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
	int idper;int km;
	char almtAwal[250], almtTujuan[250], cttnTambahan[250], tgl[11], hari[15];
	int iddriver,idpel,status,harga,statusbayar;
};

struct driver{ int idDriv;char namaDriv[150], nohpDriv[15], almtDriv[250], plat[15], motor[50],userDriv[50],passDriv[50];};
struct pelanggan{ int idPelanggan;char namaPelanggan[150], nohpPelanggan[15], almtPelanggan[250], userPelanggan[50],passPelanggan[50];};

struct payment{ int idpel,saldo; };
struct pendapatan{ int iddriver,jumlahPendapatan;char tanggalPendapatan[11]; };

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
int SearchPerjalanan(struct perjalanan *m, int n, int *search){
    int mid,low,high;
    low=0;
    high=n-1;
    while(low<=high){
        mid=(low+high)/2;
        if(*search == m[mid].idper) return mid;
        if(*search < m[mid].idper) high = mid-1;
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
        if(strcmp(search,m[i].nohpDriv) == 0 || search == m[i].nohpDriv ) return i;
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
        if(strcmp(search,m[i].nohpPelanggan) == 0) return i;
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

// Search Pelanggan where id pelanggan
int SearchPelanggan3(struct pelanggan *m, int n, int search){
    int i;
    for(i=0;i<n;i++){
        if(search == m[i].idPelanggan) return i;
    }
    return -1;
}

// <!-- END OF FUNCTION -->

// <!--  START OF SORT DATE FOR DATA PENDAPATAN
void sortDateOfPendapatan(struct pendapatan *db, int jumlah , int logIdDriv, int kondisi){
    int i,j;
	struct pendapatan temp;
    
		for(i=1;i<jumlah;i++){
			temp = db[i];
			j = i-1;
			if(kondisi == 0){
				while(strcmp(db[j].tanggalPendapatan, temp.tanggalPendapatan) > 0 && j >= 0){
					db[j+1] = db[j];
					j = j-1;
				}	
			}else if(kondisi == 1){
				while(strcmp(db[j].tanggalPendapatan, temp.tanggalPendapatan) < 0 && j >= 0){
					db[j+1] = db[j];
					j = j-1;
				}
			}
	        db[j+1] = temp;
	    }
    
    	
    printf("  %-12s %-9s\n","Tanggal","Jumlah");
	for(i=0;i<jumlah;i++){
		if(db[i].iddriver == logIdDriv) {
			printf("  %-12s %-9d\n",db[i].tanggalPendapatan,db[i].jumlahPendapatan);
		}
	}   
    
}
// <!-- END OF FUNCTION -->

// <!--  START OF SORT DATE FOR DATA PERJALANAN
void sortDateOfPerjalanan(struct perjalanan *db, int jumlah , int logIdDriv, int kondisi){
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
		if(db[i].iddriver == logIdDriv) {
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
	struct pendapatan pendapatan[300];
	
	// <!-- END OF STRUCT -->
	
	// <!-- START IDENTIFIER FOR ALL VARIABLE -->
	int i, jumlah_data, pilih;
	char lagi,logPass[50],logUser[50], logNohp[15],logNama[50], logAlamat[100], logPlat[15], logMotor[50];int logIdDriv; // untuk tampung session login
	char user[100];char pass[100]; // untuk menampung sementara username dan password pada saat login
  	int benar=0,salah=1; // untuk mengidentifikasi login berhasil atau tidak
  	int jarak;char alamatAwal[250], alamatTujuan[250], catatanTambahan[250]; // untuk menampung sementara pesanan perjalanan
  	int statusPer=0,counterperjalanan=0,counterIdPer,counterDriver=0,statusDriver,bayarsekarang,metode,saldo; // variabel tambahan
  	int countPay=0,idofpay,pilihalamat,pilLogOrDaf,pilLogPelOrDriv,pilDafPelOrDriv; // variable tambahan
  	int logPerjalanan=0,perTersedia=0,CariDataPelanggan,CariDataPerjalanan,CariIdTrip,statusInsert=0;
  	int counterpendapatan=0,SaldoPendapatanAll=0,pilihSort,JumlahPerjalananAll=0;
  	// <!-- END IDENTIFIER FOR ALL VARIABLE -->
  	
  	// <!-- START IDENTIFIER FOR TRIP DRIVER -->
  	int tripyesno,trip,tanyadua,tanyatiga,tanyaempat,tanyalima, hargadriver,hargaiojek;
  	// <!-- END OF IDENTIFIER FOR TRIP DRIVER -->
  	
  	// <!-- START IDENTIFIER VARIABLE FOR REGISTER DRIVER -->
  	char passwordDriv[50],usernameDriv[50], no_hpDriv[15],namaDriv[50], alamatDriv[100], platDriv[15], motorDriv[50];
	int counterIdDriver,checkDriver1,checkDriver2,checknohpdriv=0;
  	// <!-- END OF IDENTIFIER VARIABLE FOR REGISTER DRIVER -->
  	
  	// <!-- START IDENTIFIER VARIABLE FOR REGISTER PELANGGAN -->
  	char passwordPelanggan[50],usernamePelanggan[50], no_hpPelanggan[15],namaPelanggan[50], alamatPelanggan[100];
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
		puts  ("          iOjek Inc <Driver>");
		printf("=======================================\n\n");
		printf("       1. Login  // 2. Daftar\n\n\n");
		printf("Pilih: ");pilLogOrDaf = getchar();system("cls");
		if(pilLogOrDaf == '1'){
// <!-- START OF DRIVER -->
			  		if((file = fopen("pelanggan.txt", "r")) == NULL){ 
				   			printf("File Tidak Ditemukan\n");
						fclose(file);    			
					} else {
						do{
							printf("=======================================\n");
							puts  ("             PORTAL LOGIN");
							printf("=======================================\n\n");
					  		printf("  username : ");scanf("%s",user);fflush(stdin);
					  		printf("  password : ");readOfPassword(pass);fflush(stdin);
					  		
							file = fopen("driver.txt", "r");
						   	while(!feof(file)){
								fscanf(file, "%d#%[^#]#%[^#]#%[^#]#%[^#]#%[^#]#%[^#]#%[^\n]\n", &logIdDriv,logNama, logNohp, logAlamat, logPlat,logMotor,logUser, logPass);
								if(strcmp(logUser,user) == 0 && strcmp(logPass,pass) == 0){ benar=2;salah=0;}
								if(benar == 2 && salah == 0){ printf("\n\n  Selamat datang %s\n\n",logNama);system("pause");salah=0;benar=2;break;}
					        }
					        fclose(file); 
					        
							if(benar==0 && salah==1){
						  		puts("\n\n  Username atau password salah\n\n");system("pause");system("cls");
							}else if(benar==2 && salah==0){
								system("cls");
								do{
									counterperjalanan=0;perTersedia=0;
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
											if(perjalanan[counterperjalanan].status == 0 && perjalanan[counterperjalanan].iddriver == 0) perTersedia++;
											counterperjalanan++;
									    }
									fclose(fper); 
									
									
									FILE *fpendapatan = fopen("pendapatan.txt", "r");
										while(!feof(fpendapatan)){
											fscanf(fpendapatan, "%d#%d#%[^\n]\n",&pendapatan[counterpendapatan].iddriver,
																				&pendapatan[counterpendapatan].jumlahPendapatan,
																				pendapatan[counterpendapatan].tanggalPendapatan);
											counterpendapatan++;
									    }
									fclose(fpendapatan); 
									
									
									
									printf("=======================================\n");
									printf("             iOjek Inc.\n");
									printf("=======================================\n");
									printf("1. Terima Perjalanan (%d)\n", perTersedia);
									printf("2. Lihat Profil ( %s )\n",logNama);
									printf("3. History Perjalanan\n");
									printf("4. Pendapatan\n");
									printf("5. Refresh\n");
									printf("6. Keluar\n");
									
									printf("\n=======================================\n");
									printf("Pilih : ");scanf("%d",&pilih);fflush(stdin);
									
									if(pilih == 1){ 
										system("pause");
										system("cls");
										int jarak;									    
										do{
											printf("=======================================\n");
											printf("          Terima Perjalanan\n");
											printf("=======================================\n");
											if(perTersedia != 0){											
												printf("%-7s %-12s %-20s %-25s %-9s\n","No.","NoHp","Nama","Titik Awal","Harga");
												printf("=============================================================================\n");
											}else{
												printf("                   BELUM ADA PERJALANAN TERSEDIA\n");
											}
											perTersedia=0;counterperjalanan=0;
											FILE *fperjalanan = fopen("perjalanan.txt", "r");
										   	while(!feof(fperjalanan)){
												fscanf(fperjalanan, "%d#%d#%[^#]#%[^#]#%[^#]#%[^#]#%[^#]#%d#%d#%d#%d#%d\n",&perjalanan[counterperjalanan].idper,
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
									        fclose(fperjalanan); 
									        for(i=0;i<counterperjalanan;i++){
									        	if(perjalanan[i].status == 0 && perjalanan[i].iddriver == 0) {
													CariDataPelanggan = SearchPelanggan3(pelanggan,counterPelanggan,perjalanan[i].idpel);
													CariDataPerjalanan = perjalanan[i].idper;
													if(CariDataPelanggan != -1){
													printf("%-6d  %-12s %-20s %-25s %-9d\n",perjalanan[i].idper,pelanggan[CariDataPelanggan].nohpPelanggan,pelanggan[CariDataPelanggan].namaPelanggan,perjalanan[i].almtAwal,perjalanan[i].harga);	
													}
												}
											}
									        
									        printf("%-6d %-12s\n",-1,"kembali");
									        do{
										        printf("Pilih Trip : ");scanf("%d",&trip);fflush(stdin);
										        if(trip == -1){
										        	break;
												}else{
													tripyesno=0;
													CariIdTrip = SearchPerjalanan(perjalanan,counterperjalanan,&trip);
													do{
														if(tripyesno == 0){
															printf("Yakin ingin mengambil trip no. %d [Y/N] ? ",trip);tripyesno=getchar();fflush(stdin);
															if(tripyesno == 'y' || tripyesno == 'Y'){ perjalanan[CariIdTrip].iddriver = logIdDriv;perjalanan[CariIdTrip].status = 1;statusInsert=1;
																//printf("yes");
																//printf("trip dengan id %d iddriver %d dan status %d\n",trip,perjalanan[trip].iddriver,perjalanan[trip].status);system("pause");
															    //counterperjalanan=0;
																	
															}else if(tripyesno == 'n' || tripyesno == 'N') break;
														}else{
															if(perjalanan[CariIdTrip].status == 1){
																printf("\n\n   1. Apakah anda telah sampai di lokasi penjemputan [Y/N] ? ");tanyadua = getchar();fflush(stdin);
																if(tanyadua == 'y' || tanyadua == 'Y') {perjalanan[CariIdTrip].status = 2;statusInsert=1;}
																else if(tanyadua == 'n' || tanyadua == 'N') system("cls");
															}else if(perjalanan[CariIdTrip].status == 2){
																printf("\n\n   2. Apakah anda telah menemukan pelanggan, dan sedang dalam perjalanan ke tujuan pengantaran [Y/N] ? ");tanyatiga = getchar();fflush(stdin);
																if(tanyatiga == 'y' || tanyatiga == 'Y'){ perjalanan[CariIdTrip].status = 3;statusInsert=1;}
																else if(tanyatiga == 'n' || tanyatiga == 'N') system("cls");
															}else if(perjalanan[CariIdTrip].status == 3){
																printf("\n\n   3. Apakah anda telah sampai di alamat tujuan dari trip pelanggan [Y/N] ? ");tanyaempat = getchar();fflush(stdin);
																if(tanyaempat == 'y' || tanyaempat == 'Y'){ perjalanan[CariIdTrip].status = 4;statusInsert=1;}
																else if(tanyaempat == 'n' || tanyaempat == 'N')	system("cls");
															}else if(perjalanan[CariIdTrip].status == 4 && perjalanan[CariIdTrip].statusbayar == 0){
																printf("\n\n   4. Apakah anda telah terima pembayaran berupa cash / kredit [Y/N] ? ");tanyalima = getchar();fflush(stdin);
																if(tanyalima == 'y' || tanyalima == 'Y'){
																	perjalanan[CariIdTrip].statusbayar = 1;
																	
																	statusInsert=1;
																	
																	hargadriver = 0-(perjalanan[CariIdTrip].harga + (perjalanan[CariIdTrip].harga*0.2));
																	hargaiojek  = perjalanan[CariIdTrip].harga*0.2;
																	
																	FILE *fpendapataniOjek = fopen("pendapataniojek.txt", "a");
																	fprintf(fpendapataniOjek, "%s#%d#%d#%d\n",date,hargaiojek,logIdDriv,trip);
																	fclose(fpendapataniOjek);
																	
																	FILE *fpendapatan = fopen("pendapatan.txt", "a");
																	fprintf(fpendapatan, "%d#%d#%s\n",logIdDriv,hargadriver,date);
																	fclose(fpendapatan);
																}else if(tanyalima == 'n' || tanyalima == 'N')	system("cls");
															}else if(perjalanan[CariIdTrip].status == 4 && perjalanan[CariIdTrip].statusbayar == 1){
																printf("\n\n   5. PERJALANAN TELAH SELESAI, PENDAPATAN ANDA BERTAMBAH.. \n");
																system("pause");break;system("cls");
															}
														}
														if(statusInsert==1){
														FILE *fperjalanan = fopen("perjalanan.txt", "w");
															for(i=0;i<counterperjalanan;i++){
																fprintf(fperjalanan,"%d#%d#%s#%s#%s#%s#%s#%d#%d#%d#%d#%d\n",perjalanan[i].idper,
																															perjalanan[i].km,
																															perjalanan[i].almtAwal,
																															perjalanan[i].almtTujuan,
																															perjalanan[i].cttnTambahan,
																															perjalanan[i].tgl,
																															perjalanan[i].hari,
																															perjalanan[i].iddriver,
																															perjalanan[i].idpel,
																															perjalanan[i].status,
																															perjalanan[i].harga,
																															perjalanan[i].statusbayar);
															}	
														fclose(fperjalanan); 
														statusInsert=0;
														}
													}while(1);
												}
												if(perjalanan[CariIdTrip].status == 4 && perjalanan[CariIdTrip].statusbayar == 1) {system("cls");break;}
												
									    	}while(1);
									    	counterperjalanan=0;
											if(trip == -1){ system("cls");break;}
										}while(1);
									}else if(pilih == 2){
										system("cls");
										printf("=======================================\n");
										printf("            Data Driver \n");
										printf("=======================================\n");
									    printf("Nama pelanggan\t\t= %s\n", logNama); 
									    printf("Nomor Hp\t\t= %s\n", logNohp); 
										printf("Alamat pelanggan\t= %s\n", logAlamat); 
										printf("User name pelanggan\t= %s\n", logUser); 
										printf("Password pelanggan\t= %s\n\n\n", logPass);
										printf("Plat Nomor\t= %s\n", logPlat); 
										printf("Nama Motor\t= %s\n\n", logMotor);
										system("pause");system("cls");
									}else if(pilih == 3){
										system("cls");
										do{
											printf("======================================================================\n");
											printf("                       History Perjalanan\n");
											printf("======================================================================\n");
											
											for(i=0;i<counterperjalanan;i++){
												if(perjalanan[i].iddriver == logIdDriv) JumlahPerjalananAll++;
											}
											
											printf("   Perjalanan Anda Selama Bergabung di iOjek : %d\n",JumlahPerjalananAll);JumlahPerjalananAll=0;
												printf("======================================================================\n\n");
												printf("Sort berdasarkan tanggal\n  1. Asc // 2. Desc // 3. Kembali\nPilih : ");scanf("%d",&pilihSort);fflush(stdin);
												printf("======================================================================\n");
												if(pilihSort == 1){
													sortDateOfPerjalanan(perjalanan,counterperjalanan,logIdDriv,0);
												}else if(pilihSort == 2){
													sortDateOfPerjalanan(perjalanan,counterperjalanan,logIdDriv,1);
												}else if(pilihSort == 3){
													counterperjalanan=0;system("cls");break;
												}
											system("pause");system("cls");
										}while(1);
									}else if(pilih == 4){
										system("cls");
										do{
											printf("======================================================================\n");
											printf("                         Pendapatan Anda\n");
											printf("======================================================================\n");
											
											for(i=0;i<counterpendapatan;i++){
												if(pendapatan[i].iddriver == logIdDriv) {
													SaldoPendapatanAll += pendapatan[i].jumlahPendapatan;
												}
											}
											printf("   Pendapatan Anda Selama Bergabung di iOjek : %d\n",SaldoPendapatanAll);SaldoPendapatanAll=0;
												printf("======================================================================\n\n");
												printf("Sort berdasarkan tanggal\n  1. Asc // 2. Desc // 3. Kembali\nPilih : ");scanf("%d",&pilihSort);fflush(stdin);
												printf("======================================================================\n");
												if(pilihSort == 1){
													sortDateOfPendapatan(pendapatan,counterpendapatan,logIdDriv,0);
												}else if(pilihSort == 2){
													sortDateOfPendapatan(pendapatan,counterpendapatan,logIdDriv,1);
												}else if(pilihSort == 3){
													counterpendapatan=0;system("cls");break;
												}
											system("pause");system("cls");
										}while(1);
									}else if(pilih == 5){
										system("cls");
									}
									else if(pilih == 6){
										counterDriver=0;counterperjalanan=0;counterpendapatan=0;statusPer=0;benar=0;salah=1;system("cls");
										break;
									}else{
										system("cls");
									}
									counterpendapatan=0;
								}while(1);
							}if(pilih==5) {break;system("cls");} if(pilih==6) break;
						
						}while(1);
					}
				    fflush(stdin);
// <!-- END OF DRIVER -->			  		

		}else if(pilLogOrDaf == '2'){
			do{
				printf("=======================================\n");
				puts  ("      Daftar iOjek Inc <Driver>");
				printf("=======================================\n\n");
				printf("       1. Driver // 2. Kembali\n\n\n");
		  		printf("Pilih: ");scanf("%d",&pilDafPelOrDriv);fflush(stdin);system("cls");
		  		if(pilDafPelOrDriv == 1){
					
// <!-- START OF DAFTAR DRIVER -- >
		  			if((file = fopen("driver.txt", "a+")) == NULL){
				   		printf("File Tidak Ditemukan\n");system("pause");break;fclose(file);
				    } else {
						do{
						printf("+-----------------------------------------------+\n");
						printf("|             WELCOME NEW DRIVER ! ! !          |\n");
						printf("+-----------------------------------------------+\n\n\n");
						printf("   Yang harus diperhatikan : \n    No hp yang sudah pernah di daftarkan, \n    tidak bisa di gunakan kembali\n");
						printf("| Nama = "); gets(namaDriv); fflush(stdin);
						printf("| Nomor Hp = "); gets(no_hpDriv); fflush(stdin);
						printf("| Alamat = "); gets(alamatDriv); fflush(stdin);
						printf("| Username = "); gets(usernameDriv); fflush(stdin);
						printf("| Password = "); readOfPassword(passwordDriv); fflush(stdin);
						printf("\n\n");
						printf("| Plat No. = "); gets(platDriv); fflush(stdin);
						printf("| Nama Motor = "); gets(motorDriv); fflush(stdin);
						printf("+-----------------------------------------------+\n");
						
						if(strlen(no_hpDriv) < 11 || strlen(no_hpDriv) > 12){ printf("No telepon minimal 11 digit dan maksimal 12 digit\n");checknohpdriv=1;}
						checkDriver1 = SearchDriver2(driver,counterDriver,no_hpDriv);
						checkDriver2 = SearchDriver3(driver,counterDriver,usernameDriv);
						
						if(checkDriver1 != -1)	printf("No telepon tidak bisa digunakan, telah terdaftar sebagai akun lain\n");
						if(checkDriver2 != -1) printf("Username tidak bisa digunakan, telah terdaftar sebagai akun lain\n");
						
						//system("pause");system("cls");
						
						if(checkDriver1 == -1 && checkDriver2 == -1 && checknohpdriv == 0){
							file = fopen("counterd.txt", "r");
								fscanf(file, "%d",&counterIdDriver);
							fclose(file); counterIdDriver +=1;
							
							file = fopen("driver.txt", "a");
						   	fprintf(file, "%d#%s#%s#%s#%s#%s#%s#%s\n", counterIdDriver, namaDriv, no_hpDriv, alamatDriv, platDriv, motorDriv, usernameDriv, passwordDriv);
						   	fclose(file); 
					   	
					   		file = fopen("counterd.txt", "w+");
								fprintf(file, "%d",counterIdDriver);
							fclose(file);
							
							printf("data driver berhasil di tambahankan.\n");system("pause");system("cls");break;
						}
						}while(1);
					}
					//fflush(stdin);system("cls");
// <!-- END OF DAFTAR DRIVER -- >					
					
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
