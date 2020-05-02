// sinbrive 2020

class Led {
  private:
    int _state = 0xFF;
    int _statebis = 0;
    int _pin;
    bool _blink;
    int _to;
    long _t, _t1, _t0;
    int _nb, _n;

  public:
    Led(int pin) {
      _pin = pin;
      pinMode(_pin, OUTPUT);
    }
    
    void off() {
      _state = 0;
    }

    void on() {
      _state = 1;
    }

    void blink(int t) {
      _state = 2;
      _blink = false;
      _to = t;
    }

    void animation(int n, int t1, int t0) {
      // n number of flash, t1 frequencey, t0 duration of pause
      // _|-|_|-|_|-|_|-|___________|-|_|-|_|-|_|-|___________
      //  ^---^ 2*t1         ^t0     ^------------^ n=4
      _state = 4;
      _n = 2 * n;
      _t1 = t1;
      _t0 = t0;
      _nb = n;
    }

    void fsm() {
      switch (_state) {
        // off
        case 0:
          digitalWrite(_pin, LOW);
          _state = 0xFF; // do it only once
          break;
        // on
        case 1:
          digitalWrite(_pin, HIGH);
          _state = 0xFF; // do it only once
          break;
        // blink
        case 2:
          _blink = !_blink;
          digitalWrite(_pin, _blink ? HIGH : LOW);
          _state = 3;
          _t = millis();
          break;
        case 3:
          if ((millis() - _t) >= _to) _state = 2;
          break;
        // animation
        case 4:
          if (_nb-- > 0) {
            _blink = !_blink;
            digitalWrite(_pin, _blink ? HIGH : LOW);
            _state = 5;
            _t = millis();
          } else {
            _state = 6;
            _t = millis();
            digitalWrite(_pin, LOW);
          }
          break;
        case 5: if ((millis() - _t) >= _t1) _state = 4;
          break;
        case 6:
          if ((millis() - _t) >= _t0) {
            _state = 4;
            _nb = _n;  // do it again and again
          }
          break;
        default: break;
      }
    }
};
