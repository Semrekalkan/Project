#include <stdio.h>
#include <string.h>

// Fonksiyon prototipi
float similar_text(const char *str1, const char *str2);

int main() {
    char gkelime[100];      // Kullanıcının girdiği kelime
    char dkelime[100];       // Dosyadan okunan kelime
    char eniyieslesme[256] = ""; // En iyi eşleşen kelime
    float eybenzerlik = 0.0f; // En yüksek benzerlik oranı

    // Kullanıcıdan kelimeyi güvenli bir şekilde al
    printf("Bir kelime giriniz: ");
    if (fgets(gkelime, sizeof(gkelime), stdin) == NULL) {
        printf("Girdi alinamadi!\n");
        return 1;
    }
    gkelime[strcspn(gkelime, "\n")] = '\0'; // Satır sonunu kaldır

    // Dosyayı aç
    FILE *file = fopen("C:\\Users\\90545\\Desktop\\words.txt", "r"); // Bilgisayardaki dosyanin konumunu kullan ve words.txt dosyasini ac
    if (!file) {
        printf("Dosya acilamadi!\n");
        return 1;
    }

    // Dosyadaki her bir kelime ile karşılaştır
    while (fscanf(file, "%99s", dkelime) != EOF) { // Güvenli okuma
        float similarity = similar_text(gkelime, dkelime);
        if (similarity > eybenzerlik) {
            eybenzerlik = similarity;
            strncpy(eniyieslesme, dkelime, sizeof(eniyieslesme) - 1);
            eniyieslesme[sizeof(eniyieslesme) - 1] = '\0'; // Null terminator ekle
        }
    }
    fclose(file);
    // Benzerlik oranını değerlendir
    if (eybenzerlik > 0) {
        printf("Bunu mu demek istediniz? %s (Benzerlik Orani: %.2f)\n", eniyieslesme, eybenzerlik);
    } else {
        printf("Eslesme yok.\n");
    }
    return 0;
}
// İki kelimenin benzerlik oranını hesaplayan fonksiyon
float similar_text(const char *str1, const char *str2) {
    int match_count = 0;
    size_t len1 = strlen(str1);
    size_t len2 = strlen(str2);
    size_t min_len = len1 < len2 ? len1 : len2;
    // Boş kelimeler kontrolü
    if (len1 == 0 || len2 == 0) return 0.0f;
    // Aynı sırada eşleşen harfleri say
    for (int i = 0; i < min_len; i++) {
        if (str1[i] == str2[i]) {
            match_count++;
        }
    }
    // Ortalama uzunluğa göre oran hesaplama
    size_t total_len = (len1 + len2) / 2;
    return (float)(match_count) / (float)total_len;
}