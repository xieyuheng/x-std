#include "index.h"
#include "button_practice.h"

void
button_practice(void) {
    const char *file_name = __FILE__
        "/../button10x10.chr";
    printf("[button_practice] file_name: %s\n", file_name);
    file_t *file = fopen(file_name, "rb");
    uint8_t *bytes = file_read_bytes(file);
    uint8_t *button_up_chr = chr_subimage(bytes, 0x10, 0, 0, 3, 3);
    uint8_t *button_down_chr = chr_subimage(bytes, 0x10, 3, 0, 3, 3);

    (void) button_up_chr;
    (void) button_down_chr;
}
