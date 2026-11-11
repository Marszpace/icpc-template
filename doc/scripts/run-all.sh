#!/usr/bin/env bash
DIR=${1:-.}

# use a precompiled header for the template to improve perf
# (LLINT=1 runs everything with #define int long long)
FLAGS="-Wall -Wfatal-errors -Wconversion -std=c++17 -O2 ${LLINT:+-DLLINT}"
g++ $FLAGS $DIR/stress-tests/utilities/template.h
trap "rm -f $DIR/stress-tests/utilities/template.h.gch" EXIT

tests="$(find $DIR/stress-tests -name '*.cpp')"
declare -i pass=0
declare -i fail=0
failTests=""
ulimit -s 524288 # For 2-sat test
for test in $tests; do
    echo "$(basename $test): "
    start=`date +%s.%N`
    # a test may list moduli: `// TEST_MODS: 998244353 1000000007` runs it once per
    # value, compiled with -DTEST_MOD=<value> (see content/number-theory/ModPow.h)
    mods="$(sed -n 's,^// TEST_MODS:,,p' $test | head -1)"
    [ -z "$mods" ] && mods="-"
    retCode=0
    for m in $mods; do
        d=""
        [ "$m" != "-" ] && d="-DTEST_MOD=$m"
        g++ $FLAGS $d $test && ./a.out
        r=$?
        if (($r != 0)); then retCode=$r; echo "Failed with mod $m"; fi
    done
    if (($retCode != 0)); then
        echo "Failed with $retCode"
        fail+=1
        failTests="$failTests$test\n"
    else
        pass+=1
    fi
    end=`date +%s.%N`
    runtime=$( echo "$end - $start" | bc -l )
    echo "Took $runtime seconds"
    rm -f a.out
    echo
done
echo "$pass/$(($pass+$fail)) tests passed"
if (($fail == 0)); then
    echo "No tests failed"
    exit 0
else
    echo -e "These tests failed: \n $failTests"
    exit 1
fi
