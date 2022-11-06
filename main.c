#include <signal.h>
#include "frontend/render.h"

void signal_handler() {
    render_destroy();
    exit(EXIT_SUCCESS);
}

int main(int argc, char **argv) {
    signal(SIGINT, signal_handler);
    render_init();
    render_loop(argc, argv);
    render_destroy();
    return EXIT_SUCCESS;
}
