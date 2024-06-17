import inspect, os, sys, subprocess


def get_shiboken_generator_path():
    import shiboken@PYSIDE_VERSION@_generator as generator
    generator_dir = os.path.dirname(inspect.getfile(generator))
    return os.path.join(generator_dir, 'shiboken@PYSIDE_VERSION@')


def generate_shiboken_bindings(typesystem_file, headers=[]):
    generator = get_shiboken_generator_path()
    process = subprocess.run((generator, *headers, typesystem_file))


if __name__ == "__main__":
    typesystem_file = sys.argv[1]
    headers = sys.argv[2:]
    generate_shiboken_bindings(typesystem_file, headers)
