require 'Qt'

class BoardDisplay < Qt::Widget
  signals 'clicked()'
#  slots 'ping()'
  slots 'showBoard(Board)'

  def paintEvent(e)
    area = e.rect
    sx = area.left();
    sy = area.top();
    sw = area.width(); 
    sh = area.height(); 

    if (!area.intersects(rect())) then
      puts "no repaint necessary!"
      return
    end

    if contentChanged
      contentChanged = false
      paintState
    end

    bitBlt(self, sx, sy, @bufferFrame, sx, sy, sw, sh, Qt::CopyROP)
  end

  def resizeEvent(e)
    puts "resize"
    createBufferFrame
  end

  def initialize(parent, name)
    super(parent, name, Qt::WRepaintNoErase)
    @counter = 0
    createBufferFrame
    @contentChanged = true
    @board = nil
    @backgroundColor = Qt::Color.new(230, 230, 255)
    @fieldColor      = Qt::Color.new(210, 210, 225)
    @redCol          = Qt::Color.new(230, 100,  50)
    @bluCol          = Qt::Color.new(0  , 150, 185)
  end
  
  def showBoard(board)
    puts "showBoard()"
    @board = board
    contentChangedUpdate
  end

  def contentChangedUpdate
    @contentChanged = true
    update    
  end

#  def ping    
#     @content = (@content + 1) % 200
#     @contentChanged = true
#     update

#     puts "ping #{Time.now}" if @content % 80 == 0
#  end

  def mousePressEvent(e)
    emit clicked()
  end

  private 
  
  attr_accessor :contentChanged

  def drawRect(y, x, color, radius=0, offset=0, text="") 
    w = width
    h = height
    sx = (x+0) * w / 5 + offset
    sy = (y+0) * h / 5 + offset
    ex = (x+1) * w / 5 - offset
    ey = (y+1) * h / 5 - offset

    @painter.setPen(color)
    @painter.setBrush(color)
    @painter.drawRoundRect(sx, sy, ex-sx, ey-sy, radius, radius)
    @painter.setPen(Qt::Color.new(255, 255, 255))
    @painter.setBrush(Qt::Color.new(255, 255, 255))

    f = font
    s = [ex-sx, ey-sy].min - 2 * offset
    f.setPixelSize(s)
    @painter.setFont(f)

    @painter.drawText(0.75 * sx + 0.25 * ex, 0.15 * sy + 0.85 * ey, text)
  end

  def drawField(y, x, color)
    drawRect(y, x, color)
  end

  def drawStone(y, x, color, num)
    drawRect(y, x, color, 20, 1, "#{num}")
  end    

  def paintState
    @bufferFrame.fill(@backgroundColor)
    [
      [0, 0],         [0, 2],         [0, 4],


              [1, 1],         [1, 3], 


      [2, 0],         [2, 2],         [2, 4],


              [3, 1],         [3, 3], 


      [4, 0],         [4, 2],         [4, 4]
    ].each do |f|
      drawField(f[0], f[1], @fieldColor)
    end  

    if @board
      [:red, :blu].each do |p|
        if p == :red
          col = @redCol
        else
          col = @bluCol
        end
        6.times do |s|
          pos = @board.pos[p][s]
          drawStone(pos[0], pos[1], col, s)
        end
      end
    end
  end

  def createBufferFrame
    @bufferFrame = Qt::Pixmap.new(rect.size)
    @painter = Qt::Painter.new(@bufferFrame)
  end
end
