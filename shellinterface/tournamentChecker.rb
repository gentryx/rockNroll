#!/usr/bin/ruby
@players = 0..24
@startPos = [405, 431, 92, 83, 87, 167, 227, 63, 40, 65, 16, 407, 57, 395, 81, 116]
@results = []

@players.each do |p1|
  @results[p1] = []
  @players.each do |p2| 
    @results[p1][p2] = []
    @startPos.each do |s1|
      @results[p1][p2][s1] = []
      @startPos.each do |s2|
        @results[p1][p2][s1][s2] = nil
      end
    end
  end
end


while gets =~ /startPosM1: (.*)/
  posM1 = $1.to_i
  gets =~ /startPosM2: ([0-9]*)/
  posM2 = $1.to_i
  gets =~ /playerM1: (.*)/
  playerM1 = $1.to_i
  gets =~ /playerM2: (.*)/
  playerM2 = $1.to_i
  gets =~ /repeats: (.*)/
  repeats = $1.to_i
  gets =~ /gamesWonByM1: (.*)/
  gamesWonByM1 = $1.to_i
  gets

   if @results[playerM1][playerM2][posM1][posM2]
    puts "colosion detected while inserting |#{playerM1}| |#{playerM2}| |#{posM1}| |#{posM2}|"
    exit 1
  end
  @results[playerM1][playerM2][posM1][posM2] = [repeats, gamesWonByM1]
end

def checkPairCompletition(p1, p2)
  nilCounter = 0
  @startPos.each do |s1|
    @startPos.each do |s2|
      unless @results[p1][p2][s1][s2]
        nilCounter+=1 
      end
    end
  end
  return :complete if nilCounter == 0
  return :missing if nilCounter == 256
  puts "counter: #{nilCounter}"
  return :partitial
end

@players.each do |p1| 
  @players.each do |p2| 
    case checkPairCompletition(p1, p2)
    when :complete
    when :partitial
      puts "partitial:   #{p1} #{p2}"
    when :missing
      puts "missing: #{p1} #{p2}"
#      system "qsub jobscript.sh #{p1} #{p2} 20"
    end
  end
end
