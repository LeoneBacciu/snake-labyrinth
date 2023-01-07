#include <locale.h>
#include <signal.h>
#include "render/render.h"
#include "ai/random.h"


void signal_handler() {
    render_destroy();
    exit(EXIT_SUCCESS);
}

/*!
 * @mainpage
 * @b Welcome to the Snake Labyrinth documentation!
 *
 * To run with AI, specify one of the flags:
 *  - `--fast`: for fast AI
 *  - `--strong`: for strong AI
 *  - `--experimental`: for experimental AI
 *
 * After you can optionally specify the path for the maze file.
 * If not specified the maze will be loaded from stdin.
 *
 * Command:
 *  - `snake_labyrinth [AI FLAG] [MAZE DIRECTORY]`
 *
 * Examples:
 *  - `./snake_labyrinth --strong`
 *  - `./snake_labyrinth --fast maze.txt`
 *  - `./snake_labyrinth maze.txt`
 *  - `./snake_labyrinth`
 *
 *
 * To build, with CMake:
 *  - `cmake [SOURCE DIRECTORY] -B [BUILD DIRECTORY]`
 *  - `cmake --build [BUILD DIRECTORY] --target snake_labyrinth`
 *
 * To generate the documentation:
 *  - `doxygen [Doxyfile PATH]`
 *
 * For the full report: @ref md_REPORT
 *
 * @authors Leone Bacciu (894862)
 * @authors Marco Diotto (895937)
 */
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
