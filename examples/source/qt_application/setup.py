# Copyright (c) 2024 IHU Liryc, Université de Bordeaux, Inria.
# License: BSD-3-Clause


from distutils.core import setup


setup_options = {
    'name': '@PACKAGE_NAME@',
    'version': '@PROJECT_VERSION@',
    'packages': ['@PACKAGE_NAME@']
}


setup(**setup_options)
