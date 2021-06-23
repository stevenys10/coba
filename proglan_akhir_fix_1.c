/* Proyek Akhir Pemrogram Lanjut
Kelas           : Pemrograman Lanjut -02
Kelompok        : 8
Nama Anggota    :
        - Amanda Fairuz Syifa     (2006535653)
        - Firzy Allen             (2006577555)
        - Steven Yosua Saputra    (2006577290)
        - Zana Niswah Awahita     (2006577593)
Judul Proyek    : Program Perampungan dan Pembuatan SKL
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <omp.h>

#define MAX_LENGTH 256
#define SIZE 100


int search_database_sekolah(char input[]);
int display_database_sekolah();
int display_database_nilai(char nama_pelajaran[][SIZE]);
int display_menu();
int display_panduan();
int input_data(char nama_pelajaran[][SIZE]);
int olah_data(int array[]);

struct siswa{
    char nama[SIZE];
    int sekolah;
    int nilai[SIZE];
    char TTL[SIZE];
    int NIS;
    int NISN;
    char kelas[SIZE];
    struct siswa *next;
};

int lihat_data_siswa(struct siswa *data,char nama_pelajaran[][SIZE]);
int cetak_SKL(struct siswa *data1);

struct siswa *head=NULL;
struct siswa *ptr=NULL;
struct siswa *temp=NULL;
int main(){
	
	int sentinel_1 = 0;
	
    struct siswa *data=NULL;
    struct siswa *data1=NULL;
    
    printf ("===============================================================================================================\n");
	printf ("\n\t\t\t\t\tPROGRAM PERAMPUNGAN DAN PEMBUATAN SKL\n\n");
	printf ("===============================================================================================================\n");
	printf ("\n      Program ini dapat membantu pendataan siswa dan membantu proses pencetakan surat keterangan lulus (SKL).");
	printf ("\n\t\t\tSilahkan baca panduan untuk mengetahui cara menggunakan program!\n");
	printf ("\n\n\nSilahkan tekan tombol apapun untuk melanjutkan...");
	getch ();
	system("cls");
	printf("test");
    menu:
        display_menu ();
        int pilihan;
        char input[SIZE];
        char nama_pelajaran[SIZE][SIZE];
        display_database_nilai(nama_pelajaran);
            printf("\nMasukkan Pilihan: ");
            scanf("%d", &pilihan);
            
            switch(pilihan){
                case 1 :
                	// input data siswa 
                    system("cls");
                    input_data(nama_pelajaran);
                    system("cls");
                    sentinel_1 = 1;
                    goto menu;
                    break;
                case 2 :
                	//lihat data siswa
                	if (sentinel_1 ==1){
	                	system("cls");
	                    lihat_data_siswa(data,nama_pelajaran);
	                    printf("\n\nPress enter to return");
	                    getchar();
	                    getchar();
	                    system("cls");
	                    goto menu;	
					}
					else{
						system ("cls");
						printf ("Masukkan terlebih dahulu input data.");
						printf ("\n press enter to return...");
						getchar ();
						getchar ();
						system ("cls");
						goto menu;
					}
                    break;
                case 3 :
                //lihat daftar sekolah
                    system("cls");
                    int temp_display;
                    temp_display=display_database_sekolah();
                    if (temp_display==1){
                        system("cls");
                        getchar();
                        printf("Masukkan nama sekolah Anda: ");
                        scanf(" %[^\n]", input);
                        search_database_sekolah (input);
                        printf("\nPress enter to return");
                        getchar();
                        getchar();
                        system("cls");
                        goto menu;
                    }
                    if (temp_display==0){
                        system("cls");
                        goto menu;
                    }
                    //lihat_sekolah();
                    break;
                case 4 :    
                    //cetak SKL
                    system("cls");
                    cetak_SKL(data1);
                    system ("cls");
                    goto menu;
                    break;
                case 5 :
                    //display panduan
                    system("cls");
                    display_panduan();
                    system ("cls");
                    goto menu;
                    break;
                case 6 :
                    //exit
                    system("cls");
                    keluar();
                    break;
                //terdapat default untuk Error Handling apabila User memasukkan pilihan yang salah
                default :
                    system ("cls");
                    printf("Pilihan anda tidak sesuai.\nSilahkan ulangi pilihan\n");
                    //sleep (1);
            }
	}


int search_database_sekolah(char input[]){
    int temp=0;
    int counter = 1;
    char buffer_2[20];
    char nama[SIZE];
    int npsn_temp;
    char *file_database = "database_sekolah.txt";
    FILE *fd = fopen(file_database,"a++");

    if (fd==NULL){
        printf("Error, cannot open the file");
        return 0;
    }

    char buffer[MAX_LENGTH];
    int i;

    for (i=0;i<strlen(input);i++){
        input[i] = toupper(input[i]);
    }
    
    
    while (fgets(buffer, MAX_LENGTH, fd)){
        if (strncmp(buffer,input,strlen(input))==0){
            printf("\n%d. %s", counter, buffer);
            temp=1;
        }
        counter++;
    }
    if (temp==0){
        printf("\nNama sekolah Anda tidak terdaftar");
        printf("\nMasukkan nama sekolah Anda (Memasukkan ke dalam database: ");
        getchar();
        scanf("%[^\n]", &nama);
        printf("\nMasukkan npsn sekolah Anda (Memasukkan ke dalam database: ");
        scanf("%d", &npsn_temp);
        for (i=0;i<strlen(nama);i++){
            nama[i] = toupper(nama[i]);
        }
        fprintf(fd,"\n%s;%d",nama,npsn_temp);
    }
    fclose(fd);
}

int display_database_sekolah(){
    int i;
    int counter=1;
    char temp;
    char *file_database = "database_sekolah.txt";
    FILE *fd = fopen(file_database,"r");

    if (fd==NULL){
        printf("Error, cannot open the file");
        return 0;
    }

    char buffer[MAX_LENGTH];
    while (fgets(buffer, MAX_LENGTH, fd)){
        printf("%d. ", counter);
        for (i=0;i<strlen(buffer);i++){
            if (buffer[i]==';'){
                printf(" ");
                continue;
            }
            printf("%c", buffer[i]);
        }
        counter++;
    }
    fclose(fd);
    again:
        printf("\n\nApakah Anda ingin mencari nama sekolah Anda(Y/N)\n>>");
        getchar();
        scanf("%c", &temp);
        if (temp=='Y'||temp=='y'){
            system("cls");
            return 1;
        }
        else if(temp=='N'||temp=='n'){
            system("cls");
            return 0;
        }
        else{
            printf("pilihan Anda tidak sesuai. Silahkan memasukkan kembali pilihan Anda\n\n");
            goto again;
        }
}

int display_menu (){
  printf ("\n\nMenu Layanan :\n");
  printf ("1. Input data siswa\n");
  printf ("2. Lihat data siswa\n");
  printf ("3. Melihat sekolah\n");
  printf ("4. Cetak SKL\n");
  printf ("5. Panduan\n");
  printf ("6. Exit\n");
}

int input_data(char nama_pelajaran[][SIZE]){
    int sentinel = 1;
    int i;
    char answer;
	system("cls");
	printf("\n================================================\n");
	printf("                   Input Data           \n");
	printf("================================================\n");

    while(sentinel != -1){
            temp = malloc(sizeof(struct siswa));
            ptr=head;
            printf("\nCatatan: Nomor indeks sekolah dapat dilihat pada menu nomor 3.\n");
            printf("\nNama\t\t\t: ");
            scanf(" %[^\n]", temp->nama);
            printf ("\nIndeks Sekolah\t\t: ");
            scanf (" %d",&temp->sekolah);
            printf("\nTempat, tanggal lahir\t: ");
            scanf(" %[^\n]", temp->TTL);
            printf("\nNIS\t\t\t: ");
            scanf(" %d", &temp->NIS);
            printf("\nNISN\t\t\t: ");
            scanf(" %d", &temp->NISN);
            printf("\nKelas\t\t\t: ");
            scanf(" %[^\n]", temp->kelas);
            for (i=0;i<14;i++){
                printf("\nNilai %s\t: ", nama_pelajaran[i]);
                scanf(" %d", &temp->nilai[i]);
                if( temp->nilai[i] < 0 || temp->nilai[i] > 100){
                    while(temp->nilai[i] < 0 || temp->nilai[i] > 100){
                        printf("\nMasukkan kembali nilai %s\t: ", nama_pelajaran[i]);
                        scanf(" %d", &temp->nilai[i]);
                    }
                } 
                else{
                    continue;
                }
            }
            
            temp->next=NULL;
            answer:
                printf("\n\nApakah Anda ingin memasukkan data kembali(Y/N)= ");
                scanf("%s", &answer);
            
                if(answer=='y'||answer=='Y'){
                    if(head==NULL){
                        head = temp;
                        continue;
                    }
                    while(ptr->next!=NULL){
                        ptr=ptr->next;
                    }
                    ptr->next=temp;
                    continue;
                }
                else if(answer=='n'||answer=='N'){
                    if(head==NULL){
                        head = temp;
                        break;
                    }
                    while(ptr->next!=NULL){
                        ptr=ptr->next;
                    }
                    ptr->next=temp;
                    sentinel=-1;
                    continue;
                }
                else{
                    printf("\nInputan yang Anda masukkan salah. Silahkan memasukkan kembali input Anda.\n");
                    goto answer;
                }
    }
}

int display_database_nilai(char nama_pelajaran[][SIZE]){
    char *file_database = "database_nilai.txt";
    FILE *fd = fopen(file_database,"r");
    int i=0, j=0;

    if (fd==NULL){
        printf("Error, cannot open the file");
        return 0;
    }

    char buffer[MAX_LENGTH];
    while (fgets(buffer, MAX_LENGTH, fd)){
    	for (i=0;i<strlen(buffer);i++){
            if (buffer[i]==';'){
            	break;
            }
            nama_pelajaran[j][i]=buffer[i];
        }
        j++;
    }
    fclose(fd);
}

int display_panduan(){
    system ("cls");
    printf ("\t\t========================================\n");
    printf ("\t\t\t\tPANDUAN\n");
    printf ("\t\t========================================\n\n");
    printf ("Program ini merupakan layanan pembuatan SKL(Surat Keterangan Lulus) untuk siswa.\n");
    printf ("Tujuan dari pembuatan program ini akan memudahkan sekolah dalam menyimpan");
    printf ("data peserta didik serta mencetak SKL.\n");
    printf ("Pengguna akan memasukkan data berupa:\n1.Nama Siswa \n2.Tempat Tanggal Lahir ");
    printf ("\n3.NIS \n4.NISN \n5.Kelas \n6.Nilai");
    printf ("\nKemudian program akan mengolah nilai dengan menampilkan");
    printf ("hasil nilai rata-rata serta program juga dapat mencetak SKL tersebut");
    printf ("\nSilahkan tekan tombol apapun untuk melanjutkan...\n");
	getchar();
	getchar();
}

int keluar(){
    int pil;
	system ("cls");
	printf("\n=========================================================\n");
    printf("\t\tExit\n");
    printf("=========================================================\n");
	printf ("\nApakah anda ingin melanjutkan menggunakan program ini?\n\n");
	printf ("\t1. Ya\n\t2. Tidak\n\n");
	printf ("Pilihan : ");
	scanf ("%d", &pil);
	if (pil == 1){
		system("cls");
	}
	else if (pil == 2){
		system("cls");
		printf ("Terima kasih telah menggunakan program ini!\n");
		exit (0);
	}
	//terdapat default untuk Error Handling apabila User memasukkan pilihan yang salah
	else {
		printf ("\nPilihan yang anda masukkan salah, silahkan coba lagi.\n");
		//sleep(1);
		keluar();
	}
}

int cetak_SKL(struct siswa *data1){
    system ("cls");
    int counter = 1, print, i, j=1, k, counter2=0,l;
    char buffer[MAX_LENGTH];
	char temp[SIZE];
	data1 = head;

	while(data1 != NULL){
		printf("%d. %s\n", counter++, data1->nama);
		data1 = data1->next;
	}

	printf("\nMasukkan nomor index yang ingin anda cetak: ");
	scanf("%d", &print);
    
    data1 = head;
    
    for(i=1; i<= counter; i++){
    	if(i == print){
			printf("\n\t\t\t\t\t DINAS PENDIDIKAN");
			printf("\n\t\t\t\t         ");
			
			char *file_database = "database_sekolah.txt";
	    	FILE *fd = fopen(file_database,"r");
		    while (fgets(buffer, MAX_LENGTH, fd)){
		       if (j==data1->sekolah){
					for (l=0;l<strlen(buffer);l++){
					    if (buffer[l]==';'){
					    	fclose(fd);
			                break;
			            }
			            temp[l] = buffer[l];
			            printf("%c", buffer[l]);
			        }
			    }
			    j++;
			 }
			printf("\n\t=======================================================================================\n");
		    printf("\n\t\t\t\t      SURAT KETERANGAN LULUS");
			printf("\n\t\t\tPEMINATAN MATEMATIKA DAN ILMU PENGETAHUAN ALAM (MIPA)");
		    printf("\n\t\t\t\t    TAHUN PELAJARAN 2020/2021\n\n");
		    printf("\n\t Kepala %s  menerangkan dengan sesungguhnya bahwa:", temp);
		    printf("\n\t\t1. Nama\t\t: %s", data1->nama);
		    printf("\n\t\t2. TTL\t\t: %s", data1->TTL);
		    printf("\n\t\t3. NIS\t\t: %d", data1->NIS);
		    printf("\n\t\t4. NISN\t\t: %d", data1->NISN);
		    printf("\n\t\t5. Kelas\t: %s", data1->kelas);
		    printf("\n\t adalah peserta Ujian Sekolah (US) %s Tahun Pelajaran 2020/2021 dan\n", temp);
		    printf("\n\t berdasarkan ketuntasan dari seluruh program pembelajaran pada kurikulum 2013, kriteria kelulusan\n");
		    printf("\t peserta didik pada satuan %s  yang sesuai dengan peraturan\n", temp);
		    printf("\n\t perundang-undangan dan Hasil Rapat Pleno Dewan Pendidik tentang kelulusan Peserta Didik\n");
		    printf("\t %s  dinyatakan :\n", temp);
		 
			for(k = 0; k<14; k++){
				if(data1->nilai[k]==0){
					printf("\n\t\t\t\tTIDAK LULUS");
					break;
				}
				else if(data1->nilai[k]>0){
					counter2++;
				}
			}		 
			
			if(counter2==14)
				printf("\n\t\t\t\t\t\t      LULUS");
		 
		    printf("\n\t dengan hasil nilai sebagai berikut : \n");
		    printf("\n\t\t No \t\t\t\t Mata Pelajaran \t\t\t Nilai Ujian Sekolah\n");
		    printf("\n\n\tKelompok A");
		    printf("\n\t\t 1.\t\t\tPendidikan Agama dan Budi Pekerti Luhur\t\t\t %d", data1->nilai[0]);
		    printf("\n\t\t 2.\t\t\tPendidikan Pancasila dan Kewarganegaraan\t\t %d", data1->nilai[1]);
		    printf("\n\t\t 3.\t\t\tBahasa Indonesia\t\t\t\t\t %d", data1->nilai[2]);
		    printf("\n\t\t 4.\t\t\tMatematika\t\t\t\t\t\t %d", data1->nilai[3]);
		    printf("\n\t\t 5.\t\t\tSejarah Indonesia\t\t\t\t\t %d", data1->nilai[4]);
		    printf("\n\t\t 6.\t\t\tBahasa Inggris\t\t\t\t\t\t %d", data1->nilai[5]);
		
		    printf("\n\n\tKelompok B");
		    printf("\n\t\t 7.\t\t\tSeni Budaya\t\t\t\t\t\t %d", data1->nilai[6]);
		    printf("\n\t\t 8.\t\t\tPendidikan Jasmani, Olahraga, dan Kesehatan\t\t %d", data1->nilai[7]);
		    printf("\n\t\t 9.\t\t\tPrakarya dan Kewirausahaan\t\t\t\t %d", data1->nilai[8]);
		
		    printf("\n\n\tKelompok C");
		    printf("\n\t\t 10.\t\t\tMatematika Lintas Minat\t\t\t\t\t %d", data1->nilai[9]);
		    printf("\n\t\t 11.\t\t\tBiologi\t\t\t\t\t\t\t %d", data1->nilai[10]);
		    printf("\n\t\t 12.\t\t\tFisika\t\t\t\t\t\t\t %d", data1->nilai[11]);
		    printf("\n\t\t 13.\t\t\tKimia\t\t\t\t\t\t\t %d", data1->nilai[12]);
		    printf("\n\t\t 14.\t\t\tBahasa dan Sastra Inggris Lintas Minat\t\t\t %d", data1->nilai[13]);
		
			olah_data(data1->nilai);
		    printf("\n\n\t Surat Keterangan Lulus ini dapat digunakan sebagai pengganti ijazah sampai diterbitkan dokumen ");
		    printf("\n\t ijazah aslinya.");
		    
		    printf("\n\n\t\t\t\t\t\t\t\t\t    ........,..................\n");
		printf("\n\n\n\n\n\t\t\t\t\t\t\t\t\t(            			 )");
		
		    printf("\n\n\nSilahkan tekan tombol apapun untuk melanjutkan...\n");

		}
		data1 = data1->next;
		if (data1==NULL){
			break;
		}
	}
		getchar();
		getchar();
}

int lihat_data_siswa(struct siswa *data, char nama_pelajaran[][SIZE]){
    int i;
    int counter=7;
    int j=1;
    int sentinel = 1;
    data = head;
    
    char buffer[MAX_LENGTH];
    printf ("\t\t========================================\n");
    printf ("\t\t\t\tDATA SISWA\n");
    printf ("\t\t========================================\n\n");
    while(sentinel==1){
	    printf("\n\t\t1. Nama \t\t: %s", data->nama);
        printf ("\n\t\t2. Nama Sekolah \t: ");
        char *file_database = "database_sekolah.txt";
    	FILE *fd = fopen(file_database,"r");
	    while (fgets(buffer, MAX_LENGTH, fd)){
	       if (j==data->sekolah){
				for (i=0;i<strlen(buffer);i++){
		            if (buffer[i]==';'){
		                printf(" ");
		                continue;
		            }
		            printf("%c", buffer[i]);
		        }
		        fclose(fd);
		    }
		    j++;
		 }
        printf("\t\t3. TTL \t\t\t: %s", data->TTL);
        printf("\n\t\t4. NIS \t\t\t: %d", data->NIS);
        printf("\n\t\t5. NISN \t\t: %d", data->NISN);
        printf("\n\t\t6. Kelas \t\t: %s", data->kelas);
        for(i=0;i<14;i++){
            printf("\n\t\t%d. Nilai Siswa %s: %d",counter++,nama_pelajaran[i],data->nilai[i]);  
        }  
        data=data->next;
        j=1;
        counter = 7;
        printf("\n\n");
        if(data == NULL){
            sentinel = -1;
        }
    }
}
    
    
int olah_data (int array[]){
	omp_set_num_threads(4);
	float average, sum;
	#pragma omp parallel
	{
		int i;
		int localsum = 0;
		
		#pragma omp for
		for (i=0;i<14;i++){
			localsum += array[i];
		}
		#pragma omp critical
		sum += localsum;
	}
	average = sum/14;
	printf ("\n\n\t\t\t\t\t\tRATA-RATA\t\t\t\t\t %.2f", average);
}
