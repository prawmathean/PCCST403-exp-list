#include <stdio.h>

int main() {
    long virtual_space_mb, page_size_kb, virtual_addr;

    printf("Enter Virtual Address Space Size (in MB): ");
    scanf("%ld", &virtual_space_mb);

    printf("Enter Page Size (in KB): ");
    scanf("%ld", &page_size_kb);

    printf("Enter Virtual Address (decimal): ");
    scanf("%ld", &virtual_addr);

    // Conversions
    long virtual_space_bytes = virtual_space_mb * 1024 * 1024;
    long page_size_bytes = page_size_kb * 1024;

    if (virtual_addr >= virtual_space_bytes) {
        printf("\nError: Virtual address is out of bounds!\n");
        return 1;
    }

    // Calculations
    long page_number = virtual_addr / page_size_bytes;
    long offset = virtual_addr % page_size_bytes;

    printf("\n--- Address Translation Results ---\n");
    printf("Virtual Address: %ld\n", virtual_addr);
    printf("Page Number: %ld\n", page_number);
    printf("Offset: %ld\n", offset);

    // In a real system, page table maps page_number -> frame_number
    // Here we can simulate a simple mapping (e.g., frame = page + 100)
    long frame_number = page_number + 100; 
    printf("Simulated Physical Address: <Frame: %ld, Offset: %ld>\n", frame_number, offset);

    return 0;
}
