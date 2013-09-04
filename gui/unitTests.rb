#!/usr/bin/ruby
require 'test/unit'

require 'game'

class TestGame < Test::Unit::TestCase
  class MockPlayer
  end

  class MockGame
  end

  def setup
    @redPlayer = MockPlayer.new
    @bluPlayer = MockPlayer.new
    @board = MockGame.new
    @game = Game.new(@redPlayer, @bluPlayer, @board)
  end

  def testConstructor
    assert_equal(@redPlayer,  @game.redPlayer)
    assert_equal(@bluPlayer,  @game.bluPlayer)
    assert_equal(:waitForRed, @game.state)
  end

  def testScenario

  end
end
