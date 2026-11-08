mkdir -p build
FILE="$1"
echo "
#include \"../doc/scripts/prelude.h\"
#include \"../$FILE\"
signed main() {}
" >build/temp.cpp
g++ -Wall -Wextra -Wfatal-errors -Wconversion -std=c++17 ${LLINT:+-DLLINT} build/temp.cpp && rm a.out build/temp.cpp
