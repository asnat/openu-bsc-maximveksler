package lecture11;

class PreciseTime extends Time {
    private int _second;
    
        public PreciseTime(int h, int m, int s) {
                super(h, m);
                _second = s;
            }
      
            public void advanceSeconds (int s) {
                    int advMinutes = s / 60;
                    _second += s % 60;
                    if (_second < 0) {
                          advMinutes--;
                         _second += 60;
                   }
                   else  if  (_second >= 60) {
                        advMinutes++;
                        _second -= 60;
                   }
                   advanceMinutes(advMinutes);
           }
}          
     
