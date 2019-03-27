from __future__ import division, print_function, absolute_import

import six

def convert_to_unicode(text):
    if six.PY3:
        if isinstance(text, str):
            return text
        elif isinstance(text, bytes):
            return text.decode("utf-8", "ignore")
        else:
            raise ValueError("Un supported string type")
    elif six.PY2:
        if isinstance(text, str):
            return text.decode("utf-8", "ignore")
        elif isinstance(text, unicode):
            return text
        else:
            raise ValueError("Un supported string type")
    else:
        raise ValueError("Un supported string type")

def convert_unicode_to_bytes(text):
    if six.PY3:
        return bytes(text, encoding="utf-8")
    elif six.PY2:
        return text.encode('utf-8', "ignore")
    else:
        raise ValueError("Un supported string type")