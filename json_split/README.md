# JSONファイルを分割するやつ
- テキストエディタが重すぎるのと、一覧性に欠けるので、最も表層の要素でファイルに分割する。
- shellの補完機能で検索とかがやりやすくなり、複数回実行することで階層的な構造も分割できる。
- hard-tabや、不要な改行があるとタブ揃えの関係でバグる。
- 気が向いたら直すかもしれないが、gameparams.jsonを読むのには問題ないので直さないかもしれない。

### ビルド
- makeするだけ

```
$ cd json_split
$ ls
README.md  main.cpp  makefile  sample.json
$ make
g++ -O2 main.cpp -o jsonsplit.out
$ ls
README.md jsonsplit.out main.cpp  makefile  sample.json
$
```

### 実行
- `./jsonsplit.out filename.json`のような感じで実行する。
- jsonファイル以外のものを食わせるとセグフォととかする気がする。
- たとえば`sample.json`を、`sample/`内に展開するときは以下のようになる。

```
$ ls
README.md jsonsplit.out main.cpp  makefile  sample.json
$ mkdir sample
$ cd sample/
$ cat ../sample.json
{
    "hoge":"poyo",
    "hogehoge":{
        "poyo": 1.0,
        "poe": true
    },
    "voidhoge":{
        "kyomu":[
            0.0,
            1.0
        ]
    }
}
$ ../jsonsplit.out ../sample.json
$ hoge.json  hogehoge.json  voidhoge.json
$ cat hogehoge.json
"hogehoge":{
    "poyo": 1.0,
    "poe": true
}⏎
$
```

### 備考
- 私は~/.bin/のPATHが通してあるのでここに入れるとどこからでも使える。(`jsonsplit filename.json`のような感じでどこからでも実行できる。)
- どこからでも使えるようにすると便利

```
$ mv jsonsplit.out jsonsplit
$ mv jsonsplit ~/.bin/
```
