#include <signal.h>
#include "frontend/render.h"

void signal_handler()
{
    render_destroy();
    exit(0);
}

int main(int argc, char **argv) {
    signal(SIGINT, signal_handler);
    render_init();
    render_loop(argc, argv);
    render_destroy();
    return 0;
}