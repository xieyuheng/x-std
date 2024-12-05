fix all the use of `allocate(sizeof`

[store] `store_destroy`
[store] `store_base`
[store] `store_clear_cache`

[store] `store_has`
[store] `store_get`
[store] `store_set`

[canvas] `canvas` has `asset_store`
[canvas] `canvas_asset_get`

`example_button` -- no need to have `button_up_chr` and `button_down_chr`

- just load from store during rendering

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

[editor] `editor_t`
[editor] parse hex
[editor] use `canvas_draw_icn_image` to view font
[editor] `canvas_draw_text`
