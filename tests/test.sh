#!/bin/bash

set -o nounset
set -o errexit
set +e

TEST_DIR=`dirname "$0"`;
TEMP_DIR="$TEST_DIR/../tmp";
RESOURCE_DIR="$TEST_DIR/Resources";
TEST_CASES_DIR="$TEST_DIR/TestCases";
NODE=`which node`;

FAILURES=0;
TEST_COUNT=0;

function init {
    if [[ ! -x ../build/bin/irlib-plus ]]; then
        echo 'IrLib binary not found';
        exit 1;
    fi
}
function run {
    setup;

    if [ -z ${1+x} ]; then
        test;
    else
        SINGLE_TEST_CASE="$TEST_CASES_DIR/$1";
        performTestCase "$SINGLE_TEST_CASE";
    fi;

    tearDown;

    if [[ $FAILURES ]]; then
        echo "$FAILURES of $TEST_COUNT test cases failed";
    fi
}

function setup {
    cd $TEST_DIR;
    mkdir "$TEMP_DIR";
}
function tearDown {
    rm -r "$TEMP_DIR";
}

function performTestCase {
    if [[ -z ${1+x} ]]; then echo "Missing argument 1"; return; fi;

    TEST_CASE_PATH=$1;
    TEST_CASE_NAME=`basename "$TEST_CASE_PATH"`;
    INPUT_FILE="$TEST_CASE_PATH/input.xml";
    EXPECTED_OUTPUT_FILE="$TEST_CASE_PATH/output.xml";
    VARIABLES_FILE="$TEST_CASE_PATH/variables.js";

    let TEST_COUNT+=1;

    printf "Running case $TEST_CASE_NAME: ";

    ## Generate Script
    echo "" > "$TEMP_DIR/run.js";

    ## Generate Script: Load variables file if it is defined
    if [[ -f "$VARIABLES_FILE" ]]; then
        echo "var variables = require('$VARIABLES_FILE').variables;" >> "$TEMP_DIR/run.js";
    else
        echo "var variables = {}" >> "$TEMP_DIR/run.js";
    fi

    ## Generate Script: Load IrLib library
    echo "var IrLib = require('$RESOURCE_DIR/irlib.js');" >> "$TEMP_DIR/run.js";

    ## Generate Script: Let irlib-plus generate the blocks
    OUTPUT=`cat "$INPUT_FILE" | ../build/bin/irlib-plus`;
    echo "var templateBlocks = " >> "$TEMP_DIR/run.js";
    echo $OUTPUT >> "$TEMP_DIR/run.js";

    ## Generate Script: Create the view and render it
    echo "var view = new (IrLib.View.Template.extend({_templateBlocks: templateBlocks}))();" >> "$TEMP_DIR/run.js";
    echo "view.setVariables(variables);" >> "$TEMP_DIR/run.js";
    echo "console.log('' + view + '');" >> "$TEMP_DIR/run.js";

    ## Run the generated script
    NODE_OUTPUT=`$NODE "$TEMP_DIR/run.js"`;

    DIFF_OUTPUT=`echo $NODE_OUTPUT | diff "$EXPECTED_OUTPUT_FILE" -`;
    if [[ $DIFF_OUTPUT == "" ]]; then
        printf "Ok ✓";
    else
        echo "Failed ✗";
        echo "$DIFF_OUTPUT";
        let FAILURES+=1;
    fi

    echo "";
}

function test {
    for TEST_CASE_PATH in $TEST_CASES_DIR/*; do
        performTestCase "$TEST_CASE_PATH";
    done;
}


init;
run $@;
