#include <signal.h>
#include "frontend/render.h"

void signal_handler() {
    render_destroy();
    exit(0);
}

int main(int argc, char **argv) {
#ifdef _WIN32

#else
    signal(SIGINT, signal_handler);
#endif
    render_init();
    render_loop(argc, argv);
    render_destroy();
    return 0;
}
