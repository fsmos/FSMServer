#!/usr/bin/env python3

from distutils.core import setup, Extension

setup(
	name = "fsmgetmn111",
	version = "1.0",
	ext_modules = [Extension("fsmgetmn111", ["bind.c", "libfsmgetmn111.c"],libraries = ['fsmmn111'])]
	);
