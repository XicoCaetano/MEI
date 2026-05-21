import pytest
from solution import string_xor


def test_basic_example():
    assert string_xor('010', '110') == '100'

def test_all_zeros():
    assert string_xor('000', '000') == '000'

def test_all_ones():
    assert string_xor('111', '111') == '000'

def test_zeros_and_ones():
    assert string_xor('000', '111') == '111'

def test_ones_and_zeros():
    assert string_xor('111', '000') == '111'

def test_single_bit_zero_zero():
    assert string_xor('0', '0') == '0'

def test_single_bit_one_one():
    assert string_xor('1', '1') == '0'

def test_single_bit_zero_one():
    assert string_xor('0', '1') == '1'

def test_single_bit_one_zero():
    assert string_xor('1', '0') == '1'

def test_empty_strings():
    assert string_xor('', '') == ''

def test_alternating_pattern():
    assert string_xor('1010', '0101') == '1111'

def test_same_alternating():
    assert string_xor('1010', '1010') == '0000'

def test_longer_string():
    assert string_xor('11001100', '10101010') == '01100110'

def test_returns_string_type():
    result = string_xor('010', '110')
    assert isinstance(result, str)

def test_result_length_matches_input():
    a, b = '10110', '01001'
    result = string_xor(a, b)
    assert len(result) == len(a)

def test_xor_identity_with_zeros():
    a = '10101'
    zeros = '00000'
    assert string_xor(a, zeros) == a

def test_xor_self_gives_zeros():
    a = '10101'
    assert string_xor(a, a) == '0' * len(a)

def test_commutativity():
    a = '1100'
    b = '1010'
    assert string_xor(a, b) == string_xor(b, a)

def test_two_bit_strings():
    assert string_xor('10', '01') == '11'
    assert string_xor('11', '00') == '11'
    assert string_xor('11', '11') == '00'
    assert string_xor('00', '00') == '00'

def test_result_contains_only_0_and_1():
    result = string_xor('10110100', '01101011')
    assert all(c in ('0', '1') for c in result)