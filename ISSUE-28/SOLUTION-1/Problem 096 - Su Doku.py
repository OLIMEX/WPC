puzzle_file = open('sudoku.txt')
puzzle_data = puzzle_file.read()
puzzle_lines = puzzle_data.split('\n')

values = range(1, 10);

class Cell:
    def __init__(self, owner, row, col):
        self.owner = owner
        self.row = row
        self.col = col
        self.blk = 0
        
        self.known = False
        self.value = 0
        self.could_be = set(values)
    def known_value(self, value):
        if self.known:
            return
        self.owner.unknown = self.owner.unknown - 1
        self.known = True
        self.value = value
        self.could_be = set([value])

        self.row.known_value(self, value)
        self.col.known_value(self, value)
        self.blk.known_value(self, value)
    def cannot_be(self, value):
        if value in self.could_be:
            self.could_be = self.could_be - set([value])
            if len(self.could_be) == 1:
                for only_item in self.could_be:
                    self.known_value(only_item)
            
        

class Group:
    def __init__(self, info, cells):
        self.info = info
        self.cells = cells
    def __getitem__(self, index):
        return self.cells[index]
    def known_value(self, cell, value):
        for other_cell in self.cells:
            if other_cell <> cell:
                other_cell.cannot_be(value)
    def find_uniques(self):
        for value in values:
            count = 0
            for cell in self.cells:
                if value in cell.could_be:
                    count = count + 1
                    last_cell_found = cell
            if count == 1:
                last_cell_found.known_value(value)

block_start = [(blk, 3 * (blk / 3), 3 * (blk % 3)) for blk in xrange(9)]

class SuDoku:
    def __init__(self):
        self.unknown = 9*9
        # create cells with dummy info
        self.data = [[Cell(self, row, col) for col in xrange(9)] for row in xrange(9)]
        # create rows, columns and blocks
        self.rows = [Group(row, [self.data[row][col] for col in xrange(9)])
                                                     for row in xrange(9)]
        self.cols = [Group(col, [self.data[row][col] for row in xrange(9)])
                                                     for col in xrange(9)]
        self.blks = [Group(blk, [self.data[sr + ro][sc + co] for ro in xrange(3)
                                                             for co in xrange(3)])
                                                     for (blk, sr, sc) in block_start]
        # link cells to their containers
        for row in self.rows:
            for cell in row:
                cell.row = row
        for col in self.cols:
            for cell in col:
                cell.col = col
        for blk in self.blks:
            for cell in blk:
                cell.blk = blk
        # big list to loop over                        
        self.groups = self.rows + self.cols + self.blks
    def parse_puzzle(self, puzzle):
        for row in xrange(len(puzzle)):
            for col in xrange(len(puzzle)):
                character = puzzle[row][col:col+1]
                value = int(character)
                if value > 0:
                    self.data[row][col].known_value(value)
    def print_puzzle(self):
        for row in xrange(9):
            for col in xrange(9):
                cell = self.data[row][col]
                if cell.value > 0:
                    print cell.value,
                else:
                    print 0, 
#                    print cell.could_be, 
            print
    def solve_tricky(self, lines):
        for lin in lines:
            for blk in self.blks:
                lin_cell_set = set(lin.cells)
                blk_cell_set = set(blk.cells)
                both = lin_cell_set & blk_cell_set
                if len(both) > 0:
                    other_lin_cells = lin_cell_set - both
                    other_blk_cells = blk_cell_set - both
                    ivals = set()
                    for x in both:
                        ivals = ivals | x.could_be
                    lvals = set()
                    for x in both:
                        lvals = lvals | x.could_be
                    bvals = set()
                    for x in both:
                        bvals = bvals | x.could_be
                    for i in ivals:
                        if i not in lvals:
                            for cell in other_blk_cells:
                                cell.cannot_be(i)
                        if i not in bvals:
                            for cell in other_lin_cells:
                                cell.cannot_be(i)
    def solve(self):
        unknown = self.unknown
        while unknown > 0:
            for group in self.groups:
                group.find_uniques()
            self.solve_tricky(self.rows)
            self.solve_tricky(self.cols)
            for group in self.groups:
                group.find_uniques()
            if unknown == self.unknown:
                return
            else:
                unknown = self.unknown
    def solved(self):
        return reduce(lambda x, y: x*y,
            [self.data[0][x].value for x in xrange(3)], 1) > 1
    def solution(self):
        return reduce(lambda x, y: x+y,
            [10**(2-x) * self.data[0][x].value for x in xrange(3)], 0)
    

count_solved = 0
total_answer = 0
for x in xrange(len(puzzle_lines) / 10):
    gridname = puzzle_lines[x * 10]
    puzzle = puzzle_lines[x*10 + 1:x*10 + 10]
    sd = SuDoku()
    sd.parse_puzzle(puzzle)
    sd.solve()   
    if sd.solved():
        count_solved = count_solved + 1
        total_answer = total_answer + sd.solution()
        print gridname, sd.solution()
    else:
        print gridname
        sd.print_puzzle()
        
    
print count_solved, 'out of 50:', total_answer

