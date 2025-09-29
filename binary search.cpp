#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>

using namespace std;

// Fungsi untuk mendapatkan panjang string terpanjang
int getMaxLength(const vector<string>& arr) {
    int maxLength = 0;
    for (const string& s : arr) {
        if (s.length() > maxLength) {
            maxLength = s.length();
        }
    }
    return maxLength;
}

// Counting Sort untuk mengurutkan karakter pada posisi tertentu
void countingSort(vector<string>& arr, int place) {
    const int maxChar = 256; // Jumlah karakter ASCII
    vector<string> output(arr.size());
    vector<int> count(maxChar, 0);

    // Hitung frekuensi karakter pada posisi tertentu
    for (const string& s : arr) {
        char ch = (place < s.length()) ? s[s.length() - 1 - place] : '\0';
        count[ch]++;
    }

    // Akumulasikan frekuensi
    for (int i = 1; i < maxChar; i++) {
        count[i] += count[i - 1];
    }

    // Tempatkan elemen ke posisi yang benar
    for (int i = arr.size() - 1; i >= 0; i--) {
        char ch = (place < arr[i].length()) ? arr[i][arr[i].length() - 1 - place] : '\0';
        output[count[ch] - 1] = arr[i];
        count[ch]--;
    }

    // Salin output ke array asli
    arr = output;
}

// Radix Sort untuk mengurutkan array string
void radixSort(vector<string>& arr) {
    int maxLength = getMaxLength(arr);

    // Lakukan Counting Sort untuk setiap karakter
    for (int place = 0; place < maxLength; place++) {
        countingSort(arr, place);
    }
}

// Fungsi untuk memisahkan kalimat menjadi kata-kata
vector<string> splitSentence(const string& sentence) {
    vector<string> words;
    stringstream ss(sentence);
    string word;
    while (ss >> word) {
        words.push_back(word);
    }
    return words;
}

// Fungsi untuk menggabungkan kata-kata menjadi kalimat
string joinWords(const vector<string>& words) {
    string sentence;
    for (const string& word : words) {
        sentence += word + " ";
    }
    if (!sentence.empty()) {
        sentence.pop_back(); // Hapus spasi terakhir
    }
    return sentence;
}

// Binary Search untuk mencari kata dalam array yang sudah terurut
int binarySearch(const vector<string>& arr, const string& target) {
    int low = 0, high = arr.size() - 1;
    while (low <= high) {
        int mid = (low + high) / 2;
        if (arr[mid] == target) {
            return mid; // Kata ditemukan
        } else if (arr[mid] < target) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return -1; // Kata tidak ditemukan
}

// Driver code
int main() {
    string sentence = "mari pergi";
    
    // Pisahkan kalimat menjadi kata-kata
    vector<string> words = splitSentence(sentence);

    // Urutkan setiap kata menggunakan Radix Sort
    for (string& word : words) {
        vector<string> temp = {word}; // Ubah kata menjadi array string
        radixSort(temp);             // Urutkan kata
        word = temp[0];              // Ambil hasil pengurutan
    }

    // Gabungkan kata-kata menjadi kalimat
    string sortedSentence = joinWords(words);

    cout << "Kalimat sebelum diurutkan: " << sentence << endl;
    cout << "Kalimat setelah diurutkan: " << sortedSentence << endl;

    // Cari kata dalam kalimat yang sudah diurutkan
    string targetWord = "egipr";
    int index = binarySearch(words, targetWord);

    if (index != -1) {
        cout << "Kata '" << targetWord << "' ditemukan di indeks " << index << "." << endl;
    } else {
        cout << "Kata '" << targetWord << "' tidak ditemukan." << endl;
    }

    return 0;
}