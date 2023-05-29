#include "flight.h"
#include <string>
#include <sstream>
#include <mysql.h>
#include <mysqld_error.h>

/* MYSQL Komut */

char HOST[] = "localhost";
char USER[] = "root";
char PASSW[] = "qwerty123*";

/* Window handlers */
HWND hosgeldin, personel, musteri; // Giris Paneli
HWND pInfo, pPanel, pTC, pTCinput, pPassw, pPasswInput, pGiris, pGoruntule, pDuzenle, pGeri, pPlane,pPlaneEkle,pPlaneSil,pCikis,
pNereden,pNEinput,pNereye,pNinput,pTarih,pTinput,pSaat,pSinput,pFiyat,pFinput,pUcakEkle, pBilet,pCikis2[20],showFlight[20],showFlight2[20],
showFlight3[20],showFlight4[20],showFlight5[20],showId[20],showid,showF,showF2,showF3,showF4,showF5,deleteFlight[20],planeSil,planeSinput,pSil; // Personel Paneli
HWND mInfo, mPanel, mTC, mTCinput, mPassw, mPasswInput, mGiris, mGeri, mKayitOl, mKayitInfo, mPlane , mBilet ,mShowBilet ,mCikis; // Musteri Paneli
HWND mKayitPanel, mKayitIsim, mKIinput, mKayitTC, mKTCinput, mKayitSifre, mKSinput, mKayitYas, mKYinput, mKayitCinsiyet,	// Musteri Kayit Paneli
mKCinput, mKgeri, mKayitOldun, mLoginInfo, mLoginHeader, mBiletInfo, mBiletHeader,mIleri,mBiletS; 		

#define CinsiyetListesi 301 // combobox

char inputSaved[20]; // textbox'tan input çeker
std::string name, id, pass, gender, age; // kayit olurken input'lari temp. tutmak için
UcusYonetimSistemi musteriInfo; // musteri bilgilerini tutar

// Setters
void UcusYonetimSistemi::setName( std::string isim_) {isim = isim_;}
void UcusYonetimSistemi::setGender( std::string cins_ ) {cins = cins_;}
void UcusYonetimSistemi::setTC( std::string tc_) {tc = tc_;}
void UcusYonetimSistemi::setAge( std::string yas_) {yas = yas_;}

// Getters
std::string UcusYonetimSistemi::getName() {return isim;}
std::string UcusYonetimSistemi::getGender() {return cins;}
std::string UcusYonetimSistemi::getTC() {return tc;}
std::string UcusYonetimSistemi::getAge() {return yas;}
	
// Hos Geldin wnd
void UcusYonetimSistemi::hosGeldin(HWND hwnd){
	/* SHOWN */
	hosgeldin = CreateWindow(TEXT("static"),TEXT("Ahiret Hava Yollarina Hos Geldiniz! \n\nLütfen Giris Panelinizi Seciniz."), WS_VISIBLE | ES_CENTER | WS_CHILD , 200, 20, 240, 60, hwnd, (HMENU) 1, NULL, NULL);
	personel = CreateWindow(TEXT("button"),TEXT("Personel"), WS_VISIBLE | WS_CHILD, 200, 100, 100, 50, hwnd, (HMENU) 101, NULL, NULL);
	musteri = CreateWindow(TEXT("button"),TEXT("Müsteri"), WS_VISIBLE | WS_CHILD, 340, 100, 100, 50, hwnd, (HMENU) 201, NULL, NULL);
}

// Personel Login wnd
void UcusYonetimSistemi::personelGiris(HWND hwnd){
	/* HIDDEN */
	ShowWindow (hosgeldin, SW_HIDE); ShowWindow (personel, SW_HIDE); ShowWindow (musteri, SW_HIDE);
	
	/* SHOWN */          	
	pPanel = CreateWindow("Static", "- Personel Paneli -", WS_CHILD | WS_VISIBLE | ES_CENTER | WS_BORDER ,200, 20, 200, 20, hwnd, NULL, NULL, NULL);
    pTC = CreateWindow("Static", "ID =", WS_CHILD | WS_VISIBLE | ES_CENTER, 200, 50, 50, 20, hwnd, NULL, NULL, NULL);
    pTCinput = CreateWindow("EDIT", "", WS_BORDER | WS_CHILD | WS_VISIBLE, 260, 50, 130, 20, hwnd, NULL, NULL, NULL);
    pPassw = CreateWindow("Static", "Sifre =", WS_CHILD | WS_VISIBLE | ES_CENTER, 200, 80, 50, 20, hwnd, NULL, NULL, NULL);
    pPasswInput = CreateWindow("EDIT", "", WS_BORDER | WS_CHILD | WS_VISIBLE | ES_PASSWORD, 260, 80, 130, 20, hwnd, NULL, NULL, NULL);
    pGeri = CreateWindow("button", "Geri Dön", WS_BORDER | WS_CHILD | WS_VISIBLE, 210, 120, 80, 30, hwnd, (HMENU) 102, NULL, NULL);
    pGiris = CreateWindow("button", "Giris Yap", WS_BORDER | WS_CHILD | WS_VISIBLE, 310, 120, 80, 30, hwnd, (HMENU) 103, NULL, NULL);
}

// Personel Login back to Hos Geldin wnd
void UcusYonetimSistemi::personelGeri(HWND hwnd){	
	/* HIDDEN */
    ShowWindow (pPanel, SW_HIDE); ShowWindow (pTC, SW_HIDE); ShowWindow (pTCinput, SW_HIDE); ShowWindow (pPassw, SW_HIDE); 
    ShowWindow (pPasswInput, SW_HIDE); ShowWindow (pGiris, SW_HIDE); ShowWindow (pGeri, SW_HIDE);
    
	/* SHOWN */
    ShowWindow (hosgeldin, SW_SHOW); ShowWindow (personel, SW_SHOW); ShowWindow (musteri, SW_SHOW);
}

// Personel Panel back to Hos Geldin wnd
void UcusYonetimSistemi::personelCikis(HWND hwnd){
	/* HIDDEN */
	ShowWindow (pPanel, SW_HIDE); ShowWindow (pPlane, SW_HIDE); ShowWindow (pPlaneEkle, SW_HIDE); 
	ShowWindow (pBilet, SW_HIDE); ShowWindow (pCikis, SW_HIDE); ShowWindow (pPlaneSil, SW_HIDE);
	
	/* SHOWN */
    ShowWindow (hosgeldin, SW_SHOW); ShowWindow (personel, SW_SHOW); ShowWindow (musteri, SW_SHOW);
}

// Personel Login Check
void UcusYonetimSistemi::personelKontrol(HWND hwnd){
		
	if(GetWindowText(pTCinput, &inputSaved[0], 20) == 0 || GetWindowText(pPasswInput, &inputSaved[0], 20) == 0)
    {
    	::MessageBox(hwnd, "Lütfen alanlari bos birakmayiniz.", "Hata: Eksik Girdi", MB_ICONWARNING | MB_OK);
	}
	else if(GetWindowText(pPasswInput, &inputSaved[0], 20) < 5)
	{
		::MessageBox(hwnd, "Sifreniz en az 5 haneli olmak zorundadir.", "Hata: Sifre", MB_ICONWARNING | MB_OK);
	}
	else{
		MYSQL* obj;
		MYSQL_RES *res;
		MYSQL_ROW row;
		
		obj = mysql_init(0);
		obj = mysql_real_connect(obj, HOST, USER, PASSW, "flight", 3306, NULL, 0);
		std::string admin;
		std::string psifre;
		std::string temp;
		
		std::stringstream a;
		a << "SELECT * FROM personel WHERE id=1";
		std::string b = a.str();
		const char* query = b.c_str();
		
		int text = GetWindowText(pTCinput, &inputSaved[0],20);
		temp = inputSaved;
		text = GetWindowText(pPasswInput, &inputSaved[0],20);
		
		mysql_query(obj,query);
		res = mysql_store_result(obj);
		row = mysql_fetch_row(res);
		admin = row[1];
		psifre = row[2];
		
		if(temp == admin && inputSaved == psifre){
		::MessageBox(hwnd, "Giris Yapildi", "Basarili", MB_ICONINFORMATION | MB_OK);
		
		/* HIDDEN */
		ShowWindow (pPanel, SW_HIDE); ShowWindow (pTC, SW_HIDE); ShowWindow (pTCinput, SW_HIDE); ShowWindow (pPassw, SW_HIDE); 
        ShowWindow (pPasswInput, SW_HIDE); ShowWindow (pGiris, SW_HIDE); ShowWindow (pGeri, SW_HIDE);
        
        /* SHOWN */
        ShowWindow (pPanel, SW_SHOW);
    pPlane = CreateWindow("button", "Ucaklari Goruntule", WS_BORDER | WS_CHILD | WS_VISIBLE, 175, 80, 260, 30, hwnd, (HMENU) 109, NULL, NULL);
    pPlaneEkle = CreateWindow("button", "Ucak Seferi Ekle", WS_BORDER | WS_CHILD | WS_VISIBLE, 175, 120, 260, 30, hwnd, (HMENU) 106, NULL, NULL);
	pPlaneSil = CreateWindow("button", "Ucus Seferi Sil", WS_BORDER | WS_CHILD | WS_VISIBLE, 175, 160, 260, 30, hwnd, (HMENU) 112, NULL, NULL);
	pCikis= CreateWindow("button", "Cikis Yap", WS_BORDER | WS_CHILD | WS_VISIBLE, 260, 260, 80, 30, hwnd, (HMENU) 104, NULL, NULL);	
		}
		else{
			::MessageBox(hwnd, "Kullanici bilgileri hatali", "Hatali Girdi", MB_ICONWARNING | MB_OK);
		}
	}
}

// Musteri Login wnd
void UcusYonetimSistemi::musteriGiris(HWND hwnd){
	/* HIDDEN */
    ShowWindow (hosgeldin, SW_HIDE); ShowWindow (personel, SW_HIDE); ShowWindow (musteri, SW_HIDE);          
	
	/* SHOWN */          	
    mPanel = CreateWindow("Static", "- Musteri Paneli -", WS_CHILD | WS_VISIBLE | ES_CENTER | WS_BORDER ,200, 20, 200, 20, hwnd, NULL, NULL, NULL);
    mTC = CreateWindow("Static", "TC =", WS_CHILD | WS_VISIBLE | ES_CENTER, 200, 50, 50, 20, hwnd, NULL, NULL, NULL);
    mTCinput = CreateWindow("EDIT", "", WS_BORDER | WS_CHILD | WS_VISIBLE | ES_NUMBER, 260, 50, 130, 20, hwnd, NULL, NULL, NULL);
    mPassw = CreateWindow("Static", "Sifre =", WS_CHILD | WS_VISIBLE | ES_CENTER, 200, 80, 50, 20, hwnd, NULL, NULL, NULL);
    mPasswInput = CreateWindow("EDIT", "", WS_BORDER | WS_CHILD | WS_VISIBLE | ES_PASSWORD, 260, 80, 130, 20, hwnd, NULL, NULL, NULL);
	mGeri = CreateWindow("button", "Geri Dön", WS_BORDER | WS_CHILD | WS_VISIBLE, 210, 120, 80, 30, hwnd, (HMENU) 202, NULL, NULL);
    mGiris = CreateWindow("button", "Giris Yap", WS_BORDER | WS_CHILD | WS_VISIBLE, 310, 120, 80, 30, hwnd, (HMENU) 203, NULL, NULL);
    mKayitOl = CreateWindow("button", "Kayit Ol!", WS_BORDER | WS_CHILD | WS_VISIBLE, 260, 220, 80, 30, hwnd, (HMENU) 204, NULL, NULL);
    mKayitInfo = CreateWindow("Static", "Hesabiniz yok mu? Hemen Kayit olun.", WS_CHILD | WS_VISIBLE | ES_CENTER, 180, 180, 260, 20, hwnd, NULL, NULL, NULL);
}

// Musteri Panel back to Hos Geldin wnd
void UcusYonetimSistemi::musteriCikis(HWND hwnd){
	/* HIDDEN */
	ShowWindow (mPlane, SW_HIDE); ShowWindow (mBilet, SW_HIDE); ShowWindow (mShowBilet, SW_HIDE); 
	ShowWindow (mPanel, SW_HIDE); ShowWindow (mCikis, SW_HIDE); ShowWindow (mLoginInfo, SW_HIDE);
	ShowWindow (mLoginHeader, SW_HIDE); ShowWindow (mBiletHeader, SW_HIDE); ShowWindow (mBiletInfo, SW_HIDE);
	ShowWindow (mBiletS, SW_HIDE);	
	/* SHOWN */ 
	ShowWindow (hosgeldin, SW_SHOW); ShowWindow (personel, SW_SHOW); ShowWindow (musteri, SW_SHOW);
	
}

// Musteri Login Check
void UcusYonetimSistemi::musteriKontrol(HWND hwnd){
	
	int checkTC = (GetWindowText(mTCinput, &inputSaved[0], 20));
	
	if(GetWindowText(mTCinput, &inputSaved[0], 20) == 0 || GetWindowText(mPasswInput, &inputSaved[0], 20) == 0)
    {
    	::MessageBox(hwnd, "Lütfen alanlari bos birakmayiniz.", "Hata: Eksik Girdi", MB_ICONWARNING | MB_OK);
	}
    else if(checkTC != 11)
    {
        ::MessageBox(hwnd, "TC numaraniz 11 haneli olmak zorundadir.", "Hata: TC ", MB_ICONWARNING | MB_OK);
	}
	else if(GetWindowText(mPasswInput, &inputSaved[0], 20) < 5)
	{
		::MessageBox(hwnd, "Sifreniz en az 5 haneli olmak zorundadir.", "Hata: Sifre", MB_ICONWARNING | MB_OK);
	}
	else{
		MYSQL* obj;
		MYSQL_RES *res;
		MYSQL_ROW row;
		
		obj = mysql_init(0);
		obj = mysql_real_connect(obj, HOST, USER, PASSW, "flight", 3306, NULL, 0);
		
		// Table bilgileri
		std::string dataName;
		std::string dataTC;
		std::string dataPassw;
			
		// User Input
		std::string inputTC;
		std::string inputPassw;
		
		int text = GetWindowText(mTCinput, &inputSaved[0],20);
		inputTC = inputSaved;
		text = GetWindowText(mPasswInput, &inputSaved[0],20);
		inputPassw = inputSaved;
		
		std::stringstream a;
		a << "SELECT * FROM musteri WHERE tc='" + inputTC + "'";
		std::string b = a.str();
		const char* query = b.c_str();
		
		if(!mysql_query(obj,query))
		{	
			if(res = mysql_store_result(obj))
			{			
				if(row = mysql_fetch_row(res))
				{
					dataName = row[1];
					dataTC = row[2];
					dataPassw = row[3];
					
					// inputlari private'lara ata
					musteriInfo.setName(row[1]);
					musteriInfo.setGender(row[5]);
					musteriInfo.setAge(row[4]);
					
					std::string hosgeldin = "Hos geldin " + dataName;
					
					if(inputTC == dataTC && inputPassw == dataPassw){
			
						::MessageBox(hwnd, hosgeldin.c_str() ,"Basariyla giris yapildi", MB_ICONINFORMATION | MB_OK);
			
			     			/* HIDDEN */
     					ShowWindow (mPanel, SW_HIDE); ShowWindow (mTC, SW_HIDE); ShowWindow (mTCinput, SW_HIDE);
    					ShowWindow (mPassw, SW_HIDE); ShowWindow (mPasswInput, SW_HIDE); ShowWindow (mGeri, SW_HIDE);
	    				ShowWindow (mGiris, SW_HIDE); ShowWindow (mKayitOl, SW_HIDE);  ShowWindow (mKayitInfo, SW_HIDE);
	    				
	    				// Musteri Bilgileri
	    				std::string musteriBilgileri = musteriInfo.getName() + '\n' + musteriInfo.getAge() + '\n' + musteriInfo.getGender(); 
	    				const char* musteriInfolari = musteriBilgileri.c_str();
	    				
							/* SHOWN */
						mPanel = CreateWindow("Static", "- Musteri Paneli -", WS_CHILD | WS_VISIBLE | ES_CENTER | WS_BORDER ,200, 20, 200, 20, hwnd, NULL, NULL, NULL);
						mLoginHeader = CreateWindow("Static", "- Profiliniz -", WS_CHILD | WS_VISIBLE | ES_CENTER | WS_BORDER , 40, 60, 120, 20, hwnd, NULL, NULL, NULL);
						mLoginInfo = CreateWindow("Static", musteriInfolari, WS_CHILD | WS_VISIBLE | ES_CENTER | WS_BORDER , 40, 90, 120, 50, hwnd, NULL, NULL, NULL);
       					mPlane = CreateWindow("button", "Ucaklari Goruntule", WS_BORDER | WS_CHILD | WS_VISIBLE, 175, 60, 260, 30, hwnd, (HMENU) 110, NULL, NULL);
	    				mBilet = CreateWindow("button", "Bilet Al", WS_BORDER | WS_CHILD | WS_VISIBLE, 175, 100, 260, 30, hwnd, (HMENU) 208, NULL, NULL);
	    				mShowBilet = CreateWindow("button", "Biletlerim", WS_BORDER | WS_CHILD | WS_VISIBLE, 175, 140, 260, 30, hwnd, (HMENU) 210, NULL, NULL);
	    				mBiletS = CreateWindow("button", "Bilet Sil", WS_BORDER | WS_CHILD | WS_VISIBLE, 175, 180, 260, 30, hwnd, (HMENU) 211, NULL, NULL);
	    				mCikis = CreateWindow("button", "Cikis Yap", WS_BORDER | WS_CHILD | WS_VISIBLE, 265, 220, 80, 30, hwnd, (HMENU) 207, NULL, NULL);
					}
					else{
						::MessageBox(hwnd, "Giris bilgilerinizi kontrol ediniz.", "Hatali Girdi", MB_ICONWARNING | MB_OK);
					}
				}
				else{						
					if(MessageBox(hwnd, "Sistemde kayitli TC bulunmamaktadir.\n\nKayit olmak ister misiniz?", "Hata", MB_ICONQUESTION | MB_YESNO) == IDYES)
					{
							/* HIDDEN */
     					ShowWindow (mPanel, SW_HIDE); ShowWindow (mTC, SW_HIDE); ShowWindow (mTCinput, SW_HIDE);
    					ShowWindow (mPassw, SW_HIDE); ShowWindow (mPasswInput, SW_HIDE); ShowWindow (mGeri, SW_HIDE);
	    				ShowWindow (mGiris, SW_HIDE); ShowWindow (mKayitOl, SW_HIDE);  ShowWindow (mKayitInfo, SW_HIDE);
	    					
	    					/* SHOWN */
    					mKayitPanel = CreateWindow("Static", "- Musteri Kayit Paneli -", WS_CHILD | WS_VISIBLE | ES_CENTER | WS_BORDER , 200, 20, 250, 20, hwnd, NULL, NULL, NULL);
    					mKayitIsim = CreateWindow("Static", "Isminiz =", WS_CHILD | WS_VISIBLE | ES_CENTER, 200, 60, 80, 20, hwnd, NULL, NULL, NULL);
    					mKIinput = CreateWindow("EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER, 300, 60, 150, 20, hwnd, NULL, NULL, NULL);
    					mKayitTC = CreateWindow("Static", "TC =", WS_CHILD | WS_VISIBLE | ES_CENTER, 200, 90, 80, 20, hwnd, NULL, NULL, NULL);
						mKTCinput = CreateWindow("EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_NUMBER, 300, 90, 150, 20, hwnd, NULL, NULL, NULL);
    					mKayitSifre = CreateWindow("Static", "Sifreniz =", WS_CHILD | WS_VISIBLE | ES_CENTER, 200, 120, 80, 20, hwnd, NULL, NULL, NULL);	
						mKSinput = CreateWindow("EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER, 300, 120, 150, 20, hwnd, NULL, NULL, NULL);
    					mKayitYas = CreateWindow("Static", "Yasiniz =", WS_CHILD | WS_VISIBLE | ES_CENTER, 200, 150, 80, 20, hwnd, NULL, NULL, NULL);
   	 					mKYinput = CreateWindow("EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_NUMBER, 300, 150, 150, 20, hwnd, NULL, NULL, NULL);
    					mKayitCinsiyet = CreateWindow("Static", "Cinsiyet =", WS_CHILD | WS_VISIBLE | ES_CENTER, 200, 180, 80, 20, hwnd, NULL, NULL, NULL);
    					mKCinput = CreateWindow("COMBOBOX", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | CBS_DROPDOWN | CBS_HASSTRINGS, 300, 180, 150, 100, hwnd, (HMENU) CinsiyetListesi, NULL, NULL);
						mKgeri = CreateWindow("button", "Geri Dön", WS_BORDER | WS_CHILD | WS_VISIBLE | ES_CENTER, 230, 230, 80, 30, hwnd, (HMENU) 205, NULL, NULL);
						mKayitOldun = CreateWindow("button", "Kayit Ol", WS_BORDER | WS_CHILD | WS_VISIBLE | ES_CENTER, 330, 230, 80, 30, hwnd, (HMENU) 206, NULL, NULL);
					}
				}	
			}		
		}
	}
}

// Musteri Login back to Hos Geldin wnd
void UcusYonetimSistemi::musteriGeri(HWND hwnd){
	/* HIDDEN */
	ShowWindow (mPanel, SW_HIDE); ShowWindow (mTC, SW_HIDE); ShowWindow (mTCinput, SW_HIDE);
	ShowWindow (mPassw, SW_HIDE); ShowWindow (mPasswInput, SW_HIDE); ShowWindow (mGeri, SW_HIDE);
	ShowWindow (mGiris, SW_HIDE); ShowWindow (mKayitOl, SW_HIDE);  ShowWindow (mKayitInfo, SW_HIDE);
	
	/* SHOWN */
    ShowWindow (hosgeldin, SW_SHOW); ShowWindow (personel, SW_SHOW); ShowWindow (musteri, SW_SHOW);	
}

// Musteri Sign up wnd
void UcusYonetimSistemi::musteriKayit(HWND hwnd){
	/* HIDDEN */
    ShowWindow (mPanel, SW_HIDE); ShowWindow (mTC, SW_HIDE); ShowWindow (mTCinput, SW_HIDE);
    ShowWindow (mPassw, SW_HIDE); ShowWindow (mPasswInput, SW_HIDE); ShowWindow (mGeri, SW_HIDE);
    ShowWindow (mGiris, SW_HIDE); ShowWindow (mKayitOl, SW_HIDE); ShowWindow (mKayitInfo, SW_HIDE);
	
    /* SHOWN */
    mKayitPanel = CreateWindow("Static", "- Musteri Kayit Paneli -", WS_CHILD | WS_VISIBLE | ES_CENTER | WS_BORDER , 200, 20, 250, 20, hwnd, NULL, NULL, NULL);
    mKayitIsim = CreateWindow("Static", "Isminiz =", WS_CHILD | WS_VISIBLE | ES_CENTER, 200, 60, 80, 20, hwnd, NULL, NULL, NULL);
    mKIinput = CreateWindow("EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER, 300, 60, 150, 20, hwnd, NULL, NULL, NULL);
    mKayitTC = CreateWindow("Static", "TC =", WS_CHILD | WS_VISIBLE | ES_CENTER, 200, 90, 80, 20, hwnd, NULL, NULL, NULL);
	mKTCinput = CreateWindow("EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_NUMBER, 300, 90, 150, 20, hwnd, NULL, NULL, NULL);
    mKayitSifre = CreateWindow("Static", "Sifreniz =", WS_CHILD | WS_VISIBLE | ES_CENTER, 200, 120, 80, 20, hwnd, NULL, NULL, NULL);
    mKSinput = CreateWindow("EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER, 300, 120, 150, 20, hwnd, NULL, NULL, NULL);
    mKayitYas = CreateWindow("Static", "Yasiniz =", WS_CHILD | WS_VISIBLE | ES_CENTER, 200, 150, 80, 20, hwnd, NULL, NULL, NULL);
    mKYinput = CreateWindow("EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_NUMBER, 300, 150, 150, 20, hwnd, NULL, NULL, NULL);
    mKayitCinsiyet = CreateWindow("Static", "Cinsiyet =", WS_CHILD | WS_VISIBLE | ES_CENTER, 200, 180, 80, 20, hwnd, NULL, NULL, NULL);
    mKCinput = CreateWindow("COMBOBOX", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | CBS_DROPDOWN | CBS_HASSTRINGS, 300, 180, 150, 100, hwnd, (HMENU) CinsiyetListesi, NULL, NULL);
	mKgeri = CreateWindow("button", "Geri Dön", WS_BORDER | WS_CHILD | WS_VISIBLE | ES_CENTER, 230, 230, 80, 30, hwnd, (HMENU) 205, NULL, NULL);
	mKayitOldun = CreateWindow("button", "Kayit Ol", WS_BORDER | WS_CHILD | WS_VISIBLE | ES_CENTER, 330, 230, 80, 30, hwnd, (HMENU) 206, NULL, NULL);
	
	/* ComboBox Listesi */

	SendMessage(GetDlgItem(hwnd, CinsiyetListesi), CB_ADDSTRING, (WPARAM) 0, (LPARAM)"Erkek");
    SendMessage(GetDlgItem(hwnd, CinsiyetListesi), CB_ADDSTRING, (WPARAM) 0, (LPARAM)"Kadin");
    SendMessage(GetDlgItem(hwnd, CinsiyetListesi), CB_ADDSTRING, (WPARAM) 0, (LPARAM)"Diger");
    
    //SendMessage(mKCinput, CB_SETCURSEL, (WPARAM) 0 , (LPARAM) 0 );
}

// Musteri Sign up back to Login wnd
void UcusYonetimSistemi::musteriKayitGeri(HWND hwnd){
	/* HIDDEN */
	ShowWindow (mKayitPanel, SW_HIDE); ShowWindow (mKayitIsim, SW_HIDE); ShowWindow (mKIinput, SW_HIDE);
	ShowWindow (mKayitTC, SW_HIDE); ShowWindow (mKTCinput, SW_HIDE); ShowWindow (mKayitSifre, SW_HIDE);
	ShowWindow (mKSinput, SW_HIDE); ShowWindow (mKayitYas, SW_HIDE); ShowWindow (mKYinput, SW_HIDE);
	ShowWindow (mKayitCinsiyet, SW_HIDE); ShowWindow (mKCinput, SW_HIDE); ShowWindow (mKgeri, SW_HIDE); ShowWindow (mKayitOldun, SW_HIDE);
	
	/* SHOWN */          	
    mPanel = CreateWindow("Static", "- Musteri Paneli -", WS_CHILD | WS_VISIBLE | ES_CENTER | WS_BORDER ,200, 20, 200, 20, hwnd, NULL, NULL, NULL);
    mTC = CreateWindow("Static", "TC =", WS_CHILD | WS_VISIBLE | ES_CENTER, 200, 50, 50, 20, hwnd, NULL, NULL, NULL);
    mTCinput = CreateWindow("EDIT", "", WS_BORDER | WS_CHILD | WS_VISIBLE | ES_NUMBER, 260, 50, 130, 20, hwnd, NULL, NULL, NULL);
    mPassw = CreateWindow("Static", "Sifre =", WS_CHILD | WS_VISIBLE | ES_CENTER, 200, 80, 50, 20, hwnd, NULL, NULL, NULL);
    mPasswInput = CreateWindow("EDIT", "", WS_BORDER | WS_CHILD | WS_VISIBLE | ES_PASSWORD, 260, 80, 130, 20, hwnd, NULL, NULL, NULL);
	mGeri = CreateWindow("button", "Geri Dön", WS_BORDER | WS_CHILD | WS_VISIBLE, 210, 120, 80, 30, hwnd, (HMENU) 202, NULL, NULL);
    mGiris = CreateWindow("button", "Giris Yap", WS_BORDER | WS_CHILD | WS_VISIBLE, 310, 120, 80, 30, hwnd, (HMENU) 203, NULL, NULL);
    mKayitOl = CreateWindow("button", "Kayit Ol!", WS_BORDER | WS_CHILD | WS_VISIBLE, 260, 220, 80, 30, hwnd, (HMENU) 204, NULL, NULL);
    mKayitInfo = CreateWindow("Static", "Hesabiniz yok mu? Hemen Kayit olun.", WS_CHILD | WS_VISIBLE | ES_CENTER, 180, 180, 260, 20, hwnd, NULL, NULL, NULL);
}

// Musteri Sign up Check
void UcusYonetimSistemi::musteriKayitOl(HWND hwnd){
	
	std::string name,id,passw,age,gender;
	int temp,ageInt;
	
	temp = GetWindowText(mKIinput, &inputSaved[0], 20);
	name = inputSaved;
	temp = GetWindowText(mKTCinput, &inputSaved[0], 20);
	id = inputSaved;
	temp = GetWindowText(mKSinput, &inputSaved[0], 20);
	passw = inputSaved;
	temp = GetWindowText(mKYinput, &inputSaved[0], 20);
	age = inputSaved;
	temp = GetWindowText(mKCinput, &inputSaved[0], 20);
	gender = inputSaved;
	
	std::stringstream a;
	a << age;
	a >> ageInt;
	
	if( GetWindowText(mKIinput, &inputSaved[0], 20) == 0 || GetWindowText(mKTCinput, &inputSaved[0], 20) == 0 ||
		GetWindowText(mKSinput, &inputSaved[0], 20) == 0 || GetWindowText(mKYinput, &inputSaved[0], 20) == 0 ||
		GetWindowText(mKCinput, &inputSaved[0], 20) == 0 )
    {
    	::MessageBox(hwnd, "Lütfen bos alan birakmayiniz.", "Hata: Eksik Girdi", MB_ICONWARNING | MB_OK);
	}
    else if(GetWindowText(mKTCinput, &inputSaved[0], 20) != 11)
    {
        ::MessageBox(hwnd, "TC numaraniz 11 haneli olmak zorundadir.", "Hata: TC ", MB_ICONWARNING | MB_OK);
	}
	else if(GetWindowText(mKSinput, &inputSaved[0], 20) < 5)
	{
		::MessageBox(hwnd, "Sifreniz en az 5 haneli olmak zorundadir.", "Hata: Sifre", MB_ICONWARNING | MB_OK);
	}
	else if(ageInt < 18)
	{
		::MessageBox(hwnd, "Yasinizin en az 18 olmasi gerekmektedir.", "Uyari: Yas", MB_ICONWARNING | MB_OK);
	}
	else if(gender != "Erkek" && gender != "Kadin" && gender != "Diger")
	{
		::MessageBox(hwnd, "Lutfen cinsiyetinizi giriniz.", "Hata: Cinsiyet", MB_ICONWARNING | MB_OK);
	}
	else
	{
		MYSQL* obj;
		
		if(obj = mysql_init(0))
		{				
			if(obj = mysql_real_connect(obj, HOST, USER, PASSW, "flight", 3306, NULL, 0))
			{
				std::stringstream a;
				a << "INSERT INTO musteri(isim, tc, sifre, yas, cinsiyet) VALUES('"+ name + "','" + id + "','" + passw + "','" + age + "','" + gender + "')";
				std::string b = a.str();
				const char* query = b.c_str();
							
				if(mysql_ping(obj))
				{
					::MessageBox(hwnd, "baglanti kesildi", "mysql", MB_ICONERROR | MB_OK);
				}
				else{
					if(!(mysql_query(obj,query)))
					{
						::MessageBox(hwnd, "Basariyla kayit oldunuz" , "Islem Basarili", MB_ICONINFORMATION | MB_OK);
					}
				else{
					::MessageBox(hwnd, mysql_error(obj), "mysql", MB_ICONERROR | MB_OK);
					}
				}				
			}
		}
				
		/* HIDDEN */
	  	ShowWindow (mKayitPanel, SW_HIDE); ShowWindow (mKayitIsim, SW_HIDE); ShowWindow (mKIinput, SW_HIDE);
		ShowWindow (mKayitTC, SW_HIDE); ShowWindow (mKTCinput, SW_HIDE); ShowWindow (mKayitSifre, SW_HIDE);
		ShowWindow (mKSinput, SW_HIDE); ShowWindow (mKayitYas, SW_HIDE); ShowWindow (mKYinput, SW_HIDE);
		ShowWindow (mKayitCinsiyet, SW_HIDE); ShowWindow (mKCinput, SW_HIDE); ShowWindow (mKgeri, SW_HIDE); ShowWindow (mKayitOldun, SW_HIDE);
	
		/* SHOWN */
		mPanel = CreateWindow("Static", "- Musteri Paneli -", WS_CHILD | WS_VISIBLE | ES_CENTER | WS_BORDER ,200, 20, 200, 20, hwnd, NULL, NULL, NULL);
   		mTC = CreateWindow("Static", "TC =", WS_CHILD | WS_VISIBLE | ES_CENTER, 200, 50, 50, 20, hwnd, NULL, NULL, NULL);
    	mTCinput = CreateWindow("EDIT", "", WS_BORDER | WS_CHILD | WS_VISIBLE | ES_NUMBER, 260, 50, 130, 20, hwnd, NULL, NULL, NULL);
    	mPassw = CreateWindow("Static", "Sifre =", WS_CHILD | WS_VISIBLE | ES_CENTER, 200, 80, 50, 20, hwnd, NULL, NULL, NULL);
    	mPasswInput = CreateWindow("EDIT", "", WS_BORDER | WS_CHILD | WS_VISIBLE | ES_PASSWORD, 260, 80, 130, 20, hwnd, NULL, NULL, NULL);
		mGeri = CreateWindow("button", "Geri Dön", WS_BORDER | WS_CHILD | WS_VISIBLE, 210, 120, 80, 30, hwnd, (HMENU) 202, NULL, NULL);
    	mGiris = CreateWindow("button", "Giris Yap", WS_BORDER | WS_CHILD | WS_VISIBLE, 310, 120, 80, 30, hwnd, (HMENU) 203, NULL, NULL);
    	mKayitOl = CreateWindow("button", "Kayit Ol!", WS_BORDER | WS_CHILD | WS_VISIBLE, 260, 220, 80, 30, hwnd, (HMENU) 204, NULL, NULL);
    	mKayitInfo = CreateWindow("Static", "Hesabiniz yok mu? Hemen Kayit olun.", WS_CHILD | WS_VISIBLE | ES_CENTER, 180, 180, 260, 20, hwnd, NULL, NULL, NULL);
		}
}

// Personel Sefer Ekle back to Personel Panel wnd
void UcusYonetimSistemi::personelGeri2(HWND hwnd){
     	/* HIDDEN */ 
     	int j = 0;
	ShowWindow (pNereden, SW_HIDE); ShowWindow (pNereye, SW_HIDE); ShowWindow (pTarih, SW_HIDE);
	ShowWindow (pSaat, SW_HIDE); ShowWindow (pFiyat, SW_HIDE); ShowWindow (pNEinput, SW_HIDE);
	ShowWindow (pNinput, SW_HIDE); ShowWindow (pTinput, SW_HIDE); ShowWindow (pSinput, SW_HIDE);
	ShowWindow (pFinput, SW_HIDE); ShowWindow (pUcakEkle, SW_HIDE); ShowWindow (pCikis, SW_HIDE);
	ShowWindow (showF, SW_HIDE); ShowWindow (showF2, SW_HIDE); ShowWindow (showF3, SW_HIDE); 
	ShowWindow (showF4, SW_HIDE); ShowWindow (showF5, SW_HIDE);ShowWindow (showid, SW_HIDE);
	ShowWindow (planeSil, SW_HIDE);ShowWindow (planeSinput, SW_HIDE);ShowWindow (pSil, SW_HIDE);
	while(j<21){
	ShowWindow (showFlight[j], SW_HIDE); ShowWindow (showFlight2[j], SW_HIDE); ShowWindow (showFlight3[j], SW_HIDE);
	ShowWindow (showFlight4[j], SW_HIDE); ShowWindow (showFlight5[j], SW_HIDE); ShowWindow (pCikis2[j], SW_HIDE);
	ShowWindow (deleteFlight[j], SW_HIDE); ShowWindow (showId[j], SW_HIDE);
	j++;
   }

	   /* SHOWN */
    pPlane = CreateWindow("button", "Ucaklari Goruntule", WS_BORDER | WS_CHILD | WS_VISIBLE, 175, 80, 260, 30, hwnd, (HMENU) 109, NULL, NULL);
    pPlaneEkle = CreateWindow("button", "Ucak Seferi Ekle", WS_BORDER | WS_CHILD | WS_VISIBLE, 175, 120, 260, 30, hwnd, (HMENU) 106, NULL, NULL);
    pPlaneSil = CreateWindow("button", "Ucus Seferi Sil", WS_BORDER | WS_CHILD | WS_VISIBLE, 175, 160, 260, 30, hwnd, (HMENU) 112, NULL, NULL);
	pCikis= CreateWindow("button", "Cikis Yap", WS_BORDER | WS_CHILD | WS_VISIBLE, 260, 260, 80, 30, hwnd, (HMENU) 104, NULL, NULL);	   
}

// Personel Sefer ekle wnd
void UcusYonetimSistemi::seferEkle(HWND hwnd){
		/* HIDDEN */ 
	ShowWindow (pPlane, SW_HIDE); ShowWindow (pPlaneEkle, SW_HIDE); ShowWindow (pCikis, SW_HIDE); ShowWindow (pBilet, SW_HIDE);
	ShowWindow (pPlaneSil, SW_HIDE);
		
		/* SHOWN */          	
    pNereden = CreateWindow("Static", "Kalkis =", WS_CHILD | WS_VISIBLE | ES_CENTER, 200, 60, 80, 20, hwnd, NULL, NULL, NULL);
    pNEinput = CreateWindow("EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER, 300, 60, 150, 20, hwnd, NULL, NULL, NULL);
    pNereye = CreateWindow("Static", "Inis =", WS_CHILD | WS_VISIBLE | ES_CENTER, 200, 90, 80, 20, hwnd, NULL, NULL, NULL);
	pNinput = CreateWindow("EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER, 300, 90, 150, 20, hwnd, NULL, NULL, NULL);
    pTarih = CreateWindow("Static", "Tarih =", WS_CHILD | WS_VISIBLE | ES_CENTER, 200, 120, 80, 20, hwnd, NULL, NULL, NULL);
    pTinput = CreateWindow("EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER, 300, 120, 150, 20, hwnd, NULL, NULL, NULL);
    pSaat = CreateWindow("Static", "Saat =", WS_CHILD | WS_VISIBLE | ES_CENTER, 200, 150, 80, 20, hwnd, NULL, NULL, NULL);
    pSinput = CreateWindow("EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER, 300, 150, 150, 20, hwnd, NULL, NULL, NULL);
    pFiyat = CreateWindow("Static", "Fiyat =", WS_CHILD | WS_VISIBLE | ES_CENTER, 200, 180, 80, 20, hwnd, NULL, NULL, NULL);
    pFinput = CreateWindow("EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER, 300, 180, 150, 20, hwnd, NULL, NULL, NULL);
    pUcakEkle = CreateWindow("button", "Ekle!", WS_BORDER | WS_CHILD | WS_VISIBLE | ES_CENTER, 330, 230, 80, 30, hwnd, (HMENU) 107, NULL, NULL);
    pCikis= CreateWindow("button", "Geri", WS_BORDER | WS_CHILD | WS_VISIBLE, 200, 230, 80, 30, hwnd, (HMENU) 108, NULL, NULL);
}

// Personel Sefer ekle Check
void UcusYonetimSistemi::ucusEkle(HWND hwnd){

    std::string Kalkis,inis,Tarih,Saat,Fiyat;
	int temp;
	temp = GetWindowText(pNEinput, &inputSaved[0], 20);
	Kalkis = inputSaved;
	temp = GetWindowText(pNinput, &inputSaved[0], 20);
	inis = inputSaved;
	temp = GetWindowText(pTinput, &inputSaved[0], 20);
	Tarih = inputSaved;
	temp = GetWindowText(pSinput, &inputSaved[0], 20);
	Saat = inputSaved;
	temp = GetWindowText(pFinput, &inputSaved[0], 20);
	Fiyat = inputSaved;
	
	if( GetWindowText(pNEinput, &inputSaved[0], 20) == 0 || GetWindowText(pNinput, &inputSaved[0], 20) == 0 ||
		GetWindowText(pTinput, &inputSaved[0], 20) == 0 || GetWindowText(pSinput, &inputSaved[0], 20) == 0 ||
		GetWindowText(pFinput, &inputSaved[0], 20) == 0 )
    {
    	::MessageBox(hwnd, "Lütfen bos alan birakmayiniz.", "Hata: Eksik Girdi", MB_ICONWARNING | MB_OK);
	}
	else{	
		MYSQL* obj;
		
		if(obj = mysql_init(0))
		{				
			if(obj = mysql_real_connect(obj, HOST, USER, PASSW, "flight", 3306, NULL, 0))
			{
				std::stringstream a;
				a << "INSERT INTO seferler(Kalkis, inis, tarih, saat, fiyat) VALUES('"+ Kalkis + "','" + inis + "','" + Tarih + "','" + Saat + "','" + Fiyat + "')";
				std::string b = a.str();
				const char* query = b.c_str();
							
				if(mysql_ping(obj))
				{
					::MessageBox(hwnd, "baglanti kesildi", "mysql", MB_ICONERROR | MB_OK);
				}
				else{
					if(!(mysql_query(obj,query)))
					{
					::MessageBox(hwnd, "Yeni sefer eklendi.", "Islem Basarili", MB_ICONINFORMATION | MB_OK);
					}
				else{
					::MessageBox(hwnd, mysql_error(obj), "mysql", MB_ICONERROR | MB_OK);
					}
				}		
			}
		}			
	}
}

void UcusYonetimSistemi::ucuslariGoruntule(HWND hwnd){
			/* HIDDEN */ 
	ShowWindow (pPlane, SW_HIDE); ShowWindow (pPlaneEkle, SW_HIDE); ShowWindow (pCikis, SW_HIDE); ShowWindow (pBilet, SW_HIDE);
	ShowWindow (pPlaneSil, SW_HIDE);
		MYSQL* obj;
		MYSQL_RES *res;
		MYSQL_ROW row;
		obj = mysql_init(0);
		obj = mysql_real_connect(obj, HOST, USER, PASSW, "flight", 3306, NULL, 0);

		std::stringstream a;
		a << "SELECT * FROM seferler";
		std::string b = a.str();
		const char* query = b.c_str();
		
		mysql_query(obj,query);	
	    res = mysql_store_result(obj);
  		int i = 80;
  		int j = 0;
  	  showid = CreateWindow("Static","ID", WS_CHILD | WS_VISIBLE | ES_CENTER | WS_BORDER , 70, 60, 30, 20,hwnd, NULL, NULL, NULL);
  	  showF = CreateWindow("Static","KALKIS", WS_CHILD | WS_VISIBLE | ES_CENTER | WS_BORDER , 100, 60, 70, 20,hwnd, NULL, NULL, NULL);
      showF2 = CreateWindow("Static","INIS", WS_CHILD | WS_VISIBLE | ES_CENTER | WS_BORDER , 170, 60, 70, 20,hwnd, NULL, NULL, NULL);
      showF3 = CreateWindow("Static","TARÝH", WS_CHILD | WS_VISIBLE | ES_CENTER | WS_BORDER , 240, 60, 80, 20,hwnd, NULL, NULL, NULL);
      showF4 = CreateWindow("Static","SAAT", WS_CHILD | WS_VISIBLE | ES_CENTER | WS_BORDER , 320, 60, 70, 20,hwnd, NULL, NULL, NULL);
      showF5 = CreateWindow("Static","FIYAT", WS_CHILD | WS_VISIBLE | ES_CENTER | WS_BORDER , 390, 60, 70, 20,hwnd, NULL, NULL, NULL);
	while(row = mysql_fetch_row(res)) // Eðer veritabanýndan bilgi gelmiþse
    {
      showId[j] = CreateWindow("Static",row[0], WS_CHILD | WS_VISIBLE | ES_CENTER | WS_BORDER , 70, i, 30, 20, hwnd, NULL, NULL, NULL);
      showFlight[j] = CreateWindow("Static",row[1], WS_CHILD | WS_VISIBLE | ES_CENTER | WS_BORDER , 100, i, 70, 20, hwnd, NULL, NULL, NULL);
      showFlight2[j] = CreateWindow("Static",row[2], WS_CHILD | WS_VISIBLE | ES_CENTER | WS_BORDER , 170, i, 70, 20, hwnd, NULL, NULL, NULL);
      showFlight3[j] = CreateWindow("Static",row[3], WS_CHILD | WS_VISIBLE | ES_CENTER | WS_BORDER ,240, i, 80, 20, hwnd, NULL, NULL, NULL);
      showFlight4[j] = CreateWindow("Static",row[4], WS_CHILD | WS_VISIBLE | ES_CENTER | WS_BORDER , 320, i, 70, 20, hwnd, NULL, NULL, NULL);
      showFlight5[j] = CreateWindow("Static",row[5], WS_CHILD | WS_VISIBLE | ES_CENTER | WS_BORDER , 390, i, 70, 20, hwnd, NULL, NULL, NULL);
      i+=20;
	  j++;
      pCikis2[j]= CreateWindow("button", "Geri", WS_BORDER | WS_CHILD | WS_VISIBLE, 400, 380, 80, 30, hwnd, (HMENU) 108, NULL, NULL);
    }
}
void UcusYonetimSistemi::ucusSil(HWND hwnd)
{
		/* HIDDEN */ 
	ShowWindow (pPlane, SW_HIDE); ShowWindow (pPlaneEkle, SW_HIDE); ShowWindow (pCikis, SW_HIDE); ShowWindow (pBilet, SW_HIDE);
	ShowWindow (pPlaneSil, SW_HIDE);
	 /*SHOWN*/
	 
	 planeSil = CreateWindow("Static", "Ucak Id =", WS_CHILD | WS_VISIBLE | ES_CENTER, 200, 100, 80, 20, hwnd, NULL, NULL, NULL);
	 planeSinput = CreateWindow("EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER, 290, 100, 150, 20, hwnd, NULL, NULL, NULL);
	 pSil = CreateWindow("button", "Sil", WS_BORDER | WS_CHILD | WS_VISIBLE, 300, 230, 80, 30, hwnd, (HMENU) 113, NULL, NULL);
	 pCikis= CreateWindow("button", "Geri", WS_BORDER | WS_CHILD | WS_VISIBLE, 200, 230, 80, 30, hwnd, (HMENU) 108, NULL, NULL);
}
void UcusYonetimSistemi::ucusSilKontrol(HWND hwnd){
	
	std::string idUcak;
	int temp;
	temp = GetWindowText(planeSinput, &inputSaved[0], 20);
	idUcak = inputSaved;
	
		if( GetWindowText(planeSinput, &inputSaved[0], 20) == 0 )
    {
    	::MessageBox(hwnd, "Lütfen bos alan birakmayiniz.", "Hata: Eksik Girdi", MB_ICONWARNING | MB_OK);
	}
	else{	
		MYSQL* obj;
		
		if(obj = mysql_init(0))
		{				
			if(obj = mysql_real_connect(obj, HOST, USER, PASSW, "flight", 3306, NULL, 0))
			{
				std::stringstream a;
				a << "DELETE  FROM seferler WHERE id='" + idUcak + "'";
				std::string b = a.str();
				const char* query = b.c_str();
							
				if(mysql_ping(obj))
				{
					::MessageBox(hwnd, "baglanti kesildi", "mysql", MB_ICONERROR | MB_OK);
				}
				else{
					if(!(mysql_query(obj,query)))
					{
					::MessageBox(hwnd, "Ucus Silindi.", "Islem Basarili", MB_ICONINFORMATION | MB_OK);
					}
				else{
					::MessageBox(hwnd, mysql_error(obj), "mysql", MB_ICONERROR | MB_OK);
					}
				}		
			}
		}			
	}
 
}
void UcusYonetimSistemi::musteriBiletSil(HWND hwnd){
	/* HIDDEN */ 
		ShowWindow (mPanel, SW_HIDE);ShowWindow (mLoginHeader, SW_HIDE);ShowWindow (mBiletHeader, SW_HIDE);	
		ShowWindow (mLoginInfo, SW_HIDE);ShowWindow (mBiletInfo, SW_HIDE);ShowWindow (mPlane, SW_HIDE);	
		ShowWindow (mBilet, SW_HIDE);ShowWindow (mShowBilet, SW_HIDE);ShowWindow (mCikis, SW_HIDE);
		ShowWindow (mBiletS, SW_HIDE);	


	 /*SHOWN*/
	 mPanel = CreateWindow("Static", "- Musteri Paneli -", WS_CHILD | WS_VISIBLE | ES_CENTER | WS_BORDER ,200, 20, 200, 20, hwnd, NULL, NULL, NULL);
	 planeSil = CreateWindow("Static", "Ucak Id =", WS_CHILD | WS_VISIBLE | ES_CENTER, 200, 100, 80, 20, hwnd, NULL, NULL, NULL);      //DEÐÝÞKEN ADLARINI DÜZENLEYEBÝLRÝSÝN.
	 planeSinput = CreateWindow("EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER, 290, 100, 150, 20, hwnd, NULL, NULL, NULL);
	 pSil = CreateWindow("button", "Ýleri", WS_BORDER | WS_CHILD | WS_VISIBLE, 300, 230, 80, 30, hwnd, (HMENU) 212, NULL, NULL);
	 pCikis= CreateWindow("button", "Geri", WS_BORDER | WS_CHILD | WS_VISIBLE, 200, 230, 80, 30, hwnd, (HMENU) 111, NULL, NULL);
}

void UcusYonetimSistemi::musteriBiletSilKontrol(HWND hwnd){
		   	MYSQL* obj;
		MYSQL_RES *res;
		MYSQL_ROW row;
		
		obj = mysql_init(0);
		obj = mysql_real_connect(obj, HOST, USER, PASSW, "flight", 3306, NULL, 0);
		
		// Table bilgileri
		std::string dataTC;
		std::string idUcak;
			
		// User Input
		std::string inputTC;
		int temp;
	    temp = GetWindowText(planeSinput, &inputSaved[0], 20);
	    idUcak = inputSaved;
		int text = GetWindowText(mTCinput, &inputSaved[0],20);
		inputTC = inputSaved;

		
		std::stringstream a;
		a << "SELECT * FROM biletler WHERE tc='" + inputTC + "'";
		std::string b = a.str();
		const char* query = b.c_str();
		
		mysql_query(obj,query);	
		res = mysql_store_result(obj);
		row = mysql_fetch_row(res);

		
		if(obj = mysql_init(0))
		{				
			if(obj = mysql_real_connect(obj, HOST, USER, PASSW, "flight", 3306, NULL, 0))
			{
		std::stringstream d;
		d << "DELETE  FROM biletler WHERE id='" + idUcak + "'AND tc='" + inputTC+ "'";
		std::string e = d.str();
		const char* query = e.c_str();
		if(!mysql_query(obj,query)){	
		if(res = mysql_store_result(obj)){

		if(row = mysql_fetch_row(res))
		{	
				if(mysql_ping(obj))
				{
					::MessageBox(hwnd, "baglanti kesildi", "mysql", MB_ICONERROR | MB_OK);
				}
				else{
					if(!(mysql_query(obj,query)))
					{
				      ::MessageBox(hwnd, "Ucus Silindi.", "Islem Basarili", MB_ICONINFORMATION | MB_OK);
		        if(mysql_ping(obj))
				{
					::MessageBox(hwnd, "baglanti kesildi", "mysql", MB_ICONERROR | MB_OK);
				}

					}
				else{
					::MessageBox(hwnd, mysql_error(obj), "mysql", MB_ICONERROR | MB_OK);
					}
				}
			}
			else{
				::MessageBox(hwnd, "Bilet Alinmadi.Gecersiz ucak id.", "Islem Basarili", MB_ICONINFORMATION | MB_OK);
			}
			}}}
		}		
}


void UcusYonetimSistemi::musteriUcuslariGoruntule(HWND hwnd){
			/* HIDDEN */ 
		ShowWindow (mPanel, SW_HIDE);ShowWindow (mLoginHeader, SW_HIDE);ShowWindow (mBiletHeader, SW_HIDE);	
		ShowWindow (mLoginInfo, SW_HIDE);ShowWindow (mBiletInfo, SW_HIDE);ShowWindow (mPlane, SW_HIDE);	
		ShowWindow (mBilet, SW_HIDE);ShowWindow (mShowBilet, SW_HIDE);ShowWindow (mCikis, SW_HIDE);	
		ShowWindow (mBiletS, SW_HIDE);		
		MYSQL* obj;
		MYSQL_RES *res;
		MYSQL_ROW row;
		obj = mysql_init(0);
		obj = mysql_real_connect(obj, HOST, USER, PASSW, "flight", 3306, NULL, 0);

		std::stringstream a;
		a << "SELECT * FROM seferler";
		std::string b = a.str();
		const char* query = b.c_str();
		
		mysql_query(obj,query);	
	    res = mysql_store_result(obj);
  		int i = 80;
  		int j = 0;
  	  mPanel = CreateWindow("Static", "- Musteri Paneli -", WS_CHILD | WS_VISIBLE | ES_CENTER | WS_BORDER ,200, 20, 200, 20, hwnd, NULL, NULL, NULL);
  	  showid = CreateWindow("Static","ID", WS_CHILD | WS_VISIBLE | ES_CENTER | WS_BORDER , 70, 60, 30, 20,hwnd, NULL, NULL, NULL);
  	  showF = CreateWindow("Static","KALKIS", WS_CHILD | WS_VISIBLE | ES_CENTER | WS_BORDER , 100, 60, 70, 20,hwnd, NULL, NULL, NULL);
      showF2 = CreateWindow("Static","INIS", WS_CHILD | WS_VISIBLE | ES_CENTER | WS_BORDER , 170, 60, 70, 20,hwnd, NULL, NULL, NULL);
      showF3 = CreateWindow("Static","TARÝH", WS_CHILD | WS_VISIBLE | ES_CENTER | WS_BORDER , 240, 60, 80, 20,hwnd, NULL, NULL, NULL);
      showF4 = CreateWindow("Static","SAAT", WS_CHILD | WS_VISIBLE | ES_CENTER | WS_BORDER , 320, 60, 70, 20,hwnd, NULL, NULL, NULL);
      showF5 = CreateWindow("Static","FIYAT", WS_CHILD | WS_VISIBLE | ES_CENTER | WS_BORDER , 390, 60, 70, 20,hwnd, NULL, NULL, NULL);
	while(row = mysql_fetch_row(res)) // Eðer veritabanýndan bilgi gelmiþse
    {
      showId[j] = CreateWindow("Static",row[0], WS_CHILD | WS_VISIBLE | ES_CENTER | WS_BORDER , 70, i, 30, 20, hwnd, NULL, NULL, NULL);	
      showFlight[j] = CreateWindow("Static",row[1], WS_CHILD | WS_VISIBLE | ES_CENTER | WS_BORDER , 100, i, 70, 20, hwnd, NULL, NULL, NULL);
      showFlight2[j] = CreateWindow("Static",row[2], WS_CHILD | WS_VISIBLE | ES_CENTER | WS_BORDER , 170, i, 70, 20, hwnd, NULL, NULL, NULL);
      showFlight3[j] = CreateWindow("Static",row[3], WS_CHILD | WS_VISIBLE | ES_CENTER | WS_BORDER ,240, i, 80, 20, hwnd, NULL, NULL, NULL);
      showFlight4[j] = CreateWindow("Static",row[4], WS_CHILD | WS_VISIBLE | ES_CENTER | WS_BORDER , 320, i, 70, 20, hwnd, NULL, NULL, NULL);
      showFlight5[j] = CreateWindow("Static",row[5], WS_CHILD | WS_VISIBLE | ES_CENTER | WS_BORDER , 390, i, 70, 20, hwnd, NULL, NULL, NULL);
      i+=20;
	  j++;
      pCikis2[j]= CreateWindow("button", "Geri", WS_BORDER | WS_CHILD | WS_VISIBLE, 400, 380, 80, 30, hwnd, (HMENU) 111, NULL, NULL);
    }
}



void UcusYonetimSistemi::ucuslariGoruntuleGeri(HWND hwnd){
	int j = 0;
	/* HIDDEN */
	ShowWindow (showF, SW_HIDE); ShowWindow (showF2, SW_HIDE); ShowWindow (showF3, SW_HIDE); 
	ShowWindow (showF4, SW_HIDE); ShowWindow (showF5, SW_HIDE);ShowWindow (mPanel, SW_HIDE);
	ShowWindow (mPanel, SW_HIDE);ShowWindow (planeSil, SW_HIDE);ShowWindow (planeSinput, SW_HIDE);
	ShowWindow (pSil, SW_HIDE);ShowWindow (pCikis, SW_HIDE);ShowWindow (showid, SW_HIDE);
	ShowWindow (showFlight[1], SW_HIDE);ShowWindow (showFlight2[2], SW_HIDE);ShowWindow (showFlight3[3], SW_HIDE);ShowWindow (showFlight4[4], SW_HIDE);
	ShowWindow (showFlight5[5], SW_HIDE);ShowWindow (mIleri, SW_HIDE);
	while(j<21){
	ShowWindow (showFlight[j], SW_HIDE); ShowWindow (showFlight2[j], SW_HIDE); ShowWindow (showFlight3[j], SW_HIDE);
	ShowWindow (showFlight4[j], SW_HIDE); ShowWindow (showFlight5[j], SW_HIDE); ShowWindow (pCikis2[j], SW_HIDE);
	ShowWindow (showId[j], SW_HIDE);
	j++;
}	
		MYSQL* obj;
		MYSQL_RES *res;
		MYSQL_ROW row;
		
		obj = mysql_init(0);
		obj = mysql_real_connect(obj, HOST, USER, PASSW, "flight", 3306, NULL, 0);
		
		// Table bilgileri
		std::string dataName;
		std::string dataTC;
		std::string dataPassw;
			
		// User Input
		std::string inputTC;
		std::string inputPassw;
		
		int text = GetWindowText(mTCinput, &inputSaved[0],20);
		inputTC = inputSaved;
		text = GetWindowText(mPasswInput, &inputSaved[0],20);
		inputPassw = inputSaved;
		
		std::stringstream a;
		a << "SELECT * FROM musteri WHERE tc='" + inputTC + "'";
		std::string b = a.str();
		const char* query = b.c_str();
		
		mysql_query(obj,query);	
		res = mysql_store_result(obj);
		row = mysql_fetch_row(res);
					// inputlari private'lara ata
		musteriInfo.setName(row[1]);
		musteriInfo.setGender(row[5]);
		musteriInfo.setAge(row[4]);
	    			// Musteri Bilgileri
	   	std::string musteriBilgileri = musteriInfo.getName() + '\n' + musteriInfo.getAge() + '\n' + musteriInfo.getGender(); 
	    const char* musteriInfolari = musteriBilgileri.c_str();			
		/* SHOWN */
	mPanel = CreateWindow("Static", "- Musteri Paneli -", WS_CHILD | WS_VISIBLE | ES_CENTER | WS_BORDER ,200, 20, 200, 20, hwnd, NULL, NULL, NULL);
	mLoginHeader = CreateWindow("Static", "- Profiliniz -", WS_CHILD | WS_VISIBLE | ES_CENTER | WS_BORDER , 40, 60, 120, 20, hwnd, NULL, NULL, NULL);
	mLoginInfo = CreateWindow("Static", musteriInfolari, WS_CHILD | WS_VISIBLE | ES_CENTER | WS_BORDER , 40, 90, 120,50,hwnd, NULL, NULL, NULL);
    mPlane = CreateWindow("button", "Ucaklari Goruntule", WS_BORDER | WS_CHILD | WS_VISIBLE, 175, 60, 260, 30, hwnd, (HMENU) 110, NULL, NULL);
	mBilet = CreateWindow("button", "Bilet Al", WS_BORDER | WS_CHILD | WS_VISIBLE, 175, 100, 260, 30, hwnd, (HMENU) 208, NULL, NULL);
	mShowBilet = CreateWindow("button", "Biletlerim", WS_BORDER | WS_CHILD | WS_VISIBLE, 175, 140, 260, 30, hwnd, (HMENU) 210, NULL, NULL);
	mBiletS = CreateWindow("button", "Bilet Sil", WS_BORDER | WS_CHILD | WS_VISIBLE, 175, 180, 260, 30, hwnd, (HMENU) 211, NULL, NULL);
	mCikis = CreateWindow("button", "Cikis Yap", WS_BORDER | WS_CHILD | WS_VISIBLE, 265, 220, 80, 30, hwnd, (HMENU) 207, NULL, NULL);
  
}
void UcusYonetimSistemi::musteriBiletAl(HWND hwnd){
	
	/* HIDDEN */ 
		ShowWindow (mPanel, SW_HIDE);ShowWindow (mLoginHeader, SW_HIDE);ShowWindow (mBiletHeader, SW_HIDE);	
		ShowWindow (mLoginInfo, SW_HIDE);ShowWindow (mBiletInfo, SW_HIDE);ShowWindow (mPlane, SW_HIDE);	
		ShowWindow (mBilet, SW_HIDE);ShowWindow (mShowBilet, SW_HIDE);ShowWindow (mCikis, SW_HIDE);	
        ShowWindow (mBiletS, SW_HIDE);	

	 /*SHOWN*/
	 mPanel = CreateWindow("Static", "- Musteri Paneli -", WS_CHILD | WS_VISIBLE | ES_CENTER | WS_BORDER ,200, 20, 200, 20, hwnd, NULL, NULL, NULL);
	 planeSil = CreateWindow("Static", "Ucak Id =", WS_CHILD | WS_VISIBLE | ES_CENTER, 200, 100, 80, 20, hwnd, NULL, NULL, NULL);      //DEÐÝÞKEN ADLARINI DÜZENLEYEBÝLRÝSÝN.
	 planeSinput = CreateWindow("EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER, 290, 100, 150, 20, hwnd, NULL, NULL, NULL);
	 pSil = CreateWindow("button", "Ýleri", WS_BORDER | WS_CHILD | WS_VISIBLE, 300, 230, 80, 30, hwnd, (HMENU) 209, NULL, NULL);
	 pCikis= CreateWindow("button", "Geri", WS_BORDER | WS_CHILD | WS_VISIBLE, 200, 230, 80, 30, hwnd, (HMENU) 111, NULL, NULL);
}

void UcusYonetimSistemi::musteriBiletAlKontrol(HWND hwnd){
	   	MYSQL* obj;
		MYSQL_RES *res;
		MYSQL_ROW row;
		
		obj = mysql_init(0);
		obj = mysql_real_connect(obj, HOST, USER, PASSW, "flight", 3306, NULL, 0);
		
		// Table bilgileri
		std::string dataTC;
		std::string idUcak;
		std::string dataid;
		std::string kalkis;
		std::string inis;
		std::string tarih;
		std::string saat;
			
		// User Input
		std::string inputTC;
		int temp;
	    temp = GetWindowText(planeSinput, &inputSaved[0], 20);
	    idUcak = inputSaved;
		int text = GetWindowText(mTCinput, &inputSaved[0],20);
		inputTC = inputSaved;

		
		std::stringstream a;
		a << "SELECT * FROM musteri WHERE tc='" + inputTC + "'";
		std::string b = a.str();
		const char* query = b.c_str();
		
		mysql_query(obj,query);	
		res = mysql_store_result(obj);
		row = mysql_fetch_row(res);
		
		dataTC = row[2];
		
		if(obj = mysql_init(0))
		{				
			if(obj = mysql_real_connect(obj, HOST, USER, PASSW, "flight", 3306, NULL, 0))
			{
		std::stringstream d;
		d << "SELECT * FROM seferler WHERE id='" + idUcak + "'";
		std::string e = d.str();
		const char* query1 = e.c_str();
		if(!mysql_query(obj,query1)){	
		if(res = mysql_store_result(obj)){

		if(row = mysql_fetch_row(res))
		{
		dataid = row[0];	
				if(mysql_ping(obj))
				{
					::MessageBox(hwnd, "baglanti kesildi", "mysql", MB_ICONERROR | MB_OK);
				}
				else{
					if(!(mysql_query(obj,query)))
					{
						ShowWindow (planeSil, SW_HIDE);ShowWindow (planeSinput, SW_HIDE);
                       	ShowWindow (pSil, SW_HIDE);ShowWindow (pCikis, SW_HIDE);
                       	mPanel = CreateWindow("Static", "- Musteri Paneli -", WS_CHILD | WS_VISIBLE | ES_CENTER | WS_BORDER ,200, 20, 200, 20, hwnd, NULL, NULL, NULL);
                       	mPanel = CreateWindow("Static", "Biletiniz Kaydedildi", WS_CHILD | WS_VISIBLE | ES_CENTER | WS_BORDER ,200, 50, 200, 20, hwnd, NULL, NULL, NULL);
	                    showFlight[1] = CreateWindow("Static",row[1], WS_CHILD | WS_VISIBLE | ES_CENTER | WS_BORDER , 100, 80, 70, 20, hwnd, NULL, NULL, NULL);
                        showFlight2[2] = CreateWindow("Static",row[2], WS_CHILD | WS_VISIBLE | ES_CENTER | WS_BORDER , 170, 80, 70, 20, hwnd, NULL, NULL, NULL);
                        showFlight3[3] = CreateWindow("Static",row[3], WS_CHILD | WS_VISIBLE | ES_CENTER | WS_BORDER ,240, 80, 80, 20, hwnd, NULL, NULL, NULL);
                        showFlight4[4] = CreateWindow("Static",row[4], WS_CHILD | WS_VISIBLE | ES_CENTER | WS_BORDER , 320, 80, 70, 20, hwnd, NULL, NULL, NULL);
                        showFlight5[5] = CreateWindow("Static",row[5], WS_CHILD | WS_VISIBLE | ES_CENTER | WS_BORDER , 390, 80, 70, 20, hwnd, NULL, NULL, NULL);
                        mIleri =  CreateWindow("button", "Ýleri", WS_BORDER | WS_CHILD | WS_VISIBLE, 300, 230, 80, 30, hwnd, (HMENU) 111, NULL, NULL);
                        kalkis = row[1];
                        inis = row[2];
                        tarih = row[3];
                        saat = row[4];
                        
                        std::stringstream a;
			         	a << "INSERT INTO biletler(id,tc,kalkis,inis,tarih,saat) VALUES('"+ idUcak + "','" + dataTC + "','" + kalkis + "','" + inis + "','" + tarih + "','" + saat + "')";
				std::string b = a.str();
				const char* query = b.c_str();
						mysql_query(obj,query1);	
		            res = mysql_store_result(obj);
		             row = mysql_fetch_row(res);
		        if(mysql_ping(obj))
				{
					::MessageBox(hwnd, "baglanti kesildi", "mysql", MB_ICONERROR | MB_OK);
				}
				else{
					if(!(mysql_query(obj,query)))
					{
                     ::MessageBox(hwnd, "Bilet Alindi.", "Islem Basarili", MB_ICONINFORMATION | MB_OK);
					}
				else{
					::MessageBox(hwnd, mysql_error(obj), "mysql", MB_ICONERROR | MB_OK);
					}
				}	

					}
				else{
					::MessageBox(hwnd, mysql_error(obj), "mysql", MB_ICONERROR | MB_OK);
					}
				}
			}
			else{
				::MessageBox(hwnd, "Bilet Alinmadi.Gecersiz ucak id.", "Islem Basarili", MB_ICONINFORMATION | MB_OK);
			}
			}}}
		}		
}


void UcusYonetimSistemi::musteriBiletGoruntule(HWND hwnd){
				/* HIDDEN */ 
		ShowWindow (mPanel, SW_HIDE);ShowWindow (mLoginHeader, SW_HIDE);ShowWindow (mBiletHeader, SW_HIDE);	
		ShowWindow (mLoginInfo, SW_HIDE);ShowWindow (mBiletInfo, SW_HIDE);ShowWindow (mPlane, SW_HIDE);	
		ShowWindow (mBilet, SW_HIDE);ShowWindow (mShowBilet, SW_HIDE);ShowWindow (mCikis, SW_HIDE);	
		ShowWindow (mBiletS, SW_HIDE);	
		MYSQL* obj;
		MYSQL_RES *res;
		MYSQL_ROW row;
		obj = mysql_init(0);
		obj = mysql_real_connect(obj, HOST, USER, PASSW, "flight", 3306, NULL, 0);
		
		std::string inputTC;
		
		int text = GetWindowText(mTCinput, &inputSaved[0],20);
		inputTC = inputSaved;

		std::stringstream a;
		a << "SELECT * FROM biletler WHERE tc='" + inputTC + "'";
		std::string b = a.str();
		const char* query = b.c_str();
		
		mysql_query(obj,query);	
	    res = mysql_store_result(obj);
  		int i = 80;
  		int j = 0;
      mPanel = CreateWindow("Static", "- Musteri Paneli -", WS_CHILD | WS_VISIBLE | ES_CENTER | WS_BORDER ,200, 20, 200, 20, hwnd, NULL, NULL, NULL);
  	  showid = CreateWindow("Static","ID", WS_CHILD | WS_VISIBLE | ES_CENTER | WS_BORDER , 130, 60, 30, 20,hwnd, NULL, NULL, NULL);
  	  showF = CreateWindow("Static","KALKIS", WS_CHILD | WS_VISIBLE | ES_CENTER | WS_BORDER , 160, 60, 70, 20,hwnd, NULL, NULL, NULL);
      showF2 = CreateWindow("Static","INIS", WS_CHILD | WS_VISIBLE | ES_CENTER | WS_BORDER , 230, 60, 70, 20,hwnd, NULL, NULL, NULL);
      showF3 = CreateWindow("Static","TARÝH", WS_CHILD | WS_VISIBLE | ES_CENTER | WS_BORDER , 300, 60, 80, 20,hwnd, NULL, NULL, NULL);
      showF4 = CreateWindow("Static","SAAT", WS_CHILD | WS_VISIBLE | ES_CENTER | WS_BORDER , 380, 60, 70, 20,hwnd, NULL, NULL, NULL);
      pCikis= CreateWindow("button", "Geri", WS_BORDER | WS_CHILD | WS_VISIBLE, 380, 230, 80, 30, hwnd, (HMENU) 111, NULL, NULL);
      while(row = mysql_fetch_row(res)){
      showId[j] = CreateWindow("Static",row[0], WS_CHILD | WS_VISIBLE | ES_CENTER | WS_BORDER , 130, i, 30, 20, hwnd, NULL, NULL, NULL);	
      showFlight[j] = CreateWindow("Static",row[2], WS_CHILD | WS_VISIBLE | ES_CENTER | WS_BORDER , 160, i, 70, 20, hwnd, NULL, NULL, NULL);
      showFlight2[j] = CreateWindow("Static",row[3], WS_CHILD | WS_VISIBLE | ES_CENTER | WS_BORDER , 230, i, 70, 20, hwnd, NULL, NULL, NULL);
      showFlight3[j] = CreateWindow("Static",row[4], WS_CHILD | WS_VISIBLE | ES_CENTER | WS_BORDER ,300, i, 80, 20, hwnd, NULL, NULL, NULL);
      showFlight4[j] = CreateWindow("Static",row[5], WS_CHILD | WS_VISIBLE | ES_CENTER | WS_BORDER , 380, i, 70, 20, hwnd, NULL, NULL, NULL);
      i+=20;
	  j++;
    }
    
}
