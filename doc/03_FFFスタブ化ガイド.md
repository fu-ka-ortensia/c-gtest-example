# FFF スタブ化ガイド

## FFF（Fake Functions Framework）とは

FFF は、C/C++ でユニットテストを書く際に外部関数（スタブ）を簡単に作成できるフレームワークです。本プロジェクトでは、moduleC の `u4g_mem_wirte` 関数をスタブ化するために使用しています。

## FFF の特徴

- **軽量**: ヘッダーのみの実装
- **簡単**: マクロベースで複雑な設定不要
- **柔軟**: 戻り値、引数、呼び出し回数を自由に制御
- **可視性**: スタブの呼び出し履歴を追跡可能

## FFF のインストール

本プロジェクトでは `/fff/fff.h` に FFF ヘッダーが配置されています。

## moduleC での FFF 使用例

### 1. 基本的なセットアップ

**test_moduleC.cpp**

```cpp
extern "C" {
    #include "moduleC.h"
    #include "u4g_mem.h"
    #define DEFINE_FFF_GLOBALS
    #include "fff.h"
    FAKE_VALUE_FUNC2(u4, u4g_mem_wirte, u1*, u4);
}

#include <gtest/gtest.h>
```

### 説明

- `extern "C"`: C 言語の関数宣言と互換性を持つブロック
- `#define DEFINE_FFF_GLOBALS`: グローバルスタブ変数を定義
- `#include "fff.h"`: FFF フレームワークを取り込み
- `FAKE_VALUE_FUNC2(戻り値型, 関数名, 引数1型, 引数2型)`: 2 引数のスタブを宣言

### 2. テストケースの基本形

```cpp
TEST(ModuleCTest, WriteDataSuccess) {
    // 1. スタブをリセット
    RESET_FAKE(u4g_mem_wirte);
    
    // 2. スタブの動作を設定
    u4g_mem_wirte_fake.return_val = 4;
    
    // 3. 対象関数を呼び出し
    u1 test_data[4] = {1, 2, 3, 4};
    u4 result = moduleC_write_data(test_data, 4);
    
    // 4. 検証
    EXPECT_EQ(4, result);                            // 戻り値チェック
    EXPECT_EQ(1, u4g_mem_wirte_fake.call_count);    // 呼び出し回数チェック
}
```

## FAKE_VALUE_FUNC マクロ

### マクロ種別

FFF では、関数の引数の数に応じて異なるマクロを使用します：

| マクロ | 引数数 | 戻り値 | 使用例 |
|--------|--------|--------|--------|
| `FAKE_VOID_FUNC0` | 0 | なし | `FAKE_VOID_FUNC0(init_system);` |
| `FAKE_VOID_FUNC1` | 1 | なし | `FAKE_VOID_FUNC1(void*, data);` |
| `FAKE_VALUE_FUNC0` | 0 | あり | `FAKE_VALUE_FUNC0(int, get_status);` |
| `FAKE_VALUE_FUNC1` | 1 | あり | `FAKE_VALUE_FUNC1(int, set_param, int);` |
| `FAKE_VALUE_FUNC2` | 2 | あり | `FAKE_VALUE_FUNC2(u4, u4g_mem_wirte, u1*, u4);` |
| `FAKE_VALUE_FUNC3` | 3 | あり | `FAKE_VALUE_FUNC3(int, calc, int, int, int);` |

### 引数の指定方法

- **引数なし**: `FAKE_VOID_FUNC0(func_name)`
- **1 引数**: `FAKE_VOID_FUNC1(戻り値型, 関数名, 引数1型)`
- **2 引数**: `FAKE_VALUE_FUNC2(戻り値型, 関数名, 引数1型, 引数2型)`
- **N 引数**: `FAKE_VALUE_FUNCN(戻り値型, 関数名, 引数1型, ..., 引数N型)`

## スタブの状態制御

### return_val（戻り値の設定）

```cpp
// 単一の戻り値を設定
u4g_mem_wirte_fake.return_val = 4;

// テスト実行
u4 result = moduleC_write_data(test_data, 4);
EXPECT_EQ(4, result);
```

### arg0_val, arg1_val（引数の値を取得）

```cpp
TEST(ModuleCTest, WriteDataCheckArguments) {
    RESET_FAKE(u4g_mem_wirte);
    u4g_mem_wirte_fake.return_val = 4;
    
    u1 test_data[4] = {10, 20, 30, 40};
    moduleC_write_data(test_data, 4);
    
    // 第 1 引数（ポインタ）を取得
    u1* received_data = (u1*)u4g_mem_wirte_fake.arg0_val;
    EXPECT_EQ(10, received_data[0]);
    
    // 第 2 引数（長さ）を取得
    u4 received_length = u4g_mem_wirte_fake.arg1_val;
    EXPECT_EQ(4, received_length);
}
```

### call_count（呼び出し回数の追跡）

```cpp
TEST(ModuleCTest, WriteDataMultipleCalls) {
    RESET_FAKE(u4g_mem_wirte);
    u4g_mem_wirte_fake.return_val = 2;
    
    // 1 回目の呼び出し
    u1 data1[2] = {1, 2};
    moduleC_write_data(data1, 2);
    EXPECT_EQ(1, u4g_mem_wirte_fake.call_count);
    
    // 2 回目の呼び出し
    u1 data2[2] = {3, 4};
    moduleC_write_data(data2, 2);
    EXPECT_EQ(2, u4g_mem_wirte_fake.call_count);
}
```

## テスト前の準備（RESET_FAKE）

RESET_FAKE は、スタブの状態を初期化します：

```cpp
RESET_FAKE(u4g_mem_wirte);
```

リセット時に以下が初期化されます：

- `call_count` = 0
- `arg0_val` = 0
- `arg1_val` = 0
- `return_val` = 0
- 引数履歴（複数呼び出しの場合）

### 重要なポイント

**各テストの開始時に必ず RESET_FAKE を呼び出してください。** そうしないと、前のテストの状態が残ってしまい、テスト結果が不安定になります。

## moduleC_write_data のスタブ化例

### 実装のポイント

**moduleC.c** の実装例：

```c
u4 moduleC_write_data(u1* data, u4 length) {
    if (data == NULL || length == 0) {
        return 0;
    }
    return u4g_mem_wirte(data, length);
}
```

**test_moduleC.cpp** のテスト例：

```cpp
// テスト 1: 正常系
TEST(ModuleCTest, WriteDataSuccess) {
    RESET_FAKE(u4g_mem_wirte);
    u4g_mem_wirte_fake.return_val = 4;
    
    u1 test_data[4] = {1, 2, 3, 4};
    u4 result = moduleC_write_data(test_data, 4);
    
    EXPECT_EQ(4, result);
    EXPECT_EQ(1, u4g_mem_wirte_fake.call_count);
}

// テスト 2: 部分的な書き込み
TEST(ModuleCTest, WriteDataPartialSuccess) {
    RESET_FAKE(u4g_mem_wirte);
    u4g_mem_wirte_fake.return_val = 2;  // 2 バイトのみ書き込み成功
    
    u1 test_data[4] = {1, 2, 3, 4};
    u4 result = moduleC_write_data(test_data, 4);
    
    EXPECT_EQ(2, result);
    EXPECT_EQ(1, u4g_mem_wirte_fake.call_count);
}

// テスト 3: 空バッファ
TEST(ModuleCTest, WriteDataEmptyBuffer) {
    RESET_FAKE(u4g_mem_wirte);
    
    u1 test_data[1];
    u4 result = moduleC_write_data(test_data, 0);
    
    EXPECT_EQ(0, result);
    EXPECT_EQ(0, u4g_mem_wirte_fake.call_count);  // スタブは呼ばれない
}

// テスト 4: 複数呼び出し
TEST(ModuleCTest, WriteDataMultipleCalls) {
    RESET_FAKE(u4g_mem_wirte);
    u4g_mem_wirte_fake.return_val = 2;
    
    u1 data1[2] = {1, 2};
    u4 result1 = moduleC_write_data(data1, 2);
    
    u1 data2[2] = {3, 4};
    u4 result2 = moduleC_write_data(data2, 2);
    
    EXPECT_EQ(2, result1);
    EXPECT_EQ(2, result2);
    EXPECT_EQ(2, u4g_mem_wirte_fake.call_count);
}
```

## C/C++ 互換性の取り扱い

### プロジェクトのルール

**target/ フォルダ内のファイル**（C ソースコード）:

```c
// ❌ 禁止: #ifdef __cplusplus ブロックを入れない
// ❌ extern "C" を入れない
#include "common.h"
u4 moduleC_write_data(u1* data, u4 length) { ... }
```

**test/ フォルダ内のファイル**（C++ テストコード）:

```cpp
// ✅ 許可: extern "C" ブロックで C コードをラップ
extern "C" {
    #include "moduleC.h"
    #include "u4g_mem.h"
    #define DEFINE_FFF_GLOBALS
    #include "fff.h"
    FAKE_VALUE_FUNC2(u4, u4g_mem_wirte, u1*, u4);
}
```

### 理由

- C と C++ は関数名エンコーディングが異なる（C++ は名前空間のためにマングリング）
- target/ ファイルは C 言語として一貫性を保つ
- test/ ファイルで extern "C" を使用することで C/C++ 間の互換性を実現

## よくあるエラーと解決方法

### エラー 1: "undefined reference to u4g_mem_wirte"

**原因**: スタブがリンクされていない

**解決方法**:
1. `DEFINE_FFF_GLOBALS` を定義しているか確認
2. `FAKE_VALUE_FUNC2` 宣言を確認
3. CMakeLists.txt で test_moduleC.cpp がリンクされているか確認

### エラー 2: "u4g_mem_wirte_fake.call_count が 0"

**原因**: モジュール内で u4g_mem_wirte が呼ばれていない

**確認項目**:
1. moduleC_write_data 内で u4g_mem_wirte を呼んでいるか
2. 条件分岐で call_count が 0 になることはないか
3. 引数チェック（NULL や length == 0）で早期リターンしていないか

### エラー 3: "複数のテストで state が保持される"

**原因**: 前のテストで RESET_FAKE を呼んでいない

**解決方法**: 各テストの最初に RESET_FAKE を呼ぶ

```cpp
TEST(ModuleCTest, SomeTest) {
    RESET_FAKE(u4g_mem_wirte);  // 必須
    // ... テスト処理
}
```

## 高度な FFF テクニック

### セットアップ/テアダウン関数の使用

複数のテストで共通の初期化が必要な場合：

```cpp
class ModuleCTest : public ::testing::Test {
protected:
    void SetUp() override {
        RESET_FAKE(u4g_mem_wirte);
        u4g_mem_wirte_fake.return_val = 4;
    }
};

TEST_F(ModuleCTest, WriteDataSuccess) {
    // SetUp で自動的に初期化される
    u1 test_data[4] = {1, 2, 3, 4};
    u4 result = moduleC_write_data(test_data, 4);
    EXPECT_EQ(4, result);
}
```

### 複数のスタブを組み合わせる

```cpp
extern "C" {
    #include "moduleC.h"
    #define DEFINE_FFF_GLOBALS
    #include "fff.h"
    
    FAKE_VALUE_FUNC2(u4, u4g_mem_wirte, u1*, u4);
    FAKE_VALUE_FUNC1(s4, some_other_func, s4);
}

TEST(ModuleCTest, MultipleStubs) {
    RESET_FAKE(u4g_mem_wirte);
    RESET_FAKE(some_other_func);
    
    u4g_mem_wirte_fake.return_val = 4;
    some_other_func_fake.return_val = 100;
    
    // ... テスト処理
}
```

## FFF に関する参考情報

- **FFF GitHub**: https://github.com/meekrosoft/fff
- **ドキュメント**: fff.h 内のコメントに詳細記載
- **本プロジェクトの使用例**: `tests/moduleC/test_moduleC.cpp`
