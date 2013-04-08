from distutils.core import setup, Extension

module = Extension('explode', sources = ['explodemodule.c'])
setup(name = 'Explode', version = '1.0', ext_modules = [module])

