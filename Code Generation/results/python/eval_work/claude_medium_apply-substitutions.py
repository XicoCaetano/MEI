# === IMPORTS GERAIS (do dataset) ===
import random
import functools
import collections
import string
import math
import datetime

from typing import *
from functools import *
from collections import *
from itertools import *
from heapq import *
from bisect import *
from string import *
from operator import *
from math import *

inf = float('inf')

class ListNode:
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next

def list_node(values: list):
    if not values:
        return None
    head = ListNode(values[0])
    p = head
    for val in values[1:]:
        node = ListNode(val)
        p.next = node
        p = node
    return head

def is_same_list(p1, p2):
    if p1 is None and p2 is None:
        return True
    if not p1 or not p2:
        return False
    return p1.val == p2.val and is_same_list(p1.next, p2.next)

class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right

def tree_node(values: list):
    if not values:
        return None
    root = TreeNode(values[0])
    i = 1
    queue = deque()
    queue.append(root)
    while queue:
        node = queue.popleft()
        if i < len(values) and values[i] is not None:
            node.left = TreeNode(values[i])
            queue.append(node.left)
        i += 1
        if i < len(values) and values[i] is not None:
            node.right = TreeNode(values[i])
            queue.append(node.right)
        i += 1
    return root

def is_same_tree(p, q):
    if not p and not q:
        return True
    elif not p or not q:
        return False
    elif p.val != q.val:
        return False
    else:
        return is_same_tree(p.left, q.left) and is_same_tree(p.right, q.right)


# === MODEL RESPONSE ===
from typing import List
import re

class Solution:
    def applySubstitutions(self, replacements: List[List[str]], text: str) -> str:
        mapping = {k: v for k, v in replacements}
        
        def resolve(key):
            val = mapping[key]
            return re.sub(r'%([A-Z])%', lambda m: resolve(m.group(1)), val)
        
        return re.sub(r'%([A-Z])%', lambda m: resolve(m.group(1)), text)

# === TEST FUNCTION (do dataset) ===
def check(candidate):
    assert candidate(replacements = [['W', 'wxy'], ['X', 'xyz'], ['Y', '%W%_%X%'], ['Z', 'uvw']],text = "%Y%_%Z%") == "wxy_xyz_uvw"
    assert candidate(replacements = [['M', 'mno'], ['N', 'pqr'], ['O', 'stu'], ['P', '%M%%N%']],text = "%M%_%N%_%O%_%P%") == "mno_pqr_stu_mnopqr"
    assert candidate(replacements = [['X', 'xyz'], ['Y', 'uvw'], ['Z', '%X%%Y%']],text = "%X%_%Y%_%Z%") == "xyz_uvw_xyzuvw"
    assert candidate(replacements = [['M', 'mno'], ['N', 'pqr'], ['O', 'stu'], ['P', 'vwx']],text = "%M%_%N%_%O%_%P%") == "mno_pqr_stu_vwx"
    assert candidate(replacements = [['A', 'abc'], ['B', 'def']],text = "%A%_%B%") == "abc_def"
    assert candidate(replacements = [['Q', 'qwe'], ['R', 'rty'], ['S', '%Q%%R%'], ['T', '%R%%S%']],text = "%Q%_%R%_%S%_%T%") == "qwe_rty_qwerty_rtyqwerty"
    assert candidate(replacements = [['X', 'xyz'], ['Y', 'uvw'], ['Z', '%X%_%Y%']],text = "%X%_%Y%_%Z%") == "xyz_uvw_xyz_uvw"
    assert candidate(replacements = [['Q', 'qwe'], ['R', 'rty'], ['S', 'uiop'], ['T', 'asdf'], ['U', '%Q%%R%']],text = "%Q%_%R%_%S%_%T%_%U%") == "qwe_rty_uiop_asdf_qwerty"
    assert candidate(replacements = [['A', 'bce'], ['B', 'ace'], ['C', 'abc%B%']],text = "%A%_%B%_%C%") == "bce_ace_abcace"
    assert candidate(replacements = [['X', 'mno'], ['Y', 'pqr'], ['Z', '%X%%Y%'], ['A', 'stu'], ['B', '%Z%%A%'], ['C', 'vwx%B%']],text = "%C%") == "vwxmnopqrstu"
    assert candidate(replacements = [['A', 'xy%B%zy'], ['B', 'wv%C%vu'], ['C', 'ut%D%tu'], ['D', 'sr%E%sr'], ['E', 'qp%F%pq'], ['F', 'on%G%no'], ['G', 'ml%H%ml'], ['H', 'lk%I%lk'], ['I', 'ji%J%ji'], ['J', 'hg']],text = "%A%_%B%_%C%_%D%_%E%_%F%_%G%_%H%_%I%_%J%") == "xywvutsrqponmllkjihgjilkmlnopqsrtuvuzy_wvutsrqponmllkjihgjilkmlnopqsrtuvu_utsrqponmllkjihgjilkmlnopqsrtu_srqponmllkjihgjilkmlnopqsr_qponmllkjihgjilkmlnopq_onmllkjihgjilkmlno_mllkjihgjilkml_lkjihgjilk_jihgji_hg"
    assert candidate(replacements = [['N', 'abc%O%'], ['O', 'def%P%'], ['P', 'ghi'], ['Q', 'jkl%O%'], ['R', 'mno%P%'], ['S', 'pqr%O%']],text = "%N%_%Q%_%R%_%S%") == "abcdefghi_jkldefghi_mnoghi_pqrdefghi"
    assert candidate(replacements = [['A', 'bcd'], ['B', '%A%%A%'], ['C', '%B%def'], ['D', 'ghi%C%']],text = "%A%_%B%_%C%_%D%") == "bcd_bcdbcd_bcdbcddef_ghibcdbcddef"
    assert candidate(replacements = [['S', 'stu'], ['T', 'vwx'], ['U', '%S%%T%'], ['V', '%U%%U%'], ['W', '%V%%V%'], ['X', '%W%%W%'], ['Y', '%X%%X%']],text = "%S%_%T%_%U%_%V%_%W%_%X%_%Y%") == "stu_vwx_stuvwx_stuvwxstuvwx_stuvwxstuvwxstuvwxstuvwx_stuvwxstuvwxstuvwxstuvwxstuvwxstuvwxstuvwxstuvwx_stuvwxstuvwxstuvwxstuvwxstuvwxstuvwxstuvwxstuvwxstuvwxstuvwxstuvwxstuvwxstuvwxstuvwxstuvwxstuvwx"
    assert candidate(replacements = [['H', 'xyz%I%'], ['I', 'uvw'], ['J', '%H%_%I%'], ['K', 'lmn'], ['L', 'opq%I%'], ['M', 'rst%I%']],text = "%J%_%K%_%L%_%M%") == "xyzuvw_uvw_lmn_opquvw_rstuvw"
    assert candidate(replacements = [['S', 'abc'], ['T', 'def'], ['U', '%S%%T%'], ['V', '%U%ghi'], ['W', 'jkl%V%']],text = "%W%") == "jklabcdefghi"
    assert candidate(replacements = [['E', 'efg'], ['F', 'hij'], ['G', '%E%%F%'], ['H', '%G%%G%'], ['I', '%H%%H%'], ['J', '%I%%I%']],text = "%E%_%F%_%G%_%H%_%I%_%J%") == "efg_hij_efghij_efghijefghij_efghijefghijefghijefghij_efghijefghijefghijefghijefghijefghijefghijefghij"
    assert candidate(replacements = [['A', 'abc'], ['B', 'def'], ['C', '%A%%B%'], ['D', '%C%%C%']],text = "%A%_%B%_%C%_%D%") == "abc_def_abcdef_abcdefabcdef"
    assert candidate(replacements = [['S', '%T%%U%'], ['T', 'vwx'], ['U', '%V%uvw'], ['V', 'xyz'], ['W', '123'], ['X', '%W%%S%']],text = "%X%_%S%_%U%_%V%_%W%") == "123vwxxyzuvw_vwxxyzuvw_xyzuvw_xyz_123"
    assert candidate(replacements = [['L', 'lmn'], ['M', 'nop'], ['N', 'qrs'], ['O', '%L%%M%'], ['P', '%O%%N%'], ['Q', '%P%%P%']],text = "%L%_%M%_%N%_%O%_%P%_%Q%") == "lmn_nop_qrs_lmnnop_lmnnopqrs_lmnnopqrslmnnopqrs"
    assert candidate(replacements = [['A', 'bcd%F%'], ['B', '%E%abc'], ['C', '%A%%B%'], ['D', 'xyz'], ['E', 'uvw'], ['F', '123']],text = "%C%_%D%_%E%_%F%") == "bcd123uvwabc_xyz_uvw_123"
    assert candidate(replacements = [['A', 'abc'], ['B', 'def'], ['C', '%A%%B%'], ['D', '%C%%C%'], ['E', '%D%%D%'], ['F', '%E%%E%'], ['G', '%F%%F%']],text = "%A%_%B%_%C%_%D%_%E%_%F%_%G%") == "abc_def_abcdef_abcdefabcdef_abcdefabcdefabcdefabcdef_abcdefabcdefabcdefabcdefabcdefabcdefabcdefabcdef_abcdefabcdefabcdefabcdefabcdefabcdefabcdefabcdefabcdefabcdefabcdefabcdefabcdefabcdefabcdefabcdef"
    assert candidate(replacements = [['P', 'pqr'], ['Q', '%P%_%P%'], ['R', '%Q%_%Q%'], ['S', '%R%_%R%']],text = "%P%_%Q%_%R%_%S%") == "pqr_pqr_pqr_pqr_pqr_pqr_pqr_pqr_pqr_pqr_pqr_pqr_pqr_pqr_pqr"
    assert candidate(replacements = [['A', 'bcd%F%efg'], ['B', 'hij%G%klm'], ['C', 'nop%H%qrs'], ['D', 'tuv%I%wxy'], ['E', 'yz%J%abc'], ['F', 'def'], ['G', 'ghi'], ['H', 'jkl'], ['I', 'mno'], ['J', 'pqr']],text = "%A%_%B%_%C%_%D%_%E%") == "bcddefefg_hijghiklm_nopjklqrs_tuvmnowxy_yzpqrabc"
    assert candidate(replacements = [['P', 'pqr'], ['Q', 'stu%P%'], ['R', 'uvw%Q%'], ['S', 'xyz%R%'], ['T', 'abc'], ['U', 'def%T%'], ['V', 'ghi%U%'], ['W', 'jkl%V%'], ['X', 'mno%W%'], ['Y', 'opq%X%'], ['Z', 'rst%Y%']],text = "%Z%") == "rstopqmnojklghidefabc"
    assert candidate(replacements = [['M', 'mnop'], ['N', '%O%%P%'], ['O', 'qrst'], ['P', '%Q%%R%'], ['Q', 'uvw'], ['R', 'xyz']],text = "%M%_%N%_%O%_%P%_%Q%_%R%") == "mnop_qrstuvwxyz_qrst_uvwxyz_uvw_xyz"
    assert candidate(replacements = [['U', 'uvw'], ['V', 'xyz'], ['W', '%U%%V%'], ['X', '%W%%W%'], ['Y', '%X%%X%']],text = "%U%_%V%_%W%_%X%_%Y%") == "uvw_xyz_uvwxyz_uvwxyzuvwxyz_uvwxyzuvwxyzuvwxyzuvwxyz"
    assert candidate(replacements = [['X', 'abc'], ['Y', 'def%X%ghi'], ['Z', 'jkl%Y%mno'], ['W', 'pqr%Z%stu'], ['V', 'vwx%W%yz']],text = "%X%_%Y%_%Z%_%W%_%V%") == "abc_defabcghi_jkldefabcghimno_pqrjkldefabcghimnostu_vwxpqrjkldefabcghimnostuyz"
    assert candidate(replacements = [['Y', '%Z%abc'], ['Z', '%A%%B%'], ['A', 'def'], ['B', 'ghi'], ['C', '%Y%%A%'], ['D', 'jkl']],text = "%C%_%D%_%Y%_%Z%") == "defghiabcdef_jkl_defghiabc_defghi"
    assert candidate(replacements = [['A', 'bce'], ['B', 'ace'], ['C', 'abc%B%'], ['D', '%C%_%A%'], ['E', '%B%_%D%'], ['F', '%E%_%C%']],text = "%F%") == "ace_abcace_bce_abcace"
    assert candidate(replacements = [['I', 'mno'], ['J', 'pqr'], ['K', 'stu%I%'], ['L', '%J%%K%'], ['M', 'vwx%L%']],text = "%M%") == "vwxpqrstumno"
    assert candidate(replacements = [['M', 'abc'], ['N', 'def'], ['O', 'ghi%N%'], ['P', 'jkl%O%'], ['Q', '%P%_%M%'], ['R', '%Q%_%N%']],text = "%R%") == "jklghidef_abc_def"
    assert candidate(replacements = [['A', 'abc%F%def'], ['B', 'ghi%J%klm'], ['C', 'nop%K%qr'], ['D', 'stu'], ['E', '%A%%B%'], ['F', '%D%vwx'], ['G', '%E%%C%'], ['H', 'yz'], ['I', '%H%abc'], ['J', '%I%def'], ['K', '%J%ghi']],text = "%E%_%G%") == "abcstuvwxdefghiyzabcdefklm_abcstuvwxdefghiyzabcdefklmnopyzabcdefghiqr"
    assert candidate(replacements = [['Y', 'abc'], ['Z', 'def%Y%'], ['A', 'ghi%Z%'], ['B', 'jkl%A%'], ['C', 'mno%B%'], ['D', '%C%_%A%']],text = "%D%") == "mnojklghidefabc_ghidefabc"
    assert candidate(replacements = [['A', 'def%G%'], ['B', 'ghi'], ['C', 'jkl%G%'], ['D', 'mno'], ['E', 'pqr'], ['F', 'stu%G%'], ['G', 'abc']],text = "%A%_%B%_%C%_%D%_%E%_%F%") == "defabc_ghi_jklabc_mno_pqr_stuabc"
    assert candidate(replacements = [['E', '%F%'], ['F', '%G%'], ['G', 'xyz'], ['H', '%E%_%F%_%G%']],text = "%H%") == "xyz_xyz_xyz"
    assert candidate(replacements = [['K', 'klm'], ['L', 'nop'], ['M', 'qrs'], ['N', '%K%%L%'], ['O', '%M%%M%'], ['P', '%N%%O%'], ['Q', '%P%%P%']],text = "%K%_%L%_%M%_%N%_%O%_%P%_%Q%") == "klm_nop_qrs_klmnop_qrsqrs_klmnopqrsqrs_klmnopqrsqrsklmnopqrsqrs"
    assert candidate(replacements = [['N', 'opq'], ['O', 'rst'], ['P', '%N%%O%'], ['Q', '%P%uvw'], ['R', 'xyz%Q%']],text = "%R%") == "xyzopqrstuvw"
    assert candidate(replacements = [['G', 'ghi'], ['H', '%I%jkl'], ['I', 'mnop'], ['J', '%G%%H%'], ['K', 'qrst'], ['L', '%K%uvw']],text = "%J%_%L%") == "ghimnopjkl_qrstuvw"


# === INVOCATION ===
check(Solution().applySubstitutions)
print("All tests passed")
