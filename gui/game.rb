class Game
  VALID_STATES = [:waitForRed, :waitForBlu, :gameOver]

  attr_accessor :redPlayer, :bluPlayer, :state

  def initialize(redPlayer, bluPlayer, startBoard, redStarts=true)
    @redPlayer = redPlayer
    @bluPlayer = bluPlayer
    @boards = [startBoard]
    if redStarts
      @state = :waitForRed
    else
      @state = :waitForBlu
    end   
  end

  def board
    @boards.last
  end
end
