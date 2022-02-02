#!/usr/bin/env python3
# -*- coding: latin-1 -*-
"""
 *  File: sol_lineare.py
 *  Soluzione di riferimento per il problema block_diag_mat
 *  Romeo Rizzi, 2022-02-02
"""

import sys

def max_num_square_blocks_as_it_is(m,n,M):
    def is_nonzero(val):
        return 0 if val == 0 else 1
    num_blocks = 0
    Sw_nonzeros = 0 # maintains the number of nonzero entries of M that are situated to the strict South and to the west (or also on the same column) of the current diagonal pos (initially -1)
    En_nonzeros = 0 # maintains the number of nonzero entries of M that are situated to the strict East and to the nort (or also on the same row) of the current diagonal pos (initially -1)
    for cur_pos in range(m):
        Sw_nonzeros += sum(is_nonzero(M[i][cur_pos]) for i in range(cur_pos+1,m)) - sum(is_nonzero(M[cur_pos][j]) for j in range(cur_pos))
        En_nonzeros += sum(is_nonzero(M[cur_pos][j]) for j in range(cur_pos+1,n)) - sum(is_nonzero(M[i][cur_pos]) for i in range(cur_pos))
        if Sw_nonzeros == 0 and En_nonzeros == 0:
            num_blocks += 1
    return num_blocks


def max_num_blocks_as_it_is(m,n,M):
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
        num_blocks += 1
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
    return num_blocks


def num_blocks_with_permuting(m,n,M):
    def dfs(line):
        nonlocal visited
        visited[line] = True
        if line < m:  # line is a row
            for j in range(n):
                if M[line][j] != 0:
                    if not visited[m + j]:
                        dfs(m + j)
        else:   # line is a column
            line -= m
            for i in range(m):
                if M[i][line] != 0:
                    if not visited[i]:
                        dfs(i)

    visited = [False] * (m+n)
    num_blocks = 0
    num_all_zero_rows = 0
    for i in range(m):
        if not visited[i]:
            if sum(M[i]) > 0:
                num_blocks += 1
                dfs(i)
            else:
                num_all_zero_rows += 1 
    num_all_zero_columns = 0
    for j in range(n):
        if not visited[m+j]:
            num_all_zero_columns += 1
    num_blocks += min(num_all_zero_rows,num_all_zero_columns)
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
    print(max_num_square_blocks_as_it_is(m,n,M))
elif t == 2:
    print(max_num_blocks_as_it_is(m,n,M))
elif t == 3:
    print(num_blocks_with_permuting(m,n,M))
else:
    assert False
