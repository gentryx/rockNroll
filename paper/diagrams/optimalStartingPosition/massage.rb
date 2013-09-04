#!/usr/bin/ruby
require './diagrams/pos2tex'

INFILE="./diagrams/optimalStartingPosition/data.txt"
BESTFILE="./diagrams/optimalStartingPosition/best.tex"
WORSTFILE="./diagrams/optimalStartingPosition/worst.tex"
@boards = { }

File.open(INFILE).each do |l|  
  elements = l.split  
  next if elements.length != 2
  @boards[elements[1].to_f] = elements[0].to_i
end

def boardID2pos(id)
  lines = `/home/gentryx/rockNroll/trunk/shellinterface/showboard #{id}`.split("\n")[3..7]
  ret = []
  lines[0] =~ /\[ (.) (.) (.) (.) (.)\]/
  ret.concat([$1, $2, $3])
  lines[1] =~ /\[ (.) (.) (.) (.) (.)\]/
  ret.concat([$1, $2])
  lines[2] =~ /\[ (.) (.) (.) (.) (.)\]/
  ret.concat([$1])
  ret.collect! { |i| i.to_i + 1}
end

def ratings2file(ratings, file)
  ratings.each { |rating| displayBoard(@boards[rating], rating, file) }
end

ratings2file(@boards.keys.sort.reverse[0..15], File.open(BESTFILE, "w"))
ratings2file(@boards.keys.sort[0..15], File.new(WORSTFILE, "w"))
