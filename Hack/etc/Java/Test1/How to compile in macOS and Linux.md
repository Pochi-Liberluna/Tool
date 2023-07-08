# javacコマンドを使ったJavaコードのコンパイル方法
デスクトップにJavaコードをコンパイルする際に使うコマンドを配置して作業の効率化を図る。
</br>
## 作業
1.ターミナルを開き、'~/.bash_profile'または'~/.bashrc'ファイルを編集します（存在しない場合は新規作成）。
</br>
ファイルに以下のコードを追加しましょう。
</br>
```ruby:command.rb
export PATH=/usr/bin:/usr/local/bin:/path/to/javac
```
</br>
javacコマンドのフルパスを追加しましょう。そしたら、ファイルを保存(Ctrl+S)して閉じます。
</br>
ターミナルで'source ~/.bash_profileまたはsource ~/.bashrc'を実行し、環境変数を更新します。
</br>
2.デスクトップにシェルスクリプト(.sh)を作成します。
</br>
デスクトップ上で新しいテキストファイルを作成します。
テキストファイルの内容に以下のように書き込みます。compile.shで保存しましょう。
</br>
```shellscript:compile.sh
#!/bin/bash
javac ファイル名.java
```
</br>
ファイル名.javaは実際のファイル名に変更してください。
</br>
次に作成したシェルスクリプトに実行権限を付与します。ターミナルで「chmod +x /path/to/compile.sh」を実行してください。
</br>
'/path/to/compile.sh'を実際のシェルスクリプトのパスに置き換えます。
</br>
これで、デスクトップ上に作成したシェルスクリプトを実行することで、Javaファイルのコンパイルが簡単に行えるようになります。
