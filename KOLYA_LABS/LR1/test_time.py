from main import Livenstein_matr, Livenstein_Damerau_matr, Livenstein_Damerau_recur
import ctypes, os
d = os.path.abspath(os.path.dirname(__file__))
d += "/libtick.so"
lib = ctypes.CDLL(d)

_tick = lib.tick
_tick = ctypes.c_ulonglong

CLOCKS_PER_SEC = 2.2e+6

N = 10

def proc_line(line):
    arr = line[:-1].split("\t")
    return arr[0], arr[1]

def test(s1, s2):
    t1 = _tick()
    for i in range(N):
        res= Livenstein_matr(s1, s2)
    t2 = _tick()
    time_l_m = (t2.value - t1.value)/N
    
    t1 = _tick()
    for i in range(N):    
        res = Livenstein_Damerau_matr(s1, s2)
    t2 = _tick()
    time_l_d_m = (t2.value - t1.value)/N
    
    t1 = _tick()
    for i in range(N):
        res = Livenstein_Damerau_recur(s1, s2)
    t2 = _tick()
    time_l_d_r = (t2.value - t1.value)/N
    
    return time_l_m, time_l_d_m, time_l_d_r
    
if __name__ == "__main__":
    f = open("test_time.txt", "r")
    lines = f.readlines()
    for line in lines:
        s1, s2 = proc_line(line)
        length = len(s1)
        _tick_l_m, _tick_l_d_m, _tick_l_d_r = test(s1, s2)
        print("длина слова -", length, "время Левенштейн -", _tick_l_m, "время Левенштейн-Дораму(итер) -", _tick_l_d_m, "время Левенштейн-Дораму(рекур) -", _tick_l_d_r)
