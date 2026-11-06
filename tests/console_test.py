import pathlib
import subprocess
import sys
import tempfile

def run(text,cwd,check=True):
    return subprocess.run([sys.argv[1]],input=text.encode(),cwd=cwd,capture_output=True,timeout=3,check=check)

with tempfile.TemporaryDirectory() as cwd:
    path=pathlib.Path(cwd,'tasks.txt')
    output=run('1\nLow\nL\n3\n1\nHigh\nH\n1\n2\n0\n',cwd).stdout.decode()
    assert 'Executing: High' in output
    assert path.read_text() == 'LOW\nLow\nL\n'
    output=run('3\n4\n0\nEdited\nNew description\n1\n2\n0\n',cwd).stdout.decode()
    assert 'Low' in output and 'Executing: Edited' in output
    assert path.read_text() == ''
    assert 'No pending tasks' in run('2\n0\n',cwd).stdout.decode()
    path.write_text('HIGH\nIncomplete\n')
    assert run('0\n',cwd,False).returncode != 0
    assert path.read_text() == 'HIGH\nIncomplete\n'
    path.write_text('UNKNOWN\nTitle\nDescription\n')
    assert run('0\n',cwd,False).returncode != 0
    path.write_text('')
    assert run('invalid\n',cwd).returncode == 0
print('PASS: priority execution, edit, persistence, no resurrection, corruption and EOF')
