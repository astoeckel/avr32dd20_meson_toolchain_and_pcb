#    Copyright (c) 2022 Andreas Stöckel
#
#    Permission is hereby granted, free of charge, to any person obtaining a copy
#    of this software and associated documentation files (the "Software"), to deal
#    in the Software without restriction, including without limitation the rights
#    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
#    copies of the Software, and to permit persons to whom the Software is
#    furnished to do so, subject to the following conditions:
#
#    The above copyright notice and this permission notice shall be included in all
#    copies or substantial portions of the Software.
#
#    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
#    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
#    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
#    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
#    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
#    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
#    SOFTWARE.

project('avr32dd20_toolchain', ['c', 'cpp'],
    default_options: ['cpp_std=c++14'])

inc_local = include_directories('src')

exe_main_avr32dd20 = executable(
    'main_avr32dd20',
    sources: [
        'src/main.c'
    ],
    include_directories: [
        inc_local,
    ]
)

exe_avr_objcopy = find_program('avr-objcopy')
exe_avrdude = find_program('avrdude', required: false)

hex_main_avr32dd20 = custom_target(
    'main_avr32dd20.hex',
    input: exe_main_avr32dd20,
    output: 'main_avr32dd20.hex',
    command: [
        exe_avr_objcopy,
        '-j', '.text', '-j', '.data', '-j', '.rodata', '-O', 'ihex',
        '@INPUT@', '@OUTPUT@',
    ],
)

if exe_avrdude.found()
    run_target(
        'flash',
        command: [
            exe_avrdude,
            '-C', join_paths(meson.current_source_dir(), 'avrdude.conf'),
            '-c', 'jtag2updi',
            '-P', '/dev/ttyACM0',
            '-p', 'avr32dd20',
            '-U', 'flash:w:@0@:i'.format(hex_main_avr32dd20.full_path())
        ],
        depends: hex_main_avr32dd20,
    )
endif
