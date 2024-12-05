`cut_image_command` -- call `chr_subimage` -- only handle `.chr` for now

```
bifer cut-image button10x10.chr 0 0 button-up.03x03.chr
bifer cut-image button10x10.chr 1 0 button-down.03x03.chr
```

[example] `example_button` -- quit using `chr_subimage`

[canvas] `canvas_draw_image` load asset from `asset_store`

[canvas] `canvas_render_image_button`

- load image from asset store
- get image size from path

```c
canvas_render_image_button(canvas, x, y, "asset-name", (on_click_t *) on_click_button);
```

[canvas] `canvas_draw_icn_bytes` handle alpha
[canvas] `canvas_draw_chr_bytes` handle alpha

[practice] button custom cursor

`example_blending` - a new example to show all the blendings

[canvas] give each 16 blending a name

# editor

[editor] `editor_t`
[editor] parse hex
[editor] use `canvas_draw_icn_bytes` to view font
[editor] `canvas_draw_text`
