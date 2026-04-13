const BASE_URL = "http://192.168.0.103:3000"; // keep your IP

// 🔥 Ask username when page loads
let username = prompt("Enter your name:");

if (!username || username.trim() === "") {
  username = "Anonymous";
}

async function sendMessage() {
  const msg = document.getElementById("message").value;

  if (!msg) return;

  // 🔥 send username + message
  await fetch(`${BASE_URL}/send`, {
    method: "POST",
    headers: {
      "Content-Type": "application/json"
    },
    body: JSON.stringify({
      username: username,
      message: msg
    })
  });

  document.getElementById("message").value = "";
}

// 🔥 display messages (FIXED)
setInterval(async () => {
  const res = await fetch(`${BASE_URL}/messages`);
  const data = await res.json();

  document.getElementById("chat-box").innerHTML =
    data.map(m => `<p>${m}</p>`).join("");
}, 1000);