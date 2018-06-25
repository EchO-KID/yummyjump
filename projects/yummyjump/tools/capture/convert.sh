# Gstreamer tests. Not working.
#glretrace --snapshot-format=RGB -s - HelloCpp.1.trace | \
#    gst-launch-1.0 fdsrc ! \
#    videoparse width=800 height=600 format=rgbx framerate=60 ! \
#    videoflip method=5 ! videorate ! videoconvert ! \
#    video/x-raw-yuv,width=800,height=600,framerate=\(fraction\)30/1 \
#    x264enc pass=quant ! avimux ! filesink location=output.avi

#glretrace -sr HelloCpp.1.trace | \
    #gst-launch-1.0 fdsrc ! \
    #videoparse width=800 height=600 format=rgbx framerate=60 ! \
    #videoflip method=5 ! videorate ! videoconvert ! \
    #x264enc pass=quant ! avimux ! filesink location=output.avi


#glretrace --snapshot-format=RGB -s - HelloCpp.1.trace | \
#    gst-launch-1.0 fdsrc ! \
#    videoparse width=800 height=600 format=rgbx framerate=60 ! \
#    videoflip method=5 ! videorate ! videoconvert ! \
#    video/x-raw,format=AYUV,width=800,height=600,framerate=\(fraction\)30/1 !\
#    filesink location=output.avi

ffmpeg=~/Dev/bin/ffmpeg/ffmpeg
# Low quality mpeg video
#apitrace dump-images -o - HelloCpp.1.trace | \
#    $ffmpeg -r 60 -f image2pipe -vcodec ppm -i pipe: -vcodec mpeg4 -y output.mp4

# Options
# r: source framerate
# crf: quantizer scale range 0-51. 0 is lossless, 23 is default, and 51 is worst possible
# preset: slower preset will provide better compression. 
#       ultrafast,superfast, veryfast, faster, fast, medium, slow, slower, veryslow
# tune: film, animation, grain, stillimage, psnr, ssim, fastdecode, zerolatency
# Following configuration gives good compression and acceptable animation
#apitrace dump-images -o - $1 | \
#    $ffmpeg -r 60 -f image2pipe -vcodec ppm -i pipe: -c:v libx264 -preset slower -tune zerolatency -crf 18 -c:a copy output.mkv

mp4=output/output.mp4
mov=output/output.mov
trimmed=output/trimmed.trace
input=output/trimmed.trace
# Lossless encoding
# apitrace trim --exact --calls $2 -o $trimmed $1 # not working
apitrace dump-images -o - $1 | \
    $ffmpeg -y -re -r 60 -f image2pipe -vcodec ppm -i pipe: -c:v libx264 -acodec aac -ab 1600000 -ac 2 -preset medium -crf 22 -qp 0 -pix_fmt yuv444p -c:a copy $mp4
    
# convert to mov to import into iMovie
# && $ffmpeg -y -i $mp4 -vcodec qtrle $mov
