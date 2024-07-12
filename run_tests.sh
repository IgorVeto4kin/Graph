TEST_DIR="./tests"
INPUT_DIR="$TEST_DIR/inputs"
OUTPUT_DIR="$TEST_DIR/outputs"
TEMP_OUTPUT="$TEST_DIR/temp_output.txt"

# Флаг успешности всех тестов
ALL_TESTS_PASSED=true

for input_file in $INPUT_DIR/*; do
    test_name=$(basename "$input_file")
    
    ./build/main < "$input_file" > "$TEMP_OUTPUT"
    
    # Сравниваем результат с ожидаемым выводом
    if diff -Bb "$TEMP_OUTPUT" "$OUTPUT_DIR/$test_name" > /dev/null; then
        echo "Test $test_name PASSED"
    else
        echo "Test $test_name FAILED"
        diff "$TEMP_OUTPUT" "$OUTPUT_DIR/$test_name"
        ALL_TESTS_PASSED=false
    fi
done

# Завершаем с соответствующим кодом возврата
if $ALL_TESTS_PASSED; then
    exit 0
else
    exit 1
fi
