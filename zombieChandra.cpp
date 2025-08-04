#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <algorithm>

using namespace std;

const int MAX_LOCATIONS = 100;

struct Survivor {
    char name[20];
    int level;
    int exp;
    int health;
    int hunger;
    int thirst;
    int stamina;
    int supplies;
    int zombieKills;
    int daysSurvived;
};

struct Location {
    char name[50];
    char type[30];
    int distance;
    int zombieCount;
    int supplyValue;
    int dangerLevel;
    char status[20];
    bool isExplored;
    int lastVisit;
};

struct Supply {
    char name[50];
    char type[30];
    int quantity;
    int value;
    int weight;
    int durability;
    char effect[100];
    bool isConsumable;
};

struct Base {
    char name[50];
    int defense;
    int maxDefense;
    int capacity;
    int maxCapacity;
    int comfort;
    int maxComfort;
    int security;
    int maxSecurity;
    int upgradeLevel;
    char status[20];
};

Survivor survivor;
Location locations[MAX_LOCATIONS];
int locationCount = 0;

bool isValidString(const char* str) {
    return str[0] != '\0';
}

bool isValidLocationType(const char* type) {
    const char* validTypes[] = {"house", "supermarket", "hospital", "gas station"};
    for (int i = 0; i < 4; i++) {
        bool match = true;
        for (int j = 0; validTypes[i][j] != '\0' || type[j] != '\0'; j++) {
            if (validTypes[i][j] != type[j]) {
                match = false;
                break;
            }
            if (validTypes[i][j] == '\0' && type[j] == '\0') break;
        }
        if (match) return true;
    }
    return false;
}

void createSurvivor(Survivor &survivor) {
    survivor.level = 1;
    survivor.exp = 0;
    survivor.health = 100;
    survivor.hunger = 50;
    survivor.thirst = 50;
    survivor.stamina = 100;
    survivor.supplies = 0;
    survivor.zombieKills = 0;
    survivor.daysSurvived = 1;
    
    cout << "========= SURVIVOR STATISTIC =========" << endl;
    cout << "Nama: " << survivor.name << endl;
    cout << "Level: " << survivor.level << endl;
    cout << "Pengalaman: " << survivor.exp << " / 100" << endl;
    cout << "Kesehatan: " << survivor.health << " / 100" << endl;
    cout << "Kelaparan: " << survivor.hunger << " / 100" << endl;
    cout << "Kehausan: " << survivor.thirst << " / 100" << endl;
    cout << "Stamina: " << survivor.stamina << " / 100" << endl;
    cout << "Persediaan: " << survivor.supplies << endl;
    cout << "Zombi Tewas: " << survivor.zombieKills << endl;
    cout << "Hari Bertahan: " << survivor.daysSurvived << endl;
}

void displayStats(const Survivor &survivor) {
    cout << "========= SURVIVOR STATISTIC =========" << endl;
    cout << "Nama: " << survivor.name << endl;
    cout << "Level: " << survivor.level << endl;
    cout << "Pengalaman: " << survivor.exp << " / " << (survivor.level * 100) << endl;
    cout << "Kesehatan: " << survivor.health << " / 100" << endl;
    cout << "Kelaparan: " << survivor.hunger << " / 100" << endl;
    cout << "Kehausan: " << survivor.thirst << " / 100" << endl;
    cout << "Stamina: " << survivor.stamina << " / 100" << endl;
    cout << "Persediaan: " << survivor.supplies << endl;
    cout << "Zombi Tewas: " << survivor.zombieKills << endl;
    cout << "Hari Bertahan: " << survivor.daysSurvived << endl;
}

void updateSurvivalStats(Survivor &survivor) {
    survivor.hunger -= 10;
    survivor.thirst -= 15;
    survivor.stamina -= 5;
    survivor.daysSurvived++;

    if (survivor.hunger < 0) survivor.hunger = 0;
    if (survivor.thirst < 0) survivor.thirst = 0;
    if (survivor.stamina < 0) survivor.stamina = 0;
    if (survivor.hunger == 0 || survivor.thirst == 0) {
        survivor.health -= 10;
        if (survivor.health < 0) survivor.health = 0;
    }
}

int calculateSurvivalRating(const Survivor &survivor) {
    return survivor.health + survivor.supplies + survivor.daysSurvived;
}

void consumeSupplies(Survivor &survivor) {
    if (survivor.supplies >= 10) {
        survivor.supplies -= 10;
        survivor.hunger += 20;
        survivor.thirst += 20;
        survivor.stamina += 10;
        if (survivor.hunger > 100) survivor.hunger = 100;
        if (survivor.thirst > 100) survivor.thirst = 100;
        if (survivor.stamina > 100) survivor.stamina = 100;
        cout << "Persediaan digunakan. Kelaparan, kehausan, dan stamina pulih." << endl;
    } else {
        cout << "Persediaan tidak cukup!" << endl;
    }
}

void levelUp(Survivor &survivor) {
    if (survivor.exp >= survivor.level * 100) {
        survivor.level++;
        survivor.exp = 0;
        survivor.health += 10;
        survivor.stamina += 10;
        if (survivor.health > 100) survivor.health = 100;
        if (survivor.stamina > 100) survivor.stamina = 100;
        cout << "Selamat! " << survivor.name << " naik ke level " << survivor.level << "!" << endl;
    }
}

void addLocation(Location locations[], int &count) {
    if (count >= MAX_LOCATIONS) {
        cout << "Database lokasi penuh!" << endl;
        return;
    }
    Location &loc = locations[count];
    cout << "Masukkan nama lokasi: ";
    cin.getline(loc.name, 50);
    while (!isValidString(loc.name)) {
        cout << "Nama tidak valid! Masukkan nama yang valid: ";
        cin.getline(loc.name, 50);
    }
    cout << "Masukkan tipe lokasi (house/supermarket/hospital/gas station): ";
    cin.getline(loc.type, 30);
    while (!isValidLocationType(loc.type)) {
        cout << "Tipe tidak valid! Masukkan house/supermarket/hospital/gas station: ";
        cin.getline(loc.type, 30);
    }
    cout << "Masukkan jarak dari markas: ";
    cin >> loc.distance;
    while (loc.distance < 0) {
        cout << "Jarak tidak valid! Masukkan angka non-negatif: ";
        cin >> loc.distance;
    }
    cout << "Masukkan jumlah zombi: ";
    cin >> loc.zombieCount;
    while (loc.zombieCount < 0) {
        cout << "Jumlah zombi tidak valid! Masukkan angka non-negatif: ";
        cin >> loc.zombieCount;
    }
    cout << "Masukkan nilai persediaan: ";
    cin >> loc.supplyValue;
    while (loc.supplyValue < 0) {
        cout << "Nilai persediaan tidak valid! Masukkan angka non-negatif: ";
        cin >> loc.supplyValue;
    }
    cout << "Masukkan tingkat bahaya (1-10): ";
    cin >> loc.dangerLevel;
    while (loc.dangerLevel < 1 || loc.dangerLevel > 10) {
        cout << "Tingkat bahaya tidak valid! Masukkan angka antara 1 dan 10: ";
        cin >> loc.dangerLevel;
    }
    cin.ignore();
    loc.status[0] = 'U'; loc.status[1] = 'n'; loc.status[2] = 'k'; loc.status[3] = 'n'; loc.status[4] = 'o'; loc.status[5] = 'w'; loc.status[6] = 'n'; loc.status[7] = '\0';
    loc.isExplored = false;
    loc.lastVisit = 0;
    count++;
    cout << "Lokasi berhasil ditambahkan!" << endl;
}

void displayLocations(const Location locations[], int count) {
    cout << "\n========= DATABASE LOKASI =========" << endl;
    cout << left << setw(20) << "Nama" << setw(15) << "Tipe" << setw(10) << "Jarak"
         << setw(12) << "Zombi" << setw(12) << "Persediaan" << setw(12) << "Bahaya" << endl;
    for (int i = 0; i < count; i++) {
        cout << left << setw(20) << locations[i].name << setw(15) << locations[i].type
             << setw(10) << locations[i].distance << setw(12) << locations[i].zombieCount
             << setw(12) << locations[i].supplyValue << setw(12) << locations[i].dangerLevel << endl;
    }
}

void updateLocation(Location locations[], int count) {
    cout << "Masukkan indeks lokasi untuk diupdate (0-" << count-1 << "): ";
    int index;
    cin >> index;
    cin.ignore();
    if (index < 0 || index >= count) {
        cout << "Indeks tidak valid!" << endl;
        return;
    }
    Location &loc = locations[index];
    cout << "Masukkan nama lokasi baru: ";
    cin.getline(loc.name, 50);
    while (!isValidString(loc.name)) {
        cout << "Nama tidak valid! Masukkan nama yang valid: ";
        cin.getline(loc.name, 50);
    }
    cout << "Masukkan tipe lokasi baru (house/supermarket/hospital/gas station): ";
    cin.getline(loc.type, 30);
    while (!isValidLocationType(loc.type)) {
        cout << "Tipe tidak valid! Masukkan house/supermarket/hospital/gas station: ";
        cin.getline(loc.type, 30);
    }
    cout << "Masukkan jarak baru dari markas: ";
    cin >> loc.distance;
    while (loc.distance < 0) {
        cout << "Jarak tidak valid! Masukkan angka non-negatif: ";
        cin >> loc.distance;
    }
    cout << "Masukkan jumlah zombi baru: ";
    cin >> loc.zombieCount;
    while (loc.zombieCount < 0) {
        cout << "Jumlah zombi tidak valid! Masukkan angka non-negatif: ";
        cin >> loc.zombieCount;
    }
    cout << "Masukkan nilai persediaan baru: ";
    cin >> loc.supplyValue;
    while (loc.supplyValue < 0) {
        cout << "Nilai persediaan tidak valid! Masukkan angka non-negatif: ";
        cin >> loc.supplyValue;
    }
    cout << "Masukkan tingkat bahaya baru (1-10): ";
    cin >> loc.dangerLevel;
    while (loc.dangerLevel < 1 || loc.dangerLevel > 10) {
        cout << "Tingkat bahaya tidak valid! Masukkan angka antara 1 dan 10: ";
        cin >> loc.dangerLevel;
    }
    cin.ignore();
    cout << "Lokasi berhasil diupdate!" << endl;
}

void deleteLocation(Location locations[], int &count) {
    cout << "Masukkan indeks lokasi untuk dihapus (0-" << count-1 << "): ";
    int index;
    cin >> index;
    cin.ignore();
    if (index < 0 || index >= count) {
        cout << "Indeks tidak valid!" << endl;
        return;
    }
    for (int i = index; i < count-1; i++) {
        locations[i] = locations[i+1];
    }
    count--;
    cout << "Lokasi berhasil dihapus!" << endl;
}

void sortLocationsByDistance(Location locations[], int count) {
    for (int i = 0; i < count-1; i++) {
        for (int j = 0; j < count-i-1; j++) {
            if (locations[j].distance > locations[j+1].distance) {
                swap(locations[j], locations[j+1]);
            }
        }
    }
    cout << "Lokasi diurutkan berdasarkan jarak!" << endl;
}

void searchLocationsByType(const Location locations[], int count, const char* type) {
    cout << "\n========= LOKASI DENGAN TIPE: " << type << " =========" << endl;
    bool found = false;
    for (int i = 0; i < count; i++) {
        bool match = true;
        for (int j = 0; locations[i].type[j] != '\0' || type[j] != '\0'; j++) {
            if (locations[i].type[j] != type[j]) {
                match = false;
                break;
            }
            if (locations[i].type[j] == '\0' && type[j] == '\0') break;
        }
        if (match) {
            cout << "Indeks: " << i << ", Nama: " << locations[i].name
                 << ", Jarak: " << locations[i].distance
                 << ", Tingkat Bahaya: " << locations[i].dangerLevel << endl;
            found = true;
        }
    }
    if (!found) cout << "Tidak ada lokasi dengan tipe " << type << " ditemukan!" << endl;
}

void displayLocationsByDangerLevel(const Location locations[], int count, int dangerLevel) {
    cout << "\n========= LOKASI DENGAN TINGKAT BAHAYA: " << dangerLevel << " =========" << endl;
    bool found = false;
    for (int i = 0; i < count; i++) {
        if (locations[i].dangerLevel == dangerLevel) {
            cout << "Nama: " << locations[i].name << ", Tipe: " << locations[i].type
                 << ", Jarak: " << locations[i].distance << endl;
            found = true;
        }
    }
    if (!found) cout << "Tidak ada lokasi dengan tingkat bahaya " << dangerLevel << " ditemukan!" << endl;
}

int calculateScavengeSuccess(const Survivor &survivor, const Location &location) {
    return (survivor.stamina + survivor.supplies) - location.dangerLevel + (rand() % 20 + 1);
}

void collectSupplies(Survivor &survivor, Location &location) {
    int suppliesGained = location.supplyValue;
    survivor.supplies += suppliesGained;
    location.supplyValue = 0;
    survivor.exp += suppliesGained * 2;
    location.isExplored = true;
    location.lastVisit = survivor.daysSurvived;
    location.status[0] = 'E'; location.status[1] = 'x'; location.status[2] = 'p'; location.status[3] = 'l'; location.status[4] = 'o'; location.status[5] = 'r'; location.status[6] = 'e'; location.status[7] = 'd'; location.status[8] = '\0';
    cout << "Mengumpulkan " << suppliesGained << " persediaan!" << endl;
    levelUp(survivor);
}

int calculateCombatDamage(int weaponPower, int zombieCount) {
    return weaponPower * (rand() % 5 + 1) * zombieCount;
}

bool attemptEscape(Survivor &survivor, int dangerLevel) {
    int escapeChance = survivor.stamina - dangerLevel * 5 + (rand() % 20 + 1);
    if (escapeChance > 20) {
        survivor.stamina -= 20;
        if (survivor.stamina < 0) survivor.stamina = 0;
        cout << "Berhasil kabur!" << endl;
        return true;
    }
    cout << "Gagal kabur!" << endl;
    return false;
}

void zombieCombat(Survivor &survivor, Location &location) {
    int weaponPower = survivor.level * 5;
    int damageToZombies = calculateCombatDamage(weaponPower, location.zombieCount);
    location.zombieCount -= damageToZombies / 10;
    if (location.zombieCount < 0) location.zombieCount = 0;
    survivor.zombieKills += damageToZombies / 10;
    survivor.health -= location.dangerLevel * 5;
    survivor.stamina -= 20;
    survivor.exp += damageToZombies / 5;
    if (survivor.health < 0) survivor.health = 0;
    if (survivor.stamina < 0) survivor.stamina = 0;
    location.status[0] = 'C'; location.status[1] = 'l'; location.status[2] = 'e'; location.status[3] = 'a'; location.status[4] = 'r'; location.status[5] = 'e'; location.status[6] = 'd'; location.status[7] = '\0';
    location.isExplored = true;
    location.lastVisit = survivor.daysSurvived;
    cout << "Melawan zombi! Menimbulkan " << damageToZombies << " kerusakan, membunuh "
         << damageToZombies / 10 << " zombi." << endl;
    levelUp(survivor);
}

void scavengingSystem(Survivor &survivor, Location &location) {
    cout << "\nMencari di " << location.name << " (Tingkat Bahaya: " << location.dangerLevel << ")" << endl;
    if (survivor.health <= 0) {
        cout << "Survivor tidak bisa mencari karena kesehatan 0!" << endl;
        return;
    }
    int success = calculateScavengeSuccess(survivor, location);
    if (success > 50) {
        collectSupplies(survivor, location);
        cout << "Pencarian berhasil!" << endl;
    } else {
        cout << "Pencarian gagal! Menemui zombi!" << endl;
        char choice;
        cout << "Melawan (f) atau Kabur (e)? ";
        cin >> choice;
        cin.ignore();
        if (choice == 'f' || choice == 'F') {
            zombieCombat(survivor, location);
        } else {
            if (!attemptEscape(survivor, location.dangerLevel)) {
                zombieCombat(survivor, location);
            }
        }
    }
    updateSurvivalStats(survivor);
}

void WelcomeHome() {
    cout << "Siap siap lawan zombie bro!" << endl;
    cout << "Masukkan nama survivor: ";

    cin.getline(survivor.name, 20);

    cout << "Survivor " << survivor.name << " created successfully!" << endl;
    cout << "Mantap! Sekarang kamu siap bertahan hidup!" << endl;
    system("pause");
    system("cls");
}

int MainMenu() {
    cout << "========= SURVIVOR STATISTICS =========" << endl;
    cout << "1. Lihat Statistik" << endl;
    cout << "2. Manajemen Lokasi" << endl;
    cout << "3. Cari Persediaan di Lokasi" << endl;
    cout << "4. Gunakan Persediaan" << endl;
    cout << "5. Obati Pendarahan (jika berdarah)" << endl;
    cout << "6. Tidur & Hari Berikutnya" << endl;
    cout << "7. Lihat Karakter Mati" << endl;
    cout << "8. Keluar dari Permainan" << endl;
    cout << "Masukkan Pilihan: ";
    int choice;
    cin >> choice;
    cin.ignore();
    system("cls");
    return choice;
}

int MenuTwo() {
    cout << "========= MANAJEMEN LOKASI =========" << endl;
    cout << "1. Lihat Semua Lokasi" << endl;
    cout << "2. Tambah Lokasi Baru" << endl;
    cout << "3. Hapus Lokasi" << endl;
    cout << "4. Update Lokasi" << endl;
    cout << "5. Urutkan berdasarkan Jarak" << endl;
    cout << "6. Cari berdasarkan Tipe" << endl;
    cout << "7. Lihat berdasarkan Tingkat Bahaya" << endl;
    cout << "8. Kembali ke Menu Utama" << endl;
    cout << "Masukkan Pilihan: ";
    int choice;
    cin >> choice;
    cin.ignore();
    system("cls");
    return choice;
}

int main() {
    srand(time(0));
    WelcomeHome();
    int choice;

    do {
        choice = MainMenu();
        switch (choice) {
            case 1:
                displayStats(survivor);
                cout << "Rating Kelangsungan Hidup: " << calculateSurvivalRating(survivor) << endl;
                system("pause");
                system("cls");
                break;
            case 2: {
                int subChoice;
                do {
                    subChoice = MenuTwo();
                    switch (subChoice) {
                        case 1:
                            displayLocations(locations, locationCount);
                            system("pause");
                            system("cls");
                            break;
                        case 2:
                            addLocation(locations, locationCount);
                            system("pause");
                            system("cls");
                            break;
                        case 3:
                            displayLocations(locations, locationCount);
                            deleteLocation(locations, locationCount);
                            system("pause");
                            system("cls");
                            break;
                        case 4:
                            displayLocations(locations, locationCount);
                            updateLocation(locations, locationCount);
                            system("pause");
                            system("cls");
                            break;
                        case 5:
                            sortLocationsByDistance(locations, locationCount);
                            displayLocations(locations, locationCount);
                            system("pause");
                            system("cls");
                            break;
                        case 6: {
                            char type[30];
                            cout << "Masukkan tipe lokasi untuk dicari (house/supermarket/hospital/gas station): ";
                            cin.getline(type, 30);
                            searchLocationsByType(locations, locationCount, type);
                            system("pause");
                            system("cls");
                            break;
                        }
                        case 7: {
                            int dangerLevel;
                            cout << "Masukkan tingkat bahaya (1-10): ";
                            cin >> dangerLevel;
                            cin.ignore();
                            displayLocationsByDangerLevel(locations, locationCount, dangerLevel);
                            system("pause");
                            system("cls");
                            break;
                        }
                        case 8:
                            cout << "Kembali ke menu utama..." << endl;
                            system("cls");
                            break;
                        default:
                            cout << "Pilihan tidak valid!" << endl;
                            system("pause");
                            system("cls");
                    }
                } while (subChoice != 8);
                break;
            }
            case 3:
                if (locationCount > 0) {
                    displayLocations(locations, locationCount);
                    cout << "Pilih indeks lokasi untuk pencarian (0-" << locationCount-1 << "): ";
                    int index;
                    cin >> index;
                    cin.ignore();
                    if (index >= 0 && index < locationCount) {
                        scavengingSystem(survivor, locations[index]);
                    } else {
                        cout << "Indeks lokasi tidak valid!" << endl;
                    }
                } else {
                    cout << "Tambah lokasi terlebih dahulu!" << endl;
                }
                system("pause");
                system("cls");
                break;
            case 4:
                consumeSupplies(survivor);
                system("pause");
                system("cls");
                break;
            case 5:
                cout << "Fitur obati pendarahan belum diimplementasikan." << endl;
                system("pause");
                system("cls");
                break;
            case 6:
                updateSurvivalStats(survivor);
                cout << "Tidur... Hari baru dimulai!" << endl;
                system("pause");
                system("cls");
                break;
            case 7:
                cout << "Fitur lihat karakter mati belum diimplementasikan." << endl;
                system("pause");
                system("cls");
                break;
            case 8:
                cout << "Keluar dari permainan..." << endl;
                break;
            default:
                cout << "Pilihan tidak valid!" << endl;
                system("pause");
                system("cls");
        }
    } while (choice != 8);

    return 0;
}