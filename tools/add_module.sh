#!/bin/bash

################################################################################
# add_module.sh
# 
# モジュール自動追加スクリプト
# 
# 使用法:
#   ./tools/add_module.sh moduleD
#   ./tools/add_module.sh moduleE
#
# 説明:
#   指定されたモジュール名で、target/jchg, tests, double のフォルダと
#   テンプレートファイルを自動生成します
#
################################################################################

set -e

# Color definitions for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

# Error handling
error() {
    echo -e "${RED}❌ エラー: $1${NC}" >&2
    exit 1
}

success() {
    echo -e "${GREEN}✅ $1${NC}"
}

info() {
    echo -e "${BLUE}ℹ️  $1${NC}"
}

warning() {
    echo -e "${YELLOW}⚠️  $1${NC}"
}

# Check arguments
if [ $# -ne 1 ]; then
    error "使用法: $0 <モジュール名>\n例: $0 moduleD"
fi

MODULE_NAME=$1

# Validate module name
if ! [[ $MODULE_NAME =~ ^[a-zA-Z][a-zA-Z0-9_]*$ ]]; then
    error "モジュール名は英数字とアンダースコアのみで始まる英字で始まる必要があります"
fi

# Get script directory
SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
PROJECT_ROOT="$( cd "$SCRIPT_DIR/.." && pwd )"

info "プロジェクトルート: $PROJECT_ROOT"
info "モジュール名: $MODULE_NAME"

# Define paths
TARGET_MODULE_DIR="$PROJECT_ROOT/target/jchg/$MODULE_NAME"
TEST_MODULE_DIR="$PROJECT_ROOT/tests/$MODULE_NAME"
DOUBLE_MODULE_DIR="$PROJECT_ROOT/double/$MODULE_NAME"

# Check if module already exists
if [ -d "$TARGET_MODULE_DIR" ]; then
    error "モジュール '$MODULE_NAME' は既に存在します: $TARGET_MODULE_DIR"
fi

if [ -d "$TEST_MODULE_DIR" ]; then
    error "テストフォルダは既に存在します: $TEST_MODULE_DIR"
fi

if [ -d "$DOUBLE_MODULE_DIR" ]; then
    error "スタブフォルダは既に存在します: $DOUBLE_MODULE_DIR"
fi

# Create directories
info "ディレクトリを作成しています..."
mkdir -p "$TARGET_MODULE_DIR"
mkdir -p "$TEST_MODULE_DIR"
mkdir -p "$DOUBLE_MODULE_DIR"
success "ディレクトリを作成しました"

# Process target/jchg files
info "target/jchg/$MODULE_NAME にファイルを生成しています..."

# Header file
TARGET_HEADER_TEMPLATE="$PROJECT_ROOT/target/jchg/_template/module_template.h"
TARGET_HEADER="$TARGET_MODULE_DIR/${MODULE_NAME}.h"
sed "s/template/$MODULE_NAME/g; s/TEMPLATE/$(echo $MODULE_NAME | tr '[:lower:]' '[:upper:]')/g" \
    "$TARGET_HEADER_TEMPLATE" > "$TARGET_HEADER"
success "作成: ${MODULE_NAME}.h"

# Source file
TARGET_SOURCE_TEMPLATE="$PROJECT_ROOT/target/jchg/_template/module_template.c"
TARGET_SOURCE="$TARGET_MODULE_DIR/${MODULE_NAME}.c"
sed -e "s/module_template\.h/${MODULE_NAME}\.h/g" \
    -e "s/template/${MODULE_NAME}/g" \
    "$TARGET_SOURCE_TEMPLATE" > "$TARGET_SOURCE"
success "作成: ${MODULE_NAME}.c"

# Process tests files
info "tests/$MODULE_NAME にファイルを生成しています..."

# Test file
TEST_TEMPLATE="$PROJECT_ROOT/tests/_template/test_module_template.cpp"
TEST_FILE="$TEST_MODULE_DIR/test_${MODULE_NAME}.cpp"
CLASS_NAME=$(echo ${MODULE_NAME^} | sed 's/_\([a-z]\)/\U\1/g')
# First replace module_template, then template, to avoid double replacement
sed -e "s/module_template\.h/${MODULE_NAME}\.h/g" \
    -e "s/template/${MODULE_NAME}/g" \
    -e "s/ModuleTemplate/${CLASS_NAME}/g" \
    "$TEST_TEMPLATE" > "$TEST_FILE"
success "作成: test_${MODULE_NAME}.cpp"

# CMakeLists.txt
CMAKE_TEMPLATE="$PROJECT_ROOT/tests/_template/CMakeLists.txt.template"
CMAKE_FILE="$TEST_MODULE_DIR/CMakeLists.txt"
sed "s/template/$MODULE_NAME/g" \
    "$CMAKE_TEMPLATE" > "$CMAKE_FILE"
success "作成: CMakeLists.txt"

# Process double files
info "double/$MODULE_NAME にファイルを生成しています..."

# Stub file
STUB_TEMPLATE="$PROJECT_ROOT/double/_template/module_stub_template.c"
STUB_FILE="$DOUBLE_MODULE_DIR/${MODULE_NAME}_stub.c"
sed "s/template/$MODULE_NAME/g" "$STUB_TEMPLATE" > "$STUB_FILE"
success "作成: ${MODULE_NAME}_stub.c"

# Update CMakeLists.txt in tests directory if not using auto-detection
if grep -q "add_subdirectory(moduleA)" "$PROJECT_ROOT/tests/CMakeLists.txt" 2>/dev/null; then
    info "tests/CMakeLists.txt に subdirectory を追加しています..."
    # Check if already added
    if ! grep -q "add_subdirectory($MODULE_NAME)" "$PROJECT_ROOT/tests/CMakeLists.txt"; then
        echo "add_subdirectory($MODULE_NAME)" >> "$PROJECT_ROOT/tests/CMakeLists.txt"
        success "tests/CMakeLists.txt に add_subdirectory($MODULE_NAME) を追加しました"
    fi
fi

echo ""
echo -e "${GREEN}════════════════════════════════════════════════════════════${NC}"
echo -e "${GREEN}✅ モジュール '$MODULE_NAME' の作成が完了しました!${NC}"
echo -e "${GREEN}════════════════════════════════════════════════════════════${NC}"
echo ""

echo "📋 作成されたファイル:"
echo "  target/jchg/$MODULE_NAME/"
echo "    ├── ${MODULE_NAME}.h"
echo "    └── ${MODULE_NAME}.c"
echo ""
echo "  tests/$MODULE_NAME/"
echo "    ├── test_${MODULE_NAME}.cpp"
echo "    └── CMakeLists.txt"
echo ""
echo "  double/$MODULE_NAME/"
echo "    └── ${MODULE_NAME}_stub.c"
echo ""

echo "📝 次のステップ:"
echo "  1. target/jchg/$MODULE_NAME/${MODULE_NAME}.c と ${MODULE_NAME}.h を編集してロジックを実装"
echo "  2. tests/$MODULE_NAME/test_${MODULE_NAME}.cpp にテストケースを追加"
echo "  3. 必要に応じて double/$MODULE_NAME/${MODULE_NAME}_stub.c でスタブを実装"
echo "  4. ビルド: cd build && cmake .. && make"
echo "  5. テスト実行: ctest --output-on-failure"
echo ""

echo "📖 詳細は doc/MODULE_ADD_GUIDE.md を参照してください"
echo ""
