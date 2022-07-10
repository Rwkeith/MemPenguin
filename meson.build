project('MemPenguin', 'cpp')

incdir = include_directories('.', './include') #'./subprojects/LinuxOverlay/include/', './subprojects/ImGUI', './subprojects/ImGUI/backends')


LinuxOverlayLib = subproject('LinuxOverlay').get_variable('LinuxOverlayDep')

ImGUIinc = subproject('ImGUI').get_variable('imguiInc')
glfwInc = subproject('glfw').get_variable('glfwIncs')

files = files(
    'Main.cpp',
    'Process.cpp',
    'Interface.cpp'
)

executable('MemPenguin', files, include_directories : [incdir, ImGUIinc, glfwInc], dependencies : [LinuxOverlayLib] )
