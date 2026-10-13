import json
import pathlib
import re
import subprocess
import sys
import tempfile

exe = sys.argv[1]

def run(*args):
    return subprocess.run([exe, *args], capture_output=True, text=True, timeout=10)

assert run('--help').returncode == 0
for args in [
    ['--minx', '10', '--maxx', '10'], ['--maxx', '-1'],
    ['--points', '0'], ['--points', '-1'], ['--pop', 'abc'],
    ['--pop', '10junk'], ['--pop', '999999999999999999999'],
    ['--gen', '0'], ['--cross', '101'], ['--mut', '-1'],
    ['--fdist', 'nan'], ['--fdist', 'inf'], ['--fdist', '-1'],
    ['--fdist', '0', '--fdist2', '0'], ['--fdist2', 'junk'],
    ['--minx', '-2147483648', '--maxx', '2147483647'],
]:
    result = run(*args)
    assert result.returncode != 0, args
    assert 'error:' in result.stderr, (args, result.stderr)
    assert 'Best individual' not in result.stdout, args

for selection in ['roulette', 'hybrid']:
    assert run('--points', '1', '--maxx', '1', '--maxy', '1',
               '--sel', selection, '-g', '2').returncode == 0

with tempfile.TemporaryDirectory() as directory:
    for crossover in ['random', 'sequential']:
        report = pathlib.Path(directory) / 'report.html'
        result = run('--minx', '100', '--maxx', '110', '--miny', '1',
                     '--maxy', '3', '-m', '100', '-c', '100', '-g', '10',
                     '--ctype', crossover, '--html', str(report))
        assert result.returncode == 0, result.stderr
        data = json.loads(re.search(r'const D = (.*);', report.read_text()).group(1))
        assert len(data['generations']) == 10
        for generation in data['generations']:
            for x, y in generation['individuals']:
                assert 100 <= x <= 110 and 1 <= y <= 3, (x, y)
print('CLI regressions passed')
