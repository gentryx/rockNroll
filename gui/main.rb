#!/usr/bin/ruby

require 'Qt'

a = Qt::Application.new(ARGV)

require 'rocknrollFull'
w = RockNRollFull.new
w.show

class TimerHack < Qt::Widget

  slots 'timeout()'

  def initialize
    super
    timer = Qt::Timer.new( self )
    connect( timer, SIGNAL( 'timeout()' ), SLOT( 'timeout()' ) )
    timer.start(0)
  end

  def timeout
    sleep 0.01
  end
  
end
timerHack = TimerHack.new

#Thread.new do
#  loop do
#    sleep 0.05
#    begin
#      w.board.ping
#    rescue Exception => e
#      puts "boom: #{e}"
#    end
#  end
#end

puts "start"

a.setMainWidget(w)
a.exec()

