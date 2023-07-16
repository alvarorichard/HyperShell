-- xmake.lua
add_rules("mode.debug", "mode.release")

target("hs")
    set_kind("binary")
    add_files("main.c")
    set_toolchains("llvm")

after_clean(function ()
    os.exec("rm -rf .xmake")
    os.exec("rm -rf build")
end)
