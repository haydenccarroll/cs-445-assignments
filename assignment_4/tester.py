import os
import shutil
import sys


class bcolors:
    HEADER = '\033[95m'
    OKBLUE = '\033[94m'
    OKCYAN = '\033[96m'
    OKGREEN = '\033[92m'
    WARNING = '\033[93m'
    FAIL = '\033[91m'
    ENDC = '\033[0m'
    BOLD = '\033[1m'
    UNDERLINE = '\033[4m'


def execute(dir, cmd):
    assert os.path.exists(dir) and os.path.isdir(dir)
    cwd = os.getcwd()
    os.chdir(dir)
    os.system(cmd)
    os.chdir(cwd)

def sortA3(fileName):
    hasSplit = False
    firstPart = ""
    secondPart = []
    with open(fileName, "r") as file:
        for line in file:
            if line.startswith("ERROR") or line.startswith("WARNING") or line.startswith("Number of "):
                hasSplit = True
            if hasSplit:
                secondPart.append(line)
            else:
                firstPart += line
    
    secondPart.sort()
    secondPart = ''.join(secondPart)
    with open(fileName, "w") as file:
        file.write(firstPart + secondPart)


def make(src_dir):
    execute(src_dir, 'make')


def make_clean(src_dir):
    execute(src_dir, 'make clean')


def compile(src_dir, exe):
    make(src_dir)
    if not os.path.isfile(os.path.join(src_dir, exe)):
        raise Exception('Compilation failed!')
    return os.path.join(src_dir, exe)


def diff(path1, path2):
    are_different = True

    file1 = open(path1, 'r')
    file2 = open(path2, 'r')
    if file1.read() == file2.read():
        are_different = False

    file1.close()
    file2.close()
    return are_different


def test(src_dir, test_dir, flags='', show_diff=True):
    assert os.path.exists(src_dir) and os.path.isdir(src_dir)
    assert os.path.exists(test_dir) and os.path.isdir(test_dir)

    make_clean(src_dir)
    compiler_path = compile(src_dir, 'c-')

    tmp_dir = os.path.join(src_dir, 'tmp')
    if os.path.exists(tmp_dir):
        delete = input(f'{bcolors.WARNING}A \'tmp\' directory already exists. Would you like to delete it (Y/n)? {bcolors.ENDC}').lower()
        if delete == 'y':
            shutil.rmtree(tmp_dir)
    os.mkdir(tmp_dir)

    expected_dir = os.path.join(tmp_dir, 'expected')
    os.mkdir(expected_dir)

    actual_dir = os.path.join(tmp_dir, 'actual')
    os.mkdir(actual_dir)

    tests = [f[:-4] for f in os.listdir(test_dir) if f.endswith('.out') and os.path.isfile(os.path.join(test_dir, f))]
    passed = 0
    for i, test in enumerate(tests):
        print(f'{bcolors.OKCYAN}Running test \'{test}\' {i + 1} / {len(tests)}...{bcolors.ENDC}', end='')

        test_src = os.path.join(test_dir, test + '.c-')
        tmp_out = os.path.join(tmp_dir, 'tmp.out')
        os.system(f'{compiler_path} {flags} {test_src} > {tmp_out}')

        test_out = os.path.join(test_dir, test + '.out')
        expected_out = os.path.join(expected_dir, test + '.out')
        actual_out = os.path.join(actual_dir, test + '.out')
        os.system(f'cat {test_out} > {expected_out}')
        os.system(f'cat {tmp_out} > {actual_out}')
        sortA3(expected_out)
        sortA3(actual_out)
        os.remove(tmp_out)

        if diff(expected_out, actual_out):
            print(f'{bcolors.FAIL}[ Failed! ]{bcolors.ENDC}')
            if show_diff:
                os.system(f'diff {expected_out} {actual_out}')
        else:
            passed += 1
            print(f'{bcolors.OKGREEN}[ Passed! ]{bcolors.ENDC}')

    make_clean(src_dir)

    print('===========================================')
    print(f'Passed {passed}/{len(tests)} tests')
    print('===========================================')

    delete = input(f'{bcolors.OKCYAN}Would you like to delete the \'tmp\' directory (Y/n)? {bcolors.ENDC}').lower()
    if delete == 'y':
        shutil.rmtree(tmp_dir)


if __name__ == '__main__':
    if len(sys.argv) < 3:
        print('Usage: src_dir test_dir -flag -flag')
    elif len(sys.argv) == 3:
        test(sys.argv[1], sys.argv[2])
    elif len(sys.argv) > 3:
        test(sys.argv[1], sys.argv[2], ' '.join(sys.argv[3:]))

