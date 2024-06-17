import importlib, inspect


_class2module_map = None


def _get_class_to_module_map():
    global _class2module_map

    if _class2module_map is None:
        import PySide@PYSIDE_VERSION@
        _class2module_map = dict()

        for module_name in PySide@PYSIDE_VERSION@._find_all_qt_modules():
            module = importlib.import_module(f'PySide@PYSIDE_VERSION@.{module_name}')
            _class2module_map.update({x: module_name for x, _ in inspect.getmembers(module, inspect.isclass)})

    return _class2module_map


def get_class_module(class_name):
    module_name = _get_class_to_module_map()[class_name]
    return importlib.import_module(f'PySide@PYSIDE_VERSION@.{module_name}')


def get_class(class_name):
    return getattr(get_class_module(class_name), class_name)
