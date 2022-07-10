# meson subprojects purge works wonders :)

project('MemPenguin', 'cpp')

incdir = include_directories('.', './include')

subproject('LinuxOverlay')
LinuxOverlay = dependency('linuxoverlay')

imGuiInc = subproject('ImGUI').get_variable('imguiInc')
glfwInc = subproject('glfw').get_variable('glfwIncs')

files = files(
    'Main.cpp',
    'Process.cpp',
    'Interface.cpp',
    'System.cpp'
)

executable('MemPenguin', files, include_directories : [incdir, imGuiInc, glfwInc], dependencies : [LinuxOverlay] )
