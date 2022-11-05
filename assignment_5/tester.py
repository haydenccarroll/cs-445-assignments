import os
import shutil
import sys
import time


class Test:

    def __init__(self, src_dir, tst_dir, tmp_dir, name):
        self._src_dir = src_dir
        self._tst_dir = tst_dir
        self._tmp_dir = tmp_dir
        self._name = name
        self._diff_count = 0

    def __repr__(self):
        return f'Test(dir=\'{self._tst_dir}\', name=\'{self._name}\')'

    def get_dir(self):
        return self._tst_dir

    def get_name(self):
        return self._name

    def get_diff_count(self):
        return self._diff_count

    def run(self, compiler, flags='', show_diff=False, sort_outs=False, no_print_tree=False):
        passed = True

        src = os.path.join(self._tst_dir, self._name + '.c-')
        actual, expected, diff = self.mktmp()

        expected_out = os.path.join(expected, self._name + '.out')
        out = os.path.join(self._tst_dir, self._name + '.out')
        tmp_out = os.path.join(self._tmp_dir, 'tmp.out')
        actual_out = os.path.join(actual, self._name + '.out')

        os.system(f'cp {out} {expected_out}')
        os.system(f'{compiler} {src} {flags} > {tmp_out}')
        os.system(f'cp {tmp_out} {actual_out}')


        if no_print_tree:
            Test.getRidOfTree(expected_out)
            Test.getRidOfTree(actual_out)

        if sort_outs:
            os.system(f'sort -o {expected_out} {expected_out}')
            os.system(f'sort -o {actual_out} {actual_out}')

        if Test.diff(expected_out, actual_out):
            passed = False

            diff_out = os.path.join(diff, self._name + '.diff')
            os.system(f'diff {expected_out} {actual_out} > {diff_out}')

            with open(diff_out, 'r') as file:
                self._diff_count += len(file.readlines())

            if show_diff:
                os.system(f'diff {expected_out} {actual_out}')

        if sort_outs:
            os.remove(tmp_out)

        return passed

    def mktmp(self):
        actual = os.path.join(self._tmp_dir, 'actual')
        expected = os.path.join(self._tmp_dir, 'expected')
        diff = os.path.join(self._tmp_dir, 'diff')

        if not os.path.exists(self._tmp_dir):
            os.mkdir(self._tmp_dir)
            os.mkdir(actual)
            os.mkdir(expected)
            os.mkdir(diff)

        return actual, expected, diff

    def rmtmp(self):
        if os.path.exists(self._tmp_dir, ):
            shutil.rmtree(self._tmp_dir, )

    @classmethod
    def diff(cls, path1, path2):
        are_different = True

        file1 = open(path1, 'rb')
        file2 = open(path2, 'rb')
        if file1.read() == file2.read():
            are_different = False

        file1.close()
        file2.close()
        return are_different

    @classmethod
    def getRidOfTree(cls, path):
        arr = []
        with open(path, "r") as file:
            for line in file:
                if line.startswith("ERROR") or line.startswith("WARNING") or line.startswith("Number of "):
                    arr.append(line)
        with open(path, "w") as file:
            file.write(''.join(arr))

    @classmethod
    def get_tests(cls, src_dir, tst_dir, tmp_dir):
        return [Test(src_dir, tst_dir, tmp_dir, f[:-4]) for f in os.listdir(tst_dir) if f.endswith('.out')]


class Make:

    def __init__(self, dir):
        self._tst_dir = dir

    def __repr__(self):
        return f'Make(dir=\'{self._tst_dir}\')'

    def get_dir(self):
        return self._tst_dir

    def make(self):
        self._execute('make')

    def clean(self):
        self._execute('make clean')

    def tar(self):
        self._execute('make tar')

    def _execute(self, cmd):
        cwd = os.getcwd()
        os.chdir(self._tst_dir)
        os.system(cmd)
        os.chdir(cwd)


class Emit:
    HEADER = '\033[95m'
    SUCCESS = '\033[92m'
    WARN = '\033[93m'
    ERROR = '\033[91m'
    ENDC = '\033[0m'
    BOLD = '\033[1m'
    UNDERLINE = '\033[4m'

    @classmethod
    def br(cls, length, endc='\n'):
        print('=' * length, end=endc)

    @classmethod
    def bold(cls, msg, endc='\n'):
        print(f'{Emit.BOLD}{msg}{Emit.ENDC}', end=endc)

    @classmethod
    def underline(cls, msg, endc='\n'):
        print(f'{Emit.UNDERLINE}{msg}{Emit.ENDC}', endc)

    @classmethod
    def success(cls, msg, endc='\n'):
        Emit.bold(f'{Emit.SUCCESS}{msg}{Emit.ENDC}', endc)

    @classmethod
    def warn(cls, msg, endc='\n'):
        Emit.bold(f'{Emit.WARN}{msg}{Emit.ENDC}', endc)

    @classmethod
    def error(cls, msg, endc='\n'):
        Emit.bold(f'{Emit.ERROR}{msg}{Emit.ENDC}', endc)


if __name__ == '__main__':
    diff_flag = False
    one_flag = False
    sort_flag = False
    no_print_tree_flag = False
    removetmp_flag = False
    src_dir = ''
    tst_dir = ''
    flags = ''

    argc = len(sys.argv)
    if argc < 4:
        print('Usage: src_dir test_dir tmp_dir -flag -flag')
        print('Test Flags:')
        print('--diff \t Shows test diffs in the terminal.')
        print('--noPrintTree \t Doesnt print the tree in both expected and actual.')
        print('--one \t Only run the first test.')
        print('--removetmp \t Prompt for removal of \'tmp\' directory.')
        print('--sort \t Sort the output files before diff.')
        print('Compiler Flags:')
        print('-d: \t Provides debugging info.')
        print('-p: \t Displays the AST.')
        print('-h \t Displays a help menu')
        print('For this project:')
        print('$ python3 test.py hw1/ hw1/test')
        print('$ python3 test.py hw2/ hw2/test -p')
    elif argc == 4:
        src_dir = sys.argv[1]
        tst_dir = sys.argv[2]
        tmp_dir = sys.argv[3]
        compiler = os.path.join(src_dir, 'c-')
    elif argc > 4:
        src_dir = sys.argv[1]
        tst_dir = sys.argv[2]
        tmp_dir = sys.argv[3]
        compiler = os.path.join(src_dir, 'c-')

        flag_list = sys.argv[4:]
        if '--diff' in flag_list:
            diff_flag = True
            flag_list.remove('--diff')

        if '--one' in flag_list:
            one_flag = True
            flag_list.remove('--one')

        if '--sort' in flag_list:
            sort_flag = True
            flag_list.remove('--sort')

        if '--noPrintTree' in flag_list:
            no_print_tree_flag = True
            flag_list.remove('--noPrintTree')

        if '--removetmp' in flag_list:
            removetmp_flag = True
            flag_list.remove('--removetmp')

        flags = ' '.join(flag_list)

    make = Make(src_dir)
    if os.path.exists(compiler):
        make.clean()

    make.make()
    if not os.path.exists(compiler):
        raise Exception('Compilation failed')

    passed = 0
    tests = Test.get_tests(src_dir, tst_dir, tmp_dir)
    tests[0].rmtmp()

    if one_flag:
        tests = [tests[0]]

    diff_count = 0
    for i, test in enumerate(tests):
        print(f'Running {test} {i + 1}/{len(tests)}...', end='')
        if test.run(compiler, flags, diff_flag, sort_flag, no_print_tree_flag):
            passed += 1
            Emit.success(f'[ PASSED ]')
        else:
            Emit.error(f'[ FAILED ]')

        diff_count += test.get_diff_count()

    if passed == len(tests):
        Emit.success('=' * 30)
        Emit.success(f'Passed {passed}/{len(tests)} tests with diff {diff_count}')
        Emit.success('=' * 30)
    else:
        Emit.error('=' * 30)
        Emit.error(f'Passed: {passed}/{len(tests)} tests with diff {diff_count}')
        Emit.error('=' * 30)

    make.clean()

    if removetmp_flag:
        Emit.warn('Remove the \'tmp\' directory (y/n)? ', endc='')
        remove_tmp = input()
        if remove_tmp == 'y':
            tests[0].rmtmp()

    with open('test.history', 'a') as history:
        cmd = ' '.join(sys.argv)
        history.write(f'{time.time()},"python3 {cmd}",{passed},{len(tests)},{diff_count}\n')
