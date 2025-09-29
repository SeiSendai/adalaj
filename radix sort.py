# Fungsi untuk mendapatkan panjang string terpanjang
def get_max_length(arr):
    max_length = 0
    for s in arr:
        if len(s) > max_length:
            max_length = len(s)
    return max_length

# Counting Sort untuk mengurutkan karakter pada posisi tertentu
def counting_sort(arr, place):
    max_char = 256  # Jumlah karakter ASCII
    output = [''] * len(arr)
    count = [0] * max_char

    # Hitung frekuensi karakter pada posisi tertentu
    for s in arr:
        ch = s[len(s) - 1 - place] if place < len(s) else '\0'
        count[ord(ch)] += 1

    # Akumulasikan frekuensi
    for i in range(1, max_char):
        count[i] += count[i - 1]

    # Tempatkan elemen ke posisi yang benar
    for i in range(len(arr) - 1, -1, -1):
        ch = arr[i][len(arr[i]) - 1 - place] if place < len(arr[i]) else '\0'
        output[count[ord(ch)] - 1] = arr[i]
        count[ord(ch)] -= 1

    # Salin output ke array asli
    for i in range(len(arr)):
        arr[i] = output[i]

# Radix Sort untuk mengurutkan array string
def radix_sort(arr):
    max_length = get_max_length(arr)

    # Lakukan Counting Sort untuk setiap karakter
    for place in range(max_length):
        counting_sort(arr, place)

# Fungsi untuk memisahkan kalimat menjadi kata-kata
def split_sentence(sentence):
    return sentence.split()

# Fungsi untuk menggabungkan kata-kata menjadi kalimat
def join_words(words):
    return ' '.join(words)

# Driver code
def main():
    sentence = "mari pergi"
    
    # Pisahkan kalimat menjadi kata-kata
    words = split_sentence(sentence)

    # Urutkan setiap kata menggunakan Radix Sort
    for i in range(len(words)):
        temp = [words[i]]  # Ubah kata menjadi list
        radix_sort(temp)   # Urutkan kata
        words[i] = temp[0]  # Ambil hasil pengurutan

    # Gabungkan kata-kata menjadi kalimat
    sorted_sentence = join_words(words)

    print("Kalimat sebelum diurutkan:", sentence)
    print("Kalimat setelah diurutkan:", sorted_sentence)

if __name__ == "__main__":
    main()