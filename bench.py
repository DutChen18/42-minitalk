import asyncio
import sys
import time
import string
import random

async def run(text_in):
	server = await asyncio.create_subprocess_exec(
		"./server",
		stdout=asyncio.subprocess.PIPE,
		stderr=asyncio.subprocess.PIPE)
	pid_line = await server.stderr.readline()
	pid = int(pid_line.decode().split(": ")[1])
	client = await asyncio.create_subprocess_exec(
		"./client", str(pid), text_in)
	await client.wait()
	text_out = await server.stdout.read(len(text_in))
	server.terminate()
	await server.wait()
	return text_out

async def main():
	length = int(sys.argv[1])
	text_in = "".join(random.choice(string.printable) for _ in range(length))
	start = time.time()
	text_out = await run(text_in)
	delta = time.time() - start

	if text_in.encode() == text_out:
		kbps = int(len(text_in) / delta * 8 / 1024)
		print(f"ok {kbps} Kbps")
	else:
		print(f"error")

if __name__ == "__main__":
	asyncio.run(main())
