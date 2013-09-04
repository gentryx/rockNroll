class Board
  def initialize(pos)    
    self.pos = pos
  end

  attr_reader :pos

  def pos=(newPos)
    checkPos(newPos)
    @pos = newPos
  end

  private

  def checkPos(pos = @positions)
    #todo: fail if bad input
  end

  
end
