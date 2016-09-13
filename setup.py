#-*- coding: utf-8 -*-

from sys import version
if not version[0] == '3':
    raise RuntimeError('this is for Python3 only!')

from distutils.core import setup, Extension

unrtf_c_sources = list(map(lambda f: 'unrtf_ext/src/{}'.format(f), [
   'attr.c',
   'convert.c',
   'error.c',
   'hash.c',
   'malloc.c',
   'my_iconv.c',
   'output.c',
   'parse.c',
   'path.c',
   'unicode.c',
   'user.c',
   'util.c',
   'word.c',
   'lib.cpp',
   'pylib.cpp',
]))

unrtf_conf_files = list(map(lambda f: 'unrtf_ext/config/{}'.format(f), [
    'html.conf',
    'latex.conf',
    'rtf.conf',
    'SYMBOL.charmap',
    'text.conf',
    'troff_mm.conf',
    'vt.conf'
]))


unrtf_module = Extension('_unrtf',
                    define_macros = [('PACKAGE_VERSION', '"1"'),
                                     ('PKGDATADIR', '"/usr/local/share/python-unrtf/"')],
                    sources = unrtf_c_sources)

setup (name = 'unrtf',
       version = '0.1.0',
       description = 'GNU unrtf python bindings',
       author = 'Sławomir Zborowski',
       author_email = 'slawomir.zborowski@nokia.com',
       url = 'https://github.com/szborows/python-unrtf',
       license = 'GNU General Public License v3 (GPLv3)',
       py_modules=['unrtf'],
       ext_modules = [unrtf_module],
       data_files = [('/usr/local/share/python-unrtf/', unrtf_conf_files)],
       keywords = 'unrtf rtf',
       classifiers = [
           'Development Status :: 3 - Alpha',
           'Environment :: Console',
           'Intended Audience :: Developers',
           'License :: OSI Approved :: GNU General Public License v3 (GPLv3)',
           'Operating System :: POSIX',
           'Programming Language :: C',
           'Programming Language :: Python :: 3 :: Only',
           'Programming Language :: Python :: 3.5',
           'Topic :: Utilities'
       ])
