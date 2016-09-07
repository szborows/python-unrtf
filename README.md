python-unrtf
============

`python3` bindings for `unrtf` GNU tool

usage
-----

```python
import unrtf
with open('file.rtf') as fp:
    unrtf.unrtf(fp.read(), 'out.html')
```

installation
------------

seek guidance from `Dockerfile`
