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

def configure(conf):
    conf.load('compiler_cxx')

    # Let's spare our windows friends some pain by setting
    # then straight right away.
    if sys.platform == 'win32':
        print("Windows does not have (n)curses. Sorry.")
        print("If you really want to, cygwin's your best bet.")
        conf.fatal("Platform unsupported.")

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

    # Check for ncurses and panel
    conf.check_cxx(header_name='ncurses.h', lib=['ncurses'],
        uselib_store='NCURSES')
    conf.check_cxx(lib=['panel'], uselib_store='NCURSES',
        msg="Checking for ncurses-specific library: panel")

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
        use='NCURSES',
    )

    if bld.env.release:
        bld(rule = '${STRIP} ${SRC}', source = 'this')




