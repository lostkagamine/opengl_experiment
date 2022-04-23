project('GLTest', 'cpp',
    version: '0.1',
    default_options: [
        'warning_level=3',
        'cpp_std=c++latest'
    ])

sdl2 = dependency('sdl2')
glew = dependency('glew')
glm = dependency('glm')
fmt = dependency('fmt')

exe = executable('gltest',
    'gltest.cpp',
    'window.cpp',
    'window.h',
    'other.cpp',
    'other.h',
    'shader.cpp',
    'shader.h',
    'program.cpp',
    'program.h',
    'buffer.h',
    'vector.h',
    'vertex.h',
    'vao.h',
    install: true,
    dependencies: [sdl2, glew, glm, fmt])

test('basic', exe)
