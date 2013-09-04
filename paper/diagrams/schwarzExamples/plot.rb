#!/usr/bin/ruby
require './diagrams/pos2tex'

board2tex("$r=4$", [nil, nil,   4, nil, nil, nil, nil, nil])
board2tex("$r=\\frac{5}{6} \\cdot 1 + \\frac{1}{6} \\cdot 2 = \\frac{7}{6}$", [nil, nil, nil, nil, nil, nil,   1,   6])
