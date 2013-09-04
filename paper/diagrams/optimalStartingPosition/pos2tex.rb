def pos2tex(id, rating, pos, size, stream)
  stream.puts <<HERE
  \\subfigure[$p(#{id})=#{(rating*100).to_s[0..5]}\\%$] {
    \\begin{pgfpicture}{0cm}{0cm}{#{size}cm}{#{size}cm}
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
      \\pgfputat{\\pgfxy(#{0.5*size/5},#{4.5*size/5})}{\\pgfbox[center,center]{#{pos[0]}}}
      \\pgfputat{\\pgfxy(#{1.5*size/5},#{4.5*size/5})}{\\pgfbox[center,center]{#{pos[1]}}}
      \\pgfputat{\\pgfxy(#{2.5*size/5},#{4.5*size/5})}{\\pgfbox[center,center]{#{pos[2]}}}
      \\pgfputat{\\pgfxy(#{0.5*size/5},#{3.5*size/5})}{\\pgfbox[center,center]{#{pos[3]}}}
      \\pgfputat{\\pgfxy(#{1.5*size/5},#{3.5*size/5})}{\\pgfbox[center,center]{#{pos[4]}}}
      \\pgfputat{\\pgfxy(#{0.5*size/5},#{2.5*size/5})}{\\pgfbox[center,center]{#{pos[5]}}}
    \\end{pgfpicture}
  }
HERE
end

