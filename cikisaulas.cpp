#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include <time.h>

struct node{
	int data1;
	int data2;
	int data3;
	struct node *next;
};

struct node* top=NULL;//stack icin kullanilan top (Ustteki eleman)

struct node* head=NULL;
struct node* tail=NULL;
struct node* gecici;




void enqueue(int a , int b, int c) {
	struct node *move=(struct node *)malloc(sizeof(struct node));
	move->data1=a;//x koordinati
	move->data2=b;//y koordinati
	move->data3=c;//kuyrukta anlamli bir sekilde gosterim icin secici

	if (head==NULL && tail==NULL) {
		head=move;
		tail=move;

	}else{
		tail->next=move;
		tail=move;

	}
}




void printenqueue(/* arguments */) {
	int i=1;
	if (head==NULL) {
		printf("Kuyruk bos.\n");
		return;
	}
	gecici=head;
	while (gecici!=NULL) {
		
		if (gecici->data3==1) {
			printf("%d.Bariyer olusturuldu.[%d,%d]\n",i,gecici->data1,gecici->data2);
			gecici=gecici->next;
			i++;
		}else
		if (gecici->data3==2) {
			printf("%d.Kapi olusturuldu.[%d,%d]\n",i,gecici->data1,gecici->data2);
			gecici=gecici->next;
			i++;
		}else
		if (gecici->data3==3) {
			printf("%d.Anahtar olusturuldu.[%d,%d]\n",i,gecici->data1,gecici->data2);
			gecici=gecici->next;
			i++;
		}else
		if (gecici->data3==4) {
			printf("%d.Anahtar duvara denk geldigi icin tekrar olusturuldu.[%d,%d]\n",i,gecici->data1,gecici->data2);
			gecici=gecici->next;
			i++;
		}else
		if (gecici->data3==5) {
			printf("%d.Robot hareket etti.[%d,%d]\n",i,gecici->data1,gecici->data2);
			gecici=gecici->next;
			i++;
		}else
		if (gecici->data3==6) {
			printf("%d.Kazandiniz.Oyun sonlandirildi.[%d,%d]\n",i,gecici->data1,gecici->data2);
			gecici=gecici->next;
			i++;
		}else
		if (gecici->data3==7) {
			printf("%d.Alandan ciktigi icin kaybetti.[%d,%d]\n",i,gecici->data1,gecici->data2);
			gecici=gecici->next;
			i++;
		}else
		if (gecici->data3==8) {
			printf("%d.**********Robot engele carpti**********.[%d,%d]\n",i,gecici->data1,gecici->data2);
			gecici=gecici->next;
			i++;
		}
	}
}




//struct icin koordinat ekleme fonksiyonu(push)
void push(int a,int b) {
	struct node *list=(struct node *)malloc(sizeof(struct node));
	list->data1=a;
	list->data2=b;
	list->next=NULL;
	if (top!=NULL) {
		list->next=top;
	}
	top=list;
	printf("Robot koordinati=%d,%d\n",top->data1,top->data2);
	printf("-------------------------------------\n");
}

void pop(/* arguments */) {
	if (top==NULL) {
		printf("Stack zaten bos.\n");
	}
	else{
		struct node *temp;
		temp=top;
		top=top->next;
		free(temp);
		printf("Robot koordinati= %d,%d\n",top->data1,top->data2);
		printf("-------------------------------------\n");
	}

}

int peek(){ 
	return (top->data1,top->data2);
}

//bariyer olusturma fonksiyonu
struct node *barrier(){
  int sayac=1,en,boy;
  srand(time(NULL));
  struct node *ilk,*list;
  ilk=(struct node *)malloc(sizeof(struct node));
  en=rand()%100;
  boy=rand()%50;
  ilk->data1=en;
  ilk->data2=boy;
  list=ilk;
	enqueue(list->data1,list->data2,1);
  while(sayac != 30){
    list->next=(struct node *)malloc(sizeof(struct node));
    list=list->next;
    en=rand()%100;
    boy=rand()%50;
    list->data1=en;
    list->data2=boy;
		enqueue(list->data1,list->data2,1);
    sayac ++;
  }

  list->next=NULL;
  list=ilk;

  return list;
  }


//bariyerlerin koordinatlarini gosteren fonksiyon
void barriershow(struct node *list){
  int sayac=1;
	while(list!=NULL){
    printf("%d.Engel koordinati=%d,%d\n",sayac,list->data1,list->data2);
	  list=list->next;
    sayac++;
  }
}







//move fonksiyonu icerisinde hareketin engele gelip gelmedigini kontrol eden fonksiyon
int comparasion(int a ,int b,struct node *list){
	while (list !=NULL) {
		if (list->data1==a && list->data2==b) {
			return 1;
		}
		list=list->next;
	}
	return 0;
}

//kapi koordinatlari olusturuldu.
struct node *key(){
	struct node *key;
	key = (struct node *)malloc(sizeof(struct node));
	key ->data1=100;
	key ->data2=rand()%50;
	enqueue(key->data1,key->data2,2);
	return key;
}


//anahtar lokasyanu olusturuldu
struct node *key_location(int a,int b,struct node *bariyerler){
	struct node *list;
	int sonuc;
	list=(struct node *)malloc(sizeof(struct node));
	while (1) {
		list->data1=a+rand()%(101-a); 
		list->data2=b+rand()%(51-b);

		enqueue(list->data1,list->data2,3);

			printf("Key location= %d,%d \n",list->data1,list->data2);
			sonuc=comparasion(list->data1,list->data2,bariyerler);//anahtarin duvara denk gelip gelmemesini kontrol etmekte
			if (sonuc==1) {
				printf("\n");
				printf("Anahtar konumu duvara denk geldi, anahtar yeniden olusturuldu.\n");
				enqueue(list->data1,list->data2,4);
				printf("\n");

			}else{
				return list;

		}
	}
}


//zarin atilip gelen sayiya uygun olarak hareketin saglanmasi
int move(struct node *bariyerler){
    int zar=0;
  	int a=0;
  	int b=0;
  	int sonuc;
    struct node *temp,*anahtar,*keyloc;
		anahtar=key();
		printf("Cikis kapisi koordinati= [%d,%d]\n",anahtar->data1,anahtar->data2);
		temp=(struct node *)malloc(sizeof(struct node));
		temp->data1=a;
		temp->data2=b;
		temp->next=NULL;
		enqueue(temp->data1,temp->data2,5);
		keyloc=key_location(a,b,bariyerler);
		push(temp->data1,temp->data2);
		if (keyloc->data1==a &&keyloc->data2==b) {
			enqueue(keyloc->data1,keyloc->data2,6);
			return 1;
		}
		sonuc=comparasion(temp->data1,temp->data2,bariyerler);
		if (sonuc==1) {
			printf("Kor bahtim daha alana inemeden engele carpmayi nasil basardin....\n");
			enqueue(temp->data1,temp->data2,8);
			pop();
		}
    do{
    	printf("Zar atmak icin bir tusa basiniz.\n");
			getch();
    	zar=rand()%3;
			printf("Zar:%d\n",zar);
      	if (zar==0) {
				a+=2;
				if (a>=100) {
					printf("Robot koordinati= %d,%d\n",top->data1,top->data2);
					printf("-------------------------------------\n");
					enqueue(a,temp->data2,7);
					return 0;
				}
				if (b>50) {
					b=b%50;
				}
				keyloc=key_location(a,b,bariyerler);
				temp->data1=a;
				temp->data2=b;
				push(temp->data1,temp->data2);
				enqueue(temp->data1,temp->data2,5);
				sonuc=comparasion(temp->data1,temp->data2,bariyerler);
				if (sonuc==1) {
					printf("Engele carptin,hareket gecersiz.\n");
					enqueue(temp->data1,temp->data2,8);
					pop();
					a-=2;
				}
				if (keyloc->data1==a &&keyloc->data2==b) {
					enqueue(keyloc->data1,keyloc->data2,6);
				  return 1;
				}

        }
      	if (zar==1) {
				a+=0;
				b+=2;
				if (b>50) {
					b=b%50;
				}
				keyloc=key_location(a,b,bariyerler);
				temp->data1=a;
				temp->data2=b;
				push(temp->data1,temp->data2);
				enqueue(temp->data1,temp->data2,5);
				sonuc=comparasion(temp->data1,temp->data2,bariyerler);
				if (sonuc==1) {
					printf("Engele carptin,hareket gecersiz.\n");
					enqueue(temp->data1,temp->data2,8);
					pop();
					b-=2;
				}
				if (keyloc->data1==a &&keyloc->data2==b) {
					enqueue(keyloc->data1,keyloc->data2,6);
				  return 1;
				}

      }
      if (zar==2) {
        a +=1;
				b +=1;
				if (b>50) {
					b=b%50;
				}
				temp->data1=a;
				temp->data2=b;
				keyloc=key_location(a,b,bariyerler);
				push(temp->data1,temp->data2);
				enqueue(temp->data1,temp->data2,5);
				sonuc=comparasion(temp->data1,temp->data2,bariyerler);
				if (sonuc==1) {
					printf("Engele carptin,hareket gecersiz.\n");
					enqueue(temp->data1,temp->data2,8);
					pop();
					a-=1;
					b-=1;
				}
				if (keyloc->data1==a &&keyloc->data2==b) {
					enqueue(keyloc->data1,keyloc->data2,6);
				  return 1;
				}
      }
    } while(a<100);
		enqueue(keyloc->data1,keyloc->data2,7);
		return 0;

  }




//main fonksiyonu
  int main(){
		printf("\t\t\t\tOYUN KILAVUZU\n1.Oyunda amac her hamlede yeri degisen anahtari bulup cikis koordinatlarini almaktir.\n" );
		printf("2.Eger anahtari alirsaniz oyunu kazanmis sayilacaksiniz.\n" );
		printf("3.Eger x uzerinde 100 birim gider ve anahtari bulamazsaniz oyunu kaybetmis sayilacaksiniz.\n4.Bununla birlikte y ekseninde hareket etmekte esneklik payi vardir.\n");
		printf("5.Anahtarin her hamlede yeri degismekte ve daralan oyun alaninin disinda spamlanamayacak sekilde tasarlanmistir.\n\n\t\t\tHadi oyuna basla:) \n\n\n:))" );
		int final;
		char cev;
    struct node *bariyerler,*cinali;
    //bariyerler olusturuldu.
    bariyerler=barrier();
    //barriershow(bariyerler);
    final=move(bariyerler);
		if (final==1) {
			printf("Kazandiniz....\n");
		}else{
			printf("Kaybettiniz...\n");
		}
		printf("Oyun gunlugunu etkinlestirmek istermisiniz?\n\nYazdirmak icin e/E 'ye tiklayiniz.");
		
		scanf("%c",&cev);
		if (cev=='e'||cev=='E') {
			printenqueue();
			getch();
			return 0;
		}else{
			printf("Oyun sonlandiriliyor.\n");
			return 0;
		}

  }

