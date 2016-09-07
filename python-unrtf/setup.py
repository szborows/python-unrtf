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
   'lib.c',
   'pylib.c',
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
       description = 'unrtf python bindings',
       author = 'Sławomir Zborowski',
       author_email = 'slawomir.zborowski@nokia.com',
       py_modules=['unrtf'],
       ext_modules = [unrtf_module],
       data_files=[('/usr/local/share/python-unrtf/', unrtf_conf_files)])
