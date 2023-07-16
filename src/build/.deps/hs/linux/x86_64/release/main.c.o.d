{
    values = {
        "/usr/bin/clang",
        {
            "-Qunused-arguments",
            "-m64",
            "-fvisibility=hidden",
            "-O3",
            "-DNDEBUG"
        }
    },
    files = {
        "main.c"
    },
    depfiles_gcc = "build/.objs/hs/linux/x86_64/release/__cpp_main.c.c: main.c\
"
}