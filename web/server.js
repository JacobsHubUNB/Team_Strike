// TeamStrike web server: serves the UI and proxies commands to engine.exe
const http = require('http');
const path = require('path');
const fs = require('fs');
const { spawn } = require('child_process');

const PORT = process.env.PORT || 3117;
const ROOT = __dirname;
const ENGINE = path.join(ROOT, '..', 'engine.exe');

let engine = null;
let buffer = '';
let pending = null; // { resolve, log: [] }

function startEngine() {
  engine = spawn(ENGINE, [], { windowsHide: true });
  buffer = '';

  engine.stdout.on('data', (chunk) => {
    buffer += chunk.toString('utf8');
    let nl;
    while ((nl = buffer.indexOf('\n')) !== -1) {
      const line = buffer.slice(0, nl).replace(/\r$/, '');
      buffer = buffer.slice(nl + 1);
      if (!pending) continue;
      if (line.startsWith('STATE ')) {
        const { resolve, log } = pending;
        pending = null;
        let state = null;
        try { state = JSON.parse(line.slice(6)); } catch (e) { /* leave null */ }
        resolve({ log, state });
      } else if (line.trim() !== '') {
        pending.log.push(line);
      }
    }
  });

  engine.on('exit', () => {
    engine = null;
    if (pending) {
      const { resolve, log } = pending;
      pending = null;
      resolve({ log, state: null, error: 'engine exited' });
    }
  });
}

function sendCommand(cmd) {
  return new Promise((resolve, reject) => {
    if (!engine) startEngine();
    if (pending) return reject(new Error('another command is in flight'));
    pending = { resolve, log: [] };
    engine.stdin.write(cmd + '\n');
    setTimeout(() => {
      if (pending) {
        const { resolve: res, log } = pending;
        pending = null;
        res({ log, state: null, error: 'engine timed out' });
      }
    }, 5000);
  });
}

// Only allow the exact command shapes the engine understands
function validateCommand(body) {
  if (typeof body.cmd !== 'string') return null;
  const cmd = body.cmd.trim();
  if (/^new [^\r\n"\\]{1,40}$/.test(cmd)) return cmd;
  if (/^move [1-4] [wasd]$/.test(cmd)) return cmd;
  if (cmd === 'skip' || cmd === 'state') return cmd;
  return null;
}

const MIME = {
  '.html': 'text/html; charset=utf-8',
  '.js': 'text/javascript; charset=utf-8',
  '.css': 'text/css; charset=utf-8',
  '.svg': 'image/svg+xml',
  '.png': 'image/png',
};

const server = http.createServer((req, res) => {
  if (req.method === 'POST' && req.url === '/api/cmd') {
    let data = '';
    req.on('data', (c) => { data += c; if (data.length > 4096) req.destroy(); });
    req.on('end', async () => {
      let body;
      try { body = JSON.parse(data); } catch (e) { body = {}; }
      const cmd = validateCommand(body);
      if (!cmd) {
        res.writeHead(400, { 'Content-Type': 'application/json' });
        return res.end(JSON.stringify({ error: 'invalid command' }));
      }
      try {
        const result = await sendCommand(cmd);
        res.writeHead(200, { 'Content-Type': 'application/json' });
        res.end(JSON.stringify(result));
      } catch (e) {
        res.writeHead(409, { 'Content-Type': 'application/json' });
        res.end(JSON.stringify({ error: e.message }));
      }
    });
    return;
  }

  // Static files
  const urlPath = req.url === '/' ? '/index.html' : req.url.split('?')[0];
  const filePath = path.join(ROOT, path.normalize(urlPath));
  if (!filePath.startsWith(ROOT)) {
    res.writeHead(403); return res.end();
  }
  fs.readFile(filePath, (err, content) => {
    if (err) { res.writeHead(404); return res.end('not found'); }
    res.writeHead(200, { 'Content-Type': MIME[path.extname(filePath)] || 'application/octet-stream' });
    res.end(content);
  });
});

server.listen(PORT, () => {
  console.log(`TeamStrike server running at http://localhost:${PORT}`);
  startEngine();
});
