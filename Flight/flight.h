#ifndef FLIGHT_H
#define FLIGHT_H
#include <iostream>
#include <string>
#include <fstream>
#include <windows.h>

class UcusYonetimSistemi {

	std::string isim; // Musteri Login isim
	std::string cins; // Musteri Login cinsiyet
	std::string tc;  // Musteri Login TC No
	std::string yas; // Musteri Login yas

	public:
	
	// Setters
	void setName(std::string isim_);
	void setGender(std::string cins_ );
	void setTC(std::string tc_);
	void setAge(std::string yas_);
	
	// Getters
	std::string getName();
	std::string getGender();
	std::string getTC();
	std::string getAge();
	
	/* Personel */
	void personelGiris(HWND hwnd);
	void personelGeri(HWND hwnd);
	void personelGeri2(HWND hwnd);
	void personelCikis(HWND hwnd);
	void personelKontrol(HWND hwnd);
	void ucusSil(HWND hwnd);
	void ucusSilKontrol(HWND hwnd);
	void ucusEkle(HWND hwnd);
	void ucusEkleGeri(HWND hwnd);
	void seferEkle(HWND hwnd);
	void ucuslariGoruntule(HWND hwnd);
	void seferDuzenle(HWND hwnd);
	void seferDuzenleKontrol(HWND hwnd);	
	/* Musteri */
	void hosGeldin(HWND hwnd);
	void musteriGiris(HWND hwnd);
	void musteriGeri(HWND hwnd);
	void musteriKontrol(HWND hwnd);
	void musteriKayit(HWND hwnd);
	void musteriKayitGeri(HWND hwnd);
	void musteriKayitOl(HWND hwnd);
	void musteriCikis(HWND hwnd);
	void musteriUcuslariGoruntule(HWND hwnd);
	void ucuslariGoruntuleGeri(HWND hwnd);
    void musteriBiletAl(HWND hwnd);
    void musteriBiletAlKontrol(HWND hwnd);
    void musteriBiletGoruntule(HWND hwnd);
    void musteriBiletSil(HWND hwnd);
    void musteriBiletSilKontrol(HWND hwnd);
};

#endif
