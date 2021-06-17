while (true) 
do
  nohup ./rzrmud config.xyj
  sleep 5
  pkill rzrmud
  sleep 5
  pkill -9 rzrmud
  sleep 5
done
