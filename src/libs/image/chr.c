#include "index.h"

uint8_t *
chr_subimage(
    uint8_t *bytes, size_t width,
    size_t start_col, size_t start_row,
    size_t subwidth, size_t subheight
) {
    assert(TILE_SIZE == 8);

    // one tile in chr has TILE_SIZE * 2 bytes.
    uint8_t *subimage = allocate(subwidth * subheight * TILE_SIZE * 2);

    for (size_t row = 0; row < subheight; row++) {
        for (size_t col = 0; col < subwidth; col++) {
            for (size_t line = 0; line < TILE_SIZE; line++) {
                size_t index =
                    (start_row + row) * TILE_SIZE * 2 * width +
                    (start_col + col) * TILE_SIZE * 2;
                size_t subindex =
                    row * TILE_SIZE * 2 * subwidth +
                    col * TILE_SIZE * 2;
                subimage[subindex] = bytes[index];
                subimage[subindex + TILE_SIZE] = bytes[index + TILE_SIZE];
            }
        }
    }

    return subimage;
}
