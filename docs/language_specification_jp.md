
# Fish言語仕様

## 各種構文

### ミラー

### 計算

四則演算は`+`、`-`、`*`、`,`の四つの演算子で定義されています。一般的に除算は`/`で行われますが、fishでは`/`は[ミラー](#ミラー)に使用されているため、`,`が除算演算子として使用されます。また、`%`が剰余演算子として使用されます。

どの演算子も同様に、スタックの上から2つの値を取り出し、計算結果をスタックに積みます。
仮にスタックが`XXXXAB`のときに`+`を実行すると、スタックは`XXXX(A+B)`になります。

型について、以下のように定義されています。

- 和、差、積、剰余 : (int, int) -> int、(float, float) -> float、(int, float) -> float、(float, int) -> float
- 商に関しては、数値2つをfloatにキャストしてから計算を行います。Python3の`//`ではなく、`/`と同じ動作をします。

次の場合はエラーとなります。

- スタックから2つの値を取り出せない場合はエラーとなります。
- `,`、`%`で0除算を行った場合はエラーとなります。

注意点として、`n`命令で出力する場合、`2.0`のような浮動小数点数は整数にキャストされ、`2`として出力されます。

#### 例

```fish
,;
comment: stack is empty.
comment: out something smells fishy...
```

```fish
42,n;
comment: 4 / 2 = 2
comment: out 2
```

```fish
5,2n;
comment: 5 / 2 = 2.5
comment: out 2.5
```

```fish
23,n;
comment: 2 / 3 = 0.666...
comment: out 0.6666666666666666
```

```fish
73%,n;
comment: 7 MOD 3 = 1
comment: out 1
```

```fish
701-3*%n;
comment: 7 MOD -3 = -2 (-3 * -3 + 2 = 7)
comment: out 1
```

```fish
12,23,%n;
comment: 0.5 MOD 0.666... = 0.5
comment: out 0.5
```

### シフト

`{`、`}`はそれぞれ左シフト、右シフトを行います。スタック全体を1つずつシフトします。
例えばスタックが`ABCD`のとき、`{`を実行すると`BCDA`になります。

次の場合はエラーとなります。

- スタックが空の場合はエラーとなります。

#### 例

```fish
1234{rnnnn;
comment: 1234 -> 2341 -> 1432
comment: out 2341
```

```fish
{;
comment: stack is empty.
comment: out something smells fishy...
```