extract libs/destructor
[dict] `entry_t` -- private

[dict] `dict_new`
[dict] `dict_destroy`
[dict] `dict_new_with`

[canvas] be able to config frame rate

[canvas] `asset_store_t` -- asset file with cache

[canvas] `asset_store_has`
[canvas] `asset_store_get`
[canvas] `asset_store_set`

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
