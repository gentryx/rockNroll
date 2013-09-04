task :default => :cd

task :cd do
  cdpath = "/tmp/rockNrollCD"
  rm_rf cdpath
  sh "svn checkout svn+ssh://wintermute/home/gentryx/fin/svn/rockNroll/trunk #{cdpath}/trunk"
  cp "paper/rockNrollOnline.pdf", cdpath
  cp "paper/rockNrollPrint.pdf", cdpath
  sh "find #{cdpath} -name .svn -exec rm -rf {} \\; || echo ok"
  rm_rf "#{cdpath}/trunk/todo"
  mkdir "#{cdpath}/rockNroll"
  sh "cp /home/gentryx/rockNrollOlde/* #{cdpath}/rockNroll"
end
