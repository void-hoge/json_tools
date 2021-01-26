- jsonの中身を構造的に解析する。
- pwd:現在フォーカスしているオブジェクト。最初はroot
- list:部分一致する最表層のkeyを全部表示する。
- cd:完全一致する最表層のkeyを指定し、そこにpwoを移動する。
- add:出力用バッファに指定した最表層のキーとその値を追加する。
- output: ファイル名を指定し、addで生成されたデータ列をそのファイルに書く。
- end:終了

```
>>> list Ohio
PASB510_Ohio
PCEE293_Ohio_flag
>>> add Ohio
not found
>>> add PASB510_Ohio
>>> output PASB510_Ohio
>>> end
```
- これでOhioのデータが得られる。
