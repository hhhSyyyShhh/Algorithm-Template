from pathlib import Path
import subprocess, tempfile, shutil
root=Path(__file__).resolve().parent
compiler=shutil.which('clang++') or shutil.which('g++')
if not compiler: raise SystemExit('请先安装支持 C++17 的编译器')
files=sorted(root.rglob('*.cpp'))
with tempfile.TemporaryDirectory() as temp:
    for i,p in enumerate(files):
        binary=str(Path(temp)/str(i))
        subprocess.run([compiler,'-std=c++17','-Wall','-Wextra','-pedantic',str(p),'-o',binary],check=True)
        subprocess.run([binary],check=True,timeout=10,capture_output=True)
        print('PASS',p.relative_to(root))
print(f'通过 {len(files)} 个独立程序的编译与示例断言。')
