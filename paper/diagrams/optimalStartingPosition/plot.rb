#!/usr/bin/ruby

infile = ARGV[0]

gnuplotComm = 'gnuplot<<__EOF__
set terminal latex
set xrange [1:200000000]
set yrange [0:13]
set xrange [0:720]
set yrange [0.2:0.8]
set xlabel "Quasi-lexicographic Ordering Numbers"
set ylabel \'\begin{turn}{90}Win Probabilities\end{turn}\'
set grid
plot "'+infile+'" using 1:2 title "Measurements"
__EOF__'

rawPlot = `#{gnuplotComm}`.split("\n")

CROSSCOLOR="red"
RULECOLOR="lightgray"
CROSS='\put(1, 6){\textcolor{'+CROSSCOLOR+'}{\rule{0.20pt}{3.0pt}}}\put(-5,12){\textcolor{'+CROSSCOLOR+'}{\rule{3.0pt}{0.20pt}}}'

@dataSeen = false

def isHRule(l)
  exp = /\\rule\[-0\.200pt\]\{(.*)pt\}\{0\.400pt\}\}/
  if (l =~ exp) && ($1.to_f > 200) && !@dataSeen
    return "#{$`}\\textcolor\{#{RULECOLOR}\}\{#{$&}\}#{$'}"
  else
    nil
  end
end

def isVRule(l)
  exp = /\\rule\[-0\.200pt\]\{0\.400pt\}\{(.*)pt\}\}/
  if (l =~ exp) && ($1.to_f > 150) && !@dataSeen
    return "#{$`}\\textcolor\{#{RULECOLOR}\}\{#{$&}\}#{$'}"
  else
    nil
  end
end

def patchLine(l)
  case
  when l =~ Regexp.new(Regexp.escape('$\Diamond$'))
    @dataSeen = true
    # replace crosses
    return "#{$`}#{CROSS}#{$'}"
  when f = isHRule(l) || isVRule(l)
    return f
  else 
    return l
  end
  exit 1
end

rawPlot.each do |l|  
  puts patchLine(l)
end



