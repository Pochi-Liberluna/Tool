import subprocess

meta_data = subprocess.check_output(['netsh', 'wlan', 'show', 'profiles'])

data = meta_data.decode('UTF-8', errors ="backslashreplace")

data = data.split('\n')
#プロファイルのリスト作成(creat a list of profiles)
profiles = []

for i in data:
#各項目で「すべてのユーザー プロファイル」を見つける(find "All User Profile" in each item)
    if"All User Profile" in i :

#見つかったら(if found)
#アイテムを分割(split the item)
        i = i.split(":")

#インデックス1の項目がWi-Fi名に(item at index 1 will be the wifi name)
        i = i[1]

#名前をフォーマット(formatting the name)
#最初と最後の文字はあまり使わない(first and last character is use less)
        i = i[1:-1]

#リストの中のWi-Fi名を追加(appending the Wi-Fi name in the list)
        profiles.append(i)

#出力
print("{:<30}| {:<}".format("Wi-Fi Name", "Password"))
print("----------------------------------------------")

#プロファイルのトラバース(traversing the profiles)
for i in profiles:

    #try catch ブロックの開始(try catch block begins)
    #ブロックを試みる(try block)
    try:
        #メタデータと使用されているWi-Fi名とパスワードを取得(getting meta data with password using Wi-Fi name)
        results = subprocess.check_output(['netsh', 'wlan', 'show', 'profile', i, 'key=clear'])

        #データを行ごとにデコードして分割する(decoding and splitting data line by line)
        results = results.decode('UTF-8', errors="backslashreplace")
        results = results.split('\n')

        #結果リストからパスワードを見つける(finding the password from results list)
        results = [b.split(":")[1][1:-1] for b in results if "Key Content" in b]

        #パスワードがある場合は、パスワードを出力(if there is password it will print the password)
        try:
            print("{:<30}| {:<}".format(i, results[0]))

            #それ以外の場合は、パスワードの前に空白で出力(else it will print blank in front of password)
        except IndexError:
                        print("{:<30}| {:<}".format(i, ""))

#プロセスが失敗したら呼び出す(called when this process get failed)
    except subprocess.CalledProcessError:
                print("Encodeing Error Occured")
