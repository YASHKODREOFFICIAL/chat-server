const BASE_URL = "http://192.168.0.103:3000"; // 🔥 CHANGE THIS

async function sendMessage() {
  const msg = document.getElementById("message").value;

  if (!msg) return;

  await fetch(`${BASE_URL}/send`, {
    method: "POST",
    headers: {
      "Content-Type": "application/json"
    },
    body: JSON.stringify({ message: msg })
  });

  document.getElementById("message").value = "";
}

setInterval(async () => {
  const res = await fetch(`${BASE_URL}/messages`);
  const data = await res.json();

  document.getElementById("chat-box").innerHTML =
    data.map(m => `<p>${m}</p>`).join("");
}, 1000);