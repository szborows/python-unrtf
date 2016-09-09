#!/usr/bin/env python3
#-*- coding: utf-8 -*-

import os
import sys
from contextlib import contextmanager
import _unrtf

@contextmanager
def stdoutRedirected(to=os.devnull):
    fd = sys.stdout.fileno()

    def _redirect_stdout(to):
        sys.stdout.close()
        os.dup2(to.fileno(), fd)
        sys.stdout = os.fdopen(fd, 'w')

    with os.fdopen(os.dup(fd), 'w') as old_stdout:
        with open(to, 'w') as file:
            _redirect_stdout(to=file)
        try:
            yield
        finally:
            _redirect_stdout(to=old_stdout)

def unrtf(rtf_data, output_file, no_pict_mode=True):
    assert rtf_data is not None
    if rtf_data.strip() == '':
        return ''
    with stdoutRedirected(to=output_file):
        _unrtf.unrtf(rtf_data, no_pict_mode)
