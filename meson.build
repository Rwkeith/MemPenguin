project('MemPenguin', 'cpp')

incdir = include_directories('.', './include')

LinuxOverlayLib = subproject('LinuxOverlay').get_variable('LinuxOverlayDep')

files = files(
    'Main.cpp',
    'Process.cpp'
)

executable('MemPenguin', files, include_directories : incdir, dependencies : [LinuxOverlayLib] )
