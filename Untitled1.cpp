#include <stdio.h>
#include <string.h>
#include <ctype.h>


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
} Transactions;


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
void addMaterial(Material arr[], int *count) {
    Material m;
    char temp[100];

    printf("-------Nhap thong tin vat tu-------\n");

    // Nhap ma vat tu
    while (1) {
        printf("Nhap ma vat tu: ");
        fgets(temp, 100, stdin);
        temp[strcspn(temp, "\n")] = '\0';

        if (strlen(temp) == 0) {
            printf("Ma vat tu khong duoc rong!\n");
            continue;
        }
        if (isDupeId(arr, *count, temp)) {
            printf("Ma vat tu bi trung!\n");
            continue;
        }
        strcpy(m.matId, temp);
        break;
    }

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
        char buf[50];
        printf("Nhap so luong ton: ");
        fgets(buf, sizeof(buf), stdin);

            
	    if (strlen(buf) == 0) {
	        printf("So luong khong duoc rong!\n");
	        continue;
	    }

		if (sscanf(buf, "%d", &m.qty) != 1) {
            printf("Loi: Vui long nhap so nguyen!\n");
            continue;
        }
        if (m.qty < 0) {
            printf("So luong phai >= 0!\n");
            continue;
        }
        break;
    }

    m.status = 1; // active by default
    arr[*count] = m;
    (*count)++;

    printf("Them vat tu thanh cong!\n");
}

// Hien thi danh sach
void displayMaterials(Material arr[], int count) {
    int pageSize = 5;   // number of items per page
    int current = 0;    // index of first item on current page
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

        for (int i = current; i < current + pageSize && i < count; i++) {
            printf("%d. ID: %s | Ten: %s | Don vi: %s | Ton: %d | Trang thai: %d\n",
                   i + 1, arr[i].matId, arr[i].name, arr[i].unit,
                   arr[i].qty, arr[i].status);
        }

        // Show navigation options
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

// Tim vat tu theo ID
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
    printf("Vat tu tim thay: %s - %s - %s - %d\n",
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
            printf("ID: %s | Ten: %s | Don vi: %s | Ton: %d | Status: %d\n",
                   arr[i].matId, arr[i].name, arr[i].unit,
                   arr[i].qty, arr[i].status);
            found = 1;
        }
    }

    if (!found)
        printf("Khong tim thay vat tu phu hop!\n");
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
            printf("0. Thoat ve menu chinh\n");
            printf("Lua chon: ");

            fgets(buffer, sizeof(buffer), stdin);

            if (sscanf(buffer, "%d", &choice2) != 1) {
                printf("Loi: vui long nhap so!\n");
                continue;
            }

            switch (choice2) {
                case 1: addMaterial(list, &count); break;
                case 2: displayMaterials(list, count); break;
                case 3: updateMaterial(list, count); break;
                case 4:lockMaterial(list, count); break;
				case 5:searchMaterial(list, count); break;
                case 0: break;
                default: printf("Lua chon khong hop le!\n");
            }
        }

    case 2:
        while (1) {
            printf("\n****** MENU TRANSACTIONS ******\n");
            printf("0. Thoat ve menu chinh\n");
            printf("Lua chon: ");

            fgets(buffer, sizeof(buffer), stdin);

            if (sscanf(buffer, "%d", &choice2) != 1) {
                printf("Loi: vui long nhap so!\n");
                continue;
            }

            if (choice2 == 0) break;
            printf("Chua lam chuc nang nay!\n");
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
