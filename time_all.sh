
echo "
msvc-debug"
time install/msvc-debug/bin/readjson-nlohmann.exe ./repodata.json

echo "
msvc-release"
time install/msvc-release/bin/readjson-nlohmann.exe ./repodata.json

echo "
clang-debug"
time install/clang-debug/bin/readjson-nlohmann.exe ./repodata.json

echo "
clang-release"
time install/clang-release/bin/readjson-nlohmann.exe ./repodata.json


