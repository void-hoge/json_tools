### list option
- optionと部分一致した子要素を表示する。
- 何も指定しない場合は全部表示する。
- 標準出力

### select option
- optionは番号
- 直近のlistで表示した番号の子要素に移動する。
- move, backを実行するたびに番号は消える。
- エラーなどは標準エラー出力

### move option
- optionと完全一致した子要素に移動する。
- エラーなどは標準エラー出力

### back
- 親の階層に移動する。
- エラーなどは標準エラー出力

### dump option
- optionと完全一致した要素以下を展開して表示する。
- 何も指定しないと、現在の階層から展開して表示する。
- 標準出力(エラー以外)

### output filename command
- filenameというファイルを作成し、commandの内容(標準エラー出力以外)をそのファイルに書き出す。
- listとdumpにしか効果はないが、commandにそれ以外のコマンドを指定しても動く。
