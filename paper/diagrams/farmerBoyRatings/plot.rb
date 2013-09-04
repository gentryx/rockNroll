#!/usr/bin/ruby
require './diagrams/pos2tex'

fullBoard2tex("$r=4$", [
                0,   1, 1,  1,   1, 
                1,   2, 2,  2, 2.5, 
                1,   2, 4,  4,   5, 
                1,   2, 4,  8,  10, 
                1, 2.5, 5, 10,  16
              ])

