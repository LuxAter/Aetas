import signal

class Timeout:
    def __init__(self, seconds=1, error_message='Timeout'):
        self.seconds = seconds
        self.error_message = error_message
    def handle_timeout(self, signum, frame):
        raise TimeoutError(self.error_message)
    def __enter__(self):
        signal.signal(signal.SIGALRM, self.handle_timeout)
        signal.setitimer(signal.ITIMER_REAL, self.seconds)
    def __exit__(self, type, value, traceback):
        signal.setitimer(signal.ITIMER_REAL, 0)

class _Getch:
    def __init__(self):
        try:
            self.impl = _GetchWindows()
        except ImportError:
            self.impl = _GetchUnix()
    def __call__(self):
        return self.impl()

class _GetchUnix:
    def __init__(self):
        import tty, sys

    def __call__(self):
        import sys, tty, termios
        fd = sys.stdin.fileno()
        old_settings = termios.tcgetattr(fd)
        try:
            tty.setraw(sys.stdin.fileno())
            ch = sys.stdin.read(1)
        finally:
            termios.tcsetattr(fd, termios.TCSADRAIN, old_settings)
        return ch

class _GetchWindows:
    def __init__(self):
        import msvcrt

    def __call__(self):
        import msvcrt
        return msvcrt.getch()

getch = _Getch()

def timeout(sec):
    if sec is None:
        sec = 1
    try:
        with Timeout(sec):
            return getch()
    except:
        pass
    return None

def input(position):
    ch = getch()
    if ch == 'w':
        return 0
    elif ch == 's':
        return 1
    elif ch == 'd':
        return 2
    elif ch == 'a':
        return 3
    elif ch == 'q':
        return -1

prev = -2

def input_time(position):
    global prev
    if prev == -2:
        ch = getch()
        if ch == 'w':
            prev = 0
            return 0
        elif ch == 's':
            prev = 1
            return 1
        elif ch == 'd':
            prev = 2
            return 2
        elif ch == 'a':
            prev = 3
            return 3
        elif ch == 'q':
            prev = -1
            return -1
    ch = timeout(0.1)
    if ch == 'w':
        prev = 0
        return 0
    elif ch == 's':
        prev = 1
        return 1
    elif ch == 'd':
        prev = 2
        return 2
    elif ch == 'a':
        prev = 3
        return 3
    elif ch == 'q':
        prev = -1
        return -1
    else:
        return prev
