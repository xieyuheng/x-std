#include "index.h"

canvas_window_t *
canvas_window_new(canvas_t *canvas, size_t scale) {
    canvas_window_t *self = allocate(sizeof(canvas_window_t));
    self->canvas = canvas;
    self->scale = scale;

    size_t image_width = self->canvas->width * self->scale;
    size_t image_height = self->canvas->height * self->scale;

    self->image_buffer = allocate(image_width * image_height * sizeof(uint32_t));

    self->width = image_width;
    self->height = image_height;

    return self;
}

void
canvas_window_destroy(canvas_window_t **self_pointer) {
    assert(self_pointer);
    if (*self_pointer) {
        canvas_window_t *self = *self_pointer;
        if (self->image) XFree(self->image);
        free(self->image_buffer);
        free(self);
        *self_pointer = NULL;
    }
}

static void canvas_window_init_display(canvas_window_t *self);
static void canvas_window_init_window(canvas_window_t *self);
static void canvas_window_init_input(canvas_window_t *self);
static void canvas_window_init_title(canvas_window_t *self);

static void
canvas_window_init(canvas_window_t *self) {
    canvas_window_init_display(self);
    canvas_window_init_window(self);
    canvas_window_init_input(self);
    canvas_window_init_title(self);
}

void
canvas_window_init_display(canvas_window_t *self) {
    self->display = XOpenDisplay(NULL);
    assert(self->display);

    int screen = DefaultScreen(self->display);

    int width = XDisplayWidth(self->display, screen);
    int height = XDisplayHeight(self->display, screen);
    printf("[canvas_window_init_display] width:  %upx\n", width);
    printf("[canvas_window_init_display] height: %upx\n", height);

    uint32_t black_pixel = XBlackPixel(self->display, screen);
    uint32_t white_pixel = XWhitePixel(self->display, screen);
    printf("[canvas_window_init_display] black pixel: 0x%x\n", black_pixel);
    printf("[canvas_window_init_display] white pixel: 0x%x\n", white_pixel);
}

void
canvas_window_init_window(canvas_window_t *self) {
    int window_x = 0;
    int window_y = 0;
    uint64_t border_width = 1;
    uint64_t border_pixel = 0;
    uint64_t background_pixel = 0;
    self->window = XCreateSimpleWindow(
        self->display,
        XDefaultRootWindow(self->display),
        window_x, window_y,
        self->width,
        self->height,
        border_width,  border_pixel,
        background_pixel);
}

void
canvas_window_init_input(canvas_window_t *self) {
    long event_mask =
        ButtonPressMask |
        ButtonReleaseMask |
        PointerMotionMask |
        ExposureMask |
        KeyPressMask |
        KeyReleaseMask |
        StructureNotifyMask;
    XSelectInput(self->display, self->window, event_mask);
}

void
canvas_window_init_title(canvas_window_t *self) {
    XClassHint *class_hint = XAllocClassHint();
    class_hint->res_name = string_dup("bifer");
    class_hint->res_class = string_dup("canvas");
    XSetClassHint(self->display, self->window, class_hint);

    if (self->title)
        XStoreName(self->display, self->window, self->title);
}

static void
canvas_window_update_pixel(canvas_window_t *self, size_t col, size_t row) {
    uint32_t index = row * self->canvas->width + col;
    uint32_t pixel = self->canvas->pixels[index];
    uint32_t y_start = row * self->scale;
    uint32_t x_start = col * self->scale;
    uint32_t x_width = self->canvas->width * self->scale;
    for (size_t y = y_start; y < y_start + self->scale; y++) {
        for (size_t x = x_start; x < x_start + self->scale; x++) {
            self->image_buffer[y * x_width + x] = pixel;
        }
    }
}

static void
canvas_window_update_image_buffer(canvas_window_t *self) {
    for (size_t row = 0; row < self->canvas->height; row++) {
        for (size_t col = 0; col < self->canvas->width; col++) {
            canvas_window_update_pixel(self, col, row);
        }
    }
}

static void
canvas_window_update_image(canvas_window_t *self) {
    canvas_window_update_image_buffer(self);

    Visual *visual = XDefaultVisual(self->display, 0);
    uint64_t image_depth = XDefaultDepth(self->display, 0);
    int64_t image_offset = 0;
    int64_t pixel_bytes = sizeof(uint32_t);
    int64_t pixel_bits = pixel_bytes * 8;
    int64_t bytes_per_line = 0;

    size_t image_width = self->canvas->width * self->scale;
    size_t image_height = self->canvas->height * self->scale;

    if (self->image) XFree(self->image);
    self->image = XCreateImage(
        self->display, visual,
        image_depth, ZPixmap, image_offset,
        (char *) self->image_buffer,
        image_width, image_height,
        pixel_bits, bytes_per_line);
}

static void
canvas_window_resize(canvas_window_t *self, size_t width, size_t height) {
    printf("[canvas_window_resize] width:  %lupx\n", width);
    printf("[canvas_window_resize] height: %lupx\n", width);

    self->width = width;
    self->height = height;

    size_t width_scale = self->width / (self->canvas->width);
    size_t height_scale = self->height / (self->canvas->height);
    self->scale = uint_min(width_scale, height_scale);

    size_t image_width = self->canvas->width * self->scale;
    size_t image_height = self->canvas->height * self->scale;

    self->image_buffer = realloc(
        self->image_buffer,
        image_width *
        image_height *
        sizeof(uint32_t));

    canvas_window_update_image(self);
}

static void
canvas_window_show_image(canvas_window_t *self) {
    size_t image_width = self->canvas->width * self->scale;
    size_t image_height = self->canvas->height * self->scale;

    size_t x_offset = (self->width - image_width) / 2;
    size_t y_offset = (self->height - image_height) / 2;

    XPutImage(
        self->display, self->window,
        XDefaultGC(self->display, 0),
        self->image,
        0, 0,
        x_offset, y_offset,
        self->width,
        self->height);
}

static void
canvas_window_receive(canvas_window_t *self) {
    Atom wmDelete = XInternAtom(self->display, "WM_DELETE_WINDOW", True);
    XSetWMProtocols(self->display, self->window, &wmDelete, 1);

    XEvent unknown_event;
    XNextEvent(self->display, &unknown_event);
    switch(unknown_event.type) {
    case ClientMessage: {
        XClientMessageEvent* event = (XClientMessageEvent *) &unknown_event;
        if ((Atom)event->data.l[0] == wmDelete) {
            self->is_open = false;
            XDestroyWindow(self->display, self->window);
        }
        return;
    }

    case Expose: {
        canvas_window_show_image(self);
        return;
    }

    case ConfigureNotify: {
        XConfigureEvent* event = (XConfigureEvent *) &unknown_event;
        canvas_window_resize(self, event->width, event->height);
        return;
    }

    case KeyPress: {
        if (self->on_key) {
            XKeyPressedEvent* event = (XKeyPressedEvent*) &unknown_event;
            int group = 0;
            int level = event->state & ShiftMask ? 1 : 0;
            KeySym keysym = XkbKeycodeToKeysym(self->display, event->keycode, group, level);
            const char *key_name = XKeysymToString(keysym);
            bool is_release = false;
            self->on_key(self, self->state, key_name, is_release);
        }

        return;
    }

    case KeyRelease: {
        if (self->on_key) {
            XKeyReleasedEvent* event = (XKeyReleasedEvent*) &unknown_event;
            int group = 0;
            int level = event->state & ShiftMask ? 1 : 0;
            KeySym keysym = XkbKeycodeToKeysym(self->display, event->keycode, group, level);
            const char *key_name = XKeysymToString(keysym);
            bool is_release = true;
            self->on_key(self, self->state, key_name, is_release);
        }

        return;
    }
    }
}

static void
canvas_window_show(canvas_window_t *self) {
    XMapWindow(self->display, self->window);
    XFlush(self->display);
}

static int
frame_timerfd(size_t n) {
    // n frame per second:
    size_t ns = 1000000000 / n;
    struct timespec timespec;
    timespec.tv_sec = 0;
    timespec.tv_nsec = ns;
    struct itimerspec interval_timespec;
    interval_timespec.it_value = timespec;
    interval_timespec.it_interval = timespec;

    int timerfd = timerfd_create(CLOCK_MONOTONIC, 0);
    timerfd_settime(timerfd, 0, &interval_timespec, NULL);

    return timerfd;
}

void
canvas_window_open(canvas_window_t *self) {
    canvas_window_init(self);
    canvas_window_show(self);

    size_t nfds = 2;
    struct pollfd fds[nfds];
    fds[0].fd = XConnectionNumber(self->display);
    fds[1].fd = frame_timerfd(60);
    fds[0].events = fds[1].events = POLLIN;

    self->is_open = true;
    while (self->is_open) {
        if (poll(fds, nfds, 1000) <= 0) continue;

        while (XPending(self->display)) {
            canvas_window_receive(self);
        }

        if ((fds[1].revents & POLLIN) != 0) {
            uint64_t expirations;
            read(fds[1].fd, &expirations, sizeof(uint64_t));
            canvas_window_update_image(self);
            canvas_window_show_image(self);
            if (self->on_frame) {
                self->on_frame(self, self->state, expirations);
            }
        }
    }
}
