# meson subprojects purge works wonders :)

project('MemPenguin', 'cpp')

incdir = include_directories('.', './include')

subproject('LinuxOverlay')
LinuxOverlay = dependency('linuxoverlay')

ImGUIinc = subproject('ImGUI').get_variable('imguiInc')
glfwInc = subproject('glfw').get_variable('glfwIncs')

files = files(
    'Main.cpp',
    'Process.cpp',
    'Interface.cpp'
)

executable('MemPenguin', files, include_directories : [incdir, ImGUIinc, glfwInc], dependencies : [LinuxOverlay] )
