To compile and run this you need to put 'libdhplay.so' from the Dahua SDK in your Libary path.

Requirements:

Based on: General_PlaySDK_Eng_Linux64_IS_V3.39.0.R.161116.zip


Usasge:

./davconvert <input.dav> <output.avi>

Convert AVI to MP4 with ffmpeg:

ffmpeg -i <input.avi> -vcodec copy <output.mp4>