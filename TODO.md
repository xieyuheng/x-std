[dict] setup `libs/dict` string to pointer kv-map

[dict] `dict_t`
[dict] `dict_test` setup
[dict] `dict_new`
[dict] `dict_destroy`
[dict] `dict_new_with`

[canvas] be able to config frame rate

[canvas] `asset_store_t` -- asset file with cache

[canvas] `canvas_render_image_button` -- load image from asset store

```c
canvas_render_image_button(
    canvas, x, y,
    "asset-name",
    (on_click_t *) on_click_button);
```

[canvas] `canvas_draw_icn_image` handle alpha
[canvas] `canvas_draw_chr_image` handle alpha

[practice] button custom cursor

# canvas

[canvas] [maybe] give each 16 blending a name

# editor

[editor] `editor` setup
[editor] parse hex
[editor] use `canvas_draw_icn_image` to view font
[editor] `canvas_draw_text`
