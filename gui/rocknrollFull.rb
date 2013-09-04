require 'boardDisplay'
require 'rocknroll'
require 'board'

class RockNRollFull < RockNRoll
  def fileNew()
    pos = { 
      :red => [
        [0,0], [0,1], [0,2], [1,0], [1,1], [2,0]
      ],
      :blu => [
        [4,4], [4,3], [4,2], [3,4], [3,3], [2,4]
      ]
    }
    @board.showBoard(Board.new(pos))
  end

  def keyPressEvent(e)
#    @board.ping if @board
  end
end
