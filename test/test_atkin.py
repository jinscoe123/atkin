#
# Copyright (c) 2018 Joshua Inscoe
# Use of this source code is governed by the MIT License.
#
# test_atkin.py
#



from os.path import dirname, realpath

import hashlib
import os
import subprocess



ATKIN_EXENAME = 'atkin'

ATKIN_EXEPATH = os.path.join(dirname(dirname(realpath(__file__))), ATKIN_EXENAME)

assert os.access(ATKIN_EXEPATH, os.X_OK)


TEST_ATKIN_LIMIT_MAX = 1000000

_CURRENT_LIMIT = 1



def _atkin_md5(exepath, limit):
    '''
    Run the 'atkin' command-line program located at ``exepath`` with a limit of ``limit``, and
    return the MD5 checksum of its output.

    Arguments:
        exepath    the path to the 'atkin' executable
        limit      the limit up to which to generate prime numbers
    '''

    try:
        atkin = subprocess.run(
            [ exepath, str(limit) ], stdout=subprocess.PIPE, stderr=subprocess.PIPE, check=True
            )
    except subprocess.CalledProcessError:
        raise
    except OSError:
        raise

    hashctx = hashlib.md5(atkin.stdout.strip(b'\n') + b'\n')
    hashval = hashctx.hexdigest()

    return hashval


def _atkin_test(limit, expected):
    '''
    A decorator for test functions for testing the 'atkin' command-line program.

    This decorator returns a function that runs the program with the specified limit in a child
    process, computes the MD5 checksum of its output, and compares the checksum to a specified
    expected value.

    Arguments:
         limit       the limit to pass to the program
         expected    the expected MD5 checksum of the program output
    '''

    def _decorate(f):
        def _test_atkin():
            try:
                hashval = _atkin_md5(ATKIN_EXEPATH, limit)
            except Exception:
                raise

            assert hashval == expected

            return

        _test_atkin.__name__ = f.__name__
        _test_atkin.__dict__ = f.__dict__
        _test_atkin.__doc__ = f.__doc__

        return _test_atkin

    return _decorate



if TEST_ATKIN_LIMIT_MAX >= _CURRENT_LIMIT:
    @_atkin_test(_CURRENT_LIMIT, '68b329da9893e34099c7d8ad5cb9c940')
    def test_atkin_1():
        '''
        Test 'atkin' with a limit of 1.
        '''


_CURRENT_LIMIT *= 10

if TEST_ATKIN_LIMIT_MAX >= _CURRENT_LIMIT:
    @_atkin_test(_CURRENT_LIMIT, '72a5b709719cdb8cc8162fee2fb47fae')
    def test_atkin_10():
        '''
        Test 'atkin' with a limit of 10.
        '''


_CURRENT_LIMIT *= 10

if TEST_ATKIN_LIMIT_MAX >= _CURRENT_LIMIT:
    @_atkin_test(_CURRENT_LIMIT, '45d886e08500b82881519d5cf5cbe1d6')
    def test_atkin_100():
        '''
        Test 'atkin' with a limit of 100.
        '''


_CURRENT_LIMIT *= 10

if TEST_ATKIN_LIMIT_MAX >= _CURRENT_LIMIT:
    @_atkin_test(_CURRENT_LIMIT, '2d2382f376350089fd94503d7da478db')
    def test_atkin_1000():
        '''
        Test 'atkin' with a limit of 1,000.
        '''


_CURRENT_LIMIT *= 10

if TEST_ATKIN_LIMIT_MAX >= _CURRENT_LIMIT:
    @_atkin_test(_CURRENT_LIMIT, 'c37d039ddada44d3976ed948c3d0ef21')
    def test_atkin_10000():
        '''
        Test 'atkin' with a limit of 10,000.
        '''


_CURRENT_LIMIT *= 10

if TEST_ATKIN_LIMIT_MAX >= _CURRENT_LIMIT:
    @_atkin_test(_CURRENT_LIMIT, 'ba89921a4ba02bb51ee28d66dbfc3451')
    def test_atkin_100000():
        '''
        Test 'atkin' with a limit of 100,000.
        '''


_CURRENT_LIMIT *= 10

if TEST_ATKIN_LIMIT_MAX >= _CURRENT_LIMIT:
    @_atkin_test(_CURRENT_LIMIT, 'c13929ee9d2aea8f83aa076236079e94')
    def test_atkin_1000000():
        '''
        Test 'atkin' with a limit of 1,000,000.
        '''


_CURRENT_LIMIT *= 10

if TEST_ATKIN_LIMIT_MAX >= _CURRENT_LIMIT:
    @_atkin_test(_CURRENT_LIMIT, '60e34d268bad671a5f299e1ecc988ff6')
    def test_atkin_10000000():
        '''
        Test 'atkin' with a limit of 10,000,000.
        '''


_CURRENT_LIMIT *= 10

if TEST_ATKIN_LIMIT_MAX >= _CURRENT_LIMIT:
    @_atkin_test(_CURRENT_LIMIT, '4e2b0027288a27e9c99699364877c9db')
    def test_atkin_100000000():
        '''
        Test 'atkin' with a limit of 100,000,000.
        '''


_CURRENT_LIMIT *= 10

if TEST_ATKIN_LIMIT_MAX >= _CURRENT_LIMIT:
    @_atkin_test(_CURRENT_LIMIT, '92c178cc5bb85e06366551c0ae7e18f6')
    def test_atkin_1000000000():
        '''
        Test 'atkin' with a limit of 1,000,000,000.
        '''


_CURRENT_LIMIT *= 10

if TEST_ATKIN_LIMIT_MAX >= _CURRENT_LIMIT:
    @_atkin_test(_CURRENT_LIMIT, '95ded65c9ddca18e1df966ba2a2b373a')
    def test_atkin_10000000000():
        '''
        Test 'atkin' with a limit of 10,000,000,000.
        '''


_CURRENT_LIMIT *= 10

if TEST_ATKIN_LIMIT_MAX >= _CURRENT_LIMIT:
    @_atkin_test(_CURRENT_LIMIT, '9d8a8c2d7221497843ca289e6f463bfd')
    def test_atkin_100000000000():
        '''
        Test 'atkin' with a limit of 100,000,000,000.
        '''


_CURRENT_LIMIT *= 10

if TEST_ATKIN_LIMIT_MAX >= _CURRENT_LIMIT:
    @_atkin_test(_CURRENT_LIMIT, 'c899bf5d0ccef05787ac969afd6606ff')
    def test_atkin_1000000000000():
        '''
        Test 'atkin' with a limit of 1,000,000,000,000.
        '''
