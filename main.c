#include "frontend/render.h"

int main(int argc, char **argv) {
    render_init();
    render_loop(argc, argv);
    render_destroy();
    return 0;
}