import os
import sys


def make(dir, cmd):
    os.chdir(dir)
    os.system(cmd)
    os.chdir('../..')


def test(dir):
    if not os.path.exists(dir):
        print(f'The specified path \'{dir}\' does not exist!')
    if not os.path.isdir(dir):
        print(f'The specified path \'{dir}\' is not a dir!')

    test_dir = os.path.join(dir, 'test')
    tests = [f for f in os.listdir(test_dir) if os.path.isfile(os.path.join(test_dir, f))
             and f.endswith('.c-')]

    make(os.path.join(dir, 'src'), 'make')

    compiler_path = os.path.join(os.path.join(dir, 'src'), 'c-')
    actual_out_path = os.path.join("", 'test.out')
    for i, test in enumerate(tests):
        print(f'Running test suite \'{test[:-3]}\' {i + 1} / {len(tests)}...', end='')

        test_path = os.path.join(test_dir, test)
        expected_out_path = os.path.join(test_path[:-3] + '.out')

        os.system(f'{compiler_path} -p {test_path} > {actual_out_path}')
        expected = open(expected_out_path, 'r')
        actual = open(actual_out_path, 'r')
        
        if expected.read() == actual.read():
            print('Passed!')
        else:
            print('Failed!')
            os.system(f'diff {expected_out_path} {actual_out_path}')
            expected.close()
            actual.close()
            break

        expected.close()
        actual.close()

if __name__ == '__main__':
    if len(sys.argv) != 2:
        print('Please specify a homework directory.')

    test(sys.argv[1])