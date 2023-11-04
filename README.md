# SDL で作ったゲームを tkinter に埋め込む

- tkinter に `winfo_id()` というメソッドがあってウィンドウハンドルが取得できる
- SDL で [SetParent()](https://learn.microsoft.com/ja-jp/windows/win32/api/winuser/nf-winuser-setparent) を使えば埋め込めるのでは？
- という実験
- いったん tkinter 側を親、SDL 側を子と呼ぶ
- 子のウィンドウを `SetParent()` する前にスタイルを変更する必要がある
  - [SetParent 関数 (winuser.h) - Win32 apps | Microsoft Learn](https://learn.microsoft.com/ja-jp/windows/win32/api/winuser/nf-winuser-setparent)
  - ```cpp
    auto style = GetWindowLong(child, GWL_STYLE);
    style &= ~WS_POPUP;
    style |= WS_CHILD;
    SetWindowLong(child, GWL_STYLE, style);
    ```
- 親が終了するときに子を終了させないと、子のプロセスが残ったままになった
  - `root.protocol("WM_DELETE_WINDOW", self.on_close)`
  - という感じで終了時の処理をオーバーライドして対応できそう
- リサイズイベントなどを子のプロセスに送らないといけないようだ
  - プロセスIDからプロセスハンドルを取る、あたりが面倒
- まあ後はプロセス間通信とかをやっていけばよさそう
