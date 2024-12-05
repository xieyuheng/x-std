`cut_image_command` -- setup -- `cut-image` as a new command
`cut_image_command` -- call `chr_subimage` and save to `-o file` -- only handle `.chr` for now

[example] `example_button` -- quit using `chr_subimage`
[canvas] `canvas_render_image_button`

- load image from asset store
- get image size from path

```c
canvas_render_image_button(
    canvas, x, y,
    "asset-name",
    (on_click_t *) on_click_button);
```

[canvas] `canvas_draw_image` load asset from `asset_store`

[canvas] `canvas_draw_icn_bytes` handle alpha
[canvas] `canvas_draw_chr_bytes` handle alpha

[practice] button custom cursor

# canvas

[canvas] [maybe] give each 16 blending a name

# editor

[editor] `editor_t`
[editor] parse hex
[editor] use `canvas_draw_icn_bytes` to view font
[editor] `canvas_draw_text`
