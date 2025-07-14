# Copyright (c) 2021 kamyu. All rights reserved.
#
# Google Code Jam 2021 Virtual World Finals - Problem C. Ropes
# https://codingcompetitions.withgoogle.com/codejam/round/0000000000436329/000000000084fad0
#
# Time:  O(N^3), pass in PyPy2 but Python2
# Space: O(N^2)
#
# Usage: python interactive_runner.py python3 testing_tool.py 2 -- python ropes.py
#
# push it east solution
#   - Z=10, 18322/20000 = 91.610 %
#   - Z=14, 18251/20000 = 91.255 %
#

from sys import stdout
# from itertools import imap  # Python3 不需要 imap

def play(i, j):
    print(i+1, j+1)  # 0-indexed
    stdout.flush()
    return list(map(lambda x: int(x)-1, input().strip().split()))  # 0-indexed

def check_result():
    res = int(input())

def greedy(score_matrix):
    # given that opposing team choose the play that yields the maximum possible score for this turn.
    # if there is a tie:
    #   - they will choose one at random as problem description claims
    #   - they will not choose by a counter-greedy strategy (they choose as far east as possible), since we can never win by this greedy strategy if they can always do that
    result = None
    best_score = max(map(max, score_matrix))
    for i in range(2*N):
        for j in range(2*N):
            if score_matrix[i][j] == best_score and (result is None or (sum(result) > i+j)):
                result = (i, j)
    if result is None:
        result = (0, 0)  # 保底返回一个合法元组，防止 NoneType 错误
    return result

def update(i, j, score_matrix):
    for r in range(2*N):
        for c in range(2*N):
            if r == i or c == j:
                score_matrix[r][c] = NEG_INF
            elif (r-i)*(c-j) < 0:
                score_matrix[r][c] += 1

def ropes():
    score_matrix = [[0 for _ in range(2*N)] for _ in range(2*N)]
    for k in range(N):
        i, j = greedy(score_matrix) if k else (Z-1, Z-1)
        update(i, j, score_matrix)
        i, j = play(i, j)
        update(i, j, score_matrix)
    check_result()

NEG_INF = float("-inf")
Z = 10  # tuned by experiments that top 4 win rates are with Z = [10, 14, 9, 11]
T, N, W = map(int, input().strip().split())
for case in range(T):
    ropes()