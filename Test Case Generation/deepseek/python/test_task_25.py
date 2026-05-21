import pytest
from typing import List
from your_module import factorize  # Replace 'your_module' with the actual module name

def test_prime_numbers():
    """Test prime numbers - should return the number itself"""
    assert factorize(2) == [2]
    assert factorize(3) == [3]
    assert factorize(5) == [5]
    assert factorize(7) == [7]
    assert factorize(11) == [11]
    assert factorize(13) == [13]
    assert factorize(17) == [17]
    assert factorize(19) == [19]

def test_product_of_two_primes():
    """Test numbers that are product of two primes"""
    assert factorize(6) == [2, 3]
    assert factorize(10) == [2, 5]
    assert factorize(14) == [2, 7]
    assert factorize(15) == [3, 5]
    assert factorize(21) == [3, 7]
    assert factorize(22) == [2, 11]
    assert factorize(26) == [2, 13]
    assert factorize(33) == [3, 11]
    assert factorize(34) == [2, 17]
    assert factorize(35) == [5, 7]
    assert factorize(38) == [2, 19]
    assert factorize(39) == [3, 13]
    assert factorize(46) == [2, 23]
    assert factorize(51) == [3, 17]
    assert factorize(55) == [5, 11]
    assert factorize(57) == [3, 19]
    assert factorize(58) == [2, 29]
    assert factorize(62) == [2, 31]
    assert factorize(65) == [5, 13]
    assert factorize(69) == [3, 23]
    assert factorize(74) == [2, 37]
    assert factorize(77) == [7, 11]
    assert factorize(82) == [2, 41]
    assert factorize(85) == [5, 17]
    assert factorize(86) == [2, 43]
    assert factorize(87) == [3, 29]
    assert factorize(91) == [7, 13]
    assert factorize(93) == [3, 31]
    assert factorize(94) == [2, 47]
    assert factorize(95) == [5, 19]

def test_powers_of_two():
    """Test numbers that are powers of 2"""
    assert factorize(2) == [2]
    assert factorize(4) == [2, 2]
    assert factorize(8) == [2, 2, 2]
    assert factorize(16) == [2, 2, 2, 2]
    assert factorize(32) == [2, 2, 2, 2, 2]
    assert factorize(64) == [2, 2, 2, 2, 2, 2]
    assert factorize(128) == [2, 2, 2, 2, 2, 2, 2]
    assert factorize(256) == [2, 2, 2, 2, 2, 2, 2, 2]

def test_powers_of_odd_primes():
    """Test numbers that are powers of odd primes"""
    assert factorize(9) == [3, 3]
    assert factorize(27) == [3, 3, 3]
    assert factorize(81) == [3, 3, 3, 3]
    assert factorize(25) == [5, 5]
    assert factorize(125) == [5, 5, 5]
    assert factorize(49) == [7, 7]
    assert factorize(343) == [7, 7, 7]
    assert factorize(121) == [11, 11]
    assert factorize(1331) == [11, 11, 11]

def test_perfect_squares():
    """Test perfect squares (composite results)"""
    assert factorize(36) == [2, 2, 3, 3]
    assert factorize(100) == [2, 2, 5, 5]
    assert factorize(144) == [2, 2, 2, 2, 3, 3]
    assert factorize(169) == [13, 13]
    assert factorize(196) == [2, 2, 7, 7]
    assert factorize(225) == [3, 3, 5, 5]
    assert factorize(256) == [2, 2, 2, 2, 2, 2, 2, 2]
    assert factorize(400) == [2, 2, 2, 2, 5, 5]

def test_composite_numbers():
    """Test various composite numbers"""
    assert factorize(12) == [2, 2, 3]
    assert factorize(18) == [2, 3, 3]
    assert factorize(20) == [2, 2, 5]
    assert factorize(24) == [2, 2, 2, 3]
    assert factorize(28) == [2, 2, 7]
    assert factorize(30) == [2, 3, 5]
    assert factorize(40) == [2, 2, 2, 5]
    assert factorize(42) == [2, 3, 7]
    assert factorize(44) == [2, 2, 11]
    assert factorize(45) == [3, 3, 5]
    assert factorize(48) == [2, 2, 2, 2, 3]
    assert factorize(50) == [2, 5, 5]
    assert factorize(52) == [2, 2, 13]
    assert factorize(54) == [2, 3, 3, 3]
    assert factorize(56) == [2, 2, 2, 7]
    assert factorize(60) == [2, 2, 3, 5]
    assert factorize(63) == [3, 3, 7]
    assert factorize(66) == [2, 3, 11]
    assert factorize(68) == [2, 2, 17]
    assert factorize(70) == [2, 5, 7]
    assert factorize(72) == [2, 2, 2, 3, 3]
    assert factorize(75) == [3, 5, 5]
    assert factorize(76) == [2, 2, 19]
    assert factorize(78) == [2, 3, 13]
    assert factorize(80) == [2, 2, 2, 2, 5]
    assert factorize(84) == [2, 2, 3, 7]
    assert factorize(88) == [2, 2, 2, 11]
    assert factorize(90) == [2, 3, 3, 5]
    assert factorize(92) == [2, 2, 23]
    assert factorize(96) == [2, 2, 2, 2, 2, 3]
    assert factorize(98) == [2, 7, 7]
    assert factorize(99) == [3, 3, 11]

def test_edge_cases():
    """Test edge cases including boundary values"""
    # Smallest positive integer > 1
    assert factorize(2) == [2]
    assert factorize(3) == [3]
    
    # Large prime numbers
    assert factorize(997) == [997]
    assert factorize(1009) == [1009]
    assert factorize(1013) == [1013]
    assert factorize(104729) == [104729]
    
    # Numbers with repeated large prime factors
    assert factorize(997 * 997) == [997, 997]
    assert factorize(1009 * 1009 * 1009) == [1009, 1009, 1009]
    
    # Product of two large primes
    assert factorize(997 * 1009) == [997, 1009]

def test_highly_composite_numbers():
    """Test numbers with many factors"""
    assert factorize(360) == [2, 2, 2, 3, 3, 5]
    assert factorize(420) == [2, 2, 3, 5, 7]
    assert factorize(840) == [2, 2, 2, 3, 5, 7]
    assert factorize(1260) == [2, 2, 3, 3, 5, 7]
    assert factorize(2520) == [2, 2, 2, 3, 3, 5, 7]
    assert factorize(5040) == [2, 2, 2, 2, 3, 3, 5, 7]
    assert factorize(7560) == [2, 2, 2, 3, 3, 3, 5, 7]
    assert factorize(10080) == [2, 2, 2, 2, 2, 3, 3, 5, 7]

def test_square_of_primes():
    """Test squares of prime numbers"""
    assert factorize(4) == [2, 2]
    assert factorize(9) == [3, 3]
    assert factorize(25) == [5, 5]
    assert factorize(49) == [7, 7]
    assert factorize(121) == [11, 11]
    assert factorize(169) == [13, 13]
    assert factorize(289) == [17, 17]
    assert factorize(361) == [19, 19]

def test_cubes_of_primes():
    """Test cubes of prime numbers"""
    assert factorize(8) == [2, 2, 2]
    assert factorize(27) == [3, 3, 3]
    assert factorize(125) == [5, 5, 5]
    assert factorize(343) == [7, 7, 7]
    assert factorize(1331) == [11, 11, 11]
    assert factorize(2197) == [13, 13, 13]

def test_zero_and_negative():
    """Test that function raises ValueError for invalid inputs"""
    with pytest.raises(ValueError, match="Input must be a positive integer greater than 1"):
        factorize(0)
    
    with pytest.raises(ValueError, match="Input must be a positive integer greater than 1"):
        factorize(1)
    
    with pytest.raises(ValueError, match="Input must be a positive integer greater than 1"):
        factorize(-1)
    
    with pytest.raises(ValueError, match="Input must be a positive integer greater than 1"):
        factorize(-10)
    
    with pytest.raises(ValueError, match="Input must be a positive integer greater than 1"):
        factorize(-100)

def test_large_numbers():
    """Test large numbers to ensure performance and correctness"""
    # Large number with small prime factors
    assert factorize(2**20) == [2] * 20
    assert factorize(3**15) == [3] * 15
    assert factorize(5**12) == [5] * 12
    
    # Large composite number
    result = factorize(2**10 * 3**8 * 5**6 * 7**4)
    expected = [2] * 10 + [3] * 8 + [5] * 6 + [7] * 4
    assert sorted(result) == sorted(expected)
    assert result == expected

def test_product_verification():
    """Verify that product of factors equals original number"""
    test_numbers = [2, 3, 4, 6, 8, 9, 12, 16, 18, 20, 24, 25, 27, 30, 32, 36, 40, 42, 45, 48, 49, 50, 54, 56, 60, 63, 64, 70, 72, 75, 80, 81, 84, 90, 96, 98, 100, 105, 108, 112, 120, 121, 125, 126, 128, 135, 140, 144, 147, 150, 160, 162, 168, 169, 175, 180, 189, 192, 196, 200, 210, 216, 224, 225, 240, 243, 245, 250, 252, 256, 270, 280, 288, 294, 300, 315, 320, 324, 336, 343, 350, 360, 375, 378, 384, 392, 400, 405, 420, 432, 441, 448, 450, 480, 486, 490, 500, 504, 512, 525, 540, 560, 567, 576, 588, 600]
    
    for n in test_numbers:
        factors = factorize(n)
        product = 1
        for factor in factors:
            product *= factor
        assert product == n
        assert sorted(factors) == factors  # Verify ascending order

def test_deterministic_order():
    """Test that factors are always returned in ascending order"""
    test_cases = [
        8, 12, 18, 20, 24, 27, 28, 30, 36, 40, 42, 44, 45, 48, 50, 52, 54, 56, 60, 63, 66, 68, 70, 72, 75, 76, 78, 80, 81, 84, 88, 90, 92, 96, 98, 99, 100
    ]
    
    for n in test_cases:
        factors = factorize(n)
        assert factors == sorted(factors), f"Factors for {n} are not in ascending order: {factors}"

def test_repeated_factorization_consistency():
    """Test that factorization is consistent across multiple calls"""
    test_numbers = [2, 3, 4, 6, 8, 9, 12, 16, 18, 20, 24, 25, 27, 30, 32, 36, 40, 42, 45, 48, 49, 50, 54, 56, 60, 63, 64, 70, 72, 75, 80, 81, 84, 90, 96, 98, 100]
    
    for n in test_numbers:
        first_result = factorize(n)
        second_result = factorize(n)
        assert first_result == second_result, f"Inconsistent results for {n}: {first_result} vs {second_result}"
    
    # Also test with random numbers
    import random
    random.seed(42)
    for _ in range(50):
        n = random.randint(2, 100000)
        first_result = factorize(n)
        second_result = factorize(n)
        assert first_result == second_result, f"Inconsistent results for {n}: {first_result} vs {second_result}"

def test_large_prime_factorization():
    """Test factorization of large primes and near-primes"""
    # Large primes
    large_primes = [100003, 100019, 100043, 100049, 100057, 100069, 100103, 100109, 100129, 100151]
    
    for prime in large_primes:
        assert factorize(prime) == [prime]
    
    # Products of large primes
    for i in range(len(large_primes) - 1):
        product = large_primes[i] * large_primes[i + 1]
        result = factorize(product)
        assert result == [large_primes[i], large_primes[i + 1]]
    
    # Squares of large primes
    for prime in large_primes[:5]:
        square = prime * prime
        assert factorize(square) == [prime, prime]
    
    # Cubes of large primes
    for prime in large_primes[:3]:
        cube = prime ** 3
        assert factorize(cube) == [prime, prime, prime]

def test_boundary_algorithm_edge_cases():
    """Test edge cases that exercise the algorithm's boundary conditions"""
    # Numbers near sqrt boundaries
    assert factorize(1000000) == [2, 2, 2, 2, 2, 2, 5, 5, 5, 5, 5, 5]
    assert factorize(999983) == [999983]  # Prime just below 1,000,000
    
    # Numbers where sqrt(n) is integer
    assert factorize(99856) == [2, 2, 2, 2, 79, 79]  # 316^2
    
    # Numbers with repeated factor where i reaches sqrt(n) after division
    assert factorize(2 * 10007) == [2, 10007]
    assert factorize(3 * 10007) == [3, 10007]