# SDL で作ったゲームを tkinter に埋め込む

- tkinter に `winfo_id()` というメソッドがあってウィンドウハンドルが取得できる
- SDL で `[SetParent](https://learn.microsoft.com/ja-jp/windows/win32/api/winuser/nf-winuser-setparent)` を使えば埋め込めるのでは？
- という実験
