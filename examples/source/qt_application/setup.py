# Copyright (c) 2024 IHU Liryc, Université de Bordeaux, Inria.
# License: BSD-3-Clause


from distutils.core import setup


setup_options = {
    'name': '@PROJECT_NAME@',
    'version': '@PROJECT_VERSION@',
    'packages': ['pyncpp_examples.qt@PYNCPP_QT_VERSION@']
}


setup(**setup_options)
