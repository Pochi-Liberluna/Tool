#IO::Socketモジュールを使用する
use IO::Socket;
 
#アクセス先ホストの指定
while($host eq ""){
print "X"x"50"."n";
print "URL(ホスト名)を入力してくださいn";
print "> http://";
$host = <stdin>;
chomp $host;
if($host eq "quit"){exit;}
}
 
#ポートを指定するかユーザーへ質問する
print "X"x"50"."n";
print "ポート番号を指定しますか？[y/n]";
$q_port = <stdin>;
print "指定しない場合は80番ポートへアクセスしますn";
chomp $q_port;
 
#yが入力されたらポート番号が入力されるまで待機
if ($q_port eq "y"){
print "X"x"50"."n";
print "ポートを指定しますn";
print "> ";
$port = <stdin>;
chomp $port;
}else{
$port = "80";
}
 
#乱数を追記させるかを確認
print "X"x"50"."n";
print "送信するデータに乱数を追加しますか？[y/n]";
$r = <stdin>;
chomp $r;
 
#ファイルの場所の指定
print "X"x"50"."n";
print "URL(ファイルの場所と送信データ)を入力してくださいn";
print "乱数を追加しますのでコメントのname=で終了してくださいn" if($r eq "y");
print "> http://$host/";
$bbs = <stdin>;
chomp $bbs;
$bbs = "/".$bbs;
 
#送信回数
print "X"x"50"."n";
print "ループさせる回数を指定してくださいn";
print "> ";
$loop = <stdin>;
chomp $loop;
if($loop eq "" || $loop eq "1"){
$loop = "2";
$ex = "1";
}
if($loop == "0"){
print "Error:0回のループは指定出来ません!n";
exit;
}
$loop-="1";
 
#スリープの設定
print "X"x"50"."n";
print "指定秒ウェイトを設定する場合は入力してくださいn";
print "> ";
$slp = <stdin>;
chomp $slp;
 
#指定させた数字になるまでループ
while($ex <= $loop){
print "X"x"50"."n";
$bbs2=$bbs;
#乱数格納
if ($r eq "y"){
$rr = rand("1000");
$bbs2.=$rr;
}
 
#送信数のインクリメント
$exd = $exd+"1";
print "$exd回目n";
 
#割合
if($loop ne ""){
$sa = int(($ex/$loop)*"100");
print "進行状況:&#91;$sa%/100%&#93;を完了しましたn";
$ex +="1";
}
 
#送信情報の出力
print "ホストへ以下の情報を送信中ですn";
print "$bbs2n";
#ホストへ接続を試みる
$socket = new IO::Socket::INET (
                                 PeerAddr => "$host",
                                 PeerPort => "$port",
                                 Proto => "tcp",
                                );
die "Error:ホストに接続できませんでした！n" unless $socket;
#送信
print $socket "GET $bbs2 HTTP/1.0nn";
close($socket);
 
#スリープ
print "$slp秒スリープしますn" if($slp ne "");
sleep $slp;
}
 
print "終了しましたn"
