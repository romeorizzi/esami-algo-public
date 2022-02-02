#!/usr/bin/env python3
# -*- coding: latin-1 -*-
"""
 *  File: sol_lineare.py
 *  Soluzione di riferimento per il problema block_diag_mat
 *  Romeo Rizzi, 2022-02-02
"""

import sys
import copy

MEMO_sum_ne_of = {}
def sum_ne_of(i,j):
    """returns the sum of the entries of M above i (or in the same row) and to the right to j (or in the same column)
    """
    if i < 0:
        return 0
    if j >= n:
        return 0
    global MEMO_sum_ne_of
    if (i,j) not in MEMO_sum_ne_of:
        MEMO_sum_ne_of[i,j] = M[i][j] + sum_ne_of(i-1,j) + sum_ne_of(i,j+1) - sum_ne_of(i-1,j+1)
    return MEMO_sum_ne_of[i,j]

MEMO_sum_sw_of = {}
def sum_sw_of(i,j):
    """returns the sum of the entries of M below i (or in the same row) and to the left to j (or in the same column)
    """
    if i >= m:
        return 0
    if j < n:
        return 0
    global MEMO_sum_sw_of
    if (i,j) not in MEMO_sum_sw_of:
        MEMO_sum_sw_of[i,j] = M[i][j] + sum_sw_of(i+1,j) + sum_sw_of(i,j-1) - sum_sw_of(i+1,j-1)
    return MEMO_sum_sw_of[i,j]

def is_principal_block(first_row, first_col, last_row, last_col):
    if sum_sw_of(first_row+1, first_col-1) > 0:
        return False
    if sum_sw_of(last_row+1, last_col-1) > 0:
        return False
    if sum_ne_of(first_row-1, first_col+1) > 0:
        return False
    if sum_ne_of(last_row-1, last_col+1) > 0:
        return False
    return True


def max_num_square_blocks_as_it_is():
    def is_nonzero(val):
        return 0 if val == 0 else 1
    num_blocks = 0
    Sw_nonzeros = 0 # maintains the number of nonzero entries of M that are situated to the strict South and to the west (or also on the same column) of the current diagonal pos (initially -1)
    En_nonzeros = 0 # maintains the number of nonzero entries of M that are situated to the strict East and to the nort (or also on the same row) of the current diagonal pos (initially -1)
    pos_open_curr_block = 0
    for cur_pos in range(m):
        Sw_nonzeros += sum(is_nonzero(M[i][cur_pos]) for i in range(cur_pos+1,m)) - sum(is_nonzero(M[cur_pos][j]) for j in range(cur_pos))
        En_nonzeros += sum(is_nonzero(M[cur_pos][j]) for j in range(cur_pos+1,n)) - sum(is_nonzero(M[i][cur_pos]) for i in range(cur_pos))
        if Sw_nonzeros == 0 and En_nonzeros == 0:
            assert is_principal_block(first_row=pos_open_curr_block, first_col=pos_open_curr_block, last_row=cur_pos, last_col=cur_pos)
            num_blocks += 1
            pos_open_curr_block = cur_pos + 1
    return num_blocks


def max_num_blocks_as_it_is():
    last_nonzero_pos_in_col = [-1] * n
    last_nonzero_pos_in_row = [-1] * m
    for row,i in zip(M,range(m)):
        for j in range(n):
            if row[j] != 0:
                last_nonzero_pos_in_row[i] = j
                last_nonzero_pos_in_col[j] = i
    num_blocks = 0
    cur_row = 0
    cur_col = 0
    next_block_first_row_lower_bound = 0
    next_block_first_col_lower_bound = 0
    while cur_row < m and cur_col < n:
        assert cur_row == next_block_first_row_lower_bound
        assert cur_col == next_block_first_col_lower_bound
        first_row_cur_block = cur_row
        first_col_cur_block = cur_col
        next_block_first_row_lower_bound += 1 
        next_block_first_col_lower_bound += 1 
        while cur_row < next_block_first_row_lower_bound or cur_col < next_block_first_col_lower_bound:
            if cur_row < next_block_first_row_lower_bound:
                if last_nonzero_pos_in_row[cur_row] >= next_block_first_col_lower_bound:
                    next_block_first_col_lower_bound = 1 + last_nonzero_pos_in_row[cur_row]
                cur_row += 1
            if cur_col < next_block_first_col_lower_bound:
                if last_nonzero_pos_in_col[cur_col] >= next_block_first_row_lower_bound:
                    next_block_first_row_lower_bound = 1 + last_nonzero_pos_in_col[cur_col]
                cur_col += 1
        assert is_principal_block(first_row=first_row_cur_block, first_col=first_col_cur_block, last_row=cur_row, last_col=cur_col)
        num_blocks += 1
    return num_blocks


def num_blocks_with_permuting():
    global M # the feasibility check will first reorder the rows and cols of the matrix according to the computed solution 
    def dfs(line, color):
        nonlocal component_id
        component_id[line] = color
        if line < m:  # line is a row
            for j in range(n):
                if M[line][j] != 0:
                    if component_id[m + j] is None:
                        dfs(m + j, color)
        else:   # line is a column
            line -= m
            for i in range(m):
                if M[i][line] != 0:
                    if component_id[i] is None:
                        dfs(i, color)

    component_id = [None] * (m+n)
    num_blocks = 0
    num_all_zero_rows = 0
    for i in range(m):
        if component_id[i] is None:
            if sum(M[i]) > 0:
                dfs(i, num_blocks)
                num_blocks += 1
            else:
                num_all_zero_rows += 1 
    num_all_zero_columns = 0
    for j in range(n):
        if component_id[m+j] is None:
            num_all_zero_columns += 1
    num_blocks += min(num_all_zero_rows,num_all_zero_columns)
    M_sorted = []
    #print(f"{component_id=}, {num_blocks=}")
    def row_i_sorted_on_columns(unsorted_row,ids,num_blocks):
        #print(f"{unsorted_row=}, {ids=}, {num_blocks=}, ")
        sorted_row = []
        for id in [None] + list(range(num_blocks)):
            for j in range(n):
                if ids[j] == id:
                    sorted_row.append(unsorted_row[j])
        #print(f"{sorted_row=}")
        return sorted_row
    for id in [None] + list(range(num_blocks)):
        for i in range(m):
            if component_id[i] == id:
                M_sorted.append( row_i_sorted_on_columns(M[i], component_id[m:],num_blocks) )
    #print(f"{M_sorted=}")
    assert len(M) == m
    assert len(M[0]) == n    
    assert len(M_sorted) == m
    assert len(M_sorted[0]) == n    
    M = [ row for row in M_sorted ]
    assert len(M) == m
    assert len(M[0]) == n
    if num_blocks != max_num_blocks_as_it_is():
        print(f"{num_blocks=} differs from the answer on the sorted out matrix: {max_num_blocks_as_it_is()}")
        assert False
    return num_blocks
        

# MAIN:
t, m, n = map(int,input().split()) # t in {1,2,3} sets the task type, m = number of rows, n = number of columns
assert 1 <= t <= 3
assert 1 <= m
assert 1 <= n
if t == 1:
    assert m == n 

M = []
for i in range(m):
    M.append(list(map(int,input().split())))

if t == 1:
    print(max_num_square_blocks_as_it_is())
elif t == 2:
    print(max_num_blocks_as_it_is())
elif t == 3:
    print(num_blocks_with_permuting())
else:
    assert False
