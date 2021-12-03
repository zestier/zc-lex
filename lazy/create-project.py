import os
import pathlib
import subprocess

projectDir = pathlib.Path(__file__).resolve().parents[1]
localProjects = [x for x in projectDir.parent.iterdir() if x.is_dir() and x != projectDir]

cmakeArgs = ['cmake', '-B', 'build', '-S', '.']
for localProject in localProjects:
    cmakeArgs.append('-D')
    cmakeArgs.append(f'CPM_{localProject.name}_SOURCE={localProject.as_posix()}')

# Turn on tests
cmakeArgs.extend(['-D', 'ZC_LEX_BUILD_TESTS=ON'])

subprocess.call(
    cmakeArgs,
    cwd=projectDir
)
