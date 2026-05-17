#include <stdio.h>

/* Paging: Logical to Physical Address Translation */
int main() {
    int page_size, logical_addr, page_table[10];
    int num_pages, i;

    printf("Enter page size: ");
    scanf("%d", &page_size);

    printf("Enter number of pages in page table: ");
    scanf("%d", &num_pages);

    printf("Enter page table (frame number for each page):\n");
    for (i = 0; i < num_pages; i++) {
        printf("Page %d: ", i);
        scanf("%d", &page_table[i]);
    }

    printf("\nEnter logical address to translate: ");
    scanf("%d", &logical_addr);

    int page_num = logical_addr / page_size;
    int offset = logical_addr % page_size;

    if (page_num >= num_pages) {
        printf("Invalid logical address (Page out of bounds)!\n");
    } else if (page_table[page_num] == -1) {
        printf("Page fault! Page not in memory.\n");
    } else {
        int physical_addr = (page_table[page_num] * page_size) + offset;
        printf("Logical Address: %d\n", logical_addr);
        printf("Page Number: %d, Offset: %d\n", page_num, offset);
        printf("Frame Number: %d\n", page_table[page_num]);
        printf("Physical Address: %d\n", physical_addr);
    }

    return 0;
}
