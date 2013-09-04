#!/usr/bin/ruby

EntryExpr = /startPosM1: (.*)\nstartPosM2\: (.*)\nplayerM1\: (.*)\nplayerM2\: (.*)\nrepeats\: (.*)\ngamesWonByM1\: (.*)\n\n/
@stats = []
25.times do |i| 
  @stats[i] = []
  25.times do |j| 
    @stats[i][j] = {:won => 0, :repeats => 0}
  end
end

def readEntry
  begin
    return nil  unless (gets+gets+gets+gets+gets+gets+gets) =~ EntryExpr
  rescue
    return nil
  end  
  return [$1, $2, $3, $4, $5, $6].collect { |e| e.to_i }
end

def storeEntry(e)
  startPosM1   = e[0]
  startPosM2   = e[1]
  playerM1     = e[2]
  playerM2     = e[3]
  repeats      = e[4]
  gamesWonByM1 = e[5]

  @stats[playerM1][playerM2][:won] += gamesWonByM1
  @stats[playerM1][playerM2][:repeats] += repeats

  @stats[playerM2][playerM1][:won] += repeats-gamesWonByM1
  @stats[playerM2][playerM1][:repeats] += repeats
end

loop do
  break unless e = readEntry
  storeEntry(e)
end

@players = [
  "\\verb§MrRandom§",
  "\\verb§MrMonte§(0,\\ \\ \\ 50, \\verb§MrBlack§(0))",
  "\\verb§MrMonte§(0,        100, \\verb§MrBlack§(0))",
  "\\verb§MrMonte§(0,        150, \\verb§MrBlack§(0))",
  "\\verb§MrMonte§(0,        200, \\verb§MrBlack§(0))",
  "\\verb§MrMonte§(1,        200, \\verb§MrBlack§(0))",
  "\\verb§MrMonte§(0,        200, \\verb§MrBlack§(1))",
  "\\verb§MrBlack§(0)",
  "\\verb§MrBlack§(1)",
  "\\verb§MrBlack§(2)",
  "\\verb§MrBlack§(3)",
  "\\verb§MrBlack§(4)",
  "\\verb§FarmerBoy§(0)",
  "\\verb§FarmerBoy§(1)",
  "\\verb§FarmerBoy§(2)",
  "\\verb§FarmerBoy§(3)",
  "\\verb§FarmerBoy§(4)",
  "\\verb§MrMonte§(1,\\ \\ \\ 20, \\verb§FarmerBoy§(1))",
  "\\verb§MrMonte§(2,\\ \\ \\ 20, \\verb§FarmerBoy§(0))",
  "\\verb§MrMonte§(2,\\ \\ \\ 40, \\verb§FarmerBoy§(0))",
  "\\verb§MrMonte§(0,\\ \\ \\ 20, \\verb§MrMonte§(0))\\tnote{1}",
  "\\verb§MrMonte§(0,\\ \\ \\ 50, \\verb§FarmerBoy§(0))",
  "\\verb§MrMonte§(0,        100, \\verb§FarmerBoy§(0))",
  "\\verb§MrMonte§(0,        150, \\verb§FarmerBoy§(0))",
  "\\verb§MrMonte§(0,        200, \\verb§FarmerBoy§(0))"
]

#delete player 17

@newStats = []
25.times do |i|
  next if i == 17
  foo = []
  25.times do |j|
    next if j == 17
    foo.push @stats[i][j]
  end
  @newStats.push foo
end
@stats = @newStats

@newPlayers = []
@players.length.times { |i| @newPlayers.push(@players[i]) unless i == 17 }
@players = @newPlayers

class Range
  def length
    return max - min  + 1
  end
end

def printHeader(range, stream, summaryMode)
  columns = range.length
  ls = ""
  normColumn = (summaryMode ? "@{}c" : "D{.}{.}{2}") 
  columns.times { ls += normColumn }

  cut1stCol = ""
  if summaryMode
    cut1stCol = "@{}r@{}"
    colSizeMod1 = "\\text{\\footnotesize"
    colSizeMod2 = "}"
    ls += "@{}"
  else
    cut1stCol = "r"
    colSizeMod1 = ""
    colSizeMod2 = ""
  end

  stream.print <<HERE
\\begin{threeparttable}
    \\begin{tabular}{#{cut1stCol}l#{ls}}
    \\toprule
    \\multicolumn{2}{c}{Player vs. Player}
HERE

  range.each { |i| stream.print "& \\multicolumn{1}{c}{#{colSizeMod1}#{i+1}#{colSizeMod2}}" }
  stream.puts '\\\\'
  stream.puts '      \\cmidrule(r){1-2}'
  (columns-1).times do |i| 
    stream.print "\\cmidrule(lr){#{i+3}-#{i+3}}"
  end
  stream.puts "\\cmidrule(l){#{columns+2}-#{columns+2}}"
end

def printBody(range, stream, summaryMode)
  @stats.length.times do |i|
    if summaryMode
      stream.print "\\text{\\scriptsize#{i+1}\\ } & \\text{\\scriptsize#{@players[i]}}"
    else
      stream.print "#{i+1} & #{@players[i]}"
    end
    range.each do |j|
      e = @stats[i][j]
      num = (100.0*e[:won]/e[:repeats] * 100).round / 100.0

      if summaryMode
        case 
        when num <= 45: entry = "\\ensuremath\\ominus"
        when num >= 55: entry = "\\ensuremath\\oplus"
        else entry = "\\ensuremath\\bullet"
        end
      else
        entry = (num*100).to_i.to_s.rjust(4)
        entry = entry[0..1]+"."+entry[2..3]
#       entry = "\\textcolor{red}{#{entry}}" if i == j
#       entry = "\\textbf{\\textcolor{green}{#{entry}}}" if num >= 50
      end

      entry = "\\multicolumn{1}{c}{--}" if i == j
      stream.print " & #{entry}"
    end
    stream.print '\\\\'
#     stream.print '\\addlinespace' if i == 0
#     stream.print '\\addlinespace' if i == 4
#     stream.print '\\addlinespace' if i == 6
#     stream.print '\\addlinespace' if i == 11
#     stream.print '\\addlinespace' if i == 16
#     stream.print '\\addlinespace' if i == 18
#     stream.print '\\addlinespace' if i == 19
    stream.puts 
  end
end

def printFooter(range, stream)
  stream.puts <<HERE
    \\bottomrule
  \\end{tabular}
  \\begin{tablenotes}
    \\footnotesize
    \\item[1] Relies on two \\verb§MrMonte§(0, 10, \\verb§FarmerBoy§(0))
  \\end{tablenotes}
\\end{threeparttable}
HERE
end

def printColumns(range, stream, summaryMode)
  printHeader(range, stream, summaryMode)
  printBody(range, stream, summaryMode)
  printFooter(range, stream)
end

File.open("diagrams/tournament/fullPart1.tex", "w") { |f| printColumns( 0..11, f, false) }
File.open("diagrams/tournament/fullPart2.tex", "w") { |f| printColumns(12..23, f, false) }
File.open("diagrams/tournament/summary.tex", "w") { |f| printColumns( 0..23, f, true) }
