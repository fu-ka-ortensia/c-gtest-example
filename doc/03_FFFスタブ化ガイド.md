# FFF スタブ化ガイド

## FFF（Fake Functions Framework）とは

FFF は、C/C++ でユニットテストを書く際に外部関数（スタブ）を簡単に作成できるフレームワークです。

## FFF の特徴

- **軽量**: ヘッダーのみの実装
- **簡単**: マクロベースで複雑な設定不要
- **柔軟**: 戻り値、引数、呼び出し回数を自由に制御
- **可視性**: スタブの呼び出し履歴を追跡可能

## FFF のインストール

本プロジェクトでは `/fff/fff.h` に FFF ヘッダーが配置されています。

## FFF の基本的な使い方

### 1. テストファイルでのセットアップ

```cpp
extern "C" {
    #include "moduleX.h"
    #define DEFINE_FFF_GLOBALS
    #include "fff.h"
    FAKE_VALUE_FUNC2(戻り値型, 関数名, 引数1型, 引数2型);
}

#include <gtest/gtest.h>
```

### 説明

- `extern "C"`: C 言語の関数宣言と互換性を持つブロック
- `#define DEFINE_FFF_GLOBALS`: グローバルスタブ変数を定義
- `#include "fff.h"`: FFF フレームワークを取り込み
- `FAKE_VALUE_FUNC2(...)`: スタブ関数を宣言

### 2. テストケースの基本形

```cpp
TEST_F(ModuleXTest, WithStub) {
    // 1. スタブをリセット
    RESET_FAKE(external_function);
    
    // 2. スタブの動作を設定
    external_function_fake.return_val = expected_value;
    
    // 3. 対象関数を呼び出し
    s4 result = moduleX_function_using_external();
    
    // 4. 検証
    EXPECT_EQ(expected_value, result);
    EXPECT_EQ(call_count, external_function_fake.call_count);
}
```

## FAKE_VALUE_FUNC マクロ

### マクロ種別

FFF では、関数の引数の数に応じて異なるマクロを使用します：

| マクロ | 引数数 | 戻り値 |
|--------|--------|--------|
| `FAKE_VOID_FUNC0` | 0 | なし |
| `FAKE_VOID_FUNC1` | 1 | なし |
| `FAKE_VALUE_FUNC0` | 0 | あり |
| `FAKE_VALUE_FUNC1` | 1 | あり |
| `FAKE_VALUE_FUNC2` | 2 | あり |
| `FAKE_VALUE_FUNC3` | 3 | あり |

### 引数の指定方法

```cpp
// 引数なし
FAKE_VOID_FUNC0(func_name);

// 1 引数
FAKE_VALUE_FUNC1(戻り値型, 関数名, 引数1型);

// 2 引数
FAKE_VALUE_FUNC2(戻り値型, 関数名, 引数1型, 引数2型);

// N 引数
FAKE_VALUE_FUNCN(戻り値型, 関数名, 引数1型, ..., 引数N型);
```

## スタブの状態制御

### return_val（戻り値の設定）

```cpp
external_function_fake.return_val = expected_value;
```

### arg0_val, arg1_val（引数の値を取得）

```cpp
s4 first_arg = external_function_fake.arg0_val;
s4 second_arg = external_function_fake.arg1_val;
```

### call_count（呼び出し回数の追跡）

```cpp
EXPECT_EQ(1, external_function_fake.call_count);
```

## テスト前の準備（RESET_FAKE）

RESET_FAKE は、スタブの状態を初期化します：

```cpp
RESET_FAKE(external_function);
```

リセット時に以下が初期化されます：

- `call_count` = 0
- `arg0_val` = 0
- `arg1_val` = 0
- `return_val` = 0

### 重要なポイント

**各テストの開始時に必ず RESET_FAKE を呼び出してください。** そうしないと、前のテストの状態が残ってしまい、テスト結果が不安定になります。

## C/C++ 互換性の取り扱い

### プロジェクトのルール

**target/ フォルダ内のファイル**（C ソースコード）:

```c
// C 言語ソースコード - extern "C" を入れない
#include "common.h"
u4 moduleX_function(u1* data, u4 length) { ... }
```

**tests/ フォルダ内のファイル**（C++ テストコード）:

```cpp
// C++ テストコード - extern "C" ブロックで C コードをラップ
extern "C" {
    #include "moduleX.h"
    #define DEFINE_FFF_GLOBALS
    #include "fff.h"
    FAKE_VALUE_FUNC2(u4, external_function, u1*, u4);
}
```

### 理由

- C と C++ は関数名エンコーディングが異なる（C++ は名前空間のためにマングリング）
- target/ ファイルは C 言語として一貫性を保つ
- tests/ ファイルで extern "C" を使用することで C/C++ 間の互換性を実現

## よくあるエラーと解決方法

### エラー 1: "undefined reference to external_function"

**原因**: スタブがリンクされていない

**確認項目**:
1. `DEFINE_FFF_GLOBALS` を定義しているか確認
2. `FAKE_VALUE_FUNC*` 宣言を確認
3. CMakeLists.txt でテストファイルがリンクされているか確認

### エラー 2: "call_count が 0"

**原因**: モジュール内で外部関数が呼ばれていない

**確認項目**:
1. 実装内で外部関数を呼んでいるか
2. 条件分岐で早期リターンしていないか

### エラー 3: "複数のテストで state が保持される"

**原因**: 前のテストで RESET_FAKE を呼んでいない

**解決方法**: 各テストの最初に RESET_FAKE を呼ぶ

```cpp
TEST_F(ModuleXTest, SomeTest) {
    RESET_FAKE(external_function);  // 必須
    // ... テスト処理
}
```

## 高度な FFF テクニック

### セットアップ/テアダウン関数の使用

複数のテストで共通の初期化が必要な場合：

```cpp
class ModuleXTest : public ::testing::Test {
protected:
    void SetUp() override {
        RESET_FAKE(external_function);
        external_function_fake.return_val = expected_value;
    }
};

TEST_F(ModuleXTest, SomeTest) {
    // SetUp で自動的に初期化される
}
```

### 複数のスタブを組み合わせる

```cpp
extern "C" {
    #include "moduleX.h"
    #define DEFINE_FFF_GLOBALS
    #include "fff.h"
    
    FAKE_VALUE_FUNC2(u4, external_func1, u1*, u4);
    FAKE_VALUE_FUNC1(s4, external_func2, s4);
}

TEST_F(ModuleXTest, MultipleStubs) {
    RESET_FAKE(external_func1);
    RESET_FAKE(external_func2);
    
    external_func1_fake.return_val = 100;
    external_func2_fake.return_val = 50;
    
    // ... テスト処理
}
```

## FFF に関する参考情報

- **FFF GitHub**: https://github.com/meekrosoft/fff
- **ドキュメント**: fff.h 内のコメントに詳細記載
