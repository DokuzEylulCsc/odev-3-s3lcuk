// Selçuk Demir
// 2018280013
// C++11 desktekleyen compiler kullanılmalıdır.

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

int main() {

  int soru_sayisi, j = 0, i = 0, k = 0;
  string cevap_anahtari, ogrenci_cevap[100], soru_sayisi_str;
  float notlar[100], temp_not, ortalama_not = 0, medyan, medyan_index, medyan_index_tek, aciklik;

  ifstream itxt("input.txt");

  getline(itxt, soru_sayisi_str);

  soru_sayisi = stoi(soru_sayisi_str);

  getline(itxt, cevap_anahtari);

  float maxnot = soru_sayisi * 4;

  char cevap_anahtari_array[soru_sayisi], cevaplar[100][soru_sayisi], numaralar[100][9], temp_numara;

  // cevap anahtarini array'e yazdir
  while (cevap_anahtari[i] != NULL) {
    if (cevap_anahtari[i] != ',') {
      cevap_anahtari_array[j] = cevap_anahtari[i];
      i += 2;
      j++;
    } else if (cevap_anahtari[i] == ',') {
      cevap_anahtari_array[j] = 'x'; // bos sorular x'e esit
      i++;
      j++;
    }
  }

  /*
  for (int i = 0; i < soru_sayisi; i++){
    cout « cevap_anahtari_array[i] « ' ';
  }
  */

  for (int i = 0; i < 100; i++) {

    notlar[i] = 0;

    getline(itxt, ogrenci_cevap[i]);

    // ogrenci_cevap[i]'yi formatla

    // numarayi numaralar[]'a yazdir
    j = 0;
    k = 0;
    while (ogrenci_cevap[i][j] != ',') {
      numaralar[i][j] = ogrenci_cevap[i][j];
      j++;
    }
    j++;

    // ogrencinin cevaplarini cevaplar[][]'a yazdir
    while (ogrenci_cevap[i][j] != NULL) {
      if (ogrenci_cevap[i][j] != ',') {
        cevaplar[i][k] = ogrenci_cevap[i][j];
        j += 2;
        k++;
      } else if (ogrenci_cevap[i][j] == ',') {
        cevaplar[i][k] = 'x'; // bos sorular x'e esit
        j++;
        k++;
      }
    }

    if (ogrenci_cevap[i][j - 1] == ',') {
      cevaplar[i][k] = 'x'; // en son soru bossa onu da yaz
    }

    /*
    for (int i = 0; i < soru_sayisi+1; i++){
      cout « cevaplar[0][i] « ' ';
    }
    */

    // ogrencinin notunu hesapla ve notlar[]'a yazdir
    for (int m = 0; m < soru_sayisi; m++) {
      /*
        cout << cevaplar[i][m] << "   ->   " << cevap_anahtari_array[m] << endl;
      */
      if (cevaplar[i][m] == 'x') {
        continue;
      } else if (cevaplar[i][m] != cevap_anahtari_array[m]) {
        notlar[i]--;
      } else if (cevaplar[i][m] == cevap_anahtari_array[m]) {
        notlar[i] += 4;
      }
    }

    if (notlar[i] < 0) {
      notlar[i] = 0;
    }

    // notu 0-100 araligina cek
    notlar[i] = (100 / maxnot) * notlar[i];

    /*
    cout << endl << notlar[i];
    */

    // notlar ve numaralari paralel bir şekilde sırala
    if (i != 0) {
      for (int y = 0; y < i; y++) {
        for (int x = y + 1; x < i; x++) {
          if (notlar[y] < notlar[x]) {
            temp_not = notlar[x];
            notlar[x] = notlar[y];
            notlar[y] = temp_not;
            for (int z = 0; z < 9; z++) {
              temp_numara = numaralar[x][z];
              numaralar[x][z] = numaralar[y][z];
              numaralar[y][z] = temp_numara;
            }
          }
        }
      }
    }

    /*
	for(int d = 0; d < i; d++){
		cout << endl << notlar[d] << "  ->  ";
		for(int e = 0; e < 9; e++){
			cout << numaralar[d][e];
		}
		cout << endl;
	}
	*/

    // file'a sirali sekilde notlari yazdir
    ofstream txt("output.txt");
    if (i != 0) {
      for (int d = 0; d < i + 1; d++) {
        for (int e = 0; e < 9; e++) {
          txt << numaralar[d][e];
        }
        txt << "," << notlar[d] << endl;
      }
    }

    // en dusuk, en yuksek, ortalama, medyan, range
    ortalama_not = notlar[0];
    if (i > 0) {
      for (int g = 1; g < i + 1; g++) {
        /*
		cout << "toplananlar = " << ortalama_not << " + " << notlar[g] << endl;
    */
        ortalama_not += notlar[g];
      }
      ortalama_not = ortalama_not / (i + 1);
      /*
	cout << "ort ->" << ortalama_not;
  */
    }

    medyan_index = i / 2;
    medyan_index_tek = (i / 2) + 0.5;

    if ((i + 1) % 2 == 1) {
      medyan = notlar[(int) medyan_index_tek];
    } else {
      medyan = (notlar[(int) medyan_index] + notlar[(int) medyan_index + 1]) / 2;
    }

    aciklik = notlar[0] - notlar[i];

    txt << notlar[i] << ',' << notlar[0] << ',' << ortalama_not << ',' << medyan << "," << aciklik << endl;

  }

  return 0;
}
