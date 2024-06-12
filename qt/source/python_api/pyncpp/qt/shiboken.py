
def get_shiboken_generator_path():
    import shiboken@PYSIDE_VERSION@_generator as shiboken_generator
    return os.path.join(shiboken_generator.__path__, 'shiboken')


def generate_shiboken_bindings(typesystem_file, headers=[]):
    generator = get_shiboken_generator_path()
    subprocess.run(generator)
