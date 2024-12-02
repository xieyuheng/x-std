#pragma once

// row, col, width, height are all measured in tile.
uint8_t *chr_subimage(uint8_t *bytes, size_t row, size_t col, size_t width, size_t height);
