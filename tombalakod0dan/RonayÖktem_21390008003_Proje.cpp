/*
Ronay �KTEM
21390008003 
Bilgisayar M�hendisli�i
MFB�M1001: PROGRAMLAMAYA G�R�� I
Dr. ��r. �yesi Taner U�KAN
*/
#include<iostream>
#include<ctime>
#include<cstdlib>
#include<iomanip>
using namespace std;
//bu aral�kta prototipleri olu�turdum
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
//bu aral�kta prototipleri olu�turdum
int main()
{
	int kartlar[10][15] = {}, oyuncuPuan[5] = {};//t�m oyuncular�n puan�n� 0 kabul ettim
	int kisi, set = 0;
	srand(time(0));//rastgele say�lar �retebilmek i�in kulland�m
	setlocale(LC_ALL, "Turkish");//t�rk�e harfler kullanabilmek i�in yazd�m
	cout << "***** Tombala Oyununa Ho�geldiniz *****\n";
	KartOlusturma(kartlar);//kartlar� olu�turdum
	KartlariYazdirma(kartlar);//kartlar� ekrana yazd�rd�m
	cout << "\nOyunu ka� ki�i oynayacaks�n�z ? (2-5)\n";
	cin >> kisi;
	while (kisi > 5 || kisi < 2)//ki�i say�s�n� do�ru girene kadar d�ng�de kalmas� i�in while kulland�m
	{
		cout << "\nL�tfen 2 ile 5 aras�nda bir de�er giriniz.\n";
		cin >> kisi;
	}
	while (set<3)//set say�s�n� 0dan ba�latarak her d�ng�de 1 artt�rd�m b�ylece 3 set oynanabilecek
	{//her d�ng�n�n ba��nda kartlar� numaralar� torbay� s�f�rlad�m.
		int rastgeleNumaralar[5] = {}, torba[90] = {}, oynanacakKartlar[5][15] = {};
		TorbayiKaristir(torba);//torbay� birbirinden farkl� 1 ile 90 aras�ndaki say�larla rastgele doldurdum
		RastgeleNumaraOlusturma(rastgeleNumaralar, kisi);//ki�i say�s�na g�re rastgele numaralar verdim
		cout << "\nDa��t�lan Kartlar :\n";//rastgele ��kan numaralar� ekrana yazd�rd�m
		for (int i = 0; i < kisi; i++)
		{
			cout << rastgeleNumaralar[i] << " ";
		}
		cout << endl;
		KartDagitma(kartlar, oynanacakKartlar, rastgeleNumaralar, kisi);//olu�turdu�um rastgele rakamlar ile oyunculara kartlar� da��tt�m
		set += TorbaylaKarsilastir(torba, oynanacakKartlar, kisi, rastgeleNumaralar, oyuncuPuan);//biri tombala yapt���nda 1 d�nd�rd� ve set de�i�kenini 1 artt�rd�
		cout << "\nTorbadan �ekilen numaralar :\n";
		TorbayiYazdir(torba);//torbadaki t�m say�lar� s�ras�yla ekrana yazd�rd�m
		cout << endl << endl;
		cout <<"*****************" << set << ". set bitti*****************\n\n";
	}
	PuanTablosunuYazdir(oyuncuPuan, kisi);//son olarak puan tablosunu ekrana yazd�m
	return 758;
}
void KartOlusturma(int kartlar[][15])
{//bu fonksiyonda say�lar� farkl� tombala kartlar� olu�turdum
	int sayi;
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 15; j++)
		{
			sayi = rand() % 90 + 1;
			while (IcindeVarMi(kartlar,i,sayi))
			{//e�er dizide mevcutsa 1 d�nd�recek ve dizide olmayana kadar devam edecek
				sayi = rand() % 90 + 1;
			}
			kartlar[i][j] = sayi;
		}
	}
}
bool IcindeVarMi(int dizi[][15], int hangiKart, int sayi)
{//kart olu�tururken say�lar�n farkl� olup olmad���n� kontrol etti�im bool tipi fonksiyon
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
{//tombala kartlar�n� ekrana yazd�rmak i�in olu�turdu�um fonksiyon
	for (int i = 0; i < 10; i++)
	{
		cout << i << " Numaral� Kart = ";
		for (int j = 0; j < 15; j++)
		{
			cout << setw(4) << dizi[i][j];
		}
		cout << endl;
	}
}
void TorbayiKaristir(int torba[])
{//torba adl� diziyi 1 ile 90 aras�ndaki say�larla rastgele dizmek i�in olu�turdu�um fonksiyon
	int sayi;
	for (int i = 0; i < 90; i++)
	{
		sayi = rand() % 90 + 1;
		while (DizideMevcutMu(torba,sayi,i))
		{//e�er dizide mevcutsa 1 d�nd�recek ve dizide olmayana kadar devam edecek
			sayi = rand() % 90 + 1;
		}
		torba[i] = sayi;
	}
}
bool DizideMevcutMu(int dizi[],int sayi,int boyut)
{//g�nderdi�im say�y� g�nderdi�im tek boyutlu dizinin i�inde olup olmad���n� kontrol etti�im bool tipi fonksiyon
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
{//torbay� ekrana yazd�rd���m fonksiyon
	for (int i = 0; i < 90; i++)
	{
		if (i%10==0)
		{//her 10 say�da 1 alt sat�ra ge�mesini sa�lad�m burda
			cout << endl;
		}
		cout << setw(4) << dizi[i];
	}
}
void RastgeleNumaraOlusturma(int kart[],int kisi)
{//ki�i say�s�na g�re 0 ile 10 aras�nda birbirinden farkl� rastgele rakamlar olu�turan fonksiyon
	int rndm;
	for (int i = 0; i < kisi; i++)
	{
		rndm = rand() % 10;
		while (DizideMevcutMu(kart,rndm,kisi))
		{//e�er dizide mevcutsa 1 d�nd�recek ve dizide olmayana kadar devam edecek
			rndm = rand() % 10;
		}
		kart[i] = rndm;
	}
}
void KartDagitma(int kartlar[][15], int oynanacakKartlar[][15],int rastgeleNumaralar[],int kisi)
{//olu�turdu�um rastgele rakamlar ile oyunculara kartlar� da��tt���m fonksiyon
	for (int i = 0; i < kisi; i++)
	{
		for (int j = 0; j < 15; j++)
		{
			oynanacakKartlar[i][j] = kartlar[rastgeleNumaralar[i]][j];
		}
	}
}
bool TorbaylaKarsilastir(int torba[], int oynanacakKartlar[][15], int kisi,int rastgeleNumaralar[],int oyuncuPuan[])
{//torbay� kartlardaki her bir say� ile kar��la�t�rd���m fonksiyon
	int cinko = 0;
	int oyuncuCinko[5] = {};
	for (int i = 0; i < 90; i++)//torban�n indislerine eri�mek i�in kulland���m for d�ng�s�
	{
		for (int j = 0; j < kisi; j++)//kartlara eri�mek i�in kulland���m for d�ng�s�
		{
			for (int k = 0; k < 15; k++)//kartlardaki say�lara eri�mek i�in kulland���m for d�ng�s�
			{
				if (torba[i]==oynanacakKartlar[j][k])
				{//e�er torbadan �ekilen say� karttaki say�ya e�itse yerine -1 yaz�cak ve oyuncunun �inko de�erini 1 artt�racak
					oynanacakKartlar[j][k] = -1;
					oyuncuCinko[j]++;
					if (oyuncuCinko[j] == 5)
					{//oyuncunun �inko de�eri 5e ula��rsa ekrana 1. �inkoyu yapt��� yaz�cak ve puan� tan�mlanacak
						if (cinko == 0)
						{//cinko diye bir de�i�ken tan�mlamam�n sebebi 1 kere 1. �inko yap�l�rsa cinko de�erini artt�r�cak ve bir daha if'in i�indekiler yap�lmayacak
							cout << endl << j + 1 << " numaral� oyuncu 1. �inkoyu yapt�!\n";
							cinko++;
							cout << "\nKartlardaki son durum : \n\n";
							OynanacakKartlariYazdirma(oynanacakKartlar, kisi, rastgeleNumaralar);
							PuanTablosu(oyuncuPuan, j, 5);
						}
					}
					else if (oyuncuCinko[j] == 10)
					{
						if (cinko == 1)
						{//oyuncunun �inko de�eri 10a ula��rsa ekrana 2. �inkoyu yapt��� yaz�cak ve puan� tan�mlanacak
							cout << endl << j + 1 << " numaral� oyuncu 2. �inkoyu yapt�!\n";
							cinko++;
							cout << "\nKartlardaki son durum : \n\n";
							OynanacakKartlariYazdirma(oynanacakKartlar, kisi, rastgeleNumaralar);
							PuanTablosu(oyuncuPuan, j, 10);
						}
					}
					else if (oyuncuCinko[j] == 15)
					{//oyuncunun �inko de�eri 15e ula��rsa ekrana tombala yapt��� yaz�cak ve puan� tan�mlanacak
						cout << endl << j + 1 << " numaral� oyuncu TOMBALA yapt�!!!\n";
						cout << "\nKartlardaki son durum : \n\n";
						OynanacakKartlariYazdirma(oynanacakKartlar, kisi, rastgeleNumaralar);
						PuanTablosu(oyuncuPuan, j, 15);
						return 1;
						// de�er d�nd�rmesinin sebebi biri tombala yapt�ysa bu fonksiyonu burda bitirmek
						// 1 d�nd�rmesinin sebebi ise set de�i�kenine eklenmesi ve set de�i�keni 3 oldu�unda kodun durmas�
					}
				}
			}
		}
	}
}
void OynanacakKartlariYazdirma(int oynanacakKartlar[][15], int kisi, int rastgeleNumaralar[])
{//oyunculara atanan kartlar� ekrana yazd�rma fonksiyonu
	for (int i = 0; i < kisi; i++)
	{
		cout << i+1 << ". oyuncunun kart� = ";
		for (int j = 0; j < 15; j++)
		{
			cout << setw(4) << oynanacakKartlar[i][j];
		}
		cout << endl;
	}
}
void PuanTablosu(int oyuncuPuan[], int hangiOyuncu, int puan)
{//puanlar�n toplanmas� i�in yapt���m fonksiyon
	oyuncuPuan[hangiOyuncu] += puan;
}
void PuanTablosunuYazdir(int oyuncuPuan[],int kisi)
{//puan toplamlar�n�n en b�y���n� bulup t�m oyuncular�n puanlar�yla beraber ekrana kazanan� yazd�rmak i�in kulland���m fonksiyon
	cout << "~~~~~~~~~Puan Tablosu~~~~~~~~~\n";
	for (int i = 0; i < kisi; i++)
	{
		cout << i + 1 << ". oyuncunun puan� = " << oyuncuPuan[i] << endl;
	}
	int enYuksekPuan = oyuncuPuan[0];//en y�ksek puan olarak ilk oyuncunun puan�n� kabul ettim
	int kazananOyuncu = 0;//en y�ksek puana sahip oyuncunun dizideki indisini 0 olarak kabul ettim
	int kazananOyuncu2 = -1;//ba�ka kazanan var m� diye kontrol etmek i�in olu�turdu�um de�i�ken
	for (int i = 1; i < kisi; i++)
	{
		if (enYuksekPuan < oyuncuPuan[i])
		{
			enYuksekPuan = oyuncuPuan[i];//daha y�ksek puanl� bir oyuncu varsa art�k en y�ksek puan de�i�keni onun puan� olacak ve d�ng�de o puanla i�lem yap�lacak
			kazananOyuncu = i;//daha y�ksek puanl� bir oyuncu bulundu�unda onun indisini de�i�kende saklayacak
		}
		else if (enYuksekPuan == oyuncuPuan[i])
		{
			kazananOyuncu2 = oyuncuPuan[i];
		}
	}
	if (kazananOyuncu2 == enYuksekPuan)
	{//2.kazanan 1.ye e�itse kazanan yok yazd�rd���m if yap�s�
		cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
		cout << "kazanan yok oyun berabere";
	}
	else
	{//oyun berabere de�ilse kazanan� yazd�rd���m yap�
		cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
		cout << enYuksekPuan << " puan ile kazanan " << kazananOyuncu + 1 << ". oyuncu.\n";
	}
}