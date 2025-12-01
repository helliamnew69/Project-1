#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

const int MAX = 100;

typedef struct {
    char matId[10];
    char name[50];
    char unit[10];
    int qty;
    int status;
} Material;

typedef struct {
    char txid[20];
    char matId[10];
    char type[5];
    char date[15];
    int amount;      // so luong giao dich

} Transactions;

#define MAX_TRANS 100   // so giao dich toi da

Transactions transList[MAX_TRANS]; // mang luu giao dich
int transCount = 0;                // so giao dich hien co

// Ham kiem tra matId co bi trung khong
int isDuplicateId(Material arr[], int n, const char *id) {
    for (int i = 0; i < n; i++) {
        if (strcmp(arr[i].matId, id) == 0) {
            return 1; // trung
        }
    }
    return 0;
}

// Ham kiem tra ten co bi trung khong
int isDuplicateName(Material arr[], int n, const char *name) {
    for (int i = 0; i < n; i++) {
        if (strcmp(arr[i].name, name) == 0) {
            return 1; // trung
        }
    }
    return 0;
}



int isAlphaString(const char *s) {
    for (int i = 0; s[i] != '\0'; i++) {
        if (!isalpha(s[i]) && s[i] != ' ') {
            return 0; 
        }
    }
    return 1; 
}
// Kiem tra trung ID
int isDupeId(Material arr[], int count, char id[]) {
    for (int i = 0; i < count; i++) {
        if (strcmp(arr[i].matId, id) == 0) {
            return 1;
        }
    }
    return 0;
}

// Them vat tu 
void addMaterial(Material arr[], int *n) {
    Material m;
    char buf[50];

    // Nhap matId, khong duoc rong va khong trung
    while (1) {
        printf("Nhap matId: ");
        fgets(m.matId, sizeof(m.matId), stdin);
        m.matId[strcspn(m.matId, "\n")] = '\0';

        if (strlen(m.matId) == 0) {
            printf("matId khong duoc rong!\n");
            continue;
        }
        if (isDuplicateId(arr, *n, m.matId)) {
            printf("matId da ton tai, vui long nhap lai!\n");
            continue;
        }
        break;
    }

    // Nhap ten, khong duoc rong, chi chu cai, khong trung
    while (1) {
        printf("Nhap ten vat tu: ");
        fgets(m.name, sizeof(m.name), stdin);
        m.name[strcspn(m.name, "\n")] = '\0';

        if (strlen(m.name) == 0) {
            printf("Ten vat tu khong duoc rong!\n");
            continue;
        }
        if (!isAlphaString(m.name)) {
            printf("Ten vat tu chi duoc chua chu cai!\n");
            continue;
        }
        if (isDuplicateName(arr, *n, m.name)) {
            printf("Ten vat tu da ton tai, vui long nhap lai!\n");
            continue;
        }
        break;
    }

    // Nhap don vi
    while (1) {
        printf("Nhap don vi: ");
        fgets(m.unit, sizeof(m.unit), stdin);
        m.unit[strcspn(m.unit, "\n")] = '\0';

        if (strlen(m.unit) == 0) {
            printf("Don vi khong duoc rong!\n");
            continue;
        }
        if (!isAlphaString(m.unit)) {
            printf("Don vi chi duoc chua chu cai!\n");
            continue;
        }
        break;
    }

    // Nhap so luong
    while (1) {
        printf("Nhap so luong ton: ");
        fgets(buf, sizeof(buf), stdin);

        if (sscanf(buf, "%d", &m.qty) != 1) {
            printf("Loi: vui long nhap so nguyen!\n");
            continue;
        }
        if (m.qty < 0) {
            printf("So luong phai >= 0!\n");
            continue;
        }
        break;
    }

    m.status = 1; // mac dinh la mo khoa
    arr[*n] = m;
    (*n)++;

    printf("Them vat tu thanh cong!\n");
}


// Hien thi danh sach
void displayMaterials(Material arr[], int count) {
    int pageSize = 5;
    int current = 0;
    char buf[10];
    int choice;

    if (count == 0) {
        printf("\nDanh sach vat tu rong!\n");
        return;
    }

    while (1) {
        printf("\n===== DANH SACH VAT TU (tu %d den %d/%d) =====\n",
               current + 1,
               (current + pageSize > count ? count : current + pageSize),
               count);

        
        printf("+----+----------+----------------------+------------+-------+--------+\n");
        printf("| STT| ID       | Ten                  | Don vi     | Ton   | Status |\n");
        printf("+----+----------+----------------------+------------+-------+--------+\n");

        for (int i = current; i < current + pageSize && i < count; i++) {
            printf("| %-2d | %-8s | %-20s | %-10s | %-5d | %-6d |\n",
                   i + 1,
                   arr[i].matId,
                   arr[i].name,
                   arr[i].unit,
                   arr[i].qty,
                   arr[i].status);
        }

        
        printf("+----+----------+----------------------+------------+-------+--------+\n");

        
        printf("\n--- Dieu huong ---\n");
        if (current > 0) printf("1. Trang truoc\n");
        if (current + pageSize < count) printf("2. Trang sau\n");
        printf("0. Thoat\n");
        printf("Lua chon: ");

        fgets(buf, sizeof(buf), stdin);
        if (sscanf(buf, "%d", &choice) != 1) {
            printf("Loi: vui long nhap so!\n");
            continue;
        }

        if (choice == 1 && current > 0) {
            current -= pageSize;
            if (current < 0) current = 0;
        } else if (choice == 2 && current + pageSize < count) {
            current += pageSize;
        } else if (choice == 0) {
            break;
        } else {
            printf("Lua chon khong hop le!\n");
        }
    }
}


int findMaterialById(Material arr[], int n, char id[]) {
    for (int i = 0; i < n; i++) {
        if (strcmp(arr[i].matId, id) == 0)
            return i;
    }
    return -1;
}



// Cap nhat vat tu 
void updateMaterial(Material arr[], int n) {
    char id[10];

    // Force user to enter non-empty matId
    while (1) {
        printf("Nhap matId can cap nhat: ");
        fgets(id, sizeof(id), stdin);
        id[strcspn(id, "\n")] = '\0';

        if (strlen(id) == 0) {
            printf("matId khong duoc rong!\n");
            continue;  // hoi lai
        }
        break; 
    }

    int pos = findMaterialById(arr, n, id);
    if (pos == -1) {
        printf("Khong tim thay vat tu!\n");
        return;
    }

    Material *m = &arr[pos];
    printf("Vat tu: %s - %s - %s - %d\n",
           m->matId, m->name, m->unit, m->qty);

    char newName[50];
    char newUnit[20];
    char buf[50];
    int newQty;

    // Ten moi
    while (1) {
        printf("Nhap ten moi: ");
        fgets(newName, sizeof(newName), stdin);
        newName[strcspn(newName, "\n")] = '\0';

        if (strlen(newName) == 0) {
            printf("Ten vat tu khong duoc rong!\n");
            continue;
        }
        if (!isAlphaString(newName)) {
            printf("Ten vat tu chi duoc chua chu cai!\n");
            continue;
        }
        break;
    }

    // Don vi moi
    while (1) {
        printf("Nhap don vi moi: ");
        fgets(newUnit, sizeof(newUnit), stdin);
        newUnit[strcspn(newUnit, "\n")] = '\0';

        if (strlen(newUnit) == 0) {
            printf("Don vi khong duoc rong!\n");
            continue;
        }
        if (!isAlphaString(newUnit)) {
            printf("Don vi chi duoc chua chu cai!\n");
            continue;
        }
        break;
    }

    // So luong moi
    while (1) {
        printf("Nhap so luong moi: ");
        fgets(buf, sizeof(buf), stdin);

        if (sscanf(buf, "%d", &newQty) != 1) {
            printf("Loi: Vui long nhap so nguyen!\n");
            continue;
        }
        if (newQty < 0) {
            printf("So luong phai >= 0!\n");
            continue;
        }
        break;
    }

    strcpy(m->name, newName);
    strcpy(m->unit, newUnit);
    m->qty = newQty;

    printf("Cap nhat thanh cong!\n");
}

void lockMaterial(Material arr[], int n) {
    char id[10];
    printf("Nhap matId can khoa/mo khoa: ");
    fgets(id, sizeof(id), stdin);
    id[strcspn(id, "\n")] = '\0';

    if (strlen(id) == 0) {
        printf("matId khong duoc rong!\n");
        return;
    }

    int pos = findMaterialById(arr, n, id);
    if (pos == -1) {
        printf("Khong tim thay vat tu!\n");
        return;
    }

    // Toggle status
    if (arr[pos].status == 1) {
        arr[pos].status = 0;
        printf("Vat tu %s da bi KHOA (status = 0)\n", arr[pos].matId);
    } else {
        arr[pos].status = 1;
        printf("Vat tu %s da duoc MO KHOA (status = 1)\n", arr[pos].matId);
    }
}


int containsIgnoreCase(char *str, char *sub) {
    char a[100], b[100];
    strcpy(a, str);
    strcpy(b, sub);

    // Convert to lowercase
    for (int i = 0; a[i]; i++) a[i] = tolower(a[i]);
    for (int i = 0; b[i]; i++) b[i] = tolower(b[i]);

    return strstr(a, b) != NULL;
}

void searchMaterial(Material arr[], int n) {
    char key[50];
    printf("Nhap tu khoa tim kiem (ID hoac ten): ");
    fgets(key, sizeof(key), stdin);
    key[strcspn(key, "\n")] = '\0';

    // Prevent empty input
    if (strlen(key) == 0) {
        printf("Tu khoa khong duoc rong!\n");
        return;
    }

    int found = 0;
    printf("\n===== KET QUA TIM KIEM =====\n");

    for (int i = 0; i < n; i++) {
        // Match by exact ID or case-insensitive substring in name
        if (strcmp(arr[i].matId, key) == 0 ||
            containsIgnoreCase(arr[i].name, key)) {
            printf("| %-8s | %-20s | %-10s | %-7d | %-6d |\n",
                   arr[i].matId, arr[i].name, arr[i].unit,
                   arr[i].qty, arr[i].status);
            found = 1;
        }
    }

    if (!found)
        printf("Khong tim thay vat tu phu hop!\n");
}


void sortByNameAsc(Material arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (strcmp(arr[i].name, arr[j].name) > 0) {
                Material tmp = arr[i];
                arr[i] = arr[j];
                arr[j] = tmp;
            }
        }
    }
}


void sortByQtyAsc(Material arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (arr[i].qty > arr[j].qty) {
                Material tmp = arr[i];
                arr[i] = arr[j];
                arr[j] = tmp;
            }
        }
    }
}


void sortByQtyDesc(Material arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (arr[i].qty < arr[j].qty) {
                Material tmp = arr[i];
                arr[i] = arr[j];
                arr[j] = tmp;
            }
        }
    }
}

void sortByNameDesc(Material arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (strcmp(arr[i].name, arr[j].name) < 0) {
                Material tmp = arr[i];
                arr[i] = arr[j];
                arr[j] = tmp;
            }
        }
    }
}

void sortMaterials(Material arr[], int count) {
    char buf[10];
    int choice;

    printf("\n===== SAP XEP DANH SACH =====\n");
    printf("1. Theo Ten (A-Z)\n");
    printf("2. Theo Ten (Z-A)\n");
    printf("3. Theo So luong (Tang dan)\n");
    printf("4. Theo So luong (Giam dan)\n");
    printf("Lua chon: ");

    fgets(buf, sizeof(buf), stdin);
    if (sscanf(buf, "%d", &choice) != 1) {
        printf("Loi: vui long nhap so!\n");
        return;
    }

    switch (choice) {
        case 1: sortByNameAsc(arr, count); printf("Da sap xep theo Ten (A-Z).\n"); break;
        case 2: sortByNameDesc(arr, count); printf("Da sap xep theo Ten (Z-A).\n"); break;
        case 3: sortByQtyAsc(arr, count); printf("Da sap xep theo So luong (Tang dan).\n"); break;
        case 4: sortByQtyDesc(arr, count); printf("Da sap xep theo So luong (Giam dan).\n"); break;
        default: printf("Lua chon khong hop le!\n"); return;
    }

    displayMaterials(arr, count);
}

// Ham luu danh sach vat tu vao file
void saveMaterialsToFile(Material arr[], int count, const char *filename) {
    FILE *f = fopen(filename, "w");
    if (f == NULL) {
        printf("Khong mo duoc file %s\n", filename);
        return;
    }

    for (int i = 0; i < count; i++) {
        fprintf(f, "%s,%s,%s,%d,%d\n",
                arr[i].matId,
                arr[i].name,
                arr[i].unit,
                arr[i].qty,
                arr[i].status);
    }

    fclose(f);
    printf("Da luu danh sach vao file %s\n", filename);
}

// Ham doc danh sach vat tu tu file
int loadMaterialsFromFile(Material arr[], int maxCount, const char *filename) {
    FILE *f = fopen(filename, "r");
    if (f == NULL) {
        printf("Khong mo duoc file %s\n", filename);
        return 0;
    }

    int count = 0;
    while (count < maxCount &&
           fscanf(f, "%[^,],%[^,],%[^,],%d,%d\n",
                  arr[count].matId,
                  arr[count].name,
                  arr[count].unit,
                  &arr[count].qty,
                  &arr[count].status) == 5) {
        count++;
    }

    fclose(f);
    printf("Da tai %d vat tu tu file %s\n", count, filename);
    return count;
}

void transactionMaterial(Material arr[], int n) {
    char id[10], buf[50];
    int choice, amount;

    printf("\n===== F07: GIAO DICH XUAT / NHAP =====\n");
    printf("Nhap matId: ");
    fgets(id, sizeof(id), stdin);
    id[strcspn(id, "\n")] = '\0';

    int pos = findMaterialById(arr, n, id);
    if (pos == -1) {
        printf("Khong tim thay vat tu!\n");
        return;
    }

    if (arr[pos].status != 1) {
        printf("Vat tu dang bi khoa, khong the giao dich!\n");
        return;
    }

    // Lua chon giao dich
    while (1) {
        printf("1. Nhap vat tu (IN)\n");
        printf("2. Xuat vat tu (OUT)\n");
        printf("Lua chon: ");
        fgets(buf, sizeof(buf), stdin);

        if (sscanf(buf, "%d", &choice) != 1 || (choice != 1 && choice != 2)) {
            printf("Loi: vui long nhap 1 hoac 2!\n");
            continue;
        }
        break;
    }

    // Nhap so luong
    while (1) {
        printf("Nhap so luong: ");
        fgets(buf, sizeof(buf), stdin);

        if (sscanf(buf, "%d", &amount) != 1) {
            printf("Loi: vui long nhap so nguyen!\n");
            continue;
        }
        if (amount <= 0) {
            printf("So luong phai > 0!\n");
            continue;
        }
        if (choice == 2 && amount > arr[pos].qty) {
            printf("So luong xuat phai <= ton kho (%d)!\n", arr[pos].qty);
            continue;
        }
        break;
    }

    // Thuc hien giao dich
    if (choice == 1) { // Nhap
        arr[pos].qty += amount;
        sprintf(transList[transCount].txid, "TX%03d", transCount + 1);
        strcpy(transList[transCount].matId, id);
        strcpy(transList[transCount].type, "IN");
        strcpy(transList[transCount].date, "2025-11-28"); // tam thoi
        transList[transCount].amount = amount;
        transCount++;
        printf("Da nhap %d cho vat tu %s. Ton kho moi: %d\n",
               amount, arr[pos].matId, arr[pos].qty);
    } else { // Xuat
        arr[pos].qty -= amount;
        sprintf(transList[transCount].txid, "TX%03d", transCount + 1);
        strcpy(transList[transCount].matId, id);
        strcpy(transList[transCount].type, "OUT");
        strcpy(transList[transCount].date, "2025-11-28"); // tam thoi
        transList[transCount].amount = amount;
        transCount++;
        printf("Da xuat %d cho vat tu %s. Ton kho moi: %d\n",
               amount, arr[pos].matId, arr[pos].qty);
    }
}

void historyTransactionAllPaged(int pageSize) {
    if (transCount == 0) {
        printf("\n===== F08: LICH SU GIAO DICH =====\n");
        printf("Chua co giao dich nao!\n");
        return;
    }

    int totalPages = (transCount + pageSize - 1) / pageSize;
    int currentPage = 1;
    char buf[10];

    while (1) {
        printf("\n===== F08: LICH SU GIAO DICH (Trang %d/%d) =====\n",
               currentPage, totalPages);

        // In tiêu d? b?ng
        printf("+--------+----------+------+------------+---------+\n");
        printf("| TXID   | MatID    | Loai | Ngay       | Amount  |\n");
        printf("+--------+----------+------+------------+---------+\n");

        int start = (currentPage - 1) * pageSize;
        int end = start + pageSize;
        if (end > transCount) end = transCount;

        for (int i = start; i < end; i++) {
            printf("| %-6s | %-8s | %-4s | %-10s | %-7d |\n",
                   transList[i].txid,
                   transList[i].matId,
                   transList[i].type,
                   transList[i].date,
                   transList[i].amount);
        }

        // In du?ng k? cu?i b?ng
        printf("+--------+----------+------+------------+---------+\n");

        // Ði?u hu?ng
        printf("\n--- Dieu huong ---\n");
        if (currentPage > 1) printf("P. Trang truoc\n");
        if (currentPage < totalPages) printf("N. Trang sau\n");
        printf("0. Thoat\n");
        printf("Lua chon: ");

        fgets(buf, sizeof(buf), stdin);

        if (buf[0] == 'N' || buf[0] == 'n') {
            if (currentPage < totalPages) currentPage++;
            else printf("Dang o trang cuoi!\n");
        } else if (buf[0] == 'P' || buf[0] == 'p') {
            if (currentPage > 1) currentPage--;
            else printf("Dang o trang dau!\n");
        } else if (buf[0] == '0') {
            break;
        } else {
            printf("Lua chon khong hop le!\n");
        }
    }
}

// F09: Luu hoac doc du lieu tu file
void fileMaterials(Material arr[], int *count, int maxCount) {
    char buf[10];
    int choice;

    printf("\n===== F09: LUU / DOC DU LIEU TU FILE =====\n");
    printf("1. Luu danh sach vao file\n");
    printf("2. Doc danh sach tu file\n");
    printf("Lua chon: ");

    fgets(buf, sizeof(buf), stdin);
    if (sscanf(buf, "%d", &choice) != 1) {
        printf("Loi: vui long nhap so!\n");
        return;
    }

    if (choice == 1) {
        saveMaterialsToFile(arr, *count, "materials.txt");
    } else if (choice == 2) {
        *count = loadMaterialsFromFile(arr, maxCount, "materials.txt");
    } else {
        printf("Lua chon khong hop le!\n");
    }
}


int main() {
    Material list[100];
    int count = 0;
    int choice1;
    int choice2;
    char buffer[100];

    while (1) {
        printf("\n====== MENU ======\n");
        printf("1. Quan ly material\n");
        printf("2. Quan ly transactions\n");
        printf("0. Thoat\n");
        printf("Lua chon: ");

        fgets(buffer, sizeof(buffer), stdin);

        if (sscanf(buffer, "%d", &choice1) != 1) {
            printf("Loi: vui long nhap so!\n");
            continue;
        }

        switch (choice1) {
        case 1:
            while (1) {
                printf("\n****** MENU MATERIAL ******\n");
                printf("1. Them ma hang moi\n");
                printf("2. Hien thi danh sach vat tu\n");
                printf("3. Cap nhat vat tu\n");
                printf("4. Khoa vat tu\n");
                printf("5. Tim kiem vat tu\n");
                printf("6. Sap xep danh sach vat tu\n");
                printf("9. Luu / Doc du lieu tu file\n");
                printf("0. Thoat ve menu chinh\n");
                printf("Lua chon: ");

                fgets(buffer, sizeof(buffer), stdin);

                if (sscanf(buffer, "%d", &choice2) != 1) {
                    printf("Loi: vui long nhap so!\n");
                    continue;
                }

                if (choice2 == 0) break;

                switch (choice2) {
                    case 1: addMaterial(list, &count); break;
                    case 2: displayMaterials(list, count); break;
                    case 3: updateMaterial(list, count); break;
                    case 4: lockMaterial(list, count); break;
                    case 5: searchMaterial(list, count); break;
                    case 6: sortMaterials(list, count); break;
                    case 9: fileMaterials(list, &count, MAX); break;
                    default: printf("Lua chon khong hop le!\n");
                }
            }
            break;

        case 2:
            while (1) {
                printf("\n****** MENU TRANSACTIONS ******\n");
                printf("1. Giao dich xuat/nhap vat tu \n");
                printf("2. Lich su xuat/nhap vat tu \n");
                printf("0. Thoat ve menu chinh\n");
                printf("Lua chon: ");

                fgets(buffer, sizeof(buffer), stdin);

                if (sscanf(buffer, "%d", &choice2) != 1) {
                    printf("Loi: vui long nhap so!\n");
                    continue;
                }

                if (choice2 == 0) break;

                switch (choice2) {
                    case 1: transactionMaterial(list, count); break;
                    case 2: 
                        historyTransactionAllPaged(5);
                        break;
                    
                    default: printf("Lua chon khong hop le!\n");
                }
            }
            break;

        case 0:
            printf("Thoat chuong trinh...\n");
            return 0;

        default:
            printf("Lua chon khong hop le!\n");
        }
    }
}
