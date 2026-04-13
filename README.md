# Chat Server (Multi-client TCP Server + Web UI)

## 📌 Overview

A multi-client TCP chat server written in **C** using sockets and pthreads, integrated with a **web-based UI** via a custom HTTP bridge.

---

## 🚀 Features

* Multi-client support (thread-per-client)
* Broadcast messaging
* Username-based chat
* Web UI (HTML/CSS/JS)
* Works on mobile + desktop (same network)
* Lightweight and efficient

---

## 🧠 Architecture

```
Browser (UI)
   ↓ HTTP
Web Bridge (C)
   ↓ TCP
Chat Server (C, pthreads)
```

* Thread-per-client model
* Mutex-protected shared client list
* HTTP bridge connects frontend with TCP server
## 🌐 Configuration (Important)

To run this project correctly on your system, you may need to update the IP address.

### 🔹 1. Frontend (`web/script.js`)

Update the base URL:

```javascript
const BASE_URL = "http://<YOUR-IP>:3000";
```

👉 Example:

```javascript
const BASE_URL = "http://192.168.0.103:3000";
```

---

### 🔹 2. Backend (`bridge/web_bridge.c`) *(Optional)*

If required, update the displayed IP in:

```c
printf("🌐 Open http://<YOUR-IP>:%d\n", PORT);
```

👉 This is only for display purposes and does not affect functionality.

---

### 🔹 How to Find Your IP

Run:

```bash
ipconfig
```

Look for:

```text
IPv4 Address: 192.168.x.x
```

---

### ⚠️ Important Notes

* Do NOT use `localhost` when accessing from mobile
* Ensure your phone and PC are on the same WiFi network
* Allow port **3000** in firewall if needed

---

### ✅ Recommended (Better Approach)

Instead of hardcoding IP, you can use:

```javascript
const BASE_URL = window.location.origin;
```

✔ Works automatically on any device
✔ No need to change IP manually

---

## ⚙️ Build & Run

### 1. Compile

```bash
gcc server/server.c server/client_handler.c server/server_utils.c -o build/server_app.exe -lws2_32 -pthread
gcc bridge/web_bridge.c -o build/web_bridge.exe -lws2_32
```

---

### 2. Run

```bash
build\server_app.exe
build\web_bridge.exe
```

---

### 3. Open in Browser

```
http://<YOUR-IP>:3000
```

👉 Example:

```
http://192.168.x.x:3000
```

---

## 📱 Mobile Access

* Connect phone to same WiFi
* Open:

```
http://<YOUR-IP>:3000
```

---

## 💬 Example Chat

```
Yash: Hello
Ravi: Hi
```

---

## ⚠️ Notes

* Do NOT use `localhost` on mobile
* Use your system IP (`ipconfig` / `ifconfig`)
* Ensure firewall allows port **3000**

---

## 🔮 Future Improvements

* Real-time chat (WebSockets)
* Authentication system
* Private messaging
* Chat history persistence
* Deployment support

---

## 🧑‍💻 Author

Yash Kodre
