'''
This is a test module.
'''

from typing import List
import glob

def search_fish_files() -> List[str]:
    '''
    Search files with extension 'fish' in the test directory.
    '''
    return glob.glob('test/*.fish')

if __name__ == '__main__':
    print(search_fish_files())
