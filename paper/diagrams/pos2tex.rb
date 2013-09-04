DEFAULT_SIZE = 3.425

def displayBoard(id, rating, stream=STDOUT, size=DEFAULT_SIZE)
  pos2tex(id, rating, boardID2pos(id), stream, size)
end

def pos2tex(id, rating, pos, stream=STDOUT, size=DEFAULT_SIZE)
  caption = "$p(#{id})=#{(rating*100).to_s[0..5]}\\%$"
  board2tex(caption, pos, stream, size)
end

def board2tex(caption, pos, stream=STDOUT, size=DEFAULT_SIZE, markGoal=false)
  posPlus = []
  posPlus[0 + 0 * 5] = pos[0]
  posPlus[1 + 0 * 5] = pos[1]
  posPlus[2 + 0 * 5] = pos[2]
  posPlus[0 + 1 * 5] = pos[3]
  posPlus[1 + 1 * 5] = pos[4]
  posPlus[0 + 2 * 5] = pos[5]
  posPlus[3 + 3 * 5] = pos[6]
  posPlus[4 + 2 * 5] = pos[7]
  fullBoard2tex(caption, posPlus, stream, size, markGoal)
end

def fullBoard2tex(caption, pos, stream=STDOUT, size=DEFAULT_SIZE, markGoal=false)
  stream.puts <<HERE
  \\subfigure[#{caption}] {
    \\begin{pgfpicture}{0cm}{0cm}{#{size}cm}{#{size}cm}
      \\color{black!25}
      \\pgfmoveto{\\pgfxy(#{4.0*size/5},#{0.0*size/5})}
      \\pgflineto{\\pgfxy(#{5.0*size/5},#{0.0*size/5})}
      \\pgflineto{\\pgfxy(#{5.0*size/5},#{1.0*size/5})}
      \\pgflineto{\\pgfxy(#{4.0*size/5},#{1.0*size/5})}
      \\pgfclosepath
      \\pgffill
      \\color{black}
      \\pgfxyline(#{0.0*size/5},0)(#{0.0*size/5},#{size})
      \\pgfxyline(#{1.0*size/5},0)(#{1.0*size/5},#{size})
      \\pgfxyline(#{2.0*size/5},0)(#{2.0*size/5},#{size})
      \\pgfxyline(#{3.0*size/5},0)(#{3.0*size/5},#{size})
      \\pgfxyline(#{4.0*size/5},0)(#{4.0*size/5},#{size})
      \\pgfxyline(#{5.0*size/5},0)(#{5.0*size/5},#{size})
      \\pgfxyline(0,#{0.0*size/5})(#{size},#{0.0*size/5})
      \\pgfxyline(0,#{1.0*size/5})(#{size},#{1.0*size/5})
      \\pgfxyline(0,#{2.0*size/5})(#{size},#{2.0*size/5})
      \\pgfxyline(0,#{3.0*size/5})(#{size},#{3.0*size/5})
      \\pgfxyline(0,#{4.0*size/5})(#{size},#{4.0*size/5})
      \\pgfxyline(0,#{5.0*size/5})(#{size},#{5.0*size/5})
HERE
  25.times do |i|
    x = i % 5
    y =  4 - (i / 5)                    
    stream.puts "      \\pgfputat{\\pgfxy(#{(x+0.5)*size/5},#{(y+0.5)*size/5})}{\\pgfbox[center,center]{#{pos[i]}}}" if pos[i]                    
  end

  stream.puts <<HERE
    \\end{pgfpicture}
  }
HERE
end
