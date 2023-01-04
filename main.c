#include <locale.h>
#include <signal.h>
#include "render/render.h"
#include "ai/random.h"


void signal_handler() {
    render_destroy();
    exit(EXIT_SUCCESS);
}

int main(int argc, char **argv) {
    random_init();
    setlocale(LC_ALL, "");
    signal(SIGINT, signal_handler);

    int mode = 3;
    if (argc > 1 && !strcmp(argv[1], "--fast")) mode = 0;
    if (argc > 1 && !strcmp(argv[1], "--strong")) mode = 1;
    if (argc > 1 && !strcmp(argv[1], "--experimental")) mode = 2;

    maze_state_t *maze;
    if (argc > 1 && mode == 3) {
        maze = maze_load_file(argv[1]);
    } else if (argc > 2) {
        maze = maze_load_file(argv[2]);
    } else {
        maze = maze_load_stdin();
    }

    render_init();
    render_loop(maze, mode);
    render_destroy();
    return EXIT_SUCCESS;
}
