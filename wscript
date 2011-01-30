#!/usr/bin/env python
# encoding: utf-8
# Alexandre Gauthier, 2011

import sys

APPNAME = "FinalHopes"
VERSION = "0.1.0"

top = '.'
out = 'build'

def options(opt):
    opt.load('compiler_cxx')
    opt.add_option('--releaseflags', action="store_true", default=False,
        help='Enable release debug flags.')
    opt.add_option('--with-pdcurses-dir', action="store", default=False,
        help="Use pdcurses and specify where it is unpacked." \
        "(Mostly useful for Win32 and cross-compilation)")

def configure(conf):
    conf.load('compiler_cxx')

    if sys.platform == 'darwin':
        print "Configuring for Mac OS X"
        conf.load('c_osx')
        # Explicitely load the darwin gcc modifier
        # At the time of writing there seems to be some bug
        # that causes linker flags to contains erroneous settings
        # such as -Bstatic, which causes linking to fail.
        from waflib.Tools import gcc
        gcc.gcc_modifier_darwin(conf)
    else:
        conf.load('c_config')

    # Build type (debug/release)
    if conf.options.releaseflags:
        p = "RELEASE"
        conf.env.release = conf.options.releaseflags
        conf.find_program('strip', var='STRIP')
    else:
        p = "DEBUG"

    print(' '.join(["Configuring for", p]))

    # Use extra pdcurses directory? (mostly useful on windows
    # and for cross compiling.
    if conf.options.with_pdcurses_dir:
        conf.env.append_unique('INCLUDES', conf.options.with_pdcurses_dir)
        conf.env.append_unique('LIBPATH', conf.options.with_pdcurses_dir)

    # Check for 'curses.h', but do not link just yet.
    # We just wish to know if curses is available at all.
    conf.check(features="cxx", header_name='curses.h', mandatory=True)

    # Try to link against pdcurses if specified.
    # If not, in normal scenarios, link against ncurses.
    # If all else fails, try grandpa curses.
    if conf.options.with_pdcurses_dir:
        conf.check_cxx(lib='pdcurses', uselib_store="CURSES")
        # pdcurses has 'panel.h' but it's all in the same library.
        # i.e. not 'panel', so no need to pollute linker flags with it.
        conf.check_cxx(header_name='panel.h',
            msg="Checking if pdcurses provides 'panel.h'")
    else:
        try:
            conf.check_cxx(lib='ncurses', uselib_store="CURSES")
        except conf.errors.ConfigurationError:
            conf.check_cxx(lib='curses', uselib_store="CURSES")

        # Try panel lib, from curses. It's not always present.
        # Again, pdcurses does not provide it separately.
        conf.check_cxx(lib="panel", uselib_store="CURSES",
            msg="Checking if your curses supports 'panel'")

    # Common Compiler Flags
    conf.env.append_unique('CXXFLAGS', ['-O2', '-Wall'])

    # Set additional flags for debug
    if not conf.options.releaseflags:
        conf.env.append_unique('CXXFLAGS', ['-g'])

def build(bld):
    bld.program(
        features = 'cxx cxxprogram',
        target = 'this',
        source = 'stats.cpp login.cpp window.cpp screen.cpp main.cpp socket.cpp socketserver.cpp packets.cpp',
        use='CURSES',
    )

    if bld.env.release:
        bld(rule = '${STRIP} ${SRC}', source = 'this')




