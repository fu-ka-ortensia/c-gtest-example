# C Test Project

GoogleTest と lcov を使用した C プロジェクトのユニットテスト環境です。

## 📋 プロジェクト構成

```
c_test_prj/
├─ target/jchg/          # テスト対象のC ソースコード
│  ├─ moduleA/
│  ├─ moduleB/
│  └─ moduleC/
├─ tests/                # テストコード
│  ├─ moduleA/
│  ├─ moduleB/
│  └─ moduleC/
├─ double/               # スタブ関数
├─ fff/                  # fff.h (Mock フレームワーク)
├─ GoogleTest/           # GoogleTest ライブラリ
├─ output/result/        # テスト結果・カバレッジレポート出力
├─ CMakeLists.txt        # ビルド設定
└─ build.sh              # 統合実行スクリプト
```

## 🚀 クイックスタート

### 1. ビルド・テスト・カバレッジレポート生成

```bash
bash build.sh
```

このコマンドで以下が自動実行されます：
- CMake ビルド（カバレッジフラグ付き）
- GoogleTest テスト実行（20個全実行）
- lcov カバレッジデータ収集
- HTML レポート生成

### 2. テスト結果確認

```bash
cat output/result/test-results.txt
```

### 3. カバレッジレポート確認

ブラウザで以下を開いてください：

```
output/result/html/index.html
```

## 📊 テスト統計

| 項目 | 内容 |
|------|------|
| テストスイート | 3 (moduleA, moduleB, moduleC) |
| テストケース | 20 個 |
| 成功率 | 100% |
| 行カバレッジ | 100.0% (21/21 行) |
| 関数カバレッジ | 50.0% (7/14 関数) |

## 🧪 各モジュール説明

### ModuleA: 基本算術演算
- `add(s4 a, s4 b)` - 加算
- `multiply(s4 a, s4 b)` - 乗算
- **テスト数:** 4

### ModuleB: 除算・減算
- `divide(s4 a, s4 b)` - 整数除算
- `subtract(s4 a, s4 b)` - 減算
- **テスト数:** 5

### ModuleC: 統合・検証・正規化
- `integrate()` - A, B の統合
- `validate()` - 入力検証
- `normalize()` - 値の正規化
- **テスト数:** 11

## 📁 出力ファイル

`output/result/` ディレクトリに以下が生成されます：

- **test-results.txt** - テスト実行結果（テキスト形式）
- **test-results.xml** - テスト実行結果（XML 形式、CI/CD 用）
- **coverage.info** - lcov カバレッジデータ
- **coverage_filtered.info** - フィルター済みカバレッジデータ
- **html/index.html** - カバレッジレポート（HTML 形式）
  - moduleA/index.html - moduleA の詳細レポート
  - moduleB/index.html - moduleB の詳細レポート
  - moduleC/index.html - moduleC の詳細レポート

## 🔧 必要なツール

- CMake 3.10 以上
- GCC 4.8 以上（カバレッジサポート）
- lcov 1.14 以上
- genhtml（lcov に含まれる）

## 📝 カスタマイズ

### テストの追加

1. `tests/moduleX/test_moduleX.cpp` でテストを追加
2. `bash build.sh` を実行

### カバレッジフラグの変更

`CMakeLists.txt` または `build.sh` を編集してください。

## ⚙️ トラブルシューティング

### ビルドエラーが出る場合
```bash
rm -rf build && bash build.sh
```

### テストが実行されない場合
```bash
cd build && ctest --verbose
```

### HTML レポートが表示されない場合
- ブラウザのキャッシュをクリア
- 別のブラウザで試す

## 📄 ライセンス

GoogleTest は Apache License 2.0
fff は MIT License
