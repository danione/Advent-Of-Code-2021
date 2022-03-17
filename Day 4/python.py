import numpy as np

class Board:
    def __init__(self):
        self.board = np.zeros((5,5), dtype=int)
        self.marked = np.zeros((5,5))

    def read_from_lines(self, lines):
        for i in range(5):
            line_entries = [int(entry) for entry in lines[i].split(' ') if entry != '']
            self.board[i] = line_entries

    def check_called_number(self, called_number):
        if called_number in self.board:
            indices = np.where(self.board == called_number)
            self.marked[indices[0], indices[1]] = 1

    def check_win(self):
        return self.marked.all(axis=0).any() or self.marked.all(axis=1).any()

    def calculate_score(self, called_number):
        return (self.board * (self.marked==0)).sum() * called_number

def find_first_winner(called_numbers, boards):
    for called_number in called_numbers:
        for j in range(len(boards)):
            boards[j].check_called_number(called_number)
            if boards[j].check_win():
                print(f"Board {j+1} won!")
                print(boards[j].marked)
                return j, called_number

with open("input.txt", 'r') as f:
    lines = [entry.strip() for entry in f.readlines()]

called_numbers = [int(entry) for entry in lines[0].split(',')]

number_of_boards = (len(lines)-1)//6
print(number_of_boards)
boards = dict()
for j in range(number_of_boards):
    boards[j] = Board()
    boards[j].read_from_lines(lines[(2 + j*6):(2+5+(j+1)*6)])

winner_index, called_number = find_first_winner(called_numbers, boards)
print('score', boards[winner_index].calculate_score(called_number))
