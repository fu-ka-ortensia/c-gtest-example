#!/bin/bash

# C Test Project - ビルド・テスト・カバレッジ統合実行スクリプト

set -e

PROJECT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
BUILD_DIR="$PROJECT_DIR/build"
OUTPUT_DIR="$PROJECT_DIR/output/result"

echo ""
echo "╔════════════════════════════════════════════════════════════════╗"
echo "║           C Test Project - Build & Test & Coverage            ║"
echo "╚════════════════════════════════════════════════════════════════╝"
echo ""

# 1. ビルドディレクトリを準備
echo "📁 [1/5] ビルド環境を準備中..."
rm -rf "$BUILD_DIR"
mkdir -p "$BUILD_DIR"
cd "$BUILD_DIR"

# 2. CMake 設定とビルド（カバレッジフラグ付き）
echo "🔨 [2/5] CMake 設定とビルド中..."
cmake \
    -DCMAKE_CXX_FLAGS="--coverage" \
    -DCMAKE_C_FLAGS="--coverage" \
    .. > /dev/null 2>&1
cmake --build . > /dev/null 2>&1

# 3. テスト実行とテスト結果出力
echo "🧪 [3/5] テスト実行中..."
mkdir -p "$OUTPUT_DIR"

# テスト結果を XML と テキストで保存
ctest --output-on-failure \
      --output-junit "$OUTPUT_DIR/test-results.xml" \
      > "$OUTPUT_DIR/test-results.txt" 2>&1

# テスト結果をコンソールにも表示
ctest --output-on-failure

# 4. lcov カバレッジ取得
echo ""
echo "📊 [4/5] lcov カバレッジ取得中..."
cd "$BUILD_DIR"  # ビルドディレクトリに移動

# lcov でカバレッジ情報を収集（テスト実行後のデータから）
echo "カバレッジ情報を収集中..."
lcov --capture \
    --directory . \
    --output-file "$OUTPUT_DIR/coverage.info" \
    --ignore-errors mismatch \
    2>&1

# 不要なファイルをフィルター
echo "カバレッジレポートをフィルター中..."
lcov --remove "$OUTPUT_DIR/coverage.info" \
    '/usr/*' \
    '*/gtest/*' \
    '*/gmock/*' \
    '*/tests/*' \
    '*/GoogleTest/*' \
    --output-file "$OUTPUT_DIR/coverage_filtered.info" \
    --ignore-errors empty,unused \
    2>&1

# HTML レポートを生成
echo "HTML レポートを生成中..."
genhtml "$OUTPUT_DIR/coverage_filtered.info" \
    --output-directory "$OUTPUT_DIR/html" \
    --title "C Test Project - Code Coverage Report" \
    --legend \
    --ignore-errors empty \
    2>&1

echo ""
echo "カバレッジ取得が完了しました"

# 5. レポート確認
echo ""
echo "📄 [5/5] レポート確認中..."
cd "$PROJECT_DIR"  # プロジェクトディレクトリに戻る

echo ""
echo "╔════════════════════════════════════════════════════════════════╗"
echo "║                    ✅ すべてが完了しました！                   ║"
echo "╚════════════════════════════════════════════════════════════════╝"
echo ""
echo "📂 出力ファイル:"
echo "  📄 テスト結果: $OUTPUT_DIR/test-results.txt"
echo "  📋 テスト結果(XML): $OUTPUT_DIR/test-results.xml"
echo "  📊 カバレッジレポート(HTML): $OUTPUT_DIR/html/index.html"
echo ""
