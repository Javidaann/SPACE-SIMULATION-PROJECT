#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define PI 3.14159265359
#define NUM_PLANETS 8

// Gezegen isimleri
const char* planet_names[] = {
    "Merkur", "Venus", "Dunya", "Mars", 
    "Jupiter", "Saturn", "Uranus", "Neptun"
};

// Fonksiyon prototipleri
void print_menu();
void serbest_dusme(double*, double*);
void yukari_atis(double*, double*);
void agirlik(double*, double*);
void potansiyel_enerji(double*, double*, double*);
void hidrostatik_basinc(double*, double*, double*);
void arsimet_kaldirma(double*, double*, double*);
void sarkac_periyodu(double*, double*);
void ip_gerilmesi(double*, double*);
void asansor(double*, double*, double*);
double mutlak_deger(double);

int main() {
    // Gezegenlerin yerçekimi ivmeleri (m/s^2) - Güneşe yakından uzağa
    double g_values[NUM_PLANETS] = {
        3.7,   // Merkur
        8.87,  // Venus
        9.81,  // Dunya
        3.71,  // Mars
        24.79, // Jupiter
        10.44, // Saturn
        8.87,  // Uranus
        11.15  // Neptun
    };
    
    char scientist_name[100];
    int choice;
    
    // Bilim insanının adını al
    printf("========================================\n");
    printf("   UZAY SIMULASYONU PROGRAMINA HOSGELDINIZ\n");
    printf("========================================\n\n");
    printf("Lutfen adinizi girin: ");
    fgets(scientist_name, sizeof(scientist_name), stdin);
    scientist_name[strcspn(scientist_name, "\n")] = 0; // Satır sonu karakterini kaldır
    
    printf("\nHosgeldiniz %s!\n", scientist_name);
    printf("Simdi deneylere baslayabilirsiniz.\n\n");
    
    // Ana döngü
    while(1) {
        print_menu();
        printf("\nBir deney secin (Cikmak icin -1): ");
        scanf("%d", &choice);
        
        if(choice == -1) {
            printf("\n========================================\n");
            printf("Program sonlandiriliyor...\n");
            printf("%s, calismaniz icin tesekkur ederiz!\n", scientist_name);
            printf("========================================\n");
            break;
        }
        
        printf("\n========================================\n");
        printf("Bilim Insani: %s\n", scientist_name);
        printf("========================================\n");
        
        switch(choice) {
            case 1: {
                double time;
                printf("\nSerbest Dusme Deneyi secildi.\n");
                printf("Lutfen dusme suresini (saniye) girin: ");
                scanf("%lf", &time);
                time = mutlak_deger(time);
                serbest_dusme(&time, g_values);
                break;
            }
            case 2: {
                double v0;
                printf("\nYukari Atis Deneyi secildi.\n");
                printf("Lutfen baslangic hizini (m/s) girin: ");
                scanf("%lf", &v0);
                v0 = mutlak_deger(v0);
                yukari_atis(&v0, g_values);
                break;
            }
            case 3: {
                double mass;
                printf("\nAgirlik Deneyi secildi.\n");
                printf("Lutfen kutleyi (kg) girin: ");
                scanf("%lf", &mass);
                mass = mutlak_deger(mass);
                agirlik(&mass, g_values);
                break;
            }
            case 4: {
                double mass, height;
                printf("\nKutlecekimsel Potansiyel Enerji Deneyi secildi.\n");
                printf("Lutfen kutleyi (kg) girin: ");
                scanf("%lf", &mass);
                mass = mutlak_deger(mass);
                printf("Lutfen yuksekligi (m) girin: ");
                scanf("%lf", &height);
                height = mutlak_deger(height);
                potansiyel_enerji(&mass, &height, g_values);
                break;
            }
            case 5: {
                double density, depth;
                printf("\nHidrostatik Basinc Deneyi secildi.\n");
                printf("Lutfen sivinin yogunlugunu (kg/m^3) girin: ");
                scanf("%lf", &density);
                density = mutlak_deger(density);
                printf("Lutfen derinligi (m) girin: ");
                scanf("%lf", &depth);
                depth = mutlak_deger(depth);
                hidrostatik_basinc(&density, &depth, g_values);
                break;
            }
            case 6: {
                double density, volume;
                printf("\nArsimet Kaldirma Kuvveti Deneyi secildi.\n");
                printf("Lutfen sivinin yogunlugunu (kg/m^3) girin: ");
                scanf("%lf", &density);
                density = mutlak_deger(density);
                printf("Lutfen cismin batan hacmini (m^3) girin: ");
                scanf("%lf", &volume);
                volume = mutlak_deger(volume);
                arsimet_kaldirma(&density, &volume, g_values);
                break;
            }
            case 7: {
                double length;
                printf("\nBasit Sarkac Periyodu Deneyi secildi.\n");
                printf("Lutfen sarkac uzunlugunu (m) girin: ");
                scanf("%lf", &length);
                length = mutlak_deger(length);
                sarkac_periyodu(&length, g_values);
                break;
            }
            case 8: {
                double mass;
                printf("\nSabit Ip Gerilmesi Deneyi secildi.\n");
                printf("Lutfen kutleyi (kg) girin: ");
                scanf("%lf", &mass);
                mass = mutlak_deger(mass);
                ip_gerilmesi(&mass, g_values);
                break;
            }
            case 9: {
                double mass, acceleration;
                printf("\nAsansor Deneyi secildi.\n");
                printf("Lutfen kutleyi (kg) girin: ");
                scanf("%lf", &mass);
                mass = mutlak_deger(mass);
                printf("Lutfen asansor ivmesini (m/s^2) girin: ");
                printf("\n(Pozitif: yukari ivmelenme/asagi yavaslatma, Negatif: asagi ivmelenme/yukari yavaslatma)\n");
                scanf("%lf", &acceleration);
                asansor(&mass, &acceleration, g_values);
                break;
            }
            default:
                printf("\nGECERSIZ SECIM! Lutfen 1-9 arasinda bir sayi veya -1 girin.\n");
        }
        
        printf("\n");
    }
    
    return 0;
}

void print_menu() {
    printf("\n========================================\n");
    printf("          DENEY MENUSU\n");
    printf("========================================\n");
    printf("1. Serbest Dusme Deneyi\n");
    printf("2. Yukari Atis Deneyi\n");
    printf("3. Agirlik Deneyi\n");
    printf("4. Kutlecekimsel Potansiyel Enerji Deneyi\n");
    printf("5. Hidrostatik Basinc Deneyi\n");
    printf("6. Arsimet Kaldirma Kuvveti Deneyi\n");
    printf("7. Basit Sarkac Periyodu Deneyi\n");
    printf("8. Sabit Ip Gerilmesi Deneyi\n");
    printf("9. Asansor Deneyi\n");
    printf("========================================\n");
}

// Mutlak değer hesaplama
double mutlak_deger(double value) {
    return (value < 0) ? -value : value;
}

// 1. Serbest Düşme Deneyi
void serbest_dusme(double* time, double* g_array) {
    printf("\n--- SERBEST DUSME DENEYI SONUCLARI ---\n");
    printf("Dusme Suresi: %.2lf saniye\n\n", *time);
    
    for(int i = 0; i < NUM_PLANETS; i++) {
        double g = *(g_array + i);
        double height = 0.5 * g * (*time) * (*time);
        printf("%s yuzeyinde: %.2lf metre yol alindi\n", 
               *(planet_names + i), height);
    }
}

// 2. Yukarı Atış Deneyi
void yukari_atis(double* v0, double* g_array) {
    printf("\n--- YUKARI ATIS DENEYI SONUCLARI ---\n");
    printf("Baslangic Hizi: %.2lf m/s\n\n", *v0);
    
    for(int i = 0; i < NUM_PLANETS; i++) {
        double g = *(g_array + i);
        double h_max = (*v0) * (*v0) / (2.0 * g);
        printf("%s yuzeyinde maksimum yukseklik: %.2lf metre\n", 
               *(planet_names + i), h_max);
    }
}

// 3. Ağırlık Deneyi
void agirlik(double* mass, double* g_array) {
    printf("\n--- AGIRLIK DENEYI SONUCLARI ---\n");
    printf("Kutle: %.2lf kg\n\n", *mass);
    
    for(int i = 0; i < NUM_PLANETS; i++) {
        double g = *(g_array + i);
        double weight = (*mass) * g;
        printf("%s yuzeyinde agirlik: %.2lf Newton\n", 
               *(planet_names + i), weight);
    }
}

// 4. Kütleçekimsel Potansiyel Enerji Deneyi
void potansiyel_enerji(double* mass, double* height, double* g_array) {
    printf("\n--- KUTLECEKIMSEL POTANSIYEL ENERJI DENEYI SONUCLARI ---\n");
    printf("Kutle: %.2lf kg, Yukseklik: %.2lf metre\n\n", *mass, *height);
    
    for(int i = 0; i < NUM_PLANETS; i++) {
        double g = *(g_array + i);
        double energy = (*mass) * g * (*height);
        printf("%s yuzeyinde potansiyel enerji: %.2lf Joule\n", 
               *(planet_names + i), energy);
    }
}

// 5. Hidrostatik Basınç Deneyi
void hidrostatik_basinc(double* density, double* depth, double* g_array) {
    printf("\n--- HIDROSTATIK BASINC DENEYI SONUCLARI ---\n");
    printf("Sivi Yogunlugu: %.2lf kg/m^3, Derinlik: %.2lf metre\n\n", 
           *density, *depth);
    
    for(int i = 0; i < NUM_PLANETS; i++) {
        double g = *(g_array + i);
        double pressure = (*density) * g * (*depth);
        printf("%s yuzeyinde hidrostatik basinc: %.2lf Pascal\n", 
               *(planet_names + i), pressure);
    }
}

// 6. Arşimet Kaldırma Kuvveti Deneyi
void arsimet_kaldirma(double* density, double* volume, double* g_array) {
    printf("\n--- ARSIMET KALDIRMA KUVVETI DENEYI SONUCLARI ---\n");
    printf("Sivi Yogunlugu: %.2lf kg/m^3, Batan Hacim: %.2lf m^3\n\n", 
           *density, *volume);
    
    for(int i = 0; i < NUM_PLANETS; i++) {
        double g = *(g_array + i);
        double force = (*density) * g * (*volume);
        printf("%s yuzeyinde kaldirma kuvveti: %.2lf Newton\n", 
               *(planet_names + i), force);
    }
}

// 7. Basit Sarkaç Periyodu Deneyi
void sarkac_periyodu(double* length, double* g_array) {
    printf("\n--- BASIT SARKAC PERIYODU DENEYI SONUCLARI ---\n");
    printf("Sarkac Uzunlugu: %.2lf metre\n\n", *length);
    
    for(int i = 0; i < NUM_PLANETS; i++) {
        double g = *(g_array + i);
        double period = 2.0 * PI * sqrt((*length) / g);
        printf("%s yuzeyinde sarkac periyodu: %.2lf saniye\n", 
               *(planet_names + i), period);
    }
}

// 8. Sabit İp Gerilmesi Deneyi
void ip_gerilmesi(double* mass, double* g_array) {
    printf("\n--- SABIT IP GERILMESI DENEYI SONUCLARI ---\n");
    printf("Kutle: %.2lf kg\n\n", *mass);
    
    for(int i = 0; i < NUM_PLANETS; i++) {
        double g = *(g_array + i);
        double tension = (*mass) * g;
        printf("%s yuzeyinde ip gerilmesi: %.2lf Newton\n", 
               *(planet_names + i), tension);
    }
}

// 9. Asansör Deneyi
void asansor(double* mass, double* acceleration, double* g_array) {
    printf("\n--- ASANSOR DENEYI SONUCLARI ---\n");
    printf("Kutle: %.2lf kg, Asansor Ivmesi: %.2lf m/s^2\n\n", 
           *mass, *acceleration);
    
    for(int i = 0; i < NUM_PLANETS; i++) {
        double g = *(g_array + i);
        double effective_weight = (*mass) * (g + (*acceleration));
        printf("%s yuzeyinde etkin agirlik: %.2lf Newton\n", 
               *(planet_names + i), effective_weight);
    }
}
