'''
This is a test module.
'''

from typing import List
import glob
import subprocess

TEST_FISH_FILE_PATH = './test/fish_code'
RESULT_FILE_PATH = TEST_FISH_FILE_PATH + '/result'

def search_fish_files() -> List[str]:
    '''
    Search files with extension 'fish' in the test directory.
    '''
    return glob.glob(f'{TEST_FISH_FILE_PATH}/*.fish')

def file_path_to_name(file_path: str) -> str:
    '''
    Get the file name from the file path.
    '''
    return file_path.split('/')[-1]

def fish_file_name_to_input_file_name(fish_file_name: str) -> str:
    '''
    Get the input file name from the fish file name.
    '''
    return fish_file_name.replace('.fish', '_in.txt')

def fish_file_name_to_output_file_name(fish_file_name: str) -> str:
    '''
    Get the output file name from the fish file name.
    '''
    return fish_file_name.replace('.fish', '_out.txt')

def read_file_to_str(input_file_name: str) -> str:
    '''
    Read the file and return the content as a string.
    '''
    with open(input_file_name, 'r', encoding='utf-8') as f:
        return f.read()

def main() -> None:
    '''
    Main function.
    '''
    print('=' * 40)
    print('Now starting the test module.')
    print('Searching fish files...')
    fish_files = search_fish_files()
    print('fish file number:', len(fish_files))
    print('=' * 40)

    if len(fish_files) == 0:
        print('No fish files found in' + TEST_FISH_FILE_PATH)
        return

    test_num = len(fish_files)
    success_num = 0

    for fish_file in fish_files:
        file_name = file_path_to_name(fish_file)
        input_file_name = fish_file_name_to_input_file_name(file_name)
        try:
            input_str = read_file_to_str(f"{RESULT_FILE_PATH}/" + input_file_name)
        except FileNotFoundError:
            input_str = ''
        output_file_name = fish_file_name_to_output_file_name(file_name)
        output_str = read_file_to_str(f"{RESULT_FILE_PATH}/" + output_file_name)

        # run the fish code
        res = subprocess.run(['./build/fishc', fish_file, "-l", "10000", "-d"],
            input=input_str, check=True, capture_output=True, text=True)

        if res.stdout == output_str:
            success_num += 1
        else:
            print('Test failed:', file_name)

            print('Expected:')
            if output_str == '':
                print('[No output]')
            else:
                print(output_str)

            print('Actual:')
            if res.stdout == '':
                print('[No output]')
            else:
                print(res.stdout)

            print('-' * 40)

    print('Test finished.')
    print(f'Test number: {test_num}')
    print(f'Success number: {success_num}')
    print(f'Failure number: {test_num - success_num}')
    if success_num == test_num:
        print('All tests passed!')
    else:
        print('Some tests failed.')
    print('=' * 40)

if __name__ == '__main__':
    main()
