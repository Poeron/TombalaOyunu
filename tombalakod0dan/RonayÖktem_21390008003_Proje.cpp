/*
Ronay ÖKTEM
21390008003 
Bilgisayar Mühendisliði
MFBÝM1001: PROGRAMLAMAYA GÝRÝÞ I
Dr. Öðr. Üyesi Taner UÇKAN
*/
#include<iostream>
#include<ctime>
#include<cstdlib>
#include<iomanip>
using namespace std;
//bu aralýkta prototipleri oluþturdum
void KartOlusturma(int kartlar[][15]);
bool IcindeVarMi(int dizi[][15], int hangiKart, int sayi);
void KartlariYazdirma(int dizi[][15]);
void TorbayiKaristir(int torba[]);
bool DizideMevcutMu(int dizi[], int sayi,int boyut);
void TorbayiYazdir(int dizi[]);
void RastgeleNumaraOlusturma(int kart[], int kisi);
void KartDagitma(int kartlar[][15], int oynanacakKartlar[][15], int rastgeleNumaralar[], int kisi);
bool TorbaylaKarsilastir(int torba[], int oynanacakKartlar[][15], int kisi, int rastgeleNumaralar[], int oyuncuPuan[]);
void OynanacakKartlariYazdirma(int oynanacakKartlar[][15], int kisi, int rastgeleNumaralar[]);
void PuanTablosu(int oyuncuPuan[], int hangiOyuncu, int puan);
void PuanTablosunuYazdir(int oyuncuPuan[], int kisi);
//bu aralýkta prototipleri oluþturdum
int main()
{
	int kartlar[10][15] = {}, oyuncuPuan[5] = {};//tüm oyuncularýn puanýný 0 kabul ettim
	int kisi, set = 0;
	srand(time(0));//rastgele sayýlar üretebilmek için kullandým
	setlocale(LC_ALL, "Turkish");//türkçe harfler kullanabilmek için yazdým
	cout << "***** Tombala Oyununa Hoþgeldiniz *****\n";
	KartOlusturma(kartlar);//kartlarý oluþturdum
	KartlariYazdirma(kartlar);//kartlarý ekrana yazdýrdým
	cout << "\nOyunu kaç kiþi oynayacaksýnýz ? (2-5)\n";
	cin >> kisi;
	while (kisi > 5 || kisi < 2)//kiþi sayýsýný doðru girene kadar döngüde kalmasý için while kullandým
	{
		cout << "\nLütfen 2 ile 5 arasýnda bir deðer giriniz.\n";
		cin >> kisi;
	}
	while (set<3)//set sayýsýný 0dan baþlatarak her döngüde 1 arttýrdým böylece 3 set oynanabilecek
	{//her döngünün baþýnda kartlarý numaralarý torbayý sýfýrladým.
		int rastgeleNumaralar[5] = {}, torba[90] = {}, oynanacakKartlar[5][15] = {};
		TorbayiKaristir(torba);//torbayý birbirinden farklý 1 ile 90 arasýndaki sayýlarla rastgele doldurdum
		RastgeleNumaraOlusturma(rastgeleNumaralar, kisi);//kiþi sayýsýna göre rastgele numaralar verdim
		cout << "\nDaðýtýlan Kartlar :\n";//rastgele çýkan numaralarý ekrana yazdýrdým
		for (int i = 0; i < kisi; i++)
		{
			cout << rastgeleNumaralar[i] << " ";
		}
		cout << endl;
		KartDagitma(kartlar, oynanacakKartlar, rastgeleNumaralar, kisi);//oluþturduðum rastgele rakamlar ile oyunculara kartlarý daðýttým
		set += TorbaylaKarsilastir(torba, oynanacakKartlar, kisi, rastgeleNumaralar, oyuncuPuan);//biri tombala yaptýðýnda 1 döndürdü ve set deðiþkenini 1 arttýrdý
		cout << "\nTorbadan çekilen numaralar :\n";
		TorbayiYazdir(torba);//torbadaki tüm sayýlarý sýrasýyla ekrana yazdýrdým
		cout << endl << endl;
		cout <<"*****************" << set << ". set bitti*****************\n\n";
	}
	PuanTablosunuYazdir(oyuncuPuan, kisi);//son olarak puan tablosunu ekrana yazdým
	return 758;
}
void KartOlusturma(int kartlar[][15])
{//bu fonksiyonda sayýlarý farklý tombala kartlarý oluþturdum
	int sayi;
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 15; j++)
		{
			sayi = rand() % 90 + 1;
			while (IcindeVarMi(kartlar,i,sayi))
			{//eðer dizide mevcutsa 1 döndürecek ve dizide olmayana kadar devam edecek
				sayi = rand() % 90 + 1;
			}
			kartlar[i][j] = sayi;
		}
	}
}
bool IcindeVarMi(int dizi[][15], int hangiKart, int sayi)
{//kart oluþtururken sayýlarýn farklý olup olmadýðýný kontrol ettiðim bool tipi fonksiyon
	for (int i = 0; i < 15; i++)
	{
		if (dizi[hangiKart][i]==sayi)
		{
			return 1;
		}
	}
	return 0;
}
void KartlariYazdirma(int dizi[][15])
{//tombala kartlarýný ekrana yazdýrmak için oluþturduðum fonksiyon
	for (int i = 0; i < 10; i++)
	{
		cout << i << " Numaralý Kart = ";
		for (int j = 0; j < 15; j++)
		{
			cout << setw(4) << dizi[i][j];
		}
		cout << endl;
	}
}
void TorbayiKaristir(int torba[])
{//torba adlý diziyi 1 ile 90 arasýndaki sayýlarla rastgele dizmek için oluþturduðum fonksiyon
	int sayi;
	for (int i = 0; i < 90; i++)
	{
		sayi = rand() % 90 + 1;
		while (DizideMevcutMu(torba,sayi,i))
		{//eðer dizide mevcutsa 1 döndürecek ve dizide olmayana kadar devam edecek
			sayi = rand() % 90 + 1;
		}
		torba[i] = sayi;
	}
}
bool DizideMevcutMu(int dizi[],int sayi,int boyut)
{//gönderdiðim sayýyý gönderdiðim tek boyutlu dizinin içinde olup olmadýðýný kontrol ettiðim bool tipi fonksiyon
	for (int i = 0; i < boyut; i++)
	{
		if (dizi[i] == sayi)
		{
			return 1;
		}
	}
	return 0;
}
void TorbayiYazdir(int dizi[])
{//torbayý ekrana yazdýrdýðým fonksiyon
	for (int i = 0; i < 90; i++)
	{
		if (i%10==0)
		{//her 10 sayýda 1 alt satýra geçmesini saðladým burda
			cout << endl;
		}
		cout << setw(4) << dizi[i];
	}
}
void RastgeleNumaraOlusturma(int kart[],int kisi)
{//kiþi sayýsýna göre 0 ile 10 arasýnda birbirinden farklý rastgele rakamlar oluþturan fonksiyon
	int rndm;
	for (int i = 0; i < kisi; i++)
	{
		rndm = rand() % 10;
		while (DizideMevcutMu(kart,rndm,kisi))
		{//eðer dizide mevcutsa 1 döndürecek ve dizide olmayana kadar devam edecek
			rndm = rand() % 10;
		}
		kart[i] = rndm;
	}
}
void KartDagitma(int kartlar[][15], int oynanacakKartlar[][15],int rastgeleNumaralar[],int kisi)
{//oluþturduðum rastgele rakamlar ile oyunculara kartlarý daðýttýðým fonksiyon
	for (int i = 0; i < kisi; i++)
	{
		for (int j = 0; j < 15; j++)
		{
			oynanacakKartlar[i][j] = kartlar[rastgeleNumaralar[i]][j];
		}
	}
}
bool TorbaylaKarsilastir(int torba[], int oynanacakKartlar[][15], int kisi,int rastgeleNumaralar[],int oyuncuPuan[])
{//torbayý kartlardaki her bir sayý ile karþýlaþtýrdýðým fonksiyon
	int cinko = 0;
	int oyuncuCinko[5] = {};
	for (int i = 0; i < 90; i++)//torbanýn indislerine eriþmek için kullandýðým for döngüsü
	{
		for (int j = 0; j < kisi; j++)//kartlara eriþmek için kullandýðým for döngüsü
		{
			for (int k = 0; k < 15; k++)//kartlardaki sayýlara eriþmek için kullandýðým for döngüsü
			{
				if (torba[i]==oynanacakKartlar[j][k])
				{//eðer torbadan çekilen sayý karttaki sayýya eþitse yerine -1 yazýcak ve oyuncunun çinko deðerini 1 arttýracak
					oynanacakKartlar[j][k] = -1;
					oyuncuCinko[j]++;
					if (oyuncuCinko[j] == 5)
					{//oyuncunun çinko deðeri 5e ulaþýrsa ekrana 1. çinkoyu yaptýðý yazýcak ve puaný tanýmlanacak
						if (cinko == 0)
						{//cinko diye bir deðiþken tanýmlamamýn sebebi 1 kere 1. çinko yapýlýrsa cinko deðerini arttýrýcak ve bir daha if'in içindekiler yapýlmayacak
							cout << endl << j + 1 << " numaralý oyuncu 1. çinkoyu yaptý!\n";
							cinko++;
							cout << "\nKartlardaki son durum : \n\n";
							OynanacakKartlariYazdirma(oynanacakKartlar, kisi, rastgeleNumaralar);
							PuanTablosu(oyuncuPuan, j, 5);
						}
					}
					else if (oyuncuCinko[j] == 10)
					{
						if (cinko == 1)
						{//oyuncunun çinko deðeri 10a ulaþýrsa ekrana 2. çinkoyu yaptýðý yazýcak ve puaný tanýmlanacak
							cout << endl << j + 1 << " numaralý oyuncu 2. çinkoyu yaptý!\n";
							cinko++;
							cout << "\nKartlardaki son durum : \n\n";
							OynanacakKartlariYazdirma(oynanacakKartlar, kisi, rastgeleNumaralar);
							PuanTablosu(oyuncuPuan, j, 10);
						}
					}
					else if (oyuncuCinko[j] == 15)
					{//oyuncunun çinko deðeri 15e ulaþýrsa ekrana tombala yaptýðý yazýcak ve puaný tanýmlanacak
						cout << endl << j + 1 << " numaralý oyuncu TOMBALA yaptý!!!\n";
						cout << "\nKartlardaki son durum : \n\n";
						OynanacakKartlariYazdirma(oynanacakKartlar, kisi, rastgeleNumaralar);
						PuanTablosu(oyuncuPuan, j, 15);
						return 1;
						// deðer döndürmesinin sebebi biri tombala yaptýysa bu fonksiyonu burda bitirmek
						// 1 döndürmesinin sebebi ise set deðiþkenine eklenmesi ve set deðiþkeni 3 olduðunda kodun durmasý
					}
				}
			}
		}
	}
}
void OynanacakKartlariYazdirma(int oynanacakKartlar[][15], int kisi, int rastgeleNumaralar[])
{//oyunculara atanan kartlarý ekrana yazdýrma fonksiyonu
	for (int i = 0; i < kisi; i++)
	{
		cout << i+1 << ". oyuncunun kartý = ";
		for (int j = 0; j < 15; j++)
		{
			cout << setw(4) << oynanacakKartlar[i][j];
		}
		cout << endl;
	}
}
void PuanTablosu(int oyuncuPuan[], int hangiOyuncu, int puan)
{//puanlarýn toplanmasý için yaptýðým fonksiyon
	oyuncuPuan[hangiOyuncu] += puan;
}
void PuanTablosunuYazdir(int oyuncuPuan[],int kisi)
{//puan toplamlarýnýn en büyüðünü bulup tüm oyuncularýn puanlarýyla beraber ekrana kazananý yazdýrmak için kullandýðým fonksiyon
	cout << "~~~~~~~~~Puan Tablosu~~~~~~~~~\n";
	for (int i = 0; i < kisi; i++)
	{
		cout << i + 1 << ". oyuncunun puaný = " << oyuncuPuan[i] << endl;
	}
	int enYuksekPuan = oyuncuPuan[0];//en yüksek puan olarak ilk oyuncunun puanýný kabul ettim
	int kazananOyuncu = 0;//en yüksek puana sahip oyuncunun dizideki indisini 0 olarak kabul ettim
	int kazananOyuncu2 = -1;//baþka kazanan var mý diye kontrol etmek için oluþturduðum deðiþken
	for (int i = 1; i < kisi; i++)
	{
		if (enYuksekPuan < oyuncuPuan[i])
		{
			enYuksekPuan = oyuncuPuan[i];//daha yüksek puanlý bir oyuncu varsa artýk en yüksek puan deðiþkeni onun puaný olacak ve döngüde o puanla iþlem yapýlacak
			kazananOyuncu = i;//daha yüksek puanlý bir oyuncu bulunduðunda onun indisini deðiþkende saklayacak
		}
		else if (enYuksekPuan == oyuncuPuan[i])
		{
			kazananOyuncu2 = oyuncuPuan[i];
		}
	}
	if (kazananOyuncu2 == enYuksekPuan)
	{//2.kazanan 1.ye eþitse kazanan yok yazdýrdýðým if yapýsý
		cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
		cout << "kazanan yok oyun berabere";
	}
	else
	{//oyun berabere deðilse kazananý yazdýrdýðým yapý
		cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
		cout << enYuksekPuan << " puan ile kazanan " << kazananOyuncu + 1 << ". oyuncu.\n";
	}
}