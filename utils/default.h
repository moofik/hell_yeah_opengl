#ifndef OPENGL1_DEFAULT_H
#define OPENGL1_DEFAULT_H

# define N_ARGS(args...) N_ARGS_HELPER1(args, 9, 8, 7, 6, 5, 4, 3, 2, 1)
# define N_ARGS_HELPER1(args...) N_ARGS_HELPER2(args)
# define N_ARGS_HELPER2(x1, x2, x3, x4, x5, x6, x7, x8, x9, n, x...) n

#endif //OPENGL1_DEFAULT_H
