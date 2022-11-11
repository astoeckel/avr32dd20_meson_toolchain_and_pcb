#   AVR32DD20 Toolchain
#   Copyright (C) 2022  Andreas Stöckel
#
#   This program is free software: you can redistribute it and/or modify
#   it under the terms of the GNU General Public License as published by
#   the Free Software Foundation, either version 3 of the License, or
#   (at your option) any later version.
#
#   This program is distributed in the hope that it will be useful,
#   but WITHOUT ANY WARRANTY; without even the implied warranty of
#   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#   GNU General Public License for more details.
#
#   You should have received a copy of the GNU General Public License
#   along with this program.  If not, see <https://www.gnu.org/licenses/>.

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
        '-j', '.text', '-j', '.data', '-O', 'ihex',
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
