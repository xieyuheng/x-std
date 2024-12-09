[blob] `blob_test`

[blob] `blob_t` -- `bytes` with `length` -- with a extra ending '\0' to be viewed as string
[blob] `blob_new` -- call `realloc` to ensure a ending '\0'
[blob] `blob_length`
[blob] `blob_bytes`
[blob] `blob_string`

[file] `file_read_blob`
[file] `file_write_blob`

[store] `store_get` return `blob` instead of `bytes`

[store] also support `string` -- not only `bytes`

[font viewer] `font_viewer_init_font` -- load font from `asset_store`

[font viewer] `render_page` -- 0x10 chars per line
[font viewer] `render_page_up_button`
[font viewer] `render_page_down_button`

[font viewer] improve layout

[font] `glyph_encode_hex`

[font viewer] `render_glyph_info` -- show hex encoding of `glyph`

[font viewer] has button to next

[font editor] setup `font_editor/`

[font] `font_save_hex_file`
