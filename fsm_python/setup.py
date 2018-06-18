#!/usr/bin/env python3

from distutils.core import setup, Extension

setup(
	name = "fsmgetccklist",
	version = "1.0",
	ext_modules = [Extension("fsmgetccklist", ["bind.c", "libfsmgetccklist.c"],libraries = ['fsmcck'])]
	);
