@echo off
echo 🔄 Killing old processes...
taskkill /IM server_app.exe /F >nul 2>&1
taskkill /IM web_bridge.exe /F >nul 2>&1

echo 🔨 Compiling server...
gcc server/server.c server/client_handler.c server/server_utils.c -o build/server_app.exe -lws2_32 -pthread

echo 🔨 Compiling bridge...
gcc bridge/web_bridge.c -o build/web_bridge.exe -lws2_32

echo 🚀 Starting server...
start cmd /k build\server_app.exe

timeout /t 2 >nul

echo 🌐 Starting web bridge...
start cmd /k build\web_bridge.exe

echo ✅ Done! Open browser:
echo http://192.168.0.103:3000
pause