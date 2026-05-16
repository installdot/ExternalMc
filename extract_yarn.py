import gzip
import shutil

with gzip.open('yarn.gz', 'rb') as f_in:
    with open('yarn.tiny', 'wb') as f_out:
        shutil.copyfileobj(f_in, f_out)
