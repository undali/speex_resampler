import pyaudio
import sys

chunk = 1024
FORMAT = pyaudio.paInt16
CHANNELS = 1
RATE = 48000
RECORD_SECONDS = 20

p = pyaudio.PyAudio()
file = open('output_out.pcm', 'wb')

stream = p.open(format=FORMAT,
                channels=CHANNELS, 
                rate=RATE, 
                input=True,
                output=True,
                frames_per_buffer=chunk)

print("* recording")
#type(RATE / chunk * RECORD_SECONDS)
for i in range(0, int(RATE / chunk) * RECORD_SECONDS):
    data = stream.read(chunk)
    # check for silence here by comparing the level with 0 (or some threshold) for 
    # the contents of data.
    # then write data or not to a file
    file.write(data)

print("* done")
file.close()
stream.stop_stream()
stream.close()
p.terminate()